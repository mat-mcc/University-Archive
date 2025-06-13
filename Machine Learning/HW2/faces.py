import os
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def load_images_from_directory(folder, original_shape=(64, 64)):
    images = []
    supported_extensions = ('.png', '.jpg', '.jpeg', '.gif', 
                            '.sad', '.happy', '.centerlight', 
                            '.glasses', '.leftlight', '.noglasses', 
                            '.normal', '.rightlight', '.sleepy', 
                            '.surprised', '.wink')

    for filename in os.listdir(folder):
        if filename.endswith(supported_extensions):
            img_path = os.path.join(folder, filename)
            try:
                image = Image.open(img_path).convert('L')  # Convert to grayscale
                image = image.resize(original_shape)  # Resize to match the shape
                images.append(np.array(image).flatten())  # Flatten to vector
            except IOError as e:
                print(f"Could not open image {img_path}: {e}")
    return np.array(images)

def compute_covariance_matrix(X):
    return np.cov(X.T)

def visualize_eigenimages(eigenvectors, num_eigenvectors=10, original_shape=(64, 64), output_folder='eigen_images'):
    os.makedirs(output_folder, exist_ok=True)
    
    for i in range(num_eigenvectors):
        eigenimage = eigenvectors[:, i].reshape(original_shape)

        # Normalize using the provided formula
        eigenimage_normalized = (eigenimage - np.min(eigenimage)) / (np.max(eigenimage) - np.min(eigenimage)) * 256
        eigenimage_normalized = np.real(eigenimage_normalized).astype(np.uint8)  # Take real part and convert to uint8

        plt.imshow(eigenimage_normalized, cmap='gray')
        plt.axis('off')
        plt.title(f'Eigenimage {i + 1}')
        plt.savefig(f'{output_folder}/eigenimage_{i + 1}.png', bbox_inches='tight')
        plt.close()

    print("Eigenimages saved successfully.")

def main():
    # Load images from the current directory
    folder = '.' 
    images = load_images_from_directory(folder, original_shape=(64, 64))

    if len(images) == 0:
        print("No images loaded.")
        return

    # Calculate the mean image
    mean_image = np.mean(images, axis=0)

    # Compute the covariance matrix
    cov_matrix = compute_covariance_matrix(images)

    # Perform spectral decomposition
    eigenvalues, eigenvectors = np.linalg.eig(cov_matrix)
    sorted_indices = np.argsort(eigenvalues)[::-1]
    eigenvalues = eigenvalues[sorted_indices]
    eigenvectors = eigenvectors[:, sorted_indices]

    # Number of eigenvectors to visualize
    num_eigenvectors = 10
    top_eigenvectors = eigenvectors[:, :num_eigenvectors]

    # Create a directory to save the images
    output_folder = 'eigen_images'
    os.makedirs(output_folder, exist_ok=True)

    # Visualize each eigenvector as a grayscale image
    visualize_eigenimages(top_eigenvectors)

    # Load and process the test image
    test_image_path = 'subject01.happy'
    try:
        test_image = Image.open(test_image_path).convert('L')
        test_image = test_image.resize((64, 64))  # Resize to match training images
        test_image_vector = np.array(test_image).flatten()  # Flatten to vector
    except IOError:
        print(f"Could not open test image {test_image_path}")
        return

    # Test image approximation for different M values
    M_values = [2, 10, 100, 1000, 4000]
    approximations = {}

    for M in M_values:
        if M > len(eigenvectors):
            print(f"Warning: M = {M} exceeds the number of available eigenvectors.")
            continue
        
        E_M = eigenvectors[:, :M]  # Take the first M eigenvectors
        approximation = mean_image + E_M @ (E_M.T @ (test_image_vector - mean_image))
        approximations[M] = approximation.reshape(test_image.size[::-1])  # Reshape to original image dimensions

    # Display approximated images
    for M, approx_image in approximations.items():
        Image.fromarray(approx_image.astype(np.uint8)).show(title=f'Approximation with M={M}')

if __name__ == "__main__":
    main()
