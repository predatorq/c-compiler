# C Compiler
Assignments of Compiler Class in SYSU

## Assignments

- Experiment1: release v1.0
    - output: tokens.txt
- Experiment2: release v2.1(LL(1)) and v2.2(LR(0))
    - output: action_chart1.txt and action_chart2.txt
- Experiment3: release v3.0
    - output: RPN_correct.txt RPN_wrong.txt
- Final Assignment: release v4.0

## Final Assignment

### 基础依赖
源码运行需要安装flex, bison, nasm, make. 如为Ubuntu系统, 代码为:

```
sudo apt-get install flex bison nasm make
```

### 如何运行
- 代码运行需要在源码文件夹目录内运行, 使用 `make` 即可完成所有前后端工作并运行编译出的代码文件.
- `make clean` 可以清除所有的编译中间文件和结果文件.
- `make check` 可以生成展开宏后的汇编代码.


### 文件说明

#### make前文件
- 测试样例为 `samples/demo.c`
- 词法分析flex代码为 `src/scanner.l`
- 语法分析bison代码为 `src/parser.y`
- 目标语言生成(nasm宏代码)为 `src/macro.inc`

#### make后文件
- 中间代码 `samples/demo.asm`
- 符号表 `samples/demo.inc`
- 前端可执行文件 `./tcc-front`
- demo编译后的可执行文件 `./demo`
- 展开宏的汇编代码 `./check.asm`