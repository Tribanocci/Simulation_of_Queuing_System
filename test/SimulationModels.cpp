#include "SimulationModels.h"

Source::Source(float l, int c) { 
	Source_Rate = l; Source_Capacity = c; n = 0;
}

bool Source::isFull() {
	if (n == Source_Capacity)
		return true;
	else
		return false;
}

Server::Server(float l, int c) { 
	Server_Rate = l; Buffer_Capacity = c; state = 0; n = 0; 
} 
bool Server::isFull() {
	if (n == Buffer_Capacity + 1)
		return true;
	else
		return false;
}


Item::Item(int id, float ar_t) : Item_id(id), Arrive_Time(ar_t), Departure_Time(-1.0) {}//we dont know the departure time at initialization, with the code value "-1" we know that item is STILL IN system
void Item::setDepart_Time(float d_t) { Departure_Time = d_t; } //setter
float Item::getDepart_Time() const { return Departure_Time; } //getter
float Item::getArrive_Time() const { return Arrive_Time; } //getter
bool Item::hasDeparted() const {
	if (Departure_Time != -1.0) 
		return true; 
	else 
		return false;
}
//-----------MODEL constructor--------------------------
Model::Model(float T, int S_C, float S_R, int Ser_Num, std::vector<int> Ser_Capacities, std::vector<float> Ser_Rates) { 
	T_SIM = T; Server_Num = Ser_Num; //Model Parameters Initialization
	Model_Source = new Source(S_R, S_C);  //Source Initialization
	for (int i{0}; i < Server_Num; i++){
		Server_Vector.emplace_back(Ser_Rates[i], Ser_Capacities[i]); //Server Initialization
	}
		
}
Model::~Model() {delete Model_Source;}
//---------Rand generators----------
float Model::Uniform_Rand(){
	return 1.0*rand()/RAND_MAX;
}

float Model::Expo_Rand(float U, float lamda) {
	return -log(U)/lamda;
} 
//--------------------------------------
//-----------MMnK MODEL constructor--------------------------
Model_MMnK::Model_MMnK(float T, int S_C, float S_R, int Ser_Num, std::vector<int> Ser_Capacities, std::vector<float> Ser_Rates) : Model(T, S_C, S_R, Ser_Num, Ser_Capacities, Ser_Rates) {
	for (int i{0}; i < Server_Num; i++) {
		Time_next.push_back(T_SIM + 1);//The " + 1 "  is for "infinite" time
		System_Capacity += Server_Vector[i].Buffer_Capacity + 1; // The " + 1"  is for the item that is being proccesed
	}
	Time_next.push_back(T_SIM + 1); //The " + 1 "  is for the event of arrival, for "infinite" time respectively**
	System_Capacity += Model_Source->Source_Capacity; //
	
}
//=========================================================================================
//-------------------SIMULATION function----------------------------------------------------
void Model_MMnK::Simulation(){
	std::cout << "System capacity is : " << System_Capacity <<"\n";
	int item_id{0};
	int next_e{Server_Num};
	float prev_time{0};
	float U = Uniform_Rand();
	Time_next[Server_Num] = Expo_Rand(U, Model_Source->Source_Rate); //First event is an arrival
	//std::cout << "Arrival Time \t" << Time_next[Server_Num] << "\n";
	time += Time_next[Server_Num]; //Clock to first arrival
	std::cout << "==============================================\n";
	std::cout << "Simulation starting...\n";
	while (time < T_SIM) { //START SIMULATION
		//std::cout << "Clock says : " << time << "\n";
		//---------IMPLEMENT NEXT EVENT---------------------------------------------------------------------
		if (next_e == Server_Num) { //Next Event: ARRIVAL
			if ( Items_in_System < System_Capacity){ //Item Enters System
				//std::cout << "Item Entering\n";
				item_id++;
				try {
					Item_Vector.emplace_back(item_id, time);//Create item, note arrival time
				}
			    catch (std::exception& e) {
					std::cerr << "Error: " << e.what() << "\n";
				}
	
				
				U = Uniform_Rand();
				Time_next[Server_Num] = time + Expo_Rand(U, Model_Source->Source_Rate); //Schedule Next Arrival
				//std::cout << "New Arrival Time \t" << Time_next[Server_Num] << "\n";
				if (Items_in_System < Server_Num) { //If there is Idle server, proceed for process
					{int i{0};
						for ( auto& machine : Server_Vector){//Find the first IDLE Server
							if (machine.state == 0){
								machine.state = item_id;
								U = Uniform_Rand();
								Time_next[i] = time + Expo_Rand(U, machine.Server_Rate); //Store proceess time
								//std::cout << "Item No. : " << item_id << "assigned to Server No. :" << i+1 << "\t with process time of: " << Time_next[i] << "\n";
								break;
							}
							i++;//Keep looking
						}	
					}//Scop created for killing int i
					
				}
				else {//Item goes to queue
					Items_in_queue.push(item_id);
				}
				Items_in_System++;
			}
			else {// Item is rejected
				Rej += 1;
				U = Uniform_Rand();
				Time_next[Server_Num] = time + Expo_Rand(U, Model_Source->Source_Rate); //Schedule Next Arrival
				//std::cout << "-------------------ITEM REJECTION----------- \n";
			}
		}	
		else {	//Next Event: Departure
			int item_id_exited{Server_Vector[next_e].state}; //store item_id which was procesed, from Server STATE
			Item_Vector[item_id_exited - 1].setDepart_Time(time);// Store Departure_Time to the Item
			// ---------------------------------the " - 1 " is need beacause item indexing begins with "1", but vector indexing begins with "zero"
			//std::cout << "Item No. :" << item_id_exited << "   Processed from server No. :" << next_e + 1 << "\t";
			Items_in_System--; //Item Exited
			ThroughPut++; //Production Update
			if (Items_in_System < Server_Num){
				Server_Vector[next_e].state = 0; //No Item waiting for process, so server is now IDLE
				Time_next[next_e] = T_SIM + 1; //No process is schedule as a next event
				//std::cout << "And now server is IDLE\n";
			}
			else { //Items are waiting in Queue
				Server_Vector[next_e].state = Items_in_queue.front(); //Bring the next item
				Items_in_queue.pop();
				U = Uniform_Rand();
				Time_next[next_e] = time + Expo_Rand(U, Server_Vector[next_e].Server_Rate); //Schedule the new process time
				//std::cout << "And now server is SERVING next from line\n";
			}
		}
		//----------Find NEXT EVENT---------------------------------------------------------------------
		auto min_time_ptr = min_element(Time_next.begin(), Time_next.end());
		int min_index = distance(Time_next.begin(), min_time_ptr);
		prev_time = time;
		time = *min_time_ptr;
		next_e = min_index;
		//std::cout << "Next Event is : " << next_e << "\n";
		N_result += Items_in_System*(time - prev_time);//Calculate AREA for Number of items, in order to calculate Average items n system
	}	
	//--------Result Calculation------------------------------------------------------------------------------	
	for (const auto& element : Item_Vector) {
		if (element.hasDeparted()){ 
			Time_in_System_result += (element.getDepart_Time() - element.getArrive_Time());
			//std::cout << "time calc..." << Time_in_System_result << "\n";
		}
		//std::cout << "Item: " << element.Item_id << "\tArriv time: " << element.Arrive_Time << "\tDepart time: " << element.Departure_Time << "\n";
    }
	Time_in_System_result = Time_in_System_result/T_SIM;
	N_result = N_result/T_SIM;
	Output_Rate = (ThroughPut*1.0)/T_SIM;
	std::cout << "...Simulation Terminated\n";
}