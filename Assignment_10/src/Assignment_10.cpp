#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Point
{
private:
   float x;
   float y;
   static float MIN_VAL = -10.0;
   static float MAX_VAL = +10.0;
public:
   Point();
   Point(x,y);
   bool set(float x, float y);
   float getX();
   float getY();
   void displayPoint();
   bool setRange(float newMinVal, float newMaxVal);
};

class Polygon
{
public:
   Polygon();
   Polygon(int numPoints,float xArray[],float yArray[])
};
