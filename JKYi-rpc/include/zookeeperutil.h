#ifndef _JKYI_RPC_ZOOKEEPERUTIL_H_
#define _JKET_RPC_ZOOKEEPERUTIL_H_

#include"/usr/local/include/zookeeper/zookeeper.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/Logging.h"

#include<string>

namespace JKYiRpc{

//对zookeeper的客户端进行封装,zookeeper用于保存注册的 服务名-方法名  : ip + port
class ZKClient{
public:
    ZKClient();
    ~ZKClient();

    //连接上ZKServer
    void start();

    //在zkserver的path路径下上创建一个znode
    void create(const char* path,const char* data,int datalen,int state = 0);

    //返回某一个节点的值
    std::string getData(const char* path);
private:
    zhandle_t* m_zhandle;  //操作的句柄
};

}
#endif
