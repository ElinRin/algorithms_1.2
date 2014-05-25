#include <iostream>
#include <vector>
#include <string>
 
using std::vector;
using std::cin;
using std::cout;
using std::string;
 
class Cub
{
private:
    string word;
    int number;
    int size_word;
    vector<vector<int> > word_in_cubes;
    vector<int> cubes;
    vector<bool> used;
    bool Select_letters(int v);
 
public:
    Cub();
    Cub(string w, int n);
    void Read_cubes();
    int Get_combination();
 
};
 
Cub::Cub(string w, int n):
word(w),
number(n),
size_word(w.length())
{}
bool Cub::Select_letters(int v)
{
    if (used[v])
        return false;
    used[v] = true;
 
    for (int i = 0; i < word_in_cubes[v].size(); ++i)
    {
        if (cubes[word_in_cubes[v][i]] == -1 || Select_letters(cubes[word_in_cubes[v][i]]))
        {
            cubes[word_in_cubes[v][i]] = v;
            return true;
        }
    }
 
    return false;
}
 
void Cub::Read_cubes()
{
    word_in_cubes.resize(size_word, vector<int>());
    for (int i = 0; i < number; ++i)
    {
        string cube;
        cin >> cube;
        for (int i1 = 0; i1 < (int)cube.length(); ++i1)
        {
            for (int i2 = 0; i2 < (int)word.length(); ++i2)
            {
                if (cube[i1] == word[i2])
                    word_in_cubes[i2].push_back(i);
            }
        }
    }
}
 
 
int Cub::Get_combination()
{
    cubes.assign(number , -1);
    for (int i = 0; i < size_word; ++i)
    {
        used.assign(size_word, 0);
        if (!Select_letters(i))
        {
            cout << "NO" << '\n';
            return 0;
        }
    }
 
    cout << "YES" << '\n';
 
    vector<int> answer(size_word);
     for (int i = 0; i < (int)cubes.size(); ++i)
    {
        if (cubes[i] != -1)
        {
            answer[cubes[i]] = i + 1;
        }
    }
 
    for (int i = 0; i < (int)answer.size(); ++i)
        cout << answer[i] << " ";
    cout << '\n';
 
    return 1;
 
}
 
int main()
{
    int n;
    string w;
    cin >> n;
    cin >> w;
 
    Cub C(w,n);
    C.Read_cubes();
    C.Get_combination();
    return 0;
}
