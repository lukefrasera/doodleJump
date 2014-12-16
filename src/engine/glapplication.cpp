#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include "glapplication.h"
#include "abstractscene.h"
#include <stdio.h>

extern abstractScene * mScene;

GLApplication::GLApplication(int argc, char* argv[]){
	// mScene = &scene;

    printf("Hello\n");
    initializeScene(argc, argv);
	initializeCallbacks();
}

GLApplication::~GLApplication(){
	cleanUpScene();
}

void GLApplication::initializeScene(int argc, char* argv[]){
	// Initialize glut
    printf("width: %d, Height: %d\n", mScene->w, mScene->h);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(mScene->w, mScene->h);
    // Name and create the Window
    glutCreateWindow("Pass Through Shader Test");

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if( status != GLEW_OK)
    {
        std::cerr << "[F] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
    }

    // Handle All Game Callbacks
    initializeCallbacks();

    // Initialize Scene Object
    bool init = mScene->initialize();
    if(init)
    {
        glutMainLoop();
    }
}

void GLApplication::initializeCallbacks(){
	// Set all of the callbacks to GLUT that we need
    glutDisplayFunc(abstractScene::absrender);// Called when its time to display
    glutReshapeFunc(abstractScene::absresize);// Called if the window is resized
    glutIdleFunc(abstractScene::absupdate);// Called if there is nothing else to do
    glutKeyboardFunc(abstractScene::glutKeyPressEvent);// Called if there is keyboard input
    glutKeyboardUpFunc(abstractScene::glutKeyReleaseEvent);
    glutMouseFunc(abstractScene::glutMouseClickEvent);
    glutPassiveMotionFunc(abstractScene::glutMouseMoveEvent);
}

void GLApplication::cleanUpScene(){
	// Delete all objects and Buffers
}