#include "edge.h"

template <class T>
std::random_device edge<T>::r;

template <class T>
std::default_random_engine edge<T>::re(edge<T>::r());

template <class T>
std::uniform_real_distribution<T> edge<T>::uniform_dist(0.0, 1.0);

template <class T>
edge<T>::edge() {
	this->weight = edge<T>::uniform_dist(edge<T>::re);
}

template <class T>
edge<T>::~edge() {

}

template class edge<float>;
template class edge<double>;
template class edge<long double>;