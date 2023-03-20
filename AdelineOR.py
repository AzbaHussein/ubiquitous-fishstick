import numpy as np
features = np.array(
	[
		[-1, -1],
		[-1, 1],
		[1, -1],
		[1, 1]
	])

labels = np.array([-1, 1, 1, 1])

print(features, labels)
weight = [0.5, 0.5]
bias = 0.1
learning_rate = 0.2
epoch = 10

for i in range(epoch):
	print("epoch :", i+1)
	sum_squared_error = 0.0
	for j in range(features.shape[0]):
		actual = labels[j]
		x1 = features[j][0]
		x2 = features[j][1]
		unit = (x1 * weight[0]) + (x2 * weight[1]) + bias
		error = actual - unit
		print("error =", error)
		sum_squared_error += error * error
		weight[0] += learning_rate * error * x1
		weight[1] += learning_rate * error * x2
		bias += learning_rate * error

	print("sum of squared error = ", sum_squared_error/4, "\n\n")

