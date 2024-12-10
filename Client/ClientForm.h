#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ClientForm
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClientForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ showButton;
	protected:



	private: System::Windows::Forms::TextBox^ textBoxDir;
	private: System::Windows::Forms::TextBox^ textBoxExtension;
	private: System::Windows::Forms::DataGridView^ fileTable;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ size;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ date;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;







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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ClientForm::typeid));
			this->showButton = (gcnew System::Windows::Forms::Button());
			this->textBoxDir = (gcnew System::Windows::Forms::TextBox());
			this->textBoxExtension = (gcnew System::Windows::Forms::TextBox());
			this->fileTable = (gcnew System::Windows::Forms::DataGridView());
			this->name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->size = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->date = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileTable))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// showButton
			// 
			this->showButton->BackColor = System::Drawing::Color::Silver;
			this->showButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->showButton->Location = System::Drawing::Point(78, 369);
			this->showButton->Name = L"showButton";
			this->showButton->Size = System::Drawing::Size(214, 46);
			this->showButton->TabIndex = 0;
			this->showButton->Text = L"Show";
			this->showButton->UseVisualStyleBackColor = false;
			this->showButton->Click += gcnew System::EventHandler(this, &ClientForm::showButton_Click);
			// 
			// textBoxDir
			// 
			this->textBoxDir->Location = System::Drawing::Point(11, 37);
			this->textBoxDir->Multiline = true;
			this->textBoxDir->Name = L"textBoxDir";
			this->textBoxDir->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBoxDir->Size = System::Drawing::Size(337, 132);
			this->textBoxDir->TabIndex = 2;
			// 
			// textBoxExtension
			// 
			this->textBoxExtension->Location = System::Drawing::Point(11, 265);
			this->textBoxExtension->Name = L"textBoxExtension";
			this->textBoxExtension->Size = System::Drawing::Size(337, 22);
			this->textBoxExtension->TabIndex = 3;
			// 
			// fileTable
			// 
			this->fileTable->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			this->fileTable->AllowUserToAddRows = false;
			this->fileTable->AllowUserToDeleteRows = false;
			this->fileTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->fileTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->name, this->size,
					this->date
			});
			this->fileTable->Location = System::Drawing::Point(12, 11);
			this->fileTable->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->fileTable->Name = L"fileTable";
			this->fileTable->ReadOnly = true;
			this->fileTable->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->fileTable->RowHeadersWidth = 62;
			this->fileTable->RowTemplate->Height = 28;
			this->fileTable->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->fileTable->Size = System::Drawing::Size(780, 451);
			this->fileTable->TabIndex = 1;
			// 
			// name
			// 
			this->name->HeaderText = L"Name";
			this->name->MinimumWidth = 8;
			this->name->Name = L"name";
			this->name->ReadOnly = true;
			this->name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->name->Width = 390;
			// 
			// size
			// 
			this->size->HeaderText = L"Size";
			this->size->MinimumWidth = 8;
			this->size->Name = L"size";
			this->size->ReadOnly = true;
			this->size->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->size->Width = 125;
			// 
			// date
			// 
			this->date->HeaderText = L"Creation date";
			this->date->MinimumWidth = 8;
			this->date->Name = L"date";
			this->date->ReadOnly = true;
			this->date->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->date->Width = 200;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(7, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(310, 23);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Directory Paths (write in different lines)";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Menu;
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBoxDir);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->showButton);
			this->panel1->Controls->Add(this->textBoxExtension);
			this->panel1->Location = System::Drawing::Point(800, 11);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(358, 451);
			this->panel1->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label5->Location = System::Drawing::Point(9, 289);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(303, 16);
			this->label5->TabIndex = 8;
			this->label5->Text = L"If you want to monitor all files - leave empty";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label4->Location = System::Drawing::Point(9, 305);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(125, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Example: txt bin doc";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->label3->Location = System::Drawing::Point(9, 172);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(169, 32);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Example: C:\\User\\Folder1 \r\n                   \"C:\\User\\Folder2\"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(8, 240);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(243, 23);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Extensions (divided by spaces)";
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SlateGray;
			this->ClientSize = System::Drawing::Size(1170, 475);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->fileTable);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ClientForm";
			this->Text = L"FileMonitor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileTable))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void showButton_Click(System::Object^ sender, System::EventArgs^ e);

};
}
