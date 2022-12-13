#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Binary tree node structure. The first node within such a tree is the root.
struct binaryTreeNode{
    struct binaryTreeNode* left; //Left child node, represented by 0
    struct binaryTreeNode* right; //Right child node, represented by 1
    struct binaryTreeNode* root; //The root node of the binary tree or NULL if this node is root.
    void* value; //Value of the node
};
//Returns a properly initialised binary tree node
struct binaryTreeNode* nodeInit(void* value){
    struct binaryTreeNode* node = malloc(sizeof(struct binaryTreeNode));
    node->root = NULL;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
}
//Properly attaches a node to a binary tree as child to the parentNode. 
void mountNode(struct binaryTreeNode* parentNode, struct binaryTreeNode* node, struct binaryTreeNode** mountPoint){
    *mountPoint = node;
    if(parentNode->root == NULL){
        node->root = parentNode;
    }
    else{
        node->root = parentNode->root;
    }
}
//Returns a node located at the end of the provided binaryPath from root
//For example if we want to get the left child of the first left child binaryPath=00
struct binaryTreeNode* getNode(unsigned long binaryPath, struct binaryTreeNode* root){
    // Total number of digits
    unsigned digits;
    if(binaryPath == 0){
        digits = 1;
    }
    else{
        digits = log10(binaryPath) + 1; 
    }
    //Get the first digit of binaryPath
    unsigned digit = (int)(binaryPath / pow(10, digits - 1));
    //Get the correct binary tree node
    struct binaryTreeNode* node;
    switch (digit){
    case 0:
        node = root->left;
        break;
    case 1:
        node = root->right;
        break;
    default: //something went wrong
        return NULL;
        break;
    }
    if(digits == 1){ //If we have reached the end of the path we can return
        return node;
    }
    else if(node != NULL){ //else if we haven't retrieved a NULL value we can recursively continue
        unsigned i = pow(10, digits) * digit;
        return getNode(binaryPath - i, node);
    }
    else{ //We are probably trying to get a node that isnt in the tree so return NULL
        return NULL;
    }
}
struct binaryTreeNode* unMountNode(struct binaryTreeNode** mountPoint){
    struct binaryTreeNode* node = *mountPoint;
    *mountPoint = NULL;
    node->root = NULL;
    return node;
} 
int main(){
    struct binaryTreeNode* root = nodeInit("test");
    struct binaryTreeNode* left = nodeInit("left");
    mountNode(root, left, &root->left);
}