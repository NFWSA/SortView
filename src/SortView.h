#ifndef __SN_SORT_VIEW_H__
#define __SN_SORT_VIEW_H__

#include <chrono>
#include <string>

namespace SurgeNight
{

class DataLine;

class SortView{
public:
    SortView(const std::string &algname, const std::string &filename, const int x = 0, const int y = 0, const int w = 640, const int h = 320);
    ~SortView();

    void setData(DataLine *data);
    void getXY(int &x, int &y) const;
    void getWH(int &w, int &h) const;
    const unsigned int getMax() const;

    DataLine* begin();
    DataLine* end();

    void paint(const float rate = -1.0f);

private:
    int m_pos[5];
    DataLine *m_data, *m_outside;
    unsigned int m_max, m_size;
    std::chrono::time_point<std::chrono::system_clock> m_begTime;
    std::string m_name;
};

}

#endif //__SN_SORT_VIEW_H__
