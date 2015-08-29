project(qt-layout)

set(SOURCES
   layoutitem.cpp
   layoutmanager.cpp
   layoutprofile.cpp
)

set(HEADERS
   layoutitem.h
   layoutmanager.h
   layoutprofile.h
)

add_library(${PROJECT_NAME} SHARED
   ${SOURCES}
   ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
   ${Qt5Core_LIBRARIES}
   ${Qt5Widgets_LIBRARIES}
   ${Qt5Gui_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)

