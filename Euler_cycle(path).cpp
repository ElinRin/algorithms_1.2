#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class Graph
{
private:
    vector< vector<int> > adjacency_list;
    vector<int> answer;
    bool label;
    
    
public:
    Graph(vector< vector<int> > &matrix, vector<int> &deg);
    
    void Search_Euler(int top);
    void Euler();
    void Get_answer();
    void Euler_cycle();
    
    vector<int> degree;
    
};

Graph::Graph(vector< vector<int> > &matrix, vector<int> &deg)
: adjacency_list(matrix)
, degree(deg)
, label(true)
{
}

void Graph::Search_Euler (int top)
{
    for (int i = adjacency_list[top].size() - 1; i >= 0 ; -- i)
        if (adjacency_list[top][i] >= 0)
        {
            int toptop = adjacency_list[top][i];
            adjacency_list[top][i] = -1;
            Search_Euler(toptop);
        }
    answer.push_back(top);
}

void Graph::Euler_cycle()
{
    int i, j;
    int n = adjacency_list.size();
    answer.clear();
    
    
    int top1 = -1;
    for (int vert = 0; vert < n; ++ vert)
    {
        if (degree[vert] % 2 != 0)
            label = false;
        if (degree[vert] > 0) top1 = vert;
        
    }
    //Euler_path
    /*
     int count = 0;
     int top1 = 0;
     for (int vert = 0; vert < n; ++ vert)
     if (degree[vert] % 2 != 0)
     {
     count++;
     if (count > 2)
     label = false;
     top1 = vert;
     }
     */
    
    if (top1 != -1)
        Search_Euler(top1);
    else
        label = false;
}

void Graph::Get_answer()
{
    if (label)
    {
        cout << "Yes\n";
        for (int i = answer.size() - 1; i >= 0; i--)
            cout << answer[i] + 1 << ' ';
    }
    else cout<< "No\n";
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector< vector<int> > adl(n, vector<int> (0));
    vector<int> deg(n,0);
    
    
    for (int i = 0; i < m; i++)
    {
        int top,t;
        cin >> top >> t;
        adl[top - 1].push_back(t - 1);
        deg[top -1]++;
        deg[t-1]++;
    }
    
    Graph graph(adl, deg);
    graph.Euler_cycle();
    graph.Get_answer();
    
    return 0;
}
