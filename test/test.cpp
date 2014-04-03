#include<iostream>
#include<vector>
using namespace std;
int main()
{
		vector<int> vec_int;
		int i=0;
		for(i;i<10;i++)
				vec_int.push_back(i);
		vector<int>::iterator iter=vec_int.begin();
		for(;iter<vec_int.end();iter++)
		{
				if(*iter==5)
				{
						vec_int.erase(iter);
						continue;
				}
				cout<<*iter;
		}

}
