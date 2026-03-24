#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

node *buildtree(vector<int> preorder, int &index)
{
    if (index >= preorder.size() || preorder[index] == -1)
    {
        index++;
        return NULL;
    }

    node *newnode = new node(preorder[index]);
    index++;

    newnode->left = buildtree(preorder, index);
    newnode->right = buildtree(preorder, index);

    return newnode;
}

// print the actual tree with the level order traversal
void printTree(node *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}
int height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return max(leftHeight, rightHeight) + 1;
}

// sum of nodes
int sumofnodes(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftSum = sumofnodes(root->left);
    int rightSum = sumofnodes(root->right);

    return leftSum + rightSum + root->data;
}

int diameterofthetree(node *root, int &diameter)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftHeight = diameterofthetree(root->left, diameter);
    int rightHeight = diameterofthetree(root->right, diameter);

    diameter = max(diameter, leftHeight + rightHeight);

    return max(leftHeight, rightHeight) + 1;
}

int countnodes(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftCount = countnodes(root->left);
    int rightCount = countnodes(root->right);

    return leftCount + rightCount + 1;
}

int main()
{
    vector<int> preorder = {
        50,
        30,
        20,
        10,
        -1, -1,
        25,
        -1, -1,
        40,
        35,
        -1, -1,
        45,
        -1, -1,
        70,
        60,
        55,
        -1, -1,
        65,
        -1, -1,
        80,
        75,
        -1, -1,
        90,
        -1, -1};
    int index = 0;
    node *root = buildtree(preorder, index);
    printTree(root);
    cout << "\nHeight of the tree: " << height(root) << endl;
    cout << "Number of nodes in the tree: " << countnodes(root) << endl;
    cout << "Sum of all nodes in the tree: " << sumofnodes(root) << endl;
    int diameter = 0;
    diameterofthetree(root, diameter);
    cout << "Diameter of the tree: " << diameter << endl;
    return 0;
}