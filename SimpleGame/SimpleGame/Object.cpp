
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
using namespace std;

Object::Object(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a,float _speed) {
	x = _x;
	y = _y;
	z = _z;
	size = _size;
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	speed = _speed;
	
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
void Object::Update() {	
		x += speed;
		y += speed;
		cout << "update"<< x << " " << y  << endl;
}

