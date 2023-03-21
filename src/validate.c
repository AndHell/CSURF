#include <string.h>
#include <assert.h>

#include "csidh.h"
#include "primes.h"

// XXX: use affine initial P to save time in xMUL

static int validate_rec(proj *P, proj const *A, long long lower, long long upper, uintbig *order, int *criticaltestdone)
{
  proj Q;
  proj A24;
  xA24(&A24, A);

  assert(lower < upper);

  if (upper - lower == 1)
  {
    // now P is [(p+1) / l_lower] times the original random point
    if (fp_iszero(&P->z))
      return 0;

    if (*criticaltestdone != 1)
    {
      // is original point times p+1 the identity? test this via first l that we see
      xMUL_dac(&Q, &A24, 1, P, primes_dac[lower], primes_daclen[lower], primes_daclen[lower]);
      if (!fp_iszero(&Q.z))
        return -1;
      *criticaltestdone = 1;
    }

    uintbig_mul3_64(order, order, primes[lower]);

    uintbig tmp;
    if (uintbig_sub3(&tmp, &uintbig_four_sqrt_p, order))
      return 1;
    return 0;
  }

  long long mid = lower + (upper - lower + 1) / 2;

  Q = *P;
  for (long long i = lower; i < mid; ++i)
    xMUL_dac(&Q, &A24, 1, &Q, primes_dac[i], primes_daclen[i], primes_daclen[i]);

  int result = validate_rec(&Q, A, mid, upper, order, criticaltestdone);
  if (result)
    return result;

  Q = *P;
  for (long long i = mid; i < upper; ++i)
    xMUL_dac(&Q, &A24, 1, &Q, primes_dac[i], primes_daclen[i], primes_daclen[i]);

  return validate_rec(&Q, A, lower, mid, order, criticaltestdone);
}

int validate_cutofforder_v2(uintbig *order, const fp *P, const fp *A)
{
  const proj Aproj = {*A, fp_1};
  proj Pproj = {*P, fp_1};
  proj A24;
  int criticaltestdone = 0;

  xA24(&A24, &Aproj);

  /* maximal 2-power in p+1 */
  xDBL(&Pproj, &Pproj, &A24, 1);
  xDBL(&Pproj, &Pproj, &A24, 1);

#if BITS == 512
  // temp cofactor 53 [index 14]
  xMUL_dac(&Pproj, &A24, 1, &Pproj, primes_dac[14], primes_daclen[14], primes_daclen[14]);
#elif BITS == 513
  // CSURF has additional cofactors 3 compared to csidh
  // for *3, we can use dac with 0,0,0
  xMUL_dac(&Pproj, &A24, 1, &Pproj, 0, 0, 0);
#endif

  *order = uintbig_1;
  return validate_rec(&Pproj, &Aproj, 0, primes_num, order, &criticaltestdone);
}

#if BITS != 511
/*
 * ... besides checking supersingularity, one should also verify that A±2 are both
 * squares: This indeed guarantees that the curve y²=x³+Ax²+x is located on the
 * surface, because it has 3 rational points of order 2 (the discriminant
 * A²−4=(A+2)(A−2) is a square), and that (0,0)=P→ thanks to Lemma 4.
 */
bool validate_csurf(fp const *A)
{
  // check if A±2 is a square
  long long out = 1;

  fp tmp;
  fp_sub3(&tmp, A, &fp_2);
  out &= fp_sqrt(&tmp); // A-2
  fp_add3(&tmp, A, &fp_2);
  out &= fp_sqrt(&tmp); // A+2

  if (out == 1)
    return true;

  return false;
}
#endif

// output: true if key is valid
// output: false if key is invalid
bool validate(public_key const *in)
{
  uintbig tmp;
  if (!uintbig_sub3(&tmp, &in->A.x, &uintbig_p))
    return false; // A >= p, invalid

  fp tmp2 = fp_2;
  if (!memcmp(&in->A, &tmp2, sizeof(fp)))
    return false; // A = 2, invalid
  fp_add2(&tmp2, &in->A);
  if (fp_iszero(&tmp2))
    return false; // A = -2, invalid

#if BITS != 511
  if (!validate_csurf(&in->A))
  {
    return false;
  }
#endif

  for (;;)
  {
    fp P;
    fp_random(&P);
    uintbig tmp;

    switch (validate_cutofforder_v2(&tmp, &P, &in->A))
    {
    case 1:
      return true;
    case -1:
      return false;
    }
    // case 0: P didn't have big enough order to prove supersingularity
  }
}
