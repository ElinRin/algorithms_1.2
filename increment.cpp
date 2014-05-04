#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
 
class DSU
{
private:
    vector<int> parent;
    vector<int> rg;
   
public:
    void Add(int top);
    int Find(int t);
    void Union(int a, int b);
};

void DSU::Add(int top)
{
    int size = parent.size();
    parent.resize(top + size);
    rg.resize(top + size);
    for (int i = 0; i < parent.size(); i++)
        parent[i] = i;
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
        if (rg[a] > rg[b])
            parent[b] = a;
        else
            parent[a] = b;
        if (rg[a] == rg[b]) rg[a]++;
    }
}

int main()
{
    DSU dsu;
    cout << "V <number> - add <number> vertices \n";
    cout << "L <link> - add link \n";
    cout << "? <vert vert> - Is link between this vertices exists? \n";
    cout << "C - close \n";

    char c;
    while (1) 
    {
        cin >> c;
        int a, b;
        if ((c == 'C') || (c == 'c'))
        {
            cout << "Goodbye\n";
            break;
        }
        else 
            if ((c == 'V') || (c == 'v'))
            {
                cin >> a;
                dsu.Add(a);
            } 
        else 
            if ((c == 'L') || (c == 'l'))
            {
                cin >> a >> b;
                dsu.Union(a, b);
            } 
        else 
            if (c == '?') 
            {
                cin >> a >> b;
                if (dsu.Find(a) == dsu.Find(b)) 
                    cout << "Yes\n";
                else 
                    cout << "No\n";
            }
        else
            cout << "Error\n";
    }
    return 0;
}

