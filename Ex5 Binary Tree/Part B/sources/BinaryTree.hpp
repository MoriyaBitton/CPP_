#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <stack>
#include <sstream>
#include <stdexcept>

namespace ariel
{
    template <class T>

    class BinaryTree
    {
        // ***********************
        // Class
        // ***********************

        enum TravelType
        {
            INORDER,
            PREORDER,
            POSTORDER
        }; // END - enum "TravelType"

        struct Node
        {
            T data;
            std::shared_ptr<Node> left = nullptr;
            std::shared_ptr<Node> right = nullptr;
            std::shared_ptr<Node> parent = nullptr;

            Node(T d) : data(d) {}
        }; // END - struct "Node"

        // ***********************
        // Membes
        // ***********************

        std::shared_ptr<Node> root = nullptr;

    public:
        // **********************************************************************
        // BinaryTree - Iterator
        // **********************************************************************

        class Iterator
        {
        private:
            std::shared_ptr<Node> _cur;
            TravelType _travel;

            void downToEndLeft()
            {
                while (_cur && _cur->left != nullptr)
                {
                    _cur = _cur->left;
                }
            }

            void downToEnd()
            {
                downToEndLeft();
                while (_cur && _cur->right != nullptr)
                {
                    _cur = _cur->right;
                    downToEndLeft();
                }
            }

            void upTill_LeftSon_Root()
            {
                while (_cur && _cur->parent && (_cur->parent->right == _cur))
                {
                    _cur = _cur->parent;
                }
            }

            void upTill_RightSon_Root()
            {
                while (_cur && _cur->parent && (_cur->parent->left == _cur))
                {
                    _cur = _cur->parent;
                }
            }

        public:
            Iterator(std::shared_ptr<Node> ptr = nullptr) : _cur(ptr) {}

            Iterator(std::shared_ptr<Node> ptr, TravelType travel) : _cur(ptr), _travel(travel)
            {
                if (_cur == nullptr)
                {
                    return;
                }
                if (travel == TravelType::INORDER)
                {
                    downToEndLeft();
                }
                else if (travel == TravelType::POSTORDER)
                {
                    downToEnd();
                }
                else
                { /*_cur = root*/
                }
            }

            /* reference to data that can by edited */
            T &operator*() { return _cur->data; }

            const T &operator*() const { return _cur->data; }

            const T *operator->() const { return &(_cur->data); }

            void nextInorder()
            {
                if (_cur->right)
                {
                    _cur = _cur->right;
                    downToEndLeft();
                }
                else
                {
                    if (!_cur->parent)
                    {
                        _cur = nullptr;
                    }
                    /* left son */
                    else if (_cur->parent->left == _cur)
                    {
                        _cur = _cur->parent;
                    }
                    else /* right son */
                    {
                        upTill_LeftSon_Root();
                        if (!_cur->parent)
                        {
                            _cur = nullptr;
                        }
                        else
                        {
                            _cur = _cur->parent;
                        }
                    }
                }
            }

            void nextPreorder()
            {
                if (_cur->left)
                {
                    _cur = _cur->left;
                }
                else if (_cur->right)
                {
                    _cur = _cur->right;
                }
                else /* Both son's are nullprt */
                {
                    if (!_cur->parent) /* root only */
                    {
                        _cur = nullptr;
                        return;
                    }
                    std::shared_ptr<Node> prev;
                    while (true)
                    {
                        prev = _cur;
                        _cur = _cur->parent;
                        if (!_cur)
                        {
                            return;
                        }
                        if (_cur->right && _cur->left == prev)
                        {
                            _cur = _cur->right;
                            return;
                        }
                    }
                }
            }

            void nextPostorder()
            {
                if (_cur->parent == nullptr)
                {
                    _cur = nullptr;
                    return;
                }
                /* _cur != root */
                if (_cur == _cur->parent->left) /* left son */
                {
                    if (_cur->parent->right != nullptr)
                    {
                        _cur = _cur->parent->right;
                        downToEnd();
                    }
                    else
                    {
                        _cur = _cur->parent;
                    }
                }
                /* right son */
                else
                {
                    _cur = _cur->parent;
                }
            }

            // ++i;
            Iterator &operator++()
            {
                if (_cur == nullptr)
                {
                    return *this;
                }

                switch (_travel)
                {
                case TravelType::INORDER: /* left -> root -> right */
                    nextInorder();
                    break;

                case TravelType::PREORDER: /* root -> left -> right */
                    nextPreorder();
                    break;

                case TravelType::POSTORDER: /* left -> right -> root */
                    nextPostorder();
                    break;
                }
                return *this;
            }

            // i++;
            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const Iterator &other) const { return _cur == other._cur; }

            bool operator!=(const Iterator &other) const { return !(*this == other); }
        }; // End - Iterator

        // **********************************************************************
        // BinaryTree - Constructors
        // **********************************************************************

        BinaryTree<T>() { root = nullptr; }

        //distractor
        ~BinaryTree<T>() {}

        void copyNodes(std::shared_ptr<Node> &thisRoot, const std::shared_ptr<Node> &sourceRoot)
        {
            if (sourceRoot == nullptr)
            {
                thisRoot = nullptr;
            }
            else
            {
                thisRoot = std::make_shared<Node>(sourceRoot->data);
                // thisRoot->parent = sourceRoot->parent;
                copyNodes(thisRoot->left, sourceRoot->left);
                copyNodes(thisRoot->right, sourceRoot->right);
                if (thisRoot->left)
                {
                    thisRoot->left->parent = thisRoot;
                }
                if (thisRoot->right)
                {
                    thisRoot->right->parent = thisRoot;
                }
            }
        }

        // Copy Constractor
        BinaryTree<T>(const BinaryTree<T> &other)
        {
            if (!other.root)
            {
                root = nullptr;
            }
            else
            {
                copyNodes(this->root, other.root);
            }
        }

        // Move constractor
        BinaryTree<T>(BinaryTree<T> &&other) noexcept { *this = std::move(other); }

        // **********************************************************************
        // BinaryTree - Operators
        // **********************************************************************

        // Operator = (copy)
        BinaryTree<T> &operator=(const BinaryTree<T> &other)
        {
            if (this != &other)
            {
                root = std::make_shared<Node>(other.root->data);
                copyNodes(this->root, other.root);
            }
            return *this;
        }

        // Operator Move =
        BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept
        {
            *this = std::move(other);
            return *this;
        }

        // **********************************************************************
        // BinaryTree - function
        // **********************************************************************

        BinaryTree<T> &add_root(const T &bt)
        {
            if (root)
            {
                root->data = bt;
            }
            else
            {
                std::shared_ptr<Node> newRoot = std::make_shared<Node>(bt);
                root = newRoot;
            }
            return *this;
        }

        std::shared_ptr<Node> find(std::shared_ptr<Node> tempRoot, const T &toFind)
        {
            std::shared_ptr<Node> curent = tempRoot;
            if (curent == nullptr)
            {
                return nullptr;
            }
            if (curent->data == toFind)
            {
                return curent;
            }
            std::shared_ptr<Node> left = find(curent->left, toFind);
            std::shared_ptr<Node> right = find(curent->right, toFind);
            if (left == nullptr)
            {
                return right;
            }
            return left;
        }

        BinaryTree<T> &add_left(const T &addTo, const T &addMeLeft)
        {
            if (root == nullptr)
            {
                throw std::range_error{"Binary Tree dosent exist"}; /* Change error type */
            }
            std::shared_ptr<Node> exist = find(root, addTo);
            if (exist != nullptr)
            {
                /* replace data */
                if (exist->left)
                {
                    exist->left->data = addMeLeft;
                }
                else
                {
                    std::shared_ptr<Node> newNode = std::make_shared<Node>(addMeLeft);
                    /* add new node */
                    exist->left = newNode;
                    newNode->parent = exist;
                }
                return *this;
            }
            // if "addTo" Node dosen't exsist --> Exception
            throw std::range_error{"Node dose not excist"};
        }

        BinaryTree<T> &add_right(const T &addTo, const T &addMeRight)
        {
            if (root == nullptr)
            {
                throw std::range_error{"Binary Tree dosent exist"}; /* Change error type */
            }
            std::shared_ptr<Node> exist = find(root, addTo);
            if (exist != nullptr)
            {
                /* replace data */
                if (exist->right)
                {
                    exist->right->data = addMeRight;
                }
                else
                {
                    std::shared_ptr<Node> newNode = std::make_shared<Node>(addMeRight);
                    /* add new node */
                    exist->right = newNode;
                    newNode->parent = exist;
                }
                return *this;
            }
            // if "addTo" Node dosen't exsist --> Exception
            throw std::range_error{"Node dose not excist"};
        }

        // PreOrder : (root -> left -> right)
        Iterator begin_preorder() { return Iterator(root, TravelType::PREORDER); }

        Iterator end_preorder() { return Iterator(); }

        // InOrder : (left -> root -> right)
        Iterator begin_inorder() { return Iterator(root, TravelType::INORDER); }

        Iterator end_inorder() { return Iterator(); }

        // PostOrder : (left -> right -> root)
        Iterator begin_postorder() { return Iterator(root, TravelType::POSTORDER); }

        Iterator end_postorder() { return Iterator(); }

        Iterator begin() { return begin_inorder(); }

        Iterator end() { return end_inorder(); }

        friend std::ostream &operator<<(std::ostream &os, BinaryTree<T> &bt)
        {
            os << "\n-----------------------------------\n---------   Binary Tree   ---------\n-----------------------------------\n";
            for (auto node : bt)
            {
                os << node << "  ";
            }
            os << std::endl;
            return os;
        }
    }; // END - BinaryTree

} // END - namespace ariel
