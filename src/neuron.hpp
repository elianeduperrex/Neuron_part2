#ifndef NEURON_HPP
#define NEURON_HPP
#include <fstream>
#include <cmath>
#include <vector>
#include "constant.hpp"

class Neuron {
	private :
		//membrane potential
		double membrane_potential_;
		
		//times when spikes occure
		std::vector<double> times_;
		
		double clock_;
		
		//tell if the neuron is refractory
		bool isRefract_;
		
		//index of the neuron in the network
		Index index;
		
		//to store the time when the neuron will receive the spike from another one with each J
		std::vector<std::vector<double> > timeDelay;
		
		//test if the neuron is refractory at time t, if so isRefract_ = true
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
		Index getIndex() const;
		double getClock() const;
		
		void setMembranePotential(const double& memb);
		//update the neuron
		bool update(const double& t, const double& input_current, bool spike);
		//when a neuron receive an amplitude J
		void receive(const double& j);
		//overload of the method, used in network to store the time with the delay and the particular J
		void receive(const double& j, const double& t);
		
		void addSpikeTime(const double& t);
		
		//methods to store data in a file
		void spikeTimeEnter(std::ofstream& file) const;	
		void potentialEnter(std::ofstream& file) const;
};

#endif

