#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECT_COUNT 150

//z, size, r, g, b, a, speed, Life, level
#define TEAM1_CHARACTER 0.f, 30.f, 1.f, 0.f, 0.f, 1.f, 300.f, 100.f , 0.2f
#define TEAM2_CHARACTER 0.f, 30.f, 0.f, 0.f, 1.f, 1.f, 300.f, 100.f , 0.2f
#define TEAM1_BUILDING 0.f, 100.f, 1.f, 1.f, 1.f, 1.f, 0.f, 500.f, 0.1f
#define TEAM2_BUILDING 0.f, 100.f, 1.f, 1.f, 1.f, 1.f, 0.f, 500.f, 0.1f
#define TEAM1_BULLET 0.f, 4.f, 1.f, 0.f, 0.f, 1.f, 500.f, 20.f, 0.3f
#define TEAM2_BULLET 0.f, 4.f, 0.f, 0.f, 1.f, 1.f, 500.f, 20.f, 0.3f
#define TEAM1_ARROW 0.f, 4.f, 0.5f, 0.2f, 0.7f, 1.f, 100.f, 10.f, 0.3f
#define TEAM2_ARROW 0.f, 4.f, 1.f, 1.f, 0.f, 1.f, 100.f, 10.f, 0.3f

class ScenceMgr {
private:
	Object* Characters[MAX_OBJECT_COUNT];
	Renderer* m_renderer;
	Object* Building[6];
	Object* Bullets[MAX_OBJECT_COUNT];
	Object* Arrows[MAX_OBJECT_COUNT];
	GLuint m_texbuilding1;
	GLuint m_texbuilding2;
	GLuint m_texbackground;
	GLuint m_texcharacter;
	GLuint m_texparticle;

	int characternum;
	int bulletnum;
	int arrownum;
	float time;
	float bullettime;
	float arrowtime;
	float team1_charactertime;
	float team2_charactertime;
	float frame;


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