#include "neuron.h"

template <class T>
neuron<T>::neuron() {

}

template <class T>
neuron<T>::~neuron() {

}

template <class T>
void neuron<T>::setOutputValue(const T &data) {
	this->outputValue = data;
}

template <class T>
T neuron<T>::getOutputValue() {
	return this->outputValue;
}

template <class T>
void neuron<T>::feedForward(const std::vector<neuron<T>> &prevLayer, const typename activationFunction<T>::couple &actFunc) {
	// Sum the previous layer's outputs (which are your inputs)
	// Include the bias node from the previous layer

	T sum = 0.0;

	for(auto &&n : prevLayer) {
		sum += n.outputValue;
	}
}

template class edge<float>;
template class neuron<double>;
template class neuron<long double>;