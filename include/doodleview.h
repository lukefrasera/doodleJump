
#ifndef DOODLE_JUMP_H_
#define DOODLE_JUMP_H_
#include "abstractscene.h"

namespace doodle {

class DoodleJump : public abstractScene {
public:
  DoodleJump();
  ~DoodleJump();

public:
  virtual bool initialize();
  virtual void update();
  virtual void render();
  virtual void resize(int w, int h);

  virtual void initializeGL();
  virtual void resizeGL(int w , int h);
  virtual void updateGL();
  virtual void drawGL();

protected:
  virtual void keyPressEvent();
  virtual void keyReleaseEvent();
  virtual void mouseClickEvent();
  virtual void mouseReleaseEvent();
  virtual void mouseMoveEvent();

private:
  // Add openGL Variables to Scene

  // ARRAY OF OBJECTS IN SCENE
};
}
#endif