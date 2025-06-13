import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms
import numpy as np
import cv2
import os
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay

# PART 1: Implementing Original LeNet-5 Architecture
class LeNet5(nn.Module):
    def __init__(self):
        super(LeNet5, self).__init__()
        self.conv1 = nn.Conv2d(1, 6, kernel_size=5, stride=1, padding=2)  # 32x32 -> 28x28 -> 32x32 (padding=2)
        self.pool1 = nn.AvgPool2d(kernel_size=2, stride=2)  # 32x32 -> 16x16
        self.conv2 = nn.Conv2d(6, 16, kernel_size=5)  # 16x16 -> 12x12
        self.pool2 = nn.AvgPool2d(kernel_size=2, stride=2)  # 12x12 -> 6x6
        self.fc1 = nn.Linear(16 * 6 * 6, 120)  # Flattened size is 16 * 6 * 6 (after conv2 and pool2)
        self.fc2 = nn.Linear(120, 84)  # 120 -> 84
        self.fc3 = nn.Linear(84, 10)  # 84 -> 10

    def forward(self, x):
        x = F.tanh(self.conv1(x))  # Use Tanh activation as per original LeNet
        x = self.pool1(x)
        x = F.tanh(self.conv2(x))
        x = self.pool2(x)
        x = x.view(x.size(0), -1)  # Dynamically flatten the tensor

        x = F.tanh(self.fc1(x))
        x = F.tanh(self.fc2(x))
        x = self.fc3(x)  # No activation for final layer (CrossEntropyLoss applies softmax internally)
        return x

# PART 2: Modified LeNet-5 with Modern Techniques
class ModifiedLeNet5(nn.Module):
    def __init__(self):
        super(ModifiedLeNet5, self).__init__()
        self.conv1 = nn.Conv2d(1, 6, kernel_size=5, stride=1, padding=2)  # 32x32 -> 32x32
        self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)  # Max pooling
        self.conv2 = nn.Conv2d(6, 16, kernel_size=5)  # 16x16 -> 12x12
        self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)  # 12x12 -> 6x6
        self.fc1 = nn.Linear(16 * 6 * 6, 120)  # Flattened size is 16 * 6 * 6 (after conv2 and pool2)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
        self.dropout = nn.Dropout(0.5)  # Dropout layer for regularization

    def forward(self, x):
        x = F.relu(self.conv1(x))  # Use ReLU activation
        x = self.pool1(x)
        x = F.relu(self.conv2(x))
        x = self.pool2(x)
        x = x.view(x.size(0), -1)  # Dynamically flatten the tensor

        x = F.relu(self.fc1(x))
        x = self.dropout(x)  # Apply dropout
        x = F.relu(self.fc2(x))
        x = self.fc3(x)  # No activation for final layer (CrossEntropyLoss applies softmax internally)
        return x

# PART 1.1: Generating 7x12 Bitmaps from DIGIT Data
def generate_bitmap(image, size=(7, 12), threshold=128):
    """Resize image to target size and binarize it."""
    # Resize the image
    resized_image = cv2.resize(image, size, interpolation=cv2.INTER_AREA)
    # Convert to binary bitmap
    bitmap = (resized_image > threshold).astype(np.uint8)
    return bitmap

# Utility: Training and Testing Functions
def train(model, device, train_loader, optimizer, epoch, train_losses, train_accuracies):
    model.train()
    loss_function = nn.CrossEntropyLoss()
    correct = 0
    total_loss = 0

    print(f"Epoch {epoch} - Training in progress...")
    for batch_idx, (data, target) in enumerate(train_loader):
        data, target = data.to(device), target.to(device)
        optimizer.zero_grad()
        output = model(data)
        loss = loss_function(output, target)
        loss.backward()
        optimizer.step()

        total_loss += loss.item()
        pred = output.argmax(dim=1, keepdim=True)
        correct += pred.eq(target.view_as(pred)).sum().item()

    avg_loss = total_loss / len(train_loader.dataset)
    accuracy = 100. * correct / len(train_loader.dataset)
    train_losses.append(avg_loss)
    train_accuracies.append(accuracy)

def test(model, device, test_loader, test_losses, test_accuracies):
    model.eval()
    test_loss = 0
    correct = 0
    loss_function = nn.CrossEntropyLoss(reduction='sum')

    all_preds = []
    all_targets = []

    print("Testing in progress...")
    with torch.no_grad():
        for batch_idx, (data, target) in enumerate(test_loader):
            data, target = data.to(device), target.to(device)
            output = model(data)
            test_loss += loss_function(output, target).item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()

            all_preds.extend(pred.cpu().numpy())
            all_targets.extend(target.cpu().numpy())

    test_loss /= len(test_loader.dataset)
    accuracy = 100. * correct / len(test_loader.dataset)
    test_losses.append(test_loss)
    test_accuracies.append(accuracy)

    return all_preds, all_targets

# Prepare Dataset and DataLoader
def load_data():
    transform = transforms.Compose([
        transforms.Resize((32, 32)),
        transforms.ToTensor(),
        transforms.Normalize((0.5,), (0.5,))  # Normalize to [-1, 1]
    ])
    train_dataset = datasets.MNIST('./data', train=True, transform=transform)
    test_dataset = datasets.MNIST('./data', train=False, transform=transform)
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=64, shuffle=True)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=64, shuffle=False)
    return train_loader, test_loader

# Visualization and Metrics Functions
def plot_error_rates(train_accuracies, test_accuracies):
    epochs = range(1, len(train_accuracies) + 1)
    plt.figure(figsize=(10, 5))
    plt.plot(epochs, train_accuracies, label="Train Accuracy")
    plt.plot(epochs, test_accuracies, label="Test Accuracy")
    plt.xlabel("Epoch")
    plt.ylabel("Accuracy (%)")
    plt.title("Training and Test Accuracy")
    plt.legend()
    plt.grid()
    plt.show()

def confusion_matrix_analysis(all_preds, all_targets):
    cm = confusion_matrix(all_targets, all_preds)
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=range(10))
    disp.plot(cmap="viridis")
    plt.title("Confusion Matrix")
    plt.show()
    return cm

# Main Function
def main():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    train_loader, test_loader = load_data()

    train_losses, train_accuracies = [], []
    test_losses, test_accuracies = [], []

    # Load and evaluate original LeNet-5
    print("Loading and Evaluating Original LeNet-5...")
    model1 = LeNet5().to(device)
    model1_path = "original_lenet5.pth"
    if os.path.exists(model1_path):
        print("Loading pre-trained Original LeNet-5 model...")
        model1.load_state_dict(torch.load(model1_path,weights_only=True))
    else:
        optimizer1 = optim.SGD(model1.parameters(), lr=0.01, momentum=0.9)
        for epoch in range(1, 21):
            train(model1, device, train_loader, optimizer1, epoch, train_losses, train_accuracies)
        torch.save(model1.state_dict(), model1_path)
        print("Saved Original LeNet-5 model.")
    
    # Evaluate pre-trained Original LeNet-5
    all_preds, all_targets = test(model1, device, test_loader, test_losses, test_accuracies)
    print(f"Test Accuracy for Original LeNet-5: {test_accuracies[-1]:.2f}%")
    confusion_matrix_analysis(all_preds, all_targets)

    # Load and evaluate modified LeNet-5
    print("Loading and Evaluating Modified LeNet-5...")
    model2 = ModifiedLeNet5().to(device)
    model2_path = "modified_lenet5.pth"
    if os.path.exists(model2_path):
        print("Loading pre-trained Modified LeNet-5 model...")
        model2.load_state_dict(torch.load(model2_path,weights_only=True))
    else:
        optimizer2 = optim.Adam(model2.parameters(), lr=0.001)
        for epoch in range(1, 21):
            train(model2, device, train_loader, optimizer2, epoch, train_losses, train_accuracies)
        torch.save(model2.state_dict(), model2_path)
        print("Saved Modified LeNet-5 model.")
    
    # Evaluate pre-trained Modified LeNet-5
    all_preds, all_targets = test(model2, device, test_loader, test_losses, test_accuracies)
    print(f"Test Accuracy for Modified LeNet-5: {test_accuracies[-1]:.2f}%")
    confusion_matrix_analysis(all_preds, all_targets)

if __name__ == "__main__":
    main()
