#include "DataLine.h"
#include <ege.h>

void DataLine::draw(const int &pos, const int &weight)
{
    ege::color_t color = ege::getcolor(), flcolor = ege::getfillcolor();
    if(selected){
        ege::setcolor(ege::LIGHTBLUE);
        ege::setfillcolor(ege::LIGHTBLUE);
        selected = false;
    }
    if(checked){
        ege::setcolor(ege::LIGHTRED);
        ege::setfillcolor(ege::LIGHTRED);
        checked = false;
    }
    // ege::bar(pos, 700-key, 1+pos+weight, 701);
    for(int i=0; i<weight; ++i)
        ege::line(pos+i, 700, pos+i, 701-key);
    // ege::line(pos, 700, pos, 700-key);
    // ege::line(pos+1, 700, pos+1, 700-key);
    ege::setcolor(color);
    ege::setfillcolor(flcolor);
}

void DataLine::setKey(const int &nkey)
{
    key = nkey;
}

void DataLine::setChecked()
{
    checked = true;
}

void DataLine::setSelected()
{
    selected = true;
}

int DataLine::getKey() const
{
    return key;
}

DataLine::DataLine()
{
    key = 0;
    checked = false;
    selected = false;
}

DataLine::~DataLine()
{

}
