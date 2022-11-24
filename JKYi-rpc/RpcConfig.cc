#include"RpcConfig.h"
#include"/home/admin/JKYi-rpc/JKYi/JKYi/config.h"

using namespace JKYiRpc;

void loadConfig(){
      JKYi::Config::LoadFromConfDir("conf",true);
}
JRpcConfig::JRpcConfig(){
    loadConfig();
    m_configMap = g_rpcConfigs->getValue();
}

std::vector<std::string> JRpcConfig::query(const std::string& name){
    auto it = m_configMap.find(name);
    if(it == m_configMap.end()){
        return {};
    }
    return it->second;
}
