#include <iostream>
#include <map>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "Graph.h"

using std::cout;

int main(){

    Graph A;
    //输入常量以及变量结点 
    A.creat_nodes_1();
    //输入带有前驱的结点
    A.creat_nodes_2();
    //操作部分 
    A.commands();


    cout << std::endl;
//    system("pause");
    return 0;
}