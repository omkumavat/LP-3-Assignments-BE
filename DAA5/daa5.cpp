#include <iostream>
#include <vector>
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
using namespace std;

// ==========================
// FUNCTION DECLARATIONS
// ==========================
int partitionDeterministic(vector<int>& arr, int low, int high);
int partitionRandomized(vector<int>& arr, int low, int high);
void quickSortDeterministic(vector<int>& arr, int low, int high);
void quickSortRandomized(vector<int>& arr, int low, int high);
void printArray(const vector<int>& arr);

// ==========================
// DETERMINISTIC PARTITION
// ==========================
int partitionDeterministic(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// ==========================
// RANDOMIZED PARTITION
// ==========================
int partitionRandomized(vector<int>& arr, int low, int high) {
    int randomPivot = low + rand() % (high - low + 1); // choose random pivot
    swap(arr[randomPivot], arr[high]); // swap with last element
    return partitionDeterministic(arr, low, high); // now use deterministic partition
}

// ==========================
// DETERMINISTIC QUICK SORT
// ==========================
void quickSortDeterministic(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionDeterministic(arr, low, high);
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, pi + 1, high);
    }
}

// ==========================
// RANDOMIZED QUICK SORT
// ==========================
void quickSortRandomized(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandomized(arr, low, high);
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

// ==========================
// PRINT FUNCTION
// ==========================
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// ==========================
// MAIN FUNCTION
// ==========================
int main() {
    srand(time(0)); // seed for random pivot

    int n, choice;
    cout << "-----------------------------------------------\n";
    cout << "        QUICK SORT (Deterministic / Randomized)\n";
    cout << "-----------------------------------------------\n";

    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    do {
        cout << "\n==============================\n";
        cout << "           MENU\n";
        cout << "==============================\n";
        cout << "1. Deterministic Quick Sort\n";
        cout << "2. Randomized Quick Sort\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        vector<int> temp = arr; // copy original array to sort again

        switch (choice) {
            case 1:
                cout << "\n--- Deterministic Quick Sort ---\n";
                quickSortDeterministic(temp, 0, n - 1);
                cout << "Sorted array: ";
                printArray(temp);
                break;

            case 2:
                cout << "\n--- Randomized Quick Sort ---\n";
                quickSortRandomized(temp, 0, n - 1);
                cout << "Sorted array: ";
                printArray(temp);
                break;

            case 3:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
