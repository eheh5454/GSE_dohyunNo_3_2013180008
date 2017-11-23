#pragma once
#include <iostream>

class Object {
private:
	float x;
	float y;
	float z;
	float size;
	float xspeed;
	float yspeed;
public:
	float r;
	float g;
	float b;
	float a;
	float Life;
	float Lifetime;
	int arrow_id;
	float arrow_time;
	int team;
	float level;

public:
	Object(float _x,float _y, float _z, float _size,float _r, float _g,float _b,float _a,float speed,float _Life, float _level);
	~Object();
	float Getx();
	float Gety();
	float Getz();
	float Getsize();
	float Getr();
	float Getg();
	float Getb();
	float Geta();
	void Update(float elaspedtime);
	void bullet_arrow_Update(float elaspedtime);


};