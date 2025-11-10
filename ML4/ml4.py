# Assignment B4 - Gradient Descent Algorithm
# Aim: Implement Gradient Descent to find local minima of y = (x + 3)^2 starting from x = 2

# Import required library
import matplotlib.pyplot as plt

# Define the function and its derivative
def f(x):
    return (x + 3)**2

def df(x):
    return 2 * (x + 3)
 
x = 2            # starting point
learning_rate = 0.1
precision = 0.000001
max_iters = 1000

# To store progress
x_list = [x]
y_list = [f(x)]

# Gradient Descent Algorithm
for i in range(max_iters):
    grad = df(x)
    new_x = x - learning_rate * grad
    step_size = abs(new_x - x)
    
    x = new_x
    x_list.append(x)
    y_list.append(f(x))
    
    if step_size < precision:
        break

# Print final results
print("Local minima occurs at x =", round(x, 5))
print("Minimum value of function y =", round(f(x), 5))
print("Total iterations:", i + 1)

# Plotting the function and descent path
x_vals = [i for i in range(-10, 5)]
y_vals = [f(i) for i in x_vals]
plt.plot(x_vals, y_vals, label='y = (x + 3)^2', color='blue')
plt.scatter(x_list, y_list, color='red', label='Gradient Descent Steps')
plt.title("Gradient Descent Convergence")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.show()