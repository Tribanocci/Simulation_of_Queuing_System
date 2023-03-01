#include "MyForm.h"
#include "SimulationModels.h"

using namespace System;
using namespace System::Windows::Forms;




void OnButtonClicked(System::Object^ sender, System::EventArgs^ e)
{
	SimulationApp::MyForm^ form = dynamic_cast<SimulationApp::MyForm^>(sender);
	int Source_Capacity_Value = form->GetSourceCapacity;
	float Source_Rate_Value = form->GetSourceRate;
	float Simulation_Time_Value = form->GetSimulationTime;
	int ServerNumber_Value = form->GetServerNumber;
	//std::vector<int> Server_Capacities_Inputs_std(form->Server_Capacities_Inputs.begin(), form->Server_Capacities_Inputs.end());
	//std::vector<float> Server_Rate_Inputs_std(form->Server_Rates_Inputs.begin(), form->Server_Rates_Inputs.end());

	//std::vector<int> Server_Capacities_Inputs_std(std::make_move_iterator(form->Server_Capacities_Inputs.begin()), std::make_move_iterator(form->Server_Capacities_Inputs.end()));

	//std::move(form->Server_Capacities_Inputs.begin(), form->Server_Capacities_Inputs.end(), cliext::make_ostream_iterator(Server_Capacities_Inputs_std));

	//std::move(std::make_move_iterator(form->Server_Capacities_Inputs.begin()), std::make_move_iterator(form->Server_Capacities_Inputs.end()), std::ostream_iterator<int>(std::back_inserter(Server_Capacities_Inputs_std), ""));



	Model_MMnK Model_1(Simulation_Time_Value, Source_Capacity_Value, Source_Rate_Value, ServerNumber_Value-1, *(form->Server_Capacities_Inputs_ptr), *(form->Server_Rates_Inputs_ptr));
	Model_1.Simulation();
	
	form->Results->Items->Add("Average Items in System : " + Model_1.N_result.ToString() );
	form->Results->Items->Add("Average Time Spent in System : " + Model_1.Time_in_System_result.ToString() );
	form->Results->Items->Add("Total Throughput : " + Model_1.ThroughPut.ToString() );
 
}


void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SimulationApp::MyForm form;
	SimulationApp::MyForm^ form_ptr = %form;

	// Subscribe to the ButtonClicked event
	form_ptr->ButtonClicked += gcnew SimulationApp::ButtonClickEventHandler1(OnButtonClicked);
	

	Application::Run( form_ptr);

}