import numpy as np
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split

# Step 1: Load the data from "spam_ham.csv"
data = pd.read_csv("spam_ham.csv")

# Step 2: Separate features (X) and labels (y)
X = data.drop(columns=['cls'])  # Features
y = data['cls']  # Labels (Spam/Ham)

# Step 3: Perform PCA to reduce the dimensionality to 50
pca = PCA(n_components=50)
X_pca = pca.fit_transform(X)

# Step 4: Split the data into training and testing sets (3500 train, 500 test)
X_train, X_test, y_train, y_test = train_test_split(X_pca, y, train_size=3500, test_size=500, random_state=42)

# Step 5: Save the processed data into "train4_2.npz" and "test4_2.npz"
np.savez("train4_2.npz", X=X_train, y=y_train)
np.savez("test4_2.npz", X=X_test, y=y_test)

print("Data saved successfully to 'train4_2.npz' and 'test4_2.npz'")
