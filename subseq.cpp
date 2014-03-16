
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>


using namespace std;

void input(vector<int> &sequence)
{
	int size;
    cin >> size;
    sequence.reserve(size);
    for (int pos = 0; pos < size; ++pos)
    {
    	int a;
        cin >> a;
        sequence.push_back(a);
    }
}


void output(vector<int> &sequence, vector<int> &answer)
{
     for (int pos = answer.size() - 1 ; pos >= 0; pos--)
        cout << sequence[answer[pos]] << ' ';
}

void max_inc_subseq(vector<int> &sequence, vector<int> &last_element_of_seq, vector<int> &pred, vector<int> &leos_index, vector<int> &answer, int &res )
{
	int size = sequence.size();

	last_element_of_seq[0] = numeric_limits<int>::min();
	for (int pos = 1; pos <= size; ++pos)
		last_element_of_seq[pos] = numeric_limits<int>::max();
 
	for (int pos = 0; pos < size; pos++)
	{
		int index = int (upper_bound (last_element_of_seq.begin(), last_element_of_seq.end(),sequence[pos]) - last_element_of_seq.begin());
		if (last_element_of_seq[index - 1] < sequence[pos] && sequence[pos] < last_element_of_seq[index])
		{
			last_element_of_seq[index] = sequence[pos];
			pred[pos] = index != 1 ? leos_index[index - 1]  : -1;
			leos_index[index] = pos;
			res = res > index ? res : index;
	

		}
	}

	
    int pos = leos_index[res];
    while (pos != -1 )
    {
        answer.push_back(pos);
        pos = pred[pos];
    }
}

int main()
{
	int res = 0;
	int res_index = 0;
	vector<int> sequence;
	input(sequence);
	vector<int> last_element_of_seq(sequence.size() + 1);
	vector<int> pred(sequence.size(),-1);
	pred[0] = -1;
	vector<int> leos_index(sequence.size());
	vector<int> answer;
    max_inc_subseq(sequence, last_element_of_seq, pred, leos_index, answer, res);
    output(sequence,answer);
 
	return 0;
}
