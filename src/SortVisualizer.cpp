#include "DataLine.h"
#include "SortView.h"
#include <ege.h>
#include <string>
#include <algorithm>
#include <map>
#include <exception>

using namespace ege;

void countSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    unsigned int max = view->getMax();
    auto count = new unsigned int[max + 1]();
    try {
        for (auto i = beg; i < end; ++i) {
            i->setAccessed();
            ++count[i->getKey()];
        }
        for (auto i = 1u; i <= max; ++i) {
            count[i] += count[i-1];
            view->paint(static_cast<float>(i) / max * 100.0f);
        }
    }
    catch (const std::exception &e) {
        delete[] count;
        throw e;
        // return;
    }
    auto ndata = new DataLine[end - beg];
    view->setData(ndata);
    try {
        for (auto i = beg; i < end; ++i) {
            i->setAccessed();
            ndata[--count[i->getKey()]] = *i;
        }
    }
    catch (const std::exception &e) {
        view->setData(nullptr);
        delete[] ndata;
        delete[] count;
        throw e;
    }
    view->setData(nullptr);
    delete[] ndata;
    delete[] count;
}

void selectSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    for (auto i = beg; i < end; ++i) {
        auto key = i;
        for (auto j = i + 1; j < end; ++j) {
            if (*j < *key)
                key = j;
        }
        std::swap(*key, *i);
    }
}

void bubbleSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    for (auto i = beg; i < end; ++i) {
        for (auto j = end - 1; j > i; --j) {
            if (*(j - 1) > *j) {
                std::swap(*(j - 1), *j);
            }
        }
    }
}

void quickSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    if (end <= beg)
        return;
    auto t = end - 1;
    auto i = beg;
    for (auto j = beg; j < end - 1; ++j) {
        if (*j <= *t)
            std::swap(*i++, *j);
    }
    std::swap(*i, *t);
    quickSort(beg, i);
    quickSort(i + 1, end);
}

void insertSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    DataLine t;
    for (auto i = beg; i < end; ++i) {
        t = *i;
        auto j = i;
        for (; j > beg; --j) {
            if (*(j - 1) > t)
                *j = *(j - 1);
            else
                break;
        }
        *j = std::move(t);
    }
}

void stdSort(DataLine *beg, DataLine *end, SortView *view = nullptr)
{
    std::sort(beg, end);
}

void show(const std::string &name, std::function<void(DataLine*, DataLine*, SortView*)> func)
{
    cleardevice();
    SortView view(name, "in.txt", 0, 0, getwidth(), getheight());
    try {
        DataLine::setDrawFunc([&]() {
            cleardevice();
            view.paint();
            if (ege::kbhit() && ege::getch() == ege::key_esc) {
                std::exception a;
                throw a;
            }
        });
        func(view.begin(), view.end(), &view);
        xyprintf(20, 20, "Sort finish, press any key to continue...");
    }
    catch (const std::exception &e) {
        xyprintf(20, 20, "Sort break, press any key to continue...");
    }
    getch();
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
    typedef std::pair< std::string, std::function<void(DataLine*, DataLine*, SortView*)> > Algo;
    typedef std::map< int, Algo > AlgoTab;
    AlgoTab algo = {
        { key_1, { "Bubble", bubbleSort } },
        { key_2, { "Insert", insertSort } },
        { key_3, { "Select", selectSort } },
        { key_4, { "Quick", quickSort } },
        { key_5, { "Count", countSort } },
        { key_6, { "Std", stdSort } }
    };
    setfont(30, 0, "Arial");
    setcolor(LIGHTGREEN);
    while (true) {
        cleardevice();
        xyprintf(20, 20, "Please press key to start to sort:");
        auto menuNum = sizeof(str) / sizeof(std::string);
        for(auto i = 0u; i < menuNum; ++i)
            xyprintf(20, 50 + i * 30, "\t%d. %s", (i + 1) % menuNum, str[i].c_str());
        int key = getch();
        if (key_0 == key)
            break;
        auto it = algo.find(key);
        if (it != algo.end()){
            show((*it).second.first, (*it).second.second);
            continue;
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
