### cpp windows开发入门作业

> **介绍**

cpp入门学习阶段性作业，主要使用cpp语言和Duilib框架，完成模拟登录账号的完整流程。

> **流程介绍**

- 用户打开exe文件，显示登录页面
- 输入账号，密码完成网络请求，具有简单校验
- 支持账号密码记录，记住密码后下次打开读取记录信息，无需输入账号密码
- 支持登录方式切换，切换微信登录后展示生成二维码 模拟微信登录
- 登录完成后，跳转新窗口，展示主页，自定义列表展示和点击事件

> **技术实现和总结**

1、Duilib框架作为窗体支持 完成窗体的创建，输入框、按钮、提示、消息处理等操作

2、cpp语言为主体，自定义类 结构体 虚函数 封装util使用

3、自定义ListItem布局，重写xml支持展示头像和细节信息

4、优化普通EditUI布局，支持未输入时默认信息展示，支持设置颜色和文字

5、使用libUrl完成网络请求封装实现发送http请求

6、使用json.app和rapidjson两种反序列化方式完成接口获取json解析类和结构体

7、使用ini文件记录用户是否保存密码状态

8、使用sqlite数据库，存储用户信息，完成写入和读取数据库数据

9、接入qrcode完成二维码创建 使用bitmap完成bmp文件读取，动态设置Duilib UI控件的背景图片

10、创建子线程模拟微信登录状态获取，通过自定义消息完成窗体Ui变化。



**体验账号和流程**

账号：ljchengx

密码：Aa123456



> **流程**

1、下载文件源码，运行Jar文件夹下的jar包 启动服务端接口（需要Java_Home 环境）

```cmd
java -jar CppTest.jar
```

![image-20210917173100539](https://cdn.jsdelivr.net/gh/ljchengx/PicGo/img20210917173107.png)

2、双击bin文件夹下的**ImitationTim.exe** 

![image-20210917173124594](https://cdn.jsdelivr.net/gh/ljchengx/PicGo/img20210917173124.png)

