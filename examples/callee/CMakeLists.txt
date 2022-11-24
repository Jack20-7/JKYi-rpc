#set(SRC_LIST
#    userservice.cc
#    ../user.pb.cc
#   )

set(SRC_LIST
    friendservice.cc
    ../friend.pb.cc
    )

include_directories(/home/admin/JKYi-rpc/JKYi-rpc/include)
include_directories(/home/admin/JKYi-rpc/examples)
include_directories(/home/admin/JKYi-rpc/JKYi/JKYi/reactor)

add_executable(provider ${SRC_LIST})
target_link_libraries(provider ${LIBS})
