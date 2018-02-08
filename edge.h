#ifndef EDGE_H
#define EDGE_H

#include <random>

template <class T>
class edge {
private:
	unsigned to;
	unsigned from;

	T weight;
	T deltaWeight;

	static std::random_device r;
	static std::default_random_engine re;
	static std::uniform_real_distribution<T> uniform_dist;

public:
	edge();
	~edge();
};

#endif