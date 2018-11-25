#include<iostream>
using namespace std;

class AVL
{
    struct TreeNode
    {
        int value;
        TreeNode* left;
        TreeNode* right;
        int height;
    };

    TreeNode* root;

    void makeEmpty(TreeNode* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    TreeNode* insert(int x, TreeNode* t)
    {
        if(t == NULL)
        {
            t = new TreeNode;
            t->value = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->value)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->value)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->value)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->value)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    TreeNode* singleRightRotate(TreeNode* &t)
    {
        TreeNode* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    TreeNode* singleLeftRotate(TreeNode* &t)
    {
        TreeNode* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    TreeNode* doubleLeftRotate(TreeNode* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    TreeNode* doubleRightRotate(TreeNode* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    TreeNode* findMin(TreeNode* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    TreeNode* findMax(TreeNode* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    TreeNode* remove(int x, TreeNode* t)
    {
        TreeNode* temp;

        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(x < t->value)
            t->left = remove(x, t->left);
        else if(x > t->value)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->value = temp->value;
            t->right = remove(t->value, t->right);
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

        // If TreeNode is unbalanced
        // If left TreeNode is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right TreeNode is deleted, left case
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

    int height(TreeNode* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(TreeNode* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(TreeNode* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->value << " ";
        inorder(t->right);
    }

public:
    AVL()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }
};

int main()
{
    AVL t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.display();
    t.insert(10);
    t.display();
    t.insert(30);
    t.display();
    t.insert(5);
    t.display();
    t.insert(35);
    t.insert(67);
    t.insert(43);
    t.insert(21);
    t.insert(10);
    t.insert(89);
    t.insert(38);
    t.insert(69);
    t.display();
    t.remove(5);
    t.remove(35);
    t.remove(65);
    t.remove(89);
    t.remove(43);
    t.remove(88);
    t.remove(20);
    t.remove(38);
    t.display();
}
