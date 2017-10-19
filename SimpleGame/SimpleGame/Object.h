#pragma once
#include <iostream>

class Object {
private:
	float x;
	float y;
	float z;
	float size;
	float r;
	float g;
	float b;
	float a;
	float speed;
	
public:
	Object(float _x,float _y, float _z, float _size,float _r, float _g,float _b,float _a,float _speed);
	~Object();
	float Getx();
	float Gety();
	float Getz();
	float Getsize();
	float Getr();
	float Getg();
	float Getb();
	float Geta();
	void Setx(float x);
	void Sety(float y);

	void Update();


};