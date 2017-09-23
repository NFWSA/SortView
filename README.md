# 排序算法可视化工具

## 需求环境
### 依赖
+ [ege](https://github.com/misakamm/xege)库13.04版本及以上

### 示例编译平台
+ Windows 10 Professional x64 15063.540
+ mingw-w64-x86_64-g++ 7.1.0
+ ege library 15.04
+ [FatWhale](https://github.com/NFWSA/FatWhale) 构建工具

## 用法
### 相关文件
+ `MakeIn.bat`用于生成输入数据文件`in.txt`，双击后请输入数据数量与数据最大值
+ 程序同目录`in.txt`内为输入数据，第一行为数据量与数据最大值，此后每行是一个数据

### 使用说明
+ `SortVisualizer.exe`为主程序，请根据程序提示进行输入
+ 程序执行过程中，可以按==`Esc`==中断本次排序
+ 蓝色表示被取值的数据，红色表示被赋值的数据
+ 计数排序对数据进行一次扫描后是在进行计数数组的处理，程序会实时显示处理进度
+ 您可以按照`void (DataLine*, DataLine*, SortView*)`的原型写好自己的排序过程，然后照例加入到`algo`与`str`中即可看到排序效果
+ `algo`中记录按键到<排序名称， 排序函数>的关联，`str`中记录显示的菜单项，编号从1到9，最后一个元素为0

# Sort algorithm visualized program

## Requirements
### Librarys
+ [ege library](https://github.com/misakamm/xege) 13.04+

### Sample compile platform
+ Windows 10 Professional x64 15063.540
+ mingw-w64-x86_64-g++ 7.1.0
+ ege library 15.04
+ [FatWhale](https://github.com/NFWSA/FatWhale) build tool

## Usage
### Relative Files
+ `MakeIn.bat` is to make the input file `in.txt`, execute it and input the number and max value of the data
+ `in.txt` in folder that program in is the input file, one line is the number and max value of the data, and then one data per line

### Help
+ `SortView.exe` is the main program, please use it according to the information of it
+ during the executing of this program, user could press ==`Esc`== key to stop this sort
+ the blue data line means it is accessed, and red data line means it is assigned
+ after first scan, count sort is process the array of the count data, program will paint its rate real time
+ you could according to the theory of function `void (DataLine*, DataLine*, SortView*)` to write your own sort function, and then add it to `algo` and `str`, compile and you'll see the effect of your own sort function!
+ `algo` record the association of the key and <sort name, sort function>, `str` record the menu item string, the number from 1 to 9, and the number of last element is 0


+ Excuse me that I know my english is poor... And now I attempt to improve my english, please understand me. (Orz
