import sys
import random

if len(sys.argv) != 2:
	print("arg error")
	sys.exit()

num = int(sys.argv[1])
num_list = list(range(1, num + 1))
random.shuffle(num_list)
num_list_str = list(map(str, num_list))
num_str = ' '.join(num_list_str)
print(num_str)
