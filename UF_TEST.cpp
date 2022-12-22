#include "UF.h"
#include <stdlib.h>
#include <cstdlib>
#include "assert.h"

int main()
{
    /*int arr[100];
    Hash_table<int,int> HTtest;
    UF<int,int,int> test;
    for (int i=0; i<100;i++)
    {
        arr[i]=rand();
    }
    for (int i=0; i<100;i++)
    {
        test.insert(arr[i],i%10);
        HTtest.add(i,arr[i]);
        assert(HTtest.getsize()==i+1);
        if(i>10 && i<20)
        {
        assert(HTtest.getfactor()==20)
        }
    if(i>20 && i<40)
    {
    assert(HTtest.getfactor()==40)
    }
    if(i>40 && i<80)
    {
    assert(HTtest.getfactor()==80)
    }
    if(i>80 && i<100)
    {
    assert(HTtest.getfactor()==160)
    }
}
    for(int i=0; i<10; i++)
    {
    assert(test.connected(arr[0],arr[i*10])==true);
    assert(test.connected(arr[10],arr[i*10])==true);
    assert(test.connected(arr[20],arr[i*10])==true);
    assert(test.connected(arr[30],arr[i*10])==true);
    assert(test.connected(arr[40],arr[i*10])==true);
    assert(test.connected(arr[50],arr[i*10])==true);
    assert(test.connected(arr[60],arr[i*10])==true);
    assert(test.connected(arr[70],arr[i*10])==true);
    assert(test.connected(arr[80],arr[i*10])==true);
    assert(test.connected(arr[90],arr[i*10])==true);
    }
    for(int i=0; i<10; i++)
{
    assert(test.connected(arr[1],arr[i*10+1])==true);
    assert(test.connected(arr[11],arr[i*10+1])==true);
    assert(test.connected(arr[21],arr[i*10+1])==true);
    assert(test.connected(arr[31],arr[i*10+1])==true);
    assert(test.connected(arr[41],arr[i*10+1])==true);
    assert(test.connected(arr[51],arr[i*10+1])==true);
    assert(test.connected(arr[61],arr[i*10+1])==true);
    assert(test.connected(arr[71],arr[i*10+1])==true);
    assert(test.connected(arr[81],arr[i*10+1])==true);
    assert(test.connected(arr[91],arr[i*10+1])==true);
}
    for(int k=0;k<10;k++)
    {
        for(int i=0; i<10; i++)
        {
            assert(test.connected(arr[0+k],arr[i*10+k])==true);
            assert(test.connected(arr[10+k],arr[i*10+k])==true);
            assert(test.connected(arr[20+k],arr[i*10+k])==true);
            assert(test.connected(arr[30+k],arr[i*10+k])==true);
            assert(test.connected(arr[40+k],arr[i*10+k])==true);
            assert(test.connected(arr[50+k],arr[i*10+k])==true);
            assert(test.connected(arr[60+k],arr[i*10+k])==true);
            assert(test.connected(arr[70+k],arr[i*10+k])==true);
            assert(test.connected(arr[80+k],arr[i*10+k])==true);
            assert(test.connected(arr[90+k],arr[i*10+k])==true);
        }
    }
    for(int i=0;i<100;i++)
    {
    assert(HTtest.get(key)->node->get_data_Node()==arr[i]);
    }
    test.union(test.find(1),test.find(2));
    assert(test.find(1));*/

    return 1;
};