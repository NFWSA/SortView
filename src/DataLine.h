#ifndef DATALINE_H
#define DATALINE_H

class DataLine{
private:
    int key;
    bool checked, selected;
    
public:
    void draw(const int &pos, const int &weight = 2);
    void setKey(const int &nkey);
    void setChecked();
    void setSelected();
    int getKey() const;
    DataLine();
    ~DataLine();
};

#endif //DATALINE_H
