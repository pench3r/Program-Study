dlist
====

#### Confusion point ####

1. 节点删除, 对于节点删除，考虑头尾节点，以及接近头尾节点的节点，在实现的中间注意数据改变的先手顺序容易产生指针引用错乱，以及注意dlist_head, dlist_tail数据的维护。

2. 对于dlist destory实现, 使用节点删除功能遍历dlist，一开始实现直接使用dlist->size作为了for的判断条件，但是在调用节点删除功能时会改变这个值所以产生了不可预料的结果，使用临时变量保存进行使用。

3. 节点的插入, 考虑节点插入在头尾的情况即可。

#### screenshot ####

![Dlist_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/dlist/dlist_1.png)
