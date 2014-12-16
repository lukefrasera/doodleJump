ADD_EXECUTABLE( doodlejump
  main.cpp
  doodleview.cpp
  ${gl_SOURCE}
  ${GLEW_LIBRARIES}
)

target_link_libraries( doodlejump ${GLEW_LIBRARIES})
target_link_libraries( doodlejump ${GLUT_LIBRARY})