#ifndef FP_H
#define FP_H

#include "uintbig.h"
#include "fp_namespace.h"
#include <stdio.h>

/* fp is in the Montgomery domain, so interpreting that
   as an integer should never make sense.
   enable compiler warnings when mixing up uintbig and fp. */
typedef struct fp
{
  uintbig x;
} fp;

extern const fp fp_0;
extern const fp fp_1;
extern const fp fp_2;

void fp_cswap(fp *x, fp *y, long long c);      /* c is 0 or 1 */
void fp_cmov(fp *x, const fp *y, long long c); /* c is 0 or 1 */

void fp_copy(fp *x, fp const *y);

void fp_add2(fp *x, fp const *y);
void fp_sub2(fp *x, fp const *y);
void fp_mul2(fp *x, fp const *y);

void fp_add3(fp *x, fp const *y, fp const *z);
void fp_sub3(fp *x, fp const *y, fp const *z);
void fp_mul3(fp *x, fp const *y, fp const *z);

void fp_sq1(fp *x);
void fp_sq2(fp *x, fp const *y);

extern long long fp_mulsq_count;
extern long long fp_sq_count;
extern long long fp_addsub_count;

static inline void fp_sq1_rep(fp *x, long long n)
{
  while (n > 0)
  {
    --n;
    fp_sq1(x);
  }
}

static inline void fp_neg1(fp *x)
{
  fp_sub3(x, &fp_0, x);
}

static inline void fp_neg2(fp *x, const fp *y)
{
  fp_sub3(x, &fp_0, y);
}

static inline void fp_double1(fp *x)
{
  fp_add2(x, x);
}

static inline void fp_double2(fp *x, const fp *y)
{
  fp_add3(x, y, y);
}

static inline void fp_quadruple2(fp *x, const fp *y)
{
  fp_double2(x, y);
  fp_double1(x);
}

static inline void fp_quadruple1(fp *x)
{
  fp_double1(x);
  fp_double1(x);
}

static inline long long fp_iszero(const fp *x)
{
  return uintbig_iszero(&x->x);
}

static inline long long fp_isequal(const fp *x, const fp *y)
{
  return uintbig_isequal(&x->x, &y->x);
}

void fp_inv(fp *x);

// if x is a square: replace x by principal sqrt and return 1
// else: return 0
long long fp_sqrt(fp *x);

// square and multiply
static inline void fp_exp2(fp *out, const fp *x, const uintbig *exp)
{
  long long exp_bits = uintbig_bits_vartime(exp);

  long long exp_i;
  fp exp_tmp0 = fp_1;
  fp exp_tmp1 = fp_1;
  for (exp_i = exp_bits - 1; exp_i >= 0; --exp_i)
  {
    fp_sq1(&exp_tmp0);                // t  = t^2
    fp_mul3(&exp_tmp1, &exp_tmp0, x); // t' = t*x
    fp_cswap(&exp_tmp0, &exp_tmp1, uintbig_bit(exp, exp_i));
  }

  out->x = exp_tmp0.x;
}

#include "randombytes.h"
#include "crypto_declassify.h"

static inline void fp_print(fp *x)
{
  uintbig_print(&x->x);
}

static inline void fp_random(fp *x)
{
  for (;;)
  {
    randombytes(x, sizeof(fp));

#if BITS == 513
    // HACK
    x->x.c[8] &= 1; // drop bits outsite of range

    for (int i = (sizeof(fp) / 8) - 1; i >= 1; i--)
    {
      if (x->x.c[i] < uintbig_p.c[i])
        return;
      if (x->x.c[i] == uintbig_p.c[i] && x->x.c[i - 1] < uintbig_p.c[i - 1])
        return;
      if (x->x.c[i] > uintbig_p.c[i])
        break;
    }
#else
    uintbig diff;
    long long accept = uintbig_sub3(&diff, &x->x, &uintbig_p);

    crypto_declassify(&accept, sizeof accept);
    if (accept)
      return;
#endif
  }
}

#endif
