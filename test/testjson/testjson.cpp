#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// json序列化实例1
string func1()
{
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello , what are you doing now?";

    string sendBuf = js.dump();
    // cout << js << endl;
    // cout << sendBuf.c_str() << endl;
    return sendBuf;
}

// json序列化实例2
string func2()
{
    json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["wang san"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"wang san", "hello china"}};
    // cout << js << endl;
    return js.dump();
}

// json序列化实例3
string func3()
{
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    js["list"] = vec;

    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "泰山"});
    m.insert({3, "华山"});
    js["path"] = m;

    // json数据对象 -》 序列化json字符串
    string sendBuf = js.dump();
    // cout << sendBuf.c_str() << endl;
    return sendBuf;
}

int main()
{

    // func2();
    // func3();
    string recvBuf = func3();
    // 数据的反序列化 json字符串=》反序列化 数据对象(看作容器，方便访问)
    json buf = json::parse(recvBuf);
    // cout << buf["msg_type"] << "\n"
    //      << buf["from"] << "\n"
    //      << buf["to"] << "\n"
    //      << buf["msg"] << endl;

    // cout << buf["id"] << endl;
    // auto arr = buf["id"];
    // cout << arr[2] << endl;

    // auto msgjs = buf["msg"];
    // cout << msgjs["zhang san"] << endl;
    // cout << msgjs["wang san"] << endl;

    vector<int> vec = buf["list"];  // js对象里面的数据类型，直接放入vector容器中
    for (int num : vec) cout << num << " ";
    cout << endl;

    map<int, string> mmap = buf["path"];
    for (auto &p : mmap)
    {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}