#pragma once
#include "graph.h"
#include "LinearRegression.h"
#include "OptimalPath.h"


namespace ClassicProblemInterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Panel^  panel1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: void Draw(int acceptedError, System::Drawing::Graphics^  g)
	{

		Pen^ blackPen = gcnew Pen(Color::Black);
		Pen^ redPen = gcnew Pen(Color::Red, 2);
		Pen^ greenPen = gcnew Pen(Color::Green, 4);
		SolidBrush^ brush = gcnew SolidBrush(Color::Black);
		SolidBrush^ greenBrush = gcnew SolidBrush(Color::Green);

		int t = 63;

		int s = 5;

		// Create points that define polygon.

		Point point1 = Point(150, 175);
		Point point2 = Point(250, 200);
		Point point3 = Point(350, 200);
		Point point4 = Point(400, 275);
		Point point5 = Point(525, 275);
		Point point6 = Point(600, 175);
		Point point7 = Point(675, 150);
		Point point8 = Point(775, 150);
		Point point9 = Point(850, 200);
		Point point10 = Point(900, 250);
		Point point11 = Point(1000, 275); 
		List<Point> points;
		points.Add(point1);
		points.Add(point2);
		points.Add(point3);
		points.Add(point4);
		points.Add(point5);
		points.Add(point6);
		points.Add(point7);
		points.Add(point8);
		points.Add(point9);
		points.Add(point10);
		points.Add(point11); 
		vector<Point2D> points2D;
		for each (Point p in points)
		{
			Point2D point2D(p.X, p.Y);
			points2D.push_back(point2D);
		}



		Graph graph(points2D, t);

		for each (Point point in points)
		{
			g->DrawEllipse(blackPen, point.X - t, point.Y - t, 2 * t, 2 * t);
			g->FillEllipse(brush, point.X - s, point.Y - s, 2 * s, 2 * s);
		}
		for each (Line edge in graph.edges)
		{
			Point p1(static_cast<int>(edge.A.getX() + 0.5), static_cast<int>(edge.A.getY() + 0.5));
			Point p2(static_cast<int>(edge.B.getX() + 0.5), static_cast<int>(edge.B.getY() + 0.5));
			g->DrawLine(redPen, p1, p2);
		}

		OptimalPath path(graph, 0, acceptedError);
		
		vector<Line> edges = path.pathEdges;
		
		for (size_t j = 1; j <edges.size(); j++)
		{
			if (!(edges[j - 1].B == edges[j].A))
			{
				Point2D intersectionPoint = edges[j - 1].IntersectWith(edges[j]);
				g->FillEllipse(greenBrush, static_cast<int>(intersectionPoint.getX() + 0.5 - s), static_cast<int>(intersectionPoint.getY() + 0.5) - s, 2 * s, 2 * s);
				edges[j - 1].B = intersectionPoint;
				edges[j].A = intersectionPoint;
			}
		}

		for each (Line edge in edges)
		{
			//get 2 points so you can draw a line
			Point2D firstPoint = edge.A;
			Point2D lastPoint = edge.B;
			Point p1(static_cast<int>(firstPoint.getX() + 0.5), static_cast<int>(firstPoint.getY() + 0.5));
			Point p2(static_cast<int>(lastPoint.getX() + 0.5), static_cast<int>(lastPoint.getY() + 0.5));
			g->DrawLine(greenPen, p1, p2);

		}


	}

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->SuspendLayout();
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(196, 6);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(100, 20);
				 this->textBox1->TabIndex = 0;
				 this->textBox1->Text = L"0";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(19, 9);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(171, 13);
				 this->label1->TabIndex = 1;
				 this->label1->Text = L"accepted error(less then tolerance)";
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(302, 6);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(75, 23);
				 this->button1->TabIndex = 2;
				 this->button1->Text = L"recalculate";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				 // 
				 // panel1
				 // 
				 this->panel1->Location = System::Drawing::Point(-3, 40);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(1299, 472);
				 this->panel1->TabIndex = 3;
				 this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1100, 500);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->textBox1);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->label1);
				 this->Name = L"MyForm";
				 this->Text = L"MyForm";
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }

	
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		System::String ^text = this->textBox1->Text;
		int acceptedError = int::Parse(text);
		Graphics ^g = panel1->CreateGraphics();
		g->Clear(Color::Azure);
		Draw(acceptedError, g);

	}
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics ^g = e->Graphics;  //require for drawing
		int acceptedError = 0;
		Draw(acceptedError, g);
	}
	};
}

#pragma endregion

