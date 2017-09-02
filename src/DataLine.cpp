#include "DataLine.h"
#include <ege.h>

namespace SurgeNight
{

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

DataLine::DataLine(const DataLine &rhd) : m_key(rhd.m_key), m_accessed(rhd.m_accessed), m_assigned(true)
{

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

void DataLine::paint(const int x, const int y, const int w, const int h, const unsigned int max)
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
    for (auto i = 0u; i < w; ++i)
        ege::line(x + i, y + h, x + i, y + h - (max != 0 ? static_cast<double>(m_key) / max * h : m_key));
}

}
