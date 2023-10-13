#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode{
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode *createNode(int value, TreeNode* left, TreeNode* right) {
    TreeNode* newnode = calloc(1,sizeof(TreeNode));
    newnode->value = value;
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

void printTabs(int numtabs) {
    for (int i = 0; i < numtabs; i++) {
        printf("\t");
    }
}

void printTreeRecursive(TreeNode* root, int level) {
    if (root == NULL) {
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    printTabs(level);
    printf("value = %d\n", root->value);

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level + 1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level + 1);

    printTabs(level);
    printf("Done\n");
}

void printTree(TreeNode* root) {
    printTreeRecursive(root, 0);
}

void insertNode(TreeNode** node, int value) {
    TreeNode *node_pointer = *node;
    if (node_pointer == NULL) {
        *node = createNode(value, NULL, NULL);
        return;
    }
    if (node_pointer->value == value) {
        printf("value %d has been insert into the tree.\n", value);
        return;
    }
    if (value < node_pointer->value) {
        return insertNode(&(node_pointer->left), value);
    }
    if (value > node_pointer->value) {
        return insertNode(&(node_pointer->right), value);
    }
}

bool findNode(TreeNode* node, int value) {
    if (node == NULL) {
        return false;
    }
    if (value < node->value) {
        return findNode(node->left, value);
    }
    else if (value > node->value) {
        return findNode(node->right, value);
    }
    else {
        // node->value == value
        return true;
    }
}

TreeNode* deleteNode(TreeNode* node, int value) {
    
    if (node == NULL) {
        printf("value %d not found in the tree.\n", value);
        return node;
    }

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
        return node;
    }
    else if (value > node->value) {
        node->right = deleteNode(node->right, value);
        return node;
    }

    //found the target node, then...

    TreeNode* tmp = calloc(1, sizeof(TreeNode));
    // left or right or both empty:
    if (node->left == NULL) {
        tmp = node->right;
        free(node);
        return tmp;
    }
    else if (node->right == NULL) {
        tmp = node->left;
        free(node);
        return tmp;
    }

    //left and right both exist then...

    //we can choose largest number(most right) in left side, 
    //or smallest number(most left) in the right side.
    TreeNode* parent = node, * child = node->right;
    while (child->right!= NULL) {
        parent = child;
        child = child->left;
    }

    if (parent == node) {
        parent->right = child->right;
    }
    else {
        parent->left = child->right;
    }

    node->value = child->value;

    return node;
}

int main()
{
    TreeNode* root = NULL;

    int node[] = { 50,30,70,20,40,60,80,15,25,35,45,55,65,75,85 };
    int node_num = 15;
    for (int i = 0; i < node_num; i++)
    {
        insertNode(&root, node[i]);
    }

    printTree(root);

    int target[] = { 25,85,60,50,30,10 };
    int target_num = 6;
    for (int i = 0; i < target_num; i++)
    {
        if (findNode(root, target[i])) {
            printf("value %d found\n", target[i]);
        }
        else {
            printf("value %d not found\n", target[i]);
        }
        
    }

    root = deleteNode(root, 50);
    

    return 0;
}
