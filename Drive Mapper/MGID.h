/**
MGID Network Drive Mapper
Bradley Hamelin, 5/20/2016
Programmed in C++ with Windows API
GUI program that takes in a users username and password, and uses them to make system calls to map drive letters.
The MGID module handles the GUI. See Mapper.cpp for logic.

*/



#include "Mapper.h"
#include <msclr\marshal_cppstd.h>
#pragma comment(lib,"shell32.lib")

#pragma once

namespace MGIDNetworkDriveMapper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MGID
	/// </summary>
	public ref class MGID : public System::Windows::Forms::Form
	{
	public:
		MGID(void)
		{
			//Determine if there is a logged in user currently or not.
			string drivelist = Mapper::getDriveList();

			for (char& c : drivelist) {
				if (c < 'Q' && c > 'G'){
					MessageBox::Show("User already logged in. Please restart the computer to log on to another profile.", "MGID Network Drive Mapper", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
					exit(0);
				}
			}
			
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MGID()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtPassword;

	private: System::Windows::Forms::TextBox^  txtUsername;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  btnLogin;

	private: System::Windows::Forms::Label^  lblOutput;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MGID::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->lblOutput = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(52, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(327, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Logon To Your MGID Project Account";
			// 
			// txtPassword
			// 
			this->txtPassword->Font = (gcnew System::Drawing::Font(L"Wingdings", 8.25F));
			this->txtPassword->Location = System::Drawing::Point(119, 73);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->PasswordChar = 'l';
			this->txtPassword->Size = System::Drawing::Size(269, 20);
			this->txtPassword->TabIndex = 2;
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(119, 47);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(269, 20);
			this->txtUsername->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(53, 73);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Password:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(53, 50);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"User Name:";
			// 
			// btnLogin
			// 
			this->btnLogin->Location = System::Drawing::Point(56, 99);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(332, 42);
			this->btnLogin->TabIndex = 3;
			this->btnLogin->Text = L"Logon";
			this->btnLogin->UseVisualStyleBackColor = true;
			this->btnLogin->Click += gcnew System::EventHandler(this, &MGID::button1_Click);
			// 
			// lblOutput
			// 
			this->lblOutput->AutoSize = true;
			this->lblOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOutput->ForeColor = System::Drawing::Color::Red;
			this->lblOutput->Location = System::Drawing::Point(53, 150);
			this->lblOutput->Name = L"lblOutput";
			this->lblOutput->Size = System::Drawing::Size(0, 16);
			this->lblOutput->TabIndex = 7;
			// 
			// MGID
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(465, 176);
			this->Controls->Add(this->lblOutput);
			this->Controls->Add(this->btnLogin);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MGID";
			this->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"MGID Project Authorization";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		//Make sure there's a password or do nothing
		if (txtPassword->TextLength == 0)
		{
			return;
		}

		//Create the mapping object
		std::string username = msclr::interop::marshal_as<std::string>(txtUsername->Text);
		std::string password = msclr::interop::marshal_as<std::string>(txtPassword->Text);

		Mapper mapper = Mapper(username, password);		

		string result = mapper.setMappings('H', 'I', 'J');
		if (result == "Connection Successful")
		{
			MessageBox::Show(gcnew String("Logged on successfully."), "MGID Network Drive Mapper", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			txtPassword->Text = "";
			ShellExecute(NULL, "open", "H:\\", NULL, NULL, SW_SHOWNORMAL);//TODO???????
			exit(0);
		}

		//Failed to logon. clear the password, clear any completed mappings.
		else if (result == "Logon Failed: Invalid Username/Password.")
		{
			//User feedback
			txtPassword->Text = "";
			lblOutput->Text = gcnew String(result.c_str());
		}
		else{
			MessageBox::Show(gcnew String(result.c_str()), "MGID Network Drive Mapper", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			exit(0);
		}
	}
};
}
