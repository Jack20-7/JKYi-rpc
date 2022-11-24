#include"RpcController.h"

using namespace JKYiRpc;

JRpcController::JRpcController()
  :m_failed(false),m_errStr(""){
}

void JRpcController::Reset(){
    m_failed = false;
    m_errStr = "";
}

bool JRpcController::Failed()const{
    return m_failed; 
}

std::string JRpcController::ErrorText()const{
    return m_errStr;
}

void JRpcController::SetFailed(const std::string& str){
    m_failed = true;
    m_errStr = str;
}
void JRpcController::StartCancel(){
}

bool JRpcController::IsCanceled()const{
    return false;
}

void JRpcController::NotifyOnCancel(::google::protobuf::Closure* callback){
}

