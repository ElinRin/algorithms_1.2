#include <iostream>
#include <vector>
#include <stack>


using std::vector;
using std::cin;
using std::cout;
using std::stack;

 
    class Graph
    {

    private:
        bool label;
        vector<int> color;
        vector<int> counters;
        vector< vector<int> > adjacency_list;
        vector<int> answer;
        int Get_top(const stack<int> & work_top);


    public:

        Graph();
        Graph(int number_vertices, const vector< vector<int> > & matrix);
       
        bool Is_visit(int top);
        void DFS(int top);
        void Get_answer();
    };

    Graph::Graph(int number_vertices, const vector< vector<int> > & matrix):
    color(number_vertices, 0), 
    counters(number_vertices, 0),
    adjacency_list(matrix),
    label(true)
    {}

    int Graph::Get_top(const stack<int> & work_top)
    {
        return adjacency_list[work_top.top()][counters[work_top.top()]];
    }

    bool Graph::Is_visit(int top)
    {
        return color[top];
    }

    void Graph::DFS(int top)
    {
        stack<int> work_top;
        work_top.push(top);
        while (work_top.size() > 0 && label)
        {
            if (!color[work_top.top()])
                color[work_top.top()] = 1;
            if (adjacency_list[work_top.top()].size() == counters[work_top.top()])                                                
            {
                color[work_top.top()] = 2;
                answer.push_back(work_top.top());
                work_top.pop();
            }
            else
            {
                if (color[Get_top(work_top)] == 1) 
                    label = false;
                else 
                    if (!color[Get_top(work_top)])
                    {
                        int toptop = work_top.top();
                        work_top.push(Get_top(work_top));
                        counters[toptop]++;
                    }
                    else
                        counters[work_top.top()]++;
            }
        }
   
    }

    void Graph::Get_answer()
    {
        if (label)
        {
            cout << "Yes\n";
            for (int i = answer.size() - 1; i >= 0; i--)
                cout << answer[i] << ' ';
        }
        else cout<< "No\n";
    }


int main()
{
    int n,m;
    cin >> n >> m;
    vector< vector<int> > adl(n + 1, vector<int>(0));

    for (int i = 0; i < m; i++)
    {
        int top,t;
        cin >> top >> t;
        adl[top].push_back(t);
    }

    Graph graph(n + 1,adl);

    for (int i = 1; i <= n; i++)
        if (!graph.Is_visit(i)) 
            graph.DFS(i);

    graph.Get_answer();

    return 0;
}

