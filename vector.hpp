#ifndef VEC
#define VEC 
#include<iostream>
#include<cmath>
using namespace std;
class Vector
{
	public:
		float x;
		float y;
		float unit_x;
		float unit_y;
	
	Vector(){
	}
	Vector(float a,float b)
	{
		x=a;
		y=b;
		unit_x=x/sqrt(x*x+y*y);
		unit_y=y/sqrt(x*x+y*y);
	}	
	float length()
	{
		return sqrt(x*x+y*y);
	}
};
#endif
