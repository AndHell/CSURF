#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "fp.h"

static void test_sqrt(void)
{
  printf("fp_sqrt\n");
  fflush(stdout);

  fp x, xneg, x2, x2_, x2neg;

  for (long long loop = 0; loop < 100; ++loop)
  {
    fp_random(&x);
    fp_sq2(&x2, &x);                       // x²
    fp_sq2(&x2_, &x);                      // x²
    fp_neg2(&xneg, &x);                    // -x
    fp_neg2(&x2neg, &x2);                  // -x²
    assert(fp_sqrt(&x) != fp_sqrt(&xneg)); // either x or -x is a square
    assert(fp_sqrt(&x2));                  // x² must be square
    assert(!fp_sqrt(&x2neg));              // then -x² must not be square

    fp_exp2(&x2_, &x2_, &uintbig_p_add1_div4); // (x²)^{p+1/4}
    assert(fp_isequal(&x2, &x2_));             // (x²)^{p+1/4} == sqrt(x²)
  }
}

static void test_exp(void)
{
  printf("fp_exp\n");
  fflush(stdout);
  fp x;
  fp x2, x3, x4;
  fp x_comp;

  uintbig two, tree, four;
  uintbig_add3(&two, &uintbig_1, &uintbig_1); // 2
  uintbig_add3(&tree, &two, &uintbig_1);      // 3
  uintbig_add3(&four, &tree, &uintbig_1);     // 4


  for (long long loop = 0; loop < 1000; ++loop)
  {
 
    fp_random(&x);            // x
    fp_sq2(&x2, &x);          // x²
    fp_mul3(&x3, &x2, &x);    // x³
    fp_mul3(&x4, &x3, &x);    // x^4

    fp_exp2(&x_comp, &x, &two);
    assert(fp_isequal(&x_comp, &x2));   // check x²

    fp_exp2(&x_comp, &x, &tree);
    assert(fp_isequal(&x_comp, &x3));   // check x³

    fp_exp2(&x_comp, &x, &four);
    assert(fp_isequal(&x_comp, &x4));   // check x^4
  }
}

// returns 1 if x < p
static bool is_in_fp(fp const *x)
{
  for (int i = (sizeof(fp) / 8) - 1; i >= 1; i--)
  {
    if (x->x.c[i] < uintbig_p.c[i])
      return true;
    if (x->x.c[i] == uintbig_p.c[i] && x->x.c[i - 1] < uintbig_p.c[i - 1])
      return true;
    if (x->x.c[i] > uintbig_p.c[i])
      break;
  }
  return false;
}

static void test_fp()
{
  printf("fp_1_fp_2\n");
  fflush(stdout);
  fp tmp1, tmp2;

  fp_add3(&tmp1, &fp_1, &fp_1);
  assert(fp_isequal(&tmp1, &fp_2));

  fp_add3(&tmp1, &fp_2, &fp_2);     // 2+2
  fp_mul3(&tmp2, &fp_2, &fp_2);     // 2*2
  assert(fp_isequal(&tmp1, &tmp2)); // 2+2 == 2*2

  fp_sq2(&tmp1, &fp_2);                        // 2²
  fp_sq2(&tmp2, &fp_2);                        // 2²
  fp_exp2(&tmp2, &tmp2, &uintbig_p_add1_div4); // sqrt(2²) as x^(p+1)/4
  fp_sq1(&tmp2);

// fails for CSURF_512
#if BITS == 513
  assert(fp_isequal(&tmp1, &tmp2)); // 2² == sqrt(2²)²
  assert(fp_sqrt(&tmp1));           // sqrt(4)
  assert(fp_sqrt(&tmp1));           // sqrt(2)
#endif

  int ok = 0;
  int runs = 100;
  fp x;
  for (int i = 0; i < runs; i++)
  {
    fp_random(&x);
    assert(is_in_fp(&x));

    fp_mul3(&tmp1, &x, &fp_1);
    assert(fp_isequal(&tmp1, &x)); // x*1 == x

    fp_mul3(&tmp1, &x, &fp_2);
    fp_add3(&tmp2, &x, &x);
    ok += fp_isequal(&tmp1, &tmp2); // x+x == x*2
  }

// fails for CSURF_512 (in ~20% of the tests)
  printf("x+x == x*2: %d/%d\n", ok, runs);
  fflush(stdout);

  printf("fp_inv_sqrt\n");
  fflush(stdout);
  int ok_inv = 0;
  int ok_inv_1 = 0;
  int ok_sqrt = 0;
  int ok_sqrt_p1d4 = 0;
  for (int i = 0; i < runs; i++)
  {
    fp_random(&x);
    tmp1 = x;
    fp_inv(&tmp1);
    fp_mul3(&tmp2, &tmp1, &x); // x/x
    fp_inv(&tmp1);
    ok_inv += fp_isequal(&tmp1, &x);      // (x^-1)^-1 == x
    ok_inv_1 += fp_isequal(&tmp2, &fp_1); // x/x == 1

    fp_sq2(&tmp1, &x);                           // x²
    fp_mul3(&tmp2, &x, &x);                      // x*x
    assert(fp_isequal(&tmp1, &tmp2));            // x² == x*x
    ok_sqrt += fp_sqrt(&tmp1);                   // sqrt(x²)
    fp_exp2(&tmp2, &tmp2, &uintbig_p_add1_div4); // (x²)^{p+1/4}
    ok_sqrt_p1d4 += fp_isequal(&tmp1, &tmp2);    // (x²)^{p+1/4} == sqrt(x²)
  }

// fail allways
  printf("(x^-1)^-1 == x:  %d/%d\n", ok_inv, runs);
  printf("x/x == 1: \t %d/%d\n", ok_inv_1, runs);
  printf("sqrt(x²): \t %d/%d\n", ok_sqrt, runs);
  printf("(x²)^{p+1/4} == sqrt(x²): %d/%d\n", ok_sqrt_p1d4, runs);
  fflush(stdout);

  assert(ok == runs);
  assert(ok_inv == runs);
  assert(ok_inv_1 == runs);
  assert(ok_sqrt == runs);
  assert(ok_sqrt_p1d4 == runs);
}

int main()
{
  test_fp();
  test_exp();
  test_sqrt();
}
