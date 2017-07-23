LED点阵屏显示算法
===

LED点阵屏显示算法，包含左移、右移、上移、下移、激光、画卷、雪花、跑马灯等特效。全部代码用C语言写成，本意是用在嵌入式设备上，但是算法部分与显示部分是独立的，所以理论上可运行在支持ANSI C编译器的任何平台上。

为了演示效果，可以在UNIX/Linux/Mac平台的终端上运行，运行前需确保已安装ncurses库，以ubuntu为例，安装方法为在终端上输入：

```
$ sudo apt-get install libncurses5-dev
```

安装完成后，分别执行make clean和make命令(现已生成的可执行文件为Mac环境下生成，Mac用户可尝试跳过此步骤)：

```
$ make clean
$ make
```

随后执行目录下生成的ledsim即可：

```
$ ./ledsim
```

---