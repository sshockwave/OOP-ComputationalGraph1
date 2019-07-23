#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <sstream>
#include <stack>
#include "graph.h"

using namespace std;

// 返回运算符的操作数个数
int operation_type(string operation);

int main() {
    int n;
    cin >> n;
    Graph tf;
    for (int i = 0; i < n; ++i) {
        string node_name, node_type;
        cin >> node_name >> node_type;    //读入变量信息
        if (node_type == "P") tf.InsertPlaceholder(node_name);
        else if (node_type == "C") {
            float value;
            cin >> value;
            tf.InsertConstant(node_name, value);
        } else if (node_type == "V") {
            float value;
            cin >> value;
            tf.InsertVariable(node_name, value);
        }
    }

    int m;
    cin >> m;
    stack<string> operand_stack;
    for (int i = 0; i < m; ++i) {        //读入结点信息
        string buf;
        getline(cin, buf);
        if (buf.empty()) {        //处理空行
            i--;
            continue;
        }
        stringstream ss(buf);
        string node_name, temp, operation;
        ss >> node_name;
        unsigned int equal_sign_position = buf.find('=');
        ss.clear();
        ss.str(buf.substr(equal_sign_position + 2));
        while (ss >> temp) {
            if (operation_type(temp) == 0) operand_stack.push(temp);
            else operation = temp;
        }
        int type = operation_type(operation);
        if (type == 1) {
            tf.InsertOperation(node_name, operation, operand_stack.top());
            operand_stack.pop();
        } else if (type == 2) {
            string right = operand_stack.top();
            operand_stack.pop();
            string left = operand_stack.top();
            operand_stack.pop();
            tf.InsertOperation(node_name, operation, left, right);
        } else if (type == 3) {
            string third = operand_stack.top();
            operand_stack.pop();
            string second = operand_stack.top();
            operand_stack.pop();
            string first = operand_stack.top();
            operand_stack.pop();
            tf.InsertOperation(node_name, operation, first, second, third);
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {        //读入操作信息
        string buf;
        getline(cin, buf);
        if (buf.empty()) {
            i--;
            continue;
        }
        stringstream ss(buf);
        string op;
        ss >> op;
        if (op == "EVAL") {
            string node_name, argument_name;
            ss >> node_name;
            int argument_num = 0;
            ss >> argument_num;
            vector<pair<string, float> > argument_list;
            while (argument_num--) {
                float value;
                ss >> argument_name >> value;
                argument_list.emplace_back(make_pair(argument_name, value));
            }
            tf.Eval(node_name, argument_list);
        } else if (op == "SETCONSTANT") {
            string node_name;
            float value;
            ss >> node_name >> value;
            tf.SetVariable(node_name, value);
        } else if (op == "SETANSWER") {
            string node_name;
            int num;
            ss >> node_name >> num;
            tf.SetVariableByRecord(node_name, num);
        } else if (op == "SETVARIABLE") {
            string node_name, node_from;
            ss >> node_name >> node_from;
            tf.SetVariableByVariable(node_name, node_from);
        } else if (op == "QUERYHISTORY") {
            int num;
            ss >> num;
            tf.QueryHistoryRecord(num);
        } else if (op == "SHOWHISTORY") {
            tf.ShowHistory();
        }

    }
    tf.Clear();
}


int operation_type(string operation) {
    if (operation == "SIN" || operation == "LOG" || operation == "EXP" || operation == "TANH" ||
        operation == "SIGMOID" || operation == "PRINT")
        return 1;
    if (operation[0] == '+' || operation[0] == '-' || operation[0] == '*' || operation[0] == '/' ||
        operation[0] == '>' || operation[0] == '<' || operation[0] == '=' || operation == "MAX" || operation == "MIN" ||
        operation == "AVE")
        return 2;
    if (operation == "COND") return 3;
    return 0;
}
