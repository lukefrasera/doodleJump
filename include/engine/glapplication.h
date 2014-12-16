#include "abstractscene.h"

#ifndef GLAPPLICATION
#define GLAPPLICATION
class GLApplication {
public:
  GLApplication(int argc, char* argv[]);
  ~GLApplication();

protected:
  void initializeScene(int argc, char* argv[]);
  void cleanUpScene();

  // Setup Callbacks
  void initializeCallbacks();
};
#endif