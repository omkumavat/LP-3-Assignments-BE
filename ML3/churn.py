# Assignment B3 - Neural Network Based Classifier
# Aim: Predict customer churn using Artificial Neural Network

# Step 1: Import libraries
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import accuracy_score, confusion_matrix
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout

# Step 2: Load dataset
data = pd.read_csv("Churn_Modelling.csv")  # dataset from Kaggle

# Step 3: Feature selection (remove unnecessary columns)
X = data.drop(['RowNumber', 'CustomerId', 'Surname', 'Exited'], axis=1)
y = data['Exited']

# Step 4: Encode categorical variables
X = pd.get_dummies(X, drop_first=True)

# Step 5: Split into train and test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Step 6: Normalize the data
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Step 7: Build the ANN model
model = Sequential()
model.add(Dense(units=64, activation='relu', input_dim=X_train.shape[1]))
model.add(Dropout(0.3))
model.add(Dense(units=32, activation='relu'))
model.add(Dense(units=1, activation='sigmoid'))  # binary classification

# Step 8: Compile the model
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Step 9: Train the model
model.fit(X_train, y_train, batch_size=32, epochs=25, verbose=1)

# Step 10: Make predictions
y_pred = model.predict(X_test)
y_pred = (y_pred > 0.5)

# Step 11: Evaluate
acc = accuracy_score(y_test, y_pred)
cm = confusion_matrix(y_test, y_pred)

# Step 12: Print results
print("\n=== Model Evaluation ===")
print("Accuracy:", round(acc * 100, 2), "%")
print("Confusion Matrix:\n", cm)
