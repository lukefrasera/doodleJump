
ADD_EXECUTABLE( doodlejump
  main.cpp
  doodleview.cpp
  ${gl_SOURCE}
  ${GLEW_LIBRARIES}
)

target_link_libraries( doodlejump ${GLEW_LIBRARIES})
target_link_libraries( doodlejump ${GLUT_LIBRARY})
target_link_libraries( doodlejump ${OPENGL_LIBRARIES})
target_link_libraries( doodlejump  /usr/lib/x86_64-linux-gnu/libBulletDynamics.so /usr/lib/x86_64-linux-gnu/libBulletCollision.so /usr/lib/x86_64-linux-gnu/libLinearMath.so)