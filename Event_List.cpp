#include "Event_List.h"
Event_List& Event_List::operator()(double t, char e,double s){
this->event=e;
this->arr_time=t;
this->curr_size=s;
return *this;
}
bool Event_List::is_landing=false;
Last_Plane_In_Queue &Last_Plane_In_Queue::operator()(double t,int s){
this->time_to_land=t;
this->size=s;
return *this;
}
std::ostream& stats::get_stats(std::ostream &os)const{
return os<<"plane in queue is:"<<this->plane_in_queue<<"\n"<<"plane in system is:"<<this->plane_in_system<<"\nqueue crowed time:"<<this->crowded_time<<std::endl;
}



