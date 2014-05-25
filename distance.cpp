

#include <vector>
#include <ctime>
#include <iostream>
#include <queue>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::priority_queue;


struct Point
{
        double x;
        double y;
};

struct Edge
{
        Edge(int u_, int v_, double w_)
        :u(u_), v(v_), w(w_)
        {}
        int u;
        int v;
        double w;
        bool operator<(const Edge& edge) const{return (w < edge.w);}
};

class DSU
{
private:
    vector<int> parent;
    vector<int> rang;

public:
        DSU(int number);

    void Add_edge(int u, int v);
    int Find(int t);
    void Union(int a, int b);
    bool Is_exists(int u, int v);
};

DSU::DSU(int number):
parent(number),
rang(number, 1)
{
    for (int i = 0; i < parent.size(); i++)
    parent[i] = i;
}

bool DSU::Is_exists(int u, int v)
{
        if (u >= parent.size() || v >= parent.size())
        {
                cout << "ERROR\n";
                exit(0);
        }
        return (Find(u) == Find(v));
}

void DSU::Add_edge(int u, int v)
{
        if (u >= parent.size() || v >= parent.size())
        {
                cout << "ERROR\n";
                exit(0);
        }
        Union(u,v);
}

int DSU::Find(int t)
{
    if (parent[t] != t)
        parent[t] = Find(parent[t]);
    return parent[t];
}

void DSU::Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    if (a != b)
    {
        if (rang[a] > rang[b])
            parent[b] = a;
        else
            parent[a] = b;
        if (rang[a] == rang[b]) rang[a]++;
    }
}


class Cruscal
{
public:
        Cruscal();
private:
        priority_queue< Edge, vector<Edge> > edges_list;
        vector< vector<int> > edges_list_order;
        vector<Point> points;
        vector<int> used;
        vector < Point > answer;
        int full_distance;
        int distance;

        Point Box_Muller(Point centre, int sigma);
        void ReadGraph();
        void MinimalSpanningTree();
        void DFS(int node);
        void Get_way();
};

        Cruscal::Cruscal()
        {
                ReadGraph();
                MinimalSpanningTree();
                Get_way();
        }


        Point Cruscal::Box_Muller(Point centre, int sigma)
        {
                Point point;
                double x, y, s;
                do
                {
                        x = rand() % 100 / 100.0;
                        y = rand() % 100 / 100.0;
                        s = x*x + y*y;
                }while (s == 0 || s > 1);

                point.x = centre.x + sigma * x * sqrt( -2*log(s) / s );
                point.y = centre.y + sigma * y * sqrt( -2*log(s) / s );

                return point;
        }

        void Cruscal::ReadGraph()
        {
                int number_c, number_p, s1, s2;
                cout << "Number of centres: ";
                cin >> number_c;
                cout << "Number of points: ";
                cin >> number_p;
                cout << "Sigma1: ";
                cin >> s1;
                cout << "Sigma2: ";
                cin >> s2;

                full_distance = 0;

                for (int i = 0; i < number_c; i++)
                {
                        Point centre;
                        centre.x = 0;
                        centre.y = 0;
                        centre = Box_Muller(centre, s1);

                        for (int j = 0; j < number_p; j++)
                        {
                                points.push_back(Box_Muller(centre, s2));
                        }
                }

                for (int i = 0; i < points.size(); i++)
                {
                        for (int j = i + 1; j < points.size(); j++)
                        {
                                edges_list.push(Edge(i, j,   sqrt(pow(points[i].x - points[j].x, 2.0) + pow(points[i].y - points[j].y, 2.0))   ));
                        }
                }
                 for (int i = 1; i < points.size(); i++)
                {

                    full_distance+=sqrt(pow(points[i].x - points[i - 1].x, 2.0) + pow(points[i].y - points[i - 1].y, 2.0)) ;
                }
                full_distance+=sqrt(pow(points[0].x - points[points.size() - 1].x, 2.0) + pow(points[0].y - points[points.size() - 1].y, 2.0));
                edges_list_order.resize(points.size());
                answer.resize(points.size());
        }

        void Cruscal::MinimalSpanningTree()
        {
                DSU edges(points.size());

                while(!edges_list.empty())
                {
                        Edge edge = edges_list.top();
                        edges_list.pop();
                        if (!edges.Is_exists(edge.u, edge.v))
                        {
                                edges.Add_edge(edge.u, edge.v);
                                edges_list_order[edge.u].push_back(edge.v);
                                edges_list_order[edge.v].push_back(edge.u);
                        }
                }
        }


        void Cruscal::DFS(int node)
        {
                answer.push_back(points[node]);

                used[node] = true;
                for (int v = 0; v < edges_list_order[node].size(); v++)
                {
                        if (!used[edges_list_order[node][v]])
                                DFS(edges_list_order[node][v]);
                }
        }

        void Cruscal::Get_way()
        {
                distance = 0;
                used.resize(points.size(), false);
                DFS(0);
                cout << '\n';
                for (int i = 1; i < answer.size(); i++)
                {

                    distance+= sqrt(pow(answer[i].x - answer[i - 1].x, 2.0) + pow(answer[i].y - answer[i - 1].y, 2.0)) ;
                }
                distance+= sqrt(pow(answer[0].x - answer[answer.size()- 1].x, 2.0) + pow(answer[0].y - answer[answer.size() - 1].y, 2.0)) ;
                cout << distance << '\n';
                cout << full_distance << '\n';
        }



int main()
{
        Cruscal();
        return 0;
}
