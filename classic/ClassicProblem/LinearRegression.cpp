#pragma once
#include "stdafx.h"
#include "LinearRegression.h"


LinearRegression::LinearRegression()
{
	a = b = sumX = sumY = sumXsquared = sumYsquared = sumXY = 0.0;
}

LinearRegression::LinearRegression(const vector<Point2D>& points) :LinearRegression()
{
	addPoints(points);
}

void LinearRegression::addXY(const double& x, const double& y)
{
	sumX += x;
	sumY += y;
	sumXsquared += x * x;
	sumYsquared += y * y;
	sumXY += x * y;
	
}
void LinearRegression::removeXY(const double& x, const double& y)
{
	sumX -= x;
	sumY -= y;
	sumXsquared -= x * x;
	sumYsquared -= y * y;
	sumXY -= x * y;

}
void LinearRegression::Calculate()
{
	int n = points.size();
	if (haveData())
	{
		double meanX = sumX / n;
		double meanY = sumY / n;
		double sumXmeanX = 0; // sum after (x - mean(x))*(x - mean(x))
		double sumYmeanY = 0; //sum after (y - mean(y))*(y - mean(y))
		double sumXmeanXYmeanY = 0; //sum after (x-mean(x))(y-mean(y))
		for each(Point2D point in points)
		{
			sumXmeanX += (point.getX() - meanX)*(point.getX() - meanX);
			sumYmeanY += (point.getY() - meanY)*(point.getY() - meanY);
			sumXmeanXYmeanY += (point.getX() - meanX)*(point.getY() - meanY);
		}
		a = sumXmeanXYmeanY / sumXmeanX;
		b = meanY - a*meanX;
		
	}
}

void LinearRegression::addPoint(const Point2D& p) { 
	points.push_back(p);
	addXY(p.getX(), p.getY());
	Calculate();
	
}

void LinearRegression::removePoint() {
	Point2D p=points[points.size()-1];
	removeXY(p.getX(), p.getY());
	points.pop_back();
	Calculate();

}

void LinearRegression::addPoints(const vector<Point2D>& points) {
	for each (Point2D point in points)
	{
		addPoint(point);
	}
	
}

double LinearRegression::GetError(Point2D p) const
{ 
	return sqrt((b + a * p.getX() - p.getY())*(b + a * p.getX() - p.getY())); 
}

double LinearRegression::GetMaxError() const
{
	double maxError = 0;
	for each (Point2D point in points)
	{
		double err = GetError(point);
		if (maxError < err){
			maxError =err;
		}
	}
	return maxError;
}

Line LinearRegression::GetLine()
{
	Point2D point1 = points[0];
	Point2D point2 = points[points.size() - 1];

	Point2D estimatedPoint1(point1.getX(), estimateY(point1.getX()));
	Point2D estimatedPoint2(point2.getX(), estimateY(point2.getX()));
	Line line(estimatedPoint1, estimatedPoint2);
	return line;
}


