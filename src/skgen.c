#include <string.h>
#include <assert.h>

#include "csidh.h"
#include "primes.h"
#include "random.h"

void csidh_secret(secret_key *secret)
{
  memset(&secret->e, 0, sizeof(secret->e));
  long long pos = 0;
  for (long long b = 0; b < primes_batches; ++b)
  {
    long long w = primes_batchsize[b];
    long long S = primes_batchbound[b];
    random_boundedl1(secret->e + pos, w, S);
    pos += w;
  }
  assert(pos <= primes_num);
}
