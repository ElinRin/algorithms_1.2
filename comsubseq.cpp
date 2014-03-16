#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
void input(vector<int> &v)
{
  int size;
    cin >> size;
    v.reserve(size + 1);
    v.push_back(0);
    for (int pos = 1; pos <= size; ++pos)
    {
      int a;
        cin >> a;
        v.push_back(a);
    }
 
}
 
 
void max_com_inc_subseq(vector<int> &seq_a, vector<int> &seq_b)
{    
  int sizeA = seq_a.size();
  int sizeB = seq_b.size();
 

  vector<vector<int> > dynamic;
  dynamic.resize(sizeA);
  for(int pos = 0; pos < sizeA; ++pos)
  {
    dynamic[pos].resize(sizeB, 0);
  }

 
  vector<int> pred(sizeB);   
  for(int pos = 1; pos < sizeA; ++pos)
  {
    int psd_best = 0;      
    int best = 0;   
    for(int pos2 = 1; pos2 < sizeB; ++pos2)
    {
      dynamic [pos][pos2] = dynamic[pos-1][pos2];                        
      if ((seq_a[pos] == seq_b[pos2]) and (dynamic[pos-1][pos2] < best + 1))   
      {
        dynamic[pos][pos2] = best + 1;                        
        pred[pos2] = psd_best;
      }                          
      if ((seq_a[pos] > seq_b[pos2]) and (dynamic[pos-1][pos2] > best)) 
      {
        best = dynamic[pos-1][pos2];                
        psd_best = pos2;
      }
    }
  }  
 


  vector<int> answer;
  int end_of_seq = 1;         
  for (int j = 1; j < sizeB; j++)
  {
    if (dynamic[sizeA - 1][end_of_seq] < dynamic[sizeA - 1][j]) end_of_seq = j;
  }

  int pos = end_of_seq;
  while (pos != 0)  
  {
    answer.push_back(seq_b[pos]);
    pos = pred[pos];
  }

  cout << dynamic[sizeA - 1][end_of_seq] << '\n';
  /* 
  //вывод ответа
  if (dynamic[sizeA - 1][end_of_seq] != 0)
    for(int i = answer.size() - 1; i >= 0; --i)
      {
        cout << answer[i] << ' ';
      }
   */   
}
 
int main()
{
  vector<int> seq_a,seq_b;
  input(seq_a);
  input(seq_b);
  max_com_inc_subseq(seq_a,seq_b);
 
 
  return 0;
}
