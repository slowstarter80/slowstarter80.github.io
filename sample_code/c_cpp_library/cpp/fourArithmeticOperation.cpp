#include "fourArithmeticOperation.h"

template class fourArithmeticOperation<float>;
template class fourArithmeticOperation<int>;

template <typename T>
T fourArithmeticOperation<T>::addition(T a, T b)
{
	return a+b;
}

template <typename T>
T fourArithmeticOperation<T>::subtraction(T a, T b)
{
	return a-b;
}

template <typename T>
T fourArithmeticOperation<T>::multiplication(T a, T b)
{
	return a*b;
}

template <typename T>
T fourArithmeticOperation<T>::division(T a, T b)
{
	return a/b;
}
