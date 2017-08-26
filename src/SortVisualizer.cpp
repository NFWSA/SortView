#include "DataLine.h"
#include <ege.h>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace ege;

int g_viewHeight = 700, g_maxValue = 700;
std::chrono::time_point<std::chrono::system_clock> g_beginTime;

const bool draw(DataLine *data, const int num, const std::string &str = "Unknown", const float rate = -1.0f)
{
    int width = getwidth() / num;
    color_t color = getcolor(), flcolor = getfillcolor();
    cleardevice();
    for (int i = 0; i < num; ++i) {
        data[i].draw(i * width + 10, width, 0, g_viewHeight);
        setcolor(color);
        setfillcolor(flcolor);
    }
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - g_beginTime;
    if (rate < 0.0f)
        xyprintf(30, g_viewHeight + 10, "%s Sort : %0.2lf sec.", str.c_str(), diff.count());
    else
        xyprintf(30, g_viewHeight + 10, "%s Sort : %0.2lf sec. %0.2f%%", str.c_str(), diff.count(), rate);
    delay_ms(0);
    if (kbhit() && getch() == key_esc)
        return false;
    return true;
}

const bool countSort(DataLine *data, const int num)
{
    int *count = new int[g_maxValue + 1];
    for (int i = 0; i <= g_maxValue; ++i)
        count[i] = 0;
    for (int i = 0; i < num; ++i) {
        data[i].setSelected();
        ++count[data[i].getKey()];
        if (!draw(data, num, "Count")) {
            delete[] count;
            return false;
        }
    }
    for (int i = 1; i <= g_maxValue; ++i) {
        count[i] += count[i-1];
        if (!draw(data, num, "Count", static_cast<float>(i) / g_maxValue * 100.0f)) {
            delete[] count;
            return false;
        }

    }
    DataLine *ndata = new DataLine[num];
    for (int i = 0; i < num; ++i) {
        data[i].setChecked();
        ndata[--count[data[i].getKey()]] = std::move(data[i]);
        if (!draw(ndata, num, "Count")) {
            delete[] ndata;
            delete[] count;
            return false;
        }
    }
    delete[] ndata;
    delete[] count;
    return true;
}

const bool selectSort(DataLine *data, const int num)
{
    for (int i = 0; i < num; ++i) {
        int key = i;
        for (int j = i + 1; j < num; ++j) {
            data[key].setChecked();
            data[j].setSelected();
            if (data[j].getKey() < data[key].getKey())
                key = j;
            if (!draw(data, num, "Select"))
                return false;
        }
        std::swap(data[key], data[i]);
        if (!draw(data, num, "Select"))
            return false;
    }
    return true;
}

const bool bubbleSort(DataLine *data, const int num)
{
    for (int i = 0; i < num; ++i) {
        for (int j = num - 1; j > i; --j) {
            data[j].setSelected();
            if (data[j-1].getKey() > data[j].getKey()) {
                data[j].setChecked();
                std::swap(data[j - 1], data[j]);
            }
            if (!draw(data, num, "Bubble"))
                return false;
        }
    }
    return true;
}

const bool quickSort(DataLine *data, const int beg, const int end, const int num)
{
    if (beg >= end || beg == end - 1)
        return true;
    DataLine t = data[end - 1];
    data[end-1].setChecked();
    int i = beg;
    for (int j = beg; j < end - 1; ++j) {
        data[j].setSelected();
        if (data[j].getKey() <= t.getKey()) {
            data[j].setChecked();
            std::swap(data[i++], data[j]);
        }
        if (!draw(data, num, "Quick"))
            return false;
    }
    data[end - 1] = data[i];
    data[i] = t;
    if (!draw(data, num, "Quick"))
        return false;
    if (!quickSort(data, beg, i, num))
        return false;
    if (!quickSort(data, i + 1, end, num))
        return false;
    return true;
}

const bool insertSort(DataLine *data, const int num)
{
    DataLine t;
    for (int i = 0; i < num; ++i) {
        data[i].setChecked();
        t = data[i];
        int j = i;
        for (; j > 0; --j) {
            data[j - 1].setSelected();
            if (data[j - 1].getKey() > t.getKey())
                data[j] = data[j - 1];
            else
                break;
            if (!draw(data, num, "Insert"))
                return false;
        }
        data[j] = std::move(t);
        if (!draw(data, num, "Insert"))
            return false;
    }
    return true;
}

const bool stdSort(DataLine *data, const int num)
{
    std::sort(data, data + num, [=](DataLine &lhd, DataLine &rhd) -> bool {
        lhd.setChecked();
        rhd.setChecked();
        draw(data, num, "Std");
        return lhd.getKey() < rhd.getKey();
    });
    return true;
}

void show(const int key)
{
    std::ifstream fin("in.txt", std::ifstream::in);
    int num = 0, value = 0, j = 0;
    fin >> num >> g_maxValue;
    if(num <= 0 || g_maxValue <= 0)
        return;
    DataLine *data = new DataLine[num];
    g_viewHeight = getheight() - 40;
    while (fin >> value) {
        if(g_maxValue > g_viewHeight)
            value = static_cast<double>(value) / g_maxValue * g_viewHeight;
        data[j++].setKey(value);
    }
    fin.close();
    fin.clear();
    cleardevice();
    g_beginTime = std::chrono::system_clock::now();
    bool rlt = false;
    switch(key) {
        case key_1:
            rlt = bubbleSort(data, num);
            break;
        case key_2:
            rlt = insertSort(data, num);
            break;
        case key_3:
            rlt = selectSort(data, num);
            break;
        case key_4:
            rlt = quickSort(data, 0, num, num);
            break;
        case key_5:
            rlt = countSort(data, num);
            break;
        case key_6:
            rlt = stdSort(data, num);
            break;
    }
    if (rlt)
        xyprintf(20, 20, "Sort finish, press any key to continue...");
    else
        xyprintf(20, 20, "Sort break, press any key to continue...");
    getch();
    delete[] data;
    data = NULL;
}

int main()
{
    setinitmode( INIT_NOFORCEEXIT | INIT_RENDERMANUAL );
    //setinitmode( INIT_RENDERMANUAL | INIT_NOBORDER | INIT_NOFORCEEXIT );
    initgraph(1300, 320);
    setcaption("Sort Visualizer  by SurgeNight");
    std::string str[] = {
        "bubble sort",
        "insert sort",
        "select sort",
        "quick sort",
        "count sort",
        "std sort",
        "exit"
    };
    setfont(30, 0, "Arial");
    setcolor(LIGHTGREEN);
    while (is_run()) {
        cleardevice();
        xyprintf(20, 20, "Please press key to start to sort:");
        auto menuNum = sizeof(str) / sizeof(std::string);
        for(auto i = 0u; i < menuNum; ++i)
            xyprintf(20, 50 + i * 30, "\t%d. %s", (i + 1) % menuNum, str[i].c_str());
        int key = getch();
        if (key_0 == key)
            break;
        else if (key >= key_1 && key <= key_6) {
            show(key);
        }
        else {
            xyprintf(20, 20, "Select error! Press any key to continue...");
            getch();
            continue;
        }
    }
    closegraph();
    return 0;
}
