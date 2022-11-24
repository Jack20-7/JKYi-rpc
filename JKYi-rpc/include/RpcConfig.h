#ifndef _JKYI_RPC_CONFIG_H_
#define _JKYI_RPC_CONFIG_H_

#include"/home/admin/JKYi-rpc/JKYi/JKYi/config.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/singleton.h"

#include<unordered_map>
#include<string>
#include<vector>


namespace JKYiRpc{

static JKYi::ConfigVar<std::unordered_map<std::string,std::vector<std::string>>>::ptr
   g_rpcConfigs = JKYi::Config::Lookup("server",
                 std::unordered_map<std::string,std::vector<std::string>>(),
                                      "rpc configs");
class JRpcConfig{
public:
    JRpcConfig();
    std::vector<std::string> query(const std::string& name);
private:
    std::unordered_map<std::string,std::vector<std::string>> m_configMap;
};

typedef JKYi::Singleton<JRpcConfig> JRpcConfigMgr;
}
#endif
