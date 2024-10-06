from math import floor
import random

MAX = 10000
ARRAY_LENGTH = 100000
FILE_NAME = "test_files/TEST_" + str(ARRAY_LENGTH)

random_numbers =[str(floor(random.random() * MAX)) for i in range(ARRAY_LENGTH)]

file = open(FILE_NAME,"w")
file.write(",".join(random_numbers))
