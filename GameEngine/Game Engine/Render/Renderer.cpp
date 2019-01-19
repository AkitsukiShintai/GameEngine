/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Renderer.cpp>
Purpose:<implement all functions declared in Renderer.h, generate openGL program>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Renderer.h"

string loadTextFile(const char *fname) {
	string out,
		line;
	ifstream in(fname);
	getline(in, line);
	while (in) {
		out += line + "\n";
		getline(in, line);
	}
	return out;
}

Renderer::Renderer():aposition(-1),anormal(-1),upersp_matrix(-1),uview_matrix(-1), umodel_matrix(-1),
unormal_matrix(-1), ucolor(-1), atexturecoord(-1)
{
	
	GLint value;
	string fragtextstr = loadTextFile("defult.frag");
	//string fragtextstr = loadTextFile("dd_frag");
	const char *fragtext = fragtextstr.c_str();
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragtext, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "fragment shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	string verttextstr = loadTextFile("defult.vert");
	//string verttextstr = loadTextFile("dd_vert");
	const char *verttext = verttextstr.c_str();
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &verttext, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	mGLProgram = glCreateProgram();
	glAttachShader(mGLProgram, fshader);
	glAttachShader(mGLProgram, vshader);
	glLinkProgram(mGLProgram);
	glGetProgramiv(mGLProgram, GL_LINK_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}
	glDeleteShader(fshader);
	glDeleteShader(vshader);

	// get shader variable locations
	/*aposition = glGetAttribLocation(mGLProgram, "position");
	upersp_matrix = glGetUniformLocation(mGLProgram, "persp_matrix");
	uview_matrix = glGetUniformLocation(mGLProgram, "view_matrix");
	umodel_matrix = glGetUniformLocation(mGLProgram, "model_matrix");*/
	
	aposition = glGetAttribLocation(mGLProgram, "position");
	anormal = glGetAttribLocation(mGLProgram, "normal");
	upersp_matrix = glGetUniformLocation(mGLProgram, "persp_matrix");
	uview_matrix = glGetUniformLocation(mGLProgram, "view_matrix");
	umodel_matrix = glGetUniformLocation(mGLProgram, "model_matrix");
	unormal_matrix = glGetUniformLocation(mGLProgram, "normal_matrix");
	ucolor = glGetUniformLocation(mGLProgram, "color");
	
}

Renderer::Renderer(std::string t) {

	GLint value;
	std::string t1 = t+".frag";
	string fragtextstr = loadTextFile(t1.c_str());
	//string fragtextstr = loadTextFile("dd_frag");
	const char *fragtext = fragtextstr.c_str();
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragtext, 0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "fragment shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(fshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}
	std::string t2 =t+ ".vert";
	string verttextstr = loadTextFile(t2.c_str());
	//string verttextstr = loadTextFile("dd_vert");
	const char *verttext = verttextstr.c_str();
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &verttext, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}

	mGLProgram = glCreateProgram();
	glAttachShader(mGLProgram, fshader);
	glAttachShader(mGLProgram, vshader);
	glLinkProgram(mGLProgram);
	glGetProgramiv(mGLProgram, GL_LINK_STATUS, &value);
	if (!value) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vshader, 1024, 0, buffer);
		cerr << buffer << endl;
	}
	glDeleteShader(fshader);
	glDeleteShader(vshader);

	// get shader variable locations
	aposition = glGetAttribLocation(mGLProgram, "position");
	anormal = glGetAttribLocation(mGLProgram, "normal");
	upersp_matrix = glGetUniformLocation(mGLProgram, "persp_matrix");
	uview_matrix = glGetUniformLocation(mGLProgram, "view_matrix");
	umodel_matrix = glGetUniformLocation(mGLProgram, "model_matrix");
	unormal_matrix = glGetUniformLocation(mGLProgram, "normal_matrix");
	ulight_position = glGetUniformLocation(mGLProgram, "light_position");
	ulight_color = glGetUniformLocation(mGLProgram, "light_color");
	ucolor = glGetUniformLocation(mGLProgram, "color");
	atexturecoord = glGetUniformLocation(mGLProgram, "texture_coord");

}

Renderer::~Renderer()
{
}