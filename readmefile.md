[TOC]
# 设计思路及库的结构
##节点部分
- 在思考的时候，我们认为Constant、Placeholder、Variable三种类型的变量有着许多的共通点，比方他们都有属于自己的值和变量名，可以相互进行运算等。于是很自然的想到可以以一个基类作为支撑进行实现。为了实现所需要实现的若干功能，我们创建了一个名为Node的节点作为基础，并以Node为基类派生出`ConstantNode、PlaceholderNode、VariableNode`节点，分别与所要求的实现的三种数据类型相对应，通过提供不同的接口，给予不同的函数来实现三者分别作为常量、占位符、变量的区别。  
- 变量的运算是一个较为复杂和繁琐的部分。为了保持高效简介，并且我们分别实现一目、二目、三目运算符，即`OperationNodeOne，OperationNodeTwo，OperationNodeThree`，派生自前文提到的Node节点，作为运算符节点。而加减乘除、三角函数、比较运算等根据运算的变量个数作为一个节点继承自运算符节点，实现相对应的计算。  
**_整体Node类型相关结构_**：
```
class Node;    

class VariableNode : public Node  
class PlaceholderNode : public Node  
class ConstantNode : public Node
class OperationNode***** : public Node  

class ***Node:public OperationNode****

```
即`Node`下有`ConstantNode`、`PlaceholderNode`、`VariableNode`、`OperationNodeOne`、`OperationNodeTwo`、`OperationNodeThree`节点，每个OperationNode节点下有若干运算。  
##计算图部分  
我们把给定的一些变量、运算与操作整合到一个计算图中，符合oop规范且可以建立多张计算图进行操作。在`Graph.h`中我们储存和记录了现有的各种节点（包括变量类型与运算符节点等），为了防止内存泄漏还设立容器进行储存。  
#封装  
##节点部分  
**Node**：类内有变量的值、名称、当前计算次数、整体计算次数
**OperationNodeOne/Two/Three**：含有运算对应所需变量个数的Node*的指针，用以接受传进来的变量。  
##计算图部分
**Graph**：储存了包含所有节点的map：nodes_，记录运算操作及结果的result_,和整体计算次数  
#接口  
##节点部分  
**Node**：  
```
//构造函数
	explicit Node(string _name, const int &this_time,float _value = 0) : name_(move(_name)), value_(_value),this_time_(this_time) {}
	
//重载四则运算
	float operator+(const Node& x) const ;
	float operator-(const Node& x) const ;
	float operator*(const Node& x) const ;
	float operator/(const Node& x) const ;
	
//获取值和名称
	inline float value() { return value_; }
	inline string name() { return name_; }

//检测运算次数如果较小则会进行运算并更新
	inline bool OutOfTime (){ return last_time_ < this_time_;}

	inline void Update_last_time() { last_time_ = this_time_; }
//计算接口
	virtual void cal() {}
	virtual void UpdateValue(){}

	virtual ~Node() = 0;
```
**变量**

```
VariableNode::	void set_val(float val);//赋值接口

PlaceholderNode：：	
void set_val(float val);//赋值接口
void cal() override;//计算接口

ConstantNode：：//dbq没有接口QAQ
```
**OperationNodeOne/Two/Three**：
```
void cal();//计算接口
```
*****Node**
```
    void UpdateValue() //计算
```
##计算图部分
**Graph**：
```
//插入constant、placeholder、variable类型变量
    void InsertPlaceholder(const string &node_name);
    void InsertConstant(const string &node_name, float value);
    void InsertVariable(const string &node_name, float value);

//根据运算符不同插入不同运算节点
    void InsertOperation（+3重载）

//计算表达式
    void Eval(const string &node_name, const vector<pair<string, float>> &placeholder_initial_list);

//variable相关函数
    void SetVariable(const string &node_name, float value);
    void SetVariableByRecord(const string &node_name, int history_record);

```
#bonus部分
```
受到variable指令的启发，我们想到了变量为变量赋值的variable类型指令
//bonus使用变量为变量赋值
    void SetVariableByVariable(const string &node_name, const string &node_from);

为了方便debug和查阅，我们增加此功能
//bonus 显示一条命令中的历史记录
    void ShowHistory();
    float QueryHistoryRecord(int history_record);

//考虑到大部分操作为二目运算且使用上的便捷，我们增加了返回最大/最小/平均值的功能
void MaximumNode::UpdateValue()
void MinimumNode::UpdateValue()
void AverageNode::UpdateValue() 

//清空计算图
    void Clear();
```
