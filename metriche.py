import numpy
import statistics
import statsmodels.tsa.stattools as stat
import scipy
from hurst import compute_Hc

with open("bench.txt", "r") as input:
    array = []
    for line in input:
        array.append(int(line))

print "minimo: " + str(min(array))
print "massimo: " + str(max(array))
print "media: " + str(numpy.mean(array))
print "varianza: " + str(numpy.var(array))
print "deviazione standard: " + str(statistics.stdev(array))

kpss_stat, p_value, lags, crit = stat.kpss(array) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.kpss.html
print "KPSS: " + str(kpss_stat)

bds_stat, pvalue = stat.bds(array[:10000]) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.bds.html
print "BDS: " + str(bds_stat)

H, c, data = compute_Hc(array, kind='price', simplified=True)
print "Hurst Exponent: " + str(H)



