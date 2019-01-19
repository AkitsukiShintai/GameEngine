/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Buffer.cpp>
Purpose:<implement all functions declared in Buffer.h, generate openGL buffers>

Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Buffer.h"
#include "Plane.h"
#include"Circle.h"
#include"../Math/Affine.h"
#define MESH_SIZE  1
Buffer::Buffer():mVertexBuffer(-1){

	Plane* plane1 = new Plane();
	int face_count = plane1->faces.size();
	//plane vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	printf("当前创建的 Vertex buffer 为 %d \n", mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	int vertex_buffer_size = sizeof(glm::vec4)*plane1->vertices.size();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &(plane1->vertices[0]), GL_STATIC_DRAW);

	// plane normal buffer
	glGenBuffers(1, &mNormalBuffer);
	printf("当前创建的 normal buffer 为 %d \n", mNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &(plane1->normals[0]), GL_STATIC_DRAW);

	// plane face buffer
	glGenBuffers(1, &mFaceBuffer);
	printf("当前创建的 face buffer 为 %d \n", mFaceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mFaceBuffer);
	int face_buffer_size = sizeof(unsigned int[3])*plane1->faces.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, &(plane1->faces[0]), GL_STATIC_DRAW);
	delete plane1;

	mFaceCount = face_count;
	//glEnable(GL_DEPTH_TEST);
}
Buffer::Buffer(std::string x):mVertexBuffer(-1) {
	if (x == "circle")
	{
		Circle* plane1 = new Circle();
		int face_count = plane1->faces.size();
		//plane vertex buffer
		glGenBuffers(1, &mVertexBuffer);
		printf("当前创建的 Vertex buffer 为 %d \n", mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		int vertex_buffer_size = sizeof(glm::vec4)*plane1->vertices.size();
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &(plane1->vertices[0]), GL_STATIC_DRAW);

		// plane normal buffer
		glGenBuffers(1, &mNormalBuffer);
		printf("当前创建的 normal buffer 为 %d \n", mNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &(plane1->normals[0]), GL_STATIC_DRAW);

		// plane face buffer
		glGenBuffers(1, &mFaceBuffer);
		printf("当前创建的 face buffer 为 %d \n", mFaceBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mFaceBuffer);
		int face_buffer_size = sizeof(unsigned int[3])*plane1->faces.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, face_buffer_size, &(plane1->faces[0]), GL_STATIC_DRAW);
		delete plane1;

		mFaceCount = face_count;
		return;
	}


}

Buffer::~Buffer() {	
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mNormalBuffer);
	glDeleteBuffers(1,&mFaceBuffer);
}

void Buffer::Create() {
	
}