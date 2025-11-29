#include "Value.hpp"

#include <algorithm>

Value::Node::Node(float data) : data(data), grad(0.0f), prev{}, _backprop(nullptr)
{

}

Value::Value(std::shared_ptr<Node> node) : node(std::move(node))
{

}

Value::Value(float data) : node(std::make_shared<Node>(data))
{

}

float Value::getData() const
{
	return node->data;
}

float Value::getGrad() const
{
	return node->grad;
}

Value Value::operator+(const Value& x) const
{
	std::shared_ptr<Node> out = std::make_shared<Node>(node->data + x.node->data);
	out->prev[0] = node;
	out->prev[1] = x.node;

	auto _backprop =
		[left = node, right = x.node, out = out.get()]()
		{
			left->grad += out->grad;
			right->grad += out->grad;
		};
	out->_backprop = _backprop;

	return Value(out);
}

Value Value::operator*(const Value& x) const
{
	std::shared_ptr<Node> out = std::make_shared<Node>(node->data * x.node->data);
	out->prev[0] = node;
	out->prev[1] = x.node;

	auto _backprop =
		[left = node, right = x.node, out=out.get()]()
		{
			left->grad += out->grad * right->data;
			right->grad += out->grad * left->data;
		};
	out->_backprop = _backprop;

	return Value(out);
}

Value Value::operator-() const
{
	std::shared_ptr<Node> out = std::make_shared<Node>(-node->data);
	out->prev[0] = node;

	auto _backprop =
		[left = node, out = out.get()]()
		{
			left->grad -= out->grad;
		};
	out->_backprop = _backprop;

	return Value(out);
}

void Value::backprop()
{
	std::vector<std::shared_ptr<Node>> out;
	std::unordered_set<std::shared_ptr<Node>> visited;
	node->topo(out, visited, node);
	resetGrads(out);
	node->grad = 1.0f;
	std::reverse(out.begin(), out.end());
	for (int i = 0; i < out.size(); i++)
	{
		if (out[i]->_backprop != nullptr)
		{
			out[i]->_backprop();
		}
	}
}

void Value::Node::topo(std::vector<std::shared_ptr<Node>>& out, std::unordered_set<std::shared_ptr<Node>>& visited, std::shared_ptr<Node> curr)
{
	visited.insert(curr);
	if (prev[0] != nullptr && visited.count(prev[0]) == 0)
	{
		prev[0]->topo(out, visited, prev[0]);
	}
	if (prev[1] != nullptr && visited.count(prev[1]) == 0)
	{
		prev[1]->topo(out, visited, prev[1]);
	}
	out.push_back(curr);
}

void Value::resetGrads()
{
	std::vector<std::shared_ptr<Node>> out;
	std::unordered_set<std::shared_ptr<Node>> visited;
	node->topo(out, visited, node);

	for (std::shared_ptr<Node> n : out)
	{
		n->grad = 0.0f;
	}
}

void Value::resetGrads(std::vector<std::shared_ptr<Node>>& nodes)
{
	for (std::shared_ptr<Node> n : nodes)
	{
		n->grad = 0.0f;
	}
}

