#include "network.hpp"
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

Network::Network() {}

Network::Network(vector<Neuron> neurons, vector<vector<Index> > connexion) {
	assert(neurons.size() !=0);
	for (size_t i(0); i < neurons.size(); ++i) {
		Neuron* neuro(new Neuron (neurons[i]));
		neurons_.push_back(neuro);
	}
	for (size_t i(0); i < connexion.size() ; ++i) {
		connexion_.push_back(connexion[i]);
		for (size_t j(0); j < connexion[i].size() ; ++j) {
			connexion_[i][j] = (connexion[i][j]);
		}
	}
}

Network::~Network () {
	for (size_t i(0); i < neurons_.size(); ++i) {
		delete neurons_[i];
		neurons_[i] = nullptr;
	}
}

void Network::update(const double& t, const double& input_current, const bool& spike) {
	assert(neurons_.size() != 0);
	for (size_t i(0); i < neurons_.size(); ++i) {
		bool spik(false);
		assert(neurons_[i] != nullptr);
		spik = neurons_[i]->update(t, input_current, spike);
		if (spik) {
			cout << "neuron " << (i+1) << " has spike at time " << neurons_[i]->getClock() << endl;
			assert(neurons_[i] != nullptr);
			//give to the connected neuron the spike
			for (size_t j(0); j < connexion_[i].size(); ++j) {
				assert(neurons_[connexion_[i][j]] != nullptr);
				neurons_[connexion_[i][j]]-> receive(J, neurons_[i]->getClock() + D);
			}
		}
	}
}


