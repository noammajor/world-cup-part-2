#ifndef UF_H
#define UF_H

#include "hash.h"


template<class T,class G>
struct Node
{
    Node* father;
    T data;
    int height;
    G* group;

    T& get_data_Node();
    Node(T data): father(nullptr), data(data), height(1){}

};


template<class T, class E, class G>
class UF
{
    Hash_table<E>* elements;
    Node<T,G>* groups;
    int size;

public:
    UF();
    bool insert(E elem, T group);
    void Union(T g1, T g2);
    G* find(E elem) const;


};


template<class T, class E, class G>
bool UF<T, E, Cond>::insert(E elem, T group)
{
    Node<E> node1 = new Node<E>(elem);
    elements->add(elem->get_key(), node1);
    node1->group = group;

    return true;
}

template<class T, class E, class G>
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

template<class T, class E, class G>
G* UF<T, E, Cond>::find(int key)
{
  Pocket<T>* temp1 = this->elements.get(key);
  if(temp1== nullptr)
  {
      return nullptr;
  }
  Node<T,G>* tempnode = temp1->node;
  while(tempnode->father!= nullptr)
  {
      tempnode=tempnode->father;// hold top of the group
  }
  Node<T,G>* tempsqeezelines1=temp1->node;
  Node<T,G>* tempsqeezelines2=temp1->node;
  while(tempsqeezelines1->father!= nullptr)
  {
      tempsqeezelines2=tempsqeezelines1->father;
      tempsqeezelines1->father = tempnode;
      tempsqeezelines1=tempsqeezelines2;
  }
    return tempnode->group;
}




#endif //UF_H
