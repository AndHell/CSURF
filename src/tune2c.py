#!/usr/bin/env python3

import sys

data = []

for line in sys.stdin:
  data += [tuple(int(x) for x in line.strip().split())]

data.sort()

print('#include "steps.h"')
print('')

print('int steps_guess(long long *bs,long long *gs,long long l)')
print('{')

while len(data) > 0:
  l0,bs0,gs0,bench0,baseline0 = data[0]
  samebsgs = 1
  while samebsgs < len(data):
    l,bs,gs,bench,baseline = data[samebsgs]
    if (bs,gs) != (bs0,gs0): break
    samebsgs += 1

  for l,bs,gs,bench,baseline in data[:samebsgs]:
    print('  /* l=%d: bs=%d gs=%d bench=%d baseline=%d */' % (l,bs,gs,bench,baseline))

  print('  if (l <= %d) { *bs = %d; *gs = %d; return 1; }' % (data[samebsgs-1][0],bs0,gs0))

  data = data[samebsgs:]

print('  return 0;')
print('}')
