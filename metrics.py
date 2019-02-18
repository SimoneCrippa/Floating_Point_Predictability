import numpy
import os
import statistics
import statsmodels.tsa.stattools as stat
import scipy
from hurst import compute_Hc


path = raw_input("Provide folder with benches to analyze")

for filename in os.listdir(path):
    if(".txt" in filename):
        print "\n" + "\n" + "Analyzing " + filename + "\n"
        with open(filename, "r") as input:
            array = []
            for line in input:
                array.append(int(line))

        print "minimum: " + str(min(array))
        print "maximum: " + str(max(array))
        print "average: " + str(numpy.mean(array))
        print "variance: " + str(numpy.var(array))
        print "standard deviation: " + str(statistics.stdev(array))


        kpss_stat, p_value, lags, crit = stat.kpss(array) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.kpss.html
        print "KPSS: " + str(kpss_stat)


        start = 0
        end = 100
        max_bds = 0
        while(end <= len(array)):
            bds_stat, pvalue = stat.bds(array[start:end]) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.bds.html
            if(bds_stat > max_bds):
                max_bds= bds_stat
            start += 1
            end += 1
        print "BDS: " + str(max_bds)


        H, c, data = compute_Hc(array, kind='change', simplified=True) #https://pypi.org/project/hurst/
        print "Hurst Exponent: " + str(H)