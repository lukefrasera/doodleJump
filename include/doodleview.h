
#ifndef DOODLE_JUMP_H_
#define DOODLE_JUMP_H_
#include "abstractscene.h"
#include <GL/glew.h> 
#include <GL/glut.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <iostream>
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "IL/il.h"

using namespace std;

namespace doodle {

class DoodleJump : public abstractScene {
public:
  DoodleJump();
  ~DoodleJump();

public:
	struct Vertex{
		GLfloat position[3];
		GLfloat uv[2];
		GLfloat normal[3];
	};
  
	struct Mesh{
		  Vertex* geometry;
		  unsigned int numFaces;
		  unsigned int numVertices;
		  GLuint vbo_geometry;
		  bool hasNormals;
	};

	struct Object{
		  Mesh* mesh;
		  glm::mat4 modelMatrix;
		  unsigned int numMeshes;
		  btRigidBody *rigidBody;
		  GLuint texture;
		  GLuint altTexture;
	};

  virtual bool initialize();
  virtual void update();
  virtual void updateObj(Object&);
  virtual void render();
  virtual void renderObj(Object&);
  virtual void resize(int w, int h);
  virtual bool loadShaders();
  virtual bool loadObj(const char* objpath, const char* text,const char* alttext, Object&);
	virtual char* loadFromString(const char*);
	virtual float getDT();
	virtual void cleanUp();

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
  
  // Geometry Variables
  GLuint program;
  Object yoda;
  
  //transform matrices
	glm::mat4 model;//obj->world each object should have its own model matrix
	glm::mat4 modelView;
	glm::mat4 view;//world->eye
	glm::mat4 projection;//eye->clip
	glm::mat4 mvp;//premultiplied modelviewprojection
  
  //uniform locations
	GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader
	GLint loc_modelviewmat;
	
	//attribute locations
	GLint loc_position;
	GLint loc_normal;
	GLint loc_uv;
	GLint gSampler;
  
  //Bullet Physics Globals
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	
	std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;
	int windowWidth, windowHeight;
  // ARRAY OF OBJECTS IN SCENE
};
}
#endif
