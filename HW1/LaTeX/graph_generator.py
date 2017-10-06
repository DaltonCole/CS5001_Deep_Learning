import numpy as np
import matplotlib.pyplot as plt
import plotly.plotly as py

### Found from regression ###
"""
w0 = 2200
w1 = 200

Learning rate eta = 0.001
After 1500 iterations:
Sum of Squares Errors = 133987898
Weights:
w0 = 2211.771589
w1 = 234.991411
"""
w0 = 2211.771589
w1 = 234.991411
#############################

# List containing (x1, y)
input_output_list_tuple = []
a = []
b = []

# Get x1 and y from file
with open('./../zdata.txt', 'r') as f:
	for line in f:
		x1, y = line.split()
		a.append(int(x1))
		b.append(int(y))

# Plot points
plt.scatter(a, b, label='Zdata Points', color=['orange'])

# Get largest value
a.sort()

# Plot regression line
plt.plot([0, a[-1]], [w0, (a[-1] * w1 + w0)], 'k-', label='Regression Line')

# Place a legend to the right of this smaller subplot.
plt.legend(loc=4)

# Add labels
plt.xlabel('x')
plt.ylabel('y')

# Show and save figure
plt.savefig('plot.pdf')
plt.show()