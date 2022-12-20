#ifndef HASH
#define HASH
#include "AVL_tree.h"

template<class T, class Cond>
struct Pocket
{
    Node<T,Cond>* node;
    Pocket* next;
    int key;
};

class condition
{
    int k;
public:
    condition(int k):k(k){};
    void resizing(int m)
    {
        k=m;
    }
    int operator()(int key) const
    {
        return key%k;
    }
};
template<class T,class condition>
class Hash_table
{
    int size;
    Pocket* data;
    int size_factor;
    static const factor =2;
    condition con;
public:
    Hash_table(Cond con): size(0),data(new Pocket[10]),size_factor(10), con(con(10))
    {
        for (int i = 0; i < 10; ++i)
        {
        data[i]= nullptr;
        }
    };
    ~Hash_table();
    Hash_table<T,condition> &operator=(const Hash_table<T,condition> &hash) = delete;
    Hash_table<T,condition>(const Hash_table<T,condition> &hash) = delete;
    void add(int key, const  Node<T,Cond>* data);
 //   bool remove (int key);
    void resize();
    Pocket* get(int key) const;
};
template<class T,class condition>
Pocket* Hash_table<T,condition>::get(int key) const
{
    int index=this->con(key);
    Pocket* temp=this->data[index];
    if(temp== nullptr)
    {
        return nullptr;
    }
    else if
    {
        while(temp!=nullptr)
        {
            if(temp->key==key)
            {
                return temp;
            }
            else
                temp=temp->next;
        }
    }
    return nullptr;
}


template<class T,class condition,class cond>
void Hash_table<T,condition>::add(int key, const  Node<T,cond>* data)
{
    if(this->size_factor<=this->size)
    {
        resize();
    }
    int place=con(key);
    Pocket* t= new pocket();
    t->next= nullptr;
    t->key=key;
    t->node=data;
    if(data[place]== nullptr)
    {
        this->data[place]=t;
    }
    else if
    {
        pocket* temp =this->data[place];
        while(temp->next!=nullptr)
        {
            temp=temp->next;
        }
        temp->next=t;
    }
    this->size=size+1;
}
template<class T,class condition>
void Hash_table<T,condition>::resize()
{
    condition c=condition(size_factor*factor);
    try
    {
        Pocket* tempData=new Pocket[size_factor*factor];
        for (int i = 0; i < size_factor*factor; ++i)
        {
        tempData[i]= nullptr;
        }
        for(int i=0;i<size_factor;i++)
        {
            if(this->data[i]!= nullptr)
            {
                Pocket* temp=data[i];
                while (temp!= nullptr)
                {
                    int index=c(temp->key);
                    if(tempData[index]== nullptr)
                    {
                        tempData[index]=temp;
                    }
                    else if
                    {
                        Pocket* temprun=tempData[index];
                        while(temprun->next!=nullptr)
                        {
                            temprun=temprun->next;
                        }
                        temprun->next=temp;
                    }
                    Pocket* deltem=temp;
                    temp=temp->next;
                    delete deltem;
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        delete[] tempData;
        throw;
    }
    delete this->data;
    this->data=tempData;
    this->size_factor=this->size_factor*this->factor;
    this->con.resizing(size_factor);
}
template<class T,class condition>
Hash_table<T,condition>::~Hash_table()
{

    for (int i = 0; i < size_factor; ++i)
    {
        if(this->data[i]!= nullptr)
        {
            Pocket* temp=data[i];
            while(temp!= nullptr)
            {
                Pocket* tempdel=temp;
                temp=temp->next;
                delete tempdel;
            }
        }
    }
    delete[] data;
}




