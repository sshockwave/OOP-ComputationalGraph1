#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "node.h"
#include "operation_node.h"

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::setprecision;
using std::endl;
using std::make_pair;


// Graph类实现对计算图节点的管理以及计算操作的记录

class Graph {
private:
    //管理计算图中的所有结点，同名节点仅保留最新版本
    map<string, Node *> nodes_;

    //存放计算图创建的所有节点地址
    vector<Node *> delete_nodes_list_;

    // 存放计算操作的历史信息 pair->first 存放错误信息
    //                        -1 ：当次操作无异常且无输出
    //                        0 ：当次操作无异常且有输出
    //                        1：当次操作异常，占位符未赋值
    //                        2：当次操作异常，被除数为零
    //                        3：当次操作异常，log真数非正数
    //                        4：当次操作异常，为variable赋值的操作输出在当前操作之后
    //                        5：当次操作异常，为variable赋值的操作无输出
    //                        pair->second 存放正常且有输出的操作的结果
    vector<pair<int, float> > result_;

    //追踪计算操作的次数
    int time_count_ = 0;

public:
    Graph() = default;

    //禁止默认拷贝构造，防止重复delete
    Graph(const Graph &) = delete;

    //禁止默认赋值，防止重复delete
    void operator=(const Graph &) = delete;

    //插入placeholder
    void InsertPlaceholder(const string &node_name);

    //插入constant
    void InsertConstant(const string &node_name, float value);

    //插入variable
    void InsertVariable(const string &node_name, float value);

    //插入一元运算符结点
    void InsertOperation(const string &node_name, const string &operation_type, const string &input);

    //插入二元运算符结点
    void InsertOperation(const string &node_name, const string &operation_type, const string &input1,
                         const string &input2);

    //插入三元运算符结点
    void InsertOperation(const string &node_name, const string &operation_type, const string &input1,
                         const string &input2,
                         const string &input3);

    //进行EVAL操作 输入待EVAL的节点名称 以及placeholder的初始化列表
    void Eval(const string &node_name, const vector<pair<string, float>> &placeholder_initial_list);


    //更改variable的值 输入待更改的节点名称以及要赋的值
    void SetVariable(const string &node_name, float value);

    //更改variable为某次计算操作的结果 输入待更改的节点名称以及计算操作序号
    void SetVariableByRecord(const string &node_name, int history_record);

    //更改variable的值为另一个variable的值
    void SetVariableByVariable(const string &node_name, const string &node_from);

    //显示计算操作的历史记录
    void ShowHistory();

    //查询某次计算操作的结果
    void QueryHistoryRecord(int history_record);

    //清空计算图
    void Clear();

    ~Graph();
};
