#include "hash.h"


Hash_table::~Hash_table()
{
    for (int i = 0 ; i < size_factor ; ++i)
    {
        if(data[i])
        {
            Pocket* temp = data[i];
            while(temp)
            {
                Pocket* temp_del = temp;
                temp = temp->next;
                delete temp_del;
            }
        }
    }
    delete[] data;
}


Pocket* Hash_table::get(int key) const
{
    int index = this->con(key);
    Pocket* temp = this->data[index];
    if(!temp)
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
    int place = con(key);
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
        Pocket* temp = this->data[place];
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = t;
    }
    this->size++;
}


void Hash_table::resize()
{
    condition c = condition(size_factor * factor);
    Pocket** tempData = new Pocket*[size_factor * factor];
    for (int i = 0 ; i < size_factor*factor ; ++i)
    {
        tempData[i] = nullptr;
    }
    for(int i = 0 ; i < size_factor ; i++)
    {
        if(data[i] != nullptr)
        {
            Pocket* temp = data[i];
            while (temp)
            {
                int index = c(temp->key);
                if(tempData[index] == nullptr)
                {
                    tempData[index]=temp;
                }
                else
                {
                    Pocket* temprun = tempData[index];
                    while(temprun->next != nullptr)
                    {
                        temprun = temprun->next;
                    }
                    temprun->next = temp;
                }
                Pocket* prev_temp = temp;
                temp = temp->next;
                prev_temp->next = nullptr;
            }
        }
    }
    delete[] data;
    data = tempData;
    size_factor = size_factor * factor;
    con.resizing(size_factor);
}

int Hash_table::get_games(int id) const
{
    Pocket* temp = this->get(id);
    int sum = temp->node->player->get_games_played();
    UF_Node* runner = temp->node;
    while(runner->father)
    {
        sum += runner->father->player->get_games_played();
        runner = runner->father;
    }
    return sum;
}

void Hash_table::destroy()
{
    for (int i = 0 ; i < size_factor; ++i)
    {
        if(data[i])
        {
            Pocket* del_temp = data[i];
            Pocket* ptr_temp = data[i];
            while(ptr_temp->next)
            {
                ptr_temp = ptr_temp->next;
                delete del_temp->node->player;
                delete del_temp->node;
                del_temp = ptr_temp;
            }
            delete del_temp->node->player;
            delete del_temp->node;
        }
    }
}
