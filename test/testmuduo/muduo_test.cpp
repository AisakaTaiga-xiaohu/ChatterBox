/*
muduo网络库给用户提供了两个主要的类
TcpServer ： 用于编写服务器的
TcpClient ： 用于编写客户端程序的

epoll + 线程池
好处：能够把网络I/O的代码和业务代码区分开
    主要任务：用户的连接和断开   用户的可读写事件
    我们不需要关心什么时候会触发事件，这是网络库做的事情，它会自动触发
    我们只需要处理好，事情发送后应该怎么应对
*/
#include <muduo/net/TcpServer.h>
// #include <muduo/base/Logging.h>
// #include <boost/bind.hpp>
#include <functional>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
基于muduo网络库开发服务器程序
1. 组合TcpServer对象
2. 创建EventLoop事件循环对象的指针
3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4. 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理连续读写事件的回调函数
5. 设置合适的服务端线程数量，muduo库会自己分配合适的线程数量
*/
class ChatServer
{

public:
    ChatServer(muduo::net::EventLoop *loop,               // 事件循环
               const muduo::net::InetAddress &listenAddr, // IP+Port
               const string &nameArg);                    // 服务器名称

    void start();

private:
    // 专门处理用户的连接创建和断开
    void onConnection(const muduo::net::TcpConnectionPtr &conn);
    // 专门处理用户的读写事件
    void onMessage(const muduo::net::TcpConnectionPtr &conn, // 连接
                   muduo::net::Buffer *buf,                  // 缓冲区
                   muduo::Timestamp time);                   // 接受到数据的时间信息

    TcpServer _server; // #1
    EventLoop *_loop;  // #2 epoll
};

ChatServer::ChatServer(muduo::net::EventLoop *loop,
                       const muduo::net::InetAddress &listtenAddr,
                       const string &nameArg)
    : _server(loop, listtenAddr, nameArg), _loop(loop)
{
    // 给服务器注册用户连接的创建和断开的回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 给服务器注册用户读写事件回调
    // _server.setMessageCallback(boost::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置服务器端的线程数量 1个I/O线程 3个worker线程
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    cout << "ChatServer - " << conn->peerAddress().toIpPort() << " -> "
         << conn->localAddress().toIpPort() << " is "
         << (conn->connected() ? "online" : "offline") << endl;
    if (!conn->connected())
    {
        conn->shutdown(); // close(fd)
        // _loop->quit();
    }
}

void ChatServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
                           muduo::net::Buffer *buffer,
                           muduo::Timestamp time)
{
    // 接收到所有的消息，然后回显
    string buf = buffer->retrieveAllAsString();
    cout << "recv data :" << buf << "time:" << time.toString() << endl;
    conn->send(buf);
}

int main()
{
    // cout << "pid  = " << getpid();
    muduo::net::EventLoop loop; //  epoll
    muduo::net::InetAddress listenAddr("192.168.190.128", 6000);
    ChatServer server(&loop, listenAddr, "ChatServer");

    server.start(); // listenfd epoll_ctl => epoll
    loop.loop();    // epool_wait以阻塞的方式等待新用户连接，或者读写事件

    return 0;
}
