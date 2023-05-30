cmake_minimum_required(VERSION 3.15)
project(CFRenderEngine)

set(target CFRenderEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 17)
if (APPLE)
# use GLUT
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS})
else()
    # HACK: This is NOTFOUND on OS X 10.8
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

if(MSVC)
    # Release模式生成PDB文件
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO}")
endif()



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

include(tool)

set(Qt_dir C:/Qt/Qt5.13.0/5.13.0) #这里需要填入自己安装的路径
if(NOT EXISTS ${Qt_dir})
    set_local_qt_path(C:/Qt5.13.0/5.13.0) #这里需要填入自己安装的路径
else()
    set_local_qt_path(${Qt_dir})
endif()

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
    src/Entity/*.*
    src/Render/*.*
    src/Systems/*.*
    src/UI/*.*
    src/Core/*.*
    src/Utils/*.*
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

qt5_add_resources(QRC_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/asset/qss/qss.qrc 
    ${CMAKE_CURRENT_SOURCE_DIR}/asset/shader/shader.qrc)

add_subdirectory(vendor)

add_executable(${target} ${CORE_SOURCE_FILES} ${QRC_SOURCES})

# add_custom_target(CopyResources
#     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/external/glut/lib/freeglut.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${CMAKE_BUILD_TYPE}
#     COMMAND ${CMAKE_COMMAND} -E xcopy assets/package/windows/vendor/ ${CMAKE_CURRENT_BINARY_DIR}/resources/
#     COMMAND ${CMAKE_COMMAND} -E xcopy assets/package/shared/ ${CMAKE_CURRENT_BINARY_DIR}/resources/
#     COMMAND ${CMAKE_COMMAND} -E xcopy vendor/LightRenderer/assets/ ${CMAKE_CURRENT_BINARY_DIR}/resources/assets/ # 拷贝AEKit相关资源
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/)

# set(CMAKE_BUILD_TYPE "Debug")

# message(STATUS "dddddd${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${CMAKE_BUILD_TYPE}/${target}.exe")
# add_custom_command(TARGET ${target} POST_BUILD
#     COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${CMAKE_BUILD_TYPE}
#     COMMAND ${QT_ABSOLUTE_PATH}/msvc2017_64/bin/windeployqt.exe ${target}.exe
# )

# 指定头文件路径，否则会提示在ui_mainwindow.cpp中找不到提升的class
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/UI)
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${target} PRIVATE ${QT_libs} vendor)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${target} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()
