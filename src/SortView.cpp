#include "SortView.h"
#include "DataLine.h"
#include <ege.h>
#include <fstream>
#include <chrono>

SortView::SortView(const std::string &algname, const std::string &filename, const int x, const int y, const int w, const int h) :
    m_pos{ x, y, w, h <= 40 ? 41 : h, h - 40 }, m_data(nullptr), m_name(algname), m_outside(nullptr)
{
    std::ifstream fin(filename, std::ifstream::in);
    unsigned int value = 0, j = 0;
    fin >> m_size >> m_max;
    if(m_size <= 0 || m_max <= 0)
        return;
    m_data = new DataLine[m_size];
    for (auto i = 0u; i < m_size; ++i) {
        fin >> value;
        m_data[j++].setKey(value);
    }
    fin.close();
    m_begTime = std::chrono::system_clock::now();
}

SortView::~SortView()
{
    if (m_data != nullptr)
        delete m_data;
    DataLine::setDrawFunc(nullptr);
}

void SortView::setData(DataLine *data)
{
    m_outside = data;
}

void SortView::getXY(int &x, int &y) const
{
    x = m_pos[0];
    y = m_pos[1];
}

void SortView::getWH(int &w, int &h) const
{
    w = m_pos[2];
    h = m_pos[3];
}

const unsigned int SortView::getMax() const
{
    return m_max;
}

DataLine* SortView::begin()
{
    return m_data;
}

DataLine* SortView::end()
{
    return m_data + m_size;
}

void SortView::paint(const float rate)
{
    int width = m_pos[2] / m_size;
    auto data = (m_outside == nullptr ? m_data : m_outside);
    unsigned int max = m_max > m_pos[4] ? m_max : 0;
    ege::color_t color = ege::getcolor();
    // , flcolor = ege::getfillcolor();
    for (auto i = 0u; i < m_size; ++i) {
        data[i].paint(i * width, 0, width, m_pos[4], max);
        ege::setcolor(color);
        // ege::setfillcolor(flcolor);
    }
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - m_begTime;
    if (rate < 0.0f)
        ege::xyprintf(m_pos[0] + 30, m_pos[4] + 10, "%s Sort : %0.2lf sec.", m_name.c_str(), diff.count());
    else
        ege::xyprintf(m_pos[0] + 30, m_pos[4] + 10,
                     "%s Sort : %0.2lf sec. %0.2f%%", m_name.c_str(), diff.count(), rate);
    ege::delay_ms(0);
}
