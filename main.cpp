#include <iostream>
#include "dist_gen.h"
#include "Event_List.h"
#include <cstdlib>

int rand_size(){
        int size=rand()%100+1;
        size=size>33?size:0;
        size=size<=79?size:2;
        size=size>2?1:size;
        return size;
}


int main(int argc, char* argv[]){
//	dist_gen *d1=new dist_gen(5.4,3.2);
//	dist_gen d2(3.4,2.3);
//	dist_gen d4(2.4,1.4);

//	std::cout<<d2.gen()<<std::endl;
//	std::cout<<d4.gen()<<std::endl;

	dist_gen P_Dis_Gen[3][3]={{dist_gen(64,30),dist_gen(64,30),dist_gen(64,30)},{dist_gen(108,40),dist_gen(86,40),dist_gen(64,30)},{dist_gen(130,50),dist_gen(130,50),dist_gen(64,30)}};
	//distance distribution generator	

	dist_gen Inter_arr_gen(180,60);
	dist_gen Traveling_time_gen(600,150);
	dist_gen Landing_gen(120,30);
	dist_gen Go_around_gen(750,150);
	//other normal distribution time generator
	
	//constant queue time definition
	const unsigned int queue_time=40;
	//for holding generated time
	double t_time=0;
	double l_time=0;	

        Last_Plane_In_Queue last_plane(0,3);

        stats sta;
	size_t s_size=0;

	try{	

	Event_List P1(0.0,'S',rand_size());
	std::priority_queue<Event_List,std::vector<Event_List>,Less_By_Time> E_List;
	E_List.push(P1);
	P1=P1(86400.0,'F',rand_size());
	E_List.push(P1);
	double c_time=0;

	while (E_List.top().get_event()!='F')
	{
		if (sta.plane_in_queue>4)
		std::cout<<E_List.top().get_event()<<"\t"<<E_List.top().get_time()<<"\t"<<sta.plane_in_queue<<std::endl;
		c_time=E_List.top().get_time();
		if (sta.plane_in_queue>0) sta.plane_dt+=(c_time-l_time)*sta.plane_in_queue;
		if (sta.plane_in_queue>4) sta.crowded_time+=(c_time-l_time);
		switch(E_List.top().get_event())
		{
			case 'S'://S for begining of test
			E_List.pop();
			
			t_time=Inter_arr_gen.gen();
			while (t_time<=0)
			t_time=Inter_arr_gen.gen();
			P1=P1(t_time+c_time,'I',rand_size());
			E_List.push(P1);
			//set up new plane comes in
			//std::cout<<"S"<<std::endl;
			break;
			case 'I':
			s_size=E_List.top().get_size();
			E_List.pop();
			//I for initial contact point
			//new plane comes into system
			
			t_time=Inter_arr_gen.gen();
			while (t_time<=0)
			t_time=Inter_arr_gen.gen();
			P1=P1(t_time+c_time,'I',rand_size());
			//set up next coming plane
			E_List.push(P1);
			//set up when it will arrival to the queue
			
			t_time=Traveling_time_gen.gen();
			while (t_time<=0)
			t_time=Traveling_time_gen.gen();
			P1=P1(t_time+c_time,'E',s_size);
			E_List.push(P1);
			break;
			case 'E'://E for enter queue
			s_size=E_List.top().get_size();
			if (sta.plane_in_queue==0){	
			t_time=queue_time;
			while (t_time<=0)
                        t_time=queue_time;
			t_time+=c_time;
			sta.plane_in_queue++;
			
			last_plane.time_to_land=t_time;
			
			}else{
				
				t_time=P_Dis_Gen[s_size][last_plane.size].gen();
				while (t_time<=0)
                                t_time=P_Dis_Gen[s_size][last_plane.size].gen();
				t_time+=last_plane.time_to_land;
				sta.plane_in_queue++;
				last_plane.time_to_land=t_time;
				
			}
			last_plane.size=s_size;
			P1=P1(t_time,'T',E_List.top().get_size());
			E_List.pop();
			E_List.push(P1);
			break;
			case 'T'://T for threshold point
			                                                                                               
			s_size=E_List.top().get_size();
			sta.plane_in_queue--;
			
			
			if (!P1.is_landing){
				t_time=Landing_gen.gen();
                                while (t_time<=0)
                                t_time=Landing_gen.gen();
				t_time+=c_time;
				P1.is_landing=true;
				P1=P1(t_time,'L',s_size);
				E_List.pop();
				E_List.push(P1);
			}
			else{
				t_time=Go_around_gen.gen();
				while (t_time<=0)
                                t_time=Go_around_gen.gen();
				t_time+=c_time;
				P1=P1(t_time,'E',s_size);
				E_List.pop();
				E_List.push(P1);
			}
			break;
			case 'L'://L fot landing complete
			E_List.pop();
			P1.is_landing=false;
			break;
			default:
			std::cout<<"wrong event"<<std::endl;
			break;
		}
		if (E_List.top().get_event()=='F'){
		if (sta.plane_in_queue>0) sta.plane_dt+=(86400.0-c_time)*sta.plane_in_queue;
                if (sta.plane_in_queue>4) sta.crowded_time+=(86400.0-c_time);

		}
		l_time=c_time;
		
		
	}
	}
	catch(...){
		std::cout<<"something is wrong"<<std::endl;
	}
	
	std::cout<<"average plane in queue is:"<<sta.plane_dt/86400.0<<"time crowded:"<<sta.crowded_time/86400.0<<std::endl;
	return 0;
}
