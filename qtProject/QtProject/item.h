#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QWidget>
namespace std{
class item
{
public:
    item();
    item(string val);
    string value;
    bool isAvailable=true;
    int useCount=0;
    bool isMatched=false;
    void incCount();

};
}
#endif // ITEM_H

