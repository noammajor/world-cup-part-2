#ifndef HASH
#define HASH

#include "UF.h"

template<class T>
struct Pocket
{
    Node<T>* node;
    Pocket* next;
    int key;
};

class condition
{
    int k;
public:
    condition(int k):k(k){};
    void resizing(int m = 10)
    {
        k = m;
    }

    int operator()(int key) const
    {
        return key % k;
    }
};


template<class T,class condition>
class Hash_table
{
    int size;
    Pocket<T>* data;
    int size_factor;
    static const int factor = 2;
    condition con;

public:
    Hash_table(condition con): size(0),data(new Pocket<T>[10]),size_factor(10), con(con(10))
    {
        for (int i = 0; i < 10; ++i)
        {
        data[i]= nullptr;
        }
    };
    ~Hash_table();
    Hash_table<T,condition> &operator=(const Hash_table<T,condition> &hash) = delete;
    Hash_table<T,condition>(const Hash_table<T,condition> &hash) = delete;
    void add(int key, const  Node<T,condition>* data);
 //   bool remove (int key);
    void resize();
    Pocket<T>* get(int key) const;
};
template<class T,class condition>
Pocket<T>* Hash_table<T,condition>::get(int key) const
{
    int index=this->con(key);
    Pocket<T>* temp=this->data[index];
    if(temp== nullptr)
    {
        return nullptr;
    }
    else
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


template<class T,class condition>
void Hash_table<T,condition>::add(int key, const  Node<T,condition>* data)
{
    if(this->size_factor<=this->size)
    {
        resize();
    }
    int place=con(key);
    Pocket<T>* t= new Pocket<T>();
    t->next= nullptr;
    t->key=key;
    t->node=data;
    if(data[place]== nullptr)
    {
        this->data[place]=t;
    }
    else
    {
        Pocket<T>* temp =this->data[place];
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
        Pocket<T> *tempData = new Pocket<T>[size_factor * factor];

        for (int i = 0; i < size_factor*factor; ++i)
        {
        tempData[i]= nullptr;
        }
        for(int i=0;i<size_factor;i++)
        {
            if(this->data[i]!= nullptr)
            {
                Pocket<T>* temp=data[i];
                while (temp!= nullptr)
                {
                    int index=c(temp->key);
                    if(tempData[index]== nullptr)
                    {
                        tempData[index]=temp;
                    }
                    else
                    {
                        Pocket<T>* temprun=tempData[index];
                        while(temprun->next!=nullptr)
                        {
                            temprun=temprun->next;
                        }
                        temprun->next=temp;
                    }
                    Pocket<T>* detem1=temp;
                    temp=temp->next;
                    delete detem1;
                }
            }
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
            Pocket<T>* temp=data[i];
            while(temp!= nullptr)
            {
                Pocket<T>* tempdel=temp;
                temp=temp->next;
                delete tempdel;
            }
        }
    }
    delete[] data;
}
#endif