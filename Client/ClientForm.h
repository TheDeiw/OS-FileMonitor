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
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ fileTable;




	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ size;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ date;




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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->fileTable = (gcnew System::Windows::Forms::DataGridView());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->size = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->date = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileTable))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Silver;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(75, 390);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(214, 46);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Test Button";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &ClientForm::button1_Click);
			// 
			// fileTable
			// 
			this->fileTable->AllowUserToAddRows = false;
			this->fileTable->AllowUserToDeleteRows = false;
			this->fileTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->fileTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->name, this->size,
					this->date
			});
			this->fileTable->Location = System::Drawing::Point(9, 24);
			this->fileTable->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->fileTable->Name = L"fileTable";
			this->fileTable->ReadOnly = true;
			this->fileTable->RowHeadersWidth = 62;
			this->fileTable->RowTemplate->Height = 28;
			this->fileTable->Size = System::Drawing::Size(779, 696);
			this->fileTable->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(11, 37);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(337, 30);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(11, 118);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(337, 22);
			this->textBox2->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(230, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Directory Paths (write in different lines)";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Menu;
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Location = System::Drawing::Point(803, 24);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(358, 451);
			this->panel1->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 100);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(197, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Extentions (divided by commas)";
			// 
			// name
			// 
			this->name->HeaderText = L"Name";
			this->name->MinimumWidth = 8;
			this->name->Name = L"name";
			this->name->ReadOnly = true;
			this->name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->name->Width = 150;
			// 
			// size
			// 
			this->size->HeaderText = L"Size";
			this->size->MinimumWidth = 8;
			this->size->Name = L"size";
			this->size->ReadOnly = true;
			this->size->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->size->Width = 150;
			// 
			// date
			// 
			this->date->HeaderText = L"Creation date";
			this->date->MinimumWidth = 8;
			this->date->Name = L"date";
			this->date->ReadOnly = true;
			this->date->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->date->Width = 150;
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SlateGray;
			this->ClientSize = System::Drawing::Size(1173, 731);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->fileTable);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ClientForm";
			this->Text = L"c";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileTable))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}
