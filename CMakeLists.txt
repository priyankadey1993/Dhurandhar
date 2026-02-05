cmake_minimum_required(VERSION 3.16)
project(dhurandhar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup()

qt_add_executable(appdhurandhar
    main.cpp
)

qt_add_qml_module(appdhurandhar
    URI dhurandhar
    QML_FILES
        Main.qml
        RESOURCES images/dhurandhar-movie-logo-png.png
        RESOURCES images/ranveersingh_intro_img.jpg
        RESOURCES images/ammo-Image.png
        RESOURCES images/background.jpg
        RESOURCES images/down.png
        RESOURCES images/left.png
        RESOURCES images/right.png
        RESOURCES images/TDown.jpg
        RESOURCES images/TLeft.jpg
        RESOURCES images/TRight.png
        RESOURCES images/TUp.jpg
        RESOURCES images/up.png
        QML_FILES GameView.qml
        QML_FILES PlayerItem.qml
        QML_FILES EnemyItem.qml
        QML_FILES BulletItem.qml
        SOURCES GameController.h GameController.cpp
        SOURCES Player.h
        SOURCES Enemy.h
        SOURCES Bullet.h
)

# Add resources separately
qt_add_resources(appdhurandhar "resources"
    PREFIX "/"
    FILES
        audio/dhurandhar_title.mp3
        images/dhurandhar-movie-logo-png.png
        images/ranveersingh_intro_img.jpg
        images/ammo-Image.png
        images/background.jpg
        images/down.png
        images/left.png
        images/right.png
        images/TDown.jpg
        images/TLeft.jpg
        images/TRight.png
        images/TUp.jpg
        images/up.png
)

set_target_properties(appdhurandhar PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdhurandhar
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appdhurandhar
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
