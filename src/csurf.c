#include <string.h>
#include <assert.h>

#include "csidh.h"
#include "fp.h"
#include "primes.h"
#include "random.h"

#define primes_max_exponent_reduced 4
#define primes_max_exponent 5
#define e_0_max_exponent_137 137
#define e_0_max_exponent_75 75
#define e_0_max_exponent_50 50

#define KEY_SPACE 1 // 137
// #define KEY_SPACE 2 // 75A
// #define KEY_SPACE 3 // not used
// #define KEY_SPACE 4 // 75B
// #define KEY_SPACE 5 // 50A
// #define KEY_SPACE 6 // 50B

/*
# CSURF-513
e_0       in [-137..137]
e_1..3    in [-4..4]
e_4..49   in [-5..5]   // 46
e_50..74  in [-4..4]   // 28

cmp csurf_summer_school lecture note Example 3
and https://github.com/TDecru/CSURF/blob/c056c3156597767f020bed57333c460e762ba37e/csurf_512.m#L137

# CSURF-512(137)
(2*137+1)*(2*5+1)^57*(2*4+1)^19
e_0       in [-137..137]
e_1..3    in [-4..4]
e_4..60   in [-5..5]   // 57
e_61..73  in [-4..4]   // 16

# CSURF-512(75A)
(2*75+1)*(2*5+1)^60*(2*4+1)^13
e_0       = 75
e_1 ..e_3  = 4
e_4 ..e_63 = 5
e_64..e_73 = 4

# CSURF-512(75B)
(2*75+1)*(2*6+1)^2*(2*5+1)^58*(2*4+1)^11*(2*3+1)^2
e_0       = 75
e_1 ..e_2 =  3    -> 2 x 3
e_3 ..e_3  = 4    -> 1 x 4
e_4 ..e_19 = 5    -> 16x 5
e_20..e_21 = 6    -> 2 x 6
e_22..e_63 = 5    -> 42x 5
e_64..e_73 = 4    -> 10x 4

# CSURF-512(50A)
(2*50+1)*(2*5+1)^62*(2*4+1)^11
e_0       = 50
e_1 ..e_3  = 4  -> 3x  4
e_4 ..e_65 = 5  -> 62x 5
e_66..e_73 = 4  -> 8x  4

# CSURF-512(50B)
(2*50+1)*(2*6+1)^4*(2*5+1)^54*(2*4+1)^15)
e_0       = 50
e_1 ..e_3  = 4   -> 3 x 4
e_4 ..e_19 = 5   -> 16x 5
e_20..e_23 = 6   -> 4 x 6
e_24..e_61 = 5   -> 38x 5
e_62..e_73 = 4   -> 12x 4
*/

#if BITS == 512
/* A = 3 / sqrt(2) */
const public_key base = {0x03fcf5c9b8ca327e, 0xb8468f3c56d01ef1, 0xf8c7575b2df78935, 0x37980419e03a4525,
                         0xea50cc97e380fe98, 0x4a5c3d62db1031c5, 0x9654a3cb0a86c476, 0x2ac258c5ae598d97};
#elif BITS == 513
/* A = 3 / sqrt(2) */
const public_key base = {0xc1ca36846a58e5d1, 0xf683fe26db27e241, 0x149e670192d559db,
                         0x23d25eb5a184643a, 0xbbee046c0752d3e0, 0xb2f623a2f42db626,
                         0x6f2c7dfb441a83de, 0x054efde5c4275f97, 0x0000000000000000};
#else
#error BITS must be 512 or 513 for CSURF
#endif

/* Samples the private exponents e_i */
void csidh_secret(secret_key *secret)
{
  memset(&secret->e, 0, sizeof(secret->e));

  // e_0 in [-137..137]
  while (true)
  {
    int16_t buf = 0;
    randombytes(&buf, sizeof(buf));
    // in range?
#if BITS == 513
    if (buf <= e_0_max_exponent_137 && buf >= -e_0_max_exponent_137)
#elif BITS == 512
#if KEY_SPACE == 1 
    if (buf <= e_0_max_exponent_137 && buf >= -e_0_max_exponent_137)
#elif KEY_SPACE == 5 || KEY_SPACE == 6
    if (buf <= e_0_max_exponent_50 && buf >= -e_0_max_exponent_50)
#else
    if (buf <= e_0_max_exponent_75 && buf >= -e_0_max_exponent_75)
#endif
#endif
    {
      secret->e[0] = buf;
      break;
    }
  }

  for (long long i = 1; i < secret_key_size;)
  {
    // select random number
    int8_t buf[64];
    randombytes(buf, sizeof(buf));

    // split number into the private exponents
    for (size_t j = 0; j < sizeof(buf); ++j)
    {
      int16_t max_exponent = primes_max_exponent;

#if BITS == 513
      if (i <= 3 || i >= 50)
        max_exponent = primes_max_exponent_reduced;
#elif BITS == 512

#if KEY_SPACE == 1   // 137
      if (i <= 3 || i >= 61)
        max_exponent = primes_max_exponent_reduced;

// EXPERIMENT  75: new keyspace : 75*2-isogs
#elif KEY_SPACE == 2 // 75A
      if (i <= 3 || i >= 64)
        max_exponent = primes_max_exponent_reduced;

#elif KEY_SPACE == 4 // 75B
      if (i <= 2)
        max_exponent = 3;
      else if (i == 3 || i >= 64)
        max_exponent = 4;
      else if (i == 20 || i == 21)
        max_exponent = 6;

// EXPERIMENTS  50: new keyspace : 50*2-isogs
#elif KEY_SPACE == 5 // 50A
      if (i <= 3 || i >= 66)
        max_exponent = primes_max_exponent_reduced;
#elif KEY_SPACE == 6 // 50B
      if (i <= 3 || i >= 62)
        max_exponent = 4;
      else if (i >= 20 && i <= 23)
        max_exponent = 6;
#endif
#endif

      // in range?
      if (buf[j] <= max_exponent && buf[j] >= -max_exponent)
      {
        secret->e[i] = buf[j];

        // done?
        if (++i >= secret_key_size)
          break;
      }
    }
  }
}

/* For e_0 < 0, we walk the two-action in the other direction. For this
 * we use the Point P← at (0,0) instead of P→. Using the quadratic twist
 * with -A puts P← at (0,0). However, the following algorithm assumes P→ at
 * (0,0), so we need to find P→ and move it to the origin. This can be done
 * by finding the roots z_{1,2} of x³-Ax²+x=x(x^2-Ax+1), rescaling it by
 * x ← (x+z_{1,2}). This ends up on a curve of the from x³-ax²+bx+c,
 * however c is allways 0. If b is a square, then the correct z was picked
 * and we can proceed. Otherwise the other root z puts P→ at the origin.
 */
static void two_action_twist(fp *out_a, fp *out_b, fp const *in_A)
{
  fp fp_3, tmp_0, tmp_1, tmp_2, tmp_3, A, z, a, b;

  fp_add3(&fp_3, &fp_1, &fp_2);

  fp_neg2(&A, in_A); // A = -A

  // build up pq-formula
  tmp_1 = fp_2;
  fp_inv(&tmp_1);
  fp_mul3(&tmp_1, &A, &tmp_1); // A/2
  fp_sq2(&tmp_0, &tmp_1);      // (A/2)²
  fp_sub2(&tmp_0, &fp_1);      // (A/2)² - 1
  assert(fp_sqrt(&tmp_0));     // sqrt((A/2)² - 1)

  // compute root z
  fp_neg1(&tmp_1);             // -A/2
  fp_add3(&z, &tmp_1, &tmp_0); // -A/2 + sqrt((A/2)² - 1)

  fp_mul3(&tmp_3, &fp_2, &z); // 2z
  fp_mul2(&tmp_3, &A);        // 2zA

  // rescale B to b
  fp_sq2(&tmp_2, &z);             // z²
  fp_mul3(&tmp_2, &fp_3, &tmp_2); // 3z²
  fp_add2(&tmp_2, &tmp_3);
  fp_add3(&b, &tmp_2, &fp_1); // 3z²+2zA+1

  // check if b is a sqaure
  fp_copy(&tmp_3, &b);
  if (!fp_sqrt(&tmp_3))
  {
    // guess was wrong. use z_2 instead
    fp_sub3(&z, &tmp_1, &tmp_0); // -A/2 - sqrt((A/2)² - 1)

    fp_mul3(&tmp_3, &fp_2, &z); // 2z
    fp_mul2(&tmp_3, &A);        // 2zA

    fp_sq2(&tmp_2, &z);             // z²
    fp_mul3(&tmp_2, &fp_3, &tmp_2); // 3z²
    fp_add2(&tmp_2, &tmp_3);
    fp_add3(&b, &tmp_2, &fp_1); // 3z²+2zA+1
  }

  // rescale A to a
  fp_mul3(&tmp_2, &fp_3, &z); // 3z
  fp_add3(&a, &tmp_2, &A);    // a = 3z+A

  fp_copy(out_a, &a);
  fp_copy(out_b, &b);
}

/* compute x³ + Ax² + x */
static void montgomery_rhs(fp *rhs, fp const *A, fp const *x)
{
  fp tmp;
  *rhs = *x;
  fp_sq1(rhs);         // x²
  fp_mul3(&tmp, A, x); // Ax
  fp_add2(rhs, &tmp);  // x²+Ax
  fp_add2(rhs, &fp_1); // x²+Ax+1
  fp_mul2(rhs, x);     // x*(x²+Ax+1) = x³+Ax²+x
}

long long csidh_stattried[primes_batches];
long long csidh_statsucceeded[primes_batches];

/* compare csurf_summer_school lecture notes
 *
 * (form Section 5)
 * Summing up, in the first step one determines P→ using the basic approach,
 * after which one rewrites the curve in the form (4). Then one iteratively
 * computes β = b (p+1)/4 and substitutes a ← a + 6β, b ← 4β(a + 2β).
 *
 * (4) y²=x³+ax²+bx  P→ = (0,0)
 *
 * (From Section 6)
 * When computing isogenies of odd degree using the formulae from [13, §4], the
 * property (0, 0) = P→ is preserved. Thus the action of [l_1]^e_1 .. [l_r]^e_r
 * can be evaluated exactly as in the case of CSIDH. As for the action of
 * [l_0]e^0: if e_0 is positive then we proceed as in Section 5, where we note
 * that the first instance of P→ comes for free [..]. If e_0 is negative then we
 * resort to (2): we switch to the quadratic twist, proceed as in Section 5, and
 * twist back.
 *
 * 1. if e_0 < 0: use twist (see two_action_twist)
 * 2. x³+Ax²+x  to  x³+ax²+bx for P→ = (0,0)
 * 3. for 0..|exp|
 * 	3.1 β = b^(p+1)/4
 *	3.2 b ← 4β(a+2β)
 *	3.3 a ← a+6β
 * 4. x³+ax²+bx  to  x³+Ax²+x
 * 5. if e_0 < 0: twist back
 * 6. return A
 */
void two_action(proj *out, public_key const *in, int16_t const secret_exp)
{
  // get |exp|
  uint8_t exp_abs = (uint8_t)(secret_exp < 0 ? -secret_exp : secret_exp);

  fp a = in->A;
  fp b = fp_1;
  fp beta, two_beta, four_beta, six_beta, a_two_beta;

  // use -A as twist for P<-
  // cmp csurf_summer_school Exercise 14

  if (secret_exp < 0)
  {
    two_action_twist(&a, &b, &in->A);
  }

  // x³+Ax²+x  to  x³+ax²+bx
  // with a=A and b=1
  // this step is "free"

  for (uint8_t i = 0; i < exp_abs; i++)
  {
    beta = b; // β = b^(p+1)/4 = sqrt(b)
    assert(fp_sqrt(&beta));
    fp_double2(&two_beta, &beta);              // 2β
    fp_double2(&four_beta, &two_beta);         // 4β
    fp_add3(&six_beta, &four_beta, &two_beta); // 6β

    // calc b' first, to avoid using a'
    fp_add3(&a_two_beta, &a, &two_beta);  // (a+2β)
    fp_mul3(&b, &four_beta, &a_two_beta); // b ← 4β(a+2β)

    fp_add2(&a, &six_beta); // a ← a+6β
  }

  // x³+ax²+bx  to  x³+Ax²+x
  // with A = a/sqrt(b)
  assert(fp_sqrt(&b));
  fp_inv(&b);
  fp_mul2(&a, &b); // A = a/sqrt(b)

  // twist back
  if (secret_exp < 0)
  {
    two_action_twist(&a, &b, &a);
    assert(fp_sqrt(&b));
    fp_inv(&b);
    fp_mul2(&a, &b); // A = a/sqrt(b)
  }

  out->x = a;
}

/* totally not constant-time. */
void action(public_key *out, public_key const *in, secret_key const *secret)
{
  uintbig k[2];

  // init k with the cofactors
  k[0] = uintbig_p_cofactor;
  k[1] = uintbig_p_cofactor;

  uint8_t e[2][primes_num];
  int16_t e_0 = (int16_t)secret->e[0];

  for (long long i = 0; i < primes_num; ++i)
  {
    // retrive private exponent e_i
    // (use i+1 as we skip the first index for e_0 (2^e_0))
    int8_t t = (int8_t)secret->e[i + 1];

    if (t > 0)
    {
      e[0][i] = t;
      e[1][i] = 0;
      uintbig_mul3_64(&k[1], &k[1], primes[i]);
    }
    else if (t < 0)
    {
      e[1][i] = -t;
      e[0][i] = 0;
      uintbig_mul3_64(&k[0], &k[0], primes[i]);
    }
    else
    {
      e[0][i] = 0;
      e[1][i] = 0;
      uintbig_mul3_64(&k[0], &k[0], primes[i]);
      uintbig_mul3_64(&k[1], &k[1], primes[i]);
    }
  }

  // starting curve
  proj A = {in->A, fp_1};

  two_action(&A, in, e_0);

  bool done[2] = {false, false};

  do
  {
    assert(!memcmp(&A.z, &fp_1, sizeof(fp)));

    // sample random point
    proj P;
    fp_random(&P.x);
    P.z = fp_1;

    fp rhs;
    montgomery_rhs(&rhs, &A.x, &P.x);
    bool sign = !fp_sqrt(&rhs);

    if (done[sign])
      continue;
      
    xMUL_vartime(&P, &A, 0, &P, &k[sign]);

    done[sign] = true;

    for (long long i = primes_num - 1; i >= 0; --i)
    {
      if (e[sign][i])
      {
        uintbig cof = uintbig_1;
        for (long long j = i - 1; j >= 0; --j)
          if (e[sign][j])
            uintbig_mul3_64(&cof, &cof, primes[j]);

        proj K;
        xMUL_vartime(&K, &A, 0, &P, &cof);

        if (memcmp(&K.z, &fp_0, sizeof(fp)))
        {
          xISOG(&A, &P, 1, &K, primes[i]);

          if (!--e[sign][i])
            uintbig_mul3_64(&k[sign], &k[sign], primes[i]);
        }
      }

      done[sign] &= !e[sign][i];
    }

    fp_inv(&A.z);
    fp_mul2(&A.x, &A.z);
    A.z = fp_1;

  } while (!(done[0] && done[1]));

  out->A = A.x;
}

/* includes public-key validation. */
bool csidh(public_key *out, public_key const *in, secret_key const *secret)
{
  if (!validate(in))
  {
    fp_random(&out->A);
    return false;
  }
  action(out, in, secret);
  return true;
}
