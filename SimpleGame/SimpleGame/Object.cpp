#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include "stdlib.h"

using namespace std;

Object::Object(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a) 
{
	srand(time(NULL));
	x = _x;
	y = _y;
	z = _z;
	size = _size;
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	xspeed = 0.1f * (rand() % 5 - 0.5f);
	yspeed = 0.1f * (rand() % 5 - 0.5f);
	Lifetime = 10000.0f;
	Life = 100.f;

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
void Object::Setx(float _x) {
	x = _x;
}
void Object::Sety(float _y) {
	y = _y;
}
float Object::GetLifetime() {
	return Lifetime;
}

void Object::Update() {	
	
	    this->x = x + xspeed;
		this->y = y + yspeed;

		if (x > 250)
		{
			xspeed = -xspeed;
		}
		if (x < -250)
		{
			xspeed = -xspeed;
		}
		if (y > 250)
		{
			yspeed = -yspeed;
		}
		if (y < -250)
		{
			yspeed = -yspeed;
		}
		Lifetime -= 1.f;
}

