#include "ClientForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System;
using namespace System::Diagnostics;
using namespace std;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Client::ClientForm form;
	Application::Run(% form);
}