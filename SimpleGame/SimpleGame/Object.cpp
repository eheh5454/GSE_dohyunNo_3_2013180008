#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include "stdlib.h"
#include "ScenceMgr.h"
using namespace std;

Object::Object(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a,float speed, float _Life): arrow_id(0), arrow_time(0.f), team(0)
{
	
	x = _x;
	y = _y;
	z = _z;
	size = _size;
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	//0~1까지의 실수난수를 생성해서 0.5를 빼서 랜덤방향을 생성하고, 방향을 speed에 곱해준다.
	xspeed = speed * (float)((rand() % 1000 + 1) * 0.001 - 0.5f);
	yspeed = speed * (float)((rand() % 1000 + 1) * 0.001 - 0.5f);
	Lifetime = 10000.0f;
	Life = _Life;

}

Object::~Object() {}


float Object::Getx() {
	return x;
}
float Object::Gety() {
	return y;
}
float Object::Getz() {
	return z;
}
float Object::Getsize() {
	return size;
}
float Object::Getr() {
	return r;
}
float Object::Getg() {
	return g;
}
float Object::Getb() {
	return b;
}
float Object::Geta() {
	return a;
}


void Object::Update(float elaspedtime) {
	//elaspedtime을 second로 변환 
	float second = elaspedtime * 0.001f;
	this->x = x + xspeed * second;
    this->y = y + yspeed * second;

	if (x > 250)
	{
		xspeed = -xspeed;
	}
	if (x < -250)
	{
		xspeed = -xspeed;
	}
	if (y > 400)
	{
		yspeed = -yspeed;
	}
	if (y < -400)
	{
		yspeed = -yspeed;
	}
	Lifetime -= 0.5f;
}

