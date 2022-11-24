#ifndef  _JKYI_RPC_CONTROLLER_H_
#define  _JKYI_RPC_CONTROLLER_H_

#include"google/protobuf/service.h"

#include<string>

namespace JKYiRpc{

class JRpcController :public google::protobuf::RpcController{
public:
    JRpcController();

    void Reset()override;
    bool Failed()const override;
    std::string ErrorText()const override;
    void SetFailed(const std::string& str)override;

    //not to impletement
    void StartCancel()override;
    bool IsCanceled()const override;
    void NotifyOnCancel(google::protobuf::Closure* callback)override;
private:
    bool m_failed;  //rpc执行过程中是否出现错误
    std::string m_errStr;  //错误对于的信息
};

}

#endif
