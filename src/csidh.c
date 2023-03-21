#include <string.h>
#include <assert.h>

#include "csidh.h"
#include "fp.h"
#include "primes.h"
#include "random.h"

#define primes_max_exponent 5

static int useoldxISOG = 0;

const public_key base = {0}; /* A = 0 */

/* Samples the private exponents $e_i \in [-B;B] */
void csidh_secret(secret_key *secret)
{
  memset(&secret->e, 0, sizeof(secret->e));
  for (long long i = 0; i < primes_num;)
  {
    // select random number
    int8_t buf[64];
    randombytes(buf, sizeof(buf));

    // split number into the private exponents
    for (size_t j = 0; j < sizeof(buf); ++j)
    {
      // in range?
      if (buf[j] <= primes_max_exponent && buf[j] >= -primes_max_exponent)
      {
        // secret->e is int_8 array, but we pack the exponentes in int_4.
        secret->e[i / 2] |= (buf[j] & 0xf) << i % 2 * 4;

        // done?
        if (++i >= primes_num)
          break;
      }
    }
  }
}

/* compute x^3 + Ax^2 + x */
static void montgomery_rhs(fp *rhs, fp const *A, fp const *x)
{
  fp tmp;
  *rhs = *x;
  fp_sq1(rhs);         // x^2
  fp_mul3(&tmp, A, x); // Ax
  fp_add2(rhs, &tmp);  // x^2+Ax
  fp_add2(rhs, &fp_1); // x^2+Ax+1
  fp_mul2(rhs, x);     // x*(x^2+Ax+1) = x^3+Ax^2+x
}

long long csidh_stattried[primes_batches];
long long csidh_statsucceeded[primes_batches];

/* totally not constant-time. */
void action(public_key *out, public_key const *in, secret_key const *secret)
{
  /* compare https://eprint.iacr.org/2018/782 for details on the algorithm*/

  uintbig k[2];
  k[0] = uintbig_p_cofactor;
  k[1] = uintbig_p_cofactor;

  uint8_t e[2][primes_num];

  for (long long i = 0; i < primes_num; ++i)
  {

    // retrive private exponent e_i
    int8_t t = (int8_t)(secret->e[i / 2] << i % 2 * 4) >> 4;

    // select sign & set exponent
    // compute k
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
    // checks if rhs is square
    bool sign = !fp_sqrt(&rhs); 

    if (done[sign])
      continue;

    xMUL_vartime(&P, &A, 0, &P, &k[sign]);

    done[sign] = true;

    for (long long i = primes_num - 1; i >= 0; --i)
    { // changed loop direction

      if (e[sign][i])
      {
        uintbig cof = uintbig_1;
        for (long long j = i - 1; j >= 0; --j) // changed loop direction
          if (e[sign][j])
            uintbig_mul3_64(&cof, &cof, primes[j]);

        proj K;
        xMUL_vartime(&K, &A, 0, &P, &cof);

        if (memcmp(&K.z, &fp_0, sizeof(fp)))
        {

          if (useoldxISOG)
            xISOG_old(&A, &P, &K, primes[i]);
          else
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
