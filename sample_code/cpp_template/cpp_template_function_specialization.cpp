
#include <iostream>

using namespace std; 

template <typename T1>
void operation(T1 a1, T1 a2)
{
	cout<<"operation template function is called" <<endl;
	cout<<a1<<" + "<<a2<<" = "<<a1 + a2<<endl;
}

template <>
void operation(char a1, char a2)
{
	cout<<"operation template specialization function is called" <<endl;
	cout<<int(a1)<<" + "<<int(a2)<<" = "<<a1 + a2<<endl;
}


int main(void)
{
	operation<int>(1, 2.5);
	operation<float>(1.0, 2.5);;
	operation<char>('1', 2);;

	return 0;
}
