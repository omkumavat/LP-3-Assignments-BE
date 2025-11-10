import pandas as pd
import numpy as np

ds = pd.read_csv("Churn_Modelling.csv")
ds.head()

# check for null values
ds.isna().sum()

# Remove attributes that are unique to the customer (attributes belonging to candidate keys)
ds.drop(["RowNumber", "CustomerId", "Surname"], axis=1, inplace=True)

# binary encoding for gender
ds.loc[ds["Gender"] == "Male", ["Gender"]] = 0
ds.loc[ds["Gender"] == "Female", ["Gender"]] = 1

# one hot enc. geography
ds = pd.get_dummies(ds, columns=["Geography"], dtype='int32')

def min_max_normalize(name):
    global ds
    ds[name] = ds[name].astype('float32')
    ds[name] = (ds[name] - ds[name].min()) / (ds[name].max() - ds[name].min())

cols = ["CreditScore", "Age", "Tenure", "Balance", "NumOfProducts", "HasCrCard", "EstimatedSalary"]
for col in cols:
    min_max_normalize(col)
    
from sklearn.model_selection import train_test_split 
X = ds.drop(["Exited"], axis=1).to_numpy().astype(np.float32) # features 

y = ds["Exited"].to_numpy() # labels

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

from sklearn.neural_network import MLPClassifier

clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(5, 2), random_state=1, max_iter=50)
clf.fit(X_train, y_train)

from sklearn.metrics import accuracy_score

pred_y = clf.predict(X_test)
print(f"Accuracy is {accuracy_score(y_test, pred_y)}")

from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

cm = confusion_matrix(y_test, pred_y)
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=clf.classes_)
disp.plot()
plt.show()