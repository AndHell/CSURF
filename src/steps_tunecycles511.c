#include "steps.h"

int steps_guess(long long *bs,long long *gs,long long l)
{
  /* l=3: bs=0 gs=0 bench=10257 baseline=9225 */
  /* l=5: bs=0 gs=0 bench=8866 baseline=8698 */
  /* l=7: bs=0 gs=0 bench=12102 baseline=11591 */
  /* l=11: bs=0 gs=0 bench=18378 baseline=18779 */
  /* l=13: bs=0 gs=0 bench=21285 baseline=21476 */
  /* l=17: bs=0 gs=0 bench=27259 baseline=27395 */
  /* l=19: bs=0 gs=0 bench=28744 baseline=30790 */
  /* l=23: bs=0 gs=0 bench=34646 baseline=35256 */
  /* l=29: bs=0 gs=0 bench=42983 baseline=43654 */
  /* l=31: bs=0 gs=0 bench=45821 baseline=49463 */
  /* l=37: bs=0 gs=0 bench=54894 baseline=54775 */
  /* l=41: bs=0 gs=0 bench=60219 baseline=60499 */
  /* l=43: bs=0 gs=0 bench=63061 baseline=64648 */
  /* l=47: bs=0 gs=0 bench=68607 baseline=69696 */
  /* l=53: bs=0 gs=0 bench=77675 baseline=77708 */
  /* l=59: bs=0 gs=0 bench=85666 baseline=82711 */
  /* l=61: bs=0 gs=0 bench=84531 baseline=85208 */
  /* l=67: bs=0 gs=0 bench=93758 baseline=92605 */
  /* l=71: bs=0 gs=0 bench=100719 baseline=98282 */
  /* l=73: bs=0 gs=0 bench=102709 baseline=100758 */
  if (l <= 73) { *bs = 0; *gs = 0; return 1; }
  /* l=79: bs=6 gs=3 bench=93853 baseline=109348 */
  if (l <= 79) { *bs = 6; *gs = 3; return 1; }
  /* l=83: bs=0 gs=0 bench=86590 baseline=85823 */
  /* l=89: bs=0 gs=0 bench=92641 baseline=92759 */
  /* l=97: bs=0 gs=0 bench=100781 baseline=99421 */
  /* l=101: bs=0 gs=0 bench=106750 baseline=103693 */
  /* l=103: bs=0 gs=0 bench=107129 baseline=105994 */
  /* l=107: bs=0 gs=0 bench=111010 baseline=111620 */
  /* l=109: bs=0 gs=0 bench=112992 baseline=112350 */
  /* l=113: bs=0 gs=0 bench=117168 baseline=115749 */
  /* l=127: bs=0 gs=0 bench=131394 baseline=130551 */
  if (l <= 127) { *bs = 0; *gs = 0; return 1; }
  /* l=131: bs=8 gs=4 bench=135735 baseline=133601 */
  if (l <= 131) { *bs = 8; *gs = 4; return 1; }
  /* l=137: bs=0 gs=0 bench=136480 baseline=135087 */
  /* l=139: bs=0 gs=0 bench=138491 baseline=139127 */
  /* l=149: bs=0 gs=0 bench=153764 baseline=151826 */
  /* l=151: bs=0 gs=0 bench=155629 baseline=154145 */
  if (l <= 151) { *bs = 0; *gs = 0; return 1; }
  /* l=157: bs=8 gs=4 bench=160654 baseline=160483 */
  if (l <= 157) { *bs = 8; *gs = 4; return 1; }
  /* l=163: bs=8 gs=5 bench=167315 baseline=160123 */
  /* l=167: bs=8 gs=5 bench=164990 baseline=170096 */
  if (l <= 167) { *bs = 8; *gs = 5; return 1; }
  /* l=173: bs=0 gs=0 bench=171877 baseline=170597 */
  if (l <= 173) { *bs = 0; *gs = 0; return 1; }
  /* l=179: bs=8 gs=5 bench=176048 baseline=182102 */
  if (l <= 179) { *bs = 8; *gs = 5; return 1; }
  /* l=181: bs=0 gs=0 bench=179773 baseline=177667 */
  if (l <= 181) { *bs = 0; *gs = 0; return 1; }
  /* l=191: bs=8 gs=5 bench=188086 baseline=194662 */
  if (l <= 191) { *bs = 8; *gs = 5; return 1; }
  /* l=193: bs=8 gs=6 bench=191222 baseline=195379 */
  /* l=197: bs=8 gs=6 bench=187258 baseline=199775 */
  /* l=199: bs=8 gs=6 bench=196366 baseline=202040 */
  /* l=211: bs=8 gs=6 bench=200225 baseline=214012 */
  /* l=223: bs=8 gs=6 bench=220032 baseline=218645 */
  if (l <= 223) { *bs = 8; *gs = 6; return 1; }
  /* l=227: bs=8 gs=7 bench=220972 baseline=229904 */
  /* l=229: bs=8 gs=7 bench=215712 baseline=231896 */
  /* l=233: bs=8 gs=7 bench=228043 baseline=228246 */
  /* l=239: bs=8 gs=7 bench=225770 baseline=242487 */
  if (l <= 239) { *bs = 8; *gs = 7; return 1; }
  /* l=241: bs=10 gs=6 bench=218471 baseline=235535 */
  /* l=251: bs=10 gs=6 bench=227406 baseline=246912 */
  /* l=257: bs=10 gs=6 bench=235630 baseline=259348 */
  if (l <= 257) { *bs = 10; *gs = 6; return 1; }
  /* l=263: bs=8 gs=8 bench=243876 baseline=256717 */
  if (l <= 263) { *bs = 8; *gs = 8; return 1; }
  /* l=269: bs=10 gs=6 bench=245323 baseline=272773 */
  /* l=271: bs=10 gs=6 bench=247409 baseline=274125 */
  /* l=277: bs=10 gs=6 bench=254530 baseline=270225 */
  if (l <= 277) { *bs = 10; *gs = 6; return 1; }
  /* l=281: bs=10 gs=7 bench=247905 baseline=287394 */
  /* l=283: bs=10 gs=7 bench=248865 baseline=287542 */
  /* l=293: bs=10 gs=7 bench=259072 baseline=285681 */
  /* l=307: bs=10 gs=7 bench=272674 baseline=310052 */
  /* l=311: bs=10 gs=7 bench=276865 baseline=303464 */
  /* l=313: bs=10 gs=7 bench=278517 baseline=308952 */
  /* l=317: bs=10 gs=7 bench=293068 baseline=345801 */
  if (l <= 317) { *bs = 10; *gs = 7; return 1; }
  /* l=331: bs=10 gs=8 bench=293583 baseline=339172 */
  if (l <= 331) { *bs = 10; *gs = 8; return 1; }
  /* l=337: bs=12 gs=7 bench=296854 baseline=339699 */
  /* l=347: bs=12 gs=7 bench=295940 baseline=351916 */
  /* l=349: bs=12 gs=7 bench=308714 baseline=352847 */
  if (l <= 349) { *bs = 12; *gs = 7; return 1; }
  /* l=353: bs=10 gs=8 bench=315450 baseline=355656 */
  if (l <= 353) { *bs = 10; *gs = 8; return 1; }
  /* l=359: bs=12 gs=7 bench=308108 baseline=349735 */
  if (l <= 359) { *bs = 12; *gs = 7; return 1; }
  /* l=367: bs=10 gs=9 bench=312022 baseline=370508 */
  /* l=373: bs=10 gs=9 bench=321689 baseline=376175 */
  if (l <= 373) { *bs = 10; *gs = 9; return 1; }
  /* l=587: bs=14 gs=10 bench=439822 baseline=599396 */
  if (l <= 587) { *bs = 14; *gs = 10; return 1; }
  return 0;
}
