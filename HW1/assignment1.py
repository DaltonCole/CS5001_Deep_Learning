# File name:      assignment1.py
# Author:         Dalton Cole

from random import randrange

### Constants ###
learning_rate = 0.001
number_of_iterations = 1500
#################

### Initalize ###
x0 = 1
w0 = randrange(0,20000)
w1 = randrange(0,20000)
#################

# List containing (x1, y)
input_output_list_tuple = []

# Get x1 and y from file
with open('zdata.txt', 'r') as f:
	for line in f:
		x1, y = line.split()
		input_output_list_tuple.append((int(x1), int(y)))

# List containing the errors from each iteration
error_list = []

# Error for each weight
error0 = 0
error1 = 0

# For each iteration
for i in range(number_of_iterations):
	# Reset error list
	error_list = []

	# For each (x1, y) value pair
	for x1, y in input_output_list_tuple:
		# Compute yCap
		y_bar = (x0 * w0) + (x1 * w1)

		# Find error
		error0 = error0 + ((y - y_bar) * x0)
		error1 = error1 + ((y - y_bar) * x1)

	# Normalize error
	error0 /= len(input_output_list_tuple)
	error1 /= len(input_output_list_tuple)

	# Update weight
	w0 = w0 + (learning_rate * error0)
	w1 = w1 + (learning_rate * error1)

# Calculate sum of squares
sum_of_squares = 0
for x1, y in input_output_list_tuple:
	sum_of_squares += pow((y - ((x0 * w0) + (x1 * w1))), 2)

# Output 
print("CS-5001 : HW#1 : Regression with one variable.")
print("Programmer: Dalton Russell Cole")
print()
print("Learning rate eta = " + str(learning_rate))
print("After %d iterations:" % number_of_iterations)
print("Sum of Squares Errors = %d" % sum_of_squares)
print("Weights:")
print("w0 = %f" % w0)
print("w1 = %f" % w1)