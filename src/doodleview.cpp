#include "doodleview.h"
namespace doodle {
	DoodleJump::DoodleJump() {}
	DoodleJump::~DoodleJump() {}

	bool DoodleJump::initialize() {
		
    	projection = glm::perspective( 45.0f, float(w)/float(h), 0.01f, 100.0f);
	}
	
	void DoodleJump::update() {
		/*hello*/
		glutPostRedisplay();
	}
	
	void DoodleJump::render() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    	
    	glutSwapBuffers();
	}
	
	void DoodleJump::resize(int w, int h) {
	    windowWidth = w;
   		windowHeight = h;
    	glViewport(0, 0, windowWidth, windowHeight);
    	projection = glm::perspective(45.0f, float(windowWidth)/float(windowHeight), 0.01f, 100.0f);
    }

	void DoodleJump::initializeGL() {}
	void DoodleJump::resizeGL(int w , int h) {}
	void DoodleJump::updateGL() {}
	void DoodleJump::drawGL() {}

	void DoodleJump::keyPressEvent(unsigned char key, int x, int y) {}
	void DoodleJump::keyReleaseEvent(unsigned char key, int x, int y) {}
	void DoodleJump::mouseClickEvent(int button, int state, int x, int y) {}
	void DoodleJump::mouseReleaseEvent() {}
	void DoodleJump::mouseMoveEvent(int x, int y) {}

	void DoodleJump::initPhysics(){
		//tells bullet how to check for collisions between objects
		broadphase = new btDbvtBroadphase();
	
		//collision configuration contains default setup for memory, collision setup
		collisionConfiguration = new btDefaultCollisionConfiguration();

		//use the default collision dispatcher
		dispatcher = new  btCollisionDispatcher(collisionConfiguration);

		//the default constraint solver
		btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
		solver = sol;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0,-9.81,0));
	}
}
