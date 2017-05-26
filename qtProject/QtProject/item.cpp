#include "item.h"
using namespace std;
item::item(){
}

item::item(string _val)
{
    value=_val;
}

void item::incCount(){
    useCount++;
    if(useCount==2){
        this->isAvailable=false;
    }
}


