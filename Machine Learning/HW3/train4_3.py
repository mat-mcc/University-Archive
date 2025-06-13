import numpy as np

# Sigmoid function
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Negative Log-Likelihood (NLL) function
def compute_nll(X, y, w):
    m = X.shape[0]  # Number of samples
    predictions = sigmoid(X.dot(w))  # Model predictions
    nll = -np.mean(y * np.log(predictions) + (1 - y) * np.log(1 - predictions))  # NLL
    return nll

# Gradient of the NLL function
def compute_gradient(X, y, w):
    m = X.shape[0]  # Number of samples
    predictions = sigmoid(X.dot(w))  # Model predictions
    gradient = (1 / m) * X.T.dot(predictions - y)  # Gradient
    return gradient

# Gradient Descent algorithm to find the optimal weights
# Gradient Descent algorithm to find the optimal weights
def train_logistic_regression(X, y, learning_rate=1e-4, max_iter=1000, tolerance=1e-4):
    # Initialize weights (random small values)
    w = np.zeros(X.shape[1])
    
    # Track previous NLL to detect convergence
    prev_nll = float('inf')
    
    for iteration in range(max_iter):
        # Compute the gradient of the NLL
        gradient = compute_gradient(X, y, w)
        
        # Update the weights using gradient descent
        w -= learning_rate * gradient
        
        # Compute the current NLL
        current_nll = compute_nll(X, y, w)
        
        # Print the NLL for this iteration
        print(f"Iteration {iteration + 1}: NLL = {current_nll}")
        
        # Check for convergence (if the change in NLL is less than tolerance)
        if np.abs(prev_nll - current_nll) < tolerance:
            print(f"Converged after {iteration+1} iterations.")
            break
        
        prev_nll = current_nll
        
    return w

# Load the training data from the file "train4_2.npz"
data = np.load("train4_2.npz")
X_train = data['X']
y_train = data['y']

# normalize features to have mean 0 and variance 1
X_train = (X_train - np.mean(X_train, axis=0)) / np.std(X_train, axis=0)

# Train the logistic regression model
weights = train_logistic_regression(X_train, y_train, learning_rate=1e-4)

# Output the learned weights
print("Learned weights:", weights)

np.save('logistic_regression_weights.npy', weights)
