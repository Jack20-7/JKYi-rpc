#include"friend.pb.h"
#include"RpcConfig.h"
#include"RpcChannel.h"
#include"RpcController.h"

#include<vector>
#include<string>
#include<iostream>


int main(int argc,char** argv){
    JKYiRpc::JRpcConfigMgr::GetInstance();

    fixbug::FriendServiceRpc_Stub stub(new JKYiRpc::JRpcChannel());

    fixbug::GetFriendsListRequest request;
    request.set_userid(100);
    fixbug::GetFriendsListResponse response;

    JKYiRpc::JRpcController controller;

    stub.GetFriendsList(&controller,&request,&response,nullptr);

    if(controller.Failed()){
        std::cout << "GetFriendsList error,errStr = " << controller.ErrorText();
    }else{
        if(0 == response.result().errcode()){
            std::cout << "rpc GetFriendsList response sussecc!" << std::endl;
            int size = response.friends_size();
            for(int i = 0;i < size;++i){
                std::cout << "index = " << i + 1 << " name = " << response.friends(i) << std::endl;
            }
        }else{
            std::cout <<"rpc GetFriendsList response error,errStr = " << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}
