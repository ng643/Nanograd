#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <unordered_set>

class Value
{
private:
	struct Node
	{
		float data;
		float grad;
		std::shared_ptr<Node> prev[2];
		std::function<void()> _backprop;

		Node(float data);
		void topo(std::vector<std::shared_ptr<Node>>& out, std::unordered_set<std::shared_ptr<Node>>& visited, std::shared_ptr<Node> curr);
	};
	std::shared_ptr<Node> node;
	Value(std::shared_ptr<Node> node);
	void resetGrads(std::vector<std::shared_ptr<Node>>& nodes);
public:
	Value(float data);
	float getData() const;
	float getGrad() const;
	Value operator+(const Value& x) const;
	Value operator*(const Value& x) const;
	Value operator-() const;
	void backprop();
	void resetGrads();
};
