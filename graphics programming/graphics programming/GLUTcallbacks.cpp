#include "GLUTcallbacks.h"
#include "openGL.h"
#include "Player.h"

namespace GLUTcallbacks
{
	int updateTime = glutGet(GLUT_ELAPSED_TIME);

	namespace
	{
		openGL* helloGL = nullptr;
		Player* m_player = nullptr;
	}

	void Init(openGL *gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		helloGL->Update();

		// call this again so update loops 60 times a second
		glutTimerFunc(preferredRefresh, GLUTcallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}
}