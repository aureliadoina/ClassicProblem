#include "stdafx.h"
#include "OptimalPath.h"

OptimalPath::OptimalPath(const Graph& g,int start, double error)
{
	graph = g;
	startPointIndex = start;
	acceptedError = error;
	n = graph.GetNumberPoints();
	points = graph.points;
	CalculatePath();
}

void OptimalPath::CalculatePath()
{
	vector<bool> visited(n);
	vector<bool> resolved(n);
	int lastVisited = startPointIndex;

	CalculatePath(startPointIndex, acceptedError, visited, resolved, lastVisited);

}

void OptimalPath::CalculatePath(int currentPointIndex, double acceptedError, vector<bool>& visited, vector<bool>& resolved, int lastVisitedPointIndex)
{
	visited[currentPointIndex] = true;
	int numberSelectedNodes = GetNumberOfVisitedAndNotResolvedNodes(visited, resolved);
	if (numberSelectedNodes > 2) {
				
		LinearRegression linearRegression = GetLinearRegressionWithUnresolvedPoints(visited, resolved);
		
		if (IsLineAcceptable(linearRegression,visited, resolved))
		{
			UpdateRegressionLines(linearRegression,visited, resolved);
		}
		else
		{
			if (numberSelectedNodes > 3)
			{
				ResolvePreviousRegressionLine(visited,resolved,currentPointIndex,lastVisitedPointIndex);
			}
			if (numberSelectedNodes == 3)
			{
				if (IsLastEdgeAcceptable(visited,resolved))
				{
					ResolvePreviousEdge(visited, resolved, currentPointIndex, lastVisitedPointIndex);
				}
				else
				{
					int lastResolvedIndex = MoveTwoStepsBack(visited,resolved,currentPointIndex,lastVisitedPointIndex); 
					
					AddEdge(visited, resolved);
					CalculatePath(lastResolvedIndex, acceptedError, visited, resolved, currentPointIndex);

					return;
				}
			}
			AddEdge(visited, resolved);
		}
	}
	else
	{
		if (numberSelectedNodes == 2)
		{
			AddEdge(visited, resolved);
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (graph.IsConnected(currentPointIndex, i))
		{
			CalculatePath(i, acceptedError, visited, resolved, currentPointIndex);
		}
	}
}

int OptimalPath::GetNumberOfVisitedAndNotResolvedNodes(const vector<bool>& visited, const vector<bool>& resolved) const
{
	int numberOfVisitedNodes = 0;
	for (int i = 0; i < n; i++)
	{
		if (visited[i] && !resolved[i])
		{
			numberOfVisitedNodes++;
		}
	}
	return numberOfVisitedNodes;
}

vector<int> OptimalPath::GetUnresolvedPointsIndexes(const vector<bool>& visited,const vector<bool>& resolved,int currentPointIndex) const
{
	vector<int> unresolved;
	for (int j = 0; j < n; j++)
	{
		if (visited[j] && !resolved[j] && currentPointIndex != j)
		{
			unresolved.push_back(j);

		}
	}
	return unresolved;
}

LinearRegression OptimalPath::GetLinearRegressionWithUnresolvedPoints(const vector<bool>& visited,const vector<bool>& resolved) const
{
	vector<Point2D> regressionPoints;
	vector<int> unresolvedPointsIndexes = GetUnresolvedPointsIndexes(visited, resolved);
	for each (int index in  unresolvedPointsIndexes)
	{
		regressionPoints.push_back(graph.points[index]);
	}
	LinearRegression linearRegression(regressionPoints);
	return linearRegression;
}

void OptimalPath::UpdateRegressionLines(LinearRegression& linearRegression,vector<bool>& visited, vector<bool>& resolved)
{
	if (IsRegressionLineAdded(visited, resolved))
	{
		regressionLines.pop_back();
	}
	regressionLines.push_back(linearRegression);
	if (IsEdgeAdded(visited,resolved))
	{
		pathEdges.pop_back();
	}
	pathEdges.push_back(linearRegression.GetLine());
}

bool OptimalPath::IsRegressionLineAdded(const vector<bool>& visited, const vector<bool>& resolved) const
{
	return regressionLines.size() > 0 && GetNumberOfVisitedAndNotResolvedNodes(visited, resolved) > 3;
}

bool OptimalPath::IsEdgeAdded(const vector<bool>& visited, const vector<bool>& resolved) const
{
	return pathEdges.size() > 0 && GetNumberOfVisitedAndNotResolvedNodes(visited, resolved) > 2;
}


void OptimalPath::ResolvePreviousRegressionLine(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex)
{
	for (int j = 0; j < n; j++)
	{
		if (visited[j] && !resolved[j] && currentPointIndex != j)
		{
			resolved[j] = true;

		}
	}
	resolved[lastVisitedPointIndex] = false;

}

void OptimalPath::ResolvePreviousEdge(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex)
{
	vector<int> unresolved = GetUnresolvedPointsIndexes(visited, resolved, currentPointIndex);
	for each (int index in unresolved)
	{
		resolved[index] = true;
	}
	resolved[lastVisitedPointIndex] = false;


}

void OptimalPath::AddEdge(vector<bool>& visited, vector<bool>& resolved)
{
	vector<int> unresolved = GetUnresolvedPointsIndexes(visited, resolved);
	Line l(graph.points[unresolved[0]], graph.points[unresolved[1]]);
	pathEdges.push_back(l);
}

bool OptimalPath::IsLineAcceptable(LinearRegression linearRegression,const vector<bool>& visited,const vector<bool>& resolved) const
{
	bool isLineNotTooFar = linearRegression.GetMaxError() < acceptedError;
	bool isIntersectionPointInCircle = false;
		
	if (pathEdges.size() >= 2)
	{
		Line line = linearRegression.GetLine();
		int numberUnresolvedPoints = GetNumberOfVisitedAndNotResolvedNodes(visited, resolved);
		Line previousLine = pathEdges[pathEdges.size() - 1];
		if (numberUnresolvedPoints > 2)
		{
			previousLine = pathEdges[pathEdges.size() - 2];
		}
		Point2D intersectionPoint = line.IntersectWith(previousLine);
		if (intersectionPoint.distTo(line.A) < graph.GetTolerance())
		{
			isIntersectionPointInCircle = true;
		}
	}
	else
	{
		return isLineNotTooFar;
	}
	return isLineNotTooFar && isIntersectionPointInCircle;
}


bool OptimalPath::IsLastEdgeAcceptable(const vector<bool>& visited, const vector<bool>& resolved) const
{
	bool isIntersectionPointInCircle = false;

	if (pathEdges.size() >= 2)
	{
		Line previousLine = pathEdges[pathEdges.size() - 2];
		Line line = pathEdges[pathEdges.size() - 1];
		Point2D intersectionPoint = line.IntersectWith(previousLine);
		if (intersectionPoint.distTo(line.A) < graph.GetTolerance())
		{
			isIntersectionPointInCircle = true;
		}
	}
	else
	{
		return true;
	}
	return isIntersectionPointInCircle;

}

int OptimalPath::MoveTwoStepsBack(vector<bool>& visited, vector<bool>& resolved, int currentPointIndex, int lastVisitedPointIndex)
{
	LinearRegression regressionLine = regressionLines[regressionLines.size() - 1];
	Point2D lastPoint = regressionLine.points[regressionLine.points.size() - 1];

	//unresolved the second last point from the regression
	Point2D lastSecondPoint = regressionLine.points[regressionLine.points.size() - 2];
	int lastResolvedIndex;
	for (int i = 0; i < n; i++)
	{
		if (points[i] == lastSecondPoint)
		{
			resolved[i] = false;
			lastResolvedIndex = i;
		}
	}
	resolved[currentPointIndex] = false;
	resolved[lastVisitedPointIndex] = false;

	//remove the last point from it;
	regressionLine.removePoint();
	//remove old regression line
	regressionLines.pop_back();

	//remove last unsolved edge;
	pathEdges.pop_back();

	//remove edges for the regression line and add the new edge for regression line
	pathEdges.pop_back();

	pathEdges.push_back(regressionLine.GetLine());
	
	
	return lastResolvedIndex;
}