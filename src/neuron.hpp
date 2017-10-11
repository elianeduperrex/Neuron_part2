#ifndef NEURON_HPP
#define NEURON_HPP
#include <fstream>
#include <cmath>
#include <vector>

class Neuron {
	private :
		//membrane potential
		double membrane_potential_;
		
		//times when spikes occure
		std::vector<double> times_;
		
		double clock_;
		
		bool isRefract_;
		
		void isRefractory(const double& t);
	
	public:		
		Neuron();
		~Neuron();
		
		//getters
		double getMembranePotential() const;	
		int getTimeSize() const;
		double getTimeSpike(const int& i) const;
		std::vector<double> getTimeSpikeTab() const;
		bool getRefractoryState() const;
		
		bool update(const double& t, const double& input_current, bool spike);
		
		void addSpikeTime(const double& t);
		
		//methods to store data in a file
		void spikeTimeEnter(std::ofstream& file) const;	
		void potentialEnter(std::ofstream& file) const;	
		
};

#endif

