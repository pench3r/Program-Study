oaht: open addressed hash table
====

#### Confusion point ####

1. hash表通过将所有数据都存储在一个表中，通过特定的hash方法根据key来生成unique index，看了有线性hash，和double hash，(k mod size + i) mod 11 和 (k mod size) + i * (1 + k mod (size -2 ))

2. 在实现中没有使用vacated是由于我存储的内容为int所以不需要配置哨兵

#### screenshot ####

![Oaht_screenshot_1](https://github.com/pench3r/Program-Study/blob/master/c/Algorithm/oaht/oaht_1.png)
