#include <vector>
#include <iostream>
#include "neuron.hpp"
#include "constant.hpp"

#ifndef NETWORK_HPP
#define NETWORK_HPP
using namespace std;

class Network {
	private :
		vector<Neuron*> neurons_;
		vector<vector<Index> > connexion_;
		
	public :
		Network();
		Network(vector<Neuron> neurons, vector<vector<Index> > connexion) ;
		~Network();
		//vector<Index> getConnexion (const Neuron& neur);
		void setConnexion(const Neuron& neur);
		//Index getNeuronIndex( Neuron* neur);
		void update(const double& t, const double& input_current, const bool& spike);
		
	//cr;er une connexion entre les deux et par le biais d-un bool ou chercher dans vector dernier temps de spike
	//problem: delay ne change rien avec les spike et les 2 neurons spike en meme temps 
};

#endif
