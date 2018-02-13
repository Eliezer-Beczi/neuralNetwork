#include "neuralNetwork.h"

using namespace std;

template <class T>
struct szamPar {
	vector<T> inputs;
	vector<T> outputs;

	szamPar(const vector<T> &inputs, const vector<T> &outputs) {
		this->inputs = inputs;
		this->outputs = outputs;
	}
};

const std::string ACT_FUNC = "sigmoid";

int main(int argc, char const *argv[]) {
	neuralNetwork<long double> nn(2, 2, 1);

	vector<szamPar<long double>> data;

	data.push_back(szamPar<long double>({1.0, 1.0}, {0.0}));
	data.push_back(szamPar<long double>({1.0, 0.0}, {1.0}));
	data.push_back(szamPar<long double>({0.0, 1.0}, {1.0}));
	data.push_back(szamPar<long double>({0.0, 0.0}, {0.0}));

	unsigned i = 0;

	while(i < 1000000000) {
		unsigned randNum = i % data.size();

		for(unsigned j = 0; j < 5000; ++j) {
			nn.train(data[randNum].inputs, data[randNum].outputs);
		}

		vector<long double> result = nn.feedForward({1.0, 1.0});

		if(i % 1000000 == 0) {
			for(unsigned j = 0; j < result.size(); ++j) {
				cout << result[j] << endl;
			}
		}

		++i;
	}

	return 0;
}