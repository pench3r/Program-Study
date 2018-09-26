### Simple Process explore ###

使用MFC写的一个小工具

### Description:

- 分别通过ToolHelp系列的函数、EnumProcess系列的函数以及NtQuerySystemInformation三种方式来获取进程列表（不过进程的image path还是需要使用getprocessimagefilename来获取）
- 通过ToolHelp系列的函数和EnumProcess系列的函数获取指进程的模块列表
- 使用GetModuleFileName来获取NT格式的路径
- 通过WM_SIZE的响应函数来实现窗体和控件大小的更新

### todolist:

- <del>查看相关进程的模块信息</del>
- <del>将kernel path转化为NT路径格式</del>
- <del>窗体和控件同比例放大/缩放</del>
- 通过计时器定时更新进程列表
- 挂起、结束、恢复进程

### 遇到的一些坑:

- 使用EnumProcessModules和createToolhelp32Snapshot在获取Modules时，出现错误299,查明原因是因为程序为32位但是在64位系统上运行所导致的，后续修改生成的程序版本即可修复此bug
- 在实现AutoSize函数的功能时，通过更新对应窗体的Rect然后直接MoveWindow一直失败，通过ScreenToClient更新Rect为窗体坐标后，可正常工作

screenshoot:

![i](https://github.com/pench3r/Program-Study/blob/master/c%2B%2B/MyFirstMFCApp/image1.png)
