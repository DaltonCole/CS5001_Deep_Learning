# File name:      assignment1.py
# Author:         Dalton Cole
from random import randrange
from math import e

def sigmoid(x):
	"""Perform the sigmoid function: (1 / 1 + e^(-x))

	Returns:
		(float): The value of the signmoid function or
			1 if the value of e^(-x) is too small. The error introduced
			by doing this is insignificant.
	"""
	try:
		return (1 / (1 + (pow(e, -x))))
	except:
		# If e^(-x) is too small a number, return 1/1 = 1
		return 1

def sigmoid_derivatie(x):
	"""Performs the derivative of sigmoid: sig(x) * (1 - sig(x))

	Returns:
		(float): The value of the derivative of sigmoid
	"""
	return (sigmoid(x) * (1 - sigmoid(x)))

### Constants ###
learning_rate = 0.001
number_of_iterations = 5000
#################

### Initalize ###
x0 = 1
w0 = randrange(-1000,1001)
w1 = randrange(-1000,1001)
w2 = randrange(-1000,1001)
w3 = randrange(-1000,1001)
w4 = randrange(-1000,1001)
#################

# List containing (x1, x2, x3, x4, y)
input_output_list_tuple = []

# Get x1, x2, x3, x4, and y from file
with open('pizzacatdata.txt', 'r') as f:
	for line in f:
		x1, x2, x3, x4, y = line.split()
		input_output_list_tuple.append((int(x1), int(x2), int(x3), int(x4), int(y)))

# Error for each weight
error0 = 0
error1 = 0
error2 = 0
error3 = 0
error4 = 0

# For each iteration
for i in range(number_of_iterations):
	# For each (x1, x2, x3, x4, y) value set
	for x1, x2, x3, x4, y in input_output_list_tuple:
		# Compute yCap
		y_bar = sigmoid((x0 * w0) + (x1 * w1) + (x2 * w2) + (x3 * w3) + (x4 * w4))

		# Delta value = Y(x) - y_bar
		delta = y - y_bar

		# Update weights = wi ← wi + ηδp(1 − p)Xi(e)
		w0 = w0 + (learning_rate * delta * x0) 
		w1 = w1 + (learning_rate * delta * x1)
		w2 = w2 + (learning_rate * delta * x2)
		w3 = w3 + (learning_rate * delta * x3)
		w4 = w4 + (learning_rate * delta * x4)


# Calculate sum of squares
sum_of_squares = 0
for x1, x2, x3, x4, y in input_output_list_tuple:
	sum_of_squares += pow((y - sigmoid((x0 * w0) + (x1 * w1) + (x2 * w2) + (x3 * w3) + (x4 * w4))), 2)

# Output 
print("CS-5001 : HW#2 : Logistic Regression.")
print("Programmer: Dalton Russell Cole")
print("No cats were hurt gathering this data.")
print()
print("Using learning rate eta = " + str(learning_rate))
print("After %d iterations:" % number_of_iterations)
print("Sum of Squares Errors = %d " % sum_of_squares)
print("Weights:")
print("w0 = %f" % w0)
print("w1 = %f" % w1)
print("w2 = %f" % w2)
print("w3 = %f" % w3)
print("w4 = %f" % w4)