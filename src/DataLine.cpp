#include "DataLine.h"
#include <ege.h>

std::function<void()> DataLine::m_drawFunc = nullptr;

DataLine::DataLine() : m_key(0), m_accessed(false), m_assigned(false)
{

}

DataLine::~DataLine()
{

}

void DataLine::setAccessed()
{
    m_accessed = true;
    drawFunc();
}

DataLine::DataLine(const DataLine &rhd) : m_key(rhd.m_key), m_accessed(rhd.m_accessed), m_assigned(rhd.m_assigned)
{
    m_assigned = true;
    drawFunc();
}

DataLine& DataLine::operator=(const DataLine &rhd)
{
    m_assigned = true;
    m_key = rhd.m_key;
    drawFunc();
    return *this;
}

const bool DataLine::operator<(const DataLine &rhd)
{
    setAccessed();
    return m_key < rhd.m_key;
}

const bool DataLine::operator<=(const DataLine &rhd)
{
    setAccessed();
    return m_key <= rhd.m_key;
}

const bool DataLine::operator>(const DataLine &rhd)
{
    setAccessed();
    return m_key > rhd.m_key;
}

const bool DataLine::operator>=(const DataLine &rhd)
{
    setAccessed();
    return m_key >= rhd.m_key;
}

void DataLine::draw(const int xPos, const int width, const int yPos, const int viewHeight)
{
    if (m_accessed) {
        ege::setcolor(ege::LIGHTBLUE);
        ege::setfillcolor(ege::LIGHTBLUE);
        m_accessed = false;
    }
    if (m_assigned) {
        ege::setcolor(ege::LIGHTRED);
        ege::setfillcolor(ege::LIGHTRED);
        m_assigned = false;
    }
    for (auto i = 0u; i < width; ++i)
        ege::line(xPos + i, yPos + viewHeight, xPos + i, yPos + viewHeight - m_key);
}

void DataLine::setKey(const int key)
{
    m_key = key;
}

const int DataLine::getKey() const
{
    return m_key;
}

void DataLine::setDrawFunc(const std::function<void()> func)
{
    m_drawFunc = func;
}

void DataLine::drawFunc()
{
    if (m_drawFunc != nullptr)
        m_drawFunc();
}