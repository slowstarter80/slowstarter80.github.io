
#include <iostream>

using namespace std; 

template <typename T>
class divide
{
	public :
		T result;

		divide(T a, T b) {
			result = a / b;
		}

		void showResult() {
			cout<<"result = "<<result<<endl;
		}
};


int main(void)
{
	divide<int> aClass(4,3);
	divide<float> bClass(4.0,3.0);

	aClass.showResult();
	bClass.showResult();

	return 0;
}
