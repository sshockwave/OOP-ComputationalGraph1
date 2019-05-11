

#include "node.h"

Node::~Node() = default;

float Node::operator+(const Node &x) const {
    return value_ + x.value_;
}

float Node::operator-(const Node &x) const {
    return value_ - x.value_;
}

float Node::operator*(const Node &x) const {
    return value_ * x.value_;
}

float Node::operator/(const Node &x) const {
    if (x.value_ == 0)
        throw 2;                //被除数为0，抛出错误
    return value_ / x.value_;
}

void PlaceholderNode::set_val(float value) {
    value_ = value;
    Update_last_time();
}


void PlaceholderNode::cal() {
    if (OutOfTime())
        throw 1;    //如果placeholder未被赋值，则抛出错误
}

void VariableNode::set_val(float value) {
    value_ = value;
}

