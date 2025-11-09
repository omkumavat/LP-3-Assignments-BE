# ===============================
# Assignment No. B1
# Title: Uber Ride Price Prediction using Linear Regression and Random Forest Regression
# ===============================

# -------------------------------
# 1. Import Required Libraries
# -------------------------------
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import warnings
warnings.filterwarnings("ignore")

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score, mean_squared_error
import haversine as hs

# -------------------------------
# 2. Load Dataset
# -------------------------------
df = pd.read_csv("uber.csv")
print("Dataset Loaded Successfully!")
print(df.head())

# -------------------------------
# 3. Basic Info & Cleanup
# -------------------------------
print("\nDataset Info:")
print(df.info())

# Drop unnecessary columns
if 'Unnamed: 0' in df.columns:
    df.drop(['Unnamed: 0'], axis=1, inplace=True)
if 'key' in df.columns:
    df.drop(['key'], axis=1, inplace=True)

print("\nColumns after cleanup:", df.columns.tolist())

# -------------------------------
# 4. Handling Missing Values
# -------------------------------
print("\nMissing values before cleanup:\n", df.isnull().sum())

df['dropoff_latitude'].fillna(df['dropoff_latitude'].mean(), inplace=True)
df['dropoff_longitude'].fillna(df['dropoff_longitude'].median(), inplace=True)

print("\nMissing values after cleanup:\n", df.isnull().sum())

# -------------------------------
# 5. Convert Datetime & Extract Features
# -------------------------------
df['pickup_datetime'] = pd.to_datetime(df['pickup_datetime'], errors='coerce')

df = df.assign(
    hour=df.pickup_datetime.dt.hour,
    day=df.pickup_datetime.dt.day,
    month=df.pickup_datetime.dt.month,
    year=df.pickup_datetime.dt.year,
    dayofweek=df.pickup_datetime.dt.dayofweek
)
df.drop(['pickup_datetime'], axis=1, inplace=True)

print("\nDatetime features extracted successfully!")
print(df.head())

# -------------------------------
# 6. Handle Outliers (Using IQR)
# -------------------------------
def remove_outlier(df, col):
    Q1 = df[col].quantile(0.25)
    Q3 = df[col].quantile(0.75)
    IQR = Q3 - Q1
    lower = Q1 - 1.5 * IQR
    upper = Q3 + 1.5 * IQR
    df[col] = np.clip(df[col], lower, upper)
    return df

for c in df.select_dtypes(include=[np.number]).columns:
    df = remove_outlier(df, c)

print("\nOutliers treated successfully!")

# -------------------------------
# 7. Calculate Travel Distance using Haversine Formula
# -------------------------------
distances = []
for i in range(len(df)):
    loc1 = (df.iloc[i]['pickup_latitude'], df.iloc[i]['pickup_longitude'])
    loc2 = (df.iloc[i]['dropoff_latitude'], df.iloc[i]['dropoff_longitude'])
    dist = hs.haversine(loc1, loc2)
    distances.append(dist)

df['dist_travel_km'] = distances

# Limit unrealistic trips
df = df.loc[(df['dist_travel_km'] >= 1) & (df['dist_travel_km'] <= 130)]
print("\nDistance column added successfully!")

# -------------------------------
# 8. Correlation Analysis
# -------------------------------
plt.figure(figsize=(10,6))
sns.heatmap(df.corr(), annot=True, cmap="coolwarm")
plt.title("Correlation Heatmap")
plt.show()

# -------------------------------
# 9. Feature Selection
# -------------------------------
X = df[['pickup_longitude','pickup_latitude','dropoff_longitude','dropoff_latitude',
        'passenger_count','hour','day','month','year','dayofweek','dist_travel_km']]
y = df['fare_amount']

# -------------------------------
# 10. Train-Test Split
# -------------------------------
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
print("\nTraining and testing split done successfully!")
print("Training Size:", X_train.shape, "| Testing Size:", X_test.shape)

# -------------------------------
# 11. Linear Regression Model
# -------------------------------
lr = LinearRegression()
lr.fit(X_train, y_train)
y_pred_lr = lr.predict(X_test)

# Evaluation
r2_lr = r2_score(y_test, y_pred_lr)
mse_lr = mean_squared_error(y_test, y_pred_lr)
rmse_lr = np.sqrt(mse_lr)

print("\n📈 Linear Regression Performance:")
print(f"R² Score: {r2_lr:.3f}")
print(f"RMSE: {rmse_lr:.3f}")

# -------------------------------
# 12. Random Forest Regression Model
# -------------------------------
rf = RandomForestRegressor(n_estimators=100, random_state=42)
rf.fit(X_train, y_train)
y_pred_rf = rf.predict(X_test)

# Evaluation
r2_rf = r2_score(y_test, y_pred_rf)
mse_rf = mean_squared_error(y_test, y_pred_rf)
rmse_rf = np.sqrt(mse_rf)

print("\n🌲 Random Forest Regression Performance:")
print(f"R² Score: {r2_rf:.3f}")
print(f"RMSE: {rmse_rf:.3f}")

# -------------------------------
# 13. Model Comparison
# -------------------------------
results = pd.DataFrame({
    'Model': ['Linear Regression', 'Random Forest'],
    'R² Score': [r2_lr, r2_rf],
    'RMSE': [rmse_lr, rmse_rf]
})
print("\n==============================")
print("📊 Model Comparison")
print("==============================")
print(results)

# -------------------------------
# 14. Visualization of Predictions
# -------------------------------
plt.figure(figsize=(10,6))
plt.scatter(y_test, y_pred_lr, color='blue', alpha=0.4, label='Linear Regression')
plt.scatter(y_test, y_pred_rf, color='green', alpha=0.4, label='Random Forest')
plt.xlabel("Actual Fare")
plt.ylabel("Predicted Fare")
plt.title("Actual vs Predicted Fare Comparison")
plt.legend()
plt.show()
 