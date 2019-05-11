## Assignment Project: Static Computing Graph
本代码仓库为2019年春季学期清华大学面向对象的程序设计基础课程大作业的代码。  
This repo is the course project of Tsinghua University OOP course (2019 Spring).

#### ☆Please do not copy it for your assignment! (if you are in the same course)  请勿抄袭本代码！

### Note!!!  注意事项
#### Runtime Environment  运行环境
- Operating System : Linux - Ubuntu 16.04
- Compiler g++ (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609

### Problem Description 题目
#### First Stage Requirement 第一阶段需求：(ddl: 5th May 2019)
#### A. Nodes
1. Placeholder.
2. Constant.
3. Variable
3. Other (intermediate or output) nodes.

##### Requirement:
1. Data type = float (4 decimal digits when output). Shape = scalar. 
2. Each node has its own name.
3. Value assignment:   
Placeholder is assigned when EVAL nodes;   
Constant is assigned when building the graph and never changes;   
Variable is assigned when building the graph but can be changed by SET commands (see B.4.);  
Other nodes are not assigned but get their value by evaluation (using EVAL command).  


#### B. Commands
1. Construct and EVAL the graph  
```
3         // the number of Placeholders, Constants and Variables   
x P       // x is a Placeholder  
y V 1.0   // y is a Variable with initial value 1.0  
z C 3.0   // z is a constant with constant value 3.0  
4           // the number of other nodes  
a = x + y   // [name] = [the formula to get its value]  
b = SIN z   // the math functions will be described below  
res = a * b // the name of a   
2                 // the number of the nodes to evaluate  
EVAL x 1 x 1.0    // EVAL [name] [the number of placeholder value assignment] [name1] [value1] [name2] [value2] ...  
EVAL b 0  
  
// output:   
// 1.0000  
// 0.1411  
```

2. Math functions  
a. Plus(+), minus(-), multiply(\*), divide(/). This needs to be implemented by overloading.  
b. SIN, LOG, EXP, TANH, SIGMOID.  
c. Comparations >, <, >=, <=, ==. Returns 1.0 if true, else 0.0.  
*Note: Needs to output error info when division by 0 and log(x<=0)

3. PRINT [name]  
Sets a flag. When evaluating, the corresponding node will output its value.
```
1
x C 3.0
1
a = x   // Same as a = x, but when evaluating, node c will output its value.
1
EVAL a 0

// output: 
// Print Operator: x=3.0
// 3.0000
```
4. SET commands  
a. SETCONSTANT [v] [n]: changes v's value into n.  
b. SETANSWER [v] [i]: sets v's value as the ith operation's result.  
```
2
x P
y V 1.0
1
res = x + y
4
SETCONSTANT y 3.0   // 1st operation: y = 3.0
EVAL res 1 x 2.0    // 2nd operation: outputs 5.0000
SETANSWER y 2       // 3rd operation: y = 5.0
EVAL res 1 x 2.0    // 4th operation: outputs 7.0000
```
5. Condition statement
COND [condition] [return1] [return2]    
If condition > 0, returns return1; else, returns return2.    
Example:```res = COND b a c```(If b > 0, res = a; else, res = b)

#### C. Other requirement
1. Use OOP.
2. Output Error information for (1) division by zero (2) Placeholder missing
3. Show Error information for (1) Division b zero (2) log nonpositive (3) Placeholder missing (needs more input to get output).
4. High efficiency. When computing large graph, avoid computing unchanged nodes more than one time.
5. Reusable for later cross development.
