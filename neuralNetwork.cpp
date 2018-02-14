#include "neuralNetwork.h"

template <class T>
neuralNetwork<T>::neuralNetwork(unsigned const &inputNeurons, unsigned const &hiddenNeurons, unsigned const &outputNeurons, const std::string &funcName, const T &learningRate) {
	this->neurons.push_back(inputNeurons);
	this->neurons.push_back(hiddenNeurons);
	this->neurons.push_back(outputNeurons);

	this->weights.push_back(Matrix<T>(hiddenNeurons, inputNeurons));
	this->weights.push_back(Matrix<T>(outputNeurons, hiddenNeurons));

	// Init weights
	this->weights[0].fillRand();
	this->weights[1].fillRand();

	this->biases.push_back(Matrix<T>(hiddenNeurons, 1));
	this->biases.push_back(Matrix<T>(outputNeurons, 1));

	// Init biases
	this->biases[0].fillRand();
	this->biases[1].fillRand();

	this->actFunc = this->actFuncObj.getActivationFunction(funcName);

	this->learningRate = learningRate;
	this->numOfLayers = 3;
}

template <class T>
neuralNetwork<T>::neuralNetwork(const std::vector<unsigned> &neurons, const std::string &funcName, const T &learningRate) {
	this->neurons = neurons;

	for(unsigned i = 0; i < neurons.size() - 1; ++i) {
		this->weights.push_back(Matrix<T>(neurons[i + 1], neurons[i]));
		this->weights.back().fillRand();

		this->biases.push_back(Matrix<T>(neurons[i + 1], 1));
		this->biases.back().fillRand();
	}

	this->actFunc = this->actFuncObj.getActivationFunction(funcName);

	this->learningRate = learningRate;
	this->numOfLayers = neurons.size();
}

template <class T>
neuralNetwork<T>::neuralNetwork(const neuralNetwork<T> &cpy) {
	this->neurons = cpy.neurons;
	this->weights = cpy.weights;
	this->biases = cpy.biases;

	this->actFunc = cpy.actFunc;
	this->actFuncObj = cpy.actFuncObj;

	this->numOfLayers = cpy.numOfLayers;
	this->learningRate = cpy.learningRate;
}

template <class T>
neuralNetwork<T>::~neuralNetwork() {

}

template <class T>
T neuralNetwork<T>::getLearningRate() {
	return this->learningRate;
}

template <class T>
void neuralNetwork<T>::setLearningRate(T const &learningRate) {
	this->learningRate = learningRate;
}

template <class T>
std::vector<T> neuralNetwork<T>::feedForward(const std::vector<T> &inputValues) {
	if(inputValues.size() != this->neurons[0]) {
		throw std::invalid_argument("the number of input values doesn't match the number of input nodes!");
	}

	Matrix<T> inputs = Matrix<T>::toColumnVector(inputValues);

	for(unsigned i = 0; i < this->numOfLayers - 1; ++i) {
		inputs = this->weights[i] * inputs + this->biases[i];
		inputs.applyFunction(this->actFunc.func);
	}

	return Matrix<T>::toArray(inputs);
}

template <class T>
void neuralNetwork<T>::train(const std::vector<T> &inputValues, const std::vector<T> &targetValues) {
	if(inputValues.size() != this->neurons[0]) {
		throw std::invalid_argument("the number of input values doesn't match the number of input nodes!");
	}

	if(targetValues.size() != this->neurons.back()) {
		throw std::invalid_argument("the number of target values doesn't match the number of output nodes!");
	}

	std::vector<Matrix<T>> matrices;
	matrices.push_back(Matrix<T>::toColumnVector(inputValues));

	for(unsigned i = 0; i < this->numOfLayers - 1; ++i) {
		Matrix<T> temp = this->weights[i] * matrices.back() + this->biases[i];
		temp.applyFunction(this->actFunc.func);
		matrices.push_back(temp);
	}

	unsigned i = this->numOfLayers - 2;
	Matrix<T> errors = Matrix<T>::toColumnVector(targetValues) - matrices.back();

	while(true) {
		Matrix<T> gradients = Matrix<T>::applyFunction(matrices[i + 1], this->actFunc.derivative_func);
		gradients %= errors * this->learningRate;

		this->weights[i] += gradients >> matrices[i];
		this->biases[i] += gradients;

		if(i == 0) {
			break;
		}

		errors = this->weights[i] << errors;
		--i;
	}
}

template class neuralNetwork<float>;
template class neuralNetwork<double>;
template class neuralNetwork<long double>;