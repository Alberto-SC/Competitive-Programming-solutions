#!/usr/bin/env python

"""
run to create the figure on the problem statement.
the input used is the first line of figinput.
"""

def done(c):
  for x in c:
    if x > 1: return False
  return True

def iterate(c):
  cc = [ 0 ] * len(c)
  for i in range(len(c)):
    if c[i] > 1:
      cc[i] += c[i] - 2
      if i - 1 >= 0: cc[i - 1] += 1
      if i + 1 < len(c): cc[i + 1] += 1
    else:
      cc[i] += c[i]
  return cc

if __name__ == '__main__':
  f = open('figinput', 'r')
  s = f.readlines()[0].strip()
  c = [int(x) for x in s]
  s = [ ]
  s.append('\\begin{center}\n')
  s.append('\\begin{tikzpicture}[scale=0.15]\n')
  y0 = 0
  k = 0
  while not done(c):
    s.append('\\node[anchor=east] at (-6, ' + str(y0) + ') {\small step ' + str(k) + '};\n')
    for i in range(len(c)):
      x = 5 * i
      y = y0
      for j in range(c[i]):
        s.append('\draw[fill=orange!50!white] ({0}, {1}) ellipse (2 and 1);\n'.format(x, y))
        s.append('\\fill[orange!50!white] ({0}-2, {1}) rectangle ({0}+2, {1}+0.5);\n'.format(x, y))
        s.append('\draw[fill=orange!50!white] ({0}, {1}+0.5) ellipse (2 and 1);\n'.format(x, y))
        s.append('\draw ({0}-2, {1}) -- ({0}-2, {1}+0.5);\n'.format(x, y))
        s.append('\draw ({0}+2, {1}) -- ({0}+2, {1}+0.5);\n'.format(x, y))
        y += 0.5
    y0 -= 4
    c = iterate(c)
    k += 1
  s.append('\\node[anchor=east] at (-6, ' + str(y0) + ') {\small step ' + str(k) + '};\n')
  for i in range(len(c)):
    x = 5 * i
    y = y0
    for j in range(c[i]):
      s.append('\draw[fill=orange!50!white] ({0}, {1}) ellipse (2 and 1);\n'.format(x, y))
      s .append('\\fill[orange!50!white] ({0}-2, {1}) rectangle ({0}+2, {1}+0.5);\n'.format(x, y))
      s.append('\draw[fill=orange!50!white] ({0}, {1}+0.5) ellipse (2 and 1);\n'.format(x, y))
      s.append('\draw ({0}-2, {1}) -- ({0}-2, {1}+0.5);\n'.format(x, y))
      s.append('\draw ({0}+2, {1}) -- ({0}+2, {1}+0.5);\n'.format(x, y))
      y += 0.5
  s.append('\end{tikzpicture}\n')
  s.append('\end{center}\n')
  f = open('fig.tex', 'w')
  for x in s:
    f.write(x)
  f.close()
