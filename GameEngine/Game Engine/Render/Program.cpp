/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<Program.cpp>
Purpose:<implement all functions declared in Program.h, for rendering>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#include"Program.h"
#include"Plane.h"
#include"Texture.h"
#include"..\Math\Affine.h"
#include"..\Math\Matrix2D.h"
#include "glew.h"
#include "glm.hpp"
#include"..\Component\Sprite.h"
#include"..\Component\Transform.h"
#include "..\GameObjectManager.h"
#include<iostream>
#include"../ResourceManager.h"
#include"../Component/Body.h"
#include"../Component/Controller.h"
#define MESH_SIZE 40
using namespace std;
extern GameObjectManager* gpGameObjectManager;


const glm::vec4 O(0.0f, 0.0f, 0.0f, 1.0f),
EX(1.0f, 0.0f, 0.0f, 0.0f),
EY(0.0f, 1.0f, 0.0f, 0.0f),
EZ(0.0f, 0.0f, 1.0f, 0.0f);

Program::Program(int _w, int _h) :fov(100.0f), time(0.0f), eye(glm::vec3(0)) {
	w = _w;
	h = _h;
	aspect = float(w) / float(h);
	time = 0;
	glViewport(0, 0, w, h);
	renderDebug = false;
	showSprite = true;
	//eye = glm::vec2(100,0);
	collisionDebug = false;
	pause = false;
}

Program::~Program(void) {
	for (auto t : mRenderer)
	{
		delete(t.second);
	}

	for (auto t : mBuffer)
	{
		delete t.second;
		//glDeleteBuffers();
	}

}

void Program::resize(int W, int H) {
	aspect = float(W) / float(H);
	w = W;
	h = H;
	glViewport(0, 0, W, H);
}


void Program::Init() {
	Renderer* pR = new Renderer();
	mRenderer["defult"] = pR;
	Buffer*p = new Buffer();
	mBuffer["defult"] = p;

	p = new Buffer("circle");
	mBuffer["circle"] = p;

	glViewport(0, 0, w, h);

	Renderer* pRt = new Renderer("line");
	mRenderer["line"] = pRt;
}


void Program::draw() {
	glClearColor(0.8f, 0.8f, 0.8f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearDepth(1);
	//glClear(GL_DEPTH_BUFFER_BIT);
	Renderer* renderer = mRenderer["defult"];//mRenderer[pS->texture->renderer];
	Buffer* buffer = mBuffer["defult"];
	//glUseProgram(renderer->mGLProgram);
	for (auto go : gpGameObjectManager->GameObjectsRenderList)
	{
		if (go->name == "hell")
		{
			printf("");
		}
		if (pause)
		{
			if (go->name == "player0")
			{
				static_cast<Controller*>(go->GetComponent(CONTROLLER))->Update();
			}
		}
		if (!pause)
		{
			
			go->Update();
		}
		
		if (go->GetComponent(TRANSFORM) != nullptr &&go->GetComponent(SPRITE) && go->isShown == true)
		{

			glUseProgram(renderer->mGLProgram);
			Sprite* pS = static_cast<Sprite*> (go->GetComponent(SPRITE));
			Transform* pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
			//Body* pB = static_cast<Body*> (go->GetComponent(BODY));

		/*	glm::vec4 position((pT->mPos.x - eye.x) / float(w)*2.0f, (pT->mPos.y - eye.y) / float(h)*2.0f, 0.0f, 1.0f);
			glm::mat4 R = rotate(pT->mRotate.x, EY)*rotate(pT->mRotate.y, EZ)* rotate(180, EY)*rotate(180, EZ),
				M = translate(position)*R*scale(1.0f / float(w), 1.0f / float(h), 1.0f)*scale(pS->size.x, pS->size.y, 1.0f); */

			glm::vec4 position(pT->mPos.x, pT->mPos.y, 0.0f, 1.0f);

			glm::mat4 R = rotate(pT->mRotate.x, EY)*rotate(pT->mRotate.y, EZ)* rotate(180, EY)*rotate(180, EZ),
				M = perspective2D(w, h)*view2D(glm::vec4(eye.x, eye.y, eye.z, 0))* translate(position)*R*scale(pS->size.x / 2.0f, pS->size.y / 2.0f, 1.0f);
			if (showSprite)
			{//printf("current img size: x = %f, y = %f \n", pS->size.x, pS->size.y);
				glUniformMatrix4fv(renderer->umodel_matrix, 1, false, (float*)&M);
				glBindBuffer(GL_ARRAY_BUFFER, buffer->mVertexBuffer);
				glVertexAttribPointer(renderer->aposition, 4, GL_FLOAT, false, 0, 0);
				glEnableVertexAttribArray(renderer->aposition);
				glBindTexture(GL_TEXTURE_2D, pS->texture->texture);
				// draw the mesh
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->mFaceBuffer);
				glDrawElements(GL_TRIANGLES, 3 * buffer->mFaceCount, GL_UNSIGNED_INT, 0);
			}


			//debug
			if (renderDebug)
			{
				Renderer* rendererLine = mRenderer["line"];
				glUseProgram(rendererLine->mGLProgram);
				glm::vec4 color(1, 1, 0, 1);
				glUniform4fv(rendererLine->ucolor, 1, (float*)&color);
				glUniformMatrix4fv(rendererLine->umodel_matrix, 1, false, (float*)&M);
				glBindBuffer(GL_ARRAY_BUFFER, buffer->mVertexBuffer);
				glVertexAttribPointer(rendererLine->aposition, 4, GL_FLOAT, false, 0, 0);
				glEnableVertexAttribArray(rendererLine->aposition);
				glDrawArrays(GL_LINE_LOOP, 0, 4);
			}


		}
	}
	if (!collisionDebug)
	{
		return;
	}

	for (auto go : gpGameObjectManager->GameObjectsRenderList)
	{
		Transform* pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
		Body* pB = static_cast<Body*> (go->GetComponent(BODY));
		if (pB != nullptr &&pB->mpShape != nullptr)
		{
			if (pB->mpShape->mType == SHAPE_AABB)
			{
				ShapeAABB* pSh = static_cast<ShapeAABB*>(pB->mpShape);

				Renderer* rendererLine = mRenderer["line"];


				glUseProgram(rendererLine->mGLProgram);
				glm::vec4 color(1, 0, 0, 1);
				glUniform4fv(rendererLine->ucolor, 1, (float*)&color);
				//std::vector<glm::vec4> positionB = {glm::vec4(-1,-1, 0.0f, 1.0f),
				//	glm::vec4(1, -1, 0.0f, 1.0f),
				//	glm::vec4(1, 1, 0.0f, 1.0f),
				//	glm::vec4(-1, 1, 0.0f, 1.0f)
				//};
				//GLuint temp;
				//glGenBuffers(1, &temp);
				////printf("当前创建的 Vertex buffer 为 %d \n", mVertexBuffer);
				//glBindBuffer(GL_ARRAY_BUFFER, temp);
				//int vertex_buffer_size = sizeof(glm::vec4)*4;
				//glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &positionB[0], GL_STATIC_DRAW);
				glm::vec4 position = glm::vec4(pT->mPos.x + (pSh->mLeft + pSh->mRight) / 2.0f, pT->mPos.y + (pSh->mTop + pSh->mBottom) / 2.0f, 0.0f, 1.0f);

				glm::mat4 M = perspective2D(w, h)*view2D(glm::vec4(eye.x, eye.y, eye.z, 0))* translate(position)*scale((pSh->mRight - pSh->mLeft) / 2.0f, (pSh->mTop - pSh->mBottom) / 2.0f, 1.0f);


				glUniformMatrix4fv(rendererLine->umodel_matrix, 1, false, (float*)&M);
				glBindBuffer(GL_ARRAY_BUFFER, buffer->mVertexBuffer);
				glVertexAttribPointer(rendererLine->aposition, 4, GL_FLOAT, false, 0, 0);
				glEnableVertexAttribArray(rendererLine->aposition);
				glDrawArrays(GL_LINE_LOOP, 0, 4);
				//glDeleteBuffers(1,&temp);
			}
		}



	}


	for (auto go : gpGameObjectManager->GameObjectsRenderList)
	{
		Transform* pT = static_cast<Transform*> (go->GetComponent(TRANSFORM));
		Body* pB = static_cast<Body*> (go->GetComponent(BODY));
		if (pB != nullptr &&pB->mpShape != nullptr) {

			if (pB->mpShape->mType == SHAPE_CIRCLE)
			{
				ShapeCircle* pSh = static_cast<ShapeCircle*>(pB->mpShape);

				Renderer* rendererLine = mRenderer["line"];
				buffer = mBuffer["circle"];

				glUseProgram(rendererLine->mGLProgram);
				glm::vec4 color(0, 0, 1, 1);
				glUniform4fv(rendererLine->ucolor, 1, (float*)&color);
				glm::vec4 position = glm::vec4(pT->mPos.x , pT->mPos.y, 0.0f, 1.0f);

				glm::mat4 M = perspective2D(w, h)*view2D(glm::vec4(eye.x, eye.y, eye.z, 0))* translate(position)*scale(pSh->mRadius, pSh->mRadius, 1.0f);


				glUniformMatrix4fv(rendererLine->umodel_matrix, 1, false, (float*)&M);
				glBindBuffer(GL_ARRAY_BUFFER, buffer->mVertexBuffer);
				glVertexAttribPointer(rendererLine->aposition, 4, GL_FLOAT, false, 0, 0);
				glEnableVertexAttribArray(rendererLine->aposition);
				glDrawArrays(GL_LINE_LOOP, 0, 60);
				//glDeleteBuffers(1,&temp);
			}
		}
	}
}