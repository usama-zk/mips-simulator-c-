#pragma once
#include "mips_code.cpp"
#include <msclr\marshal_cppstd.h>
#include <string>
using namespace std;
namespace mipssgui {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();
            mips = new MIPS();
            InitializeListViewColumns();
            UpdateRegisterView();
            UpdateMemoryView();
        }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
            delete mips;
        }

    private: System::Windows::Forms::ListView^ RegView;
    private: System::Windows::Forms::ListView^ memView;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::TextBox^ enter_ins_box;
    private: System::Windows::Forms::Button^ execute_button;

    private: System::ComponentModel::Container^ components;
           MIPS* mips;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               this->RegView = (gcnew System::Windows::Forms::ListView());
               this->memView = (gcnew System::Windows::Forms::ListView());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->label3 = (gcnew System::Windows::Forms::Label());
               this->enter_ins_box = (gcnew System::Windows::Forms::TextBox());
               this->execute_button = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();
               // 
               // RegView
               // 
               this->RegView->HideSelection = false;
               this->RegView->Location = System::Drawing::Point(791, 83);
               this->RegView->Name = L"RegView";
               this->RegView->Size = System::Drawing::Size(368, 607);
               this->RegView->TabIndex = 8;
               this->RegView->UseCompatibleStateImageBehavior = false;
               this->RegView->View = System::Windows::Forms::View::Details;
               // 
               // memView
               // 
               this->memView->HideSelection = false;
               this->memView->Location = System::Drawing::Point(384, 83);
               this->memView->Name = L"memView";
               this->memView->Size = System::Drawing::Size(352, 607);
               this->memView->TabIndex = 9;
               this->memView->UseCompatibleStateImageBehavior = false;
               this->memView->View = System::Windows::Forms::View::Details;
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->BackColor = System::Drawing::SystemColors::MenuHighlight;
               this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
               this->label1->Location = System::Drawing::Point(520, 30);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(81, 20);
               this->label1->TabIndex = 10;
               this->label1->Text = L"MEMORY";
               // 
               // label2
               // 
               this->label2->AutoSize = true;
               this->label2->BackColor = System::Drawing::SystemColors::MenuHighlight;
               this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
               this->label2->Location = System::Drawing::Point(932, 30);
               this->label2->Name = L"label2";
               this->label2->Size = System::Drawing::Size(93, 20);
               this->label2->TabIndex = 11;
               this->label2->Text = L"REGISTER";
               // 
               // label3
               // 
               this->label3->AutoSize = true;
               this->label3->BackColor = System::Drawing::SystemColors::Info;
               this->label3->Location = System::Drawing::Point(117, 208);
               this->label3->Name = L"label3";
               this->label3->Size = System::Drawing::Size(175, 20);
               this->label3->TabIndex = 12;
               this->label3->Text = L"ENTER INSTRUCTION";
               // 
               // enter_ins_box
               // 
               this->enter_ins_box->Location = System::Drawing::Point(63, 264);
               this->enter_ins_box->Name = L"enter_ins_box";
               this->enter_ins_box->Size = System::Drawing::Size(301, 26);
               this->enter_ins_box->TabIndex = 13;
               // 
               // execute_button
               // 
               this->execute_button->BackColor = System::Drawing::SystemColors::ActiveCaption;
               this->execute_button->ForeColor = System::Drawing::SystemColors::Desktop;
               this->execute_button->Location = System::Drawing::Point(147, 326);
               this->execute_button->Name = L"execute_button";
               this->execute_button->Size = System::Drawing::Size(105, 49);
               this->execute_button->TabIndex = 14;
               this->execute_button->Text = L"Execute";
               this->execute_button->UseVisualStyleBackColor = false;
               this->execute_button->Click += gcnew System::EventHandler(this, &MyForm::execute_button_Click);
               // 
               // MyForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::SystemColors::ControlDark;
               this->ClientSize = System::Drawing::Size(1322, 860);
               this->Controls->Add(this->execute_button);
               this->Controls->Add(this->enter_ins_box);
               this->Controls->Add(this->label3);
               this->Controls->Add(this->label2);
               this->Controls->Add(this->label1);
               this->Controls->Add(this->memView);
               this->Controls->Add(this->RegView);
               this->Name = L"MyForm";
               this->Text = L"MyForm";
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

           void InitializeListViewColumns() {
               RegView->Columns->Add("Register", 100, HorizontalAlignment::Left);
               RegView->Columns->Add("Value", 100, HorizontalAlignment::Left);

               memView->Columns->Add("Address", 100, HorizontalAlignment::Left);
               memView->Columns->Add("Value", 100, HorizontalAlignment::Left);
           }

           void UpdateRegisterView() {
               RegView->Items->Clear();
               for (int i = 0; i < t_reg; ++i) {
                   String^ regName = "$" + i;
                   String^ regValue = gcnew String(to_string(mips->Register[i]).c_str());

                   ListViewItem^ item = gcnew ListViewItem(regName);
                   item->SubItems->Add(regValue);
                   RegView->Items->Add(item);
               }
           }

           void UpdateMemoryView() {
               memView->Items->Clear();
               for (const auto& mem : mips->memory) {
                   String^ memAddress = gcnew String(to_string(mem.first).c_str());
                   String^ memValue = gcnew String(to_string(mem.second).c_str());

                   ListViewItem^ item = gcnew ListViewItem(memAddress);
                   item->SubItems->Add(memValue);
                   memView->Items->Add(item);
               }
           }

    private: System::Void execute_button_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
         
            String^ ins = enter_ins_box->Text;
          
            string stdIns = msclr::interop::marshal_as<std::string>(ins);
        
            vector<string> one_ins;
            one_ins.push_back(stdIns);

            // Now send tosimulator to execute this instruction
            mips->simulate(one_ins);

            //  update the views
            UpdateMemoryView();
            UpdateRegisterView();
        }
        catch (const runtime_error& ex) {
            String^ errorMessage = gcnew String(ex.what());
            MessageBox::Show(errorMessage, "Runtime Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        catch (System::AccessViolationException^ ex) {
            MessageBox::Show("An access violation occurred while executing the instruction.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        catch (Exception^ ex) {
            MessageBox::Show("An unexpected error occurred: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}