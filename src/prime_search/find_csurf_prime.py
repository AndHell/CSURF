#!/usr/bin/env python3

import random


def FermatPrimalityTest(n, tests=10):
    for _ in range(tests):
        rand = random.randint(2, n-1)
        if (pow(rand, n-1, n) != 1):
            return False
    return True


def get_prime(cofactor, factors):
    p = cofactor
    for l in factors:
        p *= l
    return p-1


def count_bits(p):
    pbits = 0
    while (1 << pbits) <= p:
        pbits += 1
    return pbits


csidh_factors = [  3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,
                  59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
                 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
                 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
                 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 587]

csurf_factors_513 = [  3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,
                   59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
                 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
                 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
                 293, 307, 311, 313, 317, 331, 337, 349, 353, 367, 373, 379, 383, 389]

new_csurf_512_factors = [
            3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,
           71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
          163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 241, 251, 257, 263,
          269, 271, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 379, 383, 389, 397,
          401]

# print("CSURF 513:")
# csurf_prime = get_prime(4*2*3, csurf_factors)
# print("bits:", count_bits(csurf_prime))
# print("p mod 8  == ", csurf_prime % 8)
# print("p:", csurf_prime)
# print("(p+1)/4:", (csurf_prime+1)//4)

print("CSURF 512:")
csurf_prime = get_prime(4*2*53, new_csurf_512_factors)
print("bits:", count_bits(csurf_prime))
print("p mod 8  == ", csurf_prime % 8)
print("p:", csurf_prime)
print("p: 0x%x" % csurf_prime)

# print("CSIDH:")
# csidh_prime = get_prime(4, csidh_factors)
# print("bits:", count_bits(csidh_prime))
# print("p mod 8  == ", csidh_prime % 8)
# print("p:", csidh_prime)


# first 100 primes
primes_100 = [   2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
               71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
              151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
              233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
              317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
              503, 509, 521, 523, 541]



base_facs = [  3,  5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53, 
              59,  61,  67,  71,  73,  79,  83,  89 , 97, 101, 103, 107, 109, 113, 127, 
             131, 137, 139, 149, 151,  157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 
             211, 223, 227, 229
              ]

test_facs = [
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
              317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401]#, 409]
              #419, 421, 431, 433, 439,]
              # 443, 449, 457, 461, 463, 467, 479, 487, 491, 499]
             # 503, 509, 521, 523, 541]
             # ,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659]




def find_new_primes(cofactor, min_bits, max_bits, num_cofactors):
    assert(min_bits <= max_bits)
    primes = {}
    tries = 0
    while tries < 10000:
        tries += 1
        tester = random.sample(test_facs, num_cofactors-len(base_facs))
        assert(len(tester)+len(base_facs) == num_cofactors)

        tester.sort()
        prime = get_prime(cofactor, base_facs + tester)
        if prime % 8 != 7:
            continue
       
        pbits = count_bits(prime)
        if pbits > max_bits or pbits < min_bits:
            continue
        
        if not FermatPrimalityTest(prime):
            continue


        result = base_facs + tester
        primes[prime] = result
    return primes


primes = {}
cofac = 1
i = 15
while len(primes) == 0 and i < 100:
    cofac = primes_100[i]
    primes = find_new_primes(4*2*cofac, 511, 511, 73) 
    i += 1



print(cofac)
for prime, factors in primes.items():
    pbits = count_bits(prime)
    print("p: 0x%x" % prime)
    # print("p: %d" % prime)
    print("bits:", pbits, "|| p mod 8:", prime % 8)
    print("factor sum: ", sum(factors))
    print(factors)