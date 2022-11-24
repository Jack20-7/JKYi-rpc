#set(SRC_LIST
#    calleruserservice.cc
#    ../user.pb.cc
#    )
set(SRC_LIST
    callerfriendservice.cc
    ../friend.pb.cc
    )

include_directories(/home/admin/JKYi-rpc/JKYi-rpc/include)
include_directories(/home/admin/JKYi-rpc/examples/)

add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer ${LIBS})
