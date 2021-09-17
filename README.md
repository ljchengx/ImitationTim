### cpp windows开发入门作业

> **介绍**

cpp入门学习阶段性作业，主要使用cpp语言和Duilib框架，完成模拟登录账号的完整流程。

> **流程介绍**

- 用户打开exe文件，显示登录页面
- 输入账号，密码完成网络请求，具有简单校验
- 支持账号密码记录，记住密码后下次打开读取记录信息，无需输入账号密码
- 支持登录方式切换，切换微信登录后展示生成二维码 模拟微信登录
- 登录完成后，跳转新窗口，展示主页，列表和点击事件

> **技术实现和总结**

1、Duilib框架作为窗体支持 完成窗体的创建，输入框、按钮、提示、消息处理等操作

2、cpp语言为主体，自定义类 结构体 虚函数 封装util使用

3、使用libUrl完成网络请求封装实现发送http请求

4、使用json.app和rapidjson两种反序列化方式完成接口获取json解析类和结构体

5、使用ini文件记录用户是否保存密码状态

6、使用sqlite数据库，存储用户信息，完成写入和读取数据库数据

7、接入qrcode完成二维码创建 使用bitmap完成bmp文件读取，动态设置Duilib UI控件的背景图片

8、创建子线程模拟微信登录状态获取，通过自定义消息完成窗体Ui变化。


