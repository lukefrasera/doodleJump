#include "abstractscene.h"
#include "baseglscene.h"
#include "glapplication.h"
#include <iostream>

abstractScene * mScene;

int main(int argc, char* argv[]){
	basicGLScene * w = new basicGLScene;
  w->w=200;
  w->h=200;
  mScene = w;
	GLApplication app(argc, argv);
	
	return 0;
}