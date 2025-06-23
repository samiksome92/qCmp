cmake_minimum_required(VERSION 3.19)

project(qCmp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Gui Quick)

qt_standard_project_setup(REQUIRES 6.8)
add_subdirectory(image)

qt_add_executable(qcmp
    main.cpp
    backend.cpp
    utils.cpp
)

set_source_files_properties(Style.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
qt_add_qml_module(qcmp
    URI qCmp
    VERSION 1.0
    QML_FILES
        Main.qml
        Style.qml
)

qt_add_resources(qcmp "fonts"
    FILES
        "fonts/IBMPlexSans-VariableFont_wdth,wght.ttf"
)

target_link_libraries(qcmp
    PRIVATE Qt6::Gui Qt6::Quick
)

install(TARGETS qcmp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET qcmp
    OUTPUT_SCRIPT deploy_script
    NO_TRANSLATIONS
    NO_COMPILER_RUNTIME
)
install(SCRIPT ${deploy_script})
