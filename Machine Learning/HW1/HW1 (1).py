# Matthew McCaughan
# CS 461 Machine Learning Principles
# Homework 1, Question 4
# Naive Bayes Classifier

# Adopted from:
# https://docs.python.org/3/library/csv.html
# https://www.kaggle.com/code/prashant111/naive-bayes-classifier-in-python
# https://www.datacamp.com/tutorial/naive-bayes-scikit-learn


import numpy
# Load CSV data
def load_csv(file_path):
    data = numpy.genfromtxt(file_path, delimiter=',', skip_header=1)
    return data

# mean and variance using MLE
def mle_mean_variance(feature_values):
    mean_value = numpy.mean(feature_values)
    variance_value = numpy.var(feature_values)
    return mean_value, variance_value

# PDF
def gaussian_pdf(value, mean, variance):
    return (1 / numpy.sqrt(2 * numpy.pi * variance)) * numpy.exp(-(value - mean)**2 / (2 * variance))

# calculate priors and parameters
def train_naive_bayes(data):
    glucose_values = data[:, 0]
    blood_pressure_values = data[:, 1]
    diabetes_labels = data[:, 2]

    # separate positive/negative samples
    glucose_positive = glucose_values[diabetes_labels == 1]
    glucose_negative = glucose_values[diabetes_labels == 0]
    blood_pressure_positive = blood_pressure_values[diabetes_labels == 1]
    blood_pressure_negative = blood_pressure_values[diabetes_labels == 0]

    # estimates for mean and variance
    mean_glucose_positive, variance_glucose_positive = mle_mean_variance(glucose_positive)
    mean_glucose_negative, variance_glucose_negative = mle_mean_variance(glucose_negative)
    mean_blood_pressure_positive, variance_blood_pressure_positive = mle_mean_variance(blood_pressure_positive)
    mean_blood_pressure_negative, variance_blood_pressure_negative = mle_mean_variance(blood_pressure_negative)

    # priors
    prior_diabetes_positive = numpy.mean(diabetes_labels)
    prior_diabetes_negative = 1 - prior_diabetes_positive

    return {
        'mean_glucose_positive': mean_glucose_positive, 
        'variance_glucose_positive': variance_glucose_positive,
        'mean_glucose_negative': mean_glucose_negative, 
        'variance_glucose_negative': variance_glucose_negative,
        'mean_blood_pressure_positive': mean_blood_pressure_positive, 
        'variance_blood_pressure_positive': variance_blood_pressure_positive,
        'mean_blood_pressure_negative': mean_blood_pressure_negative, 
        'variance_blood_pressure_negative': variance_blood_pressure_negative,
        'prior_diabetes_positive': prior_diabetes_positive, 
        'prior_diabetes_negative': prior_diabetes_negative
    }

# predict class based on Naive Bayes
def predict_naive_bayes(glucose_value, blood_pressure_value, model_parameters):
    # Likelihoods
    likelihood_glucose_given_diabetes_positive = gaussian_pdf(glucose_value, 
                                                              model_parameters['mean_glucose_positive'], 
                                                              model_parameters['variance_glucose_positive'])
    likelihood_blood_pressure_given_diabetes_positive = gaussian_pdf(blood_pressure_value, 
                                                                     model_parameters['mean_blood_pressure_positive'], 
                                                                     model_parameters['variance_blood_pressure_positive'])
    
    likelihood_glucose_given_diabetes_negative = gaussian_pdf(glucose_value, 
                                                              model_parameters['mean_glucose_negative'], 
                                                              model_parameters['variance_glucose_negative'])
    likelihood_blood_pressure_given_diabetes_negative = gaussian_pdf(blood_pressure_value, 
                                                                     model_parameters['mean_blood_pressure_negative'], 
                                                                     model_parameters['variance_blood_pressure_negative'])

    # posteriors
    posterior_diabetes_positive = (likelihood_glucose_given_diabetes_positive * 
                                   likelihood_blood_pressure_given_diabetes_positive * 
                                   model_parameters['prior_diabetes_positive'])
    
    posterior_diabetes_negative = (likelihood_glucose_given_diabetes_negative * 
                                   likelihood_blood_pressure_given_diabetes_negative * 
                                   model_parameters['prior_diabetes_negative'])

    return 1 if posterior_diabetes_positive > posterior_diabetes_negative else 0

# evaluate model
def evaluate_naive_bayes(test_data, model_parameters):
    glucose_test_values = test_data[:, 0]
    blood_pressure_test_values = test_data[:, 1]
    true_diabetes_labels = test_data[:, 2]

    predictions = numpy.array([predict_naive_bayes(glucose, blood_pressure, model_parameters) 
                               for glucose, blood_pressure in zip(glucose_test_values, blood_pressure_test_values)])

    accuracy = numpy.mean(predictions == true_diabetes_labels)
    return accuracy

if __name__ == "__main__":
    train_data = load_csv('train.csv')
    test_data = load_csv('test.csv')

    # train!
    model_parameters = train_naive_bayes(train_data)

    # test!
    accuracy = evaluate_naive_bayes(test_data, model_parameters)

    print(f"Accuracy: {accuracy * 100:.2f}%")
