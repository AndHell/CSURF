#include "steps.h"

int steps_guess(long long *bs,long long *gs,long long l)
{
  /* l=3: bs=0 gs=0 bench=9340 baseline=8486 */
  /* l=5: bs=0 gs=0 bench=9031 baseline=8696 */
  /* l=7: bs=0 gs=0 bench=12091 baseline=12166 */
  /* l=11: bs=0 gs=0 bench=18463 baseline=18930 */
  /* l=13: bs=0 gs=0 bench=20911 baseline=20829 */
  /* l=17: bs=0 gs=0 bench=27302 baseline=27432 */
  /* l=19: bs=0 gs=0 bench=29832 baseline=30253 */
  /* l=23: bs=0 gs=0 bench=36377 baseline=36546 */
  /* l=29: bs=0 gs=0 bench=42308 baseline=45242 */
  /* l=31: bs=0 gs=0 bench=45061 baseline=48586 */
  /* l=37: bs=0 gs=0 bench=53708 baseline=53941 */
  /* l=41: bs=0 gs=0 bench=60918 baseline=61200 */
  /* l=43: bs=0 gs=0 bench=61942 baseline=65317 */
  /* l=47: bs=0 gs=0 bench=65321 baseline=66410 */
  /* l=53: bs=0 gs=0 bench=76409 baseline=76362 */
  /* l=59: bs=0 gs=0 bench=80231 baseline=85484 */
  /* l=61: bs=0 gs=0 bench=84381 baseline=83718 */
  /* l=67: bs=0 gs=0 bench=93859 baseline=92666 */
  /* l=71: bs=0 gs=0 bench=102079 baseline=98362 */
  if (l <= 71) { *bs = 0; *gs = 0; return 1; }
  /* l=73: bs=6 gs=3 bench=95593 baseline=100291 */
  if (l <= 73) { *bs = 6; *gs = 3; return 1; }
  /* l=79: bs=0 gs=0 bench=82508 baseline=82092 */
  /* l=83: bs=0 gs=0 bench=86601 baseline=85762 */
  /* l=89: bs=0 gs=0 bench=91245 baseline=91356 */
  /* l=97: bs=0 gs=0 bench=100939 baseline=97765 */
  /* l=101: bs=0 gs=0 bench=105051 baseline=103668 */
  /* l=103: bs=0 gs=0 bench=106581 baseline=104201 */
  /* l=107: bs=0 gs=0 bench=110982 baseline=113057 */
  /* l=109: bs=0 gs=0 bench=113013 baseline=113838 */
  /* l=113: bs=0 gs=0 bench=115305 baseline=117977 */
  /* l=127: bs=0 gs=0 bench=129186 baseline=128279 */
  /* l=131: bs=0 gs=0 bench=137074 baseline=133601 */
  if (l <= 131) { *bs = 0; *gs = 0; return 1; }
  /* l=137: bs=8 gs=4 bench=139749 baseline=141545 */
  if (l <= 137) { *bs = 8; *gs = 4; return 1; }
  /* l=139: bs=0 gs=0 bench=141160 baseline=143246 */
  /* l=149: bs=0 gs=0 bench=153833 baseline=151968 */
  /* l=151: bs=0 gs=0 bench=155809 baseline=154253 */
  /* l=157: bs=0 gs=0 bench=158961 baseline=157830 */
  if (l <= 157) { *bs = 0; *gs = 0; return 1; }
  /* l=163: bs=8 gs=5 bench=166835 baseline=163026 */
  /* l=167: bs=8 gs=5 bench=171142 baseline=170258 */
  /* l=173: bs=8 gs=5 bench=176856 baseline=179054 */
  if (l <= 173) { *bs = 8; *gs = 5; return 1; }
  /* l=179: bs=0 gs=0 bench=186936 baseline=182092 */
  if (l <= 179) { *bs = 0; *gs = 0; return 1; }
  /* l=181: bs=8 gs=5 bench=184374 baseline=184094 */
  /* l=191: bs=8 gs=5 bench=194972 baseline=194615 */
  if (l <= 191) { *bs = 8; *gs = 5; return 1; }
  /* l=193: bs=8 gs=6 bench=188738 baseline=195535 */
  /* l=197: bs=8 gs=6 bench=197931 baseline=199739 */
  /* l=199: bs=8 gs=6 bench=196037 baseline=201955 */
  /* l=211: bs=8 gs=6 bench=204756 baseline=214042 */
  /* l=223: bs=8 gs=6 bench=216956 baseline=226563 */
  if (l <= 223) { *bs = 8; *gs = 6; return 1; }
  /* l=227: bs=8 gs=7 bench=222397 baseline=226080 */
  /* l=229: bs=8 gs=7 bench=215669 baseline=232133 */
  if (l <= 229) { *bs = 8; *gs = 7; return 1; }
  /* l=233: bs=8 gs=6 bench=226137 baseline=239497 */
  if (l <= 233) { *bs = 8; *gs = 6; return 1; }
  /* l=241: bs=10 gs=6 bench=225949 baseline=239785 */
  /* l=251: bs=10 gs=6 bench=227426 baseline=255701 */
  /* l=257: bs=10 gs=6 bench=240790 baseline=265267 */
  /* l=263: bs=10 gs=6 bench=244521 baseline=261379 */
  /* l=269: bs=10 gs=6 bench=254031 baseline=276424 */
  /* l=271: bs=10 gs=6 bench=256553 baseline=274237 */
  if (l <= 271) { *bs = 10; *gs = 6; return 1; }
  /* l=283: bs=10 gs=7 bench=254098 baseline=283001 */
  /* l=293: bs=10 gs=7 bench=268729 baseline=290816 */
  /* l=307: bs=10 gs=7 bench=281933 baseline=310008 */
  /* l=311: bs=10 gs=7 bench=282685 baseline=314248 */
  /* l=313: bs=10 gs=7 bench=284325 baseline=314600 */
  /* l=317: bs=10 gs=7 bench=293335 baseline=320970 */
  if (l <= 317) { *bs = 10; *gs = 7; return 1; }
  /* l=331: bs=10 gs=8 bench=293791 baseline=343671 */
  if (l <= 331) { *bs = 10; *gs = 8; return 1; }
  /* l=337: bs=12 gs=7 bench=297089 baseline=346321 */
  /* l=347: bs=12 gs=7 bench=302394 baseline=346316 */
  /* l=349: bs=12 gs=7 bench=309985 baseline=353139 */
  /* l=353: bs=12 gs=7 bench=312762 baseline=350333 */
  if (l <= 353) { *bs = 12; *gs = 7; return 1; }
  /* l=359: bs=14 gs=6 bench=315617 baseline=356548 */
  if (l <= 359) { *bs = 14; *gs = 6; return 1; }
  /* l=379: bs=10 gs=9 bench=336837 baseline=371052 */
  /* l=383: bs=10 gs=9 bench=339732 baseline=386739 */
  if (l <= 383) { *bs = 10; *gs = 9; return 1; }
  /* l=389: bs=12 gs=8 bench=327132 baseline=391620 */
  if (l <= 389) { *bs = 12; *gs = 8; return 1; }
  /* l=397: bs=14 gs=7 bench=327265 baseline=406575 */
  if (l <= 397) { *bs = 14; *gs = 7; return 1; }
  /* l=401: bs=12 gs=8 bench=335195 baseline=398650 */
  if (l <= 401) { *bs = 12; *gs = 8; return 1; }
  return 0;
}
