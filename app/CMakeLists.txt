# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

#配置CMake的最低版本
cmake_minimum_required(VERSION 3.4.1)

#配置工程路径
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../../libs)


#添加两个预编译的so库
add_library( fmod
             SHARED
             IMPORTED )

add_library( fmodL
             SHARED
             IMPORTED )


#设置两个预编译的库的路径，注意这里最好要使用绝对路径，不然会链接错误
set_target_properties( fmod
                       PROPERTIES IMPORTED_LOCATION
                       ../../../../libs/armeabi/libfmod.so )
set_target_properties( fmodL
                       PROPERTIES IMPORTED_LOCATION
                       ../../../../libs/armeabi/libfmodL.so )

include_directories(src/main/cpp/inc)

#添加自己写的库
add_library( sound
             SHARED
             src/main/cpp/supersound.cpp )



#找到Android的log库（这个库已经在Android平台中了
find_library( # Sets the name of the path variable.
              log-lib

              log )


#把需要的库链接到自己的库中
target_link_libraries( sound
                        fmod
                        fmodL
                       ${log-lib}
                       )