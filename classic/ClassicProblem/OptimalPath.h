#pragma once
#include "Point2D.h"
#include "Graph.h"
#include "Line.h"
#include "LinearRegression.h"

class OptimalPath
{
public:
	Graph graph;
	vector<LinearRegression> regressionLines;
	vector<Line> pathEdges;

	OptimalPath(const Graph& g, int startPoint, double acceptedError);


private:

	int startPointIndex;
	double acceptedError;
	int n;
	vector<Point2D> points;

	void CalculatePath();
	void CalculatePath(int v, double tolerance, vector<bool>& visited, vector<bool>& resolved, int lastVisited);

	int GetNumberOfVisitedAndNotResolvedNodes(const vector<bool>& visited, const vector<bool>& resolved) const;
	vector<int> GetUnresolvedPointsIndexes(const vector<bool>& visited, const vector<bool>& resolved, int currentPointIndex = -1) const;
	LinearRegression GetLinearRegressionWithUnresolvedPoints(const vector<bool>& visited, const vector<bool>& resolved) const;
	bool IsRegressionLineAdded(const vector<bool>& visited, const vector<bool>& resolved) const;

	void UpdateRegressionLines(LinearRegression& linearRegression, vector<bool>& visited, vector<bool>& resolved);
	void ResolvePreviousRegressionLine(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex);
	void ResolvePreviousEdge(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex);
	void AddEdge(vector<bool>& visited, vector<bool>& resolved);
	bool IsEdgeAdded(const vector<bool>& visited, const vector<bool>& resolved) const;
	bool IsLineAcceptable(LinearRegression linearRegression, const vector<bool>& visited, const vector<bool>& resolved) const;
	bool IsLastEdgeAcceptable(const vector<bool>& visited, const vector<bool>& resolved) const;

	int OptimalPath::MoveTwoStepsBack(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex);
};