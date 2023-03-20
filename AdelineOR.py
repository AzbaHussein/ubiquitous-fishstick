import numpy as np

features = np.array(
    [
        [-1, -1],
        [-1, 1],
        [1, -1],
        [1, 1]
    ]
)

labels = np.array([-1, 1, 1, -1])

print(features, labels)

# Initialize weights and bias
weight = np.array([0.5, 0.5])
bias = 0.1

# Set learning rate and number of epochs
learning_rate = 0.2
num_epochs = 10

# Train the model
for i in range(num_epochs):
    print("Epoch :", i+1)
    sum_squared_error = 0.0
    for j in range(features.shape[0]):
        actual = labels[j]
        x = features[j]
        unit = np.dot(x, weight) + bias
        error = actual - np.sign(unit)
        print("Error :", error)
        sum_squared_error += error * error
        weight += learning_rate * error * x
        bias += learning_rate * error

    print("Sum of Squared Error = ", sum_squared_error/4, "\n\n")
