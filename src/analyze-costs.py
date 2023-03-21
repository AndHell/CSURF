#!/usr/bin/env python3

import sys
import math
import numpy as np



def median(d):
  return np.median(d)

def mean(d):
  return sum(d)*1.0/len(d)

def deviation(d, m):
  return math.sqrt(sum((x-m)**2 for x in d)*1.0/len(d))

def cost(d):
  m = mean(d)
  e = deviation(d, m)
  return (m,e)

keys = set()
validate = {}
action = {}
num = 0

for line in sys.stdin:
  line = line.split()
  if len(line) < 11: continue
  if line[3] != 'mulsq': continue
  if line[5] != 'sq': continue
  if line[7] != 'addsub': continue
  if line[9] != 'cycles': continue

  if line[2] == 'validate':
    target = validate
  elif line[2] == 'action':
    target = action
  else:
    continue

  mulsq = int(line[4])
  sq = int(line[6])
  addsub = int(line[8])
  Mcyc = 0.000001*int(line[10])
  mul = mulsq-sq
  #combo185 = mul+s0.8*q+0.05*addsub
  combo = mul+1.05*sq+0.15*addsub

  keys.add(int(line[1]))
  for k in int(line[1]),'total':
    for name,value in (
      ('Mcyc',Mcyc),
      ('mulsq',mulsq),
      ('sq',sq),
      ('addsub',addsub),
      ('mul',mul),
      ('combo',combo),
    ):
      if (k,name) not in target:
        target[k,name] = []
      target[k,name] += [value]

  num += 1

for k in sorted(keys)+['total']:
  for targetname,target in (
    ('validate',validate),
    ('action',action),
  ):
    output = '%s %s' % (k,targetname)
    output += ' experiments %d' % len(target[k,'Mcyc'])
    for name in ('Mcyc','mulsq','sq','addsub','mul','combo','median'):
      if name == 'median':
        x = target[k, 'combo']
      else:
        x = target[k,name]
      format = ' %s %.0f+-%.0f'
      if name == 'Mcyc':
        format = ' %s %.2f+-%.2f'
      (m,d) = cost(x)
      if name == 'median':
        m = median(x)
        d = deviation(x,m)
      output += format%(name,m,d)
    print(output)
