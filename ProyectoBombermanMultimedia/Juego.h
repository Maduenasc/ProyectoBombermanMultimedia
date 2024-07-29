#pragma once
#include "Sistema.h"

namespace ProyectoBombermanMultimedia {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	public:

		Juego(void)
		{
			InitializeComponent();
			sistema = new Sistema();
			//
			//TODO: agregar código de constructor aquí
			//
			bomberman->MakeTransparent(bomberman->GetPixel(0, 0));
			bomba->MakeTransparent(bomba->GetPixel(0, 0));
			explosion->MakeTransparent(explosion->GetPixel(0, 0));
			monstruos->MakeTransparent(monstruos->GetPixel(0, 0));
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		Sistema* sistema;
		Bitmap^ solido = gcnew Bitmap("Imagenes\\solido.png");
		Bitmap^ hueco = gcnew Bitmap("Imagenes\\hueco.png");
		Bitmap^ destruible = gcnew Bitmap("Imagenes\\destruible.png");
		Bitmap^ bomberman = gcnew Bitmap("Imagenes\\bomber.png");
		Bitmap^ bomba = gcnew Bitmap("Imagenes\\bomba.png");
		Bitmap^ powerups = gcnew Bitmap("Imagenes\\powerups.png");
		Bitmap^ explosion = gcnew Bitmap("Imagenes\\explosion.png");
		Bitmap^ monstruos = gcnew Bitmap("Imagenes\\monstruo.png");
		SoundPlayer^ temaNivel;




	private: System::Windows::Forms::Timer^ timerCarga;

		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerCarga = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// timerCarga
			// 
			this->timerCarga->Enabled = true;
			this->timerCarga->Tick += gcnew System::EventHandler(this, &Juego::timer2_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Desktop;
			this->ClientSize = System::Drawing::Size(850, 743);
			this->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->Name = L"Juego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Juego";
			this->Load += gcnew System::EventHandler(this, &Juego::On_load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Pulsar);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Soltar);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ mapa = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = mapa->Allocate(g, this->ClientRectangle);
		sistema->dibujarJuego(buffer->Graphics, hueco, solido, destruible, bomberman, bomba, explosion, powerups, monstruos);
		buffer->Render(g);
		if (sistema->getMonstruos()->getVector().size() == 0) {
			g->Clear(System::Drawing::Color::Black);
			stopMusica();
			pasaNivel();
		}
		delete buffer, mapa, g;
	}

	private: System::Void On_load(System::Object^ sender, System::EventArgs^ e) {
		sistema->crearNivel();
	}
	void pasaNivel() {
		timer1->Enabled = false;
		timerCarga->Enabled = true;
		sistema->avanzaNivel();
		sistema->crearNivel();
		sistema->getPowerups()->getVector()->clear();
	}
	private: System::Void Pulsar(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Down:
			sistema->getBomberman()->setDirecciones(Aba);
			break;

		case Keys::Left:
			sistema->getBomberman()->setDirecciones(Izq);
			break;

		case Keys::Right:
			sistema->getBomberman()->setDirecciones(Der);
			break;

		case Keys::Up:
			sistema->getBomberman()->setDirecciones(Arr);
			break;
		}
	}
	private: System::Void Soltar(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Space:
			sistema->aniadeBomba();
			break;

		default:
			sistema->getBomberman()->setDirecciones(No);
			break;
		}
	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void flowLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
	   public: Sistema* getSistema() { 
		   return sistema; 
	   }
	   void stopMusica() { 
			 temaNivel->Stop(); 
	   }

	   void musica() {
		   temaNivel = gcnew SoundPlayer("audio\\TemaNivel.wav");
		   temaNivel->PlayLooping();
	   }
private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
	while (sistema->getPowerups()->getVector()->size() < sistema->getNivelActual()) {
		sistema->generaPowerupsYEnemigos();
	}
	timerCarga->Enabled = false;
	timer1->Enabled = true;
	musica();

}

public: void cargarGameOver() {
	SoundPlayer^ music = gcnew SoundPlayer("audio\\GameOver.wav");
	music->Play();
	timer1->Enabled = false;
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
