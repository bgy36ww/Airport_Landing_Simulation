#ifndef EVENT_LIST
#define EVENT_LIST
#include<iostream>
#include<queue>


class Event_List{
public:
Event_List();
Event_List(double t,const char e,double s):arr_time(t),event(e),curr_size(s){}
Event_List& operator()(double, const char,double);
char get_event()const{
	return event;
}
double get_time()const{
	return arr_time;
}
double get_size()const{
	return curr_size;
}
private:
double arr_time;
char event;
int curr_size;
public:
static bool is_landing;


};

struct Last_Plane_In_Queue{
Last_Plane_In_Queue(double t, int s):time_to_land(t),size(s){}
Last_Plane_In_Queue& operator()(double,int);
double time_to_land;
int size;
};

struct stats{
int plane_in_queue;
int plane_in_system;
double plane_dt;
double crowded_time;
bool crowded;
stats():plane_in_queue(0),plane_in_system(0),plane_dt(0),crowded_time(0.00),crowded(false){}
std::ostream& get_stats(std::ostream&)const;
};

struct Less_By_Time
{
        bool operator()(const Event_List &lhs, const Event_List &rhs) const
        {
                return lhs.get_time()>rhs.get_time();
        }
};





#endif
