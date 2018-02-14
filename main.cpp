#include "neuralNetwork.h"

using namespace std;

template <class T>
struct szamPar {
	vector<T> inputs;
	vector<T> targets;

	szamPar(const vector<T> &inputs, const vector<T> &targets) {
		this->inputs = inputs;
		this->targets = targets;
	}
};

const string ACT_FUNC = "tanh";

int main(int argc, char const *argv[]) {
	neuralNetwork<long double> nn(2, 16, 1);

	vector<szamPar<long double>> data;

	data.push_back(szamPar<long double>({0.0, 0.0}, {0.0}));
	data.push_back(szamPar<long double>({1.0, 0.0}, {1.0}));
	data.push_back(szamPar<long double>({0.0, 1.0}, {1.0}));
	data.push_back(szamPar<long double>({1.0, 1.0}, {0.0}));

	random_device r;
	default_random_engine re(r());
	uniform_int_distribution<> dist(0, 3);

	for(unsigned i = 0; i < 50000; ++i) {
		for(unsigned j = 0; j < 10; ++j) {
			unsigned num = dist(re);
			nn.train(data[num].inputs, data[num].targets);
		}

		for(unsigned i = 0; i < 4; ++i) {
			cout << "inputs: " << data[i].inputs[0] << ' ' << data[i].inputs[1] << endl;
			cout << "outputs: " << nn.feedForward(data[i].inputs).back() << endl;
			cout << "targets: " << data[i].targets.back() << endl << endl;
		}
	}

	return 0;
}