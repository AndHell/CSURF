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

  for (long long loop = 0; loop < 1000; ++loop)
  {
    fp x;
    fp xneg;
    fp x2;
    fp x2neg;
    fp_random(&x);
    fp_sq2(&x2, &x);
    fp_neg2(&xneg, &x);
    fp_neg2(&x2neg, &x2);
    assert(fp_sqrt(&x) != fp_sqrt(&xneg));
    assert(fp_sqrt(&x2));
    assert(!fp_sqrt(&x2neg));
  }

  fp tmp = fp_2;
  fp tmp2;
  fp_sq1(&tmp);
  fp_exp2(&tmp2, &tmp, &uintbig_p_add1_div4);
  fp_sq1(&tmp2);
  assert(fp_isequal(&tmp, &tmp2));
}

static void test_nike(void)
{
  secret_key sec_alice, sec_bob;
  public_key pub_alice, pub_bob;
  public_key shared_alice, shared_bob;
  bool ok;

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

      csidh_secret(&sec_alice);
      ok = csidh(&pub_alice, &base, &sec_alice);
      assert(ok);

      steps_override(0, 0);

      csidh_secret(&sec_bob);
      ok = csidh(&pub_bob, &base, &sec_bob);
      assert(ok);

      ok = csidh(&shared_bob, &pub_alice, &sec_bob);
      assert(ok);

      steps_override(bs, gs);

      ok = csidh(&shared_alice, &pub_bob, &sec_alice);
      assert(ok);

      assert(!memcmp(&shared_alice, &shared_bob, sizeof(public_key)));
    }
  }
}
int main()
{
  test_iszero();
  test_sqrt();
  // test_dac();
  // test_elligator();
  // test_validate();
  // test_isog();
  test_nike();
  return 0;
}
