#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks {
	namespace {
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl) {
		helloGL = gl;
	}

	void Display() {
		if (helloGL != nullptr)
			helloGL->Display();
	}

	void Timer(int preferredRefresh) {
		//Calculate how long Update() took to process
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;

		//Delays for preferred ms, then calls this function again.
		//We take the Update() process time off of the delay, otherwise the process time would add on to the delay
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y) {
		helloGL->Keyboard(key, x, y);
	}
}