//SCT221-0361/2022 CALEB KYALO
//SCT221-0640/2022 ALVIN MUTHOMI
//SCT221-0276/2022 BENJAMIN SANI

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for a node in the BST

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createBSTFromArray(int arr[], int start, int end);
Node* deleteNode(Node* root, int key);
int getHeight(Node* root);
int getNodeLevel(Node* root, int key, int level);
void printNodeLevelAndHeight(Node* root, int key);

// Function to create a BST from a sorted array
Node* createBSTFromArray(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = arr[mid];
    root->left = createBSTFromArray(arr, start, mid - 1);
    root->right = createBSTFromArray(arr, mid + 1, end);
    return root;
}

// Function to delete a node from BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of BST
int getHeight(Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

// Function to get the level of a node in BST
int getNodeLevel(Node* root, int key, int level) {
    if (root == NULL)
        return -1;
    if (root->data == key)
        return level;
    int downlevel = getNodeLevel(root->left, key, level + 1);
    if (downlevel != -1)
        return downlevel;
    downlevel = getNodeLevel(root->right, key, level + 1);
    return downlevel;
}

// Function to print the level and height of a node in BST
void printNodeLevelAndHeight(Node* root, int key) {
    int level = getNodeLevel(root, key, 1);
    int height = getHeight(root);
    printf("Level of Node %d: %d\n", key, level);
    printf("Height of BST: %d\n", height);
}

// Main function
int main() {
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = createBSTFromArray(arr, 0, n - 1);

    // Delete a node (for example, node with data 20)
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);

    // Print the height of the BST
    printf("Height of BST: %d\n", getHeight(root));

    // Print the level and height of any node in the BST (for example, node with data 30)
    int keyToPrint = 30;
    printNodeLevelAndHeight(root, keyToPrint);

    return 0;
}
