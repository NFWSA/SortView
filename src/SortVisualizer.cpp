#include "DataLine.h"
#include <ege.h>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <exception>

using namespace ege;

int g_viewHeight = 700, g_maxValue = 700;
std::chrono::time_point<std::chrono::system_clock> g_beginTime;

void draw(DataLine *data, const int num, const std::string &str = "Unknown", const float rate = -1.0f)
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
    if (kbhit() && getch() == key_esc) {
        std::runtime_error a("break sort");
        throw a;
    }
}

void countSort(DataLine *data, const int num)
{
    int *count = new int[g_maxValue + 1];
    try {
        for (int i = 0; i <= g_maxValue; ++i)
            count[i] = 0;
        for (int i = 0; i < num; ++i) {
            data[i].setAccessed();
            ++count[data[i].getKey()];
        }
        for (int i = 1; i <= g_maxValue; ++i) {
            count[i] += count[i-1];
            draw(data, num, "Count", static_cast<float>(i) / g_maxValue * 100.0f);
        }
    }
    catch (const std::runtime_error &e) {
        delete[] count;
        return;
    }
    DataLine *ndata = new DataLine[num];
    DataLine::setDrawFunc([&](){
        draw(ndata, num, "Count");
    });
    try {
        for (int i = 0; i < num; ++i) {
            data[i].setAccessed();
            ndata[--count[data[i].getKey()]] = std::move(data[i]);
        }
    }
    catch (const std::runtime_error &e) {
    }
    delete[] ndata;
    delete[] count;
}

void selectSort(DataLine *data, const int num)
{
    for (int i = 0; i < num; ++i) {
        int key = i;
        for (int j = i + 1; j < num; ++j) {
            if (data[j] < data[key])
                key = j;
        }
        std::swap(data[key], data[i]);
    }
}

void bubbleSort(DataLine *data, const int num)
{
    for (int i = 0; i < num; ++i) {
        for (int j = num - 1; j > i; --j) {
            if (data[j-1] > data[j]) {
                std::swap(data[j - 1], data[j]);
            }
        }
    }
}

void quickSort(DataLine *data, const int beg, const int end, const int num)
{
    if (beg >= end || beg == end - 1)
        return;
    DataLine t = data[end - 1];
    int i = beg;
    for (int j = beg; j < end - 1; ++j) {
        if (data[j] <= t)
            std::swap(data[i++], data[j]);
    }
    data[end - 1] = data[i];
    data[i] = t;
    quickSort(data, beg, i, num);
    quickSort(data, i + 1, end, num);
}

void insertSort(DataLine *data, const int num)
{
    DataLine t;
    for (int i = 0; i < num; ++i) {
        t = data[i];
        int j = i;
        for (; j > 0; --j) {
            if (data[j - 1] > t)
                data[j] = data[j - 1];
            else
                break;
        }
        data[j] = std::move(t);
    }
}

void stdSort(DataLine *data, const int num)
{
    std::sort(data, data + num);
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
    DataLine::setDrawFunc(nullptr);
    try {
        switch(key) {
            case key_1:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Bubble");
                });
                bubbleSort(data, num);
                break;
            case key_2:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Insert");
                });
                insertSort(data, num);
                break;
            case key_3:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Select");
                });
                selectSort(data, num);
                break;
            case key_4:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Quick");
                });
                quickSort(data, 0, num, num);
                break;
            case key_5:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Count");
                });
                countSort(data, num);
                break;
            case key_6:
                DataLine::setDrawFunc([&](){
                    draw(data, num, "Std");
                });
                stdSort(data, num);
                break;
        }
        xyprintf(20, 20, "Sort finish, press any key to continue...");
    }
    catch (const std::runtime_error &e) {
        xyprintf(20, 20, "Sort break, press any key to continue...");
    }
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
