/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"
Renderer *g_Renderer = NULL;
Object* ob1 = new Object(50.0f, 50.0f, 0.0f, 20.0f, 20.0f, 10.0f, 40.0f, 30.0f, 0.01f);
Object* oblist[100];
int obnum = 0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	
	g_Renderer->DrawSolidRect(ob1->Getx(), ob1->Gety(), ob1->Getz(), ob1->Getsize(), ob1->Getr(), ob1->Getg(), ob1->Getb(), ob1->Geta());
	for (int i = 0; i < obnum; i++)
	{
		g_Renderer->DrawSolidRect(oblist[i]->Getx(), oblist[i]->Gety(), oblist[i]->Getz(), oblist[i]->Getsize(), oblist[i]->Getr(), oblist[i]->Getg(), oblist[i]->Getb(), oblist[i]->Geta());
		oblist[i]->Update();
	}
	
	// Renderer Test
	g_Renderer->DrawSolidRect(30, 30, 0, 40, 10, 20, 30, 40);
	ob1->Update();
	glutSwapBuffers();
	
}

void Idle(void)
{
	
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// ÁÂÇ¥º¯È¯x -250, -(y-250) 
		//ob1->Setx(x - 250);
		//ob1->Sety(-(y - 250));
		Object* ob = new Object(x - 250, -(y - 250), 0.0f, 20.0f, 20.0f, 10.0f, 40.0f, 30.0f, 0.01f);
		oblist[obnum] = ob;
		obnum++;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

void makeob(float x,float y)
{
	
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");
	
	glewInit();
	
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	
	glutMainLoop();
	
	delete g_Renderer;
	delete ob1;
	delete[] oblist;

    return 0;
}

