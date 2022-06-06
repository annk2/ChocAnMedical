cmake_minimum_required(VERSION 3.21)
project(ChocAnApplication)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChocAnApplication src/chocAn.cpp src/application.cpp src/application.h src/directory_list.cpp src/directory_list.h src/manager.cpp src/manager.h src/provider.cpp src/provider.h src/member.cpp src/member.h src/member_list.cpp src/member_list.h src/personal_info.cpp src/personal_info.h src/procedure.cpp src/procedure.h src/provider_list.cpp src/provider_list.h src/service.cpp src/service.h src/service_list.cpp src/service_list.h src/provider_directory.txt)
