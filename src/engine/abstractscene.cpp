#include "abstractscene.h"
#include <stdio.h>
#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting

extern abstractScene * mScene;
abstractScene::abstractScene(){
}
abstractScene::~abstractScene(){}

void abstractScene::absupdate() {
  mScene->update();
  glutPostRedisplay();
}
void abstractScene::absrender() {
  mScene->render();
}
void abstractScene::absresize(int w, int h) {
  mScene->resize(w,h);
}

void abstractScene::glutKeyPressEvent(unsigned char key, int x, int y) {
	printf("glutKeyPressEvent\n");
	mScene->keyPressEvent();
}

void abstractScene::glutKeyReleaseEvent(unsigned char key, int x, int y) {
  printf("glutKeyReleaseEvent\n");
	mScene->keyReleaseEvent();
}

void abstractScene::glutMouseMoveEvent(int x, int y) {
  printf("glutMouseMoveEvent\n");
	mScene->mouseMoveEvent();
}

void abstractScene::glutMouseClickEvent(int button, int state, int x, int y) {
  printf("glutMouseClickEvent\n");
	mScene->mouseClickEvent();
}