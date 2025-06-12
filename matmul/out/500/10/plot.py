# bar for each dataset in seconds

import matplotlib.pyplot as plt
import numpy

# read in CSVs
ijk = numpy.genfromtxt('ijk.csv', delimiter=',')
kij = numpy.genfromtxt('kij.csv', delimiter=',')
jik = numpy.genfromtxt('jik.csv', delimiter=',')
ikj = numpy.genfromtxt('ikj.csv', delimiter=',')
jki = numpy.genfromtxt('jki.csv', delimiter=',')
kji = numpy.genfromtxt('kji.csv', delimiter=',')
transposed_a = numpy.genfromtxt('transposed_a.csv', delimiter=',')
transposed_b = numpy.genfromtxt('transposed_b.csv', delimiter=',')

# exclude first 3 values
ijk = ijk[3:]
kij = kij[3:]
jik = jik[3:]
ikj = ikj[3:]
jki = jki[3:]
kji = kji[3:]
transposed_a = transposed_a[3:]
transposed_b = transposed_b[3:]

# get the mean 
ijk_mean = numpy.mean(ijk)
kij_mean = numpy.mean(kij)
jik_mean = numpy.mean(jik)
ikj_mean = numpy.mean(ikj)
jki_mean = numpy.mean(jki)
kji_mean = numpy.mean(kji)
transposed_a_mean = numpy.mean(transposed_a)
transposed_b_mean = numpy.mean(transposed_b)

# get the standard deviation
ijk_std = numpy.std(ijk)
kij_std = numpy.std(kij)
jik_std = numpy.std(jik)
ikj_std = numpy.std(ikj)
jki_std = numpy.std(jki)
kji_std = numpy.std(kji)
transposed_a_std = numpy.std(transposed_a)
transposed_b_std = numpy.std(transposed_b)

# set the labels
labels = ['ijk', 'kij', 'jik', 'ikj', 'jki', 'kji', 'AT', 'BT']

# set the x locations for the groups
x = numpy.arange(len(labels))
    
# set the width of the bars
width = 0.5

fig, ax = plt.subplots()
rects1 = ax.bar(x, [ijk_mean, kij_mean, jik_mean, ikj_mean, jki_mean, kji_mean, transposed_a_mean, transposed_b_mean], width, yerr=[ijk_std, kij_std, jik_std, ikj_std, jki_std, kji_std, transposed_a_std, transposed_b_std], label='Mean')

# add some text for labels, title and axes ticks
ax.set_ylabel('Seconds')
ax.set_title('Mean and Standard Deviation of Times')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

# save plot
plt.savefig('plot.png')
