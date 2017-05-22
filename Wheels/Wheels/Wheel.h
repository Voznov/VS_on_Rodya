#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Drawing;


namespace Wheels {

	/// <summary>
	/// ������ ��� Wheel
	/// </summary>

	public ref class Wheel :  public System::ComponentModel::Component
	{
	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;
		Pen^ myPen,^ simplePen;
		float _x, _y, _radius, _angle, _width;
		int _count;
		Color _color;
		Graphics^ _g;
	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Wheel()
		{
			if (components)
			{
				delete components;
				delete myPen;
				delete simplePen;
			}
		}
	public:
		Wheel(void)
		{
			InitializeComponent();
		}
		Wheel(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// ��������� ��� ��������� ������������ ���������� ������� Windows.Forms
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

		void Set(float x, float y, float radius, int count, System::Drawing::Color color, Graphics^ g)
		{
			_x = x; _y = y; _radius = radius;
			_count = count;
			_color = color;
			_angle = 0;
			_width = radius / 8;
			_g = g;
			simplePen = gcnew Pen(Color::Black, 1);
		}

		void Draw()
		{
			for (int i = 0; i < _count; ++i)
				_g->DrawLine(simplePen, 
					_x + _radius * sinf(_angle + i * M_PI / _count),
					_y + _radius * cosf(_angle + i * M_PI / _count),
					_x - _radius * sinf(_angle + i * M_PI / _count),
					_y - _radius * cosf(_angle + i * M_PI / _count));
			myPen = gcnew Pen(_color, _width);
			_g->DrawEllipse(myPen, _x - _radius, _y - _radius, 2*_radius, 2*_radius);
		}
		
		void Angle(float part_of_pi)
		{
			_angle += M_PI * part_of_pi;
			if (_angle > 2 * M_PI)
				_angle -= 2 * M_PI;
		}

		void MoveTo(float x, float y)
		{
			_x = x;
			_y = y;
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};
}
