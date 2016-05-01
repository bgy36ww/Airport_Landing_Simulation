#include "dist_gen.h"

double dist_gen::gen() {
return dist->operator()(*generator);}
dist_gen& dist_gen::operator=(const dist_gen& dd){
mean=dd.get_mean();
std=dd.get_std();
generator=std::make_shared<std::default_random_engine>();
dist=std::make_shared<std::normal_distribution<double>>(mean,std);
std::cout<<"copy assignment constructor"<<std::endl;
return *this;
}

