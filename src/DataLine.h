#ifndef __DATALINE_H__
#define __DATALINE_H__

#include <functional>

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
    
    void setKey(const int key);
    const int getKey() const;
    static void setDrawFunc(const std::function<void()> func);

    void draw(const int xPos, const int weight = 2, const int yPos = 0, const int viewHeight = 700);

private:
    void drawFunc();
    static std::function<void()> m_drawFunc;
    int m_key;
    bool m_accessed, m_assigned;
};

#endif //__DATALINE_H__
