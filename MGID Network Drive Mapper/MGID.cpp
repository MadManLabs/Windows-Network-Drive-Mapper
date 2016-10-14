#include "MGID.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MGIDNetworkDriveMapper::MGID form;
	Application::Run(%form);
}