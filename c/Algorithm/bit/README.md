bit operation
====

#### confusion point ####

1.	在使用setbit函数的时候，我测试使用的数据为unsigned char\*指针初始化一个字符，导致在修改时产生segment fault， 原因是初始化的字符是直接存储在rodata区域是无法修改，最后使用数组解决这个问题

#### screenshot ####

![bit_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/bit/bit_1.png)
