#include"RpcConfig.h"
#include"user.pb.h"
#include"RpcChannel.h"

#include<iostream>

using namespace JKYiRpc;

int main(int argc,char** argv){
    JRpcConfigMgr::GetInstance();

    fixbug::UserServiceRpc_Stub stub(new JRpcChannel());

    fixbug::LoginRequest request;
    request.set_name("wcy");
    request.set_pwd("123");

    fixbug::LoginResponse response;
    
    //调用rpc调用
    stub.Login(nullptr,&request,&response,nullptr);

    if(0 == response.result().errcode()){
        std::cout << "rpc response success: " << response.success() << std::endl;
    }else{
        std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
    }

    fixbug::RegisterRequest req;
    req.set_id(1);
    req.set_name("wcy");
    req.set_pwd("123");

    fixbug::RegisterResponse rsp;

    stub.Register(nullptr,&req,&rsp,nullptr);

    if(0 == rsp.result().errcode()){
        std::cout << "rpc register response success:" << rsp.success() << std::endl;
    }else{
        std::cout << "rpc register response error:" << rsp.result().errmsg() << std::endl;
    }

    return 0;
}
