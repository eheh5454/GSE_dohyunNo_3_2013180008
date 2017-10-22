#pragma once
#include <iostream>
#include "Object.h"
#include "Renderer.h"
#define MAX_OBJECT_COUNT 100

class ScenceMgr {
private:
public:
	Object* m_objects[MAX_OBJECT_COUNT];
	int obnum;
public:
	ScenceMgr();
	~ScenceMgr();
	void Update_AllObject(void);
	void RenderObject(Renderer *Renderer);
	
};