qt_add_qml_module(image
    URI image
    VERSION 1.0
    DEPENDENCIES
        QtGui
        QtQuick
    SOURCES
        image.cpp
        image.h
)

target_link_libraries(image
    PRIVATE Qt6::Gui Qt6::Quick
)
