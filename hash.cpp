#include "hash.h"

int Hash_table:: getsize() const
{
    return this->size;
}

int Hash_table:: getfactor() const
{
    return this->size_factor;
}

Pocket* Hash_table::get(int key) const
{
    int index = this->con(key);
    Pocket* temp = this->data[index];
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


void Hash_table::add(int key, UF_Node* elem)
{
    if(this->size_factor <= this->size)
    {
        resize();
    }
    int place=con(key);
    Pocket* t= new Pocket();
    t->next= nullptr;
    t->key = key;
    t->node = elem;
    if(data[place] == nullptr)
    {
        this->data[place] = t;
    }
    else
    {
        Pocket* temp =this->data[place];
        while(temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = t;
    }
    this->size++;
}


void Hash_table::resize()
{
    condition c=condition(size_factor*factor);
    Pocket** tempData = new Pocket*[size_factor * factor];
    for (int i = 0 ; i < size_factor*factor ; ++i)
    {
        tempData[i] = nullptr;
    }
    for(int i = 0 ; i < size_factor ; i++)
    {
        if(this->data[i] != nullptr)
        {
            Pocket* temp = data[i];
            while (temp!= nullptr)
            {
                int index = c(temp->key);
                if(tempData[index] == nullptr)
                {
                    tempData[index]=temp;
                }
                else
                {
                    Pocket* temprun=tempData[index];
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


Hash_table::~Hash_table()
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

int Hash_table::get_games(int id) const
{
    Pocket* temp = this->get(id);
    int sum=0;
    sum=temp->node->player->get_games_played();
    UF_Node* runner=temp->node;
    while(runner->father!=nullptr)
    {
        sum+=runner->player->get_games_played();
        runner=runner->father;
    }
    sum+=runner->player->get_games_played();
    return sum;
}



bool Hash_table::is_active(int id) const
{
    Pocket* temp= this->get(id);
    UF_Node runner= temp->node;
    while(runner->father!=nullptr)
    {
        runner=runner->father;
    }
    if(runner->team==nullptr)
    {
        return false
    }
    else
        return true;


}