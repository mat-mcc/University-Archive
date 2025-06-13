import numpy as np
import matplotlib.pyplot as plt
from itertools import combinations_with_replacement

def check_npz_keys(file_name):
    """Check and print the keys in a .npz file."""
    with np.load(file_name) as data:
        print(f"Keys in {file_name}: {list(data.keys())}")
        return list(data.keys())

train_keys = check_npz_keys('vgg16_train.npz')
test_keys = check_npz_keys('vgg16_test.npz')


train_data = np.load('vgg16_train.npz', allow_pickle=True)
test_data = np.load('vgg16_test.npz', allow_pickle=True)

# Extract embeddings, target years, and filenames
X_train = train_data['logit']  
y_train = train_data['year']   
train_filenames = train_data['filename'].astype(str)  

X_test = test_data['logit']    
y_test = test_data['year']       
test_filenames = test_data['filename'].astype(str)  

def pca_whitening(X, n_components):
    # Center the data
    X_centered = X - np.mean(X, axis=0)

    # Perform PCA
    cov_matrix = np.cov(X_centered, rowvar=False)
    eigenvalues, eigenvectors = np.linalg.eigh(cov_matrix)

    # Sort eigenvalues and eigenvectors
    sorted_indices = np.argsort(eigenvalues)[::-1]
    eigenvalues = eigenvalues[sorted_indices][:n_components]
    eigenvectors = eigenvectors[:, sorted_indices][:, :n_components]

    # Project the data
    X_pca = X_centered @ eigenvectors

    # Whitening transformation
    X_whitened = X_pca / np.sqrt(eigenvalues + 1e-5)  

    return X_whitened

def plot_pca(X, y, title):
    plt.figure(figsize=(8, 6))
    plt.scatter(X, y, alpha=0.5)
    plt.title(title)
    plt.xlabel('PCA Dimension')
    plt.ylabel('Year of Made')
    plt.grid()
    plt.show()

def create_polynomial_features(X, degree):
    n_samples, n_features = X.shape
    features = [np.ones(n_samples)]  
    
    for d in range(1, degree + 1):
        for combination in combinations_with_replacement(range(n_features), d):
            features.append(np.prod(X[:, combination], axis=1))
    
    return np.column_stack(features)

def train_model(X, y, degree):
    X_poly = create_polynomial_features(X, degree)
    weights = np.linalg.pinv(X_poly) @ y  
    return weights

def mean_squared_error(y_true, y_pred):
    return np.mean((y_true - y_pred) ** 2)

def evaluate_model(model, X_test, y_test, degree):
    X_test_poly = create_polynomial_features(X_test, degree)
    y_pred_test = X_test_poly @ model
    test_mse = mean_squared_error(y_test, y_pred_test)
    print(f"Test MSE: {test_mse}")
    return y_pred_test

def find_most_accurate_prediction(model, X_test, y_test, degree, filenames):
    X_test_poly = create_polynomial_features(X_test, degree)
    y_pred_test = X_test_poly @ model

    differences = np.abs(y_test - y_pred_test)
    most_accurate_index = np.argmin(differences)

    print(f"Most Accurate Prediction Index: {most_accurate_index}")
    print(f"Actual Year: {y_test[most_accurate_index]}, Predicted Year: {y_pred_test[most_accurate_index]}")
    print(f"Filename: {filenames[most_accurate_index]}")

def find_least_accurate_prediction(model, X_test, y_test, degree, filenames):
    X_test_poly = create_polynomial_features(X_test, degree)
    y_pred_test = X_test_poly @ model

    differences = np.abs(y_test - y_pred_test)
    least_accurate_index = np.argmax(differences)

    print(f"Least Accurate Prediction Index: {least_accurate_index}")
    print(f"Actual Year: {y_test[least_accurate_index]}, Predicted Year: {y_pred_test[least_accurate_index]}")
    print(f"Filename: {filenames[least_accurate_index]}")

X_train_1d = pca_whitening(X_train, n_components=1)
plot_pca(X_train_1d, y_train, title='Year over 1D PCA')

X_train_2d = pca_whitening(X_train, n_components=2)
plt.figure(figsize=(8, 6))
plt.scatter(X_train_2d[:, 0], y_train, alpha=0.5, label='First PCA Component')
plt.scatter(X_train_2d[:, 1], y_train, alpha=0.5, label='Second PCA Component', color='r')
plt.title('Year over 2D PCA')
plt.xlabel('PCA Dimension 1 / PCA Dimension 2')
plt.ylabel('Year of Made')
plt.legend()
plt.grid()
plt.show()

# Train a model using polynomial regression
degree = 2  # Choose the polynomial degree based on performance
X_train_poly = create_polynomial_features(X_train_2d, degree)  # Create polynomial features for training
model = train_model(X_train_poly, y_train, degree)  # Train the model

# Create polynomial features for testing data
X_test_2d = pca_whitening(X_test, n_components=2)  # Perform PCA on test data
X_test_poly = create_polynomial_features(X_test_2d, degree)  # Create polynomial features for testing

# Evaluate the model and get predictions
y_pred_test = evaluate_model(model, X_test_poly, y_test, degree)

# Identify the most accurate and least accurate predictions
find_most_accurate_prediction(model, X_test_poly, y_test, degree, test_filenames)
find_least_accurate_prediction(model, X_test_poly, y_test, degree, test_filenames)
