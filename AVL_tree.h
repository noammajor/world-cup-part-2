#ifndef AVL_TREE
#define AVL_TREE

#include "Team.h"
#include <stdio.h>
#include <math.h>
#include "Player.h"



template<class T, class Cond>
struct Node
{
    Node* father;
    Node* son_smaller;
    Node* son_larger;
    T data;
    int height;
    int size;
    T& get_data_Node();
};



template<class T, class Cond>
class AVL_Tree
{
    Node<T, Cond>* root;
    Node<T, Cond>* higher_data;
    int size;

public:
    AVL_Tree(): root(nullptr), higher_data(nullptr), size(0) {}

    AVL_Tree(Node<T, Cond>*  root, int size): root(root), higher_data(nullptr), size(size){}

    AVL_Tree<T, Cond> &operator=(const AVL_Tree<T, Cond> &tree) = delete;

    AVL_Tree<T, Cond>(const AVL_Tree<T, Cond> &tree) = delete;

    ~AVL_Tree();

    void postorderDelete_nodes(Node<T,Cond>* p);

    void postorderDelete_data(Node<T,Cond>* p);

    int height(Node<T, Cond> *t);

    int bf(Node<T, Cond> *t);

    template<class S>
    Node<T, Cond>* search(const S data);

    Node<T, Cond>* rotate_LL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RR(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_LR(Node<T, Cond>* t);

    bool insert_to_tree(const T& data);

    Node<T, Cond>* insert(Node<T, Cond>* t,const T& data);

    Node<T, Cond>* fix_balance (Node<T, Cond>* t);

    template<class S>
    bool remove (S num);

    void set_root();

    bool isLeaf (Node<T, Cond>* node);

    void remove_leaf (Node<T, Cond>* ptr);

    void remove_half_leaf (Node<T, Cond>* ptr);

    void fix_height (Node<T, Cond>* node);

    T& get_data(Node<T, Cond>* node) const;

    Node<T, Cond>* get_root() const;

    T& get_higher() const;

    int get_size() const;

    void Highest_setting();

};

template<class T, class Cond>
T& Node<T, Cond>::get_data_Node()
{
    return data;
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::get_size() const
{
    return size;
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::height(Node<T, Cond>* t)
{
    if (t == nullptr)
        return -1;
    else
    {
        int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
        int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
        return s_height > l_height ? s_height + 1 : l_height + 1;
    }
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::bf(Node<T, Cond> *t)
{
    int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
    int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
    return s_height - l_height;
}

template<class T, class Cond>
template<class S>
Node<T, Cond>* AVL_Tree<T, Cond>::search(const S data)
{
    Cond is_bigger;
    if (root == nullptr)
        return nullptr;
    Node<T, Cond>* t= root;
    while(t != nullptr)
    {
        if(is_bigger(data, t->data))
        {
            t = t->son_larger;
        }
        else if(is_bigger(t->data, data))
        {
            t = t->son_smaller;
        }
        else
        {
            return t;
        }
    }
    return nullptr;
}

 template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_RR(Node<T, Cond>* t)
{
    Cond is_bigger;
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_larger;
    temp1->son_larger = temp2->son_smaller;
    if (temp1->son_larger)
        temp1->son_larger->father = temp1;
    temp2->son_smaller = temp1;
    temp2->father = temp1->father;
    if (temp1->father)
    {
        if (is_bigger(temp1->father->data, temp1->data))
            temp1->father->son_smaller = temp2;
        else
            temp1->father->son_larger = temp2;
    }
    temp1->father = temp2;//father changes
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    return temp2;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_RL(Node<T, Cond>* t)
{
    Cond is_bigger;
    Node<T, Cond> *temp1 = t;  //points to A
    Node<T, Cond> *temp2 = t->son_larger;  //points to B
    Node<T, Cond> *temp3 = t->son_larger->son_smaller;  //points to C
    temp1->son_larger = temp3->son_smaller;  //right side of A point to left of C
    if (temp3->son_smaller)
        temp3->son_smaller->father = temp1;  //right side of C points to new father A
    temp2->son_smaller = temp3->son_larger;  //left side of B points to right side of C
    if (temp2->son_smaller)
        temp2->son_smaller->father = temp2;  //right side of C points to new father B
    temp3->son_smaller = temp1;  //left side C points to A
    temp3->son_larger = temp2;  //right side C points to B
    if (temp1->father)
    {
        if (is_bigger(temp1->father->data, temp1->data))
            temp1->father->son_smaller = temp3;
        else
            temp1->father->son_larger = temp3;
    }
    temp3->father = t->father;  //C points to A's father (C's father pointer)
    temp1->father = temp3;  //A points to father C
    temp2->father = temp3;  //B points to father C
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    temp3->height = height(temp3);
    return temp3;  // return new C to be t.
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_LR(Node<T, Cond>* t)
{
    Cond is_bigger;
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_smaller;
    Node<T, Cond> *temp3 = t->son_smaller->son_larger;
    temp1->son_smaller = temp3->son_larger;
    if (temp3->son_larger)
        temp3->son_larger->father = temp1;
    temp2->son_larger = temp3->son_smaller;
    if (temp2->son_larger)
        temp2->son_larger->father = temp2;
    temp3->son_larger = temp1;
    temp3->son_smaller = temp2;
    if (temp1->father)
    {
        if (is_bigger(temp1->father->data, temp1->data))
            temp1->father->son_smaller = temp3;
        else
            temp1->father->son_larger = temp3;
    }
    temp3->father = temp1->father;
    temp1->father = temp3;
    temp2->father = temp3;
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    temp3->height = height(temp3);
    return temp3;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_LL(Node<T, Cond>* t)
{
    Cond is_bigger;
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_smaller;
    temp1->son_smaller = temp2->son_larger;
    if (temp1->son_smaller)
        temp1->son_smaller->father = temp1;
    temp2->son_larger = temp1;
    temp2->father = temp1->father;
    if (temp1->father)
    {
        if (is_bigger(temp1->father->data, temp1->data))
            temp1->father->son_smaller = temp2;
        else
            temp1->father->son_larger = temp2;
    }
    temp1->father = temp2;
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    return temp2;
}

template<class T, class Cond>
bool AVL_Tree<T, Cond>::insert_to_tree(const T& data)
{
    Node<T, Cond>* ptr = insert(root, data);
    if (ptr != nullptr)
    {
        root = ptr;
        ptr->father = nullptr;
        size++;
        this->Highest_setting();
        return true;
    }
    return false;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::insert(Node<T, Cond>* t,const T& data)
{
    Cond is_bigger;
    if (t == nullptr)
    {
        Node<T, Cond>* base = new(Node<T, Cond>);
        base->data = data;
        base->son_larger = nullptr;
        base->son_smaller = nullptr;
        base->father = nullptr;
        base->height = 0;
        base->size = 1;
        if (!root)
            higher_data = base;
        return base;
    }
    else
    {
        if (is_bigger(data, t->data))
        {
            Node<T, Cond>* temp = insert(t->son_larger, data);
            if (temp == nullptr)
                return nullptr;
            t->son_larger = temp;
            temp->father = t;
            t->size++;
        }
        else if (is_bigger(t->data, data))
        {
            Node<T, Cond>* temp = insert(t->son_smaller, data);
            if (temp == nullptr)
                return nullptr;
            t->son_smaller = temp;
            temp->father = t;
            t->size++;
        }
        else
        {
            return nullptr;
        }
        t = fix_balance(t);
        return t;
    }
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::fix_balance (Node<T, Cond>* t)
{
    if (bf(t) == 2 && bf(t->son_smaller) >= 0)
    {
        t = rotate_LL(t);
    }
    else if (bf(t) == 2 && bf(t->son_smaller) < 0) {
        t = rotate_LR(t);
    }
    else if (bf(t) == -2 && bf(t->son_larger) <= 0) {
        t = rotate_RR(t);
    }
    else if (bf(t) == -2 && bf(t->son_larger) == 1) {
        t = rotate_RL(t);
    }
    else
        t->height = height(t);
    return t;
}

template<class T, class Cond>
template<class S>
bool AVL_Tree<T, Cond>::remove (S num)
{
    Cond is_bigger;
    Node<T, Cond> *ptr = search(num);
    if (ptr == nullptr)
        return false;
    Node<T, Cond>* ptr_father = ptr->father;
    if (isLeaf(ptr))
    {
        remove_leaf(ptr);
    }
    else if (!ptr->son_larger || !ptr->son_smaller)
    {
        remove_half_leaf(ptr);
    }
    else
    {
        Node<T, Cond> *temp1 = ptr->son_larger;
        Node<T, Cond> *temp2 = temp1->son_smaller;
        if (!temp1->son_smaller)
        {
            if (ptr->father && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp1;
            else if (ptr->father)
                ptr->father->son_larger = temp1;
            else
                root = temp1;
            temp1->father = ptr->father;
            temp1->son_smaller = ptr->son_smaller;
            ptr->son_smaller->father = temp1;
            ptr_father = temp1;  //pointer to fb
        }
        else
        {
            while (temp2->son_smaller)
                temp2 = temp2->son_smaller;
            temp2->father->son_smaller = temp2->son_larger;
            if (temp2->son_larger)
                temp2->son_larger->father = temp2->father;
            temp2->son_larger = temp1;
            temp1->father = temp2;
            ptr_father = temp2->father; //using the  same pointer for bf
            temp2->father = ptr->father;
            if (ptr->father && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp2;
            else if (ptr->father)
                ptr->father->son_larger = temp2;
            else
                root = temp2;
           temp2->son_smaller = ptr->son_smaller;
           ptr->son_smaller->father = temp2;
        }
    }
    delete ptr;
    fix_height(ptr_father);
    size--;
    this->set_root();
    this->Highest_setting();
    return true;
}

template<class T, class Cond>
bool AVL_Tree<T, Cond>::isLeaf (Node<T, Cond>* node)
{
    if (!node->son_larger && !node->son_smaller)
        return true;
    return false;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::remove_leaf (Node<T, Cond>* ptr) {
    Cond is_bigger;
    if (ptr->father)
    {
        if (is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = nullptr;
        else
            ptr->father->son_larger = nullptr;
    }
    else
    {
       root = nullptr;
    }
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::remove_half_leaf (Node<T, Cond>* ptr)
{
    Cond is_bigger;
    if (!ptr->son_larger)
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_smaller;
        else if (ptr->father)
            ptr->father->son_larger = ptr->son_smaller;
        ptr->son_smaller->father = ptr->father;
        if (!ptr->son_smaller->father)
            root = ptr->son_smaller;
    }
    else
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_larger;
        else  if (ptr->father)
            ptr->father->son_larger = ptr->son_larger;
        ptr->son_larger->father = ptr->father;
        if (!ptr->son_larger->father)
            root = ptr->son_larger;
    }
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::fix_height (Node<T, Cond>* node)
{
    if (!node)
        return;
    int prev_height = node->height;
    node = fix_balance(node);
    if (prev_height != node->height)
    {
        node = node->father;
        fix_height(node);
    }
}

template<class T, class Cond>
T& AVL_Tree<T, Cond>::get_data(Node<T, Cond>* node) const
{
    return node->data;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::get_root() const
{
    return root;
}

template<class T, class Cond>
T& AVL_Tree<T, Cond>::get_higher() const
{
    return higher_data->data;
}

template<class T, class Cond>
void AVL_Tree<T,Cond>::postorderDelete_nodes(Node<T,Cond>* p)
{

    if (p == nullptr)
        return;
    postorderDelete_nodes(p->son_smaller);
    postorderDelete_nodes(p->son_larger);
    delete p;
}

template<class T, class Cond>
void AVL_Tree<T,Cond>::postorderDelete_data(Node<T,Cond>* p)
{
    if (p == nullptr)
        return;
    postorderDelete_data(p->son_smaller);
    postorderDelete_data(p->son_larger);
    if (p->data)
        delete p->data;
}

template<class T, class Cond>
AVL_Tree<T,Cond>::~AVL_Tree()
{
    postorderDelete_nodes(root);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::set_root()
{
    Node<T,Cond>* temp = this->get_root();
    if(temp == nullptr)
        return;
    while(temp->father)
    {
        temp = temp->father;
    }
    root = temp;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>:: Highest_setting()
{
    Node<T,Cond>* temp = this->get_root();
    if(temp == nullptr)
    {
        higher_data = nullptr;
        return;
    }
    while(temp->son_larger != nullptr)
    {
        temp = temp->son_larger;
    }
    higher_data = temp;
}


#endif //AVL_TREE