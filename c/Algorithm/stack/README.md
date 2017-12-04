stack
====

#### Confusion point ####

1. 针对stack_top值的维护容易混淆，开始使用的stack_base和current_size来计算指向的是第一个未占用的位置，最后发现输出的时候容易越界无法正常使用。最后使用stack_base+current_size-1来指向最后一个占用的地址。

2. 对于buffer为空，或者满的边界操作需要多思考。 

#### screenshot ####

![Stack_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/stack/stack_1.png)
