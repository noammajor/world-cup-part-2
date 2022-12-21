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
    UF(): elements(new Hash_table<T,G>), groups(new AVL_Tree<G, Cond>), size(0){}
    UF<T, G, Cond>& operator=(const UF<T, G, Cond>&) = delete;
    UF<T, G, Cond>(const UF<T, G, Cond>&) = delete;
    ~UF() = default; ////////////////////////do later

    bool insert(T elem, G group);
    void Union(G g1, G g2);
    G* find(int key);
    bool connected(E elem1,E elem2) const;
    bool addteam(int id);
    bool removeteam(int id);
   T* getplayer(int id);

};
template<class T, class G, class Cond>
bool UF<T, G, Cond>::addteam(int id)
{
    return groups->insert_to_tree(id);
}

template<class T, class G, class Cond>
bool UF<T, G, Cond>::removeteam(int id)
{
    return groups->template remove(id);
}
template<class T, class G, class Cond>
T* UF<T, G, Cond>::getplayer(int id)
{
   Pocket<T,G>* temp = elements->get(id);
   if(temp== nullptr)
   {
       return nullptr;
   }
    return temp->node->data;
}

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
bool UF<T, E, Cond>::connected(E elem1,E elem2) const
{
    return (this->find(elem1)==this->(elem2));
}

template<class T, class G, class Cond>
void UF<T, G, Cond>::Union(G g1, G g2)
{
    if(g1 == g2)
        return;
    UF_Node<T,G> root1 = g1->get_elements();
    UF_Node<T,G> root2 = g2->get_elements();
    if (g1->get_size() > g2->get_size())
        root2.father = root1;
    else
        root1.father = root2;
}


template<class T, class G, class Cond>
G* UF<T, G, Cond>::find(int key)
{
    Pocket<T, G>* pocket1 = this->elements.get(key);
    if(pocket1 == nullptr)
    {
        return nullptr;
    }
    UF_Node<T,G>* rootNode = pocket1->node;
    while(rootNode->father != nullptr)
    {
        rootNode = rootNode->father; // hold top of the group
    }
    UF_Node<T,G>* tempSqueezeLines1 = pocket1->node;
    UF_Node<T,G>* tempSqueezeLines2 = pocket1->node;
    while(tempSqueezeLines1->father != nullptr)
    {
        tempSqueezeLines2 = tempSqueezeLines1->father;
        tempSqueezeLines1->father = rootNode;
        tempSqueezeLines1 = tempSqueezeLines2;
    }
    return rootNode->group;
}




#endif //UF_H
