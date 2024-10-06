from math import floor
import random

ARRAY_SIZES = [1000,5000,10000,20000,50000,100000];
MAX = 10000

for size in ARRAY_SIZES:
  FILE_NAME = "test_files/TEST_" + str(size)
  random_numbers =[str(floor(random.random() * MAX)) for i in range(size)]
  file = open(FILE_NAME,"w")
  file.write(",".join(random_numbers))
