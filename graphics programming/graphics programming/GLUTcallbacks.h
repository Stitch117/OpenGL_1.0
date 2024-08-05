#pragma once

class openGL;

namespace GLUTcallbacks
{
	void Init(openGL* gl);
	
	void Display();

	void Timer(int prefferedRefresh); //set framerate to 60 fps

	void Keyboard(unsigned char key, int x, int y); //get keyboard functionality
}

