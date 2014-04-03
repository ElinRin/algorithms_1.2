
#include <string>
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::max;
using std::pair;

string getanswer(string &line, vector< vector<int> > &dynamic, int left, int right)
{
    if (left == right)
            return "";
    else
    if (left == right - 1)
            return line.substr(left,1);
    else
    {
            if (line[left] == line[right - 1])
                    return line[left] + getanswer(line, dynamic, left + 1, right - 1) + line[right - 1];
            else if (dynamic[left+1][right] > dynamic[left][right-1])
                    return getanswer(line, dynamic, left+1, right);
            else return getanswer(line, dynamic, left, right - 1);
    }
}

int main()
    {
    string line;
    cin >> line;
        int n = line.length();

    vector< vector<int> > dynamic(n + 1, vector<int>(n + 1));

        for (int i = 0; i < n; i++)
        {
            dynamic[i][i+1] = 1;
            dynamic[i][i] = 0;
        }
        dynamic[n][n] = 0;
        for (int k = 2; k <= n; k++)
        {

            for (int i = 0; i <= n - k; i++)
            {
                    int j = i + k;
                    if (line[i] == line[j - 1])
                            dynamic[i][j] = dynamic[i+1][j-1] + 2;
                    else
                            dynamic[i][j] = max(dynamic[i][j-1], dynamic[i+1][j]);
            }
        }

        string s = getanswer(line, dynamic, 0, line.length());
    cout << s.length() << '\n';
    cout << s;
    sreturn 0;
}

