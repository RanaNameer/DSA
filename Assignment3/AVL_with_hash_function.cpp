#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class AVL {
public:
    struct avl_node {
        string data;
        struct avl_node* left;
        struct avl_node* right;
        int height;
    };
    struct avl_node* root;

    int height(avl_node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    avl_node* findMin(avl_node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    avl_node* findMax(avl_node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    avl_node* singleRightRotate(avl_node* &node) {
        if (node->left!=NULL) {
            avl_node* u = node->left;
            node->left = u->right;
            u->right = node;
            node->height = max(height(node->left), height(node->right))+1;
            u->height = max(height(u->left), node->height)+1;
            return u;
        }
        return node;
    }

    avl_node* singleLeftRotate(avl_node* &node)
    {
        if (node->right != NULL) {
            avl_node* u = node->right;
            node->right = u->left;
            u->left = node;
            node->height = max(height(node->left), height(node->right)) + 1;
            u->height = max(height(node->right), node->height) + 1;
            return u;
        }
        return node;
    }

    avl_node* doubleLeftRotate(avl_node* &node)
    {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }

    avl_node* doubleRightRotate(avl_node* &node)
    {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }

    avl_node* insert(string x, avl_node* t)
    {
        if(t == NULL)
        {
            t = new avl_node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->data) //left left case
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t); //left right case
            }
        }
        else if(x > t->data)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->data) //right right case
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t); //right left case
            }
        }
        else if (x == t->data) {
            return t; //equal value nodes not allowed
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }
    //removing element from AVL tree
    avl_node* remove(string x, avl_node* t)
    {
        avl_node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

            // Searching for element
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);

            // Element found
            // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
            // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
                // right left case
            else
                return doubleLeftRotate(t);
        }
            // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
                // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int getBalance(avl_node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }
    //inorder traversal of AVL tree
    void inorder(avl_node* t, int index)
    {
        if(t == NULL)
            return;
        inorder(t->left,index);
        cout<<" <<---------------------<< "<<index<<" >>--------------------->> "<<endl;
        cout << t->data << endl;
        inorder(t->right,index);
    }
};

class Hashing {
    AVL* collection;
    int size;
public:
    //creating hash table of specified size
    Hashing(int Size) {
        this->size = Size;
        collection = new AVL[size]; //AVL type array
    }
    //hashing function: produces hash key/index
    int hashFunction(string name) {
        char letter = name[0];
        int bin = (int)letter;
        int arr[64];
        int a[64] = { 0 };
        int x = 0, i;
        for (i = 0; bin > 0; i++) {
            a[i] = bin % 2;
            bin /= 2;
        }
        int hashIndex = 0, p = 0;
        for (int i = x - 3; i < x; i++) {
            hashIndex += a[i] * pow(2, p++);
        }
        return hashIndex;
    }
    //returns height of AVL tree at a particular index
    int height(int val) {
        return collection[val].root->height;
    }
    //inserting name in hash table
    int insert(string name) {
        int hash = hashFunction(name);
        collection[hash].root = collection[hash].insert(name, collection[hash].root);
        return hash;
    }
    //removing name from hash table
    int remove(string name) {
        int hash = hashFunction(name);
        collection[hash].root = collection[hash].remove(name, collection[hash].root);
        return hash;
    }
    //displaying hash table
    void display() {
        for (int i = 0; i < 10; i++) {
            collection[i].inorder(collection[i].root,i);
        }
    }
    //options/modes of the program
    void menu() {
        cout<<"1. Insert a name."<<endl;
        cout<<"2. Delete/Remove a name."<<endl;
        cout<<"Display the names."<<endl;
        cout<<"Exit the program."<<endl;
    }
};

int main() {
    string arr[91]; //string array to store names of all students
    int index = 0;
    ifstream file; //for file reading
    string line;
    Hashing hash(8);

    file.open("C:/Users/User/Desktop/NamesToHash.txt");

    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, line);
            arr[index++] = line;
        }
        file.close();
    }

    int size = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        hash.insert(arr[i]);
    }

    int choice;
    cout<<"Select the operatioon you want to perform: "<<endl;
    hash.menu();
    cin>>choice;
    string name;
    int index1;

    while(true) {
        switch(choice) {
            case 1:
                getline(cin, name);
                index1 = hash.insert(name);
                cout<<"Inserted at index: "<<index1<<endl;
                hash.menu();
                cin>>choice;
                break;
            case 2:
                getline(cin, name);
                index1 = hash.remove(name);
                cout<<"Inserted at index: "<<index1<<endl;
                hash.menu();
                cin>>choice;
                break;
            case 3:
                hash.display();
                hash.menu();
                cin>>choice;
                break;
            case 4:
                break;
            default:
                cout<<"Choose a valid option."<<endl;
                hash.menu();
                cin>>choice;
                break;
        }
    }
}
