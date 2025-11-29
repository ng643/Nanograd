#include "Value.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
	Value x1(4.0f);
	Value x2(10.0f);

	Value w1(0.3f);
	Value w2(0.5f);
	Value b(0.1f);

	std::vector<Value> x1s = {};
	std::vector<Value> x2s = {};
	std::vector<Value> y = {};

	for (int i = 0; i < 100000; i++)
	{
		Value t1 = ((double)rand() / (RAND_MAX));
		Value t2 = ((double)rand() / (RAND_MAX));
		x1s.push_back(t1);
		x2s.push_back(t2);
		if (t1.getData() > t2.getData())
		{
			y.push_back(Value(1.0f));
		}
		else
		{
			y.push_back(Value(-1.0f));
		}
	}

	for (size_t i = 0; i < 100000; i++)
	{
		Value p = x1s[i % x1s.size()]*w1 + x2s[i % x2s.size()]*w2 + b;
		Value mse = (y[i % y.size()] + -p) * (y[i % y.size()] + -p);
		mse.backprop();
		w1 = Value(w1.getData() + -w1.getGrad() * 0.001f);
		w2 = Value(w2.getData() + -w2.getGrad() * 0.001f);
		b = Value(b.getData() + -b.getGrad() * 0.001f);
	}

	std::cout << (x1 * w1 + x2 * w2 + b).getData() << std::endl;

	return 0;
}
