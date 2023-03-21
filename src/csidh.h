#ifndef CSIDH_H
#define CSIDH_H

#include "uintbig.h"
#include "fp.h"
#include "mont.h"
#include "primes.h"
#include "csidh_namespace.h"

extern long long csidh_stattried[primes_batches];
extern long long csidh_statsucceeded[primes_batches];

#if BITS != 511 // csurf: we need int16 as e_0 in [-137..137]
typedef struct secret_key
{
  int16_t e[secret_key_size];
} secret_key;
#else
typedef struct secret_key
{
  int8_t e[secret_key_size];
} secret_key;
#endif

typedef struct public_key
{
  fp A; /* Montgomery coefficient: represents y² = x² + Ax² + x */
} public_key;

extern const public_key base;

void csidh_secret(secret_key *secret);

bool csidh(public_key *out, public_key const *in, secret_key const *secret);

int validate_cutofforder_v2(uintbig *order, const fp *P, const fp *A);
bool validate(public_key const *in);

// ToDo: remove after testing
void two_action(proj *out, public_key const *in, int16_t const secret_exp);

void action(public_key *out, public_key const *in, secret_key const *secret);

#endif
