#include "Day12.h"

#define INPUT "Day12/1.IN"
#define INF std::numeric_limits<int>::max()

typedef pair<int, int> iPair;

class Graph 
{
	int V;
	list<pair<int, int>>* adj;
public:
	Graph(int V); 
	void addEdge(int u, int v, int w);
	int shortestPath(int s, int g);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].emplace_back(make_pair(v, w));
	//adj[v].emplace_back(make_pair(u, w));
}

int Graph::shortestPath(int src, int dest)
{
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
	vector<int> dist(V, INF);
	pq.push(make_pair(0, src));
	dist[src] = 0;
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		list<pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			int v = (*i).first;
			int weight = (*i).second;
			if (dist[v] > dist[u] + weight) 
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	//printf("From %d to %d took %d\n", src, dest, dist[dest]);
	return dist[dest];
}

void swap_char(std::string& str, char c1, char c2) 
{
	for (std::size_t i = 0; i < str.length(); i++) 
	{
		if (str[i] == c1)
			str[i] = c2;
	}
}

void Day12::Part1()
{
    ScopedTimer timer;

	auto input = Utils::ReadInput(INPUT);
	for (size_t i = 0; i < input.size(); i++)
		swap_char(input[i], 'E', 'z' + 1);

	Graph g(input.size() * input[0].size());
	int startIndex = -1;
	int goalIndex = -1;
	for (size_t x = 0; x < input.size(); x++)
	{
		for (size_t y = 0; y < input[x].size(); y++)
		{
			int vertexIndex = x * input[x].size() + y;
			char heightChar = input[x][y];

			if (heightChar == 'S')
			{
				startIndex = vertexIndex;
				heightChar = 'a' - 1;
			}
			else if (heightChar == 'z' + 1)
			{
				goalIndex = vertexIndex;
			}

			if (x > 0 &&						input[x - 1][y] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex - input[x].size(), 1);

			if (x < (input.size() - 1) &&		input[x + 1][y] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex + input[x].size(), 1);

			if (y > 0 &&						input[x][y - 1] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex - 1, 1);

			if (y < (input[x].size() - 1) &&	input[x][y + 1] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex + 1, 1);
		}
	}
	g.shortestPath(startIndex, goalIndex);
}

void Day12::Part2()
{
	ScopedTimer timer;

	auto input = Utils::ReadInput(INPUT);
	vector<int> startingPositions;
	for (size_t i = 0; i < input.size(); i++)
	{
		swap_char(input[i], 'E', 'z' + 1);
		swap_char(input[i], 'S', 'a' - 1);
		for (size_t j = 0; j < input[i].size(); j++)
		{
			int vertexIndex = i * input[i].size() + j;
			if (input[i][j] == 'a')
				startingPositions.push_back(vertexIndex);
		}
	}
	Graph g(input.size() * input[0].size());
	int goalIndex = -1;
	for (size_t x = 0; x < input.size(); x++)
	{
		for (size_t y = 0; y < input[x].size(); y++)
		{
			int vertexIndex = x * input[x].size() + y;
			char heightChar = input[x][y];

			if (heightChar == 'z' + 1)
				goalIndex = vertexIndex;

			if (x > 0 && input[x - 1][y] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex - input[x].size(), 1);

			if (x < (input.size() - 1) && input[x + 1][y] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex + input[x].size(), 1);

			if (y > 0 && input[x][y - 1] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex - 1, 1);

			if (y < (input[x].size() - 1) && input[x][y + 1] <= heightChar + 1)
				g.addEdge(vertexIndex, vertexIndex + 1, 1);
		}
	}

	std::map<int, int> distMap;
	for (int startIndex : startingPositions)
		distMap[g.shortestPath(startIndex, goalIndex)] = startIndex;

	printf("Shortest is from %d and is %d.", distMap.begin()->second, distMap.begin()->first);
}
