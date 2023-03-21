#!/usr/bin/env python3

import sim
import distmults
import costs
import chain
import sys
import re
import random
from pyexpat import model
import math
import os
data = (
  # (511, 'csidh',  # same CSIDH-512 prime but only 2^220 keys
  #  (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
  #     71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
  #    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
  #    263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 
  #    373, 587),
  #  (2, 3, 4, 4, 5, 5, 5, 5, 5, 7, 7, 8, 7, 6, 1),
  #  (6, 9, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 8, 6, 1),
  #  ),
  (511, 'csidh', 4,
    (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
       71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
      163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 
      263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 
      373, 587),
    (2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 6, 8, 1),
    (10, 14, 16, 17, 17, 17, 18, 18, 18, 18, 18, 13, 13, 1),
  ),
  (512, 'csurf',  4*2*53,
    # start with 3 as we handle 2 action seperatly
    # ONLY FOR TESTING
    # ONLY 73 primes beside 2, need to update keyspace
    (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
       71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
      163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 241, 251, 257, 263, 
      269, 271, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 379, 383, 389, 397, 
      401),
    (2, 3, 4, 4, 4, 5, 6, 7, 7, 8, 8, 6, 8, 1),
    (10, 14, 16, 17, 17, 17, 18, 18, 18, 18, 18, 13, 13, 1),
  ),
  (513, 'csurf',  4*3*2, # orginal paramter
    # start with 3 as we handle 2 action seperatly
    # first 75 primes, skip 347 and 359
    (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
       71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
      163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
      263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 349, 353, 367, 373, 379, 
      383, 389),
    (2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 6, 8, 1),
    (10, 14, 16, 17, 17, 17, 18, 18, 18, 18, 18, 13, 13, 1),
  ),
  # (1024, 'csidh',
  #  (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
  #     71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
  #    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
  #    263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 
  #    373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 
  #    479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 
  #    601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 
  #    719, 727, 733, 983),
  #  (2, 3, 5, 4, 6, 6, 6, 6, 6, 7, 7, 7, 6, 7, 7, 5, 6, 5, 10, 3, 10, 5, 1),
  #  (2, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 3, 6, 2, 6, 2, 0)
  #  ),
  # (2048, 'csidh',
  #  (   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67, 
  #     71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 
  #    163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
  #    263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 
  #    373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 
  #    479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 
  #    601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709,
  #    719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 
  #    839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 
  #    971, 977, 983, 991, 997 1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087, 
  #   1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,
  #   1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,
  #   1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,3413),
  #  (9, 10, 8, 8, 7, 10, 12, 11, 10, 15, 10, 9,
  #   8, 6, 10, 13, 10, 9, 12, 13, 10, 10, 10, 1),
  #  (1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 0, 2, 0)
  #  )
)


sys.setrecursionlimit(10000)


def maybeupdate(fn):
  if os.access(fn, os.F_OK):
    with open(fn) as f:
      x = f.read()
    with open(fn+'.tmp') as f:
      y = f.read()
    if x == y:
      os.unlink(fn+'.tmp')
      return
  os.rename(fn+'.tmp', fn)


def batchkeys(x, y):
  poly = [1]
  for i in range(x):
    newpoly = poly+[0]
    for j in range(len(poly)):
      newpoly[j+1] += poly[j]
    poly = newpoly
  for i in range(y):
    newpoly = poly+[0]
    for j in range(len(poly)):
      newpoly[j+1] += 2*poly[j]
    poly = newpoly
  return poly[x]


def dac_search(target, r0, r1, r2, chain, chainlen, best, bestlen):
  if chainlen >= bestlen:
    return best, bestlen
  if r2 > target:
    return best, bestlen
  if r2 << (bestlen-1-chainlen) < target:
    return best, bestlen
  if r2 == target:
    return chain, chainlen
  chain *= 2
  chainlen += 1
  best, bestlen = dac_search(
      target, r0, r2, r0+r2, chain+1, chainlen, best, bestlen)
  best, bestlen = dac_search(
      target, r1, r2, r1+r2, chain, chainlen, best, bestlen)
  return best, bestlen


def dac(target):
  best = None
  bestlen = 0
  while best == None:
    bestlen += 1
    best, bestlen = dac_search(target, 1, 2, 3, 0, 0, best, bestlen)
  return best, bestlen


for bits, mode, cofac, primes, batchsize, batchbound in data:
  fn = 'primes_{0}_{1}.c'.format(mode, bits)
  with open(fn+'.tmp', 'w') as f:
    f.write('// DO NOT EDIT! generated by ./autogen\n\n')
    f.write('#include "primes.h"\n')
    f.write('\n')
    keys = 1
    for s, b in zip(batchsize, batchbound):
      keys *= batchkeys(s, b)
    f.write('// number of keys: %d\n' % keys)
    f.write('// approximately 2^%f\n' % math.log(keys, 2))
    f.write('\n')
    f.write('// average costs (calculated):\n')
    x = distmults.average(primes, batchsize, batchbound)
    f.write(costs.strstats(x, '// ', '%.6f', primes, batchsize).strip()+'\n')
    f.write('\n')

    trials = 4096
    f.write('// average costs (%d simulated trials):\n' % trials)
    y = {}
    for trial in range(trials):
      x = sim.trial(primes, batchsize, batchbound)
      for cost in x:
        if cost not in y:
          y[cost] = 0
        y[cost] += x[cost]
    for cost in y:
      y[cost] *= 1.0/trials
    f.write(costs.strstats(y, '// ', '%.6f', primes, batchsize).strip()+'\n')
    f.write('\n')

    f.write('const long long primes[primes_num] = {\n')
    f.write(' ')
    for l in primes:
      assert l < 2**63
      f.write(' %d,' % l)
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    primesdac = [dac(l) for l in primes]
    f.write('const long long primes_dac[primes_num] = {\n')
    f.write(' ')
    for D in primesdac:
      assert D[0] < 2**63
      f.write(' %d,' % D[0])
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_daclen[primes_num] = {\n')
    f.write(' ')
    for D in primesdac:
      assert D[1] < 2**63
      f.write(' %d,' % D[1])
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_batchsize[primes_batches] = {\n')
    f.write(' ')
    for s in batchsize:
      f.write(' %d,' % s)
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_batchstart[primes_batches] = {\n')
    f.write(' ')
    pos = 0
    for s in batchsize:
      f.write(' %d,' % pos)
      pos += s
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_batchstop[primes_batches] = {\n')
    f.write(' ')
    pos = 0
    for s in batchsize:
      pos += s
      f.write(' %d,' % pos)
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_batchmaxdaclen[primes_batches] = {\n')
    f.write(' ')
    pos = 0
    for s in batchsize:
      f.write(' %d,' % max(D[1] for D in primesdac[pos:pos+s]))
      pos += s
    f.write('\n')
    f.write('};\n')
    f.write('\n')
    f.write('const long long primes_batchbound[primes_batches] = {\n')
    f.write(' ')
    for s in batchbound:
      f.write(' %d,' % s)
    f.write('\n')
    f.write('};\n')
  maybeupdate(fn)

fn = 'primes.h'
with open(fn+'.tmp', 'w') as f:
  f.write('// DO NOT EDIT! generated by ./autogen\n\n')
  f.write('#ifndef primes_h\n')
  f.write('#define primes_h\n')
  f.write('\n')
  f.write('#include "primes_namespace.h"\n')
  f.write('\n')

  hashif = '#if'
  for bits, mode, cofac, primes, batchsize, batchbound in data:
    f.write('%s BITS == %d // %s\n' % (hashif, bits, mode))
    f.write('#define primes_num %d\n' % len(primes))
    key_size = len(primes)
    if mode == 'csurf':
      key_size += 1
    f.write('#define secret_key_size %d\n' % key_size)
    f.write('#define primes_batches %d\n' % len(batchsize))
    m = max(b+s for b, s in zip(batchbound, batchsize))
    f.write('#define primes_maxbatchboundplussize %d\n' % m)
    hashif = '#elif'

  f.write('#else\n')
  orbits = ' or '.join('%d' % bits for bits, mode, cofac, primes,
                       batchsize, batchbound in data)
  f.write('#error BITS must be %s\n' % orbits)
  f.write('#endif\n')
  f.write('\n')
  f.write('extern const long long primes[primes_num];\n')
  f.write('extern const long long primes_dac[primes_num];\n')
  f.write('extern const long long primes_daclen[primes_num];\n')
  f.write('extern const long long primes_batchsize[primes_batches];\n')
  f.write('extern const long long primes_batchstart[primes_batches];\n')
  f.write('extern const long long primes_batchstop[primes_batches];\n')
  f.write('extern const long long primes_batchbound[primes_batches];\n')
  f.write('extern const long long primes_batchmaxdaclen[primes_batches];\n')
  f.write('\n')
  f.write('#endif\n')
maybeupdate(fn)


def writeconst(f, n, limbs):
  assert n >= 0

  nquad = []
  while n:
    nquad += [n % (1 << 64)]
    n >>= 64

  while len(nquad) < limbs:
    nquad += [0]
  assert len(nquad) == limbs

  while len(nquad) > 0:
    nquad4, nquad = nquad[:4], nquad[4:]
    f.write('    .quad %s\n' % ', '.join('%d' %
                                         x if x < 10 else '0x%016x' % x for x in nquad4))


def FermatPrimalityTest(n):
  for _ in range(20):
    rand = random.randint(2, n)-1
    if (pow(rand, n-1, n) != 1):
      return False
  return True


for bits, mode, cofactor, primes, batchsize, batchbound in data:
  p = cofactor
  for l in primes:
    p *= l
  p -= 1

  print(mode, p)
  assert(p % 4 == 3)
  if mode == 'csurf':
    assert(p % 8 == 7)
  assert(FermatPrimalityTest(p))

  p_add1_div4 = (p+1)//4

  pbits = 0
  while (1 << pbits) <= p:
    pbits += 1
  # pbytes = (pbits+63)//8
  plimbs = (pbits+63)//64
  pbytes = plimbs*8
  pmontbits = 64*plimbs

  # this asserts we have space to do math
  assert(pbits < pmontbits)

  sqrt16p = 1
  while True:
    if sqrt16p**2 <= 16*p and (sqrt16p+1)**2 > 16*p:
      break
    sqrt16p = (sqrt16p+(16*p)//sqrt16p)//2

  inv = 2**64-pow(p, 2**62-1, 2**64)

  invchain = chain.chain2(p-2)
  invchaincost = chain.cost2(invchain)

  fn = 'fp_{0}_inv_{1}.c'.format(mode, bits)
  with open(fn+'.tmp', 'w') as f:
    f.write('// DO NOT EDIT! generated by ./autogen\n\n')
    f.write('#include "fp.h"\n')
    f.write('\n')
    f.write('// %s mults, %s squarings\n' % invchaincost)
    f.write('void fp_inv(fp *x)\n')
    f.write('{\n')
    f.write(chain.code(invchain))
    f.write('}\n')
  maybeupdate(fn)

  sqrtchain = chain.chain2((p+1)//4)
  sqrtchaincost = chain.cost2(sqrtchain)

  fn = 'fp_{0}_sqrt_{1}.c'.format(mode, bits)
  with open(fn+'.tmp', 'w') as f:
    f.write('// DO NOT EDIT! generated by ./autogen\n\n')
    f.write('#include "fp.h"\n')
    f.write('\n')
    f.write('// %s mults, %s squarings\n' %
            (sqrtchaincost[0], sqrtchaincost[1]+1))
    f.write('long long fp_sqrt(fp *x)\n')
    f.write('{\n')
    f.write('  fp origx = *x;\n')
    f.write(chain.code(sqrtchain))
    f.write('  fp check; fp_sq2(&check,x);\n')
    f.write('  return fp_isequal(&check,&origx);\n')
    f.write('}\n')
  maybeupdate(fn)

  fn = 'uintbig_{0}_{1}.S'.format(mode, bits)
  with open(fn+'.tmp', 'w') as f:
    f.write('/* DO NOT EDIT! generated by ./autogen */\n\n')
    f.write('.intel_syntax noprefix\n')
    f.write('\n')
    f.write('#include "uintbig_namespace.h"\n')
    f.write('\n')
    f.write('.section .rodata\n')
    f.write('\n')

    f.write('.global uintbig_1\n')
    f.write('uintbig_1:\n')
    writeconst(f, 1, plimbs)
    f.write('\n')

    f.write('.global uintbig_p\n')
    f.write('uintbig_p:\n')
    writeconst(f, p, plimbs)
    f.write('\n')

    f.write('.global uintbig_p_cofactor\n')
    f.write('uintbig_p_cofactor:\n')
    writeconst(f, cofactor, plimbs)
    f.write('\n')

    f.write('.global uintbig_four_sqrt_p\n')
    f.write('uintbig_four_sqrt_p:\n')
    writeconst(f, sqrt16p, plimbs)
    f.write('\n')

    f.write('.global uintbig_p_add1_div4\n')
    f.write('uintbig_p_add1_div4:\n')
    writeconst(f, p_add1_div4, plimbs)
    f.write('\n')

    f.write('.section .text\n')
    f.write('\n')
    f.write('.global uintbig_set\n')
    f.write('uintbig_set:\n')
    f.write('    cld\n')
    f.write('    mov rax, rsi\n')
    f.write('    stosq\n')
    f.write('    xor rax, rax\n')
    f.write('    mov rcx, %d\n' % (plimbs-1))
    f.write('    rep stosq\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('\n')
    f.write('.global uintbig_bit\n')
    f.write('uintbig_bit:\n')
    f.write('    mov rcx, rsi\n')
    f.write('    and rcx, 0x3f\n')
    f.write('    shr rsi, 6\n')
    f.write('    mov rax, [rdi + 8*rsi]\n')
    f.write('    shr rax, cl\n')
    f.write('    and rax, 1\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('\n')
    f.write('.global uintbig_add3\n')
    f.write('uintbig_add3:\n')
    f.write('    mov rax, [rsi +  0]\n')
    f.write('    add rax, [rdx +  0]\n')
    f.write('    mov [rdi +  0], rax\n')
    f.write('    .set k, 1\n')
    f.write('    .rept %d\n' % (plimbs-1))
    f.write('        mov rax, [rsi + 8*k]\n')
    f.write('        adc rax, [rdx + 8*k]\n')
    f.write('        mov [rdi + 8*k], rax\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('    setc al\n')
    f.write('    movzx rax, al\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('.global uintbig_sub3\n')
    f.write('uintbig_sub3:\n')
    f.write('    mov rax, [rsi +  0]\n')
    f.write('    sub rax, [rdx +  0]\n')
    f.write('    mov [rdi +  0], rax\n')
    f.write('    .set k, 1\n')
    f.write('    .rept %d\n' % (plimbs-1))
    f.write('        mov rax, [rsi + 8*k]\n')
    f.write('        sbb rax, [rdx + 8*k]\n')
    f.write('        mov [rdi + 8*k], rax\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('    setc al\n')
    f.write('    movzx rax, al\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('\n')
    f.write('.global uintbig_mul3_64\n')
    f.write('uintbig_mul3_64:\n')
    f.write('\n')
    f.write('    mulx r10, rax, [rsi +  0]\n')
    f.write('    mov [rdi +  0], rax\n')
    f.write('\n')
    for i in range(1, plimbs):
      if i & 1:
        f.write('    mulx r11, rax, [rsi + %d]\n' % (8*i))
        if i == 1:
          f.write('    add  rax, r10\n')
        else:
          f.write('    adcx rax, r10\n')
        f.write('    mov [rdi + %d], rax\n' % (8*i))
      else:
        f.write('    mulx r10, rax, [rsi + %d]\n' % (8*i))
        f.write('    adcx rax, r11\n')
        f.write('    mov [rdi + %d], rax\n' % (8*i))
      f.write('\n')
    f.write('    ret\n')

  maybeupdate(fn)

  fn = 'fp_{0}_{1}.S'.format(mode, bits)
  with open(fn+'.tmp', 'w') as f:
    f.write('/* DO NOT EDIT! generated by ./autogen */\n\n')
    f.write('.intel_syntax noprefix\n')
    f.write('\n')
    f.write('#include "uintbig_namespace.h"\n')
    f.write('#include "fp_namespace.h"\n')
    f.write('\n')
    f.write('.section .rodata\n')
    f.write('\n')
    f.write('.set pbits,%d\n' % pbits)
    f.write('.set pbytes,%d\n' % pbytes)
    f.write('.set plimbs,%d\n' % plimbs)

    f.write('.inv_min_p_mod_r: /* -p^-1 mod 2^64 */\n')
    writeconst(f, inv, 1)
    f.write('\n')

    f.write('.global fp_0\n')
    f.write('fp_0:\n')
    f.write('    .zero %d\n' % pbytes)
    f.write('\n')

    f.write('.global fp_1\n')
    f.write('fp_1: /* 2^%d mod p */\n' % pmontbits)
    writeconst(f, (1 << pmontbits) % p, plimbs)
    f.write('\n')

    f.write('.global fp_2\n')
    f.write('fp_2: /* 2^%d mod p */\n' % (pmontbits+1))
    writeconst(f, (1 << (pmontbits+1)) % p, plimbs)
    f.write('\n')

    f.write('.r_squared_mod_p: /* (2^%d)^2 mod p */\n' % pmontbits)
    writeconst(f, (1 << (2*pmontbits)) % p, plimbs)
    f.write('\n')


    # f.write('.global p_minus_2\n')
    # f.write('p_minus_2:\n')
    # writeconst(f,p-2,plimbs)
    # f.write('\n')

    f.write('.p_minus_1_halves:\n')
    writeconst(f, (p-1)//2, plimbs)
    f.write('\n')

    f.write('.section .data\n')
    f.write('.global fp_mulsq_count\n')
    f.write('fp_mulsq_count:\n')
    f.write('    .quad 0\n')
    f.write('.global fp_sq_count\n')
    f.write('fp_sq_count:\n')
    f.write('    .quad 0\n')
    f.write('.global fp_addsub_count\n')
    f.write('fp_addsub_count:\n')
    f.write('    .quad 0\n')
    f.write('\n')
    f.write('.section .text\n')
    f.write('.p2align 4,,15\n')
    f.write('\n')
    f.write('.global fp_copy\n')
    f.write('fp_copy:\n')
    f.write('    cld\n')
    f.write('    mov rcx, plimbs\n')
    f.write('    rep movsq\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('.global fp_cmov\n')
    f.write('fp_cmov:\n')
    f.write('    movzx rax, dl\n')
    f.write('    neg rax\n')
    f.write('    .set k, 0\n')
    f.write('    .rept plimbs\n')
    f.write('        mov rcx, [rdi + 8*k]\n')
    f.write('        mov rdx, [rsi + 8*k]\n')
    f.write('\n')
    f.write('        xor rdx, rcx\n')
    f.write('        and rdx, rax\n')
    f.write('        xor rcx, rdx\n')
    f.write('\n')
    f.write('        mov [rdi + 8*k], rcx\n')
    f.write('\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('.global fp_cswap\n')
    f.write('fp_cswap:\n')
    f.write('    movzx rax, dl\n')
    f.write('    neg rax\n')
    f.write('    .set k, 0\n')
    f.write('    .rept plimbs\n')
    f.write('        mov rcx, [rdi + 8*k]\n')
    f.write('        mov rdx, [rsi + 8*k]\n')
    f.write('\n')
    f.write('        mov r8, rcx\n')
    f.write('        xor r8, rdx\n')
    f.write('        and r8, rax\n')
    f.write('\n')
    f.write('        xor rcx, r8\n')
    f.write('        xor rdx, r8\n')
    f.write('\n')
    f.write('        mov [rdi + 8*k], rcx\n')
    f.write('        mov [rsi + 8*k], rdx\n')
    f.write('\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('.reduce_once:\n')
    f.write('    push rbp\n')
    if plimbs > 8:
      f.write('    sub rsp, %d\n' % (8*(plimbs-8)))
    f.write('    mov rbp, rdi\n')
    f.write('\n')

    regs = ('rdi', 'rsi', 'rdx', 'rcx', 'r8', 'r9', 'r10', 'r11')
    for i in range(plimbs):
      regi = regs[i % len(regs)]+', '
      if len(regi) < 5:
        regi += ' '
      f.write('    mov %s[rbp + %d]\n' % (regi, i*8))
      if i == 0:
        f.write('    sub %s[rip + uintbig_p + %d]\n' % (regi, i*8))
      else:
        f.write('    sbb %s[rip + uintbig_p + %d]\n' % (regi, i*8))
      if i < plimbs-8:
        f.write('    movq [rsp + %d], %s\n' % (8*i, regs[i % len(regs)]))

    f.write('\n')
    f.write('    setnc al\n')
    f.write('    movzx rax, al\n')
    f.write('    neg rax\n')
    f.write('\n')
    f.write('.macro cswap2, r, m\n')
    f.write('    xor \\r, \\m\n')
    f.write('    and \\r, rax\n')
    f.write('    xor \\m, \\r\n')
    f.write('.endm\n')
    f.write('\n')

    for i in range(plimbs-8, plimbs):
      regi = regs[i % len(regs)]
      f.write('    cswap2 %s, [rbp + %d]\n' % (regi, 8*i))

    for i in range(plimbs-8):
      regi = regs[i % len(regs)]
      f.write('    movq %s, [rsp + %d]\n' % (regs[i % len(regs)], 8*i))
      f.write('    cswap2 %s, [rbp + %d]\n' % (regi, 8*i))
    f.write('\n')

    if plimbs > 8:
      f.write('    add rsp, %d\n' % (8*(plimbs-8)))
    f.write('    pop rbp\n')
    f.write('    ret\n')
    f.write('\n')
    f.write('.global fp_add2\n')
    f.write('fp_add2:\n')
    f.write('    mov rdx, rdi\n')
    f.write('.global fp_add3\n')
    f.write('fp_add3:\n')
    f.write('    addq [fp_addsub_count+rip],1\n')
    f.write('    push rdi\n')
    f.write('    call uintbig_add3\n')
    f.write('    pop rdi\n')
    f.write('    jmp .reduce_once\n')
    f.write('\n')
    f.write('.global fp_sub2\n')
    f.write('fp_sub2:\n')
    f.write('  mov rdx, rdi\n')
    f.write('  xchg rsi, rdx\n')
    f.write('.global fp_sub3\n')
    f.write('fp_sub3:\n')
    f.write('    addq [fp_addsub_count+rip],1\n')
    f.write('    push rdi\n')
    f.write('    call uintbig_sub3\n')
    f.write('    pop rdi\n')

    f.write('    neg rax\n')
    f.write('\n')
    f.write('    sub rsp, pbytes\n')
    f.write('\n')
    f.write('    mov rcx, [rip + uintbig_p +  0]\n')
    f.write('    and rcx, rax\n')
    f.write('    mov [rsp + 0],rcx\n')
    f.write('    .set k, 1\n')
    f.write('    .rept plimbs-1\n')
    f.write('        mov rcx, [rip + uintbig_p + 8*k]\n')
    f.write('        and rcx, rax\n')
    f.write('        mov [rsp + 8*k], rcx\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('\n')
    f.write('    mov rcx, [rsp +  0]\n')
    f.write('    add rcx, [rdi +  0]\n')
    f.write('    mov [rdi +  0], rcx\n')
    f.write('    .set k, 1\n')
    f.write('    .rept plimbs-1\n')
    f.write('        mov rcx, [rsp + 8*k]\n')
    f.write('        adc rcx, [rdi + 8*k]\n')
    f.write('        mov [rdi + 8*k], rcx\n')
    f.write('        .set k, k+1\n')
    f.write('    .endr\n')
    f.write('\n')
    f.write('    add rsp, pbytes\n')

    f.write('    ret\n')
    f.write('\n')
    f.write('\n')
    f.write('/* Montgomery arithmetic */\n')
    f.write('\n')
    f.write('.global fp_mul2\n')
    f.write('fp_mul2:\n')
    f.write('  mov rdx, rdi\n')

    f.write('.global fp_mul3\n')
    f.write('fp_mul3:\n')
    f.write('    push rbp\n')
    f.write('    push rbx\n')

    if plimbs == 8:
      f.write('    push r12\n')
      f.write('    push r13\n')
      f.write('    push r14\n')
      f.write('    push r15\n')
      f.write('\n')
      f.write('    push rdi\n')
      f.write('\n')
      f.write('    addq [fp_mulsq_count+rip],1\n')
      f.write('\n')
      f.write('    mov rdi, rsi\n')
      f.write('    mov rsi, rdx\n')
      f.write('\n')
      f.write('    xor r8,  r8\n')
      f.write('    xor r9,  r9\n')
      f.write('    xor r10, r10\n')
      f.write('    xor r11, r11\n')
      f.write('    xor r12, r12\n')
      f.write('    xor r13, r13\n')
      f.write('    xor r14, r14\n')
      f.write('    xor r15, r15\n')
      f.write('    xor rbp, rbp\n')
      f.write('\n')
      f.write('    /* flags are already cleared */\n')
      f.write('\n')
      f.write('.macro MULSTEP, k, r0, r1, r2, r3, r4, r5, r6, r7, r8\n')
      f.write('\n')
      f.write('    mov rdx, [rsi +  0]\n')
      f.write('    mulx rcx, rdx, [rdi + 8*\\k]\n')
      f.write('    add rdx, \\r0\n')
      f.write('    mulx rcx, rdx, [rip + .inv_min_p_mod_r]\n')
      f.write('\n')
      f.write('    xor rax, rax /* clear flags */\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rip + uintbig_p +  0]\n')
      f.write('    adox \\r0, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rip + uintbig_p +  8]\n')
      f.write('    adcx \\r1, rbx\n')
      f.write('    adox \\r1, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rip + uintbig_p + 16]\n')
      f.write('    adcx \\r2, rcx\n')
      f.write('    adox \\r2, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rip + uintbig_p + 24]\n')
      f.write('    adcx \\r3, rbx\n')
      f.write('    adox \\r3, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rip + uintbig_p + 32]\n')
      f.write('    adcx \\r4, rcx\n')
      f.write('    adox \\r4, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rip + uintbig_p + 40]\n')
      f.write('    adcx \\r5, rbx\n')
      f.write('    adox \\r5, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rip + uintbig_p + 48]\n')
      f.write('    adcx \\r6, rcx\n')
      f.write('    adox \\r6, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rip + uintbig_p + 56]\n')
      f.write('    adcx \\r7, rbx\n')
      f.write('    adox \\r7, rax\n')
      f.write('\n')
      f.write('    mov rax, 0\n')
      f.write('    adcx \\r8, rcx\n')
      f.write('    adox \\r8, rax\n')
      f.write('\n')
      f.write('\n')
      f.write('    mov rdx, [rdi + 8*\\k]\n')
      f.write('\n')
      f.write('    xor rax, rax /* clear flags */\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rsi +  0]\n')
      f.write('    adox \\r0, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rsi +  8]\n')
      f.write('    adcx \\r1, rbx\n')
      f.write('    adox \\r1, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rsi + 16]\n')
      f.write('    adcx \\r2, rcx\n')
      f.write('    adox \\r2, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rsi + 24]\n')
      f.write('    adcx \\r3, rbx\n')
      f.write('    adox \\r3, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rsi + 32]\n')
      f.write('    adcx \\r4, rcx\n')
      f.write('    adox \\r4, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rsi + 40]\n')
      f.write('    adcx \\r5, rbx\n')
      f.write('    adox \\r5, rax\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rsi + 48]\n')
      f.write('    adcx \\r6, rcx\n')
      f.write('    adox \\r6, rax\n')
      f.write('\n')
      f.write('    mulx rcx, rax, [rsi + 56]\n')
      f.write('    adcx \\r7, rbx\n')
      f.write('    adox \\r7, rax\n')
      f.write('\n')
      f.write('    mov rax, 0\n')
      f.write('    adcx \\r8, rcx\n')
      f.write('    adox \\r8, rax\n')
      f.write('\n')
      f.write('.endm\n')
      f.write('\n')
      f.write('    MULSTEP 0, r8,  r9,  r10, r11, r12, r13, r14, r15, rbp\n')
      f.write('    MULSTEP 1, r9,  r10, r11, r12, r13, r14, r15, rbp, r8\n')
      f.write('    MULSTEP 2, r10, r11, r12, r13, r14, r15, rbp, r8,  r9\n')
      f.write('    MULSTEP 3, r11, r12, r13, r14, r15, rbp, r8,  r9,  r10\n')
      f.write('    MULSTEP 4, r12, r13, r14, r15, rbp, r8,  r9,  r10, r11\n')
      f.write('    MULSTEP 5, r13, r14, r15, rbp, r8,  r9,  r10, r11, r12\n')
      f.write('    MULSTEP 6, r14, r15, rbp, r8,  r9,  r10, r11, r12, r13\n')
      f.write('    MULSTEP 7, r15, rbp, r8,  r9,  r10, r11, r12, r13, r14\n')
      f.write('\n')
      f.write('    pop rdi\n')
      f.write('\n')
      f.write('    mov [rdi +  0], rbp\n')
      f.write('    mov [rdi +  8], r8\n')
      f.write('    mov [rdi + 16], r9\n')
      f.write('    mov [rdi + 24], r10\n')
      f.write('    mov [rdi + 32], r11\n')
      f.write('    mov [rdi + 40], r12\n')
      f.write('    mov [rdi + 48], r13\n')
      f.write('    mov [rdi + 56], r14\n')
      f.write('\n')
      f.write('    pop r15\n')
      f.write('    pop r14\n')
      f.write('    pop r13\n')
      f.write('    pop r12\n')
    else:
      f.write('\n')
      f.write('  addq [fp_mulsq_count+rip],1\n')
      f.write('\n')
      f.write('  sub rsp,%d\n' % (8*plimbs+16))
      f.write('  mov [rsp+%d],rdi\n' % (8*plimbs+8))
      f.write('  mov rdi,rsi\n')
      f.write('  mov rsi,rdx\n')
      f.write('\n')
      f.write('  /* XXX: put directly into output */\n')
      f.write('  xor rax,rax\n')
      for i in range(plimbs+1):
        f.write('  mov [rsp+%d],rax\n' % (8*i))
      f.write('\n')
      f.write('.macro MULSTEP, k, %s\n' %
              ', '.join('I%d' % i for i in range(plimbs+1)))
      f.write('\n')
      f.write('    mov r11,[rsp+\\I0]\n')
      f.write('    mov rdx, [rsi +  0]\n')
      f.write('    mulx rcx, rdx, [rdi + 8*\\k]\n')
      f.write('    add rdx, r11\n')
      f.write('    mulx rcx, rdx, [rip + .inv_min_p_mod_r]\n')
      f.write('\n')
      f.write('    xor rax, rax /* clear flags */\n')
      f.write('\n')
      f.write('    mulx rbx, rax, [rip + uintbig_p +  0]\n')
      f.write('    adox r11, rax\n')
      f.write('    mov [rsp+\\I0],r11\n')
      f.write('\n')

      for i in range(1, plimbs):
        f.write('    mov r11,[rsp+\\I%d]\n' % i)
        if i & 1:
          f.write('    mulx rcx, rax, [rip + uintbig_p + %d]\n' % (8*i))
          f.write('    adcx r11, rbx\n')
          f.write('    adox r11, rax\n')
        else:
          f.write('    mulx rbx, rax, [rip + uintbig_p + %d]\n' % (8*i))
          f.write('    adcx r11, rcx\n')
          f.write('    adox r11, rax\n')
        f.write('    mov [rsp+\\I%d],r11\n' % i)
        f.write('\n')

      f.write('    mov r11,[rsp+\\I%d]\n' % plimbs)
      f.write('    mov rax, 0\n')
      if plimbs & 1:
        f.write('    adcx r11, rbx\n')
        f.write('    adox r11, rax\n')
      else:
        f.write('    adcx r11, rcx\n')
        f.write('    adox r11, rax\n')
      f.write('    mov [rsp+\\I%d],r11\n' % plimbs)
      f.write('\n')

      f.write('    mov rdx, [rdi + 8*\\k]\n')
      f.write('\n')
      f.write('    xor rax, rax /* clear flags */\n')
      f.write('\n')
      f.write('    mov r11,[rsp+\\I0]\n')
      f.write('    mulx rbx, rax, [rsi +  0]\n')
      f.write('    adox r11, rax\n')
      f.write('    mov [rsp+\\I0],r11\n')
      f.write('\n')

      for i in range(1, plimbs):
        f.write('    mov r11,[rsp+\\I%d]\n' % i)
        if i & 1:
          f.write('    mulx rcx, rax, [rsi + %d]\n' % (8*i))
          f.write('    adcx r11, rbx\n')
          f.write('    adox r11, rax\n')
        else:
          f.write('    mulx rbx, rax, [rsi + %d]\n' % (8*i))
          f.write('    adcx r11, rcx\n')
          f.write('    adox r11, rax\n')
        f.write('    mov [rsp+\\I%d],r11\n' % i)
        f.write('\n')

      f.write('    mov r11,[rsp+\\I%d]\n' % plimbs)
      f.write('    mov rax, 0\n')
      if plimbs & 1:
        f.write('    adcx r11, rbx\n')
        f.write('    adox r11, rax\n')
      else:
        f.write('    adcx r11, rcx\n')
        f.write('    adox r11, rax\n')
      f.write('    mov [rsp+\\I%d],r11\n' % plimbs)
      f.write('\n')

      f.write('.endm\n')
      f.write('\n')

      for i in range(plimbs):
        indices = ['%d' % (8*((j+i+1) % (plimbs+1))) for j in range(plimbs+1)]
        indices = ', '.join(indices)
        f.write('    MULSTEP %d, %s\n' % (i, indices))
      f.write('\n')
      f.write('    mov rdi,[rsp+%d]\n' % (8*plimbs+8))
      f.write('\n')

      for i in range(plimbs):
        f.write('    mov r11,[rsp+%d]\n' % (8*i))
        f.write('    mov [rdi+%d],r11\n' % (8*i))
      f.write('\n')
      f.write('    add rsp,%d\n' % (8*plimbs+16))
      f.write('\n')

    f.write('    pop rbx\n')
    f.write('    pop rbp\n')
    f.write('    jmp .reduce_once\n')
    f.write('\n')

    f.write('.global fp_sq1\n')
    f.write('fp_sq1:\n')
    f.write('    mov rsi, rdi\n')
    f.write('.global fp_sq2\n')
    f.write('fp_sq2:\n')
    f.write('    /* TODO implement optimized Montgomery squaring */\n')
    f.write('    mov rdx, rsi\n')
    f.write('    addq [fp_sq_count+rip],1\n')
    f.write('    jmp fp_mul3\n')
    f.write('\n')

  maybeupdate(fn)


cctest = '\t$(CC) -D\'NAMESPACEGENERIC(x)=highctidh_##x\' \\\n'
ccgeneric = '\t$(CC) -D\'NAMESPACEGENERIC(x)=highctidh_##x\' \\\n'
ccbits = '\t$(CC) -DBITS={0} -D\'NAMESPACEBITS(x)=highctidh_{0}_##x\' -D\'NAMESPACEGENERIC(x)=highctidh_##x\' \\\n'
scc = '\t$(SCC) -DBITS={0} -D\'NAMESPACEBITS(x)=highctidh_{0}_##x\' -D\'NAMESPACEGENERIC(x)=highctidh_##x\' \\\n'


def includes(fn):
  result = [fn]
  with open(fn) as f:
    for line in f:
      m = re.match(r'\s*#\s*include\s*"([^"]*)"', line)
      if m == None:
        continue
      for i in includes(m.group(1)):
        if i not in result:
          result += [i]
  return result


modes = (('ctidh', 511), ('csidh', 511), ('csurf', 512), ('csurf', 513))

fn = 'Makefile'
with open(fn+'.tmp', 'w') as f:
  f.write('# DO NOT EDIT! generated by ./autogen\n\n')
  f.write('SCC=gcc\n')
  # f.write('CC=clang -O3 -Os -march=native -mtune=native -std=gnu99 -pedantic -Wall -Wextra -Wno-language-extension-token -fwrapv -DTIMECOP -DGETRANDOM\n')
  # no -DTIMECOP
  f.write('CC=clang -O3 -Os -march=native -mtune=native -std=gnu99 -pedantic -Wall -Wextra -Wno-language-extension-token -fwrapv -DGETRANDOM\n')
  f.write('\n')
  f.write('default: 512\n')
  f.write('\n')
  f.write('all: default generic timecop\n')
  f.write('\n')
  f.write('generic: testrandom.out\n')
  f.write('\n')

  f.write('512: ctidh_511 csidh_511 csurf_512 csurf_513\n')
  f.write('\n')
  # for bits in databits: # could be an oneliner, but i'm to lazy right now
  #   f.write('{0}: '.format(bits))
  #   for mode in modes:
  #     f.write('{1}_{0} '.format(bits, mode))
  #   f.write('\n\n')

  # we ignore checkct for now
  for mode, bits in modes:
    f.write('{1}_{0}: costpoly_{1}_{0}.out bench_{1}_{0}untuned test_{1}_{0}.out \\\n'.format(
        bits, mode))
    f.write('bench_{1}_{0}mults \\\n'.format(bits, mode))
    f.write('bench_{1}_{0}cycles \\\n'.format(bits, mode))
    f.write('ubench_{1}_{0} umults_{1}_{0}\n'.format(bits, mode))
    f.write('\n')

  # f.write('timecop: \\\n')
  # for bits in databits:
  #   f.write('checkct{0}untuned checkct{0}mults checkct{0}cycles \\\n'.format(bits))
  # f.write('\n')
  # for bits in databits:
  #   f.write('\tvalgrind ./checkct{0}untuned\n'.format(bits))
  #   f.write('\tvalgrind ./checkct{0}mults\n'.format(bits))
  #   f.write('\tvalgrind ./checkct{0}cycles\n'.format(bits))
  # f.write('\n')

  f.write('# ----- benchmarks:\n')
  f.write('\n')

  #for app in ('checkct','bench'):
  for app in ('bench',):
    for mode, bits in modes:
      f.write('{1}_{2}_{0}cycles: {1}.c \\\n'.format(bits, app, mode))
      f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_tunecycles{0}.a libtest.a\n'.format(
          bits, mode))
      f.write(ccbits.format(bits))
      f.write('\t\t-o {1}_{2}_{0}cycles {1}.c \\\n'.format(bits, app, mode))
      f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_tunecycles{0}.a libtest.a\n'.format(
          bits, mode))
      f.write('\n')

      f.write('{1}_{2}_{0}mults: {1}.c \\\n'.format(bits, app, mode))
      f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_tunemults{0}.a libtest.a\n'.format(
          bits, mode))
      f.write(ccbits.format(bits))
      f.write('\t\t-o {1}_{2}_{0}mults {1}.c \\\n'.format(bits, app, mode))
      f.write('\t\libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_tunemults{0}.a libtest.a\n'.format(
          bits, mode))
      f.write('\n')

      f.write('{1}_{2}_{0}untuned: {1}.c \\\n'.format(bits, app, mode))
      f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
          bits, mode))
      f.write(ccbits.format(bits))
      f.write('\t\t-o {1}_{2}_{0}untuned {1}.c \\\n'.format(bits, app, mode))
      f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
          bits, mode))
      f.write('\n')

  f.write('# ----- tests run automatically:\n')
  f.write('\n')

  f.write('testrandom.out: testrandom\n')
  f.write('\t[ -f testrandom.time ] && cat testrandom.time || :\n')
  f.write('\ttime ./testrandom > testrandom.out\n')
  f.write('\tcmp testrandom.out testrandom.exp\n')
  f.write('\n')
  f.write('testrandom: testrandom.o libhighctidh_base.a libtest.a\n')
  f.write('\t$(CC) -o testrandom testrandom.o libhighctidh_base.a libtest.a\n')
  f.write('\n')
  f.write('testrandom.o: testrandom.c random.h Makefile\n')
  f.write(ccgeneric)
  f.write('\t\t-c testrandom.c\n')
  f.write('\n')

  for mode, bits in modes:
    f.write('test_{1}_{0}: test_{1}.c \\\n'.format(bits, mode))
    f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o test_{1}_{0} test_{1}.c \\\n'.format(bits, mode))
    f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write('\n')

    f.write(
        'test_{1}_{0}.out: test_{1}_{0} test_{1}_{0}.exp\n'.format(bits, mode))
    f.write('\t[ -f test{0}.time ] && cat test{0}.time || :\n'.format(bits))
    f.write('\ttime ./test_{1}_{0} > test_{1}_{0}.out\n'.format(bits, mode))
    f.write('\tcmp test_{1}_{0}.out test_{1}_{0}.exp\n'.format(bits, mode))
    f.write('\n')

  f.write('# ----- microbenchmarks (some run automatically):\n')
  f.write('\n')

  for mode, bits in modes:
    f.write('costpoly_{1}_{0}.out: costpoly_{1}_{0}\n'.format(bits, mode))
    f.write('\t./costpoly_{1}_{0} > costpoly_{1}_{0}.out\n'.format(bits, mode))
    f.write('\tcmp costpoly_{1}_{0}.out costpoly.py\n'.format(bits, mode))
    f.write('\n')

    f.write('costpoly_{1}_{0}: costpoly.c \\\n'.format(bits, mode))
    f.write(
        'libhigh{1}_{0}.a libhighctidh_base.a libtest.a\n'.format(bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o costpoly_{1}_{0} costpoly.c \\\n'.format(bits, mode))
    f.write(
        '\t\tlibhigh{1}_{0}.a libhighctidh_base.a libtest.a\n'.format(bits, mode))
    f.write('\n')

    f.write('umults_{1}_{0}: umults.c \\\n'.format(bits, mode))
    f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o umults_{1}_{0} umults.c \\\n'.format(bits, mode))
    f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write('\n')

    f.write('ubench_{1}_{0}: ubench.c \\\n'.format(bits, mode))
    f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o ubench_{1}_{0} ubench.c \\\n'.format(bits, mode))
    f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write('\n')

  f.write('# ----- libhighctidh_tune{mults,cycles}:\n')
  f.write('\n')

  for bits, mode in ((511, 'ctidh'), (512, 'csurf'), (513, 'csurf')):
    f.write(
        'libhighctidh_tunemults{0}.a: steps_tunemults{0}.o Makefile\n'.format(bits))
    f.write(
        '\tar cr libhighctidh_tunemults{0}.a steps_tunemults{0}.o\n'.format(bits))
    f.write('\tranlib libhighctidh_tunemults{0}.a\n'.format(bits))
    f.write('\n')

    f.write(
        'steps_tunemults{0}.o: steps_tunemults{0}.c steps.h Makefile\n'.format(bits))
    f.write(ccbits.format(bits))
    f.write('\t\t-c steps_tunemults{0}.c\n'.format(bits))
    f.write('\n')

    f.write(
        'steps_tunemults{0}.c: tunemults{0}.out tune2c.py Makefile\n'.format(bits))
    f.write(
        '\t./tune2c.py < tunemults{0}.out > steps_tunemults{0}.c\n'.format(bits))
    f.write('\n')

    f.write('tunemults{0}.out: tunemults{0} Makefile\n'.format(bits))
    f.write(
        '\t[ -f tunemults{0}.time ] && cat tunemults{0}.time || :\n'.format(bits))
    f.write('\ttime ./tunemults{0} > tunemults{0}.out\n'.format(bits))
    f.write('\n')

    f.write('tunemults{0}: tunemults.c \\\n'.format(bits))
    f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o tunemults{0} tunemults.c \\\n'.format(bits))
    f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write('\n')

    f.write(
        'libhighctidh_tunecycles{0}.a: steps_tunecycles{0}.o Makefile\n'.format(bits))
    f.write(
        '\tar cr libhighctidh_tunecycles{0}.a steps_tunecycles{0}.o\n'.format(bits))
    f.write('\tranlib libhighctidh_tunecycles{0}.a\n'.format(bits))
    f.write('\n')

    f.write(
        'steps_tunecycles{0}.o: steps_tunecycles{0}.c steps.h Makefile\n'.format(bits))
    f.write(ccgeneric)
    f.write('\t\t-c steps_tunecycles{0}.c\n'.format(bits))
    f.write('\n')

    f.write(
        'steps_tunecycles{0}.c: tunecycles{0}.out tune2c.py Makefile\n'.format(bits))
    f.write(
        '\t./tune2c.py < tunecycles{0}.out > steps_tunecycles{0}.c\n'.format(bits))
    f.write('\n')

    f.write('tunecycles{0}.out: tunecycles{0} Makefile\n'.format(bits))
    f.write(
        '\t[ -f tunecycles{0}.time ] && cat tunecycles{0}.time || :\n'.format(bits))
    f.write('\ttime ./tunecycles{0} > tunecycles{0}.out\n'.format(bits))
    f.write('\n')

    f.write('tunecycles{0}: tunecycles.c \\\n'.format(bits))
    f.write('libhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write(ccbits.format(bits))
    f.write('\t\t-o tunecycles{0} tunecycles.c \\\n'.format(bits))
    f.write('\t\tlibhigh{1}_{0}.a libhighctidh_base.a libhighctidh_untuned.a libtest.a\n'.format(
        bits, mode))
    f.write('\n')

  f.write('# ----- libhigh{0}, size-dependent functions:\n'.format(
      ','.join('{0}_{1}'.format(mode, bits) for mode, bits in modes)))
  f.write('\n')
  bits = 511
  # ctidh
  f.write('libhighctidh_{0}.a: uintbig_csidh_{0}.o fp_csidh_{0}.o  fp_csidh_inv_{0}.o fp_csidh_sqrt_{0}.o \
    primes_csidh_{0}.o poly{0}.o mont{0}.o elligator{0}.o skgen{0}.o validate{0}.o ctidh{0}.o Makefile\n'.format(bits))
  f.write('\tar cr libhighctidh_{0}.a uintbig_csidh_{0}.o fp_csidh_{0}.o fp_csidh_inv_{0}.o fp_csidh_sqrt_{0}.o \
    primes_csidh_{0}.o poly{0}.o mont{0}.o elligator{0}.o skgen{0}.o validate{0}.o ctidh{0}.o\n'.format(bits))
  f.write('\tranlib libhighctidh_{0}.a\n'.format(bits))
  f.write('\n')

  #csidh
  f.write('libhighcsidh_{0}.a: uintbig_csidh_{0}.o fp_csidh_{0}.o fp_csidh_inv_{0}.o fp_csidh_sqrt_{0}.o \
    primes_csidh_{0}.o poly{0}.o mont{0}.o elligator{0}.o validate{0}.o csidh{0}.o Makefile\n'.format(bits))
  f.write('\tar cr libhighcsidh_{0}.a uintbig_csidh_{0}.o fp_csidh_{0}.o fp_csidh_{0}.o fp_csidh_inv_{0}.o \
    fp_csidh_sqrt_{0}.o primes_csidh_{0}.o  poly{0}.o mont{0}.o elligator{0}.o validate{0}.o csidh{0}.o\n'.format(bits))
  f.write('\tranlib libhighcsidh_{0}.a\n'.format(bits))
  f.write('\n')

  for c in ('ctidh', 'csidh', 'validate', 'skgen', 'elligator', 'mont', 'poly'):
    ch = ' '.join(includes(c+'.c'))
    f.write('{1}{0}.o: {2} Makefile\n'.format(bits, c, ch))
    f.write(ccbits.format(bits))
    f.write('\t\t-o {1}{0}.o -c {1}.c\n'.format(bits, c))
    f.write('\n')

  for c in ('fp_csidh_inv', 'fp_csidh_sqrt', 'primes_csidh'):
    ch = ' '.join(includes('%s_%s.c' % (c, bits)))
    f.write('{1}_{0}.o: {2} Makefile\n'.format(bits, c, ch))
    f.write(ccbits.format(bits))
    f.write('\t\t-c {1}_{0}.c\n'.format(bits, c))
    f.write('\n')

  #csurf
  for bits in (512, 513):
    f.write('libhighcsurf_{0}.a: uintbig_csurf_{0}.o fp_csurf_{0}.o fp_csurf_inv_{0}.o fp_csurf_sqrt_{0}.o \
      primes_csurf_{0}.o poly{0}.o mont{0}.o elligator{0}.o validate{0}.o csurf{0}.o Makefile\n'.format(bits))
    f.write('\tar cr libhighcsurf_{0}.a uintbig_csurf_{0}.o fp_csurf_{0}.o fp_csurf_inv_{0}.o fp_csurf_sqrt_{0}.o \
      primes_csurf_{0}.o  poly{0}.o mont{0}.o elligator{0}.o validate{0}.o csurf{0}.o\n'.format(bits))
    f.write('\tranlib libhighcsurf_{0}.a\n'.format(bits))
    f.write('\n')

    for c in ('csurf', 'validate', 'skgen', 'elligator', 'mont', 'poly'):
      ch = ' '.join(includes(c+'.c'))
      f.write('{1}{0}.o: {2} Makefile\n'.format(bits, c, ch))
      f.write(ccbits.format(bits))
      f.write('\t\t-o {1}{0}.o -c {1}.c\n'.format(bits, c))
      f.write('\n')

    for c in ('fp_csurf_inv', 'fp_csurf_sqrt', 'primes_csurf'):
      ch = ' '.join(includes('%s_%s.c' % (c, bits)))
      f.write('{1}_{0}.o: {2} Makefile\n'.format(bits, c, ch))
      f.write(ccbits.format(bits))
      f.write('\t\t-c {1}_{0}.c\n'.format(bits, c))
      f.write('\n')

  for mode, bits in (('csidh', 511), ('csurf', 512), ('csurf', 513)):
    f.write('fp_{1}_{0}.o: fp_{1}_{0}.S fp.h fp_namespace.h uintbig.h uintbig_namespace.h Makefile\n'.format(
        bits, mode))
    f.write(scc.format(bits))
    f.write('\t\t-c fp_{1}_{0}.S\n'.format(bits, mode))
    f.write('\n')

    f.write('uintbig_{1}_{0}.o: uintbig_{1}_{0}.S uintbig.h uintbig_namespace.h Makefile\n'.format(
        bits, mode))
    f.write(scc.format(bits))
    f.write('\t\t-c uintbig_{1}_{0}.S\n'.format(bits, mode))
    f.write('\n')

  f.write('# ----- libhighctidh_untuned, size-independent but normally replaced by tuned functions:\n')
  f.write('\n')
  f.write('libhighctidh_untuned.a: steps_untuned.o Makefile\n')
  f.write('\tar cr libhighctidh_untuned.a steps_untuned.o\n')
  f.write('\tranlib libhighctidh_untuned.a\n')
  f.write('\n')
  f.write('steps_untuned.o: steps_untuned.c steps.h Makefile\n')
  f.write(ccgeneric)
  f.write('\t\t-c steps_untuned.c\n')
  f.write('\n')

  f.write('# ----- libhighctidh_base, size-independent functions:\n')
  f.write('\n')
  f.write('libhighctidh_base.a: steps.o random.o Makefile\n')
  f.write('\tar cr libhighctidh_base.a steps.o random.o\n')
  f.write('\tranlib libhighctidh_base.a\n')
  f.write('\n')
  f.write('steps.o: steps.c steps.h Makefile\n')
  f.write(ccgeneric)
  f.write('\t\t-c steps.c\n')
  f.write('\n')
  f.write('random.o: random.c random.h int32_sort.h randombytes.h Makefile\n')
  f.write(ccgeneric)
  f.write('\t\t-c random.c\n')
  f.write('\n')

  f.write('# ----- functions that libhighctidh wants from a core crypto library:\n')
  f.write('\n')
  f.write('libtest.a: crypto_classify.o crypto_declassify.o randombytes.o int32_sort.o Makefile\n')
  f.write('\tar cr libtest.a crypto_classify.o crypto_declassify.o randombytes.o int32_sort.o\n')
  f.write('\tranlib libtest.a\n')
  f.write('\n')

  f.write('randombytes.o: randombytes.c randombytes.h Makefile\n')
  f.write(cctest)
  f.write('\t\t-c randombytes.c\n')
  f.write('\n')
  f.write('int32_sort.o: int32_sort.c int32_sort.h Makefile\n')
  f.write(cctest)
  f.write('\t\t-c int32_sort.c\n')
  f.write('\n')
  f.write('crypto_declassify.o: crypto_declassify.c crypto_declassify.h Makefile\n')
  f.write(cctest)
  f.write('\t\t-c crypto_declassify.c\n')
  f.write('\n')
  f.write('crypto_classify.o: crypto_classify.c crypto_classify.h Makefile\n')
  f.write(cctest)
  f.write('\t\t-c crypto_classify.c\n')

maybeupdate(fn)
