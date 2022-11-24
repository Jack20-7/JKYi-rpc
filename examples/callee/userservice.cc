#include"user.pb.h"
#include"RpcProvider.h"
#include"RpcConfig.h"
#include"EventLoop.h"

#include<iostream>
#include<string>

using namespace JKYiRpc;

//继承自user.proto文件生成的UserServiceRpc
class UserService : public fixbug::UserServiceRpc{
public:
    bool Login(const std::string& name,
                                      const std::string& pwd){
        std::cout << "doing local service : Login" << std::endl;
        std::cout << "name = " << name << " pwd = " << pwd;
        return false;
    }
    bool Register(uint32_t id,const std::string & name,
                                       const std::string& pwd){
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id = " << id << " name = " << name << " pwd = " << pwd;
        return false;
    }

    //下面就是对从UserServiceRpc继承而来的两个虚函数进行重写
    //这样当收到客户端发送来的请求的时候，会根据service的name和method的name找到rpc所在的service和method Descriptor
    //然后在根据service调用->callMethod,在callMethodd中就会根据传入的method的idx调用对应的函数
    void Login(::google::protobuf::RpcController* controller,
                   const ::fixbug::LoginRequest* request,
                   ::fixbug::LoginResponse* response,
                   ::google::protobuf::Closure* done)override{
        std::string name = request->name();
        std::string pwd = request->pwd();

        //调用本地的对应的函数做业务逻辑
        bool login_result = Login(name,pwd);

        //根据调用的结果对返回的响应进行填充
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(5);
        code->set_errmsg("登录失败");
        response->set_success(login_result);

        //调用之前注册好的回调函数，该回调函数会将生成的响应序列化之后返回给客户端
        done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                   const ::fixbug::RegisterRequest* request,
                   ::fixbug::RegisterResponse* response,
                   ::google::protobuf::Closure* done)override{

        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = Register(id,name,pwd);

        response->mutable_result()->set_errcode(2);
        response->mutable_result()->set_errmsg("注册失败");
        response->set_success(ret);

        done->Run();
    }
};

int main(int argc,char** argv){
    JKYiRpc::JRpcConfigMgr::GetInstance();  //记载配置文件

    JKYi::net::EventLoop loop;
    JKYiRpc::JRpcProvider provider(&loop);
    provider.notifyService(new UserService());
    provider.run();
    return 0;
}
