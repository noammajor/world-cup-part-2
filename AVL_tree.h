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

    AVL_Tree<T, Cond>* unite(AVL_Tree<T, Cond>* t2);

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

    void print_tree (int* const output);

    void array_tree (T* const output);

    void inorder_print (Node<T, Cond>* node, int* const output, int* i);

    void inorder_array (Node<T, Cond>* node, T* const output, int* i);

    int knockout_tree (int min, int max);

    void inorder_knockout (Node<T, Cond>* node, int* output, int min, int max, int* i, int* counter);

    void inorder_change (Node<T, Cond>* node, Team* t);

    T& get_data(Node<T, Cond>* node) const;

    Node<T, Cond>* get_root() const;

    T& get_higher() const;

    bool isSmallest(const Node<T,Cond>* t) const;

    Node<T,Cond>* set_closests_small(Node<T,Cond>* player) const;

    void merge (T* united, T* t1, int t1_size, T* t2, int t2_size);

    Node<T, Cond>* create_next(int index, int size, T* united_data, Node<T, Cond>* node);

    Node<T, Cond>* create_tree(int height);

    void inorder_assign(Node<T, Cond>* node, T* elements, int size, int* i);

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
        }
        else if (is_bigger(t->data, data))
        {
            Node<T, Cond>* temp = insert(t->son_smaller, data);
            if (temp == nullptr)
                return nullptr;
            t->son_smaller = temp;
            temp->father = t;
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
void AVL_Tree<T, Cond>::print_tree (int* const output)
{
    int index = 0;
    int* i = &index;
    inorder_print(root, output, i);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::array_tree (T* const output)
{
    int index = 0;
    int* i = &index;
    inorder_array(root, output, i);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_print (Node<T, Cond>* node,  int* const output, int* i)
{
    if (!node)
        return;
    inorder_print(node->son_smaller, output, i);
    output[(*i)++] = node->data->get_playerID();
    inorder_print(node->son_larger, output, i);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_array (Node<T, Cond>* node,  T* const output, int* i)
{
    if (!node)
        return;
    inorder_array(node->son_smaller, output, i);
    output[(*i)++] = node->data;
    inorder_array(node->son_larger, output, i);
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::knockout_tree (int min, int max)
{
    if (this->get_size() == 0)
        return 0;
    int* table = new int[2*this->get_size()];
    int index = 0;
    int* i = &index;
    int counter = 0;
    int* counter_p = &counter;
    inorder_knockout(root, table, min, max, i, counter_p);
    if (counter == 0)
    {
        delete[] table;
        return 0;
    }
    for (int k = 2 ; k < 2*counter ; k *= 2)
    {
        for (int j = 0 ; j < (2*counter - k) ; j += k)
        {
            table[j] = table[j + 1] > table[j + k + 1] ? table[j] : table[j + k];
            table[j + 1] += table[j + k + 1] + 3;
        }
    }
    int winner_id = table[0];
    delete[] table;
    return winner_id;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_knockout (Node<T, Cond>* node, int* output, int min, int max, int* i , int* counter)
{
    Cond is_bigger;
    if (!node)
        return;
    if (!(is_bigger(min,node->data)))
        inorder_knockout(node->son_smaller, output, min, max, i, counter);
    if (!is_bigger(min, node->data) && !is_bigger(node->data, max))
    {
        output[(*i)++] = node->data->get_ID();
        output[(*i)++] = node->data->tot_game_points();
        (*counter)++;
    }
    if(!is_bigger(node->data, max))
        inorder_knockout(node->son_larger, output, min, max, i, counter);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_change (Node<T, Cond>* node, Team* t)
{
    if (!node)
        return;
    inorder_change(node->son_smaller, t);
    node->data->change_team(t);
    inorder_change(node->son_larger, t);
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
bool AVL_Tree<T, Cond>::isSmallest(const Node<T,Cond>* t) const
{
    Node<T,Cond>* temp = root;
    while(temp->son_smaller != nullptr)
        temp = temp->son_smaller;
    if(t == temp)
        return true;
    return false;
}

template<class T, class Cond>
Node<T,Cond>* AVL_Tree<T, Cond>::set_closests_small(Node<T,Cond>* player) const
{
    if(isSmallest(player))
        return nullptr;
    Node<T, Cond>* temp = player;
    if(temp->son_smaller == nullptr)
    {
        if(temp->father == nullptr)
        {
            return nullptr;
        }
        else if(temp == temp->father->son_smaller)
        {
            while(temp == temp->father->son_smaller)
            {
                temp = temp->father;
            }
            temp = temp->father;
            return temp;
        }
        else if(temp == temp->father->son_larger)
        {
                return temp->father;
        }
    }
    return temp->son_smaller;
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
AVL_Tree<T, Cond>* AVL_Tree<T, Cond>::unite(AVL_Tree<T, Cond>* t2)
{
    T *t1_data = new T[this->size];
    T *t2_data = new T[t2->size];
    this->array_tree(t1_data);
    t2->array_tree(t2_data);
    int size = this->size + t2->size;
    T *united_data = new T[size];
    merge(united_data, t1_data, this->size, t2_data, t2->size);
    Node<T, Cond> *root = new Node<T, Cond>;
    create_next(0, size, united_data, root);
    AVL_Tree<T, Cond> *tree = new AVL_Tree<T, Cond>(root, size);
    tree->Highest_setting();
    delete[] t1_data;
    delete[] t2_data;
    delete[] united_data;
    root->father = nullptr;
    return tree;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::create_next(int index, int size, T* united_data, Node<T, Cond>* node)
{
    node->data = united_data[index + size/2];
    if (size/2 > 0)
    {
        Node<T, Cond>* next_smaller = new Node<T, Cond>;
        node->son_smaller = create_next(index, size/2, united_data, next_smaller);
        node->son_smaller->father = node;
    }
    else
        node->son_smaller = nullptr;
    if ((size - 1)/2 > 0)
    {
        Node<T, Cond>* next_larger = new Node<T, Cond>;
        node->son_larger = create_next(index + size/2 + 1, (size - 1)/2, united_data, next_larger);
        node->son_larger->father = node;
    }
    else
        node->son_larger = nullptr;
    node->height = height(node);
    return node;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::merge (T* united, T* t1, int t1_size, T* t2, int t2_size)
{
    Cond is_bigger;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < t1_size && j < t2_size)
        is_bigger(t1[i], t2[j]) ? united[k++] = t2[j++] : united[k++] = t1[i++];
    while (i  < t1_size)
        united[k++] =t1[i++];
    while (j < t2_size)
        united[k++] =  t2[j++];
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::create_tree(int height)
{
    if (height <= 0)
        return nullptr;
    Node<T, Cond>* node = new Node<T, Cond>;
    node->father = nullptr;
    node->height = 0;
    node->son_larger = create_tree(height - 1);
    if (node->son_larger)
        node->son_larger->father = node;
    node->son_smaller = create_tree(height - 1);
    if (node->son_smaller)
        node->son_smaller->father = node;
    return node;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_assign(Node<T, Cond>* node, T* elements, int size, int* i)
{
    if (!node)
        return;
    inorder_assign(node->son_smaller, elements, size, i);
    if (*i == size)
    {
        if (node == node->father->son_smaller)
            node->father->son_smaller = nullptr;
        else
            node->father->son_larger = nullptr;
        delete node;
        return;
    }
    node->data = elements[(*i)++];
    node->height = height(node);
    inorder_assign(node->son_larger, elements, size, i);
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