
#include "stdafx.h"
#include "ScenceMgr.h"
#include "Renderer.h"
#include "Object.h"

ScenceMgr::ScenceMgr(int width,int height):obnum(0)
{
	m_renderer = new Renderer(width, height);
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		m_objects[i] = NULL;
	}

	if (!m_renderer->IsInitialized())
	{
	std::cout << "Renderer could not be initialized.. \n";
	}

}


ScenceMgr::~ScenceMgr()
{	
	
}


void ScenceMgr::Update_AllObject(void)
{
	if (obnum >= 10) {
		obnum = 0;
	}
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (m_objects[i] != NULL) {
			m_objects[i]->Update();
			if (m_objects[i]->GetLifetime() == 0.f || m_objects[i]->Life == 0.f) {
				delete m_objects[i];

			}
		}
	}
		
}

void ScenceMgr::Clickmake(int x, int y)
{	
	if (m_objects[obnum] == NULL) {
		Object* ob = new Object(x - 250, -(y - 250), 0.0f, 20.0f, 20.0f, 10.0f, 40.0f, 30.0f);
		m_objects[obnum] = ob;
		obnum++;
	}
}

void ScenceMgr::RenderObject()
{
	CollisionTest();
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_objects[i] != NULL) 
		{
			m_renderer->DrawSolidRect(m_objects[i]->Getx(), m_objects[i]->Gety(),
				m_objects[i]->Getz(), m_objects[i]->Getsize(),
				m_objects[i]->Getr(), m_objects[i]->Getg(),
				m_objects[i]->Getb(), m_objects[i]->Geta());
		}

	}
	
}

void ScenceMgr::CollisionTest()
{
	
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
			for (int j = 0; j < MAX_OBJECT_COUNT; j++)
			{
				if (m_objects[j] != NULL && m_objects[i] != NULL) {
					if ((m_objects[i]->Getx() - m_objects[i]->Getsize() / 2) < (m_objects[j]->Getx() + m_objects[j]->Getsize() / 2) &&
						(m_objects[i]->Getx() + m_objects[i]->Getsize() / 2) > (m_objects[j]->Getx() - m_objects[j]->Getsize() / 2))
					{
						m_objects[i]->r = 1, m_objects[i]->g = 0, m_objects[i]->b = 0;
						//m_objects[i]->Life -= 0.5f;
					}
					else if ((m_objects[i]->Gety() - m_objects[i]->Getsize() / 2) < (m_objects[j]->Gety() + m_objects[j]->Getsize() / 2) &&
						(m_objects[i]->Gety() + m_objects[i]->Getsize() / 2) > (m_objects[j]->Gety() - m_objects[j]->Getsize() / 2))
					{
						m_objects[i]->r = 1, m_objects[i]->g = 0, m_objects[i]->b = 0;
						//m_objects[i]->Life -= 0.5f;
					}

					else
						m_objects[i]->r = 1, m_objects[i]->g = 1, m_objects[i]->b = 1;
				}

			}
	}
}
	
