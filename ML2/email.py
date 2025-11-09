import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

data = pd.read_csv("emails.csv")

print(data.shape)
print(data.head())

# Separate features and target
X = data.drop(columns=['Email No.', 'Prediction'])
y = data['Prediction']

# Split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Train KNN
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
knn_pred = knn.predict(X_test)

# Train SVM
svm = SVC(kernel='rbf', class_weight='balanced')
svm.fit(X_train, y_train)
svm_pred = svm.predict(X_test)

# Evaluate models
def evaluate(pred, name):
    print(f"\n{name} Results:")
    print("Accuracy :", accuracy_score(y_test, pred))
    print("Precision:", precision_score(y_test, pred, zero_division=0))
    print("Recall   :", recall_score(y_test, pred, zero_division=0))
    print("F1 Score :", f1_score(y_test, pred, zero_division=0))
    print("Confusion Matrix:\n", confusion_matrix(y_test, pred))

evaluate(knn_pred, "KNN")
evaluate(svm_pred, "SVM")
