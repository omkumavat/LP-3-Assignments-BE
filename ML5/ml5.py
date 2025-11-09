# Assignment No. B5 - K-Means Clustering
# Aim: Implement K-Means clustering on sales_data_sample.csv and use Elbow Method

import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

# Step 1: Load dataset
df = pd.read_csv('sales_data_sample.csv', encoding='unicode_escape')
print("Dataset Loaded Successfully!")
print(df.head())

# Step 2: Select numerical features for clustering
num_features = ['SALES', 'QUANTITYORDERED', 'PRICEEACH']
data = df[num_features]

# Step 3: Normalize the data
scaler = StandardScaler()
scaled_data = scaler.fit_transform(data)

# Step 4: Determine optimal number of clusters using Elbow Method
wcss = []  # Within-Cluster Sum of Squares
for k in range(1, 11):
    kmeans = KMeans(n_clusters=k, init='k-means++', random_state=42)
    kmeans.fit(scaled_data)
    wcss.append(kmeans.inertia_)  # inertia_ = WCSS

# Plot Elbow Curve
plt.figure(figsize=(8, 5))
plt.plot(range(1, 11), wcss, marker='o', linestyle='--', color='b')
plt.title('Elbow Method for Optimal k')
plt.xlabel('Number of Clusters (k)')
plt.ylabel('WCSS')
plt.grid(True)
plt.show()

# Step 5: From the plot, suppose optimal k = 3
k_optimal = 3
kmeans = KMeans(n_clusters=k_optimal, init='k-means++', random_state=42)
df['Cluster'] = kmeans.fit_predict(scaled_data)

# Step 6: Visualize Clusters (for 2D visualization using first 2 features)
plt.figure(figsize=(8, 6))
plt.scatter(scaled_data[:, 0], scaled_data[:, 1],
            c=df['Cluster'], cmap='rainbow', s=50)
plt.title('Customer Segmentation using K-Means')
plt.xlabel('SALES (Standardized)')
plt.ylabel('QUANTITYORDERED (Standardized)')
plt.show()

# Step 7: Display cluster centers and sample output
print("\nCluster Centers (in standardized units):")
print(kmeans.cluster_centers_)

print("\nSample of Clustered Data:")
print(df[['SALES', 'QUANTITYORDERED', 'PRICEEACH', 'Cluster']].head(10))
