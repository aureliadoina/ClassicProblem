#pragma once
#include "stdafx.h"
#include <utility>
#include "Point2D.h"

class Line{

public:
	Point2D A;
	Point2D B;

	Line(const Point2D& p1,const Point2D& p2);

	bool operator==(const Line& line);
	Point2D IntersectWith(const Line& line);
};
