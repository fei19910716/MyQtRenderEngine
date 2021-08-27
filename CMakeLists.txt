cmake_minimum_required(VERSION 3.15)
project(CFRenderEngine)

set(target CFRenderEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(tool)

set_local_qt_path(C:/Qt5.13.0/5.13.0) #这里需要填入自己安装的路径
include(qt_config)

set(QT_libs
        Qt5::OpenGL
        Qt5::Core
        Qt5::Gui
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Multimedia
        Qt5::WebEngine
        Qt5::Svg
        Qt5::Concurrent
        Qt5::Network
        )

file(GLOB_RECURSE CORE_SOURCE_FILES
    src/Components/*.*
    src/Entities/*.*
    src/Render/*.*
    src/Systems/*.*
    main.cpp
    src/mainwindow.cpp
    src/renderview.cpp
)

add_subdirectory(vendor)

add_executable(${target} ${CORE_SOURCE_FILES})

# add_custom_target(CopyResources
#     COMMAND cp -r assets/package/windows/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources/
#     COMMAND cp -r assets/package/windows/vendor/ ${CMAKE_CURRENT_BINARY_DIR}/resources/
#     COMMAND cp -r assets/package/shared/ ${CMAKE_CURRENT_BINARY_DIR}/resources/
#     COMMAND cp -r vendor/LightRenderer/assets/ ${CMAKE_CURRENT_BINARY_DIR}/resources/assets/ # 拷贝AEKit相关资源
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/)

# 指定头文件路径，否则会提示在ui_mainwindow.cpp中找不到提升的class
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${target} PRIVATE ${QT_libs} vendor)