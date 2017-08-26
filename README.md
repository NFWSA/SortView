# 排序算法可视化工具

## 需求环境
### 依赖
+ [ege](https://github.com/misakamm/xege)库13.04版本及以上

### 示例编译平台
+ Windows 7 x64 Ultimate Sevice Pack 1
+ mingw-w64-x86_64-g++
+ ege library 15.04

## 用法
### 相关文件
+ `MakeIn.bat`用于生成输入数据文件`in.txt`，双击后请输入数据数量
+ 同目录`in.txt`内为输入数据，第一行为数据量，此后每行是一个数据，其值范围为[1，690]

### 使用说明
+ `SortVisualizer.exe`为主程序，请根据程序提示进行输入
+ 程序执行过程中，可以按==`Alt+F4`==结束本次运行
+ 蓝色表示被扫描的数据，红色表示被选中等待处理的数据
+ 计数排序的二次扫描那个过程实际上是在进行计数数组的处理，显示为扫描过程是为了更直观的感受消耗时间，其实际扫描数据组只有一次
+ 您可以写好自己的排序过程，然后稍加修改加入到里面就可以看到你自己的排序程序的大概运行情况

# Sort algorithm visualized program

## Requirements
### Librarys
+ [ege library](https://github.com/misakamm/xege) 13.04+

### Sample compile platform
+ Windows 7 x64 Ultimate Sevice Pack 1
+ mingw-w64-x86_64-g++
+ ege library 15.04

## Usage
+ `MakeIn.bat`用于生成输入数据文件`in.txt`，双击后请输入数据数量
+ 同目录`in.txt`内为输入数据，第一行为数据量，此后每行是一个数据，其值范围为[1，690]

## 执行说明
+ SortView.exe为主程序，请根据程序提示进行输入
+ 程序执行过程中，可以按==`Alt+F4`==结束本次运行
+ 蓝色表示被扫描的数据，红色表示被选中等待处理的数据
+ 计数排序的二次扫描那个过程实际上是在进行计数数组的处理，显示为扫描过程是为了更直观的感受消耗时间，其实际扫描数据组只有一次
+ 您可以写好自己的排序过程，然后稍加修改加入到里面就可以看到你自己的排序程序的大概运行情况
