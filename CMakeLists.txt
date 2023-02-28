cmake_minimum_required(VERSION 3.15)

project(RenderWindowUIMultipleInheritance LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS                "-Wall -std=c++17")
#set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
 
file(GLOB UI_FILES *.ui)

# .h files
list(APPEND HEADER_FILES
    CommonHeaders.h
    viewer.h
    vtkbordercallback.h
    myvtkinteractorstyleimage.h
    itk.h
    postprocessingfilters.h
    RenderWindowUIMultipleInheritance.h
)
# .cpp files
list(APPEND SOURCE_FILES
    viewer.cpp
    vtkbordercallback.cpp
    myvtkinteractorstyleimage.cpp
    itk.cpp
    postprocessingfilters.cpp
    RenderWindowUIMultipleInheritance.cxx
    RenderWindowUIMultipleInheritanceDriver.cxx
)


qt5_wrap_ui(UISrcs ${UI_FILES} )
# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.


add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UISrcs} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
qt5_use_modules(RenderWindowUIMultipleInheritance Core Gui)
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES} ${ITK_LIBRARIES})
