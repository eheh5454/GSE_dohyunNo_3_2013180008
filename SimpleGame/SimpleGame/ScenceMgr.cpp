#include "stdafx.h"
#include "ScenceMgr.h"
#include "Renderer.h"
#include "Object.h"

ScenceMgr::ScenceMgr(int width,int height):obnum(0),bulletnum(0),time(0),bullettime(0),arrownum(0)
{
	m_renderer = new Renderer(width, height);
	m_texCharacter = m_renderer->CreatePngTexture("./Resource/Building.png");


	if (!m_renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. " << endl;
	}

}

ScenceMgr::~ScenceMgr()
{	
	
}

//��ü ������Ʈ ������Ʈ �Լ� 
void ScenceMgr::Update_AllObject(float elaspedtime)
{   
	//obnum�� 10�̻��� �Ǹ� 0���� �ʱ�ȭ�Ͽ� 10���� ���� 
	if (obnum >= 10) {
		obnum = 0;
	}
	if (arrownum >= MAX_OBJECT_COUNT) {
		arrownum = 0;
	}

	// 0.5�ʸ��� ȭ�� ���� 
	MakeArrow(elaspedtime);

	// 0.5�ʸ��� �Ѿ��� ���� 
	MakeBullet(elaspedtime);

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
	
	// arrow�� Life or Lifetime�� 0���ϰ� �Ǹ� ��������  
	for (int i = 0; i < arrownum; i++) {
		if (Arrows[i] != NULL) {
			Arrows[i]->Update(elaspedtime);
			if (Arrows[i]->Lifetime <= 0.1f || Arrows[i]->Life <= 0.f) {
				delete Arrows[i];
				Arrows[i] = NULL;
			}
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
//Arrow�� �������ִ� �Լ�
void ScenceMgr::MakeArrow(float elaspedtime)
{	
	for (int i = 0; i < obnum; i++) {
		if (m_objects[i] != NULL) {
			m_objects[i]->arrow_time += (elaspedtime * 0.001f);
			if (m_objects[i]->arrow_time > 0.5f && Arrows[arrownum] == NULL) {
				Object* Arrow = new Object(m_objects[i]->Getx(), m_objects[i]->Gety(), OBJECT_ARROW);
				// arrow���� id�� �������ش�(arrow�� ������ ĳ���Ϳ��� �浹����) 
				Arrow->arrow_id = i;
				Arrows[arrownum] = Arrow;
				arrownum++;
				m_objects[i]->arrow_time = 0.f;
			}
			else if (m_objects[i]->arrow_time > 0.5f && Arrows[arrownum] != NULL) {
				delete Arrows[arrownum];
				Object* Arrow = new Object(m_objects[i]->Getx(), m_objects[i]->Gety(), OBJECT_ARROW);
				// arrow���� id�� �������ش�(arrow�� ������ ĳ���Ϳ��� �浹����) 
				Arrow->arrow_id = i;
				Arrows[arrownum] = Arrow;
				arrownum++;
				m_objects[i]->arrow_time = 0.f;
			}
		}
	}
}
		
	

//Bullet�� �������ִ� �Լ� 
void ScenceMgr::MakeBullet(float elaspedtime)
{
	if (Building != NULL) {
		bullettime += (elaspedtime*0.001f);
		if (bulletnum < MAX_OBJECT_COUNT) {
			if (bullettime >= 0.5f) {
				Object* bullet = new Object(0.f, 0.f, OBJECT_BULLET);
				Bullets[bulletnum] = bullet;
				bulletnum++;
				bullettime = 0;
			}

		}
	}
}

//Ŭ���ϴ� ��ġ�� ĳ���͸� ������ִ� �Լ� 
void ScenceMgr::Clickmake(int x, int y)
{	
	if (m_objects[obnum] == NULL) {
		Object* ob = new Object((float)x - 250, (float)-(y - 400), OBJECT_CHARACTER);
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
		m_renderer->DrawTexturedRect(Building->Getx(), Building->Gety(), Building->Getz(), Building->Getsize(),
			Building->Getr(), Building->Getg(), Building->Getb(), Building->Geta(),m_texCharacter);
	}

	//�Ѿ� ���� 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			m_renderer->DrawSolidRect(Bullets[i]->Getx(), Bullets[i]->Gety(), Bullets[i]->Getz(),
				Bullets[i]->Getsize(), Bullets[i]->Getr(), Bullets[i]->Getg(), Bullets[i]->Getb(), Bullets[i]->Geta());
		}
	}
	//Arrow ���� 
	for (int i = 0; i < arrownum; i++) {
		if (Arrows[i] != NULL) {
			m_renderer->DrawSolidRect(Arrows[i]->Getx(), Arrows[i]->Gety(), Arrows[i]->Getz(),
				Arrows[i]->Getsize(), Arrows[i]->Getr(), Arrows[i]->Getg(), Arrows[i]->Getb(), Arrows[i]->Geta());
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
				cout << "Building HP:" << Building->Life << endl;
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
	//character�� arrow�� �浹 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_objects[i] != NULL) {
			for (int j = 0; j < arrownum; j++)
			{
				//arrow�� id�� ĳ������ i�� ������ continue
				if (Arrows[j] != NULL && Arrows[j]->arrow_id == i)
				{
					continue;
				}

				if (Arrows[j] != NULL) {
					if ((m_objects[i]->Getx() - m_objects[i]->Getsize() / 2.f) < (Arrows[j]->Getx() + Arrows[j]->Getsize() / 2.f) &&
						(m_objects[i]->Getx() + m_objects[i]->Getsize() / 2.f) > (Arrows[j]->Getx() - Arrows[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() - m_objects[i]->Getsize() / 2.f) < (Arrows[j]->Gety() + Arrows[j]->Getsize() / 2.f) &&
						(m_objects[i]->Gety() + m_objects[i]->Getsize() / 2.f) > (Arrows[j]->Gety() - Arrows[j]->Getsize() / 2.f)) 
					{
						m_objects[i]->Life -= Arrows[j]->Life;
					}
				
				}
			}
		}
	}
	//Building�� arrow�� �浹 
	for (int i = 0; i < arrownum; i++)
	{
		if (Building != NULL && Arrows[i] != NULL) {
			if ((Building->Getx() - Building->Getsize() / 2.f) < (Arrows[i]->Getx() + Arrows[i]->Getsize() / 2.f) &&
				(Building->Getx() + Building->Getsize() / 2.f) > (Arrows[i]->Getx() - Arrows[i]->Getsize() / 2.f) &&
				(Building->Gety() - Building->Getsize() / 2.f) < (Arrows[i]->Gety() + Arrows[i]->Getsize() / 2.f) &&
				(Building->Gety() + Building->Getsize() / 2.f) > (Arrows[i]->Gety() - Arrows[i]->Getsize() / 2.f))
			{
				Building->Life -= Arrows[i]->Life;
				Arrows[i]->Life = 0;
				cout << "Building HP:" << Building->Life << endl;
			}
		}

	}
	
}

