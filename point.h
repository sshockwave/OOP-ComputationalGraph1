#pragma once
#include <cstring>
#include <iostream>
using namespace std;
class point{
public:
    string name;//节点名称
    string type;//节点类型
    float value;//节点数值
    int position;
    string getway;//该节点经由哪种计算s得到
    int source[3];//该节点经由哪些节点计算得到
    int ifcal;//该节点的值是否已经被算过
    void set(string a);//对节点进行初始化的操作
    int ifori=0;//该节点是否是初始节点
};
