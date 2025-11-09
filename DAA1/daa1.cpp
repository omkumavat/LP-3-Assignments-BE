// ===============================================================
// Assignment No. 1
// Title: Recursive and Iterative Algorithms (Fibonacci Series)
// ===============================================================
//
// Objectives:
// 1. Learn to implement procedures and pass parameters.
// 2. Understand recursion and stack handling.
// 3. Implement recursive and iterative programs.
// 4. Analyze algorithm time and space complexity.
//
// ===============================================================

#include <iostream>
using namespace std;

// ---------------------------------------------------------------
// Recursive Fibonacci Function
// Time Complexity: O(2^n)
// Space Complexity: O(n) - due to function call stack
// ---------------------------------------------------------------
int recursiveFibonacci(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2));
}

// ---------------------------------------------------------------
// Iterative Fibonacci Function
// Time Complexity: O(n)
// Space Complexity: O(1)
// ---------------------------------------------------------------
int iterativeFibonacci(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;

    int a = 0, b = 1, c = 0;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ---------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------
int main()
{
    int n;

    cout << "=============================================\n";
    cout << "Recursive and Iterative Fibonacci Program\n";
    cout << "=============================================\n";

    cout << "Enter the value of n (nth Fibonacci term to compute): ";
    cin >> n;

    cout << "\n--- Recursive Approach ---" << endl;
    cout << "Fibonacci number (Recursive) of " << n << " is: " << recursiveFibonacci(n) << endl;

    cout << "\n--- Iterative Approach ---" << endl;
    cout << "Fibonacci number (Iterative) of " << n << " is: " << iterativeFibonacci(n) << endl;

    // -----------------------------------------------------------
    // Analysis Summary
    // -----------------------------------------------------------
    cout << "\n=============================================\n";
    cout << "Algorithm Analysis:\n";
    cout << "---------------------------------------------\n";
    cout << "Recursive Fibonacci:\n";
    cout << "  → Time Complexity: O(2^n)\n";
    cout << "  → Space Complexity: O(n)\n\n";
    cout << "Iterative Fibonacci:\n";
    cout << "  → Time Complexity: O(n)\n";
    cout << "  → Space Complexity: O(1)\n";
    cout << "=============================================\n";

    return 0;
}

// ---------------------------------------------------------------
// FAQ Section
// ---------------------------------------------------------------
//
// 1. What is Fibonacci series?
//    → A sequence of numbers where each term is the sum of the two preceding ones.
//
// 2. What is the logic of Fibonacci series?
//    → F(n) = F(n-1) + F(n-2) with F(0)=0 and F(1)=1.
//
// 3. Give example of Fibonacci series:
//    → 0, 1, 1, 2, 3, 5, 8, 13, 21...
//
// 4. What is recursion?
//    → A process where a function calls itself until a base condition is met.
//
// 5. What are the advantages of using functions?
//    → Code reusability, modularity, easy debugging, and better readability.
//
// 6. What data structure is used in recursive function of Fibonacci series?
//    → Stack (for storing function call information).
//
// 7. What is the complexity (space and time) of recursive & non-recursive Fibonacci?
//    → Recursive: Time O(2^n), Space O(n)
//    → Iterative: Time O(n), Space O(1)
//
// ===============================================================
