#pragma once
#include "Point2D.h"
#include "Line.h"

using namespace std;

class Graph {
private:
	int numberPoints;
	int numberEdges;
	double tolerance;
		
public:
	vector<Line> edges;
	vector<Point2D> points;

	Graph();
	Graph(const vector<Point2D>& vertices,double tolerance);
			
	void addEdge(const Point2D& x,const Point2D& y);
	
	int GetNumberEdges() const{ return numberEdges; }
	int GetNumberPoints() const{ return numberPoints; }
	double GetTolerance() const{ return tolerance; }
	bool Graph::IsConnected(int i, int j);
};

