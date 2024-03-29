> 代码中的头文件数目、类的数目过多
>
> ——B组

头文件、类的数目应由实际情况决定而不应是简单地越少越好。经过再次检查，我们认为创建的每个类的含义清晰、作用明确，不存在可合并或可省略的情况。

我们创建的几个头文件分别负责基础类的声明、运算符的声明、图的管理。我们认为现有代码保证了各个模块在不符合实际需求的时候可以被随时替换或扩展；但为了代码可维护性，使用场景相近的内容也已经被合并在了同一份文件中。对于`arithmetics`模块，一般使用了加法的场景，也会使用减法；使用了`arithmetics`中的运算，却未必希望使用`Graph`中定义的功能较为有限的图管理系统。如果觉得从外部调用需要麻烦地引入若干头文件，可以直接使用预定义好的快捷方式`cgraph.h`一次性引入该计算图库所有头文件。

虽然头文件和类的数目的好坏是较为主观的评价，但综合以上两点，我们认为“过多”这一说法有失偏颇。

> 有些类中的成员个数很少且功能过于单一(如Error)，增加了阅读和整体把握代码结构的难度。
>
> ——B组

我们不认为这里存在因果关系。事实上，许多大量使用的库（如STL）中包含大量完全没有成员变量，只有一两个成员函数。在这里，`Error`类的作用主要是标识和区分，为异常处理机制提供方便，它本身并不需要起到存储或完成任务的作用。

另一方面，功能单一是单一职责原则的一个体现。异常处理机制中，我们甚至考虑过给每一种错误建一个类。这会确实导致类的数量变多，但为了可维护性和鲁棒性，我们认为稍长的代码是可以接受的代价。

> 节点计算时用expression来包装不明白它的好处，反而增大了扩展的难度；
>
> ——C组
>
> 这三个类的对象均可以转为Expression对象以支持在Expression上定义好的加减乘除等运算。  不如直接是node？
>
> ——D组

Expression和指向Node的指针是不同的两个概念。Expression的作用是调度计算，Node是底层进行计算时实际占用内存的结构，shared_ptr只是指向Node的指针。在C++中，指针的运算符不能被重载，即使智能指针的运算符能被重载，我们也应该遵守这一规则。

一方面，需要添加功能时，指针是写死不能改的，而在Expression类上就很容易进行扩展，重载运算符，如`expr.eval()`可以计算`expr`的值。另一方面，Expression是一层封装，控制了shared_ptr和Node的访问权限。除非将Expression显式转换成Node指针，否则完全不用关心Expression如何进行计算、计算的状态如何。shared_ptr也含有大量接口，暴露这些接口会给重载的运算符带来歧义，还会给内存安全带来隐患。

> visted与version两个标记作用有重叠，两者各自的作用不清晰；
>
> ——C组

visited和version两个标记的作用都是提高运算效率，但是具有不一样的含义。visited的意思是在该轮是否访问过，这是为了防止在同一轮计算中多次访问同一节点（及其后继），决定的是要不要继续沿着这个节点搜索下去；version的意思是最后一次被更新的时间，一个节点如果计算依赖的节点没有变化，那也就不用重新计算，这决定的是要不要进行这个节点对应的计算。

> 计算结果的记录是在主程序中实现的，没有封装到类中；
>
> ——C组
>
> main.cpp中的代码有点冗长，关于交互的部分也可以进行封装，与Graph有关的函数可以放到相应的头文件中。
>
> ——E组

根据我们对实验要求的理解，我们需要设计的是计算图库，主程序只用于单元测试。虽然封装起来没有什么坏处，但是既然代码不长、也不需要复用，最后还是优先了可读性和开发速度。

> 对于父类的利用不充分，Expression、Placeholder、Constant、Variable四个类都为Node的子类，但是Graph中分别使用了四个map分别存储着四个类型的点，还用了两组函数来进行操作，函数的实现方法是定义一个模板函数来对四个函数分别进行实现，个人认为这里应该充分利用Node类来完成这一操作。也有利于后续增加新的类。
>
> ——D组

首先，Expression类是管理了Node类，具体实现为一个指向Node类的指针，而不是Node类的子类。如果要利用父类，那么就要使用`dynamic_cast`等方法，有待商榷。

很遗憾，我们也考虑过使用模板函数，但我们没有找到在C++中定义成员变量模板的方法。值得一提的是，普通的变量模板在C++14中被引入。

> 增加了阅读和整体把握代码结构的难度
>
> ——B组
>
> * 说明文档不够详细；
> * 部分函数程序中没有使用到，也没说清楚可能的用法和设置这些函数的目的；
>
> ——C组
>
> 部分cpp中注释较少，有些影响阅读体验。
>
> ——E组

抱歉给大家带来了困扰，下次争取做得更好。
