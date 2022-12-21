#ifndef HASH
#define HASH

#include "UF.h"

template<class T,class G>
struct Pocket
{
    UF_Node<T,G>* node;
    Pocket* next;
    int key;
};

class condition
{
    int k;
public:
    condition(int k = 10):k(k){};
    void resizing(int m)
    {
        k = m;
    }

    int operator()(int key) const
    {
        return key % k;
    }
};


template<class T,class G>
class Hash_table
{
    int size;
    Pocket<T,G>* data;
    int size_factor;
    static const int factor = 2;
    condition con;

public:
    Hash_table<T,G>(): size(0),data(new Pocket<T,G>[10]),size_factor(10), con()
    {
        for (int i = 0; i < 10; ++i)
        {
        data[i]= nullptr;
        }
    };

    ~Hash_table<T,G>();
    Hash_table<T,G> &operator=(const Hash_table<T,G> &hash) = delete;
    Hash_table<T,G>(const Hash_table<T,G> &hash) = delete;
    void add(int key, const  UF_Node<T,G>* data);


 //   bool remove (int key);
    void resize();
    Pocket<T,G>* get(int key) const;
    int getsize() const;
    int getfactor() const;
};


template<class T,class G>
int Hash_table<T,G>:: getsize() const
{
    return this->size;
}
template<class T,class G>
int Hash_table<T,G>:: getfactor() const
{
    return this->size_factor;
}
template<class T,class G>
Pocket<T,G>* Hash_table<T,G>::get(int key) const
{
    int index = this->con(key);
    Pocket<T,G>* temp = this->data[index];
    if(temp== nullptr)
    {
        return nullptr;
    }
    else
    {
        while(temp)
        {
            if(temp->key == key)
            {
                return temp;
            }
            else
                temp = temp->next;
        }
    }
    return nullptr;
}


template<class T,class G>
void Hash_table<T,G>::add(int key, const  UF_Node<T,G>* elem)
{
    if(this->size_factor <= this->size)
    {
        resize();
    }
    int place=con(key);
    Pocket<T,G>* t= new Pocket<T,G>();
    t->next= nullptr;
    t->key = key;
    t->node = elem;
    if(data[place] == nullptr)
    {
        this->data[place] = t;
    }
    else
    {
        Pocket<T,G>* temp =this->data[place];
        while(temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = t;
    }
    this->size++;
}

template<class T,class G>
void Hash_table<T,G>::resize()
{
    condition c=condition(size_factor*factor);
        Pocket<T,G> *tempData = new Pocket<T,G>[size_factor * factor];

        for (int i = 0 ; i < size_factor*factor ; ++i)
        {
        tempData[i] = nullptr;
        }
        for(int i = 0 ; i < size_factor ; i++)
        {
            if(this->data[i] != nullptr)
            {
                Pocket<T,G>* temp=data[i];
                while (temp!= nullptr)
                {
                    int index = c(temp->key);
                    if(tempData[index] == nullptr)
                    {
                        tempData[index]=temp;
                    }
                    else
                    {
                        Pocket<T,G>* temprun=tempData[index];
                        while(temprun->next!=nullptr)
                        {
                            temprun=temprun->next;
                        }
                        temprun->next=temp;
                    }
                    temp=temp->next;
                }
            }
        }
    delete[] this->data;
    this->data=tempData;
    this->size_factor=this->size_factor*this->factor;
    this->con.resizing(size_factor);
}

template<class T,class G>
Hash_table<T,G>::~Hash_table()
{

    for (int i = 0; i < size_factor; ++i)
    {
        if(this->data[i]!= nullptr)
        {
            Pocket<T,G>* temp=data[i];
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