#pragma once
#include "stdafx.h"
#include "Point2D.h"
#include "Line.h"

Line::Line(const Point2D& p1,const Point2D& p2)
{
	A = p1;
	B = p2;
}

bool Line::operator==(const Line& line)
{
	return (A.getX() == line.A.getX() && A.getY() == line.A.getY() && B.getX() == line.B.getX() && B.getY() == line.B.getY());
}

Point2D Line::IntersectWith(const Line& line)
{
	double denominator = (A.getX() - B.getX())*(line.A.getY() - line.B.getY()) - (A.getY() - B.getY())*(line.A.getX() - line.B.getX());

	if (denominator == 0) return NULL;

	double x_intersection = ((line.A.getX() - line.B.getX())*(A.getX()* B.getY() - A.getY()*B.getX()) - (A.getX() - B.getX())*(line.A.getX()*line.B.getY() - line.A.getY()*line.B.getX())) / denominator;

	double y_intersection = ((line.A.getY() - line.B.getY())*(A.getX()*B.getY() - A.getY()*B.getX()) - (A.getY() - B.getY())*(line.A.getX()*line.B.getY() - line.A.getY()*line.B.getX())) / denominator;
		
	Point2D p(x_intersection, y_intersection);
	return p;
}