
#pragma once

//单目运算符基类
class OperationNodeOne : public Node {
protected:
    //指向与运算符相连的操作数
    Node *input;
public:
    OperationNodeOne(string name, Node *x, const int &this_time) : Node(move(name), this_time), input(x) {}

    void cal() override;

    ~OperationNodeOne() override = 0;
};

//双目运算符基类
class OperationNodeTwo : public Node {
protected:
    //指向与运算符相连的操作数
    Node *input1, *input2;
public:
    OperationNodeTwo(string name, Node *x1, Node *x2, const int &this_time) : Node(move(name), this_time), input1(x1),
                                                                              input2(x2) {}

    void cal() override;

    ~OperationNodeTwo() override = 0;
};

//三目运算符基类：
class OperationNodeThree : public Node {
protected:
    //指向与运算符相连的操作数
    Node *input1, *input2, *input3;
public:
    OperationNodeThree(string name, Node *x1, Node *x2, Node *x3, const int &this_time) : Node(move(name), this_time),
                                                                                          input1(x1), input2(x2),
                                                                                          input3(x3) {}

    void cal() override;

    ~OperationNodeThree() override = 0;
};


class PlusNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class MinusNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class MultipleNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class DivisionNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class MaximumNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class MinimumNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class AverageNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class EqualNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class GreaterAndEqualNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class LessAndEqualNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class NotEqualNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class GreaterNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};

class LessNode : public OperationNodeTwo {
    using OperationNodeTwo::OperationNodeTwo;

    void UpdateValue() override;
};


class SinNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void UpdateValue() override;
};

class LogNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void UpdateValue() override;
};

class ExpNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void UpdateValue() override;
};

class TanhNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void UpdateValue() override;
};

class SigmoidNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void UpdateValue() override;
};


class ConditionNode : public OperationNodeThree {
    using OperationNodeThree::OperationNodeThree;

    void UpdateValue() override;
};

class PrintNode : public OperationNodeOne {
    using OperationNodeOne::OperationNodeOne;

    void cal() override;
};
