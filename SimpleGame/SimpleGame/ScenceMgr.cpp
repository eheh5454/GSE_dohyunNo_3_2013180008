#include "stdafx.h"
#include "ScenceMgr.h"
#include "Renderer.h"
#include "Object.h"

ScenceMgr::ScenceMgr(int width,int height):obnum(0),bulletnum(0),time(0)
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

//��ü ������Ʈ ������Ʈ �Լ� 
void ScenceMgr::Update_AllObject(float elaspedtime)
{   //obnum�� 10�̻��� �Ǹ� 0���� �ʱ�ȭ�Ͽ� 10���� ���� 
	if (obnum >= 10) {
		obnum = 0;
	}
	//ĳ������ Life or Lifetime�� 0���ϰ� �Ǹ� �������� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (m_objects[i] != NULL) {
			m_objects[i]->Update(elaspedtime);
			if (m_objects[i]->Lifetime <= 0.f || m_objects[i]->Life <= 0.f) {
				delete m_objects[i];
				m_objects[i] = NULL;

			}
		}
	}
	// 0.5�ʸ��� �Ѿ��� ���� 
	time += (elaspedtime*0.001f);
	cout << time << endl;
	if (bulletnum < MAX_OBJECT_COUNT) {
		if (time >= 0.5f) {
			MakeBullet();
			time = 0;
		}
	}
		
	//�Ѿ��� Life or Lifetime�� 0���ϰ� �Ǹ� �������� 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			Bullets[i]->Update(elaspedtime);
			if (Bullets[i]->Lifetime <= 0.f || Bullets[i]->Life <= 0.f) {
				delete Bullets[i];
				Bullets[i] = NULL;
			}
		}
	}
	//���� Life�� 0���ϰ� �Ǹ� ���� 
	if (Building != NULL) {
		if (Building->Life <= 0) {
			delete Building;
			Building = NULL;
		}
	}

		
}
//Bullet�� �������ִ� �Լ� 
void ScenceMgr::MakeBullet()
{
	Object* bullet = new Object(0.f, 0.f, OBJECT_BULLET);
	Bullets[bulletnum] = bullet;
	bulletnum++;

}
//Ŭ���ϴ� ��ġ�� ĳ���͸� ������ִ� �Լ� 
void ScenceMgr::Clickmake(int x, int y)
{	
	if (m_objects[obnum] == NULL) {
		Object* ob = new Object((float)x - 250, (float)-(y - 250), OBJECT_CHARACTER);
		m_objects[obnum] = ob;
		obnum++;
	}
	
}
//������ �Լ� 
void ScenceMgr::RenderObject()
{
	CollisionTest();
	//ĳ���� ���� 
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

	//���� ���� 
	if (Building != NULL) {
		m_renderer->DrawSolidRect(Building->Getx(), Building->Gety(), Building->Getz(), Building->Getsize(),
			Building->Getr(), Building->Getg(), Building->Getb(), Building->Geta());
	}

	//�Ѿ� ���� 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			m_renderer->DrawSolidRect(Bullets[i]->Getx(), Bullets[i]->Gety(), Bullets[i]->Getz(),
				Bullets[i]->Getsize(), Bullets[i]->Getr(), Bullets[i]->Getg(), Bullets[i]->Getb(), Bullets[i]->Geta());
		}
	}
}

//�浹�׽�Ʈ �Լ� 
void ScenceMgr::CollisionTest()
{
	//ĳ���Ͱ��� �浹 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		bool check = false;
		if (m_objects[i] != NULL) {
			for (int j = 0; j < MAX_OBJECT_COUNT; j++)
			{
				if (i == j)
					continue;
				if (m_objects[j] != NULL) {
					if ((m_objects[i]->Getx() - m_objects[i]->Getsize() / 2.f) < (m_objects[j]->Getx() + m_objects[j]->Getsize() / 2.f) &&
						(m_objects[i]->Getx() + m_objects[i]->Getsize() / 2.f) > (m_objects[j]->Getx() - m_objects[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() - m_objects[i]->Getsize() / 2.f) < (m_objects[j]->Gety() + m_objects[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() + m_objects[i]->Getsize() / 2.f) > (m_objects[j]->Gety() - m_objects[j]->Getsize() / 2.f))
						check = true;
				}
			}
			if (check) {
				m_objects[i]->r = 1, m_objects[i]->g = 0, m_objects[i]->b = 0, m_objects[i]->a = 1;
			}
			else {
				m_objects[i]->r = 1, m_objects[i]->g = 1, m_objects[i]->b = 1, m_objects[i]->a = 1;
			}

		}
	}
	//������ ĳ������ �浹	
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Building != NULL && m_objects[i] != NULL) {
			if ((Building->Getx() - Building->Getsize() / 2.f) < (m_objects[i]->Getx() + m_objects[i]->Getsize() / 2.f) &&
				(Building->Getx() + Building->Getsize() / 2.f) > (m_objects[i]->Getx() - m_objects[i]->Getsize() / 2.f) &&
				(Building->Gety() - Building->Getsize() / 2.f) < (m_objects[i]->Gety() + m_objects[i]->Getsize() / 2.f) &&
				(Building->Gety() + Building->Getsize() / 2.f) > (m_objects[i]->Gety() - m_objects[i]->Getsize() / 2.f))
			{
				Building->Life -= m_objects[i]->Life;
				m_objects[i]->Life = 0;
				cout << Building->Life << endl;
			}
		}

	}
	//�Ѿ˰� ĳ������ �浹 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_objects[i] != NULL) {
			for (int j = 0; j < bulletnum; j++)
			{				
				if (Bullets[j] != NULL) {
					if ((m_objects[i]->Getx() - m_objects[i]->Getsize() / 2.f) < (Bullets[j]->Getx() + Bullets[j]->Getsize() / 2.f) &&
						(m_objects[i]->Getx() + m_objects[i]->Getsize() / 2.f) > (Bullets[j]->Getx() - Bullets[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() - m_objects[i]->Getsize() / 2.f) < (Bullets[j]->Gety() + Bullets[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() + m_objects[i]->Getsize() / 2.f) > (Bullets[j]->Gety() - Bullets[j]->Getsize() / 2.f))
						m_objects[i]->Life -= Bullets[j]->Life;
				}
			}	
		}
	}
	
}

