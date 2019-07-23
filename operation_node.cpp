
#include "node.h"
#include "operation_node.h"

OperationNodeOne::~OperationNodeOne() = default;

OperationNodeTwo::~OperationNodeTwo() = default;

OperationNodeThree::~OperationNodeThree() = default;

void OperationNodeOne::cal() {    //递归
    if (OutOfTime()) {    //当前结点本次计算操作未被计算时才计算；保证高效性
        input->cal();
        UpdateValue();
        Update_last_time();
    }
}

void OperationNodeTwo::cal() {
    if (OutOfTime()) {
        input1->cal();
        input2->cal();
        UpdateValue();
        Update_last_time();
    }
}

void OperationNodeThree::cal() {
    if (OutOfTime()) {
        input1->cal();
        input2->cal();
        input3->cal();
        UpdateValue();
        Update_last_time();
    }
}

void PrintNode::cal() {
    if (OutOfTime()) {
        input->cal();
        value_ = input->value();
        std::cout << "PRINT operator: " << input->name() << " = " << std::fixed << std::setprecision(4) << value_
                  << std::endl;
        Update_last_time();
    }
}

void PlusNode::UpdateValue() {
    value_ = *input1 + *input2;
}

void MinusNode::UpdateValue() {
    value_ = *input1 - *input2;
}

void MultipleNode::UpdateValue() {
    value_ = *input1 * *input2;
}

void DivisionNode::UpdateValue() {
    value_ = *input1 / *input2;
}

void EqualNode::UpdateValue() {
    if (input1->value() == input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}

void GreaterAndEqualNode::UpdateValue() {
    if (input1->value() >= input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}

void LessAndEqualNode::UpdateValue() {
    if (input1->value() <= input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}

void NotEqualNode::UpdateValue() {
    if (input1->value() != input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}

void GreaterNode::UpdateValue() {

    if (input1->value() > input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}

void LessNode::UpdateValue() {
    if (input1->value() < input2->value())
        value_ = 1.0;
    else
        value_ = 0.0;
}


void SinNode::UpdateValue() {
    value_ = sin(input->value());
}

void LogNode::UpdateValue() {
    float val = input->value();
    if (val <= 0)
        throw 3;        //参数不在定义域内，抛出错误
    value_ = log(val);
}

void ExpNode::UpdateValue() {
    value_ = exp(input->value());
}

void TanhNode::UpdateValue() {
    value_ = tanh(input->value());
}

void SigmoidNode::UpdateValue() {
    value_ = 1.0 / (exp(-input->value()) + 1.0);
}


void ConditionNode::UpdateValue() {
    if (input1->value() > 0)
        value_ = input2->value();
    else
        value_ = input3->value();
}

void MaximumNode::UpdateValue() {
    value_ = input1->value() > input2->value() ? input1->value() : input2->value();
}

void MinimumNode::UpdateValue() {
    value_ = input1->value() < input2->value() ? input1->value() : input2->value();
}

void AverageNode::UpdateValue() {
    value_ = (input1->value() + input2->value()) / 2;
}
