#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::max;

string subpalindromes(string &line, vector< vector<string> > &dynamic, int left, int right)
{

    if (left < 0 || left >= line.length() || right < 0 || right >= line.length() || left > right) return "";
    else
    if (dynamic[left][right] == "")
    {
        if (left == right)
        {
            dynamic[left][right] = line[left];
        }
        else
        {
            string subpal1 = subpalindromes(line, dynamic, left, right - 1);
            string subpal2 = subpalindromes(line, dynamic, left + 1, right);
            string subpal3 = (line[left] == line[right]) ? (line[left] + subpalindromes(line, dynamic, left + 1, right - 1) + line[right]) : "";
            int size = max(subpal3.length() ,max(subpal1.length(),subpal2.length()));
            if (size == subpal1.length()) dynamic[left][right] = subpal1;
            if (size == subpal2.length()) dynamic[left][right] = subpal2;
            if (size == subpal3.length()) dynamic[left][right] = subpal3;
        }
    }
    return dynamic[left][right];
}

int main()
{
    string line;
    cin >> line;

    vector< vector<string> > dynamic(line.length() + 1);
    for(int pos = 0; pos <= line.length(); ++pos)
    {
        dynamic[pos].resize(line.length() + 1, "");
    }

    string answer = subpalindromes(line, dynamic, 0, line.length()-1);
    cout << answer.length() << '\n';
    cout << answer;
    return 0;
}
