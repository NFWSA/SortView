#ifndef __DATALINE_H__
#define __DATALINE_H__

class DataLine{
public:
    DataLine();
    ~DataLine();

    void setChecked();
    void setSelected();
    void setKey(const int key);
    const int getKey() const;

    void draw(const int xPos, const int weight = 2, const int yPos = 0, const int viewHeight = 700);

private:
    int m_key;
    bool m_checked, m_selected;
};

#endif //__DATALINE_H__
