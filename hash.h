#ifndef HASH
#define HASH

#include "UF.h"
#include "Player.h"


struct UF_Node
{
    UF_Node* father;
    Player* data;
    int size;
    Team* group;

    explicit UF_Node( Player* data): father(nullptr), data(data), size(1){}

};



struct Pocket
{
    UF_Node* node;
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

class Hash_table
{
    int size;
    Pocket* data;
    int size_factor;
    static const int factor = 2;
    condition con;

public:
    Hash_table(): size(0),data(new Pocket[10]),size_factor(10), con()
    {
        for (int i = 0; i < 10; ++i)
        {
        data[i] = nullptr;
        }
    };

    ~Hash_table();
    Hash_table &operator=(const Hash_table&hash) = delete;
    Hash_table(const Hash_table &hash) = delete;
    void add(int key, const  UF_Node* data);
    void resize();
    Pocket* get(int key) const;
    int getsize() const;
    int getfactor() const;
};

#endif