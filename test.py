import random
import subprocess
import time
import matplotlib.pyplot as plt
import numpy as np

#simple script designed to test the different algorythms i have written

first = 1000
last = first * 10

lengths = range(first, last + 1, first)

results = {'mrgSort':[], 'selSort':[], 'qkSort':[]}

for len in lengths:
    print("Input length:%d" % len)

    output = ""
    for i in range(len):
        output += str(random.randint(0, len))
        output += " "

    for algo in results.keys():
        t = time.time()
        p = subprocess.Popen('./%s' % algo, stdin=subprocess.PIPE, stdout=subprocess.DEVNULL)
        p.communicate(output.encode("ASCII"))
        te = time.time() - t
        print("Time elapsed for %s:%.2f" % (algo, te))
        results[algo].append(te)
#graph rendering
fig, ax = plt.subplots()

scaleCol = []

for algo in results.keys():
    ax.plot(lengths, results[algo], label=algo)
    scaleCol.append(min(results[algo]))

#sq = np.square(lengths)
#f = np.divide(sq, pow(min(scaleCol), 2)/min(lengths))
#sqLine = ax.plot(lengths, f, label="Scaled cuadratic")

ax.set(xlabel='Input Length', ylabel='Time [s]', title='Sorting algorythm comparison')
ax.grid()
ax.legend(title='Sorting Algorythms')

fig.savefig("algoComparison%d-%d.png" % (lengths.start, lengths.stop - 1))

