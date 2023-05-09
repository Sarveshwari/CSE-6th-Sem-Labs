import sys

mostfreq=[]
currentmax=-1

for line in sys.stdin:
    count, word = line.strip().split('\t', 1)
    count=int(count)
    if(count>currentmax):
        currentmax=count
        mostfreq=[word]
    elif(currentmax==count):
        mostfreq.append(word)
for word in mostfreq:
    print('%s\t%s' % (word,currentmax))
