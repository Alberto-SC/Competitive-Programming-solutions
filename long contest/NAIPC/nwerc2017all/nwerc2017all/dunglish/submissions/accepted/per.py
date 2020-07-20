n = int(raw_input())
S = raw_input().split()
m = int(raw_input())

trans = {}
for (d, e, c) in [raw_input().split() for _ in range(m)]:
    if d not in trans:
        trans[d] = ([], [])
    trans[d][c=='correct'].append(e)

total = reduce(lambda x, y: x*y, (len(trans[w][0])+len(trans[w][1]) for w in S), 1)
correct = reduce(lambda x, y: x*y, (len(trans[w][1]) for w in S), 1)

if total == 1:
    print ' '.join((trans[w][0]+trans[w][1])[0] for w in S)
    print 'correct' if correct else 'incorrect'
else:
    print '%d correct' % correct
    print '%d incorrect' % (total-correct)
    

