clist
====

#### Confusion point ####

1. 这个circle list实现的比较粗糙，数据的插入比较费劲，如果想插入指定位置必须要先获取对应位置的前一个node指针，然后再调用接口插入。

2. 纠结是否需要tail_clist_node，使用它可以方便在尾部添加数据。

3. 主要练习使用通过node结构体来找位置插入数据。对于方法的实现先考虑普通的场景，再考虑特例其中对于 关键的数据是否变动需要重点考虑（大部分的逻辑错误出现在这个地方）

#### screenshot ####

![Clist_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/clist/clist_1.png)
