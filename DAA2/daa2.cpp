// ===============================================================
// Assignment No. 2
// Title: Huffman Coding Algorithm
// ===============================================================
//
// Objective:
// - Learn to implement Huffman Coding (Lossless Data Compression)
// - Understand construction of Huffman Tree
// - Generate Prefix-Free Codes based on character frequencies
// - Analyze time and space complexity
//
// ===============================================================

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// A Huffman Tree Node
// ---------------------------------------------------------------
struct Node
{
    char symbol;    // Character
    int freq;       // Frequency of the character
    Node *left;     // Left child
    Node *right;    // Right child

    Node(char s, int f, Node *l = nullptr, Node *r = nullptr)
    {
        symbol = s;
        freq = f;
        left = l;
        right = r;
    }
};

// ---------------------------------------------------------------
// Custom comparator for priority queue (min-heap)
// ---------------------------------------------------------------
struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

// ---------------------------------------------------------------
// Print Huffman Codes by traversing the tree
// ---------------------------------------------------------------
void printCodes(Node *root, string code)
{
    if (!root)
        return;

    // If leaf node, print the code
    if (!root->left && !root->right)
    {
        cout << root->symbol << " : " << code << endl;
        return;
    }

    // Traverse left -> add '0', right -> add '1'
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// ---------------------------------------------------------------
// Build Huffman Tree and print codes
// ---------------------------------------------------------------
void buildHuffmanTree(vector<char> &chars, vector<int> &freq)
{
    priority_queue<Node *, vector<Node *>, Compare> minHeap;

    // Step 1: Create leaf nodes and add to min heap
    for (int i = 0; i < chars.size(); i++)
        minHeap.push(new Node(chars[i], freq[i]));

    // Step 2: Repeat until heap contains only one node
    while (minHeap.size() > 1)
    {
        // Extract two smallest frequency nodes
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with combined frequency
        Node *newNode = new Node('\0', left->freq + right->freq, left, right);

        // Add new node to heap
        minHeap.push(newNode);
    }

    // Step 3: Root node is the final Huffman Tree
    Node *root = minHeap.top();

    cout << "\nHuffman Codes for given characters:\n";
    cout << "-----------------------------------\n";
    printCodes(root, "");
}

// ---------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------
int main()
{
    cout << "=============================================\n";
    cout << "Huffman Coding Implementation in C++\n";
    cout << "=============================================\n";

    // Given characters and their frequencies
    vector<char> chars = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    // Build and display Huffman Tree
    buildHuffmanTree(chars, freq);

    // -----------------------------------------------------------
    // Time Complexity: O(n log n)
    // Space Complexity: O(n)
    // -----------------------------------------------------------
    cout << "\nAnalysis:\n";
    cout << "Time Complexity  : O(n log n)\n";
    cout << "Space Complexity : O(n)\n";

    return 0;
}

// ===============================================================
// Output:
// f : 0
// c : 100
// d : 101
// a : 1100
// b : 1101
// e : 111
// ===============================================================
//
// Explanation:
// - The most frequent character gets the smallest code.
// - The codes are prefix-free (no code is prefix of another).
//
// ===============================================================
