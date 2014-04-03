#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


using std::cin;
using std::cout;
using std::string;
using std::min;
using std::vector;
using std::swap;
using std::stringstream;
using std::ifstream;


void wagner_fischer_alg(string & line1, string & line2, int &result)	
{ 
	int size_1 = line1.length();
	int size_2 = line2.length();

	vector< vector<int> > dynamic;
    dynamic.resize(size_1 + 1);
    for(int i = 0; i <= size_1; ++i)
    {
    	dynamic[i].resize(size_2 + 1);
    }
	for (int i = 0; i <= size_1; i++) 
	{
		dynamic[i][0] = i;
	}
	for (int i = 0; i <= size_2;i++) 
	{
		dynamic[0][i] = i;
	}

	for (int i = 1; i <= size_1; i++)
		for (int j = 1; j <= size_2; j++)
	 	{
			int score = (line1[i - 1] != line2[j - 1]) ? 1 : 0;
			dynamic[i][j] = min(min(dynamic[i-1][j] + 1,dynamic[i][j-1] + 1),dynamic[i-1][j-1] + score);
			
			
		}
	result = dynamic[size_1][size_2];
}

void hirschberg_alg(const string & line1, const string &line2, int first_1, int last_1, int first_2, int last_2, vector<string> &result)
{
        if (first_2 == last_2)
        {
            for (int i = last_1 - 1; i >= first_1; i--)
            {
            	stringstream wording;
            	wording << "Symbol " << line1[i] << " insert in second line in pos " << first_2 + 1;
            	result.push_back(wording.str());

            }
        } else
        if (first_1 == last_1 - 1)
		{

            bool label = false;
            for (int i = last_2 - 1; i >= first_2; i--)
            {
                if (label || (line2[i] != line1[first_1]))
                {
                	stringstream wording;
	            	wording << "Delete symbol in second line in pos " << i + 1;
	            	result.push_back(wording.str());                	
                } else if (line2[i] == line1[first_1])
                        label = true;
            }

            if (!label)
            {
            	stringstream wording;
                result.pop_back();
            	wording << "In second line change symbol in pos " << first_2 + 1 << " on " << line1[first_1];
    			result.push_back(wording.str());
            }

        } else
        {
        	int size_1 = last_1 - first_1 + 1;
            int size_2 = last_2 - first_2 + 1;
            vector<int> new_val_dyn_left(size_2), new_val_dyn_right(size_2), past_val_dyn_left(size_2), past_val_dyn_right(size_2);

            for (int i = 0; i < size_2; i++)
                    past_val_dyn_left[i] = new_val_dyn_left[i] = i;

            int separation_1 = size_1 / 2;
            for (int i = 1; i <= separation_1; i++)
            {
                new_val_dyn_left[0] = i;
                for (int j = 1; j < size_2; j++)
                {
                    int score = (line1[first_1 + i - 1] != line2[first_2 + j - 1]) ? 1 : 0;
                    new_val_dyn_left[j] = min(min(past_val_dyn_left[j] + 1, new_val_dyn_left[j - 1] + 1), past_val_dyn_left[j - 1] + score);
                }
                if (i < separation_1)
                        past_val_dyn_left.swap(new_val_dyn_left);
            }

            for (int i = 0; i < size_2; i++)
                    past_val_dyn_right[i] = new_val_dyn_right[i] = size_2 - i - 1;

            for (int i = size_1 - 1; i > separation_1; i--)
            {
                    new_val_dyn_right[size_2 - 1] = size_1 - i;
                    for (int j = size_2 - 2; j >= 0; j--)
                    {
                    	int score = (line1[first_1 + i - 1] != line2[first_2 + j]) ? 1 : 0;
                    	new_val_dyn_right[j] = min(min(past_val_dyn_right[j] + 1, new_val_dyn_right[j + 1] + 1), past_val_dyn_right[j + 1] + score);
                    }
                    if ( i > separation_1 + 1)
                    	past_val_dyn_right.swap(new_val_dyn_right);
            }
            separation_1 += first_1;

            int min_dist = size_1 + size_2;
            int separation_2 = 0;
            for (int i = 0; i < size_2; i++)
                    if (new_val_dyn_left[i] + new_val_dyn_right[i] < min_dist)
                    {
                            min_dist = new_val_dyn_left[i] + new_val_dyn_right[i];
                            separation_2 = i;
                    }
            separation_2 += first_2;

            new_val_dyn_left.clear(); past_val_dyn_left.clear();
            new_val_dyn_right.clear(); past_val_dyn_right.clear();

            hirschberg_alg(line1, line2, separation_1, last_1, separation_2, last_2, result);
            hirschberg_alg(line1, line2, first_1, separation_1, first_2, separation_2, result);
                
        }
}

int main()
{
	string l1,l2;
	//cin >> l1 >> l2;
    ifstream first("war_and_peace");
    ifstream second("war_and_peace1");
    getline(first, l1, '\0');
    getline(second, l2, '\0');

    int res = 0;
   // wagner_fischer_alg(l1,l2,res);
	// cout << res << '\n';
	vector <string> result;
    hirschberg_alg(l1,l2, 0, l1.length(), 0, l2.length(), result);
	cout << result.size() << '\n';
	for (int i = 0; i < result.size(); ++i)
	{
		cout << result[i] << '\n';
	}

	first.close();
	second.close();
	return 0;
}
