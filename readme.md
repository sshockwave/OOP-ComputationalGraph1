# OOP计算图大作业

库相关文档见`doc/`目录。

## 编译代码

支持在Windows和Linux下编译。

需要安装至少支持C++14的g++和make。

```bash
make
```

有可能需要根据运行环境设置Makefile中的`$(CXX)`变量。

Makefile生成步骤：
1. 生成`.d`依赖关系文件到`dep/`目录；
2. 再生成`.o`二进制文件到`bin/`中；
3. 最终程序生成为`main`。

可以在`Makefile`中调整编译选项`$(CXX_FLAGS)`。

## 运行程序

```bash
make run
```
或直接运行：
```bash
./main
```
从stdin读入，stdout输出。

## 测试程序

所有的测试用例都放在了`test/`目录下。
```bash
make test
```
或者运行
```bash
./test.sh
```
即可对所有数据进行测试。

注意，该脚本仅支持Linux。
