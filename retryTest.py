import os
import sys
import time

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

fd = open(dirname + "/summary.txt", "w")

for i in retries:
  for j in scale_factor:
    filename = dirname + "/" + "retry_" + str(i) + "_" + str(j)
    result = os.system("./build/s3-sample " + n + " " + flambda + " " + filename + " " + str(i) + " " + str(j))
    fd.write(str(i) + " retries and " + str(j) + " scale_factor:" + "\n")
    fd.write(str(result))
    fd.write("\n")

fd.close()
