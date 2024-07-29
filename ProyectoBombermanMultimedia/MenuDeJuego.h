#pragma once
#include "Juego.h"
#include <Windows.h>

namespace ProyectoBombermanMultimedia {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Resumen de MenuDeJuego
	/// </summary>
	public ref class MenuDeJuego : public System::Windows::Forms::Form
	{
	public:
		MenuDeJuego(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MenuDeJuego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ ControlesIn;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;



	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		Juego^ juego;
		SoundPlayer^ Musica;
		bool reinicio = false;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
		   /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MenuDeJuego::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->ControlesIn = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(658, 333);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MenuDeJuego::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(248, 351);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(158, 35);
			this->button1->TabIndex = 1;
			this->button1->Text = L"¡Jugar!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MenuDeJuego::button1_Click);
			// 
			// ControlesIn
			// 
			this->ControlesIn->Location = System::Drawing::Point(282, 404);
			this->ControlesIn->Name = L"ControlesIn";
			this->ControlesIn->Size = System::Drawing::Size(90, 25);
			this->ControlesIn->TabIndex = 2;
			this->ControlesIn->Text = L"Controles";
			this->ControlesIn->UseVisualStyleBackColor = true;
			this->ControlesIn->Click += gcnew System::EventHandler(this, &MenuDeJuego::button2_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(1001, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(170, 101);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(677, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(318, 32);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Muevete con las teclas: ";
			this->label1->Click += gcnew System::EventHandler(this, &MenuDeJuego::label1_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(1001, 144);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(170, 77);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(729, 165);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(242, 32);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Pon bombas con: ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(705, 249);
			this->label3->MaximumSize = System::Drawing::Size(450, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(442, 152);
			this->label3->TabIndex = 7;
			this->label3->Text = L"¡Rompe los bloques de ladrillo, encuentra mejoras, y derrota a los enemigos para "
				L"avanzar de nivel!";
			this->label3->Click += gcnew System::EventHandler(this, &MenuDeJuego::label3_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 75;
			this->timer1->Tick += gcnew System::EventHandler(this, &MenuDeJuego::timer1_Tick_1);
			// 
			// MenuDeJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(685, 453);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->ControlesIn);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MenuDeJuego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MenuDeJuego";
			this->Load += gcnew System::EventHandler(this, &MenuDeJuego::On_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void TemaMenu() {
			Musica = gcnew SoundPlayer("Audio\\MenuPrincipal.wav");
			Musica->PlayLooping();
		}

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		reinicio = false;
		juego = gcnew Juego();
		this->Visible = false;
		timer1->Enabled = true;
		juego->Show();
		Musica->Stop();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->Width == 900)
			this->Width = 525;
		else
			this->Width = 900;
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
}

	   private: System::Void Timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		   if (juego->getSistema()->getBomberman()->getVidas() == 0 && reinicio == false) {
			   juego->stopMusica();
			   juego->cargarGameOver();
			   Sleep(4500);
			   this->Visible = true;
			   TemaMenu();
			   delete juego;
			   reinicio = true;
		   }
	   }
	  
 private: System::Void On_Load(System::Object^ sender, System::EventArgs^ e) {
	 timer1->Enabled = false;
	 TemaMenu();
	 srand(time(NULL));
	   }

private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}



//Trata los game over
private: System::Void timer1_Tick_1(System::Object^ sender, System::EventArgs^ e) {
	if (juego->getSistema()->getBomberman()->getVidas() == 0 && reinicio == false) {
		juego->stopMusica();
		juego->cargarGameOver();
		Sleep(4500);
		this->Visible = true;
		TemaMenu();
		delete juego;
		reinicio = true;
	}
}
};
}
