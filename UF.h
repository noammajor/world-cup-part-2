#ifndef UF_H
#define UF_H

#include "hash.h"
#include "AVL_tree.h"


template<class T,class G>
struct UF_Node
{
    UF_Node* father;
    T data;
    int height;
    G* group;

    explicit UF_Node(T data): father(nullptr), data(data), height(1){}

};


template<class T, class G, class Cond>
class UF
{
    Hash_table<T, G>* elements;
    AVL_Tree<G, Cond>* groups;
    int size;

public:
    UF();
    bool insert(T elem, G group);
    void Union(G g1, G g2);
    G* find(int key);


};


template<class T, class G, class Cond>
bool UF<T, G, Cond>::insert(T elem, G group)
{
    UF_Node<T,G> node1 = new UF_Node<T,G>(elem);
    elements->add(elem->get_key(), node1);
    node1->group = group;
    UF_Node<T, G> root = group->get_elements();
    node1.father = root;

    // elem->partial_spirit += team_spirit


    return true;
}

template<class T, class G, class Cond>
void UF<T, G, Cond>::Union(G g1, G g2)
{
    if(g1 == g2)
        return;
    UF_Node<T,G> root1 = g1->get_elements();
    UF_Node<T,G> root2 = g2->get_elements();
    if (g1->get_size() > g2->get_size())
    {
        root2->make_father(root1);
        g1->resize(g2->get_size());
    }
    else
    {
        root1->make_father(root2);
        g2->resize(g1->get_size());
    }
}

// new functions- make_father and resize


template<class T, class G, class Cond>
G* UF<T, G, Cond>::find(int key)
{
    Pocket<T, G>* temp1 = this->elements.get(key);
    if(temp1 == nullptr)
    {
        return nullptr;
    }
    UF_Node<T,G>* tempnode = temp1->node;
    while(tempnode->father!= nullptr)
    {
        tempnode=tempnode->father;// hold top of the group
    }
    UF_Node<T,G>* tempsqeezelines1=temp1->node;
    UF_Node<T,G>* tempsqeezelines2=temp1->node;
    while(tempsqeezelines1->father!= nullptr)
    {
        tempsqeezelines2=tempsqeezelines1->father;
        tempsqeezelines1->father = tempnode;
        tempsqeezelines1=tempsqeezelines2;
    }
    return tempnode->group;
}




#endif //UF_H
