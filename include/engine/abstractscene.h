/* ABSTRACT SCENE CLASS: This class defines the abstract base class for minecraft scenes to inherit.
// This defines the basee class for glut and GLEW scene setup for app use
*/
#ifndef ABSTRACT_SCENE
#define ABSTRACT_SCENE
class abstractScene {
public:
	abstractScene();
	~abstractScene();

public:
	virtual bool initialize() = 0;
	static void absupdate();
	static void absrender();
	static void absresize(int w, int h);

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void resize(int w, int h) = 0;

	// Gut Wraper functions
	static void glutKeyPressEvent(unsigned char, int, int);
	static void glutKeyReleaseEvent(unsigned char, int, int);
	static void glutMouseMoveEvent(int x, int y);
	static void glutMouseClickEvent(int button, int state, int x, int y);

	int w,h;
protected:

	virtual void keyPressEvent(unsigned char, int, int) = 0;
	virtual void keyReleaseEvent(unsigned char, int, int) = 0;
	virtual void mouseClickEvent(int button, int state, int x, int y) = 0;
	virtual void mouseReleaseEvent() = 0;
	virtual void mouseMoveEvent(int x, int y) = 0;
	
	// Private Data Members
private:
	char * windowtitle;
	bool fullScreen;
};
#endif