#include "abstractscene.h"
#include "baseglscene.h"
#include "glapplication.h"
#include "doodleview.h"
#include <iostream>

abstractScene * mScene;

int main(int argc, char* argv[]){
	doodle::DoodleJump * w = new doodle::DoodleJump;
  w->w=400;
  w->h=600;
  mScene = w;
	GLApplication app(argc, argv);

  printf("Hello\n");
	
	return 0;
}
