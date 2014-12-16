#include "baseglscene.h"
#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include <stdio.h>

basicGLScene::basicGLScene() {}
basicGLScene::~basicGLScene() {}

bool basicGLScene::initialize() {}
void basicGLScene::update() {}
void basicGLScene::render(){}
void basicGLScene::resize(int w, int h) {}

void basicGLScene::initializeGL() {}
void basicGLScene::resizeGL(int w , int h) {}
void basicGLScene::updateGL() {}
void basicGLScene::drawGL() {}

void basicGLScene::keyPressEvent() {}
void basicGLScene::keyReleaseEvent() {}
void basicGLScene::mouseClickEvent() {}
void basicGLScene::mouseReleaseEvent() {}
void basicGLScene::mouseMoveEvent() {}