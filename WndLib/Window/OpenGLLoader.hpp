#pragma once
#include <glad/glad.h>

#include <iostream>

class OpenGLLoader
{
public:
	int load_opengl(GLADloadproc proc)
	{
		int status = gladLoadGLLoader(proc);
		if (!status) {
			std::cout << "Could not initialize glad openGL" << std::endl;
			return status;
		}
		return 1;
	}
};