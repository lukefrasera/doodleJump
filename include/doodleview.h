
#ifndef DOODLE_JUMP_H_
#define DOODLE_JUMP_H_
#include "abstractscene.h"
#include "bullet/btBulletCollisionCommon.h"

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
  void initPhysics();

protected:
  virtual void keyPressEvent(unsigned char, int, int);
  virtual void keyReleaseEvent(unsigned char, int, int);
  virtual void mouseClickEvent(int button, int state, int x, int y);
  virtual void mouseReleaseEvent();
  virtual void mouseMoveEvent(int x, int y);

private:
  // Add openGL Variables to Scene
  //Bullet Physics Globals
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
  // ARRAY OF OBJECTS IN SCENE
};
}
#endif
