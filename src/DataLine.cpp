#include "DataLine.h"
#include <ege.h>

DataLine::DataLine() : m_key(0), m_checked(false), m_selected(false)
{

}

DataLine::~DataLine()
{

}

void DataLine::draw(const int xPos, const int width, const int yPos, const int viewHeight)
{
    if (m_selected) {
        ege::setcolor(ege::LIGHTBLUE);
        ege::setfillcolor(ege::LIGHTBLUE);
        m_selected = false;
    }
    if (m_checked) {
        ege::setcolor(ege::LIGHTRED);
        ege::setfillcolor(ege::LIGHTRED);
        m_checked = false;
    }
    for (auto i = 0u; i < width; ++i)
        ege::line(xPos + i, yPos + viewHeight, xPos + i, yPos + viewHeight - m_key);
}

void DataLine::setChecked()
{
    m_checked = true;
}

void DataLine::setSelected()
{
    m_selected = true;
}

void DataLine::setKey(const int key)
{
    m_key = key;
}

const int DataLine::getKey() const
{
    return m_key;
}
