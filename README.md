项目描述：本项目主要实现了 QQ 的注册、登录、获取好友列表、添加好友、删除好友和聊天的功能，同时可以查看好友的在线状态；
使用技术：项目采用 C/S 架构、基于 Windows 操作系统，使用了中介者设计模式，采用 TCP 协议实现局域网聊天传输系统，服务器端通过 MySQL 数据库来保存用户信息，并能把数据库中的信息显示在控件上，使用了多线程技术为每一个连接成功的客户端分配线程，通过 Socket 向服务器发送数据，服务器解析数据包后，根据包头标志实现相应功能。
