#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "steps.h"
#include "csidh.h"
#include "primes.h"

static void test_iszero(void)
{
  printf("uintbig_iszero\n");
  fflush(stdout);

  uintbig u;
  unsigned char *x = (void *)&u;

  memset(x, 0, sizeof u);
  assert(uintbig_iszero(&u));

  for (unsigned long long i = 0; i < 8 * sizeof u; ++i)
  {
    memset(x, 0, sizeof u);
    x[i / 8] = 1 << (i & 7);
    assert(!uintbig_iszero(&u));
    for (unsigned long long j = 0; j < 8 * sizeof u; ++j)
    {
      memset(x, 0, sizeof u);
      x[i / 8] = 1 << (i & 7);
      x[j / 8] = 1 << (j & 7);
      assert(!uintbig_iszero(&u));
    }
  }
}

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

  for (long long loop = 0; loop < 1000; ++loop)
  {
    fp x;
    fp x2, x3, x4;
    fp x_comp;
    fp_random(&x);
    fp_sq2(&x2, &x);
    fp_mul3(&x3, &x2, &x);
    fp_mul3(&x4, &x3, &x);

    uintbig two, tree, four;
    uintbig_add3(&two, &uintbig_1, &uintbig_1);
    uintbig_add3(&tree, &two, &uintbig_1);
    uintbig_add3(&four, &tree, &uintbig_1);

    fp_exp2(&x_comp, &x, &two);
    assert(fp_isequal(&x_comp, &x2));

    fp_exp2(&x_comp, &x, &tree);
    assert(fp_isequal(&x_comp, &x3));

    fp_exp2(&x_comp, &x, &four);
    assert(fp_isequal(&x_comp, &x4));
  }
}

static void print_secret_key(secret_key const *sec_key)
{
  printf("[");
  for (int i = 0; i < secret_key_size; i++)
  {
    printf("e_%d:%d, ", i, sec_key->e[i]);
  }
  printf("\b\b]\n");
  fflush(stdout);
}

static void test_secret_key_gen()
{
  printf("secret_key_gen\n");
  fflush(stdout);
  secret_key sec_key;
  for (int try = 0; try < 100; try++)
  {
    csidh_secret(&sec_key);
    // print_sec_key(&sec_key);
    assert(sec_key.e[0] >= -137 && sec_key.e[0] <= 137);

    int i = 1;
    for (; i <= 3; i++)
      assert(sec_key.e[i] >= -4 && sec_key.e[i] <= 4);

#if BITS == 513
    for (; i <= 49; i++)
      assert(sec_key.e[i] >= -5 && sec_key.e[i] <= 5);
#elif BITS == 512
    for (; i <= 61; i++)
      assert(sec_key.e[i] >= -5 && sec_key.e[i] <= 5);
#endif

    for (; i < secret_key_size; i++)
      assert(sec_key.e[i] >= -4 && sec_key.e[i] <= 4);
  }
}

static void test_starting_curve()
{
  printf("starting_curve\n");
  fp tmp;
  fp_add3(&tmp, &fp_1, &fp_2); // 3
  fp sqrt_2 = fp_2;
  assert(fp_sqrt(&sqrt_2)); // sqrt(2)
  fp_inv(&sqrt_2);
  fp_mul2(&tmp, &sqrt_2); // 3/sqrt(2)

  if (!fp_isequal(&tmp, &base.A))
    fp_print(&tmp);

  assert(fp_isequal(&tmp, &base.A));
}

static void test_validate()
{
  printf("validate\n");
  fflush(stdout);

  int runs = 10;
  int good = 0;
  for (int i = 0; i < runs; i++)
  {
    good += validate(&base);
  }

  if (good != runs)
  {
    printf("\t%d/%d\n", good, runs);
    fflush(stdout);
  }

  assert(good == runs);
  // todo: include more tests
}

static void test_nike(void)
{
  printf("test_nike\n");
  fflush(stdout);

  secret_key sec_alice, sec_bob;
  public_key pub_alice, pub_bob;
  public_key shared_alice, shared_bob;

  for (long long bs = 0; bs <= 64; bs += 2)
  {
    for (long long gs = 0;; ++gs)
    {
      if (!gs)
        if (bs)
          continue;
      if (!bs)
        if (gs)
          break;
      if (2 * bs * gs > (primes[primes_num - 1] - 1) / 2)
        break;
      if (gs > 4 * bs)
        continue;
      if (bs > 4 * gs)
        continue;

      printf("trying alice bs=%lld gs=%lld, bob bs=0 gs=0\n", bs, gs);
      fflush(stdout);

      steps_override(bs, gs);

      // Alice
      csidh_secret(&sec_alice);
      assert(csidh(&pub_alice, &base, &sec_alice));
      assert(validate(&pub_alice));

      steps_override(0, 0);

      // Bob
      csidh_secret(&sec_bob);
      assert(csidh(&pub_bob, &base, &sec_bob));
      assert(validate(&pub_bob));

      // shared key: Bob
      assert(csidh(&shared_bob, &pub_alice, &sec_bob));
      assert(validate(&shared_bob));

      steps_override(bs, gs);

      // shared key: Alice
      assert(csidh(&shared_alice, &pub_bob, &sec_alice));
      assert(validate(&shared_alice));

      int shared_equal = !memcmp(&shared_alice, &shared_bob, sizeof(public_key));
      assert(shared_equal);
    }
  }
}

static void test_two_action()
{
  proj out;
  public_key key;
  for (int16_t i = -137; i <= 137; i++)
  //for (int16_t i = 0; i <= 2*137; i++)
  {
    printf(" %4d |", i);
    fflush(stdout);
    two_action(&out, &base, i);
    key.A = out.x;
    if (validate(&key))
    {
      printf(" :) \n");
      fflush(stdout);
    }
    else
    {
      printf(" :( \n");
      fflush(stdout);
    }
  }
}

// retruns 1 if x < p
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

int main()
{
  // test_2_action_twist();
  // test_two_action();
  test_sqrt();
  test_exp();
  test_starting_curve();
  //test_secret_key_gen();
  test_iszero();
  test_validate();
  test_nike();

  // test_dac();
  // test_elligator();
  // test_isog();
  return 0;
}
