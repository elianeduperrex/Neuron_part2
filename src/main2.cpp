#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include "neuron.hpp"
#include "constant.hpp"

using namespace std;

//initialise the time interval and the external input current
void initialiser(double& a, double& b, double& current);
//test the connection between 2 neurons
bool testConnection();
//run the test
void runTest();

int main() {
	double  simTime(T_SART);
	double input_current_ext(0.0);
	double a, b;
	Neuron neuron1, neuron2;
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
		//to store the membrane potential
		neuron1.potentialEnter(entree_donne);
		if (neuron1.update(H, input_current, false)) {
			cout << "Spike for neuron 1 occured at " << simTime << " ms" << endl;
		} 
		if (neuron2.update(H, 0.0, neuron1.getRefractoryState())) {
			cout << "Spike for neuron 2 occured at " << simTime << " ms" << endl;
		}
		simTime = simTime + N*H;
	}
	//to store the spike times
	entree_donne << "Spike Time for neuron 1";
	neuron1.spikeTimeEnter(entree_donne);
	entree_donne << "Spike Time for neuron 2 ";
	neuron2.spikeTimeEnter(entree_donne);
	entree_donne.close();
	runTest();
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

bool testConnection () {
	Neuron neur;
	bool result(false) ;
	double current(0.0);
	bool receivedSpike(true);
	//creation of a neuron and give it that a neuron connected to it spiked
	//at initialisation the membrane potential is at 0.0 -> the potential varies only with J 
	(neur.update(H, current, receivedSpike)) ;
		if (neur.getMembranePotential() == J) {
			result  = true ;
		}
	return result ;
}

void runTest() {
	cout << "Connection test is ";
	if (testConnection()) {
			cout << " passed ";
		} else {
			cout << " failed ";
		}	
	cout << endl;
}
