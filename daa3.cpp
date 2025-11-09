#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int value;
};

// ======================================================
// Recursive Dynamic Programming (Top-Down with Memoization)
// ======================================================

int knapsackRecDP(int i, int W, vector<Item>& items, vector<vector<int>>& memo) {
    // Base condition
    if (i == 0 || W == 0)
        return 0;

    // Check memoization table
    if (memo[i][W] != -1)
        return memo[i][W];

    // If item weight is more than current capacity, skip it
    if (items[i - 1].weight > W)
        memo[i][W] = knapsackRecDP(i - 1, W, items, memo);
    else {
        int include = items[i - 1].value + knapsackRecDP(i - 1, W - items[i - 1].weight, items, memo);
        int exclude = knapsackRecDP(i - 1, W, items, memo);
        memo[i][W] = max(include, exclude);
    }

    return memo[i][W];
}

// ======================================================
// Recursive Branch and Bound
// ======================================================

struct Node {
    int level;
    int profit;
    int weight;
    float bound;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

float calcBound(Node u, int n, int W, vector<Item>& arr) {
    if (u.weight >= W)
        return 0;

    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while ((j < n) && (totweight + arr[j].weight <= W)) {
        totweight += arr[j].weight;
        profit_bound += arr[j].value;
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * ((float)arr[j].value / arr[j].weight);

    return profit_bound;
}

// Recursive Branch & Bound
void knapsackBnBRec(int level, int profit, int weight, int& maxProfit, int n, int W, vector<Item>& arr) {
    if (weight > W)
        return;

    if (profit > maxProfit)
        maxProfit = profit;

    if (level == n)
        return;

    Node u;
    u.level = level;
    u.profit = profit;
    u.weight = weight;
    u.bound = calcBound(u, n, W, arr);

    // Include next item
    knapsackBnBRec(level + 1,
                   profit + arr[level].value,
                   weight + arr[level].weight,
                   maxProfit, n, W, arr);

    // Exclude next item
    knapsackBnBRec(level + 1,
                   profit,
                   weight,
                   maxProfit, n, W, arr);
}

// ======================================================
// MAIN FUNCTION - MENU
// ======================================================
int main() {
    int n, W, choice;
    cout << "---------------------------------------\n";
    cout << "   0-1 Knapsack Problem (Recursive DP & BnB)\n";
    cout << "---------------------------------------\n";

    cout << "Enter number of items: ";
    cin >> n;
    vector<Item> items(n);

    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight value): ";
        cin >> items[i].weight >> items[i].value;
    }

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    do {
        cout << "\n==============================\n";
        cout << "       MENU\n";
        cout << "==============================\n";
        cout << "1. Solve using Recursive Dynamic Programming (Memoization)\n";
        cout << "2. Solve using Recursive Branch and Bound\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- Recursive Dynamic Programming Method ---\n";
                vector<vector<int>> memo(n + 1, vector<int>(W + 1, -1));
                int maxVal = knapsackRecDP(n, W, items, memo);
                cout << "\nMaximum value in Knapsack = " << maxVal << endl;
                break;
            }
            case 2: {
                cout << "\n--- Recursive Branch and Bound Method ---\n";
                sort(items.begin(), items.end(), cmp);
                int maxProfit = 0;
                knapsackBnBRec(0, 0, 0, maxProfit, n, W, items);
                cout << "\nMaximum value in Knapsack = " << maxProfit << endl;
                break;
            }
            case 3:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
