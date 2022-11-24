include_directories(include/)
link_directories(../JKYi/lib)

set(SRC_LIST
     RpcConfig.cc
     rpcheader.pb.cc
     RpcChannel.cc
     RpcProvider.cc
     RpcController.cc
     zookeeperutil.cc
   )


add_library(JKYiRpc SHARED ${SRC_LIST})
target_link_libraries(JKYiRpc JKYi)
