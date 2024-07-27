cmake_minimum_required(VERSION 3.20)
project(view)

find_package(QT NAMES Qt6 Qt5 REQUIRED Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED Quick)

add_library(${PROJECT_NAME} STATIC
        NPKImageListModel.cpp
        NPKImageListModel.h
        EXWardrobe.cpp
        EXWardrobe.h
        MatrixRenderer.cpp
        MatrixRenderer.h
        NPKMatrixConvertor.cpp
        NPKMatrixConvertor.h
)

target_link_libraries(view PUBLIC Qt${QT_VERSION_MAJOR}::Quick)