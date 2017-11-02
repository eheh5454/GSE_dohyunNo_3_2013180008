#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECT_COUNT 30

class ScenceMgr {
private:
	Object* m_objects[MAX_OBJECT_COUNT];
	int obnum;
public:
	Renderer* m_renderer;
	ScenceMgr(int width,int height);
	~ScenceMgr();
	void Update_AllObject(void);
	void RenderObject();
	void CollisionTest();
	void Clickmake(int x, int y);
};