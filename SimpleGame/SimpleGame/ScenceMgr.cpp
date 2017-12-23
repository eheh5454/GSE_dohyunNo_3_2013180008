#include "stdafx.h"
#include "ScenceMgr.h"
#include "Renderer.h"
#include "Object.h"


ScenceMgr::ScenceMgr(int width,int height):allynum(0),bulletnum(0),time(0.f),bullettime(0),arrownum(0),eyemonster_time(0), character_frame(0), enermynum(0), koromon_time(0)
{
	m_renderer = new Renderer(width, height);
	m_texbuilding1 = m_renderer->CreatePngTexture("./Resource/Building.png");
	m_texbuilding2 = m_renderer->CreatePngTexture("./Resource/Egg.png");
	m_texbackground = m_renderer->CreatePngTexture("./Resource/background.png");
	m_texeyemonster = m_renderer->CreatePngTexture("./Resource/Eye_monster.png");
	m_texagumon = m_renderer->CreatePngTexture("./Resource/agumon.png");
	m_texparticle = m_renderer->CreatePngTexture("./Resource/particle.png");
	m_texstar = m_renderer->CreatePngTexture("./Resource/star.png");
	m_texgreymon = m_renderer->CreatePngTexture("./Resource/greymon.png");
	m_texmetalgreymon = m_renderer->CreatePngTexture("./Resource/metalgreymon.png");
	m_texevolution = m_renderer->CreatePngTexture("./Resource/evolution.png");
	m_texkoromon = m_renderer->CreatePngTexture("./Resource/koromon.png");
	m_texkoromon_arrow = m_renderer->CreatePngTexture("./Resource/koromon_arrow.png");
	m_texalien = m_renderer->CreatePngTexture("./Resource/Alien.png");
	
	Object* building1 = new Object(-150.f, 300.f, TEAM1_BUILDING);
	Object* building2 = new Object(0.f, 300.f, TEAM1_BUILDING);
	Object* building3 = new Object(150.f, 300.f, TEAM1_BUILDING);
	Object* building4 = new Object(-150.f, -300.f, TEAM2_BUILDING);
	Object* building5 = new Object(0.f, -300.f, TEAM2_BUILDING);
	Object* building6 = new Object(150.f, -300.f, TEAM2_BUILDING);
	soundBG = m_sound->CreateSound("./Resource/BGM.mp3");
	m_sound->PlaySoundW(soundBG, true, 20.f);

	building1->team = 1, building2->team = 1, building3->team = 1;
	building4->team = 2, building5->team = 2, building6->team = 2;

	Building[0] = building1;
	Building[1] = building2;
	Building[2] = building3; 
	Building[3] = building4;
	Building[4] = building5;
	Building[5] = building6;

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
    CollisionTest();

	if (arrownum >= MAX_OBJECT_COUNT) {
		arrownum = 0;
	}
	
	
	MakeArrow(elaspedtime);

	MakeCharacter(elaspedtime);

	MakeBullet(elaspedtime);

	agumon_time += elaspedtime * 0.001f;

	time += elaspedtime * 0.001f;
	
	if (character_frame > 8.f) {
		character_frame = 0.f;
	}

	character_frame += (elaspedtime * 0.001f) * 5.f;


	//ĳ������ Life or Lifetime�� 0���ϰ� �Ǹ� �������� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Dizimons[i] != NULL) {
			Dizimons[i]->Update(elaspedtime);
			if (Dizimons[i]->Lifetime <= 0.f || Dizimons[i]->Life <= 0.f) {
				delete Dizimons[i];
				Dizimons[i] = NULL;

			}
		}
	}

	//������ Life or Lifetime�� 0���ϰ� �Ǹ� �������� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Enermys[i] != NULL) {
			Enermys[i]->Update(elaspedtime);
			if (Enermys[i]->Lifetime <= 0.f || Enermys[i]->Life <= 0.f) {
				delete Enermys[i];
				Enermys[i] = NULL;

			}
		}
	}
	
	// arrow�� Life or Lifetime�� 0���ϰ� �Ǹ� ��������  
	for (int i = 0; i < arrownum; i++) {
		if (Arrows[i] != NULL) {
			Arrows[i]->bullet_arrow_Update(elaspedtime);
			if (Arrows[i]->Lifetime <= 0.1f || Arrows[i]->Life <= 0.f || Arrows[i]->Getx() > 250 || Arrows[i]->Getx() < -250 || Arrows[i]->Gety() > 400 || Arrows[i]->Gety() < -400) {
				delete Arrows[i];
				Arrows[i] = NULL;
			}
		}
	}
		
	//�Ѿ��� Life or Lifetime�� 0���ϰ� �Ǹ� �������� 
	for (int i = 0; i < bulletnum; i++) {
		if (Bullets[i] != NULL) {
			Bullets[i]->bullet_arrow_Update(elaspedtime);
			if (Bullets[i]->Lifetime <= 0.f || Bullets[i]->Life <= 0.f || Bullets[i]->Getx() > 250 || Bullets[i]->Getx() < -250 || Bullets[i]->Gety() > 400 || Bullets[i]->Gety() < -400) {
				delete Bullets[i];
				Bullets[i] = NULL;
			}
		}
	}
	
	//���� Life�� 0���ϰ� �Ǹ� ���� 
	for (int i = 0; i < 6; i++) {
		if (Building[i] != NULL) {
			if (Building[i]->Life <= 0) {
				delete Building[i];
				Building[i] = NULL;
			}
		}
	}

		
}
// character���� 3�ʸ��� Arrow�� �������ִ� �Լ�
void ScenceMgr::MakeArrow(float elaspedtime)
{	
	//�Ʊ��� arrow ����
	for (int i = 0; i < allynum; i++) {
		if (Dizimons[i] != NULL) {
			Dizimons[i]->arrow_time += (elaspedtime * 0.001f);
			if (Dizimons[i]->arrow_time > 3.f && Arrows[arrownum] == NULL) {
				Object* Arrow = new Object(Dizimons[i]->Getx(), Dizimons[i]->Gety(), TEAM2_ARROW);
				Arrow->team = Dizimons[i]->team;
				Arrow->Settype("koromon_arrow");
				Arrows[arrownum] = Arrow;
				arrownum++;
				Dizimons[i]->arrow_time = 0.f;
			}
		}
	}
	//������ arrow ���� 
	for (int i = 0; i < enermynum; i++) {
		if (Enermys[i] != NULL) {
			Enermys[i]->arrow_time += (elaspedtime * 0.001f);
			if (Enermys[i]->arrow_time > 3.f && Arrows[arrownum] == NULL) {
				Object* Arrow = new Object(Enermys[i]->Getx(), Enermys[i]->Gety(), TEAM1_ARROW);
				Arrow->team = Enermys[i]->team;
				Arrows[arrownum] = Arrow;
				arrownum++;
				Enermys[i]->arrow_time = 0.f;
			}	
		}
	}
}

//Building���� 10�ʴ� Bullet�� �����ϴ� �Լ� 
void ScenceMgr::MakeBullet(float elaspedtime) 
{
	bullettime += (elaspedtime * 0.001f);
	if (bullettime >= 5.f) {
		for (int i = 0; i < 6; i++) {
			if (Building[i] != NULL) {
				if (i < 3) {
					Object* bullet = new Object(Building[i]->Getx(), Building[i]->Gety(), TEAM1_BULLET);
					Bullets[bulletnum] = bullet;
					Bullets[bulletnum]->team = 1;
					bulletnum++;
				}
				else {
					Object* bullet = new Object(Building[i]->Getx(), Building[i]->Gety(), TEAM2_BULLET);
					Bullets[bulletnum] = bullet;
					Bullets[bulletnum]->team = 2;					
					bulletnum++;
				}
			}
		}
		bullettime = 0;
	}
	

}
	
//���� �ֱ�� ���� ���� 
void ScenceMgr::MakeCharacter(float elaspedtime)
{
	eyemonster_time += elaspedtime * 0.001f;
	koromon_time += elaspedtime * 0.001f;
	alien_time += elaspedtime * 0.001f;
	if (eyemonster_time > 5.f) {
		Object *eyemonster = new Object(rand()%500-250,rand()%400, EYE_MONSTER);
		eyemonster->team = 1;
		eyemonster->Settype("Eye");
		Enermys[enermynum] = eyemonster;
		enermynum++;
		eyemonster_time = 0.f;
		}

	if (alien_time > 5.f) {
		Object *alien = new Object(rand() % 500 - 250, rand() % 400, ALIEN);
		alien->team = 1;
		alien->Settype("Alien");
		Enermys[enermynum] = alien;
		enermynum++;
		alien_time = 0.f;
	}

	if (koromon_time > 5.f) {
		Object *koromon = new Object(rand() % 500 - 250, rand() % 400 - 400, KOROMON);
		koromon->team = 2;
		koromon->Settype("koromon");
		Dizimons[allynum] = koromon;
		allynum++;
		koromon_time = 0.f;
	}

	
}

//Ŭ���ϴ� ��ġ�� �Ʊ����� ���� 
void ScenceMgr::Clickmake(int x, int y)
{	
	if (Dizimons[allynum] == NULL && agumon_time > 5.0f) {
		if ((float)-(y - 400) < 0) {
			Object* agumon = new Object((float)x - 250, (float)-(y - 400), AGUMON);
			agumon->team = 2;
			agumon->Settype("agumon");
			agumon->xspeed = 0;
			agumon->yspeed = 50.f;
			Dizimons[allynum] = agumon;
			allynum++;
			agumon_time = 0.f;
		}
	}	
}
//������ �Լ� 
void ScenceMgr::RenderObject()
{
	//���ȭ�� ���� 
	m_renderer->DrawTexturedRect(0.f,0.f,0.f,800.f,1.f,1.f,1.f,1.f,m_texbackground, 0.4f);
	//ĳ���� ���� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (Dizimons[i] != NULL)
		{
			//agumon ����, evolution time�� ���� ��ȭ		
			if (Dizimons[i]->evolutiontime > 20.f && Dizimons[i]->Gettype().compare("agumon")==0) {
				m_renderer->DrawTexturedRectSeq(Dizimons[i]->Getx(), Dizimons[i]->Gety(),
					Dizimons[i]->Getz(), Dizimons[i]->Getsize(),
					Dizimons[i]->Getr(), Dizimons[i]->Getg(),
					Dizimons[i]->Getb(), Dizimons[i]->Geta(), m_texmetalgreymon, (int)character_frame, 0, 4, 1, Dizimons[i]->level);
			}
			else if (Dizimons[i]->evolutiontime > 10.f && Dizimons[i]->Gettype().compare("agumon")==0) {
				m_renderer->DrawTexturedRectSeq(Dizimons[i]->Getx(), Dizimons[i]->Gety(),
					Dizimons[i]->Getz(), Dizimons[i]->Getsize(),
					Dizimons[i]->Getr(), Dizimons[i]->Getg(),
					Dizimons[i]->Getb(), Dizimons[i]->Geta(), m_texgreymon, (int)character_frame, 0, 6, 1, Dizimons[i]->level);
			}
			else if (Dizimons[i]->Gettype().compare("agumon")==0){
				m_renderer->DrawTexturedRectSeq(Dizimons[i]->Getx(), Dizimons[i]->Gety(),
					Dizimons[i]->Getz(), Dizimons[i]->Getsize(),
					Dizimons[i]->Getr(), Dizimons[i]->Getg(),
					Dizimons[i]->Getb(), Dizimons[i]->Geta(), m_texagumon, (int)character_frame, 0, 6, 1, Dizimons[i]->level);
			}
			else if (Dizimons[i]->Gettype().compare("koromon")==0) {
				m_renderer->DrawTexturedRectSeq(Dizimons[i]->Getx(), Dizimons[i]->Gety(),
					Dizimons[i]->Getz(), Dizimons[i]->Getsize(),
					Dizimons[i]->Getr(), Dizimons[i]->Getg(),
					Dizimons[i]->Getb(), Dizimons[i]->Geta(), m_texkoromon, (int)character_frame, 0, 4, 1, Dizimons[i]->level);
			}
		}
	}
	
	//���� eyemonster ����
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Enermys[i] != NULL) {
			if (Enermys[i]->Gettype().compare("Eye")==0) {
				m_renderer->DrawTexturedRectSeq(Enermys[i]->Getx(), Enermys[i]->Gety(),
					Enermys[i]->Getz(), Enermys[i]->Getsize(),
					Enermys[i]->Getr(), Enermys[i]->Getg(),
					Enermys[i]->Getb(), Enermys[i]->Geta(), m_texeyemonster, (int)character_frame, 0, 8, 1, Enermys[i]->level);
			}
			if (Enermys[i]->Gettype().compare("Alien") == 0) {
				m_renderer->DrawTexturedRectSeq(Enermys[i]->Getx(), Enermys[i]->Gety(),
					Enermys[i]->Getz(), Enermys[i]->Getsize(),
					Enermys[i]->Getr(), Enermys[i]->Getg(),
					Enermys[i]->Getb(), Enermys[i]->Geta(), m_texalien, (int)character_frame, 0, 8, 1, Enermys[i]->level);
			}
		}
	}

	//���� ���� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Building[i] != NULL) {
			if (Building[i]->team == 1) {
				m_renderer->DrawTexturedRect(Building[i]->Getx(), Building[i]->Gety(), Building[i]->Getz(), Building[i]->Getsize(),
					Building[i]->Getr(), Building[i]->Getg(), Building[i]->Getb(), Building[i]->Geta(), m_texbuilding1,Building[i]->level);
			}
			else if (Building[i]->team == 2) {
				m_renderer->DrawTexturedRect(Building[i]->Getx(), Building[i]->Gety(), Building[i]->Getz(), Building[i]->Getsize(),
					Building[i]->Getr(), Building[i]->Getg(), Building[i]->Getb(), Building[i]->Geta(), m_texbuilding2, Building[i]->level);
			}
		}
	}

	//�Ѿ� ���� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Bullets[i] != NULL) {
				m_renderer->DrawParticle(Bullets[i]->Getx(), Bullets[i]->Gety(), Bullets[i]->Getz(),
					Bullets[i]->Getsize(), Bullets[i]->Getr(), Bullets[i]->Getg(), Bullets[i]->Getb(), Bullets[i]->Geta(), -(Bullets[i]->xspeed*0.01f), -(Bullets[i]->yspeed*0.01f), m_texparticle, Bullets[i]->particletime, 0.1f);
		}
	}
	//Arrow ���� 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		if (Arrows[i] != NULL) {
			if (Arrows[i]->Gettype().compare("koromon_arrow") == 0)
			{
				m_renderer->DrawTexturedRect(Arrows[i]->Getx(), Arrows[i]->Gety(), Arrows[i]->Getz(),
					Arrows[i]->Getsize(), Arrows[i]->Getr(), Arrows[i]->Getg(), Arrows[i]->Getb(), Arrows[i]->Geta(),m_texkoromon_arrow, Arrows[i]->level);
			}
			else {
				m_renderer->DrawSolidRect(Arrows[i]->Getx(), Arrows[i]->Gety(), Arrows[i]->Getz(),
					Arrows[i]->Getsize(), Arrows[i]->Getr(), Arrows[i]->Getg(), Arrows[i]->Getb(), Arrows[i]->Geta(), Arrows[i]->level);
			}
		}
	}
	//Building Gauge ����
	for (int i = 0; i < 6; i++) {
		if (Building[i] != NULL) {
			if (Building[i]->team == 1)
				m_renderer->DrawSolidRectGauge(Building[i]->Getx(), Building[i]->Gety() + 60.f, 0.f, Building[i]->Getsize(), Building[i]->Getsize() / 10.f, 1.0f, 0.f, 0.f, 1.f, Building[i]->Life / 500.f, 0.1f);
			else if(Building[i]->team == 2)
				m_renderer->DrawSolidRectGauge(Building[i]->Getx(), Building[i]->Gety() + 60.f, 0.f, Building[i]->Getsize(), Building[i]->Getsize() / 10.f, 0.0f, 0.f, 1.f, 1.f, Building[i]->Life / 500.f, 0.1f);
		}
	}
	//agumon Gauge ���� 
	for (int i = 0; i < allynum; i++) {
		if (Dizimons[i] != NULL) {
			if (Dizimons[i]->teer == 1) {
				m_renderer->DrawSolidRectGauge(Dizimons[i]->Getx(), Dizimons[i]->Gety() + 25.f, Dizimons[i]->Getz(), Dizimons[i]->Getsize(), Dizimons[i]->Getsize() / 10.f, 0.0f, 0.f, 1.f, 1.f, Dizimons[i]->Life / 100.f, 0.1f);
			}
			if (Dizimons[i]->teer == 2) {
				m_renderer->DrawSolidRectGauge(Dizimons[i]->Getx(), Dizimons[i]->Gety() + 25.f, Dizimons[i]->Getz(), Dizimons[i]->Getsize(), Dizimons[i]->Getsize() / 10.f, 0.0f, 0.f, 1.f, 1.f, Dizimons[i]->Life / 200.f, 0.1f);
			}
			if (Dizimons[i]->teer == 3) {
				m_renderer->DrawSolidRectGauge(Dizimons[i]->Getx(), Dizimons[i]->Gety() + 25.f, Dizimons[i]->Getz(), Dizimons[i]->Getsize(), Dizimons[i]->Getsize() / 10.f, 0.0f, 0.f, 1.f, 1.f, Dizimons[i]->Life / 300.f, 0.1f);
			}
		}
	}

	//eyemonster Gauge ����
	for (int i = 0; i < enermynum; i++) {
		if (Enermys[i] != NULL) {
			m_renderer->DrawSolidRectGauge(Enermys[i]->Getx(), Enermys[i]->Gety() + 25.f, Enermys[i]->Getz(), Enermys[i]->Getsize(), Enermys[i]->Getsize() / 10.f, 1.0f, 0.f, 0.f, 1.f, Enermys[i]->Life / 100.f, 0.1f);
		}

	}

	//���˺� �������� ȿ�� 
	m_renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, m_texstar, time, 0.01);

	//Text ���� 
	m_renderer->DrawTextW(-250.f, 380.f, GLUT_BITMAP_TIMES_ROMAN_24, 1.f, 1.f, 0.f, "Dohyun");

}

//�浹�׽�Ʈ �Լ� 
void ScenceMgr::CollisionTest()
{	
	//������ ������ �浹	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < enermynum; j++) {
			if (Building[i] != NULL && Enermys[j] != NULL) {
				if (CollisionCheck(Building[i], Enermys[j]) && Building[i]->team != Enermys[j]->team) {
					Building[i]->Life -= Enermys[j]->Life;
					Enermys[j]->Life = 0;
					cout << "����" << i + 1 << "�� life=" << Building[i]->Life << endl;
				}
			}

		}
	}

	//Building�� bullet�� �浹 üũ 
	for (int i = 0; i < 6; i++) {
		if (Building[i] != NULL) {
			for (int j = 0; j < bulletnum; j++) {
				if (Bullets[j] != NULL) {
					if ( CollisionCheck(Building[i],Bullets[j]) && (Building[i]->team != Bullets[j]->team)) {
						Building[i]->Life -= Bullets[j]->Life;
						Bullets[j]->Life = 0;
						cout << "����" << i+1 << "�� life=" << Building[i]->Life << endl;
					}
				}
			}
		}
	}
	
	//�Ѿ˰� ĳ������ �浹 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		//�Ʊ��� �浹
		if (Dizimons[i] != NULL) {
			for (int j = 0; j < bulletnum; j++)
			{				
				if (Bullets[j] != NULL) {
					if (CollisionCheck(Dizimons[i], Bullets[j]) && Dizimons[i]->team != Bullets[j]->team) {
						Dizimons[i]->Life -= Bullets[j]->Life;
						Bullets[j]->Life = 0;
					}
				}
			}	
		}
		//������ �浹 
		if (Enermys[i] != NULL) {
			for (int j = 0; j < bulletnum; j++)
			{
				if (Bullets[j] != NULL) {
					if (CollisionCheck(Enermys[i], Bullets[j]) && Enermys[i]->team != Bullets[j]->team) {
						Enermys[i]->Life -= Bullets[j]->Life;
						Bullets[j]->Life = 0;
					}
				}
			}
		}
	 }

	
	//character�� arrow�� �浹 
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		//�Ʊ��� �浹 
		if (Dizimons[i] != NULL) {
			for (int j = 0; j < arrownum; j++)
			{
				if (Arrows[j] != NULL) {
					if (CollisionCheck(Dizimons[i],Arrows[j]) && Dizimons[i]->team != Arrows[j]->team)
					{
						Dizimons[i]->Life -= Arrows[j]->Life;
						Arrows[j]->Life = 0;
					}
				
				}
			}
		}
		//������ �浹 
		if (Enermys[i] != NULL) {
			for (int j = 0; j < arrownum; j++)
			{
				if (Arrows[j] != NULL) {
					if (CollisionCheck(Enermys[i], Arrows[j]) && Enermys[i]->team != Arrows[j]->team)
					{
						Enermys[i]->Life -= Arrows[j]->Life;
						Arrows[j]->Life = 0;
					}

				}
			}
		}
	}
	
	//Building�� arrow�� �浹 
	for (int i = 0; i < 6; i++)
	{
		if (Building[i] != NULL) {
			for (int j = 0; j < arrownum; j++) {
				if (Arrows[j] != NULL) {
					if (CollisionCheck(Building[i], Arrows[j]) && Building[i]->team != Arrows[j]->team) {
						Building[i]->Life -= Arrows[j]->Life;
						Arrows[j]->Life = 0;
						cout << "����" << i + 1 << "�� life=" << Building[i]->Life << endl;
					}
				}
			}
		}
	}
	
}

//�浹üũ �Լ� 
bool ScenceMgr::CollisionCheck(Object *a, Object *b) {
	float left_a = a->Getx() - (a->Getsize() / 2.f);
	float right_a = a->Getx() + (a->Getsize() / 2.f);
	float top_a = a->Gety() + (a->Getsize() / 2.f);
	float bottom_a = a->Gety() - (a->Getsize() / 2.f);
	float left_b = b->Getx() - (b->Getsize() / 2.f);
	float right_b = b->Getx() + (b->Getsize() / 2.f);
	float top_b = b->Gety() + (b->Getsize() / 2.f);
	float bottom_b = b->Gety() - (b->Getsize() / 2.f);

	if (left_a > right_b) return false;
	if (right_a < left_b) return false;
	if (top_a < bottom_b) return false; 
	if (bottom_a > top_b) return false;

	return true;
}