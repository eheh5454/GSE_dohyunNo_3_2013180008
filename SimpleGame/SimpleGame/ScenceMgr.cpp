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

//전체 오브젝트 업데이트 함수 
void ScenceMgr::Update_AllObject(float elaspedtime)
{   
	//obnum이 10이상이 되면 0으로 초기화하여 10개로 제한 
	if (obnum >= 10) {
		obnum = 0;
	}
	if (arrownum >= MAX_OBJECT_COUNT) {
		arrownum = 0;
	}

	// 0.5초마다 화살 생성 
	MakeArrow(elaspedtime);

	// 0.5초마다 총알을 생성 
	MakeBullet(elaspedtime);

	//캐릭터의 Life or Lifetime이 0이하가 되면 삭제해줌 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (m_objects[i] != NULL) {
			m_objects[i]->Update(elaspedtime);
			if (m_objects[i]->Lifetime <= 0.f || m_objects[i]->Life <= 0.f) {
				delete m_objects[i];
				m_objects[i] = NULL;

			}
		}
	}
	
	// arrow의 Life or Lifetime이 0이하가 되면 삭제해줌  
	for (int i = 0; i < arrownum; i++) {
		if (Arrows[i] != NULL) {
			Arrows[i]->Update(elaspedtime);
			if (Arrows[i]->Lifetime <= 0.1f || Arrows[i]->Life <= 0.f) {
				delete Arrows[i];
				Arrows[i] = NULL;
			}
		}
	}
		
	//총알의 Life or Lifetime이 0이하가 되면 삭제해줌 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			Bullets[i]->Update(elaspedtime);
			if (Bullets[i]->Lifetime <= 0.f || Bullets[i]->Life <= 0.f) {
				delete Bullets[i];
				Bullets[i] = NULL;
			}
		}
	}
	//빌딩 Life가 0이하가 되면 제거 
	if (Building != NULL) {
		if (Building->Life <= 0) {
			delete Building;
			Building = NULL;
		}
	}

		
}
//Arrow를 생성해주는 함수
void ScenceMgr::MakeArrow(float elaspedtime)
{	
	for (int i = 0; i < obnum; i++) {
		if (m_objects[i] != NULL) {
			m_objects[i]->arrow_time += (elaspedtime * 0.001f);
			if (m_objects[i]->arrow_time > 0.5f && Arrows[arrownum] == NULL) {
				Object* Arrow = new Object(m_objects[i]->Getx(), m_objects[i]->Gety(), OBJECT_ARROW);
				// arrow마다 id를 설정해준다(arrow를 생성한 캐릭터와의 충돌방지) 
				Arrow->arrow_id = i;
				Arrows[arrownum] = Arrow;
				arrownum++;
				m_objects[i]->arrow_time = 0.f;
			}
			else if (m_objects[i]->arrow_time > 0.5f && Arrows[arrownum] != NULL) {
				delete Arrows[arrownum];
				Object* Arrow = new Object(m_objects[i]->Getx(), m_objects[i]->Gety(), OBJECT_ARROW);
				// arrow마다 id를 설정해준다(arrow를 생성한 캐릭터와의 충돌방지) 
				Arrow->arrow_id = i;
				Arrows[arrownum] = Arrow;
				arrownum++;
				m_objects[i]->arrow_time = 0.f;
			}
		}
	}
}
		
	

//Bullet을 생성해주는 함수 
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

//클릭하는 위치에 캐릭터를 만들어주는 함수 
void ScenceMgr::Clickmake(int x, int y)
{	
	if (m_objects[obnum] == NULL) {
		Object* ob = new Object((float)x - 250, (float)-(y - 400), OBJECT_CHARACTER);
		m_objects[obnum] = ob;
		obnum++;
	}
	
}
//렌더러 함수 
void ScenceMgr::RenderObject()
{
	CollisionTest();
	//캐릭터 렌더 
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

	//빌딩 렌더 
	if (Building != NULL) {
		m_renderer->DrawTexturedRect(Building->Getx(), Building->Gety(), Building->Getz(), Building->Getsize(),
			Building->Getr(), Building->Getg(), Building->Getb(), Building->Geta(),m_texCharacter);
	}

	//총알 렌더 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			m_renderer->DrawSolidRect(Bullets[i]->Getx(), Bullets[i]->Gety(), Bullets[i]->Getz(),
				Bullets[i]->Getsize(), Bullets[i]->Getr(), Bullets[i]->Getg(), Bullets[i]->Getb(), Bullets[i]->Geta());
		}
	}
	//Arrow 렌더 
	for (int i = 0; i < arrownum; i++) {
		if (Arrows[i] != NULL) {
			m_renderer->DrawSolidRect(Arrows[i]->Getx(), Arrows[i]->Gety(), Arrows[i]->Getz(),
				Arrows[i]->Getsize(), Arrows[i]->Getr(), Arrows[i]->Getg(), Arrows[i]->Getb(), Arrows[i]->Geta());
		}
	}
}

//충돌테스트 함수 
void ScenceMgr::CollisionTest()
{
	//캐릭터간의 충돌 
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
	//빌딩과 캐릭터의 충돌	
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
	//총알과 캐릭터의 충돌 
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
	//character와 arrow의 충돌 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_objects[i] != NULL) {
			for (int j = 0; j < arrownum; j++)
			{
				//arrow의 id와 캐릭터의 i가 같으면 continue
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
	//Building과 arrow의 충돌 
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

