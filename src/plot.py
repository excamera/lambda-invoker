import csv
import matplotlib.pyplot as plt

filename = "results.txt"
def getColumn(filename, column):
    results = csv.reader(open(filename), delimiter=",")
    return [result[column] for result in results]

n = getColumn(filename,0)
s = getColumn(filename,1)
e = getColumn(filename, 2)

plt.figure("Lambdas/Time")
plt.xlabel("Lambda Invocation")
plt.ylabel("Time")
plt.plot(n,s,e)
