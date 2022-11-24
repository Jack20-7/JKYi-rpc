#include"friend.pb.h"
#include"RpcConfig.h"
#include"RpcProvider.h"
#include"Logging.h"
#include"EventLoop.h"

#include<iostream>
#include<vector>
#include<string>

class FriendService : public fixbug::FriendServiceRpc{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid){
        std::cout << "do GetFriendsList service,userid = " << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("wcy");
        vec.push_back("zhangsan");
        vec.push_back("lisi");

        return vec;
    }

    void GetFriendsList(google::protobuf::RpcController* controller,
                         const ::fixbug::GetFriendsListRequest* request,
                         ::fixbug::GetFriendsListResponse* response,
                         ::google::protobuf::Closure* done)override{
        uint32_t userid = request->userid();
        std::vector<std::string> friendslist = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");

        for(const std::string& name : friendslist){
            response->add_friends(name);
        }
        done->Run();
    }
};

int main(int argc,char** argv){
    JKYiRpc::JRpcConfigMgr::GetInstance();//加载配置文件

    JKYi::net::EventLoop loop;
    JKYiRpc::JRpcProvider provider(&loop);
    provider.notifyService(new FriendService());
    provider.run();

    return 0;
}
