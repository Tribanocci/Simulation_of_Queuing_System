#include "SimulationModels.h"

int main(){
	
	Model_MMnK Model_1(200, 6, 1, 2);
	Model_1.Simulation();
	std::cout << "N = " << Model_1.N_result << "\t T = " << Model_1.Time_in_System_result << "\tThrouput iyems : " << Model_1.ThroughPut << "\tStitll in system : " << Model_1.Items_in_System << "\n" ;
	
	
	return 0;
}