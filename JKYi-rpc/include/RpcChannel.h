#ifndef _JKYI_RPC_CHANNEL_H_
#define _JKYI_RPC_CHANNEL_H_

#include"google/protobuf/service.h"
#include"google/protobuf/descriptor.h"
#include"google/protobuf/message.h"

namespace JKYiRpc{

class JRpcChannel : public google::protobuf::RpcChannel{
public:
    //在客户端上，所有通过stub调用的rpc函数都会执行到这里
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                      google::protobuf::RpcController* controller,
                      const google::protobuf::Message* request,
                      google::protobuf::Message* response,
                      google::protobuf::Closure* done);
};

}
#endif
