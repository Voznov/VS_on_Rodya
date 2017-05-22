#pragma once

#include "Wheel.h"
#define _USE_MATH_DEFINES
#include <cmath>

const float centerX = 200, centerY = 200, radiusFirst = 90, radiusSecond = 50, fps = 50, speed = 1;

namespace Wheels {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			// timer
			timer = gcnew Timers::Timer();
			timer->Interval = 1000 / fps;
			timer->Elapsed += gcnew Timers::ElapsedEventHandler(this, &MainForm::timerEvent);
			timer->Enabled = false;
			// g
			g = pictureBox1->CreateGraphics();
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
				delete g;
				delete timer;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		Wheel mainWheel, secondWheel;
		float angleWheels;
		Timers::Timer^ timer;
	private: System::Windows::Forms::Button^  startButton;
	private: System::Windows::Forms::Button^  pauseButton;
	private: System::Windows::Forms::Button^  stopButton;
	private: System::Windows::Forms::Button^  exitButton;




			 Graphics^ g;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->exitButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(473, 473);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// startButton
			// 
			this->startButton->Location = System::Drawing::Point(492, 13);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(75, 46);
			this->startButton->TabIndex = 1;
			this->startButton->Text = L"Старт";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->Enabled = false;
			this->pauseButton->Location = System::Drawing::Point(492, 65);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(75, 46);
			this->pauseButton->TabIndex = 2;
			this->pauseButton->Text = L"Пауза";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Enabled = false;
			this->stopButton->Location = System::Drawing::Point(492, 117);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(75, 46);
			this->stopButton->TabIndex = 3;
			this->stopButton->Text = L"Стоп";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
			// 
			// exitButton
			// 
			this->exitButton->Location = System::Drawing::Point(492, 169);
			this->exitButton->Name = L"exitButton";
			this->exitButton->Size = System::Drawing::Size(75, 46);
			this->exitButton->TabIndex = 4;
			this->exitButton->Text = L"Выход";
			this->exitButton->UseVisualStyleBackColor = true;
			this->exitButton->Click += gcnew System::EventHandler(this, &MainForm::exitButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(577, 497);
			this->Controls->Add(this->exitButton);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->startButton);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void timerEvent(Object^ source, System::Timers::ElapsedEventArgs^ e)
		{
			g->Clear(pictureBox1->BackColor);
			mainWheel.Angle((float)-1 * speed / fps);
			secondWheel.Angle((float)2 * speed / fps);
			angleWheels += M_PI / 100;
			if (angleWheels > 2 * M_PI)
				angleWheels -= 2 * M_PI;
			secondWheel.MoveTo(centerX + (radiusFirst + radiusSecond) * sinf(angleWheels), centerY + (radiusFirst + radiusSecond) * cosf(angleWheels));
			mainWheel.Draw();
			secondWheel.Draw();
		}
		System::Void startButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			startButton->Enabled = false;
			pauseButton->Enabled = true;
			stopButton->Enabled = true;

			g->Clear(pictureBox1->BackColor);
			angleWheels = 0;
			mainWheel.Set(centerX, centerY, radiusFirst, 3, Color::ForestGreen, g);
			mainWheel.Draw();
			secondWheel.Set(centerX, centerY + (radiusFirst + radiusSecond), radiusSecond, 3, Color::Red, g);
			secondWheel.Draw();
			timer->Enabled = true;
		}
		System::Void exitButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			this->Close();
		}
		System::Void pauseButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if (timer->Enabled)
			{
				startButton->Enabled = false;
				pauseButton->Enabled = true;
				stopButton->Enabled = false;

				timer->Enabled = false;
			}
			else
			{
				startButton->Enabled = false;
				pauseButton->Enabled = true;
				stopButton->Enabled = true;

				timer->Enabled = true;
			}
		}
		System::Void stopButton_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			startButton->Enabled = true;
			pauseButton->Enabled = false;
			stopButton->Enabled = false;

			timer->Enabled = false;

		}
	};
}