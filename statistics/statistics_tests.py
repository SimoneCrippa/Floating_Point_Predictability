import statistics
import pandas as pd
from statsmodels.tsa.stattools import kpss
from statsmodels.tsa.stattools import bds
import numpy
import os

path = raw_input("Provide file with statistics to analyze\n")

file = open("tests_results.txt", "w")

names = []
kpssValues = []
bdsValues = []
hurstValues = []

with open(path,"r") as input:  # get data from a file and load into arrays
    for line in input:
        if "Analyzing" in line:
            names.append(str(line.split(" ")[1]))
        if "KPSS" in line:
            kpssValues.append(float((line.split(" ")[1][0:-1])))
        if "BDS" in line:
            bdsValues.append(float((line.split(" ")[1][0:-1])))
        if "Hurst" in line:
            hurstValues.append(float((line.split(":")[1][0:-1])))

kpssSignValues = [("5%", 0.463), ("2.5%", 0.574), ("1%", 0.739)]    # significance values for KPSS upper tailed test

file.write("KPSS Test:" + "\n")

for sign in kpssSignValues:
    file.write("\n" + "Significance level: " + sign[0] + "\n\n")
    countFixed = 0  # counters for fixed/floating benchmarks which pass the test
    countFloating = 0
    acceptedNames = []  # name of devices/benchmarks which pass the test
    currentDevice = ""
    for i in range(0, len(kpssValues)):
        if kpssValues[i] < sign[1]:     # upper tailed test: if the test statistic is lower than the critical value I cannot reject the null hypothesis
            if "fixed" in names[i]:
                countFixed += 1
            else:
                countFloating += 1
            acceptedNames.append(names[i])

    file.write("A total of " + str(countFixed) + " on " + str(len(names)/2) + " fixed benchmarks have accepted the KPSS H0 hypothesis" + "\n")
    file.write("A total of " + str(countFloating) + " on " + str(len(names) / 2) + " floating benchmarks have accepted the KPSS H0 hypothesis" + "\n")

    for elem in acceptedNames:
        if elem.split("/")[0] != currentDevice:
            file.write("\n" + "Device name: " + elem.split("/")[0] + "\n")
            currentDevice = elem.split("/")[0]
        file.write("Benchmark name: " + (elem.split("/")[1]).split("results")[0][0:-1] + "\n")


bdsSignValues = [("2.5%", 1.96), ("1%", 2.33), ("0.05%", 2.58)]    # # significance values for BDS double tailed test

file.write("\nBDS Test:" + "\n")

for sign in bdsSignValues:
    file.write("Significance level: " + sign[0] + "\n")
    countFixed = 0
    countFloating = 0
    acceptedNames = []
    currentDevice = ""
    for i in range(0, len(bdsValues)):
        if abs(bdsValues[i]) < sign[1]:  # double tailed test, if the statistic test is included in the two bounds, I cannot reject H0
            if "fixed" in names[i]:
                countFixed += 1
            else:
                countFloating += 1
            acceptedNames.append(names[i])

    file.write("A total of " + str(countFixed) + " on " + str(len(names)/2) + " fixed benchmarks have accepted the BDS H0 hypothesis" + "\n")
    file.write("A total of " + str(countFloating) + " on " + str(len(names) / 2) + " floating benchmarks have accepted the BDS H0 hypothesis" + "\n")

    for elem in acceptedNames:
        if elem.split("/")[0] != currentDevice:
            file.write("\n" + "Device name: " + elem.split("/")[0] + "\n")
            currentDevice = elem.split("/")[0]
        file.write("Benchmark name: " + (elem.split("/")[1]).split("results")[0][0:-1] + "\n")

hurstExpThreshold = 0.5		# hurst exponent threshold

file.write("\nHurst Exponent:" + "\n")

countFixed = 0
countFloating = 0
uncorrelatedCount = 0
uncorrelatedNames = []
acceptedNames = []
currentDevice = ""
for i in range(0, len(hurstValues)):
    if hurstValues[i] > hurstExpThreshold:  # if 0.5 < H < 1 positive autocorrelation
        if "fixed" in names[i]:
            countFixed += 1
        else:
            countFloating += 1
        acceptedNames.append(names[i])
    elif hurstValues[i] == hurstExpThreshold:    # if H = 0.5 uncorrelated series
        uncorrelatedCount += 1
        uncorrelatedNamesNames.append(names[i])

file.write("A total of " + str(countFixed) + " on " + str(len(names)/2) + " fixed benchmarks have Hurst exponent > " + str(hurstExpThreshold) + "\n")
file.write("A total of " + str(countFloating) + " on " + str(len(names) / 2) + " floating benchmarks have Hurst exponent > " + str(hurstExpThreshold) + "\n")
if uncorrelatedCount != 0:
    file.write(str(uncorrelatedCount) + " benchmarks have Hurst Exponent = " + str(hurstExpThreshold) + "\n")

for elem in acceptedNames:
    if elem.split("/")[0] != currentDevice:
        file.write("\n" + "Device name: " + elem.split("/")[0] + "\n")
        currentDevice = elem.split("/")[0]
    file.write("Benchmark name: " + (elem.split("/")[1]).split("results")[0][0:-1] + "\n")


file.close()
