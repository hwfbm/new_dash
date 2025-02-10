# cmake_minimum_required(VERSION 3.16)

# project(New_dash VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort)
# #find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)
# # set(PROJECT_SOURCES
# #         main.cpp
# #         mainwindow.cpp
# #         mainwindow.h
# #         mainwindow.ui
# #         battery.h
# #         battery.cpp
# #         battery.ui
# #         imu.h
# #         imu.cpp
# #         imu.ui
# # )

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(New_dash
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#         battery.h battery.cpp battery.ui
#         imu.h imu.cpp imu.ui
#         serialsimulator.h serialsimulator.cpp


#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET New_dash APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# else()
#     if(ANDROID)
#         add_library(New_dash SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(New_dash
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()

# target_link_libraries(New_dash PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort)

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.New_dash)
# endif()
# set_target_properties(New_dash PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# include(GNUInstallDirs)
# install(TARGETS New_dash
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(New_dash)
# endif()



cmake_minimum_required(VERSION 3.16)

project(New_dash VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt 包，包括 Widgets 和 SerialPort 模块
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort Network)

# 设置源文件
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    battery.h
    battery.cpp
    battery.ui
    imu.h
    imu.cpp
    imu.ui
    serialsimulator.h
    serialsimulator.cpp
)

# 添加可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(New_dash
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        serial.h serial.cpp
        AircraftData.h
        GpsTime.h
        weather.h weather.cpp
        Icon.qrc
    )
else()
    if(ANDROID)
        add_library(New_dash SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(New_dash
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 链接 Qt Widgets 和 SerialPort 模块
target_link_libraries(New_dash PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort Qt${QT_VERSION_MAJOR}::Network)

# 设置 macOS 和 Windows 的特定属性
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.New_dash)
endif()

set_target_properties(New_dash PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")


# 安装配置
include(GNUInstallDirs)
install(TARGETS New_dash
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 针对 Qt 6 的最终处理
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(New_dash)
endif()
