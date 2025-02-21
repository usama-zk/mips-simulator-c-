#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;


void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	mipssgui::MyForm form;
	Application::Run(% form);

}