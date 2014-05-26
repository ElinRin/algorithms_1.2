#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <unordered_map>
 
using std::vector;
using std::unordered_map;
using std::swap;
using std::abs;
using std::cout;
using std::cin;
using std::string;
using std::min;
 
struct vertex
{
    int x;
    int y;
    bool operator==(const vertex &other) const {
        return x==other.x && y==other.y;
    }
};
 
struct weighted_vertex
{
    int w;
    vertex v;
};
 
struct hash
{
    size_t operator () (const vertex &p) const
    {
        return p.x*p.y + p.x;
    }
};
class Heap
{
private:
    vector<weighted_vertex> elements;
    unordered_map<vertex, int,hash> index_elements;
    void Go_up(int v);
    void Go_down(int v);
   
public:
    weighted_vertex top();
    void Push(weighted_vertex p);
    bool Empty();
};
 
class Dijkstra
{
    string s1, s2;
    Heap heap;
    int answer;
    int Delete_potentials(vertex begin, vertex end, int old);
    int Add_potential  (vertex begin, vertex end, int old);
   
public:
    Dijkstra(const string &string1, const string &string2);
    void Solve_distance();
    int Get_weight();
};
 
 
void Heap::Go_up(int v)
{
    if (v > 0 && elements[v].w < elements[(v - 1) / 2].w)
    {
        auto a = index_elements.find(elements[v].v);
        auto b = index_elements.find(elements[(v - 1) / 2].v);
        if (a != index_elements.end()) a->second = (v - 1) / 2;
        if (b != index_elements.end()) b->second = v;
        swap(elements[v], elements[(v - 1) / 2]);
        Go_up((v - 1) / 2);
    }
}
void Heap::Go_down(int v)
{
    int left = 2 * v + 1;
    int right = 2 * v + 2;
    int smallest = v;
    if (left < elements.size() && elements[left].w < elements[smallest].w)
        smallest = left;
    if (right < elements.size() && elements[right].w < elements[smallest].w)
        smallest = right;
    if (smallest != v)
    {
        auto a = index_elements.find(elements[v].v);
        auto b = index_elements.find(elements[smallest].v);
        if (a != index_elements.end()) a->second = smallest;
        if (b != index_elements.end()) b->second = v;
        swap(elements[v], elements[smallest]);
        Go_down(smallest);
    }
}
 
weighted_vertex Heap::top()
{
    weighted_vertex temp = elements[0];
    index_elements.erase(temp.v);
    elements[0] = elements[elements.size() - 1];
    elements.pop_back();
    Go_down(0);
    return temp;
}
 
void Heap::Push(weighted_vertex p)
{
    auto it = index_elements.find(p.v);
    if (it == index_elements.end())
    {
        elements.push_back(p);
        index_elements[p.v] = elements.size() - 1;
        Go_up(elements.size() - 1);
    }
    else if (elements[(*it).second].w > p.w)
    {
        elements[(*it).second].w = p.w;
        Go_up((*it).second);
    }
   
}
 
bool Heap::Empty()
{
    return elements.size() == 0;
}
 
Dijkstra::Dijkstra(const string &string1, const string &string2):
s1(string1),
s2(string2)
{}
void Dijkstra::Solve_distance()
{
    weighted_vertex wt = {0,0,0};
    heap.Push(wt);
    s1 = "0" + s1;
    s2 = "0" + s2;
    while (!heap.Empty())
    {
        weighted_vertex top = heap.top();
        vertex now_top = top.v;
 
        if (now_top.y + 1 < s2.length() && s1[now_top.x] != s2[now_top.y + 1])
        {
            vertex temp = now_top;
            temp.y++;
            weighted_vertex wt;
            wt.w = Add_potential(now_top, temp, top.w + 1);
            wt.v = temp;
            heap.Push(wt);
        }
       
        if (now_top.x + 1 < s1.length() && s1[now_top.x + 1] != s2[now_top.y])
        {
            vertex temp = now_top;
            temp.x++;
            weighted_vertex wt;
            wt.w = Add_potential(now_top, temp, top.w + 1);
            wt.v = temp;
            heap.Push(wt);
        }
       
        if (now_top.x + 1 < s1.length() && now_top.y + 1 < s2.length())
        {
            int weight = 0;
            if (s1[now_top.x + 1] != s2[now_top.y + 1]) weight = 1;
            vertex temp = now_top;
            temp.x++;
            temp.y++;
            weighted_vertex wt;
            wt.w = Add_potential(now_top, temp, top.w + 1);
            wt.v = temp;
            heap.Push(wt);
        }
   
        if (now_top.x == (int)s1.length() - 1 && now_top.y == (int)s2.length() - 1)
        {
            vertex t = {0,0};
            answer = Delete_potentials(t, now_top, top.w);
            break;
        }
    }
}
int Dijkstra::Get_weight()
{
    return answer;
}
int Dijkstra::Delete_potentials(vertex begin, vertex end, int old)
{
    int begin_c = abs(begin.x - begin.y);
    int end_c = abs(end.x - end.y);
    return old + begin_c - end_c;
}
 
int Dijkstra::Add_potential(vertex begin, vertex end, int old)
{
    int begin_c = abs(begin.x - begin.y);
    int end_c = abs(end.x - end.y);
    return old + end_c- begin_c;
}
 
 
 
int main()
{
    string string1;
    string string2;
    cin >> string1;
    cin >> string2;
    Dijkstra D(string1,string2);
    D.Solve_distance();
    cout << D.Get_weight();
 
    return 0;
}
