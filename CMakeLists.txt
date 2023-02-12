cmake_minimum_required(VERSION 3.15)

project(RenderWindowUIMultipleInheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_AUTOUIC ON)
find_package(ITK REQUIRED)
IF(ITK_FOUND)
    INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
    MESSAGE(FATAL_ERROR "Cannot build InsightApplications without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

 
if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
  # Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)
  find_package(Qt5Widgets REQUIRED QUIET)
else()
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
endif()
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
 
file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cxx *.cpp)

#target_link_libraries(RenderWindowUIMultipleInheritance ${ITK_LIBRARIES})
 
if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
  qt5_wrap_ui(UISrcs ${UI_FILES} )
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(RenderWindowUIMultipleInheritance ${CXX_FILES} ${UISrcs} ${QT_WRAP})
    target_compile_features(RenderWindowUIMultipleInheritance PUBLIC cxx_std_17)
  qt5_use_modules(RenderWindowUIMultipleInheritance Core Gui)
  target_link_libraries(RenderWindowUIMultipleInheritance ${VTK_LIBRARIES} ${ITK_LIBRARIES})
else()
  QT4_WRAP_UI(UISrcs ${UI_FILES})
  QT4_WRAP_CPP(MOCSrcs ${QT_WRAP})
  add_executable(RenderWindowUIMultipleInheritance ${CXX_FILES} ${UISrcs} ${MOCSrcs})
 
  if(VTK_LIBRARIES)
    if(${VTK_VERSION} VERSION_LESS "6")
      target_link_libraries(RenderWindowUIMultipleInheritance ${VTK_LIBRARIES} QVTK)
    else()
      target_link_libraries(RenderWindowUIMultipleInheritance ${VTK_LIBRARIES})
    endif()
  else()
    target_link_libraries(RenderWindowUIMultipleInheritance vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
  endif()
endif()
