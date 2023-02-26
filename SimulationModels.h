#ifndef SIMULATION_MODELS_H
#define SIMULATION_MODELS_H
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <exception>



class Source {
	public:
		int Source_Capacity; float Source_Rate;
		int n;
		Source(float l, int c);
		~Source() {}
		bool isFull(); 	
};




class Server {
	public:
		float Server_Rate; int Buffer_Capacity; 
		int state; // 0: Sleep, [1..i..inf) : Working the item with item_id = i
		int n; //current number of items in buffer PLUS process
		Server(float l, int c);
		~Server() {}
		bool isFull(); 
		
};

class Item {
	public:
		Item(int id, float ar_t);//we dont know the departure time at initialization, with the code value "-1" we know that item is STILL IN system
		~Item() {}
		void setDepart_Time(float d_t);//setter
		float getDepart_Time() const ;//getter
		float getArrive_Time() const ;//getter
		bool hasDeparted() const;
	private:
		int Item_id;
		float Arrive_Time; //Store the arrival time of an item
		float Departure_Time; //Store the departure time of an item
};

		
class Model {
	public:
		Model(float T, int S_C, float S_R, int Ser_Num);
		~Model();
		//----------Model Outputs----------------------
		float N_result{0.0}; //number of items in system over (TIME) MULTIPLIED by TIME, at the end becomes Average Items in system
		float Time_in_System_result{0.0}; //At the end is Average Time In System
		int ThroughPut{0}; //Number of items Exited he system
		float Output_Rate{0.0};
		//----------------------------------------------
		float Uniform_Rand();
		float Expo_Rand(float U, float lamda);
	protected:
		Source* Model_Source;
		std::vector<Server> Server_Vector;
		//---------Model Inputs------------------------
		float T_SIM;
		int Server_Num;
		//----------------------------------------------
		int item_id{0};

		
};




class Model_MMnK : public Model {
	public:
		float time{0};
		int System_Capacity{0};
		int Items_in_System{0};
		std::vector<float> Time_next; // Vector of next time of events. 
//INDEX NOTATION, Index (0, Server_Num-1): is for proceess from servers.  Index Server_Num: is for arrival**.
		std::vector<Item> Item_Vector;
		std::queue<int> Items_in_queue;
		int Rej{0}; //Number of rejected items
		Model_MMnK(float T, int S_C, float S_R, int Ser_Num);
		float Expo_Rand(float U, float lamda) {return -log(U)/lamda;} 
		void Simulation(); 
		 
};