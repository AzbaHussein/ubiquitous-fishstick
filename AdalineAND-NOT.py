# input array
arr = [[1, 1], [1, -1], [-1, 1], [-1, -1]]

# target array
t = [-1, 1, -1, -1]

w1, w2, b = 0.2, 0.2, 0.2  # initial weights and bias
learning_rate = 0.2
num_epochs = 5

for i in range(num_epochs):
    avg_error = 0
    print("EPOCH ", i + 1, " Errors\n")
    for j in range(len(arr)):
        # calculating net input
        yi = arr[j][0] * w1 + arr[j][1] * w2 + 1 * b
        dif = t[j] - yi
        
        # updated weights
        w1 += learning_rate * dif * arr[j][0]
        w2 += learning_rate * dif * arr[j][1]
        b += learning_rate * dif * 1
        err = dif * dif
        print(err, end=" ")
        avg_error += err
    print("\nTotal Mean Error :", avg_error, "\n\n")


