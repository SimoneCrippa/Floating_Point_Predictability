import numpy
import os
import statistics
import statsmodels.tsa.stattools as stat
import warnings
from hurst import compute_Hc

warnings.filterwarnings("ignore", module="stat") #ignore warnings on BDS pvalue

path = raw_input("Provide folder with benches to analyze")

file = open("statistics_results.txt", "w")

for folder in os.listdir(path):
    if("." not in folder):
        for filename in os.listdir(path+"/"+folder):
            if(".txt" in filename):
                print "\n" + "\n" + "Analyzing " + folder + "/" + filename + "\n"
                file.write("\n" + "\n" + "Analyzing " + folder + "/" + filename + "\n")
                with open(path + "/" + folder + "/" + filename, "r") as input:
                    array = []
                    for line in input:
                        array.append(int(line))

                file.write("minimum: " + str(min(array)) + "\n")
                file.write("maximum: " + str(max(array)) + "\n")
                file.write("mean: " + str(numpy.mean(array)) + "\n")
                file.write("variance: " + str(numpy.var(array)) + "\n")
                file.write("standard deviation: " + str(statistics.stdev(array)) + "\n")

                kpss_stat, p_value, lags, crit = stat.kpss(array) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.kpss.html
                file.write("KPSS: " + str(kpss_stat) + "\n")

                start = 0
                end = 200
                max_bds = 0
                while(end <= len(array)):
                    bds_stat, pvalue = stat.bds(array[start:end]) #https://www.statsmodels.org/dev/generated/statsmodels.tsa.stattools.bds.html
                    if(bds_stat > max_bds):
                        max_bds= bds_stat
                    start += 1
                    end += 1
                file.write("BDS: " + str(max_bds) + "\n")

                H, c, data = compute_Hc(array, kind='change', simplified=True) #https://pypi.org/project/hurst/
                file.write("Hurst Exponent: " + str(H) + "\n")

file.close()


