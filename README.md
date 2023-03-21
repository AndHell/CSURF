# CSURF
## Absract
*Post Quantum cryptography* is of great interest among the cryptographic research
community. It is motivated by the need to find new schemes to keep cryptographic
applications secure, even after large-scale quantum computers become available. For
this reason, the National Institute of Standards and Technology (NIST) is currently
running the PQC competition to standardize new PQC schemes. Even though not
part of the competition, one promising candidate is the isogeny-based Commutative
Supersingular Isogeny Diffie Hellman (CSIDH) [https://eprint.iacr.org/2018/383] key exchange scheme. CSIDH offers
small keys and can be used as drop-in replacement in Diffie-Hellman-based protocol,
such as Signals end-to-end encryption protocol for mobile messenger. The downside of
CSIDH is its rather expensive performance. To this end Castryck and Decru published
CSIDH on the surface (CSURF) in 2020 [https://eprint.iacr.org/2019/1404], which gives an 5.68% improvement. The
same authors later revisited CSURF with some small tweaks to the arithmetic of the
scheme [https://homes.esat.kuleuven.be/~wcastryc/summer_school_csurf.pdf].
In this work, we present the first implementation of the updated CSURF using
optimized Fp arithmetic. While the results can not confirm the improvements of
5.68% by Castryck and Decru, we propose new parameters for a 511-bit prime that
can tie the performance of a state-of-the-art CSIDH implementation.

## Software
based on [http://ctidh.isogeny.org/software.html]

