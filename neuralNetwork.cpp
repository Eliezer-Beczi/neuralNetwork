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