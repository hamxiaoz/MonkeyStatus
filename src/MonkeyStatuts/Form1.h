#pragma once
#include "PowerMate.h"

// GetDC
//#include <Windows.h>
//#pragma comment(lib, "User32.lib")

namespace MonkeyStatuts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    using namespace Zurassic;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
        Form1(void): _drawingFont(L"Arial", 50)
		{
			InitializeComponent();
			
            _powerMate.ButtonDownPressed += gcnew MethodInvoker(this, &Form1::PowerMateButtonDownPressed);
            _refreshDelegate = gcnew MethodInvoker(this, &Form1::ThreadSafeRefreshImp);
		}

    private:
        PowerMate _powerMate;
        MethodInvoker^ _refreshDelegate;
        System::Drawing::Font _drawingFont;
    private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
             GrowlNotifier _notifier;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::ComponentModel::IContainer^  components;
    protected: 

    protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->components = (gcnew System::ComponentModel::Container());
            this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
            this->SuspendLayout();
            // 
            // notifyIcon1
            // 
            this->notifyIcon1->Text = L"notifyIcon1";
            this->notifyIcon1->Visible = true;
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(172, 132);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->Name = L"Form1";
            this->ShowIcon = false;
            this->ShowInTaskbar = false;
            this->Text = L"Form1";
            this->TopMost = true;
            this->TransparencyKey = System::Drawing::SystemColors::Control;
            this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
            this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
             {
                 Int32 width = 100;
                 Int32 height = Screen::PrimaryScreen->Bounds.Bottom - Screen::PrimaryScreen->WorkingArea.Bottom;
                 Int32 x = Screen::PrimaryScreen->Bounds.Right - width;
                 Int32 y = Screen::PrimaryScreen->WorkingArea.Bottom;
                 this->Width = width;
                 this->Height = height;
                 this->Location = Point(x, y);
             }
    private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
             {
                 //_powerMate.PulseOn = this->checkBox1->Checked;
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 /*Random^ random = gcnew Random();
                 Byte speed = (Byte)random->Next(24);
                 _powerMate.PulseSpeed = speed;*/
             }

    private:
        void ThreadSafeRefresh()
        {
            if(this->InvokeRequired)
               this->BeginInvoke(_refreshDelegate); 
            else
                _refreshDelegate->Invoke();
        }
        void ThreadSafeRefreshImp()
        {
            Refresh();
        }

        void PowerMateButtonDownPressed()
        {
            //ThreadSafeRefresh();
            _notifier.SendNotification();
        }
    private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
             {
                 //e->Graphics->DrawString(_powerMate.ButtonPressed.ToString(), %_drawingFont, Brushes::Black, 0, 0);
                 if(_powerMate.ButtonPressed > 0)
                 {
                     //this->Location = Point(this->Location.X-10, this->Location.Y);
                     e->Graphics->FillRectangle(Brushes::Red, this->DisplayRectangle);

                     // draw on screen, it'll get erased pretty easily by any window activity.
                     /*HDC hdc = ::GetDC(NULL);
                     Graphics^ g = Graphics::FromHdc(IntPtr(hdc));
                     g->FillRectangle(Brushes::Red, 0, 0, 100, 100);
                     ::ReleaseDC(NULL, hdc);*/
                 }
                 
             }
};
}

