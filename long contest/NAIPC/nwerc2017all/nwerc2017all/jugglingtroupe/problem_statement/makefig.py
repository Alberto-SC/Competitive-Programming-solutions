#!/usr/bin/env python

"""
run to create the figure on the problem statement.
the input used is the first line of figinput.
"""

def done(c):
  for x in c:
    if len(x) > 1: return False
  return True

def iterate(c):
  cc = [[]] * len(c)
  for i in range(len(c)):
    if len(c[i]) > 1:
      cc[i] = cc[i] + c[i][1:-1]
      if i - 1 >= 0: cc[i-1] = cc[i-1] + [c[i][0]]
      if i + 1 < len(c): cc[i+1] = [c[i][-1]] + cc[i+1]
    else:
      cc[i] = cc[i] + c[i]
  return cc

available_colours = [
  'LimeGreen', 'blue', 'orange', 'Magenta',
  'red', 'Dandelion', 'ProcessBlue', 'olive',
  'violet', 'brown', 'black']
def make_pile(balls):
  global available_colours
  if balls == 0: return []
  available_colours = available_colours[balls:] + available_colours[:balls]
  return available_colours[-balls:]

if __name__ == '__main__':
  f = open('figinput', 'r')
  s = f.readlines()[0].strip()
  c = [make_pile(int(x)) for x in s]
  s = [
    '\\documentclass[class=article,border=0pt]{standalone}\n',
    '\\usepackage[usenames,dvipsnames]{xcolor}\n',
    '\\usepackage{tikz}\n',
    '\\begin{document}\n',
    '\\pagestyle{empty}\n',
    '\\thispagestyle{empty}\n',
    '\\begin{tikzpicture}[scale=0.25]\n']
  y0 = 0
  k = 0
  offsets = [
    [],
    [(0, 0)],
    [(-0.75, 0), (0.75, 0)],
    [(-0.75, -0.4), (0.0, 0.8), (0.75, -0.4)]]
  while True:
    s.append('\\node[anchor=east] at (-6, ' + str(y0) + ') {\small step ' + str(k) + '};\n')
    for i in range(len(c)):
      xy = map(lambda xy: (5*i+xy[0], y0+xy[1]), offsets[len(c[i])])

      # Draw the coloured balls.
      for j in sorted(range(len(c[i])), key=lambda a: (xy[a][1],-xy[a][0])):
        s.append('\draw[fill={2}] ({0}, {1}) ellipse (1 and 1);\n'.format(
          xy[j][0], xy[j][1], c[i][j]))

        # Draw the unnecessarily elaborate stitching pattern.
        '''
        s.append('\draw [fill=white,opacity=0.2,draw=none] ({0},{1}) to[out=110,in=210] ({2},{3}) to[out=-30,in=70] ({4},{5}) to[out=-150,in=0] ({6},{7}) to[out=180,in=-30] ({0},{1});\n'.format(
          xy[j][0] - 0.5, xy[j][1] - 0.866,
          xy[j][0], xy[j][1] + 0.4,
          xy[j][0] + 0.5, xy[j][1] - 0.866,
          xy[j][0], xy[j][1] - 1.0))
        s.append('\draw [fill=black,opacity=0.3,draw=none] ({0},{1}) to[out=60,in=150] ({2},{3}) to[out=30,in=120] ({4},{5}) to[out=120,in=0] ({6},{7}) to [out=180,in=60] ({0},{1});\n'.format(
          xy[j][0] - 0.866, xy[j][1] + 0.5,
          xy[j][0], xy[j][1] + 0.4,
          xy[j][0] + 0.866, xy[j][1] + 0.5,
          xy[j][0], xy[j][1] + 1))
        '''

        # Draw the shine.
        s.append('\draw[fill=white,draw=white,opacity=0.8] ({0}+0.4, {1}+0.4) ellipse (0.15 and 0.15);\n'.format(
          xy[j][0], xy[j][1]))

      # Draw the left and right arrows.
      if len(c[i]) >= 2:
        s.append('\draw [->,>=latex] ({0},{1}) to[out=-125,in=35] ({2},{3});\n'.format(
          xy[+0][0] - 1, xy[+0][1] - 1, xy[+0][0] - 2.0, xy[+0][1] - 2.0))
        s.append('\draw [->,>=latex] ({0},{1}) to[out=-55,in=145] ({2},{3});\n'.format(
          xy[-1][0] + 1, xy[-1][1] - 1, xy[-1][0] + 2.0, xy[-1][1] - 2.0))

    if done(c):
      break
    else:
      c = iterate(c)
      k += 1
      y0 -= 3.5
  s.append('\\end{tikzpicture}\n')
  s.append('\\end{document}\n')
  f = open('fig.tex', 'w')
  for x in s:
    f.write(x)
  f.close()
