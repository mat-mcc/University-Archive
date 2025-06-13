import numpy as np

def inspect_npz(file):
    data = np.load(file)
    print(f"Keys in {file}: {data.files}")
    return data

# 1. Load and inspect the train.npz file
data_train = inspect_npz('train.npz')
X_train = data_train['x']  # Corrected key
y_train = data_train['y']  # Corrected key

# 2. Load and inspect the test.npz file
data_test = inspect_npz('test.npz')
X_test = data_test['x']  # Corrected key
y_test = data_test['y']  # Corrected key

# 3. Load the large dataset 
try:
    data_large = inspect_npz('train_100.npz')  # Corrected filename
    X_train_large = data_large['x']  # Corrected key
    y_train_large = data_large['y']  # Corrected key
except FileNotFoundError:
    print("train_100.npz not found, skipping large dataset part.")

# Polynomial basis transformation
def poly_features(X, degree=9):
    return np.vstack([X**i for i in range(degree + 1)]).T

# Ordinary Least Squares (OLS) Regression
def ols_regression(X, y):
    Phi = poly_features(X)
    w = np.linalg.inv(Phi.T @ Phi) @ Phi.T @ y
    return w

# Ridge Regression function
def ridge_regression(X, y, lambda_, degree=9):
    Phi = poly_features(X, degree)
    I = np.identity(Phi.shape[1])
    w_ridge = np.linalg.inv(Phi.T @ Phi + lambda_ * I) @ Phi.T @ y
    return w_ridge

# Cross-validation for OLS Regression
def cross_validation_ols(X, y, k_folds=5):
    fold_size = len(X) // k_folds
    errors = []

    for k in range(k_folds):
        start, end = k * fold_size, (k + 1) * fold_size
        X_val_fold = X[start:end]
        y_val_fold = y[start:end]
        X_train_fold = np.concatenate((X[:start], X[end:]), axis=0)
        y_train_fold = np.concatenate((y[:start], y[end:]), axis=0)

        Phi_train = poly_features(X_train_fold)
        Phi_val = poly_features(X_val_fold)

        w = np.linalg.inv(Phi_train.T @ Phi_train) @ Phi_train.T @ y_train_fold

        y_pred = Phi_val @ w
        error = np.mean((y_val_fold - y_pred) ** 2)
        errors.append(error)

    return np.mean(errors)

# Cross-validation for Ridge Regression
def cross_validation_ridge(X, y, lambdas, k_folds=5):
    fold_size = len(X) // k_folds
    avg_errors = []

    for lambda_ in lambdas:
        errors = []
        for k in range(k_folds):
            start, end = k * fold_size, (k + 1) * fold_size
            X_val_fold = X[start:end]
            y_val_fold = y[start:end]
            X_train_fold = np.concatenate((X[:start], X[end:]), axis=0)
            y_train_fold = np.concatenate((y[:start], y[end:]), axis=0)

            w_ridge = ridge_regression(X_train_fold, y_train_fold, lambda_)
            Phi_val = poly_features(X_val_fold)

            y_pred = Phi_val @ w_ridge
            error = np.mean((y_val_fold - y_pred) ** 2)
            errors.append(error)

        avg_errors.append(np.mean(errors))

    return avg_errors

# Load train and test data (this part is now handled above)
# data_train = np.load('train.npz') # This is now replaced
# X_train = data_train['x'] # Corrected key
# y_train = data_train['y'] # Corrected key

# data_test = np.load('test.npz') # This is now replaced
# X_test = data_test['x'] # Corrected key
# y_test = data_test['y'] # Corrected key

# 3.1 - OLS with cross-validation
avg_val_error_ols = cross_validation_ols(X_train, y_train)
w_ols = ols_regression(X_train, y_train)
print(f'Average Validation Error (OLS): {avg_val_error_ols}')
print(f"OLS Weights: {w_ols}")

# 3.2 - Ridge regression with cross-validation
lambdas = np.logspace(-8, 0, 50)
avg_val_errors_ridge = cross_validation_ridge(X_train, y_train, lambdas)
best_lambda = lambdas[np.argmin(avg_val_errors_ridge)]
w_ridge = ridge_regression(X_train, y_train, best_lambda)

print(f'Best Lambda (Ridge): {best_lambda}')
print(f'Ridge Weights (Best λ): {w_ridge}')

# 3.3 - Plotting weights (numerically)
x_vals = np.linspace(0, 1, 10)
phi_vals = poly_features(x_vals)
y_ols_vals = phi_vals @ w_ols
y_ridge_vals = phi_vals @ w_ridge

# Display the model predictions at key points
print(f"x values: {x_vals}")
print(f"OLS predictions: {y_ols_vals}")
print(f"Ridge predictions: {y_ridge_vals}")

# 3.4 - Test MSE for both models
Phi_test = poly_features(X_test)

y_pred_ols = Phi_test @ w_ols
mse_ols = np.mean((y_test - y_pred_ols) ** 2)

y_pred_ridge = Phi_test @ w_ridge
mse_ridge = np.mean((y_test - y_pred_ridge) ** 2)

print(f'Test MSE for OLS Model: {mse_ols}')
print(f'Test MSE for Ridge Model: {mse_ridge}')

# 3.5 - Large dataset (without cross-validation)
try:
    data_large = np.load('train_100.npz')  # Use the correct file name
    X_train_large = data_large['x']  # Corrected key
    y_train_large = data_large['y']  # Corrected key
    w_large_ols = ols_regression(X_train_large, y_train_large)
    y_large_vals = poly_features(x_vals) @ w_large_ols

    print("OLS Weights (Large Dataset):", w_large_ols)
    print(f"OLS predictions (Large Dataset): {y_large_vals}")

except FileNotFoundError:
    print("train_100.npz not found, skipping large dataset part.")

# Summary of results
print("\nSummary of Results:")
print(f"1. OLS Weights: {w_ols}")
print(f"2. Best Lambda for Ridge: {best_lambda}")
print(f"3. Ridge Weights: {w_ridge}")
print(f"4. OLS Test MSE: {mse_ols}")
print(f"5. Ridge Test MSE: {mse_ridge}")
