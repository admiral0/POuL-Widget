cmake_minimum_required(VERSION 2.6)

find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED )
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} qmaemo5homescreenadaptor)

set(homescreen_helper qmaemo5homescreenadaptor/qmaemo5homescreenadaptor.cpp)
set(poul_src poulstatus.cpp
             main.cpp
             poulwidget.cpp)

qt4_automoc(${homescreen_helper} ${poul_src})
QT4_ADD_RESOURCES(poulwidget_RCC resources/resource.rcc)
add_executable(poul-widget ${homescreen_helper} ${poul_src} ${poulwidget_RCC})
target_link_libraries(poul-widget  ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

install(TARGETS poul-widget DESTINATION lib/hildon-desktop)
install(FILES poulwidget.desktop DESTINATION share/applications/hildon-home)