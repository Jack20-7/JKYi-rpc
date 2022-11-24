#ifndef _JKYI_RPC_PROVIDER_H_
#define _JKYI_RPC_PROVIDER_H_

#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/TcpServer.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/EventLoop.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/reactor/TcpConnection.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/address.h"

#include"google/protobuf/service.h"
#include"google/protobuf/descriptor.h"

#include<string>
#include<functional>
#include<unordered_map>

namespace JKYiRpc{

class JRpcProvider{
public:
    JRpcProvider(JKYi::net::EventLoop* loop);

    //对服务进行注册
    void notifyService(google::protobuf::Service* service);

    //启动rpc服务器，给客户端提供服务
    void run();

private:
     struct ServiceInfo{
         google::protobuf::Service* service;
         std::unordered_map<std::string,
                 const google::protobuf::MethodDescriptor*> methodsMap;
     };

     void onConnection(const JKYi::net::TcpConnectionPtr& conn);
     void onMessage(const JKYi::net::TcpConnectionPtr& conn,
                    JKYi::net::Buffer* buf,
                    JKYi::net::Timestamp receiveTime);
     void sendRpcResponse(const JKYi::net::TcpConnectionPtr& conn,
                          google::protobuf::Message* response);

     //存放所有注册的服务的信息
     std::unordered_map<std::string,ServiceInfo> m_servicesMap;
     JKYi::net::EventLoop* loop_;
};

}

#endif
