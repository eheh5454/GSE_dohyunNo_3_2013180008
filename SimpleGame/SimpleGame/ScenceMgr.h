#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECT_COUNT 100
#define OBJECT_BUILDING 0.f, 50.f, 1.f, 1.f, 0.f, 0.f, 0.f, 500.f
#define OBJECT_CHARACTER 0.f, 10.f, 1.f, 1.f, 1.f, 1.f, 300.f, 10.f
#define OBJECT_BULLET 0.f, 2.f, 1.f, 0.f, 0.f, 0.f, 600.f, 20.f
#define OBJECT_ARROW 0.f, 2.f, 0.f, 1.f, 0.f, 0.f, 100.f, 10.f

class ScenceMgr {
private:
	Object* m_objects[MAX_OBJECT_COUNT];
	Renderer* m_renderer;
	Object* Building = new Object(0.f, 0.f, OBJECT_BUILDING);
	Object* Bullets[MAX_OBJECT_COUNT];
	int obnum;
	int bulletnum;
	float time;
public:
	ScenceMgr(int width,int height);
	~ScenceMgr();
	void Update_AllObject(float elaspedtime);
	void RenderObject();
	void CollisionTest();
	void Clickmake(int x, int y);
	void MakeBullet();
	
};