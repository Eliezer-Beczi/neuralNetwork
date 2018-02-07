#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include <vector>

#include "neuron.h"
#include "activationFunction.h"

template <class T>
class neuralNetwork {
private:
	std::vector<std::vector<neuron<T>>> neurons;
	typename activationFunction<T>::couple actFunc;

public:
	neuralNetwork(unsigned const&, unsigned const&, unsigned const&, const std::string &funcName = "sigmoid");
	neuralNetwork(const std::vector<unsigned>&, const std::string &funcName = "sigmoid");
	neuralNetwork(const neuralNetwork<T>&);
	~neuralNetwork();
};

#endif