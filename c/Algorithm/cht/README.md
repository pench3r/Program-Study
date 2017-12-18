cht: chained hash table
====

#### Confusion point ####

1. 通过chained single list来保存对应索引的数据

2. 简单的hash function直接通过data % length来确定索引

3. 写的过程中没有什么大问题，在最后使用valgrind的时候发现Uninitialised value was created by a heap allocation， 原因是在chtinit的时候，没有初始化每个list导致

#### screenshot ####

![Cht_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/cht/cht_1.png)
