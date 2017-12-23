#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"
#define MAX_OBJECT_COUNT 150

//z, size, r, g, b, a, speed, Life, level
#define AGUMON 0.f, 30.f, 1.f, 0.f, 0.f, 1.f, 300.f, 100.f , 0.2f
#define KOROMON 0.f, 30.f, 1.f, 0.f, 0.f, 1.f, 300.f, 100.f , 0.2f
#define EYE_MONSTER 0.f, 30.f, 0.f, 0.f, 1.f, 1.f, 300.f, 100.f , 0.2f
#define ALIEN 0.f, 60.f, 0.f, 0.f, 1.f, 1.f, 300.f, 200.f , 0.2f
#define TEAM1_BUILDING 0.f, 100.f, 1.f, 1.f, 1.f, 1.f, 0.f, 500.f, 0.1f
#define TEAM2_BUILDING 0.f, 100.f, 1.f, 1.f, 1.f, 1.f, 0.f, 500.f, 0.1f
#define TEAM1_BULLET 0.f, 4.f, 1.f, 0.f, 0.f, 1.f, 600.f, 20.f, 0.3f
#define TEAM2_BULLET 0.f, 4.f, 0.f, 0.f, 1.f, 1.f, 600.f, 20.f, 0.3f
#define TEAM1_ARROW 0.f, 10.f, 0.5f, 0.2f, 0.7f, 1.f, 100.f, 20.f, 0.3f
#define TEAM2_ARROW 0.f, 10.f, 1.f, 1.f, 1.f, 1.f, 100.f, 20.f, 0.3f

class ScenceMgr {
private:
	Object* Dizimons[MAX_OBJECT_COUNT];
	Object* Enermys[MAX_OBJECT_COUNT];
	Renderer* m_renderer;
	Object* Building[6];
	Object* Bullets[MAX_OBJECT_COUNT];
	Object* Arrows[MAX_OBJECT_COUNT];
	GLuint m_texbuilding1;
	GLuint m_texbuilding2;
	GLuint m_texbackground;
	GLuint m_texeyemonster;
	GLuint m_texparticle;
	GLuint m_texstar;
	GLuint m_texagumon;
	GLuint m_texgreymon;
	GLuint m_texmetalgreymon;
	GLuint m_texevolution;
	GLuint m_texkoromon;
	GLuint m_texkoromon_arrow;
	GLuint m_texalien;
	Sound* m_sound = new Sound();

	int soundBG;
	int allynum;
	int enermynum;
	int bulletnum;
	int arrownum;
	float time;
	float bullettime;
	float arrowtime;
	float eyemonster_time;
	float agumon_time;
	float character_frame;
	float koromon_time;
	float alien_time;

public:
	ScenceMgr(int width,int height);
	~ScenceMgr();
	void Update_AllObject(float elaspedtime);
	void RenderObject();
	void CollisionTest();
	void Clickmake(int x, int y);
	void MakeBullet(float elaspedtime);
	void MakeArrow(float elaspedtime);
	void MakeCharacter(float elaspedtime);
	bool CollisionCheck(Object *a, Object *b);
	
};