#include "doodleview.h"
namespace doodle {
	DoodleJump::DoodleJump() {}
	DoodleJump::~DoodleJump() {}

	bool DoodleJump::initialize() {
		ilInit();
		
		bool loaded = loadObj("../bin/yoda.obj", "../bin/yoda.dds", "../bin/yoda.dds", yoda);
		if(!loaded) {
			cout << "Error loading object" << endl;
			return false;
		}
		
		initPhysics();
		
		if(!loadShaders())
			return false;
		
		view = glm::lookAt( glm::vec3(0.0, 10.0, -20.0), //Eye Position
                        	glm::vec3(0.0, 0.0, 0.0), //Focus point
                        	glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
                        	
    	projection = glm::perspective( 45.0f, float(w)/float(h), 0.01f, 100.0f);
    	
    	//enable depth testing
    	glUniform1i(gSampler, 0);
    	glEnable(GL_DEPTH_TEST);
    	glDepthFunc(GL_LESS);

    	//and its done
    	return true;
	}
	
	bool DoodleJump::loadShaders() {
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		
		const char *vs = loadFromString("../bin/shader.vert");
		const char *fs = loadFromString("../bin/shader.frag");
		
		GLint shader_status;
		
		// Vertex shader first
		glShaderSource(vertex_shader, 1, &vs, NULL);
		glCompileShader(vertex_shader);
		//check the compile status
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_status);
		
		char buffer[512]; // buffer for error
    
		if(!shader_status) {
			glGetShaderInfoLog(vertex_shader, 512, NULL, buffer); // inserts the error into the buffer
			cerr << buffer << endl; // prints out error
		    return false;
		}
		
		// Fragment shader
		glShaderSource(fragment_shader, 1, &fs, NULL);
		glCompileShader(fragment_shader);
		// check the compile status
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_status);
		
		if(!shader_status) {
		    glGetShaderInfoLog(fragment_shader, 512, NULL, buffer); // inserts the error into the buffer
			cerr << buffer << endl; // prints out error
		    return false;
		}
		
		//Now we link the 2 shader objects into a program
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		
		//check if everything linked ok
		glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
		if(!shader_status) {
		    std::cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" << std::endl;
		    return false;
		}
		
		//Now we set the locations of the attributes and uniforms
		//this allows us to access them easily while rendering
		loc_position = glGetAttribLocation(program, const_cast<const char*>("v_position"));
		if(loc_position == -1) {
		    std::cerr << "[F] POSITION NOT FOUND" << std::endl;
		    return false;
		}

		loc_uv = glGetAttribLocation(program, const_cast<const char*>("v_uv"));
		if(loc_uv == -1) {
		    std::cerr << "[F] V_UV NOT FOUND" << std::endl;
		    return false;
		}

		loc_mvpmat = glGetUniformLocation(program, const_cast<const char*>("mvpMatrix"));
		if(loc_mvpmat == -1) {
		    std::cerr << "[F] MVPMATRIX NOT FOUND" << std::endl;
		    return false;
		}
		
		gSampler = glGetUniformLocation(program, const_cast<const char*>("gSampler"));
		if(gSampler == -1){
		    std::cerr << "[F] LMAG NOT FOUND" << std::endl;
		    return false;
		}
	}
	
	void DoodleJump::update() {
		float dt = getDT();
        dynamicsWorld->stepSimulation(dt,10);
        
   		updateObj(yoda);
   		
		glutPostRedisplay();
	}
	
	void DoodleJump::updateObj(Object& obj){
		//initiate object transform
		btTransform trans;
		btScalar buffer[16];
		trans = obj.rigidBody -> getCenterOfMassTransform();
		trans.getOpenGLMatrix(buffer);
		glm::mat4 modelPosition = glm::make_mat4(buffer);
		obj.modelMatrix = modelPosition;
	}
	
	void DoodleJump::render() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    	//enable the shader program
		glUseProgram(program);

		//enable
		glUniform1i(gSampler, 0);
    	glEnableVertexAttribArray(loc_position);
    	glEnableVertexAttribArray(loc_normal);
    	glEnableVertexAttribArray(loc_uv);
    	
    	// Render objects
    	renderObj(yoda);
    	
    	//clean up
		glDisableVertexAttribArray(loc_position);
	    glDisableVertexAttribArray(loc_normal);
		glDisableVertexAttribArray(loc_uv);
    
    	printText(-0.15, .8, (char*)"Replay? <y/n>");
    
    	glutSwapBuffers();
	}
	
	void DoodleJump::renderObj(Object &obj) {
		for(unsigned int i=0; i<obj.numMeshes; i++) {
		    mvp = projection * view * obj.modelMatrix;
		    modelView = view * obj.modelMatrix;
		    glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));
		    glUniformMatrix4fv(loc_modelviewmat, 1, GL_FALSE, glm::value_ptr(modelView));
		    glBindBuffer(GL_ARRAY_BUFFER, obj.mesh[i].vbo_geometry);
		    glVertexAttribPointer(loc_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		    glVertexAttribPointer(loc_normal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex,normal));
		    glVertexAttribPointer(loc_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
		    glActiveTexture(GL_TEXTURE0);
		    //if(textureToggle == 0)
		        glBindTexture(GL_TEXTURE_2D, obj.texture);
		    //else
		       // glBindTexture(GL_TEXTURE_2D, obj._texture);*/
		    glDrawArrays(GL_TRIANGLES, 0, obj.mesh[i].numFaces * 3);
		}
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

	bool DoodleJump::loadObj(const char* filePathObj, const char* filePathTex,const char* filePathTex2, Object& obj) {
		//read file
		srand(time(NULL));
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(filePathObj, aiProcess_Triangulate);
		//return false if there is a scene error
		if(scene == NULL){
		    cout << "Error: Unable to read in object file path" << endl;
		    const char* msg = importer.GetErrorString();
		    cout << msg << endl;
		    return false;
		}

		// Get Materials (textures)
		bool success;
		success = ilLoadImage((const ILstring)filePathTex);
		if(!success) {
		    cout << "Error: Unable to load texture " << filePathTex << endl;
		    return false;
		}
		else {
		    success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		    if(!success) {
		        cout << "Error: Unable to convert image " << filePathTex << endl;
		        return false;
		    }
		    glGenTextures(1, &obj.texture);
		    glBindTexture(GL_TEXTURE_2D, obj.texture);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		        ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		        ilGetData());
		}

		// Get mesh
		obj.numMeshes = scene->mNumMeshes;
		obj.mesh = new Mesh[obj.numMeshes];

		for(unsigned int i=0; i<scene->mNumMeshes; i++){
		    aiMesh *tmpMesh = scene->mMeshes[i]; //aiMesh temporary to give to struct
		    tmpMesh = scene->mMeshes[i];
		    obj.mesh[i].geometry = new Vertex[tmpMesh->mNumVertices]; //3 vertex for each face
		    obj.mesh[i].numVertices = tmpMesh->mNumVertices;
		    obj.mesh[i].numFaces = tmpMesh->mNumFaces;

		    for(unsigned int j=0; j<tmpMesh->mNumFaces; j++){
		        aiFace &tmpFace = tmpMesh->mFaces[j];
		        for(unsigned int k=0; k<3; k++){
		            unsigned int tmpVertex = tmpFace.mIndices[k];
		            //load vertex positions
		            obj.mesh[i].geometry[3*j+k].position[0] = tmpMesh->mVertices[tmpVertex].x;
		            obj.mesh[i].geometry[3*j+k].position[1] = tmpMesh->mVertices[tmpVertex].y;
		            obj.mesh[i].geometry[3*j+k].position[2] = tmpMesh->mVertices[tmpVertex].z;
		            //load vertex uv
		            obj.mesh[i].geometry[3*j+k].uv[0] = tmpMesh->mTextureCoords[0][tmpVertex].x;
		            obj.mesh[i].geometry[3*j+k].uv[1] = tmpMesh->mTextureCoords[0][tmpVertex].y;
		            //load vertex normal
		            obj.mesh[i].hasNormals = tmpMesh->HasNormals();
		            if(tmpMesh->HasNormals()) {
		                obj.mesh[i].geometry[3*j+k].normal[0] = tmpMesh->mNormals[tmpVertex].x;
		                obj.mesh[i].geometry[3*j+k].normal[1] = tmpMesh->mNormals[tmpVertex].y;
		                obj.mesh[i].geometry[3*j+k].normal[2] = tmpMesh->mNormals[tmpVertex].z;
		            }
		        }
		    }
		}

		//Create Vertex Array Object for each mesh
		for(unsigned int i=0; i<scene->mNumMeshes; i++){
		    glGenBuffers(1, &(obj.mesh[i].vbo_geometry));
		    glBindBuffer(GL_ARRAY_BUFFER, obj.mesh[i].vbo_geometry);
		    glBufferData(GL_ARRAY_BUFFER, obj.mesh[i].numFaces * 3 * sizeof(Vertex), &(obj.mesh[i].geometry[0]), GL_STATIC_DRAW);
		}

		return true;
	}   

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
		
		//YODA
		btCollisionShape* yodaShape = new btBoxShape(btVector3(.3,.3,.3));
		btDefaultMotionState* yodaMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
		btRigidBody::btRigidBodyConstructionInfo yodaRigidBodyCI(0, yodaMotionState, yodaShape, btVector3(0,0,0));
		yoda.rigidBody = new btRigidBody(yodaRigidBodyCI);
		yoda.rigidBody->setActivationState(DISABLE_DEACTIVATION);
		dynamicsWorld->addRigidBody(yoda.rigidBody);	
	}
	
	char* DoodleJump::loadFromString(const char* fileName){
		char* temp;
		ifstream fin;
		int length;
	
		fin.open(fileName);
		fin.seekg(0, fin.end);
		length = fin.tellg();
		fin.seekg(0, fin.beg);
		temp = new char[length+1];
		fin.read(temp, length);
		temp[length+1]='\0';	
		fin.close();
	
		return temp;
	}
	
	float DoodleJump::getDT(){
		float ret;
		t2 = std::chrono::high_resolution_clock::now();
		ret = std::chrono::duration_cast< std::chrono::duration<float> >(t2-t1).count();
		t1 = std::chrono::high_resolution_clock::now();
		return ret;
	}
	
	void DoodleJump::printText(float x, float y, char* text){
		glUseProgram(0);

		float r,g,b;
		r = 0.;
		g = 1.;
		b = 1.;

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		bool blending = false;

		if(glIsEnabled(GL_BLEND)) 
		blending = true;

		glEnable(GL_BLEND);
		glColor3f(r,g,b);
		glRasterPos2f(x,y);

		while(*text){
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
		    text++;
		}

		if(!blending) 
		glDisable(GL_BLEND);
	}
	
	void DoodleJump::cleanUp(){
		// Clean up
		glDeleteProgram(program);
		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}
}
