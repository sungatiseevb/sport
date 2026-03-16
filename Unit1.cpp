#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"

using namespace std;

#define CLR_BG       0x001A1A1A
#define CLR_PANEL    0x00252525
#define CLR_GREEN    0x0033AA55
#define CLR_TEXT     0x00FFFFFF
#define CLR_MUTED    0x00888888
#define CLR_BORDER   0x00333333

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    Color = CLR_BG;
    Label1->Font->Color = CLR_GREEN;
    Label1->Font->Size = 28;
    Label1->Font->Style = TFontStyles() << fsBold;
    Label2->Font->Color = CLR_MUTED;
    Label2->Font->Size = 11;
}

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
    if (ProgressBar1->Position < 100)
        ProgressBar1->Position += 3;
    else
        ProgressBar1->Position = 100;
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;
    Timer2->Enabled = false;
    Form2->Show();
    this->Close();
}