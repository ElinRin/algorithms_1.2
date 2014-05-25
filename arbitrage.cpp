
#include <vector>
#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::vector;
using std::stack;

class Currency
{
public:
	void Floyd_Uorshal();
	void Ford_Bellman();
	void Read_list();

private:
	vector< vector <double> > currency_list_FB;
	vector< vector <double> > currency_list_FU;
	vector< vector<int> > mediator;
    vector<double> money;
    vector<int> pred;
	int number;

	void Get_way_FU(int begin, int end);
    void Get_way_FB(int note);

};

void Currency::Read_list()
{
	cout << "Number of currency: ";
	cin >> number;

	currency_list_FU.resize( number, vector<double> (number,1) );
	currency_list_FB.resize( number, vector<double> (number,1) );
	mediator.resize( number, vector<int> (number));
	pred.resize(number);

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < number; j++)
		{
			double element;
            if (i!=j)
            {
                cout << "How much note " << j + 1 << " for one " << i + 1 << '\n';
                cin >> element;
            }
            else
                element = 1;
			currency_list_FU[i][j] = element;
			currency_list_FB[i][j] = element;
			mediator[i][j] = i;
			pred[i] = i;
		}
	}


}

void Currency::Get_way_FU(int begin, int end)
{
    int x = mediator[begin][end];
	if (x == begin)
		cout << x + 1 << " -> ";
	else
	{
		Get_way_FU(begin,x);
		Get_way_FU(x, end);
	}
}


void Currency::Floyd_Uorshal()
{
	bool label = false;
	int note;

	for (int k = 0; k < number; k++) if (!label)
	{
		for (int i = 0; i < number; i++) if (!label)
		{
			for (int j = 0; j < number; j++) if (!label)
			{
				if (currency_list_FU[i][j] < currency_list_FU[i][k]*currency_list_FU[k][j])
				{
					currency_list_FU[i][j] = currency_list_FU[i][k]*currency_list_FU[k][j];
					mediator[i][j] = k;
				}
			}
			if (currency_list_FU[i][i] > 1)
			{
				label = true;
				note = i;
			}
		}
	}

	if (label)
	{
		cout << "You will be able to make money of air, if you do this way:" << '\n';
		Get_way_FU(note, note);
		cout << note + 1 << '\n';
	}
	else
		cout << "You won't be able to make money of air" << '\n';
}

void Currency::Ford_Bellman()
{
	money.resize(number, 1);
	bool label;
	int note;

	for (int k = 0; k <= number; k++)
	{
        label = false;
		for (int i = 0; i < number; i++) if (!label)
		{
			for (int j = 0; j < number; j++) if (!label)
			{
				if (money[j] < money[i]*currency_list_FB[i][j])
				{
					money[j] = money[i]*currency_list_FB[i][j];
					pred[j] = i;
					note = j;
					label = true;
				}
			}
		}
	}

	if (label)
	{
		cout << "You will be able to make money of air, if you do this way:" << '\n';
		Get_way_FB(note);
	}
	else
	{
		cout << "You won't be able to make money of air" << '\n';
	}
}


void Currency::Get_way_FB(int note)
{
	stack<int> order;
	vector<bool> used(number, 0);
	int begin;

	while (used[note] != 1)
	{
		used[note] = 1;
		order.push(note);
		note = pred[note];
		if (used[note] == 1) begin = note;
	}
	cout << begin + 1 << " -> ";

	while (order.top() != begin)
	{
		cout << order.top() + 1 << " -> ";
		order.pop();
	}
	cout << order.top() + 1 << '\n';

}


int main()
{
	Currency Cur;
	Cur.Read_list();
	Cur.Floyd_Uorshal();
	Cur.Ford_Bellman();

	return 0;
}
