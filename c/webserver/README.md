首先修改WWW_ROOT指定的根目录

1. 编译

```
gcc -o z za.c thread_pool.c parse_http_request.c -lpthread
```

2. 使用root运行

```
sudo ./z
```
