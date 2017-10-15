#include "neuron.hpp"
 #include <iostream>
 #include <cassert>


//when there hasn't been any spike, the neuron cannot be refractory
Neuron::Neuron() : membrane_potential_(0.0), clock_(0.0), isRefract_(false) {}

Neuron::~Neuron() {}

//update the membrane potential of the neuron depending on if it is refractory
bool Neuron::update(const double& t, const double& input_current, bool spike) {
	bool hasSpike(false);
	assert(t > 0.0);
	const double T_STOP_ = clock_ + t;
	while (clock_ < T_STOP_) {
		if (membrane_potential_ >= V_threshold) {
			addSpikeTime(clock_);
			hasSpike = true;	
			isRefract_ = true;
		}
		isRefractory(clock_); 
		if (!isRefract_) {
			membrane_potential_ = exp(-H/TAU)*membrane_potential_ + input_current*R*(1-exp(-H/TAU));
			if (timeDelay.size() != 0) {
				for (size_t i(0); i < timeDelay.size(); ++i) {
					if(abs(clock_ -timeDelay[i][0]) < 0.00001) {
						receive(timeDelay[i][1]);
					}
				}
			}
			if (spike) {
				receive(J);
			}
		} else {
			membrane_potential_ = V_RESET;
		}
		clock_ += t;
	}
	
	return hasSpike;
}

//return if the neuron is refractory
void  Neuron::isRefractory(const double& t) {		
	//for te first loop, the vector is empty 
	if (times_.size() != 0) {		
		isRefract_ = (times_.back() >0 and (t-times_.back()) <= TAU_REFRACTORY);	
	} 		
}
//different getters
int Neuron::getTimeSize() const {
	return times_.size();
}

double Neuron::getTimeSpike(const int& i) const {
	return times_[i];
}

double Neuron::getMembranePotential() const {
	return membrane_potential_;
}
std::vector<double> Neuron::getTimeSpikeTab() const {
	return times_;
}

bool Neuron::getRefractoryState() const {
	return isRefract_;
}

Index Neuron::getIndex() const {
	return index;
}

double Neuron::getClock() const {
	return clock_;
}

//add a new spike
void Neuron::addSpikeTime(const double& t) {
	times_.push_back(t);
}

//store the times when spikes occured in a file
void Neuron::spikeTimeEnter(std::ofstream& file) const {
	
	if (file.fail()) {
		std::cerr << "Error ";
	} else {
		file << "Spike time : " << std::endl;
		for (size_t i(0); i < times_.size(); ++i) {
			file << times_[i] << std::endl;
		}
	}		
}

//store the potential in a file
void Neuron::potentialEnter(std::ofstream& file) const {
	if (file.fail()) {
			std::cerr << "Error ";
		} else {
			file << membrane_potential_ << std::endl;
		}	
}

void Neuron::setMembranePotential(const double& memb) {
	membrane_potential_ = memb;
}

void Neuron::receive(const double& j) {
	membrane_potential_ += j;
}

void Neuron::receive(const double& j, const double& t) {
	assert(t != 0);
	timeDelay.push_back({t, j});
}
