cmake_minimum_required(VERSION 3.12)
project(JKYi-rpc)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

#添加头文件的查找
include_directories(.)
include_directories(/root/yaml-cpp-master/include)
include_directories(/usr/local/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JKYi)
include_directories(${CAMKE_CURRENT_SOURCE_DIR}/JKYi-rpc/include)

#加载下载的一些的一下开源库
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(OpenSSL REQUIRED)
if(OPNESSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/JKYi)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/JKYi-rpc)

#添加要需要链接的库的路径，相当于在gcc时的-L，就相当于将对应目录下的库加到搜索范围内
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/JKYi/lib)
link_directories(/usr/local/lib)
link_directories(/usr/local/lib64)
link_directories(/usr/local/mysql/lib)


set(LIBS
      JKYiRpc
      JKYi
	  dl
      pthread
      yaml-cpp
      jsoncpp
      ssl
      crypto
      mysqlclient
      zookeeper_mt
      event
      hiredis_vip
      z
      protobuf
   )


#执行框架的cmake
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)


