#pragma once

#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>

using std::string;
using std::move;

//Node类 为所有节点的基类

class Node {
protected:
    //结点数值
    float value_;

    //结点名字
    string name_;

    //结点最后一次被更新的时间
    int last_time_ = 0;

    //本次操作的时间
    const int &this_time_;

public:
    explicit Node(string _name, const int &this_time, float _value = 0) : name_(move(_name)), value_(_value),
                                                                          this_time_(this_time) {}

    float operator+(const Node &x) const;

    float operator-(const Node &x) const;

    float operator*(const Node &x) const;

    float operator/(const Node &x) const;

    //interface of value_
    inline float value() { return value_; }

    //interface if name_
    inline string name() { return name_; }

    //返回true，如果结点上一次更新时间早于本次操作时间
    inline bool OutOfTime() { return last_time_ < this_time_; }

    //更新结点的last_time
    inline void Update_last_time() { last_time_ = this_time_; }

    //节点计算时进行的操作
    virtual void cal() {}

    //节点更新value_的方法
    virtual void UpdateValue() {}

    virtual ~Node() = 0;
};

class VariableNode : public Node {
public:
    VariableNode(string name, float value, const int &this_time) : Node(move(name), this_time, value) {}

    void set_val(float val);
};

class PlaceholderNode : public Node {
public:
    explicit PlaceholderNode(string name, const int &this_time) : Node(move(name), this_time) {}

    void set_val(float val);

    void cal() override;
};

class ConstantNode : public Node {
public:
    ConstantNode(string name, float value, const int &this_time) : Node(move(name), this_time, value) {}
};
