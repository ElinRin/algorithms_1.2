#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using std::cin;
using std::cout;
using std::vector;
using std::min;
using std::pair;
using std::make_pair;

class Graph
{
private:
    vector < bool > label;
    vector < int > label_color;
    vector < int > order_graph;
    vector< vector<int> > adjacency_list;
    int timer;
	vector < int > time_in;
	vector < int > time_f;
	vector < int > child;
	vector<bool> answer;
	int count;
	int color;
    
    
    void DFS_oreintation(int &v);
    void DFS_color(int &v, int &color);
    void DFS_time(int &v);
    
    
public:
    Graph(int number_vertices, const vector< vector<int> > & matrix);
    
    void Search_bridges();
    void Search_points();
    
    void Get_bridges(const vector< pair<int,int> > &edges);
    void Get_points();
    
};

Graph::Graph(int number_vertices, const vector< vector<int> > & matrix):
label_color(number_vertices, 0),
adjacency_list(matrix),
time_in(number_vertices, 0),
time_f(number_vertices, 0),
label(number_vertices, true),
child(number_vertices, 0),
answer(number_vertices,false),
count(0),
timer(0),
color(0)
{}

void Graph::DFS_oreintation (int &v)
{
    label[v] = false;
    order_graph.push_back(v);
    
    for (int i = 0; i < adjacency_list[v].size( ); ++ i)
        if (label[adjacency_list[v][i]] && adjacency_list[v][i] >= 0)
        {
            int toptop = adjacency_list[v][i];
            adjacency_list[v][i] = -1;
            DFS_oreintation (toptop);
        }
}

void Graph::DFS_color (int &v, int &color)
{
    label_color[v] = color;
    
    for (int i = 0; i < adjacency_list[v].size (); ++ i)
        if (label_color[adjacency_list[v][i]] == 0 && adjacency_list[v][i] >= 0)
            DFS_color (adjacency_list[v][i], color);
}

void Graph::Search_bridges()
{
    for (int i = 0; i < adjacency_list.size (); ++ i)
        if (label[i])
            DFS_oreintation (i);
    
    label_color.assign (adjacency_list.size (), 0);
    
    for (int i = 0; i < order_graph.size (); ++ i)
        if (label_color[order_graph[i]] == 0)
        {
            ++ color;
            DFS_color (order_graph[i], color);
        }
}

void Graph::DFS_time(int &v)
{
    label[v] = false;
    ++ timer;
    time_in[v] = timer;
    time_f[v] = timer;
    
    for (int i = 0; i < adjacency_list[v].size (); ++ i)
    {
        int next_top = adjacency_list[v][i];
        
        if (label[next_top])
        {
            ++ child[v];
            DFS_time (next_top);
            
            time_f[v] = min (time_f[v], time_f[next_top]);
            if (time_f[next_top] >= time_in[v]) answer[v] = true;
        }
        else
            time_f[v] = min (time_f[v], time_in[next_top]);
    }
}
void Graph::Search_points()
{
    
    for (int i = 0; i < adjacency_list.size (); i++)
    {
        if (label[i])
        {
            DFS_time (i);
            answer[i] = (child[i] > 1);
        }
        if (answer[i]) count++;
    }
    
}
void Graph::Get_bridges(const vector< pair<int,int> > &edges)
{
    vector<int> answer;
    
	//cout << '\n' << 'массив цветов вершин, вершины одного цвета это компонента вершинной и реберной двусвязности' << '\n';
    for (int i = 0; i < label_color.size(); i++)
    {
        //cout << i+1 << '-' << label_color[i] << '\n';
        if (label_color[edges[i].first] != label_color[edges[i].second]) answer.push_back(i+1);
        
    }
	//cout <<'\n' << 'Количество мостов и их номера' << '\n';
	cout << answer.size() << '\n';
	for (int i = 0; i < answer.size(); i++)
        cout << answer[i]  << ' ';
    
    
    
    
}

void Graph::Get_points()
{
	//cout << '\n' << 'Количество точек и их номера' << '\n';
	cout << count << '\n';
	for (int i = 0; i < answer.size(); i++)
    {
		if (answer[i]) cout << i+1 << ' ';
	}
	
}



int main()
{
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    vector< vector<int> > adl(n, vector<int>(0));
    vector< pair<int,int> > edges;
    
    
    for (int i = 0; i < m; i++)
    {
        int top,t;
        cin >> top >> t;
        adl[top-1].push_back(t-1);
        adl[t-1].push_back(top-1);
        edges.push_back(make_pair(top-1,t-1));
    }
    
    
	Graph graph(n,adl);
    
	graph.Search_bridges();
	//graph.Search_points();
	graph.Get_bridges(edges);
	//graph.Get_points();
    
    
    return 0;
}
