#pragma once

namespace Zurassic
{
    using namespace System;
    using namespace Zurassic::USB;
    using namespace System::Diagnostics;

    // reference: PowerMateDemo.project
    // 1. press and draw full screen
    // 2. read keypress event.
    ref class PowerMate
    {
    public:
        PowerMate(void) : _hid(VID, PID)
        {
            _hid.Connect();
            _hid.NativeDataRead += gcnew NativeDataReadEventHandler(this, &PowerMate::InterruptInputRead);
        }

    public:
        property Boolean PulseOn
        {
            void set(Boolean value)
            {
                array<Byte>^ data = gcnew array<Byte>(_hid.FeatureReportLengthInBytes);
                data[0] = 0x00;
                data[1] = 0x41;
                data[2] = 0x01;
                data[3] = 0x03;	// command type
                data[4] = 0x00;
                data[5] = value ? 0x01 : 0x00;
                _hid.WriteFeatureReport(data);
            }
        }

        // 0-24, while 8 being 1 pulse/sec 
       property Byte PulseSpeed 
		{
			void set(Byte value)
			{
                if(value > 24) value = 24;

                array<Byte>^ data = gcnew array<Byte>(_hid.FeatureReportLengthInBytes);
                data[0] = 0x00;
                data[1] = 0x41;
                data[2] = 0x01;
                data[3] = 0x04;	// command type
                data[4] = 0x00;

                // set pulse rate
                // byte 5; 0 = divide, 1 = normal speed, 2 = multiply
                // byte 6; value
                int pos = value;
                if (pos < 8)
                {
                    data[5] = 0;
                    data[6] = (7-pos) * 2;
                }
                else if (pos > 8)
                {
                    data[5] = 2;
                    data[6] = (pos-8) * 2;
                }
                else
                {
                    data[5] = 1;
                    data[6] = 0;
                }

                _hid.WriteFeatureReport(data);
			}
       }
       
    property UInt32 ButtonPressed
    {
        UInt32 get() { return _buttonPressed;}
    }

    public:
        event System::Windows::Forms::MethodInvoker^ ButtonDownPressed;

    private:
        void InterruptInputRead(unsigned char* report)
        {
            // test for pushbutton
            if (report[0] == 1 )
            {
                // button down
                _buttonPressed++;
                ButtonDownPressed();
            }
            else if ( report[1] == 0 && report[0] == 0)
            {
                // button up
                _buttonPressed = 0;
                ButtonDownPressed();
            }

            // test for knob rotation
            if (report[1] != 0 )
            {
                if(report[1] == 1)
                    Debug::WriteLine("->");
                if(report[1] == 255)
                    Debug::WriteLine("<-");
            }
        }

    private:
        // PowerMate
        static initonly UInt16 VID = 0x077d;
        static initonly UInt16 PID = 0x0410;

        HIDComponent _hid;
        UInt32 _buttonPressed;
    };
}
