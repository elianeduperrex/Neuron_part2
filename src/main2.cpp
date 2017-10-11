#include <iostream>
#include <vector>
#include <fstream>

#include "neuron.hpp"
#include "constant.hpp"

using namespace std;


void initialiser(double& a, double& b, double& current);

int main() {
	//vector<Neuron> neurons;
	Neuron neuron1, neuron2;
	double  simTime(T_SART);
	double input_current_ext(0.0);
	double a, b;
	
	//file where the data would be collected
	ofstream entree_donne("times_spike");

	//ask the user to enter data for the time interval and the membrane potential
	initialiser(a, b, input_current_ext);
	entree_donne << "Membrane potential: " << endl;
	
	double input_current(0.0);
	//run simulation
	while (simTime <= T_STOP) {
		
		if (simTime >= a and simTime < b) {
			input_current = input_current_ext;
		 } else { 
		 	input_current = 0.0;
		 }
			//for (auto neuron : neurons) {
		
			//to store the membrane potential
			neuron1.potentialEnter(entree_donne);
			if (neuron1.update(H, input_current, false)) {
				cout << "Spike  occurs at " << simTime << " ms" << endl;
			}
			
			//cr;er une connexion entre les deux et par le biais d-un bool ou chercher dans vector dernier temps de spike 

			if (neuron2.update(H, 0.0, neuron1.getRefractoryState())) {
				cout << " at 2 " << simTime << endl;
			}
		
		simTime = simTime + N*H;

	}
	//to store the spike times
	neuron1.spikeTimeEnter(entree_donne);
	entree_donne.close();
	return 0;
}

void initialiser(double& a, double& b, double& input_current_ext) {
	cout << "Choose an external current: ";
	cin >> input_current_ext;
	do {	
		cout << "Choose a time interval: (a < b), a and b must be positive numbers ";
		cin >> a;
		cin >> b;
	} while (a >= b or a < 0.0 or b < 0.0) ;
	
	cout << "[a,b] = [" << a << ", " << b << "]" << endl;
}

/*bool testConnexion(const Neuron& neur, const Neuron& neuron1) {
	bool result(false);
	
	return result;
}*/
