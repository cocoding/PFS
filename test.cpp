#include<iostream>
using namespace std;
class b
{
	public:
		b(){
				cout<<"b Cons"<<endl;
				}
	virtual	~b()
		{
			cout<<"b Dis"<<endl;
		}
};
class a:public b
{
	public:
		a()
		{
			cout<<"a Cons"<<endl;
		}
		~a()
		{
				cout<<"a Dis"<<endl;
		}


};
int main()
{
	b *a_t=new a();
	delete a_t;
	

}
