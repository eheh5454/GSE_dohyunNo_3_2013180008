#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECT_COUNT 50

class ScenceMgr {
private:
	Object* m_objects[MAX_OBJECT_COUNT];
	Renderer* m_renderer;
	int obnum;
public:
	ScenceMgr(int width,int height);
	~ScenceMgr();
	void Update_AllObject(void);
	void RenderObject();
	void CollisionTest();
	void Clickmake(int x, int y);
};