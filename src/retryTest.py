import os
import sys
import time
import subprocess

retries      = range(0,15)
scale_factor = [10, 20, 25, 30, 40, 50]

print sys.argv

if len(sys.argv) >= 1:
  n = sys.argv[1]
else:
  n = 1

if len(sys.argv) >= 2:
  flambda = sys.argv[2]
else:
  flambda = "SLEEP5"

dirname = "build/" + flambda + "_retry_expt_" + str(time.time())
print "Creating directory " + dirname + "..."
os.mkdir(dirname)

for i in retries:
  for j in scale_factor:
    filename = dirname + "/" + "retry_" + str(i) + "_" + str(j)
    os.system("./build/s3-sample " + n + " " + flambda + " " + filename + " " + str(i) + " " + str(j) + " >> " + dirname + "/summary.txt")

fd.close()
