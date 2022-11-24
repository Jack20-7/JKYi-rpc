#include"RpcChannel.h"
#include"rpcheader.pb.h"
#include"zookeeperutil.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/Logging.h"

#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>

using namespace JKYi;
using namespace JKYi::net;
using namespace JKYiRpc;


//主要就是用来对调用的rpc调用的参数进行打包、序列化等操作
void JRpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                             google::protobuf::RpcController* controller,
                             const google::protobuf::Message* request,
                             google::protobuf::Message* response,
                             google::protobuf::Closure* done){

    const google::protobuf::ServiceDescriptor* sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    uint32_t args_size = 0; //记录参数的大小
    std::string args_str;  //保存序列化的参数
    if(request->SerializeToString(&args_str)){
        args_size = args_str.size();
    }else{
        controller->SetFailed("serialize request error");
        return ;
    }

    JKYiRpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);

    uint32_t header_size = 0;
    std::string rpc_header_str;   //保存序列化后的rpcheader
    if(rpcHeader.SerializeToString(&rpc_header_str)){
        header_size = rpc_header_str.size();
    }else{
        controller->SetFailed("serialize rpc header error");
        return ;
    }

    std::string send_rpc_str;
    send_rpc_str.insert(0,std::string((char*)&header_size,4));
    send_rpc_str += rpc_header_str;
    send_rpc_str += args_str;

    //打印信息
    LOG_DEBUG << " -------------------------------------------";
    LOG_DEBUG << "header_size = " << header_size;
    LOG_DEBUG << "rpc_header_str " << rpc_header_str;
    LOG_DEBUG << "service_name = " << service_name;
    LOG_DEBUG << "method_name = " << method_name;
    LOG_DEBUG << "args_str = " << args_str;
    LOG_DEBUG << " -------------------------------------------";

    //由于涉及到要将产生的字节流发送给目标服务器，所以需要先向ZK查询目标服务器的地址
    ZKClient zkCli;
    zkCli.start();

    std::string path = "/" + service_name + "/" + method_name;
    std::string data = zkCli.getData(path.c_str());
    if(data.empty()){
        controller->SetFailed(path + "is not exist");
        return ;
    }
    int idx = data.find(":");
    if(idx == -1){
        controller->SetFailed(path + " address is invalid");
        LOG_ERROR << "Invalid address:" << data;
        return ;
    }

    std::string ip = data.substr(0,idx);
    uint16_t port = atoi(data.substr(idx + 1,data.size() - idx).c_str());

    int clientFd = socket(PF_INET,SOCK_STREAM,0);
    if(-1 == clientFd){
        LOG_ERROR << "client socket error,errno = " << errno;
        controller->SetFailed("socket create error");
        return ;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(port);

    if(-1 == connect(clientFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr))){
        close(clientFd);
        LOG_ERROR << "clientFd connect error,errno = " << errno;
        controller->SetFailed("socket connected error");
        return ;
    }

    if(-1 == send(clientFd,send_rpc_str.c_str(),send_rpc_str.size(),0)){
        close(clientFd);
        LOG_ERROR << "clientFd send message error";
        controller->SetFailed("socket send message error");
        return ;
    }

    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientFd,recv_buf,1024,0))){
        close(clientFd);
        LOG_ERROR << "clientFd recv message error";
        controller->SetFailed("socket recv message error");
        return ;
    }

    //对服务器返回的数据进行反序列化
    if(!response->ParseFromArray(recv_buf,recv_size)){
        close(clientFd);
        LOG_ERROR << "parse response error,errno = " << errno;
        controller->SetFailed("parse response error");
        return ;
    }

    close(clientFd);
    return ;
}
