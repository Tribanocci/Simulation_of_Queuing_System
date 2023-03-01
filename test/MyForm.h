#pragma once

#include <cliext/vector>
#include <vector>
#include <iterator>


namespace SimulationApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	delegate void ButtonClickEventHandler1(System::Object^ sender, System::EventArgs^ e);
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			CreateServerInputs();
		}

		event ButtonClickEventHandler1^ ButtonClicked;

		
		
		property int GetSourceCapacity {
			int get() {
				return Convert::ToInt32(Source_Capacity_Input->Text);
			}
		};

		property float GetSourceRate {
			float get() {
				return Convert::ToSingle(Source_Rate_Input->Text);
			}
		};

		property float GetSimulationTime {
			float get() {
				return Convert::ToSingle(Simulation_Time_Input->Text);
			}
		};
		
		property int GetServerNumber {
			int get() {
				return Convert::ToInt32(Server_Number);
			}
		};

		

		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete Server_Capacities_Inputs_ptr;
			Server_Capacities_Inputs_ptr = nullptr;
			delete Server_Rates_Inputs_ptr;
			Server_Rates_Inputs_ptr = nullptr;
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:

	private: System::Windows::Forms::Label^ Model_Input_Label;
	private: System::Windows::Forms::ComboBox^ Model_selection;
	private: System::Windows::Forms::RadioButton^ hasBuffers_false;
	private: System::Windows::Forms::RadioButton^ hasBuffers_true;
	private: System::Windows::Forms::Label^ isServerBuffers_label;
	private: System::Windows::Forms::TextBox^ Simulation_Time_Input;
	private: System::Windows::Forms::Label^ Simulation_Time_label;
	private: System::Windows::Forms::TextBox^ Source_Capacity_Input;
	private: System::Windows::Forms::Label^ Source_Capacity_label;
	private: System::Windows::Forms::TextBox^ Source_Rate_Input;
	private: System::Windows::Forms::Label^ Source_Rate_label;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ AddServerButton;
	public: std::vector<int> *Server_Capacities_Inputs_ptr = new std::vector<int>();
	public: std::vector<float> *Server_Rates_Inputs_ptr = new std::vector<float>();

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^ SimulationResultsButton;
	public: System::Windows::Forms::ListBox^ Results;
	private: System::Windows::Forms::Button^ Reset_Button;
	public:
	private: int Server_Number = 0;
	
		 
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->hasBuffers_false = (gcnew System::Windows::Forms::RadioButton());
			this->hasBuffers_true = (gcnew System::Windows::Forms::RadioButton());
			this->isServerBuffers_label = (gcnew System::Windows::Forms::Label());
			this->Simulation_Time_Input = (gcnew System::Windows::Forms::TextBox());
			this->Simulation_Time_label = (gcnew System::Windows::Forms::Label());
			this->Source_Capacity_Input = (gcnew System::Windows::Forms::TextBox());
			this->Source_Capacity_label = (gcnew System::Windows::Forms::Label());
			this->Source_Rate_Input = (gcnew System::Windows::Forms::TextBox());
			this->Source_Rate_label = (gcnew System::Windows::Forms::Label());
			this->Model_Input_Label = (gcnew System::Windows::Forms::Label());
			this->Model_selection = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->AddServerButton = (gcnew System::Windows::Forms::Button());
			this->SimulationResultsButton = (gcnew System::Windows::Forms::Button());
			this->Results = (gcnew System::Windows::Forms::ListBox());
			this->Reset_Button = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->hasBuffers_false);
			this->groupBox1->Controls->Add(this->hasBuffers_true);
			this->groupBox1->Controls->Add(this->isServerBuffers_label);
			this->groupBox1->Controls->Add(this->Simulation_Time_Input);
			this->groupBox1->Controls->Add(this->Simulation_Time_label);
			this->groupBox1->Controls->Add(this->Source_Capacity_Input);
			this->groupBox1->Controls->Add(this->Source_Capacity_label);
			this->groupBox1->Controls->Add(this->Source_Rate_Input);
			this->groupBox1->Controls->Add(this->Source_Rate_label);
			this->groupBox1->Controls->Add(this->Model_Input_Label);
			this->groupBox1->Controls->Add(this->Model_selection);
			this->groupBox1->Location = System::Drawing::Point(53, 42);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(333, 386);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"groupBox1";
			// 
			// hasBuffers_false
			// 
			this->hasBuffers_false->AutoSize = true;
			this->hasBuffers_false->Location = System::Drawing::Point(264, 257);
			this->hasBuffers_false->Name = L"hasBuffers_false";
			this->hasBuffers_false->Size = System::Drawing::Size(39, 17);
			this->hasBuffers_false->TabIndex = 10;
			this->hasBuffers_false->TabStop = true;
			this->hasBuffers_false->Text = L"No";
			this->hasBuffers_false->UseVisualStyleBackColor = true;
			// 
			// hasBuffers_true
			// 
			this->hasBuffers_true->AutoSize = true;
			this->hasBuffers_true->Location = System::Drawing::Point(203, 257);
			this->hasBuffers_true->Name = L"hasBuffers_true";
			this->hasBuffers_true->Size = System::Drawing::Size(43, 17);
			this->hasBuffers_true->TabIndex = 9;
			this->hasBuffers_true->TabStop = true;
			this->hasBuffers_true->Text = L"Yes";
			this->hasBuffers_true->UseVisualStyleBackColor = true;
			// 
			// isServerBuffers_label
			// 
			this->isServerBuffers_label->AutoSize = true;
			this->isServerBuffers_label->Location = System::Drawing::Point(32, 261);
			this->isServerBuffers_label->Name = L"isServerBuffers_label";
			this->isServerBuffers_label->Size = System::Drawing::Size(129, 13);
			this->isServerBuffers_label->TabIndex = 8;
			this->isServerBuffers_label->Text = L"Do Servers have Buffers\?";
			// 
			// Simulation_Time_Input
			// 
			this->Simulation_Time_Input->Location = System::Drawing::Point(203, 101);
			this->Simulation_Time_Input->Name = L"Simulation_Time_Input";
			this->Simulation_Time_Input->Size = System::Drawing::Size(100, 20);
			this->Simulation_Time_Input->TabIndex = 7;
			// 
			// Simulation_Time_label
			// 
			this->Simulation_Time_label->AutoSize = true;
			this->Simulation_Time_label->Location = System::Drawing::Point(32, 104);
			this->Simulation_Time_label->Name = L"Simulation_Time_label";
			this->Simulation_Time_label->Size = System::Drawing::Size(106, 13);
			this->Simulation_Time_label->TabIndex = 6;
			this->Simulation_Time_label->Text = L"Give Simulation Time";
			// 
			// Source_Capacity_Input
			// 
			this->Source_Capacity_Input->Location = System::Drawing::Point(203, 224);
			this->Source_Capacity_Input->Name = L"Source_Capacity_Input";
			this->Source_Capacity_Input->Size = System::Drawing::Size(100, 20);
			this->Source_Capacity_Input->TabIndex = 5;
			// 
			// Source_Capacity_label
			// 
			this->Source_Capacity_label->AutoSize = true;
			this->Source_Capacity_label->Location = System::Drawing::Point(32, 227);
			this->Source_Capacity_label->Name = L"Source_Capacity_label";
			this->Source_Capacity_label->Size = System::Drawing::Size(128, 13);
			this->Source_Capacity_label->TabIndex = 4;
			this->Source_Capacity_label->Text = L"Give the Source Capacity";
			// 
			// Source_Rate_Input
			// 
			this->Source_Rate_Input->Location = System::Drawing::Point(203, 177);
			this->Source_Rate_Input->Name = L"Source_Rate_Input";
			this->Source_Rate_Input->Size = System::Drawing::Size(100, 20);
			this->Source_Rate_Input->TabIndex = 3;
			// 
			// Source_Rate_label
			// 
			this->Source_Rate_label->AutoSize = true;
			this->Source_Rate_label->Location = System::Drawing::Point(32, 180);
			this->Source_Rate_label->Name = L"Source_Rate_label";
			this->Source_Rate_label->Size = System::Drawing::Size(110, 13);
			this->Source_Rate_label->TabIndex = 2;
			this->Source_Rate_label->Text = L"Give the Source Rate";
			// 
			// Model_Input_Label
			// 
			this->Model_Input_Label->AutoSize = true;
			this->Model_Input_Label->Location = System::Drawing::Point(32, 42);
			this->Model_Input_Label->Name = L"Model_Input_Label";
			this->Model_Input_Label->Size = System::Drawing::Size(96, 13);
			this->Model_Input_Label->TabIndex = 1;
			this->Model_Input_Label->Text = L"Select Model Type";
			// 
			// Model_selection
			// 
			this->Model_selection->FormattingEnabled = true;
			this->Model_selection->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"M/M/n/K", L"Flow Model" });
			this->Model_selection->Location = System::Drawing::Point(35, 58);
			this->Model_selection->Name = L"Model_selection";
			this->Model_selection->Size = System::Drawing::Size(121, 21);
			this->Model_selection->TabIndex = 0;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->AddServerButton);
			this->groupBox2->Location = System::Drawing::Point(553, 42);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(513, 386);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"groupBox2";
			// 
			// AddServerButton
			// 
			this->AddServerButton->Location = System::Drawing::Point(390, 80);
			this->AddServerButton->Name = L"AddServerButton";
			this->AddServerButton->Size = System::Drawing::Size(75, 23);
			this->AddServerButton->TabIndex = 1;
			this->AddServerButton->Text = L"Add Server";
			this->AddServerButton->UseVisualStyleBackColor = true;
			this->AddServerButton->Click += gcnew System::EventHandler(this, &MyForm::AddServerButton_Click);
			// 
			// SimulationResultsButton
			// 
			this->SimulationResultsButton->Location = System::Drawing::Point(969, 477);
			this->SimulationResultsButton->Name = L"SimulationResultsButton";
			this->SimulationResultsButton->Size = System::Drawing::Size(128, 58);
			this->SimulationResultsButton->TabIndex = 2;
			this->SimulationResultsButton->Text = L"Simulation Results";
			this->SimulationResultsButton->UseVisualStyleBackColor = true;
			this->SimulationResultsButton->Click += gcnew System::EventHandler(this, &MyForm::SimulationResultsButton_Click);
			// 
			// Results
			// 
			this->Results->FormattingEnabled = true;
			this->Results->Location = System::Drawing::Point(553, 457);
			this->Results->Name = L"Results";
			this->Results->Size = System::Drawing::Size(410, 95);
			this->Results->TabIndex = 4;
			// 
			// Reset_Button
			// 
			this->Reset_Button->Location = System::Drawing::Point(78, 487);
			this->Reset_Button->Name = L"Reset_Button";
			this->Reset_Button->Size = System::Drawing::Size(116, 34);
			this->Reset_Button->TabIndex = 5;
			this->Reset_Button->Text = L"Reset Parameters";
			this->Reset_Button->UseVisualStyleBackColor = true;
			this->Reset_Button->Click += gcnew System::EventHandler(this, &MyForm::Reset_Button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1123, 637);
			this->Controls->Add(this->Reset_Button);
			this->Controls->Add(this->Results);
			this->Controls->Add(this->SimulationResultsButton);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		void CreateServerInputs() {
			System::Windows::Forms::Label^ label1_ = gcnew System::Windows::Forms::Label();
			System::Windows::Forms::TextBox^ textBox1_ = gcnew System::Windows::Forms::TextBox();
			System::Windows::Forms::Label^ label2_ = gcnew System::Windows::Forms::Label();
			System::Windows::Forms::TextBox^ textBox2_ = gcnew System::Windows::Forms::TextBox();
			Server_Number++;
			//label_Server_Rate
			label1_->AutoSize = true;
			label1_->Location = System::Drawing::Point(60, 50 + 70*(Server_Number-1));
			label1_->Name = L"Server_Rate_label" + Server_Number ;
			label1_->Size = System::Drawing::Size(35, 13);
			label1_->TabIndex = (Server_Number-1)*4 ;
			label1_->Text = L"Give Process Rate of Server " + Server_Number;
			
			this->groupBox2->Controls->Add(label1_);
			// textBox_Server_Rate
// 
			textBox1_->Location = System::Drawing::Point(250, 43 + 70 * (Server_Number - 1));
			textBox1_->Name = L"Server"+Server_Number+"_Rate_Input";
			textBox1_->Size = System::Drawing::Size(100, 20);
			textBox1_->TabIndex = (Server_Number - 1) * 4 + 1;

			this->groupBox2->Controls->Add(textBox1_);

			//label_Server_Capacity
			label2_->AutoSize = true;
			label2_->Location = System::Drawing::Point(60, 80 + 70 * (Server_Number - 1));
			label2_->Name = L"Server_Capacity_label" + Server_Number;
			label2_->Size = System::Drawing::Size(35, 13);
			label2_->TabIndex = (Server_Number - 1) * 4 + 2;
			label2_->Text = L"Give Capacity of Server " + Server_Number;

			this->groupBox2->Controls->Add(label2_);

			// textBox_Server_Capacity
// 
			textBox2_->Location = System::Drawing::Point(250, 73 + 70 * (Server_Number - 1));
			textBox2_->Name = L"Server" + Server_Number + "_Capacity_Input";
			textBox2_->Size = System::Drawing::Size(100, 20);
			textBox2_->TabIndex = (Server_Number - 1) * 4 + 3;

			this->groupBox2->Controls->Add(textBox2_);
			this->AddServerButton->Location = System::Drawing::Point(390, 80 + 70 * (Server_Number - 1 ));
			
		}
#pragma endregion


	

private: System::Void AddServerButton_Click(System::Object^ sender, System::EventArgs^ e) {
	Diagnostics::Debug::WriteLine("Inside Button1");
	this->Server_Capacities_Inputs_ptr->push_back(Convert::ToInt32(this->groupBox2->Controls[L"Server" + Server_Number + "_Capacity_Input"]->Text));
	this->Server_Rates_Inputs_ptr->push_back(Convert::ToSingle(this->groupBox2->Controls[L"Server" + Server_Number + "_Rate_Input"]->Text));
	Diagnostics::Debug::WriteLine((*Server_Capacities_Inputs_ptr)[Server_Number-1]);
	CreateServerInputs();
}
private: System::Void SimulationResultsButton_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the text from the textbox
	
	Diagnostics::Debug::WriteLine("Inside Button2");
	// Raise the ButtonClicked event
	this->Results->Items->Clear();
	ButtonClicked(this, e);
}
private: System::Void Reset_Button_Click(System::Object^ sender, System::EventArgs^ e) {
	for (int i = 1; i <= Server_Number; i++) {
		delete this->groupBox2->Controls[L"Server" + i + "_Rate_Input"];
		delete this->groupBox2->Controls[L"Server" + i + "_Capacity_Input"];
		delete this->groupBox2->Controls[L"Server_Rate_label" + i];
		delete this->groupBox2->Controls[L"Server_Capacity_label" + + i];
	}
	this->Server_Capacities_Inputs_ptr->clear();
	this->Server_Rates_Inputs_ptr->clear();
	Server_Number = 0;
	CreateServerInputs();
	//this->AddServerButton->Location = System::Drawing::Point(390, 80 + 70 * (Server_Number - 1));
}
};
}
