#pragma once
#include "stdafx.h"
using namespace std;

class Point2D
{
public:
	Point2D(double X = 0.0, double Y = 0.0) : x(X), y(Y) { }

	void setPoint(double X, double Y) { x = X; y = Y; }
	void setX(double X) { x = X; }
	void setY(double Y) { y = Y; }

	double getX() const { return x; }
	double getY() const { return y; }
	bool operator==(const Point2D& r) const
	{
		return x == r.x && y == r.y;
	}
	double distTo(const Point2D& point) const{
		double dx = (getX() - point.getX())*(getX() - point.getX());
		double dy = (getY() - point.getY())*(getY() - point.getY());
		return sqrt(dx + dy);
	}
private:
	double x, y;
};
