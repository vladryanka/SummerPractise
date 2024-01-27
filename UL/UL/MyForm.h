#pragma once
#include <Windows.h>
#include <math.h>
#include <cmath>

namespace SecondBlock {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//основные параметры
	int a;
	double Step = 0.1; //для траектории
	int minB; int maxB; //пульсирование 10..100
	int ab; int bc; int angA; // параметры параллелограмма 30, 50, 30
	int speed; //скорость движения параллелограмма
	double Step1; //шаг изменения угла параллелограмма 30
	int stepP; // количество пульсирвоаний за проход 20
	int k; //число повторов прохождения параллелограмма
	int stepM; //шаг перемещения параллелограмма

	double thickTraj;
	double thickParal;
	bool pulse = 0;
	bool direction = 0;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;

	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Label^ label15;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;

	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::ComboBox^ comboBox4;
	private: System::Windows::Forms::ComboBox^ comboBox5;
	private: System::Windows::Forms::ComboBox^ comboBox6;
	private: System::Windows::Forms::ComboBox^ comboBox7;
	private: System::Windows::Forms::PictureBox^ pictureBox3;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

	private: void Paint_Paral(int x, int y, int height, int width, double ang, int a, int ab, int bc, int angA, Pen^ colorParal, Brush^ cP) {
		Graphics^ Графика1 = pictureBox1->CreateGraphics();
		Графика1->TranslateTransform(width / 2 + x, height / 2 + y);
		Графика1->RotateTransform(ang);

		array<Point>^ paral;
		paral = gcnew array<Point>(4); // точки для прорисовки

		paral[0] = Point((int)(-(bc - ab * cos(angA) / 2)), (int)(-(ab * sin(angA)) / 2));
		paral[1] = Point((int)((bc
			+ ab * cos(angA) / 2)), (int)(-(ab * sin(angA)) / 2));
		paral[2] = Point((int)((bc - ab * cos(angA) / 2)), (int)((ab * sin(angA)) / 2));
		paral[3] = Point((int)(-(bc + ab * cos(angA) / 2)), (int)((ab * sin(angA)) / 2));
		Графика1->DrawPolygon(colorParal, paral);
		Графика1->FillPolygon(cP, paral);
	}

	private: void Paint(Pen^ colorTraj, Pen^ colorParal, SolidBrush^ cP) {

		double InitT = 0, LastT = 6.3; // оборот в 360 градусов (6,28 радиан)
		double angle = InitT;

		int width = pictureBox1->Width; //размеры pictureBox
		int height = pictureBox1->Height;

		//расчитаем начало координат
		int x0 = 0;
		int y0 = 0;

		Graphics^ Графика = pictureBox1->CreateGraphics();
		Графика->TranslateTransform(width / 2, height / 2);

		array<Point>^ p;
		p = gcnew array<Point>(LastT / Step + 2); // точки для прорисовки
		double x, y, x1, y1;
		int i = 0; //index

		while (abs(angle) <= LastT) // просто график
		{
			Графика->Clear(BackColor);

			x = 2 * a * cos(angle) - a * cos(2 * angle);
			y = 2 * a * sin(angle) - a * sin(2 * angle);

			p[i] = Drawing::Point(x0 + int(x), y0 + int(y)); // расчет очередной точки траектории
			//рисуем оси
			Графика->DrawLine(Pens::Black, 0, -height, 0, height); //y
			Графика->DrawLine(Pens::Black, width, 0, -width, 0); // x
			Графика->DrawEllipse(Pens::Black, -a, -a, a * 2, a * 2); //статичная окружность
			Графика->DrawLines(colorTraj, p); // траектория

			//расчёт центра движущейся окружности
			x1 = 2 * a * cos(angle) - a;
			y1 = 2 * a * sin(angle) - a;

			Графика->DrawEllipse(Pens::Black, int(x1), int(y1), a * 2, a * 2);
			Графика->DrawLine(Pens::Black, int(x1) + a, int(y1) + a, int(x), int(y));

			angle += Step;
			::Sleep(40); //время приостановки прорисовки
			i++;
		}

		double ang = 0;

		if (direction == 0) { // прямое движение
			for (int j = 0; j < k * LastT / Step; j += stepM) {
				Графика->Clear(BackColor);
				Графика->DrawPolygon(colorTraj, p);
				Графика->DrawEllipse(Pens::Black, -a, -a, a * 2, a * 2); //статичная окружность
				Графика->DrawEllipse(Pens::Black, a, -a, a * 2, a * 2);
				Графика->DrawLine(Pens::Black, 0, -height, 0, height); //y
				Графика->DrawLine(Pens::Black, width, 0, -width, 0); // x

				ang += Step1;
				if (ang >= 360) ang = 0;

				Paint_Paral(p[j % p->Length].X, p[j % p->Length].Y, height, width, ang, a, ab, bc, angA, colorParal, cP);

				::Sleep(speed); //время приостановки прорисовки
			}

			if (pulse == 1) {
				int minA = ab / bc * minB; int maxA = ab / bc * maxB;

				double stepPB = (maxB - minB) / (stepP - 1);
				double stepPA = (maxA - minA) / (stepP - 1);

				int cntP = 0;

				for (int j = 0; j < k * LastT / Step; j += stepM) {
					if (p[j % p->Length].X != 0 && p[j % p->Length].Y != 0) {
						if (cntP < stepP / 2) {
							minB += stepPA;
							minA += stepPB;
							ab = minA;
							bc = minB;
							cntP++;
						}
						if (cntP >= stepP / 2 && cntP < stepP) {
							minB -= stepPA;
							minA -= stepPB;
							ab = minA;
							bc = minB;
							cntP++;
						}
						if (cntP == stepP) {
							cntP = 1;
							minB += stepPA;
							minA += stepPB;
							ab = minA;
							bc = minB;
						}

						Графика->Clear(BackColor);
						Графика->DrawPolygon(colorTraj, p);
						Графика->DrawEllipse(Pens::Black, -a, -a, a * 2, a * 2); //статичная окружность
						Графика->DrawEllipse(Pens::Black, a, -a, a * 2, a * 2);
						Графика->DrawLine(Pens::Black, 0, -height, 0, height); //y
						Графика->DrawLine(Pens::Black, width, 0, -width, 0); // x

						ang += Step1;
						if (ang >= 360) ang = 0;

						Paint_Paral(p[j % p->Length].X, p[j % p->Length].Y, height, width, ang, a, ab, bc, angA, colorParal, cP);

						::Sleep(60); //время приостановки прорисовки
					}
				}
			}
		}
		else { // обратное движение
			for (int j = k * LastT / Step; j > 0; j -= stepM) { 
				Графика->Clear(BackColor);
				Графика->DrawPolygon(colorTraj, p);
				Графика->DrawEllipse(Pens::Black, -a, -a, a * 2, a * 2); //статичная окружность
				Графика->DrawEllipse(Pens::Black, a, -a, a * 2, a * 2);
				Графика->DrawLine(Pens::Black, 0, -height, 0, height); //y
				Графика->DrawLine(Pens::Black, width, 0, -width, 0); // x

				ang += Step1;
				if (ang >= 360) ang = 0;

				Paint_Paral(p[j % p->Length].X, p[j % p->Length].Y, height, width, ang, a, ab, bc, angA, colorParal, cP);

				::Sleep(speed); //время приостановки прорисовки
			}

			if (pulse == 1) { // пульсирование
				int minA = ab / bc * minB; int maxA = ab / bc * maxB;

				double stepPB = (maxB - minB) /
					(stepP - 1);
				double stepPA = (maxA - minA) / (stepP - 1);

				int cntP = 0;

				for (int j = k * LastT / Step; j > 0; j -= stepM) {
					if (p[j % p->Length].X != 0 && p[j % p->Length].Y != 0) {
						if (cntP < stepP / 2) {
							minB += stepPA;
							minA += stepPB;
							ab = minA;
							bc = minB;
							cntP++;
						}
						if (cntP >= stepP / 2 && cntP < stepP) {
							minB -= stepPA;
							minA -= stepPB;
							ab = minA;
							bc = minB;
							cntP++;
						}
						if (cntP == stepP) {
							cntP = 1;
							minB += stepPA;
							minA += stepPB;
							ab = minA;
							bc = minB;
						}

						Графика->Clear(BackColor);
						Графика->DrawPolygon(colorTraj, p);
						Графика->DrawEllipse(Pens::Black, -a, -a, a * 2, a * 2); //статичная окружность
						Графика->DrawEllipse(Pens::Black, a, -a, a * 2, a * 2);
						Графика->DrawLine(Pens::Black, 0, -height, 0, height); //y
						Графика->DrawLine(Pens::Black, width, 0, -width, 0); // x

						ang += Step1;
						if (ang >= 360) ang = 0;

						Paint_Paral(p[j % p->Length].X, p[j % p->Length].Y, height, width, ang, a, ab, bc, angA, colorParal, cP);

						::Sleep(60); //время приостановки прорисовки
					}
				}
			}
		}

	}

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Требуемый метод для поддержки конструктора — не изменяйте
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->label10 = (gcnew System::Windows::Forms::Label());
			   this->label11 = (gcnew System::Windows::Forms::Label());
			   this->label12 = (gcnew System::Windows::Forms::Label());
			   this->label13 = (gcnew System::Windows::Forms::Label());
			   this->label15 = (gcnew System::Windows::Forms::Label());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			   this->label17 = (gcnew System::Windows::Forms::Label());
			   this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			   this->label18 = (gcnew System::Windows::Forms::Label());
			   this->label19 = (gcnew System::Windows::Forms::Label());
			   this->label20 = (gcnew System::Windows::Forms::Label());
			   this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			   this->label14 = (gcnew System::Windows::Forms::Label());
			   this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			   this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			   this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			   this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			   this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			   this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			   this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			   this->SuspendLayout();
			   //
			   // pictureBox1
			   //
			   this->pictureBox1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			   this->pictureBox1->Location = System::Drawing::Point(24, 29);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(460, 583);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   //
			   // button1
			   //
			   this->button1->Location = System::Drawing::Point(756, 428);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(112, 39);
			   this->button1->TabIndex = 5;
			   this->button1->Text = L"button1";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			   //
			   // label1
			   //
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(544, 29);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(51, 20);
			   this->label1->TabIndex = 6;
			   this->label1->Text = L"label1";
			   //
			   // label2
			   //
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(678, 29);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(51, 20);
			   this->label2->TabIndex = 7;
			   this->label2->Text = L"label2";
			   //
			   // label3
			   //
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(898, 29);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(51, 20);
			   this->label3->TabIndex = 8;
			   this->label3->Text = L"label3";
			   //
			   // label4
			   //
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(546, 84);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(51, 20);
			   this->label4->TabIndex = 9;
			   this->label4->Text = L"label4";
			   //
			   // label5
			   //
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(680, 84);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(51, 20);
			   this->label5->TabIndex = 10;
			   this->label5->Text = L"label5";
			   //
			   // label6
			   //
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(900, 84);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(51, 20);
			   this->label6->TabIndex = 11;
			   this->label6->Text = L"label6";
			   //
			   // label7
			   //
			   this->label7->AutoSize = true;
			   this->label7->Location = System::Drawing::Point(1073, 84);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(51, 20);
			   this->label7->TabIndex = 12;
			   this->label7->Text = L"label7";
			   //
			   // label8
			   //
			   this->label8->AutoSize = true;
			   this->label8->Location = System::Drawing::Point(544, 142);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(51, 20);
			   this->label8->TabIndex = 13;
			   this->label8->Text = L"label8";
			   //
			   // label9
			   //
			   this->label9->AutoSize = true;
			   this->label9->Location = System::Drawing::Point(789, 142);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(51, 20);
			   this->label9->TabIndex = 14;
			   this->label9->Text = L"label9";
			   //
			   // label10
			   //
			   this->label10->AutoSize = true;
			   this->label10->Location = System::Drawing::Point(1038, 142);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(60, 20);
			   this->label10->TabIndex = 15;
			   this->label10->Text = L"label10";
			   //
			   // label11
			   //
			   this->label11->AutoSize = true;
			   this->label11->Location = System::Drawing::Point(789, 265);
			   this->label11->Name = L"label11";
			   this->label11->Size = System::Drawing::Size(60, 20);
			   this->label11->TabIndex = 16;
			   this->label11->Text = L"label11";
			   //
			   // label12
			   //
			   this->label12->AutoSize = true;
			   this->label12->Location = System::Drawing::Point(544, 203);
			   this->label12->Name = L"label12";
			   this->label12->Size = System::Drawing::Size(60, 20);
			   this->label12->TabIndex = 17;
			   this->label12->Text = L"label12";
			   //
			   // label13
			   //
			   this->label13->AutoSize = true;
			   this->label13->Location = System::Drawing::Point(789, 203);
			   this->label13->Name = L"label13";
			   this->label13->Size = System::Drawing::Size(60, 20);
			   this->label13->TabIndex = 18;
			   this->label13->Text = L"label13";
			   //
			   // label15
			   //
			   this->label15->AutoSize = true;
			   this->label15->Location = System::Drawing::Point(544, 265);
			   this->label15->Name = L"label15";
			   this->label15->Size = System::Drawing::Size(60, 20);
			   this->label15->TabIndex = 20;
			   this->label15->Text = L"label15";
			   //
			   // textBox1
			   //
			   this->textBox1->Location = System::Drawing::Point(548, 166);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(190, 26);
			   this->textBox1->TabIndex = 22;
			   //
			   // textBox2
			   //
			   this->textBox2->Location = System::Drawing::Point(793, 166);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(209, 26);
			   this->textBox2->TabIndex = 23;
			   //
			   // textBox3
			   //
			   this->textBox3->Location = System::Drawing::Point(1042, 165);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(165, 26);
			   this->textBox3->TabIndex = 24;
			   //
			   // textBox4
			   //
			   this->textBox4->Location = System::Drawing::Point(793, 383);
			   this->textBox4->Name = L"textBox4";
			   this->textBox4->Size = System::Drawing::Size(166, 26);
			   this->textBox4->TabIndex = 25;
			   //
			   // textBox5
			   //
			   this->textBox5->Location = System::Drawing::Point(793, 226);
			   this->textBox5->Name = L"textBox5";
			   this->textBox5->Size = System::Drawing::Size(209, 26);
			   this->textBox5->TabIndex = 26;
			   //
			   // textBox7
			   //
			   this->textBox7->Location = System::Drawing::Point(548, 304);
			   this->textBox7->Name = L"textBox7";
			   this->textBox7->Size = System::Drawing::Size(56, 26);
			   this->textBox7->TabIndex = 28;
			   //
			   // textBox8
			   //
			   this->textBox8->Location = System::Drawing::Point(682, 303);
			   this->textBox8->Name = L"textBox8";
			   this->textBox8->Size = System::Drawing::Size(64, 26);
			   this->textBox8->TabIndex = 29;
			   //
			   // label17
			   //
			   this->label17->AutoSize = true;
			   this->label17->Location = System::Drawing::Point(544, 345);
			   this->label17->Name = L"label17";
			   this->label17->Size = System::Drawing::Size(60, 20);
			   this->label17->TabIndex = 30;
			   this->label17->Text = L"label20";
			   //
			   // textBox9
			   //
			   this->textBox9->Location = System::Drawing::Point(548, 383);
			   this->textBox9->Name = L"textBox9";
			   this->textBox9->Size = System::Drawing::Size(181, 26);
			   this->textBox9->TabIndex = 31;
			   //
			   // label18
			   //
			   this->label18->AutoSize = true;
			   this->label18->Location = System::Drawing::Point(789, 345);
			   this->label18->Name = L"label18";
			   this->label18->Size = System::Drawing::Size(60, 20);
			   this->label18->TabIndex = 32;
			   this->label18->Text = L"label17";
			   //
			   // label19
			   //
			   this->label19->AutoSize = true;
			   this->label19->Location = System::Drawing::Point(1038, 345);
			   this->label19->Name = L"label19";
			   this->label19->Size = System::Drawing::Size(60, 20);
			   this->label19->TabIndex = 33;
			   this->label19->Text = L"label18";
			   //
			   // label20
			   //
			   this->label20->AutoSize = true;
			   this->label20->Location = System::Drawing::Point(1038, 265);
			   this->label20->Name = L"label20";
			   this->label20->Size = System::Drawing::Size(60, 20);
			   this->label20->TabIndex = 34;
			   this->label20->Text = L"label19";
			   //
			   // textBox6
			   //
			   this->textBox6->Location = System::Drawing::Point(1042, 303);
			   this->textBox6->Name = L"textBox6";
			   this->textBox6->Size = System::Drawing::Size(100, 26);
			   this->textBox6->TabIndex = 35;
			   //
			   // textBox10
			   //
			   this->textBox10->Location = System::Drawing::Point(1042, 383);
			   this->textBox10->Name = L"textBox10";
			   this->textBox10->Size = System::Drawing::Size(100, 26);
			   this->textBox10->TabIndex = 36;
			   //
			   // label14
			   //
			   this->label14->AutoSize = true;
			   this->label14->Location = System::Drawing::Point(1042, 202);
			   this->label14->Name = L"label14";
			   this->label14->Size = System::Drawing::Size(60, 20);
			   this->label14->TabIndex = 37;
			   this->label14->Text = L"label14";
			   //
			   // textBox11
			   //
				this->textBox11->Location = System::Drawing::Point(1046, 225);
			   this->textBox11->Name = L"textBox11";
			   this->textBox11->Size = System::Drawing::Size(161, 26);
			   this->textBox11->TabIndex = 38;
			   //
			   // comboBox1
			   //
			   this->comboBox1->FormattingEnabled = true;
			   this->comboBox1->Location = System::Drawing::Point(548, 53);
			   this->comboBox1->Name = L"comboBox1";
			   this->comboBox1->Size = System::Drawing::Size(121, 28);
			   this->comboBox1->TabIndex = 39;
			   //
			   // textBox12
			   //
			   this->textBox12->Location = System::Drawing::Point(682, 54);
			   this->textBox12->Name = L"textBox12";
			   this->textBox12->Size = System::Drawing::Size(100, 26);
			   this->textBox12->TabIndex = 40;
			   //
			   // comboBox2
			   //
			   this->comboBox2->FormattingEnabled = true;
			   this->comboBox2->Location = System::Drawing::Point(550, 108);
			   this->comboBox2->Name = L"comboBox2";
			   this->comboBox2->Size = System::Drawing::Size(121, 28);
			   this->comboBox2->TabIndex = 41;
			   //
			   // textBox13
			   //
			   this->textBox13->Location = System::Drawing::Point(684, 109);
			   this->textBox13->Name = L"textBox13";
			   this->textBox13->Size = System::Drawing::Size(100, 26);
			   this->textBox13->TabIndex = 42;
			   //
			   // comboBox3
			   //
			   this->comboBox3->FormattingEnabled = true;
			   this->comboBox3->Location = System::Drawing::Point(1077, 107);
			   this->comboBox3->Name = L"comboBox3";
			   this->comboBox3->Size = System::Drawing::Size(121, 28);
			   this->comboBox3->TabIndex = 43;
			   //
			   // comboBox4
			   //
			   this->comboBox4->FormattingEnabled = true;
			   this->comboBox4->Location = System::Drawing::Point(902, 52);
			   this->comboBox4->Name = L"comboBox4";
			   this->comboBox4->Size = System::Drawing::Size(121, 28);
			   this->comboBox4->TabIndex = 44;
			   //
			   // comboBox5
			   //
			   this->comboBox5->FormattingEnabled = true;
			   this->comboBox5->Location = System::Drawing::Point(904, 107);
			   this->comboBox5->Name = L"comboBox5";
			   this->comboBox5->Size = System::Drawing::Size(121, 28);
			   this->comboBox5->TabIndex = 45;
			   //
			   // comboBox6
			   //
			   this->comboBox6->FormattingEnabled = true;
			   this->comboBox6->Location = System::Drawing::Point(548, 226);
			   this->comboBox6->Name = L"comboBox6";
			   this->comboBox6->Size = System::Drawing::Size(121, 28);
			   this->comboBox6->TabIndex = 46;
			   //
			   // comboBox7
			   //
			   this->comboBox7->FormattingEnabled = true;
			   this->comboBox7->Location = System::Drawing::Point(793, 303);
			   this->comboBox7->Name = L"comboBox7";
			   this->comboBox7->Size = System::Drawing::Size(121, 28);
			   this->comboBox7->TabIndex = 47;
			   //
			   // pictureBox3
			   //
			   this->pictureBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->pictureBox3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.BackgroundImage")));
			   this->pictureBox3->Location = System::Drawing::Point(957, 428);
			   this->pictureBox3->Name = L"pictureBox3";
			   this->pictureBox3->Size = System::Drawing::Size(250, 238);
			   this->pictureBox3->TabIndex = 48;
			   this->pictureBox3->TabStop = false;
			   //
			   // MyForm
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1444, 678);
			   this->Controls->Add(this->pictureBox3);
			   this->Controls->Add(this->comboBox7);
			   this->Controls->Add(this->comboBox6);
			   this->Controls->Add(this->comboBox5);
			   this->Controls->Add(this->comboBox4);
			   this->Controls->Add(this->comboBox3);
			   this->Controls->Add(this->textBox13);
			   this->Controls->Add(this->comboBox2);
			   this->Controls->Add(this->textBox12);
			   this->Controls->Add(this->comboBox1);
			   this->Controls->Add(this->textBox11);
			   this->Controls->Add(this->label14);
			   this->Controls->Add(this->textBox10);
			   this->Controls->Add(this->textBox6);
			   this->Controls->Add(this->label20);
			   this->Controls->Add(this->label19);
			   this->Controls->Add(this->label18);
			   this->Controls -> Add(this->textBox9);
			   this->Controls->Add(this->label17);
			   this->Controls->Add(this->textBox8);
			   this->Controls->Add(this->textBox7);
			   this->Controls->Add(this->textBox5);
			   this->Controls->Add(this->textBox4);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label15);
			   this->Controls->Add(this->label13);
			   this->Controls->Add(this->label12);
			   this->Controls->Add(this->label11);
			   this->Controls->Add(this->label10);
			   this->Controls->Add(this->label9);
			   this->Controls->Add(this->label8);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->pictureBox1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->Text = "Кардиоида";
		label1->Text = "Цвет траектории";
		label2->Text = "Толщина линии траектории";
		label3->Text = "Вид линии траектории";

		label4->Text = "Цвет объекта";
		label5->Text = "Толщина линии объекта";
		label6->Text = "Вид линии объекта";
		label7->Text = "Цвет заливки объекта";

		label8->Text = "Скорость движения объекта";
		label9->Text = "Число пульсирований за раз";
		label10->Text = "Шаг перемещения объекта";
		label11->Text = "Направление движения";

		label12->Text = "Пульсирование";
		label13->Text = "Шаг изменения угла";
		label14->Text = "Число проходов";

		label15->Text = "Интервал пульсирования";
		label17->Text = "1 сторона параллелограмма";
		label18->Text = "2 сторона параллелограмма";
		label19->Text = "Угол параллелограмма";
		label20->Text = "Радиус";

		array<System::String^>^ ColorsTraj = gcnew array<System::String^>{"Red", "Green", "Black", "Blue", "Yellow"};
		comboBox1->Items->AddRange(ColorsTraj);

		array<System::String^>^ ColorsParal = gcnew array<System::String^>{"Red", "Green", "Black", "Blue", "Yellow"};
		comboBox2->Items->AddRange(ColorsParal);

		array<System::String^>^ csP = gcnew array<System::String^>{"Red", "Green", "Black", "Blue", "Yellow"};
		comboBox3->Items->AddRange(ColorsParal);

		array<System::String^>^ dashTraj = gcnew array<System::String^>{"Solid", "Dash", "Dot", "DashDot", "DashDotDot"};
		comboBox4->Items->AddRange(dashTraj);

		array<System::String^>^ dashParal = gcnew array<System::String^>{"Solid", "Dash", "Dot", "DashDot", "DashDotDot"};
		comboBox5->Items->AddRange(dashParal);

		array<System::String^>^ Pulse = gcnew array<System::String^>{"No", "Yes"};
		comboBox6->Items->AddRange(Pulse);

		array<System::String^>^ Direction = gcnew array<System::String^>{"Прямое", "Обратное"};
		comboBox7->Items->AddRange(Direction);

		button1->Text = "Рисовать";

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		speed = Convert::ToInt32(textBox1->Text);
		stepM = Convert::ToInt32(textBox3->Text);
		bc = Convert::ToInt32(textBox4->Text);
		Step1 = Convert::ToDouble(textBox5->Text);
		a = Convert::ToInt32(textBox6->Text);
		ab = Convert::ToInt32(textBox9->Text);
		angA = Convert::ToInt32(textBox10->Text);
		k = Convert::ToInt32(textBox11->Text);
		thickTraj = Convert::ToDouble(textBox12->Text);
		thickParal = Convert::ToDouble(textBox13->Text);

		Pen^ colorTraj;
		Pen^ colorParal;

		switch (comboBox1->SelectedIndex)
		{
		case 0:
			colorTraj = gcnew Pen(Color::Red, thickTraj); break;
		case 1:
			colorTraj = gcnew Pen(Color::Green, thickTraj); break;
		case 2:
			colorTraj = gcnew Pen(Color::Black, thickTraj); break;
		case 3:
			colorTraj = gcnew Pen(Color::Blue, thickTraj); break;
			case
			4:
				colorTraj = gcnew Pen(Color::Yellow, thickTraj); break;
		}

		switch (comboBox2->SelectedIndex)
		{
		case 0:
			colorParal = gcnew Pen(Color::Red, thickParal); break;
		case 1:
			colorParal = gcnew Pen(Color::Green, thickParal); break;
		case 2:
			colorParal = gcnew Pen(Color::Black, thickParal); break;
		case 3:
			colorParal = gcnew Pen(Color::Blue, thickParal); break;
		case 4:
			colorParal = gcnew Pen(Color::Yellow, thickParal); break;
		}

		switch (comboBox4->SelectedIndex)
		{
		case 0:
			colorTraj->DashStyle = System::Drawing::Drawing2D::DashStyle::Solid; break;
		case 1:
			colorTraj->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash; break;
		case 2:
			colorTraj->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot; break;
		case 3:
			colorTraj->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDot; break;
		case 4:
			colorTraj->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDotDot; break;
		}

		switch (comboBox5->SelectedIndex)
		{
		case 0:
			colorParal->DashStyle = System::Drawing::Drawing2D::DashStyle::Solid; break;
		case 1:
			colorParal->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash; break;
		case 2:
			colorParal->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot; break;
		case 3:
			colorParal->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDot; break;
		case 4:
			colorParal->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDotDot; break;
		}

		switch (comboBox6->SelectedIndex)
		{
		case 0:
			pulse = 0; break;
		case 1:
			pulse = 1;
			stepP = Convert::ToInt32(textBox2->Text);
			minB = Convert::ToInt32(textBox7->Text);
			maxB = Convert::ToInt32(textBox8->Text);
			break;
		}

		switch (comboBox7->SelectedIndex)
		{
		case 0:
			direction = 0; break;
		case 1:
			direction = 1; break;
		}

		SolidBrush^ cP;

		switch (comboBox3->SelectedIndex)
		{
		case 0:
			cP = gcnew SolidBrush(Color::Red); break;
		case 1:
			cP = gcnew SolidBrush(Color::Green); break;
		case 2:
			cP = gcnew SolidBrush(Color::Black); break;
		case 3:
			cP = gcnew SolidBrush(Color::Blue); break;
		case 4:
			cP = gcnew SolidBrush(Color::Yellow); break;
		}

		Paint(colorTraj, colorParal, cP);

	}
	};
}
