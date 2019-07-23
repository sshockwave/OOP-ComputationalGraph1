#include <iostream>
#include <cstring>
#include "point.h"
using namespace std;

void point::set(string a){
    int g=0;
    int len=a.length();
    for(int i=0;i<len;i++)
        if(a[i]==' '){
            g=i;
            break;
        }
    name=a.substr(0,g);//获得节点名称
    type=a[g+1];//获得节点类型
    if(type=="C"||type=="V"){//如果节点是V或C，获得节点的值
        string dd=a.substr(g+3,len-g);
        value=atof(dd.c_str());
        ifcal=1;
    }
}
