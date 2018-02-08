#include "neuralNetwork.h"

template <class T>
neuralNetwork<T>::neuralNetwork(unsigned const &inputNeurons, unsigned const &hiddenNeurons, unsigned const &outputNeurons, const std::string &funcName) {
	this->neurons.push_back(std::vector<neuron<T>>(inputNeurons + 1));
	this->neurons.push_back(std::vector<neuron<T>>(hiddenNeurons + 1));
	this->neurons.push_back(std::vector<neuron<T>>(outputNeurons + 1));
	this->actFunc = activationFunction<T>::getActivationFunction(funcName);
}

template <class T>
neuralNetwork<T>::neuralNetwork(const std::vector<unsigned> &neurons, const std::string &funcName) {
	for(auto &&d : neurons) {
		this->neurons.push_back(std::vector<neuron<T>>(d + 1));
	}

	this->actFunc = activationFunction<T>::getActivationFunction(funcName);
}

template <class T>
neuralNetwork<T>::neuralNetwork(const neuralNetwork<T> &cpy) {
	this->neurons = cpy.neurons;
	this->actFunc = cpy.actFunc;
}

template <class T>
neuralNetwork<T>::~neuralNetwork() {

}

template <class T>
void neuralNetwork<T>::feedForward(const std::vector<T> &inputValues) {
	if(inputValues.size() != this->neurons[0].size() - 1) {
		throw std::invalid_argument("the number of input values doesn't match the number of input nodes!");
	}

	// Assign the input values to the input neurons
	for(unsigned i = 0; i < inputValues.size(); ++i) {
		this->neurons[0][i].setOutputValue(inputValues[i]);
	}

	// Forward propagate
	for(unsigned i = 1; i < this->neurons.size(); ++i) {
		std::vector<neuron<T>> &prevLayer = this->neurons[i];

		for(unsigned j = 0; j < this->neurons[i].size() - 1; ++j) {
			this->neurons[i][j].feedForward(prevLayer, this->actFunc);
		}
	}
}

template class edge<float>;
template class neuralNetwork<double>;
template class neuralNetwork<long double>;