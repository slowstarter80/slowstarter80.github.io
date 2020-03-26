
#include <iostream>

using namespace std; 

template <typename T>
T add(T a1, T a2)
{
	return a1 + a2;
}

template <typename t1, typename t2>
t2 sub(t1 a1, t2 a2)
{
	return a1 - a2;
}


int main(void)
{
	cout<<"template int type add 1 + 2 = "<<add<float>(1, 2)<<endl;;
	cout<<"template float type add 1.0 + 2.0 = "<<add<float>(1.0, 2.0)<<endl;;
	cout<<"template float type sub 1.0 - 2.0 = "<<sub(1, 2.0)<<endl;;

	return 0;
}
