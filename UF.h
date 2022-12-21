#ifndef UF_H
#define UF_H

#include "hash.h"
#include "AVL_tree.h"





template<class T, class G, class Cond>
class UF
{
    Hash_table<T, G>* elements;
    AVL_Tree<G, Cond>* groups;

public:
    UF(): elements(new Hash_table<T,G>), groups(new AVL_Tree<G, Cond>){}
    UF<T, G, Cond>& operator=(const UF<T, G, Cond>&) = delete;
    UF<T, G, Cond>(const UF<T, G, Cond>&) = delete;
    ~UF() = default; ////////////////////////do later

    void insert(T elem, G group);
    void Union(G g1, G g2);
    G* find(int key);
    bool connected(T elem1, T elem2) const;
    bool addTeam(int id);
    bool removeTeam(int id);
    T* getPlayer(int id);
    bool teamExists(int teamID) const;


};

template<class T, class G, class Cond>
bool teamExists(int teamID) const
{
    if(groups->search(teamID) == nullptr)
    {
        return true;
    }
    else
        return false;
}
template<class T, class G, class Cond>
bool UF<T, G, Cond>::addTeam(int id)
{
    return groups->insert_to_tree(id);
}

template<class T, class G, class Cond>
bool UF<T, G, Cond>::removeTeam(int id)
{
    return groups->remove(id);
}

template<class T, class G, class Cond>
T* UF<T, G, Cond>::getPlayer(int id)
{
   Pocket<T,G>* temp = elements->get(id);
   if(temp == nullptr)
   {
       return nullptr;
   }
    return temp->node->data;
}

template<class T, class G, class Cond>
void UF<T, G, Cond>::insert(T elem, G group)
{
    UF_Node<T,G> node1 = new UF_Node<T,G>(elem);
    elements->add(elem->get_key(), node1);
    node1->group = group;
    UF_Node<T, G> root = group->get_elements();
    node1.father = root;
    root->size++;

    // elem->partial_spirit += team_spirit

    return true;
}

template<class T, class G, class Cond>
bool UF<T, G, Cond>::connected(T elem1, T elem2) const
{
    return (this->find(elem1) == this->find(elem2));
}

template<class T, class G, class Cond>
void UF<T, G, Cond>::Union(G g1, G g2)
{
    if (g1 == g2)
        return;
    UF_Node<T, G>* root1 = g1->get_elements();
    UF_Node<T, G>* root2 = g2->get_elements();
    if (root1->size > g2->size)
    {
        root2->father = root1;
        root1->size += root2->size;
    }
    else
    {
        root1->father = root2;
        root2->size += root1->size;
    }
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
