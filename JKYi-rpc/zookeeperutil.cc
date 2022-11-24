#include"zookeeperutil.h"
#include"RpcConfig.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/CountDownLatch.h"

#include<iostream>
#include<vector>

using namespace JKYi;
using namespace JKYi::net;
using namespace JKYiRpc;

//全局的监视器，当连接建立好时会被触发
void global_watcher(zhandle_t* zh,int type,int state,const char* path,
                       void* watcherCtx){
    if(type == ZOO_SESSION_EVENT){
        if(state == ZOO_CONNECTED_STATE){
            CountDownLatch* latch = (CountDownLatch*)zoo_get_context(zh);
            latch->countDown();
        }
    }
    return ;
}

ZKClient::ZKClient()
  :m_zhandle(nullptr){
}

ZKClient::~ZKClient(){
    if(m_zhandle){
        zookeeper_close(m_zhandle);
    }
}

void ZKClient::start(){
    //从配置中读取到zookeeper服务器的ip+port
    std::vector<std::string> vecs = JRpcConfigMgr::GetInstance()->query("Zookeepers");
    //这里暂时默认选择第一个吧
    std::string host = vecs[0];

    m_zhandle = zookeeper_init(host.c_str(),global_watcher,30000,nullptr,nullptr,0);
    if(nullptr == m_zhandle){
        LOG_ERROR << "zookeeper_init error";
        exit(EXIT_FAILURE);
    }
    JKYi::CountDownLatch latch(1);
    zoo_set_context(m_zhandle,&latch);
    latch.wait();

    LOG_INFO << "zookeeper_init success!";
}

void ZKClient::create(const char* path,const char* data,int dataLen,int state){
    char path_buffer[128];
    int buffLen = 0;
    int flag = 0;

    //首先先判断该节点的值是否存在
    flag = zoo_exists(m_zhandle,path,0,nullptr);
    if(ZNONODE == flag){
        //不存在的话.就创建指定节点
        flag = zoo_create(m_zhandle,path,data,dataLen,&ZOO_OPEN_ACL_UNSAFE,
                             state,path_buffer,buffLen);
        if(flag == ZOK){
            LOG_DEBUG << "znode is created,path = " << path
                      << "  data = " << data;
        }else{
            LOG_ERROR << " znode create error,flag = " << flag
                      << " path = " << path;
            exit(EXIT_FAILURE);
        }
    }
}

std::string ZKClient::getData(const char* path){
    char buffer[64];
    int bufferLen = sizeof(buffer); 
    //也就是zoo_get的第五个参数是用来接收数据的缓冲区的大小
    int flag = zoo_get(m_zhandle,path,0,buffer,&bufferLen,nullptr);
    if(flag == ZOK){
        LOG_DEBUG << "get znode value success,path = " << path
                  << " value = " << buffer;
    }else{
        LOG_ERROR << "get znnode value error,path = " << path
                  << " flag = " << flag;
        return "";
    }
    return buffer;
}


