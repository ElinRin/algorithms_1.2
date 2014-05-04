#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <stack>

using std::vector;
using std::cin;
using std::cout;
using std::set;
using std::pair;
using std::make_pair;
using std::stack;
using std::min;

class Graph
{
private:
    vector < vector<int> > adjacency_list_1, adjacency_list_2;
    vector<bool> used;
    vector<int> component;
    vector<int> time_out, time_in, time_f;
    set< pair<int,int> > answer;
    stack<int> used_verteces;
    unsigned int current_time;
    unsigned int current_color;

public:

    Graph();
    Graph(int number_verteces, const vector< vector<int> > & matrix_1, const vector< vector<int> > & matrix_2);

    bool Is_visit(int top);
    void DFS_1(int top);
    void DFS_2(int top, int color);
    void Tarjan(int top);
    void Used_False(int number_verteces);
    int Get_time_out(int top);
    int Get_answer();

};

    Graph::Graph(int number_verteces, const vector< vector<int> > & matrix_1, const vector< vector<int> > & matrix_2):
    used(number_verteces, false), 
    adjacency_list_1(matrix_1),
    adjacency_list_2(matrix_2),
    component(number_verteces,0),
    time_in(number_verteces,0),
    time_f(number_verteces),
    current_time(0),
    current_color(1)
    {}

int Graph::Get_answer()
{
    for(int top = 1; top < adjacency_list_1.size(); top++)
    {
        for (int i = 0; i < adjacency_list_1[top].size(); ++i)
            if (component[top] != component[adjacency_list_1[top][i]])
                answer.insert(make_pair(component[top],component[adjacency_list_1[top][i]]));

    }
   // for (set<pair<int,int> >::iterator it = answer.begin(); it!= answer.end(); it++)
   //    cout << it->first << " " << it->second << std::endl;
    cout << answer.size() << '\n';
}

void Graph::Used_False(int number_verteces)
{
    used.assign(number_verteces, false);
}

bool Graph::Is_visit(int top)
{
    return used[top];
}

//Kosaraju 

int Graph::Get_time_out(int top)
{
    return time_out[top];
}

void Graph::DFS_1 (int top) 
{
    used[top] = true;
    for (int i = 0; i < adjacency_list_1[top].size(); ++i)
        if (!used[ adjacency_list_1[top][i] ])
            DFS_1 (adjacency_list_1[top][i]);
    time_out.push_back (top);
}

void Graph::DFS_2 (int top,int color)
{
    used[top] = true;
    component[top] = color;
    for (int i = 0; i < adjacency_list_2[top].size(); ++i)
        if (!used[ adjacency_list_2[top][i] ])
            DFS_2 (adjacency_list_2[top][i], color);
}

//Tarjan

void Graph::Tarjan(int top)
{
    used[top] = true;
    used_verteces.push(top);
    time_f[top] = time_in[top] = ++current_time;
    for (int i = 0; i < adjacency_list_1[top].size(); i++)
    {
            unsigned int incedent_top = adjacency_list_1[top][i];
            if (component[incedent_top] == 0)
            {
                    if (time_in[incedent_top] == 0)
                            Tarjan(incedent_top);
                    time_f[top] = min(time_f[top], time_f[incedent_top]);
            }
    }
    if (time_f[top] == time_in[top])
    {
            int new_top;
            do 
            {
                new_top = used_verteces.top();
                component[new_top] = current_color;
                used_verteces.pop();
            } 
            while (new_top != top);
            current_color++;
    }


}

int main()
{
    //freopen("condense2.in", "r", stdin);
    //freopen("condense2.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    vector< vector<int> > adl1(n + 1, vector<int>(0));
    vector< vector<int> > adl2(n + 1, vector<int>(0));

     for (int i = 0; i < m; i++)
    {
        int top,t;
        cin >> top >> t;
        adl1[top].push_back(t);
        adl2[t].push_back (top);
    }
 
    Graph graph(n + 1, adl1, adl2);

//Kosaraju
 /*   for (int i = 1; i <= n; ++i)
        if (!graph.Is_visit(i)) 
            graph.DFS_1(i);

    graph.Used_False(n + 1);

    int c = 0;
    for (int i = 1; i <= n; ++i) 
    {
        int v = graph.Get_time_out(n-i);
        if (!graph.Is_visit(v))
        {
            c++;
            graph.DFS_2 (v,c);
        }
    }

    graph.Get_answer();*/

//Tarjan
    graph.Used_False(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        if(!graph.Is_visit(i))
            graph.Tarjan(i);
    }

    graph.Get_answer();

    return 0;
}
