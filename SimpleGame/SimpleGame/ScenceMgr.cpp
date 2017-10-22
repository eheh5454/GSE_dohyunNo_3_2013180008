
#include "stdafx.h"
#include "ScenceMgr.h"
#include "Renderer.h"
#include "Object.h"

ScenceMgr::ScenceMgr()
{
	obnum = 50;
	
	for (int i = 0; i < obnum; i++) {
		float x = -250 + rand() % 500;
		float y = -250 + rand() % 500;
		Object* ob = new Object(x, y, 0.0f, 5.0f, 20.0f, 10.0f, 40.0f, 30.0f, 0.01f);
		m_objects[i] = ob;
	}
}

ScenceMgr::~ScenceMgr()
{
	delete[] m_objects;
	
}


void ScenceMgr::Update_AllObject(void)
{
	for (int i = 0; i < obnum; i++) {
		m_objects[i]->Update();
	}
	
}

void ScenceMgr::RenderObject(Renderer *Renderer)
{
	for (int i = 0; i < obnum; i++)
	{
	    Renderer->DrawSolidRect(m_objects[i]->Getx(), m_objects[i]->Gety(),
			                    m_objects[i]->Getz(), m_objects[i]->Getsize(),
			                    m_objects[i]->Getr(), m_objects[i]->Getg(),
			                    m_objects[i]->Getb(), m_objects[i]->Geta());

		//oblist[i]->Update();
	}
}