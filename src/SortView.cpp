#include "DataLine.h"
#include <ege.h>
#include <fstream>
#include <string>
#include <ctime>

using namespace ege;

const int min = 1, max = 690;
long btime = 0;

void draw(DataLine *data, const int &num, std::string str = "Unknown")
{
    int weight = 1346/num;
    cleardevice();
    for(int i=0; i<num; ++i){
        data[i].draw(i*weight+10, weight);
    }
    xyprintf(430, 725, "%s Sort : %ld sec.", str.c_str(), std::time(NULL)-btime);
}

void countSort(DataLine *data, const int &num)
{
    int count[max];
    for(int i=0; i<max; ++i)
        count[i] = 0;
    for(int i=0; i<num; ++i){
        delay_ms(0);
        data[i].setSelected();
        ++count[data[i].getKey()-1];
        draw(data, num, "Count");
    }
    for(int i=1; i<max; ++i){
        delay_ms(0);
        data[i%num].setSelected();
        count[i] += count[i-1];
        draw(data, num, "Count");
    }
    DataLine *ndata = new DataLine[num];
    for(int i=0; i<num; ++i){
        delay_ms(0);
        data[i].setChecked();
        ndata[--count[data[i].getKey()-1]] = data[i];
        draw(ndata, num, "Count");
    }
    delete[] ndata;
}

void selectSort(DataLine *data, const int &num)
{
    DataLine t;
    for(int i=0; i<num; ++i){
        int key = i;
        for(int j=i+1; j<num; ++j){
            delay_ms(0);
            data[key].setChecked();
            data[j].setSelected();
            if(data[j].getKey()<data[key].getKey())
                key = j;
            draw(data, num, "Select");
        }
        t = data[key];
        data[key] = data[i];
        data[i] = t;
        draw(data, num, "Select");
    }
}

void bubbleSort(DataLine *data, const int &num)
{
    DataLine t;
    for(int i=0; i<num; ++i){
        for(int j=num-1; j>i; --j){
            data[j].setSelected();
            delay_ms(0);
            if(data[j-1].getKey()>data[j].getKey()){
                data[j].setChecked();
                t = data[j-1];
                data[j-1] = data[j];
                data[j] = t;
            }
            draw(data, num, "Bubble");
        }
    }
}

void quickSort(DataLine *data, const int &beg, const int &end, const int &num)
{
    if(beg>=end || beg==end-1)
        return;
    DataLine t = data[end-1], temp;
    data[end-1].setChecked();
    int i = beg;
    for(int j=beg; j<end-1; ++j){
        delay_ms(0);
        data[j].setSelected();
        if(data[j].getKey()<=t.getKey()){
            data[j].setChecked();
            temp = data[i];
            data[i++] = data[j];
            data[j] = temp;
        }
        draw(data, num, "Quick");
    }
    data[end-1] = data[i];
    data[i] = t;
    draw(data, num, "Quick");
    quickSort(data, beg, i, num);
    quickSort(data, i+1, end, num);
}

void insertSort(DataLine *data, const int &num)
{
    DataLine t;
    for(int i=0; i<num; ++i){
        data[i].setChecked();
        t = data[i];
        int j = i;
        for(; j>0; --j){
            delay_ms(0);
            data[j-1].setSelected();
            if(data[j-1].getKey()>t.getKey())
                data[j] = data[j-1];
            else
                break;
            draw(data, num, "Insert");
        }
        data[j] = t;
        draw(data, num, "Insert");
    }
}

int main()
{
    // setinitmode( INIT_NOFORCEEXIT | INIT_RENDERMANUAL | INIT_NOBORDER | INIT_TOPMOST );
    setinitmode( INIT_RENDERMANUAL | INIT_NOBORDER );
    initgraph(-1, -1);
    setcaption("Sort View #use EGE #by NFWSA"); 
    std::string str[6];
    str[0] = "bubble sort";
    str[1] = "insert sort";
    str[2] = "select sort";
    str[3] = "quick sort";
    str[4] = "count sort";
    str[5] = "exit";
    setfont(30, 0, "Î¢ÈíÑÅºÚ");
    while(true){
        std::ifstream fin("in.txt", std::ifstream::in);
        int num = 1346, i = 0, j = 0;
        fin >> num;
        DataLine *data = new DataLine[num];
        while(fin>>i){
            data[j].setKey(i);
            ++j;
        }
        fin.close();
        fin.clear();
        cleardevice();
        xyprintf(20, 20, "Please press key to start to sort:");
        for(int i=0; i<6; ++i)
            xyprintf(20, 50+i*30, "\t%d¡¢%s", i+1, str[i].c_str());
        int key = getch();
        cleardevice();
        setcolor(LIGHTGREEN);
        btime = std::time(NULL);
        switch(key){
            case key_1:
                bubbleSort(data, num);
                break;
            case key_2:
                insertSort(data, num);
                break;
            case key_3:
                selectSort(data, num);
                break;
            case key_4:
                quickSort(data, 0, num, num);
                break;
            case key_5:
                countSort(data, num);
                break;
            case key_6:
                return 0;
            default:
                xyprintf(20, 20, "Select error! Press any key to exit...");
                getch();
                return -1;
        }
        xyprintf(20, 20, "Sort finish, press any key to continue...");
        getch();
        delete[] data;
        data = NULL;
    }
    closegraph();
    return 0;
}