#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include <vector>

#include "matrixAlgebra.h"
#include "activationFunction.h"

template <class T>
class neuralNetwork {
private:
	T learningRate;
	unsigned numOfLayers;

	std::vector<unsigned> neurons;
	std::vector<Matrix<T>> weights;
	std::vector<Matrix<T>> biases;

	activationFunction<T> actFuncObj;
	typename activationFunction<T>::couple actFunc;

public:
	neuralNetwork(unsigned const&, unsigned const&, unsigned const&, const std::string &funcName = "sigmoid", const T &learningRate = 0.1);
	neuralNetwork(const std::vector<unsigned>&, const std::string &funcName = "sigmoid", const T &learningRate = 0.1);
	neuralNetwork(const neuralNetwork<T>&);
	~neuralNetwork();

	T getLearningRate();
	void setLearningRate(T const&);

	std::vector<T> feedForward(const std::vector<T>&);
	void train(const std::vector<T>&, const std::vector<T>&);
};

#endif