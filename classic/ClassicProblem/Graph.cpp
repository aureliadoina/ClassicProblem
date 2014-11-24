#pragma once
#include "stdafx.h"
#include "Graph.h"
#include "Line.h"

using namespace std;

Graph::Graph() {};
Graph::Graph(const vector<Point2D>& vertices, double t)
{
	numberPoints = vertices.size();
	points = vertices;
	tolerance = t;

	for (int i = 0; i < numberPoints - 1; i++)
	{
		for (int j = i + 1; j < numberPoints; j++)
		{
			if (vertices[i].distTo(vertices[j]) <= 2 * tolerance && vertices[i].distTo(vertices[j]) > 0)
			{
				addEdge(vertices[i], vertices[j]);
			}
		}
	}


}

void Graph::addEdge(const Point2D& x, const Point2D& y) {
	numberEdges++;
	Line line(x, y);
	edges.push_back(line);
}

bool Graph::IsConnected(int i, int j) 
{
	vector<Line>::iterator start = edges.begin();
	vector<Line>::iterator end = edges.end();
	if (i != j)
	{
		Line line(points[i], points[j]);
		vector<Line>::iterator p = find(start, end, line);
		if (p != end)
		{
			return true;
		}
	}
	return false;
}


