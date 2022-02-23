# cpython_Toy

一个为了深入学习 python 而产生的 repo。着重于实现 python 的一些基本的抽象数据类型，使用最简单的方式来实现，至于 interpreter 部分的 parser ，VM 什么的，有空再说。

## 已经实现的类型

- [X] python object. 基本的 object ，其他所有的类都继承
- [X] python type type 类型的类型，最基础的类，所有的用户自定义类型比如 class 继承于此
- [X] python int object 包含 大整数池(linked-list 实现) 和 小整数池(array 实现)
- [ ] python string object
- [ ] as_Number function set for number-like class
