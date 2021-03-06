//============================================================================
// Name        : a3_tbst.cpp
// Author      : Shreyash Halge
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : Create an inordered threaded binary tree and perform inorder and preorder traversals. Analyze time and space complexity of the algorithm.
//============================================================================

#include <iostream>
using namespace std;

class Node
{ // node declaration
public:
    int data;
    Node *left, *right;
    bool leftTh, rightTh;
};
class ThreadedBinaryTree
{
    Node *root;

public:
    ThreadedBinaryTree()
    { // constructor to initialize the variables
        root = new Node();
        root->right = root->left = root;
        root->leftTh = true;
        root->data = INT_MAX;
    }

    void makeEmpty()
    { // clear tree
        root = new Node();
        root->right = root->left = root;
        root->leftTh = true;
        root->data = INT_MAX;
    }

    void insert(int key)
    {
        Node *p = root;
        for (;;)
        {
            if (p->data < key)
            { // move to right thread
                if (p->rightTh)
                    break;
                p = p->right;
            }
            else if (p->data > key)
            { // move to left thread
                if (p->leftTh)
                    break;
                p = p->left;
            }
            else
            {
                return;
            }
        }

        Node *temp = new Node();
        temp->data = key;
        temp->rightTh = temp->leftTh = true;

        if (p->data < key)
        {
            temp->right = p->right;
            temp->left = p;
            p->right = temp;
            p->rightTh = false;
        }
        else
        {
            temp->right = p;
            temp->left = p->left;
            p->left = temp;
            p->leftTh = false;
        }
    }

    bool search(int key)
    {
        Node *temp = root->left;
        for (;;)
        {
            if (temp->data < key)
            {
                // search in left thread
                if (temp->rightTh)
                    return false;
                temp = temp->right;
            }
            else if (temp->data > key)
            {
                // search in right thread
                if (temp->leftTh)
                    return false;
                temp = temp->left;
            }
            else
            {
                return true;
            }
        }
    }

    void Delete(int key)
    {
        Node *dest = root->left, *p = root;
        for (;;)
        { // find Node and its parent.
            if (dest->data < key)
            {
                if (dest->rightTh)
                    return;
                p = dest;
                dest = dest->right;
            }
            else if (dest->data > key)
            {
                if (dest->leftTh)
                    return;
                p = dest;
                dest = dest->left;
            }
            else
            {
                break;
            }
        }
        Node *target = dest;
        if (!dest->rightTh && !dest->leftTh)
        {
            p = dest;            // has two children
            target = dest->left; // largest node at left child
            while (!target->rightTh)
            {
                p = target;
                target = target->right;
            }
            dest->data = target->data; // replace mode
        }
        if (p->data >= target->data)
        { // only left child
            if (target->rightTh && target->leftTh)
            {
                p->left = target->left;
                p->leftTh = true;
            }
            else if (target->rightTh)
            {
                Node *largest = target->left;
                while (!largest->rightTh)
                {
                    largest = largest->right;
                }
                largest->right = p;
                p->left = target->left;
            }
            else
            {
                Node *smallest = target->right;
                while (!smallest->leftTh)
                {
                    smallest = smallest->left;
                }
                smallest->left = target->left;
                p->left = target->right;
            }
        }
        else
        { // only right child
            if (target->rightTh && target->leftTh)
            {
                p->right = target->right;
                p->rightTh = true;
            }
            else if (target->rightTh)
            {
                Node *largest = target->left;
                while (!largest->rightTh)
                {
                    largest = largest->right;
                }
                largest->right = target->right;
                p->right = target->left;
            }
            else
            {
                Node *smallest = target->right;
                while (!smallest->leftTh)
                {
                    smallest = smallest->left;
                }
                smallest->left = p;
                p->right = target->right;
            }
        }
    }

    void inorder()
    {
        Node *temp = root, *p;
        for (;;)
        {
            p = temp;
            temp = temp->right;
            if (!p->rightTh)
            {
                while (!temp->leftTh)
                {
                    temp = temp->left;
                }
            }
            if (temp == root)
                break;
            cout << temp->data << " ";
        }
        cout << endl;
    }

    Node *pre_succ(Node *t)
    {
        if (t->leftTh == 0)
        {
            return t->left;
        }
        if (t->rightTh == 0)
        {
            return t->right;
        }
        while (t->rightTh == 1)
        {
            t = t->right;
        }
        return t->right;
    }

    void preorder()
    {
        Node *t;
        t = root->left;
        cout << "\n";
        while (t != root)
        {
            cout << " " << t->data;
            t = pre_succ(t);
        }
        cout << endl;
    }
};

int main()
{
    ThreadedBinaryTree tbt;
    cout << "ThreadedBinaryTree\n";
    char ch;
    int c, v;
    while (1)
    {
        cout << "\n----- MAIN MENU -----\n";
        cout << "1. Insert " << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Clear" << endl;
        cout << "5. Inorder display" << endl;
        cout << "6. Preorder display" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> c;
        // perform switch operation
        switch (c)
        {
        case 1:
            cout << "Enter integer element to insert: ";
            cin >> v;
            tbt.insert(v);
            break;
        case 2:
            cout << "Enter integer element to delete: ";
            cin >> v;
            tbt.Delete(v);
            break;
        case 3:
            cout << "Enter integer element to search: ";
            cin >> v;
            if (tbt.search(v) == true)
                cout << "Element " << v << " found in the tree" << endl;
            else
                cout << "Element " << v << " not found in the tree" << endl;
            break;
        case 4:
            cout << "\nTree Cleared\n";
            tbt.makeEmpty();
            break;
        case 5:
            cout << "Display tree: \n ";
            tbt.inorder();
            break;
        case 6:
            cout << "Preorder tree: ";
            tbt.preorder();
            break;
        case 7:
            exit(1);
        default:
            cout << "\nInvalid choice \n";
        }
    }
    cout << "\n";
    return 0;
}

/*
ThreadedBinaryTree

----- MAIN MENU -----
1. Insert 
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 1
Enter integer element to insert: 3

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 1
Enter integer element to insert: 5

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 1
Enter integer element to insert: 8

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 3
Enter integer element to search: 3
Element 3 found in the tree

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 1
Enter integer element to insert: 9

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 5
Display tree: 
 3 5 8 9

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 2
Enter integer element to delete: 8

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 5
Display tree: 
 3 5 9

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 3
Enter integer element to search: 9
Element 9 found in the tree

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 4

Tree Cleared

----- MAIN MENU -----
1. Insert
2. Delete
3. Search
4. Clear
5. Inorder display
6. Preorder display
7. Exit
Enter Your Choice: 7
*/
