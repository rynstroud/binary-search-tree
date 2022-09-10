//
//  BST.hpp
//  Lab 08 BST
//
//  Created by C/R

#ifndef BST_h
#define BST_h
#include <string>
#include <iostream>
#include <sstream>
#include "BSTInterface.h"

// A binary tree node with data, left and right child pointers
template<typename T>
class BST : public BSTInterface<T>
{
private:
    template<typename K>
    struct Node
    {
        T data;
        Node<K>* left;
        Node<K>* right;
        Node(const K& d) : data(d), left(NULL) , right(NULL) {}
        Node(const K& d, Node<K>* l, Node<K>* r) : data(d), left(l), right(r) {}
        ~Node() {}
    };
    Node<T>* root;
    int siz;
    
public:
    BST(void) : root(NULL), siz(0) {}
    BST(const T& the_data, const BST<T>& left_child = BST(), const BST<T>& right_child = BST()) : root(new Node<T>(the_data, left_child.root, right_child.root)) {}
    ~BST(void) { clearTree(); }

    // Return true if node added to BST, else false
    bool addNode(const T& item)
    {
        std::cout << "Add node: size: " << siz << std::endl;
        return insert(this->root, item);
    }
    
    bool insert(Node<T>*& local_root, const T& item)
    {
        if (local_root == NULL)
        {
            local_root = new Node<T>(item);
            ++siz;
            return true;
        }
        else
        {
            if (item < local_root->data) return insert(local_root->left, item);
            else  if (local_root->data < item) return insert(local_root->right, item);
            else return false;
        }
    }

    // Return true if node removed from BST, else false
    bool removeNode(const T& item)
    {
        if (!find(item)) return false;
        return erase(this->root, item);
        return false;
    }
    
    bool erase(Node<T>*& local_root, const T& item)
    {
        if (local_root == NULL) return false;
        else
        {
            if (item < local_root->data) return erase(local_root->left, item);
            else if (local_root->data < item) return erase(local_root->right, item);
            else
            {
                Node<T>* old_root = local_root;
                if (local_root->left == NULL) local_root = local_root->right;
                else if (local_root->right == NULL) local_root = local_root->left;
                else
                {
                    replace_parent(old_root, old_root->left);
                }
                delete old_root;
                --siz;
                std::cout << "Remove node: size: " << siz << std::endl;
                return true;
            }
        }
    }
    
    void replace_parent(Node<T>*& old_root, Node<T>*& local_root)
    {
        if (local_root->right != NULL) replace_parent(old_root, local_root->right);
        else
        {
            old_root->data = local_root->data;
            old_root = local_root;
            local_root = local_root->left;
        }
    }

    // Return true if BST cleared of all nodes, else false
    bool clearTree()
    {
        while (root != NULL) removeNode(root->data);
        return true;
    }
    
    /*bool deleteTree(Node<T>*& local_root)
    {
        if ((local_root->left == NULL) && (local_root->right == NULL))
        {
            delete local_root;
            return true;
        }
        else if (local_root->right != NULL) deleteTree(local_root->right);
        else if (local_root->left != NULL) deleteTree(local_root->left);
        else throw std::string("Babe you got problems");
        return false;
    }*/
    
    bool find(const T& target) const
    {
        return find(this->root, target);
    }
    
    bool find(Node<T>* local_root, const T& target) const
    {
        if (local_root == NULL) return false;
        if (target < local_root->data) return find(local_root->left, target);
        else if (local_root->data < target) return find(local_root->right, target);
        else return true;
    }
    
    size_t size() { return siz; }

    /** Output nodes at a given level */
    bool outLevel(Node<T>* root, int level, std::stringstream& out) const
    {
       if (root == NULL) return false;
       if (level == 1)
       {
          out << " " << root->data;
          if ((root->left != NULL) || (root->right != NULL)) return true;
          return false;
       }
       if ((level == 2) && !root->left && root->right) out << " _";
       bool left = outLevel(root->left, level - 1, out);
       bool right = outLevel(root->right, level - 1, out);
       if ((level == 2) && root->left && !root->right) out << " _";
       return left || right;
    }
    
    // Return a level order traversal of a BST as a string
    std::string toString() const
    {
       std::stringstream out;
       if (root == NULL) out << " empty";
       else
       {
          int level = 0;
          do
          {
             out << std::endl << "  " << ++level << ":";
          } while (outLevel(root, level, out));
       }
       return out.str();
    }
    
    // Overrides the extraction operator
    friend std::ostream& operator<<(std::ostream& os, BST& myClass) { return os << myClass.toString(); }

};
#endif /* BST_h */
