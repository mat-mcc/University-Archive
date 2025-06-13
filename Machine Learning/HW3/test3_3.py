import numpy as np
import os

def gaussian(x, mean, variance):
    """Calculate the Gaussian probability density function."""
    return (1 / np.sqrt(2 * np.pi * variance)) * np.exp(-0.5 * ((x - mean) ** 2) / variance)

def load_data(file_name):
    """Load data from a .npz file in the same directory."""
    file_path = os.path.join(os.path.dirname(__file__), file_name)
    data = np.load(file_path)
    X = data['x']  # Feature matrix
    y = data['y']  # Labels
    return X, y

def calculate_priors(y):
    """Calculate prior probabilities for each class."""
    prior_pos = np.sum(y == 1) / len(y)  # Probability of class +1
    prior_neg = np.sum(y == -1) / len(y) # Probability of class -1
    return prior_pos, prior_neg

def predict(X_test, mu_pos, var_pos, mu_neg, var_neg, prior_pos, prior_neg):
    """Predict class labels for test data using MAP rule."""
    predictions = []
    
    for x in X_test:
        # Calculate Gaussian probabilities for class +1 and apply prior
        prob_pos = prior_pos * gaussian(x, mu_pos, var_pos).prod()  # Assuming independence across features
        
        # Calculate Gaussian probabilities for class -1 and apply prior
        prob_neg = prior_neg * gaussian(x, mu_neg, var_neg).prod()  # Assuming independence across features
        
        # Classify based on the higher probability
        if prob_pos >= prob_neg:
            predictions.append(1)
        else:
            predictions.append(-1)
    
    return np.array(predictions)

def calculate_accuracy(y_true, y_pred):
    """Calculate the accuracy of predictions."""
    correct = np.sum(y_true == y_pred)
    return correct / len(y_true)

def main():
    # Load the training data to compute prior probabilities
    _, y_train = load_data('train.npz')
    prior_pos, prior_neg = calculate_priors(y_train)

    # Set the model parameters (use values train3_1.py)
    mu_pos = np.array([-0.0721922106722285])
    var_pos = np.array([1.3031231465734459])
    mu_neg = np.array([0.9401561132214228])
    var_neg = np.array([1.9426265036964034])  
    
    # L
    # Load the test data
    X_test, y_test = load_data('test.npz')

    # Predict the classes for the test set using MAP rule
    y_pred = predict(X_test, mu_pos, var_pos, mu_neg, var_neg, prior_pos, prior_neg)

    # Calculate and print the test accuracy
    accuracy = calculate_accuracy(y_test, y_pred)
    print(f"Test Accuracy with MAP rule: {accuracy * 100:.2f}%")

if __name__ == "__main__":
    main()
