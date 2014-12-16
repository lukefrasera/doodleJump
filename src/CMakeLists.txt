
ADD_EXECUTABLE( doodlejump
  main.cpp
  doodleview.cpp
  ${gl_SOURCE}
  ${GLEW_LIBRARIES}
  ${ASSIMP_LIBRARIES}
)

target_link_libraries( doodlejump ${GLEW_LIBRARIES})
target_link_libraries( doodlejump ${GLUT_LIBRARY})
<<<<<<< HEAD
target_link_libraries( doodlejump ${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES})
=======
target_link_libraries( doodlejump ${OPENGL_LIBRARIES} )
target_link_libraries( doodlejump ${ASSIMP_LIBRARIES})
target_link_libraries( doodlejump ${IL_LIBRARIES})
>>>>>>> cb136f02873061c4158e53cc07dea47b3440baaa
target_link_libraries( doodlejump  /usr/lib/x86_64-linux-gnu/libBulletDynamics.so /usr/lib/x86_64-linux-gnu/libBulletCollision.so /usr/lib/x86_64-linux-gnu/libLinearMath.so /usr/lib/libassimp.so)
