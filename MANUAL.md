# Static Computing Graph - Manual

## Makefile Option
### make (build)
- Compile and link all .h and .cpp files regularly (-O2 -std=c++14).
- Please run ./main after compilation complete.
### make debug
- Debug mode of this project.
- Allow GDB debug in Visual Studio Code .
### make cleanall
- Clean all the .o and main file created during compilation.
### make TAR=test1
- Compile test1.cpp to test high efficiency

## Structure of this Project
### ☆Parser/
- Gets commands & split them into tokens for future use.
#### Parser.h Parser.cpp
1. `operator>>`
- Reads commands from istream and call parse().
2. `split()`
- Splits commands to tokens by spaces.
3. `parse()`
- Calls `split` automatically, identifies the operation and refer to the corresponding functions in Graph, and catches exceptions (see Exception (异常) part). You can add more parse options. See Expansibility (可拓展性) part.

### ☆Graph/
Construciton of the graph, adding nodes and calculation.
#### Value.h Value.cpp
- Currently only scalar type is written and support `float`.
- If you want to expand the type of value, edit `dtype`, `shape` and `stype` before deriving from `Value`. See below and Expansibility (可拓展性) part.
- `dtype`: `char`. Data type, like 'f'loat, 'i'nt (to do).
- `shape`: `vector<int>`. For `Scalar`, `shape` is `{1}`; for 2x2 `Array` (to do), `shape` is `{2, 2}`.
- `stype`: `char`. Shape type, like 'S'calar, 'A'rray (to do).
#### Node.h Node.cpp
- Class Node includes the basic information (`name`, `value`, `updateFlag`), math function (`nullptr` if it is a Placeholder/Variable/Constant), and relationship with other nodes (ancestor/father/child/descendent) of a node.
- Functions in this part is trivial (hahahahaha...)
- **NOTE** `prints` contains nodes that are printed out when this node is `eval`ed by `graph`. See High Efficency (高效性) part.
#### Graph.h Graph.cpp
1. newNode()
- There are 3 overloads of this function. It creates new node in graph.
- `newNode(string name, char ntype, float initValue)` same as below, initial value is `float`.
- `newNode(string name, char ntype, Value *initValue)` is used when PVC nodes are created.
- `newNode(string name, vector<string> fathers, MathFunc *func, bool printFlag)` is used when intermediate nodes are created.
2. editNode()
- There are two overloads of this function, allows editting the node `value` while setting `updateFlag`. As for `updateFlag`, see High Efficency (高效性) part.
3. eval()
- If nessesary placeholders (stored in `Node::ancestors`) are not all assigned, throw an error.
- Edit the value of given nodes if needed.
- Compute using a DFS method (computing the value of fathers and use the function to compute the final value)
- Print the nodes in `prints` if there is any.
- Print eval answer and push it into `ans`.
4. noAnsStep()
- `step ++` is done in eval(), however, if the operation is `SETCONSTANT` or `SETANSWER`, we need a funtion to tell the graph to add step.
- Meanwhile, it pushes a `nullptr` into ans.
#### MathFunc.h Mathfunc.cpp
- Just mathematical functions~
- Rarely used directly in future development.
- If you want to derive more `MathFunc`. See Expansibility (可拓展性) part.

## Interfaces
#### `Graph`
- `newNode`
- `editNode`
- `eval`
- `getAns`: get `ans[step-1]`
- `noAnsStep`: see "Graph.h Graph.cpp, part 4"
#### `Parser`
- `operator>>`
- `parse`: parse given line


## Exception (异常)
- Exceptions are thrown by `throw`, which can easily terminate a bad command.
- Exceptions should be caught by parser before they break down the program.
- Caught exceptions are `string` or `char *`, or invalid_argument (caused by failed stof).

## High Efficency (高效性)
#### timing
- To check the high efficency, use this make command `make TAR=test1`
- Then the program will output time using for `EVAL`, `SETCONSTANT`, and `SETANSWER`.
#### eval and DFScompute
- To avoid redundant computation, every node has a `updateFlag`. `updateFlag=true` means the node needs to be computed.
-  Since the value of a node is changed only when its originally dependence (aka `ancestors`, which are Placeholders/Variables) changes, the `ancestors` determines whether their `descendants` need update.
- The only way to change an ancestor's value is `editNode`, so `editNode` decide `descendants`'s `updateFlag`s.
- `eval` calls `DFScompute` to do deep-first searching until `updateFlag=false` or meeting a PVC node. Then `DFSsearch` calls `compute`, sets `updateFlag=false`, and passes the value back to eval target.
- This makes sure there is less redundant computation since `compute` is only called on update-needed nodes.
#### prints
- Since `updateFlag=false` prevents computing while the node may has `PRINT`, printing need to be done outside `compute`.
- We use space to exchange time. Every node has a `prints`, records the fathers and grandfathers with print. At the end of eval, before printing eval answer, eval will print values of nodes in eval target's prints.

## Expansibility (可拓展性)
#### parser
- As we have done in Parser.h and Parser.cpp, you can set more `mod` of parser, add more `if`, create more `cmdXXX`, and put `cmdXXX` inside `if`s to make `Parser::parse` as clean as possible.
- You can design new exceptions and remember to catch them in `Parser::parse`
#### Value
- `Value` does not store `value`. `value` is stored in derived classes since values may have different types.
- It means to access `value`, you need to cast the pointer of `Value` to a derived class.
- `Value::dtype`, `Value::stype` can tell you which derived class to cast. After adding more types, don't forget to define relavtive `MathFunc::compute`.For example, `+` is different between `Scalar` and `Array`, which means you need to add some codes in `compute`.
#### MathFunc
- There are about 16 `MathFunc`s, so I use macro to shorten my code. 
- To derive `MathFunc` is easy. Follow these steps.
- Use `DERIVE_FROM_MATHFUNC(name)`, a derived class is defined, and its static object `__name__` is created.
- Define your `compute` and `match` in `MathFunc.cpp`. Be careful of segmentation fault.
- Push the new class into `parser.mathFuncs` in constructor `Parser::Parser`, then parser will automatically recognize your `MathFunc`.
