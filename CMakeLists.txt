cmake_minimum_required(VERSION 3.20)

project(NeapuExToolkit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)

if (MSVC)
    add_compile_options(/utf-8)
endif ()

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NeapuExToolkit
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resource.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NeapuExToolkit APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NeapuExToolkit SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NeapuExToolkit
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NeapuExToolkit PRIVATE Qt${QT_VERSION_MAJOR}::Quick)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NeapuExToolkit)
endif()
set_target_properties(NeapuExToolkit PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE # 调试阶段不要设置这个，否则会导致无法输出日志

)

add_compile_definitions(ENABLE_OLD_STYLE_LOG)

include_directories(first_party/logger)
include_directories(first_party/neapu_npk)
add_subdirectory(first_party)

target_link_libraries(NeapuExToolkit PRIVATE logger)
include_directories(NeapuExToolkit PRIVATE first_party/logger)

target_link_libraries(NeapuExToolkit PRIVATE npk)

add_subdirectory(view/cpp)
target_link_libraries(NeapuExToolkit PRIVATE view)

include(GNUInstallDirs)
install(TARGETS NeapuExToolkit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NeapuExToolkit)
endif()
