#ifndef UF_H
#define UF_H

#include "AVL_tree.h"

template<class T, class E, class Cond>
class UF
{
    //Pocket<E>* elements;
    Node<T, Cond>* groups;
    int size;

public:
    UF();
    bool insert(E elem, T group);
    void Union(T g1, T g2);
    T find(E elem) const;


};


template<class T, class E, class Cond>
bool UF<T, E, Cond>::insert(E elem, T group)
{
    return true;
}

template<class T, class E, class Cond>
void UF<T, E, Cond>::Union(T g1, T g2)
{
    if(g1 == g2)
        return;
    T root1 = g1->get_root();
    T root2 = g2->get_root();
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

template<class T, class E, class Cond>
T UF<T, E, Cond>::find(E elem) const
{

}




#endif //UF_H
