# ChatterBox
Cluster chat server and client source code that can work in nginx tcp load balancing environment based on muduo

## 技术栈

- `Json`序列化和反序列化
- `muduo`网络课开发
- `nginx`源码编译安装和环境部署
- `nginx`的`tcp`负载均衡器配置
- `redis`缓存服务器编程实践
- 基于发布-订阅的服务器中间件`redis`消息队列编程实践
- `MySql`数据库编程
- `CMake`构建编译环境
- `Github`托管项目  

## 开发环境

1. `ubuntu linux`环境
2. 安装`Json`开发库
3. 安装boost + muduo网络库开发环境，参考博客，https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980  
4. 安装`redis`环境
5. 安装`mysql`数据库环境
6. 安装`nginx`
7. 安装`CMake`环境


## 数据库设计

### 表设计

**User表**

| 字段名称 | 字段类型                  | 字段说明     | 约束                        |
| -------- | ------------------------- | ------------ | --------------------------- |
| id       | INT                       | 用户id       | PRIMARY KEY、AUTO_INCREMENT |
| name     | VARCHAR(50)               | 用户名       | NOT NULL, UNIQUE            |
| password | VARCHAR(50)               | 用户密码     | NOT NULL                    |
| state    | ENUM('online', 'offline') | 当前登录状态 | DEFAULT 'offline'           |

**Friend表**

| 字段名称 | 字段类型 | 字段说明 | 约束               |
| -------- | -------- | -------- | ------------------ |
| userid   | INT      | 用户id   | NOT NULL、联合主键 |
| friendid | INT      | 好友id   | NOT NULL、联合主键 |

**AllGroup表**

| 字段名称  | 字段类型     | 字段说明   | 约束                        |
| --------- | ------------ | ---------- | --------------------------- |
| id        | INT          | 组id       | PRIMARY KEY、AUTO_INCREMENT |
| groupname | VARCHAR(50)  | 组名称     | NOT NULL,UNIQUE             |
| groupdesc | VARCHAR(200) | 组功能描述 | DEFAULT ''                  |

**GroupUser表**

| 字段名称  | 字段类型                  | 字段说明 | 约束               |
| --------- | ------------------------- | -------- | ------------------ |
| groupid   | INT                       | 组id     | NOT NULL、联合主键 |
| userid    | INT                       | 组员id   | NOT NULL、联合主键 |
| grouprole | ENUM('creator', 'normal') | 组内角色 | DEFAULT ‘normal’   |

**OfflineMessage表**

| 字段名称 | 字段类型     | 字段说明                   | 约束     |
| -------- | ------------ | -------------------------- | -------- |
| userid   | INT          | 用户id                     | NOT NULL |
| message  | VARCHAR(500) | 离线消息（存储Json字符串） | NOT NULL |
