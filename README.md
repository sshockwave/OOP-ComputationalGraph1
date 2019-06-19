# OOP计算图大作业

项目地址：https://github.com/sshockwave/OOP-ComputationalGraph1

测试状态：[![CircleCI](https://circleci.com/gh/sshockwave/OOP-ComputationalGraph1/tree/master.svg?style=svg)](https://circleci.com/gh/sshockwave/OOP-ComputationalGraph1/tree/master)

## 文档

对第一阶段互评提出的异议见[doc/第一阶段互评/objections.md](doc/第一阶段互评/objections.md)。

第二阶段实现文档见[doc/第二阶段扩展说明.md](doc/第二阶段扩展说明.md)。

## 编译代码

支持在Windows和Linux下编译，需要安装至少支持C++14的g++和make。

运行：
```bash
make
```
即可完成编译。

有可能需要根据运行环境设置Makefile中的`$(CXX)`变量，该变量为使用的编译器可执行文件。可以在`Makefile`中调整编译选项`$(CXX_FLAGS)`。

程序生成步骤：
1. 生成`.d`依赖关系文件到`dep/`目录；
2. 再生成`.o`二进制文件到`bin/`中；
3. 生成各个任务的主程序为`test/{task_name}/main`；其中`{task_name}`为任务名称，具体实现了的任务见文档和`test/`目录。

## 运行程序

基础部分的三个程序`main1`、`main2`、`main3`在项目根目录下生成。其他程序见对应`test`目录。

```bash
# 运行第一阶段程序
./main1
# 运行第二阶段程序
./main2
# 运行牛顿迭代法
./main3
```

## 测试程序

自动化测试需要在linux环境下进行。

运行
```bash
make test
```
即可对所有数据进行测试。

如需单独测试：
```bash
# 测试第一阶段程序
make test/stage1/run
# 测试第二阶段程序
make test/stage2/run
# 测试牛顿迭代法
make test/newton/run
```
