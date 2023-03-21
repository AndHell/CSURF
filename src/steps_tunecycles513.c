#include "steps.h"

int steps_guess(long long *bs,long long *gs,long long l)
{
  /* l=3: bs=0 gs=0 bench=11651 baseline=10743 */
  /* l=5: bs=0 gs=0 bench=12661 baseline=13119 */
  /* l=7: bs=0 gs=0 bench=17005 baseline=18112 */
  /* l=11: bs=0 gs=0 bench=27636 baseline=27498 */
  /* l=13: bs=0 gs=0 bench=29799 baseline=31808 */
  /* l=17: bs=0 gs=0 bench=38005 baseline=38550 */
  /* l=19: bs=0 gs=0 bench=43295 baseline=43234 */
  /* l=23: bs=0 gs=0 bench=53000 baseline=55145 */
  /* l=29: bs=0 gs=0 bench=63022 baseline=64327 */
  /* l=31: bs=0 gs=0 bench=66991 baseline=69148 */
  /* l=37: bs=0 gs=0 bench=64092 baseline=58592 */
  /* l=41: bs=0 gs=0 bench=66736 baseline=66930 */
  /* l=43: bs=0 gs=0 bench=69075 baseline=68542 */
  /* l=47: bs=0 gs=0 bench=77316 baseline=74260 */
  /* l=53: bs=0 gs=0 bench=84804 baseline=85843 */
  /* l=59: bs=0 gs=0 bench=91147 baseline=95380 */
  /* l=61: bs=0 gs=0 bench=93971 baseline=98495 */
  /* l=67: bs=0 gs=0 bench=123671 baseline=107110 */
  /* l=71: bs=0 gs=0 bench=110613 baseline=126414 */
  /* l=73: bs=0 gs=0 bench=118048 baseline=129773 */
  /* l=79: bs=0 gs=0 bench=126977 baseline=128888 */
  /* l=83: bs=0 gs=0 bench=132819 baseline=134157 */
  /* l=89: bs=0 gs=0 bench=142209 baseline=141551 */
  /* l=97: bs=0 gs=0 bench=155368 baseline=165762 */
  /* l=101: bs=0 gs=0 bench=162479 baseline=165949 */
  /* l=103: bs=0 gs=0 bench=170141 baseline=163433 */
  /* l=107: bs=0 gs=0 bench=170640 baseline=174793 */
  /* l=109: bs=0 gs=0 bench=173775 baseline=176365 */
  /* l=113: bs=0 gs=0 bench=180022 baseline=173873 */
  /* l=127: bs=0 gs=0 bench=194996 baseline=243164 */
  if (l <= 127) { *bs = 0; *gs = 0; return 1; }
  /* l=131: bs=8 gs=4 bench=200591 baseline=206055 */
  if (l <= 131) { *bs = 8; *gs = 4; return 1; }
  /* l=137: bs=6 gs=4 bench=213860 baseline=211176 */
  if (l <= 137) { *bs = 6; *gs = 4; return 1; }
  /* l=139: bs=0 gs=0 bench=213181 baseline=220082 */
  if (l <= 139) { *bs = 0; *gs = 0; return 1; }
  /* l=149: bs=6 gs=5 bench=231985 baseline=226060 */
  if (l <= 149) { *bs = 6; *gs = 5; return 1; }
  /* l=151: bs=8 gs=4 bench=231138 baseline=229540 */
  if (l <= 151) { *bs = 8; *gs = 4; return 1; }
  /* l=157: bs=0 gs=0 bench=242532 baseline=240702 */
  if (l <= 157) { *bs = 0; *gs = 0; return 1; }
  /* l=163: bs=8 gs=5 bench=239785 baseline=265829 */
  /* l=167: bs=8 gs=5 bench=244468 baseline=262486 */
  if (l <= 167) { *bs = 8; *gs = 5; return 1; }
  /* l=173: bs=8 gs=4 bench=263964 baseline=262109 */
  if (l <= 173) { *bs = 8; *gs = 4; return 1; }
  /* l=179: bs=8 gs=5 bench=269185 baseline=271206 */
  /* l=181: bs=8 gs=5 bench=263181 baseline=273920 */
  if (l <= 181) { *bs = 8; *gs = 5; return 1; }
  /* l=191: bs=8 gs=4 bench=287603 baseline=289962 */
  if (l <= 191) { *bs = 8; *gs = 4; return 1; }
  /* l=193: bs=8 gs=6 bench=279411 baseline=306146 */
  /* l=197: bs=8 gs=6 bench=274865 baseline=297752 */
  /* l=199: bs=8 gs=6 bench=288531 baseline=311728 */
  /* l=211: bs=8 gs=6 bench=297012 baseline=347850 */
  /* l=223: bs=8 gs=6 bench=325845 baseline=355293 */
  if (l <= 223) { *bs = 8; *gs = 6; return 1; }
  /* l=227: bs=10 gs=5 bench=325848 baseline=345616 */
  if (l <= 227) { *bs = 10; *gs = 5; return 1; }
  /* l=229: bs=8 gs=7 bench=329017 baseline=357612 */
  /* l=233: bs=8 gs=7 bench=338706 baseline=363829 */
  /* l=239: bs=8 gs=7 bench=344274 baseline=373074 */
  if (l <= 239) { *bs = 8; *gs = 7; return 1; }
  /* l=241: bs=10 gs=6 bench=333547 baseline=411000 */
  if (l <= 241) { *bs = 10; *gs = 6; return 1; }
  /* l=251: bs=8 gs=7 bench=350124 baseline=397402 */
  if (l <= 251) { *bs = 8; *gs = 7; return 1; }
  /* l=257: bs=10 gs=6 bench=356674 baseline=399689 */
  /* l=263: bs=10 gs=6 bench=366472 baseline=409670 */
  /* l=269: bs=10 gs=6 bench=378424 baseline=419406 */
  /* l=271: bs=10 gs=6 bench=378947 baseline=426527 */
  /* l=277: bs=10 gs=6 bench=391944 baseline=436202 */
  if (l <= 277) { *bs = 10; *gs = 6; return 1; }
  /* l=281: bs=0 gs=0 bench=442668 baseline=439371 */
  if (l <= 281) { *bs = 0; *gs = 0; return 1; }
  /* l=283: bs=10 gs=7 bench=379628 baseline=649741 */
  /* l=293: bs=10 gs=7 bench=410047 baseline=455955 */
  if (l <= 293) { *bs = 10; *gs = 7; return 1; }
  /* l=307: bs=0 gs=0 bench=501263 baseline=504919 */
  if (l <= 307) { *bs = 0; *gs = 0; return 1; }
  /* l=311: bs=10 gs=7 bench=653342 baseline=715658 */
  /* l=313: bs=10 gs=7 bench=429450 baseline=795050 */
  if (l <= 313) { *bs = 10; *gs = 7; return 1; }
  /* l=317: bs=8 gs=6 bench=488009 baseline=512088 */
  if (l <= 317) { *bs = 8; *gs = 6; return 1; }
  /* l=331: bs=10 gs=8 bench=646492 baseline=758823 */
  if (l <= 331) { *bs = 10; *gs = 8; return 1; }
  /* l=337: bs=8 gs=9 bench=469632 baseline=792754 */
  if (l <= 337) { *bs = 8; *gs = 9; return 1; }
  /* l=349: bs=4 gs=4 bench=573330 baseline=633191 */
  if (l <= 349) { *bs = 4; *gs = 4; return 1; }
  /* l=353: bs=12 gs=7 bench=681819 baseline=882796 */
  if (l <= 353) { *bs = 12; *gs = 7; return 1; }
  /* l=367: bs=14 gs=6 bench=683135 baseline=859224 */
  if (l <= 367) { *bs = 14; *gs = 6; return 1; }
  /* l=373: bs=12 gs=7 bench=739715 baseline=811871 */
  if (l <= 373) { *bs = 12; *gs = 7; return 1; }
  /* l=379: bs=14 gs=6 bench=758193 baseline=873031 */
  if (l <= 379) { *bs = 14; *gs = 6; return 1; }
  /* l=383: bs=6 gs=6 bench=602557 baseline=913072 */
  if (l <= 383) { *bs = 6; *gs = 6; return 1; }
  /* l=389: bs=12 gs=8 bench=774738 baseline=931544 */
  if (l <= 389) { *bs = 12; *gs = 8; return 1; }
  return 0;
}
