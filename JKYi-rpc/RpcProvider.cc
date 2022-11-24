#include"RpcProvider.h"
#include"RpcConfig.h"
#include"rpcheader.pb.h"
#include"zookeeperutil.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/Logging.h"

#include<vector>

using namespace JKYiRpc;
using namespace JKYi;
using namespace JKYi::net;

JRpcProvider::JRpcProvider(EventLoop* loop)
    :loop_(loop){
}

//对服务进行注册
void JRpcProvider::notifyService(google::protobuf::Service* service){
    ServiceInfo service_info;
    const google::protobuf::ServiceDescriptor* sd = service->GetDescriptor();
    std::string service_name = sd->name();
    int methodCount = sd->method_count();

    for(int i = 0;i < methodCount;++i){
        const google::protobuf::MethodDescriptor* md = sd->method(i);
        std::string method_name = md->name();
        service_info.methodsMap.insert({method_name,md});
    }
    LOG_DEBUG << "service:" << service_name 
              << " register success";
    service_info.service = service;
    m_servicesMap.insert({service_name,service_info});
}

//启动rpc节点
void JRpcProvider::run(){
   std::vector<std::string> addrs = 
               JRpcConfigMgr::GetInstance()->query("RpcServers");

   //默认使用第一个rpc server
   std::string host = addrs[0];

   using std::placeholders::_1;
   using std::placeholders::_2;
   using std::placeholders::_3;

   //将当前注册的服务信息推送到zookeeper服务器上去
   ZKClient zkCli;
   zkCli.start();

   for(auto& i : m_servicesMap){
       std::string service_path= "/" + i.first;
       zkCli.create(service_path.c_str(),nullptr,ZOO_EPHEMERAL);  //创建服务节点
       for(auto& m : i.second.methodsMap){
           std::string method_path = service_path + "/" + m.first;
           zkCli.create(method_path.c_str(),host.c_str(),strlen(host.c_str()),
                          ZOO_EPHEMERAL);
       }
   }

    Address::ptr serverAddr = Address::LookupAnyIPAddress(host);
    TcpServer server(loop_,serverAddr,"RpcServer");
    server.setConnectionCallback(
            std::bind(&JRpcProvider::onConnection,this,_1));
    server.setMessageCallback(
            std::bind(&JRpcProvider::onMessage,this,_1,_2,_3));

    LOG_DEBUG << "RpcServer start,host = " << host;

    server.start();

    loop_->loop();
}

void JRpcProvider::onConnection(const TcpConnectionPtr& conn){
    if(!conn->connected()){
        conn->shutdown();
    }
}

void JRpcProvider::onMessage(const TcpConnectionPtr& conn,
                               Buffer* buf,
                               Timestamp recviveTime){

    std::string recv_buf = buf->retrieveAllAsString(); 

    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size,4,0);  //读出header的长度

    std::string rpc_header_str = recv_buf.substr(4,header_size);
    JKYiRpc::RpcHeader rpcHeader;

    std::string service_name;
    std::string method_name;
    uint32_t args_size = 0;
    if(rpcHeader.ParseFromString(rpc_header_str)){
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    }else{
        LOG_ERROR << "rpcHeader parseFromString error";
        return ;
    }

    std::string args_str = recv_buf.substr(4 + header_size,args_size);

        //打印信息
    LOG_DEBUG << " -------------------------------------------";
    LOG_DEBUG << "header_size = " << header_size;
    LOG_DEBUG << "rpc_header_str " << rpc_header_str;
    LOG_DEBUG << "service_name = " << service_name;
    LOG_DEBUG << "method_name = " << method_name;
    LOG_DEBUG << "args_str = " << args_str;
    LOG_DEBUG << " -------------------------------------------";

    auto it = m_servicesMap.find(service_name);
    if(it == m_servicesMap.end()){
       LOG_ERROR << "service name = " << service_name << " is not existe";
       return ;
    }

    auto mit = it->second.methodsMap.find(method_name);
    if(mit == it->second.methodsMap.end()){
        LOG_ERROR << "method name = " << method_name  << " is not exists";
        return ;
    }
    const google::protobuf::MethodDescriptor* method = mit->second; //需要调用的方法
    google::protobuf::Service* service = it->second.service;

    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str)){
        LOG_ERROR << "request parseFromString error";
        return ;
    }

    google::protobuf::Message* response = service->GetResponsePrototype(method).New();

    //注册一个调用完指定函数之后的回调函数
    google::protobuf::Closure* done = 
              google::protobuf::NewCallback<JRpcProvider,
                                            const TcpConnectionPtr&>
                                                (this,&JRpcProvider::sendRpcResponse,
                                                 conn,
                                                 response);
    service->CallMethod(method,nullptr,request,response,done);
}

//该回调函数的作用就是将结果序列化后返回给客户端
void JRpcProvider::sendRpcResponse(const TcpConnectionPtr& conn,
                                       google::protobuf::Message* response){
    std::string response_str;
    if(response->SerializeToString(&response_str)){
        conn->send(response_str);
    }else{
        LOG_ERROR << "sendRpcResponse send response error";
    }
    conn->shutdown(); //采用的短连接
}


