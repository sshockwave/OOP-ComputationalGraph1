#pragma once
#include <cstring>
#include "point.h"
#include <cmath>
class pc{//short for pointcollection
private:
    int num=0;//记录图中存在的节点数
    int errornum=0;//记录计算过程是否出错
    int opnum=0;//short for operate 操作序号
    float result[6000];//记录每次计算的结果
    point pois[6000];//存储每个节点的信息
    int ifexist(string &nam);//判断并返回某特定名称的结点在pois[]的位置
    float getval(int pos);//计算总函数
    void eval(string c);//eval操作
    void setconstant(string c);//setconstant操作
    void setanswer(string c);//setanswer操作
public:
    void ori();//初始化
    void operate();
};
