#ifndef __SN_DATA_LINE_H__
#define __SN_DATA_LINE_H__

#include <functional>

namespace SurgeNight
{

class DataLine{
public:
    DataLine();
    ~DataLine();
    DataLine(const DataLine &rhd);

    void setAccessed();
    DataLine& operator=(const DataLine &rhd);
    const bool operator<(const DataLine &rhd);
    const bool operator<=(const DataLine &rhd);
    const bool operator>(const DataLine &rhd);
    const bool operator>=(const DataLine &rhd);

    void setKey(const unsigned int key) { m_key = key; }
    const unsigned int getKey() const { return m_key; }
    static void setDrawFunc(const std::function<void()> &func) { m_drawFunc = func; }

    void paint(const int x, const int y, const int w, const int h, const unsigned int max = 0);

private:
    void drawFunc() { if (m_drawFunc != nullptr) m_drawFunc(); }
    static std::function<void()> m_drawFunc;
    unsigned int m_key;
    bool m_accessed, m_assigned;
};

}

#endif //__SN_DATA_LINE_H__
