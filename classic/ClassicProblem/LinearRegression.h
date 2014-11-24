#pragma once
#include "stdafx.h"
#include "Point2D.h"
#include "Line.h"


class LinearRegression
{
	
private:
	double sumX, sumY;  // sums of x and y
	double sumXsquared, // sum of x squares
		sumYsquared; // sum y squares
	double sumXY;       // sum of x*y

	double a, b;        // coefficients of f(x) = ax +b
	void Calculate();   // calculate coefficients
	

	void addXY(const double& x, const double& y);
	void removeXY(const double& x, const double& y);
	void addPoints(const vector<Point2D>& points);
	
public:
	vector<Point2D> points;
	LinearRegression();
	LinearRegression(const vector<Point2D>& points);
	void addPoint(const Point2D& p);
	void removePoint();
	
	bool haveData() const { return points.size() > 2; }
	long numberPoints() const { return points.size(); }

	double getA() const { return a; }
	double getB() const { return b; }
	Line GetLine();

	double estimateY(double x) const { return (a *x+ b ); }
	double GetError(Point2D p) const; 
	double GetMaxError() const;
};

