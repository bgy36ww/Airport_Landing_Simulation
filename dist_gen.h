#ifndef DIST_GEN
#define DIST_GEN

#include <iostream>
#include <random>
#include <memory>

class dist_gen{
	double mean;
	double std;
	std::shared_ptr<std::normal_distribution<double>> dist;
	std::shared_ptr<std::default_random_engine> generator;
	
	public:
	dist_gen():dist(std::make_shared<std::normal_distribution<double>>()),generator(std::make_shared<std::default_random_engine>()){
	std::cout<<"constructor"<<std::endl;}
	dist_gen(double m, double s):mean(m),std(s),dist(std::make_shared<std::normal_distribution<double>>(m,s)),generator(std::make_shared<std::default_random_engine>())
	{
		std::cout<<"initializer"<<std::endl;

	}
	dist_gen(const dist_gen& dd):mean(dd.get_mean()),std(dd.get_std()),dist(std::make_shared<std::normal_distribution<double>>(dd.get_mean(),dd.get_std())),generator(std::make_shared<std::default_random_engine>()){std::cout<<"copy constructor"<<std::endl;}	
//	dist_gen& operator=(const dist_gen& dd):mean(dd.get_mean()),std(dd.get_std()),dist(std::make_shared<std::normal_distribution<double>>(dd.get_mean(),dd.get_std())),generator(std::make_shared<std::default_random_engine>()){std::cout<<"copy assignment constructor"<<std::endl;}
	dist_gen& operator=(const dist_gen& dd);
	double get_mean() const {return mean;}
	double get_std() const {return std;}
	double gen();
	~dist_gen(){std::cout<<"destructor"<<std::endl;}
//	double gen(double,double) const;
};

#endif
