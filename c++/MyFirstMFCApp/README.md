### Simple Process explore ###

使用MFC写的一个小工具

### Description:

- 分别通过ToolHelp系列的函数、EnumProcess系列的函数以及NtQuerySystemInformation三种方式来获取进程列表（不过进程的image path还是需要使用getprocessimagefilename来获取）
- 通过ToolHelp系列的函数和EnumProcess系列的函数获取指进程的模块列表

### todolist:

- <del>查看相关进程的模块信息</del>
- 将kernel path转化为NT路径格式
- 窗体和控件同比例放大/缩放
- 通过计时器定时更新进程列表
- 挂起、结束、恢复进程

screenshoot:

![i](https://github.com/pench3r/Program-Study/blob/master/c%2B%2B/MyFirstMFCApp/image1.png)
