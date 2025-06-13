import numpy as np
import os

def load_data(file_name):
    """Load the training data from a .npz file in the same directory."""
    file_path = os.path.join(os.path.dirname(__file__), file_name)
    data = np.load(file_path)
    X = data['x']  # Feature matrix
    y = data['y']  # Labels
    return X, y

def compute_statistics(X, y):
    """Compute mean and variance for each class."""
    # Find the indices for the positive and negative classes
    pos_indices = np.where(y == 1)[0]
    neg_indices = np.where(y == -1)[0]

    # Compute the statistics for the positive class
    mu_pos = np.mean(X[pos_indices], axis=0)
    var_pos = np.var(X[pos_indices], axis=0)

    # Compute the statistics for the negative class
    mu_neg = np.mean(X[neg_indices], axis=0)
    var_neg = np.var(X[neg_indices], axis=0)

    return mu_pos, var_pos, mu_neg, var_neg

def main():
    # Load the training data
    X, y = load_data('train.npz')

    # Compute the statistics
    mu_pos, var_pos, mu_neg, var_neg = compute_statistics(X, y)

    # Print the results
    print("Class + Statistics:")
    print(f"Mean (µ): {mu_pos}")
    print(f"Variance (σ²): {var_pos}\n")

    print("Class - Statistics:")
    print(f"Mean (µ): {mu_neg}")
    print(f"Variance (σ²): {var_neg}")

if __name__ == "__main__":
    main()
