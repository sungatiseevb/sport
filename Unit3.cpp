#include <vcl.h>
#pragma hdrstop
#include "Unit3.h"
#include "Unit4.h"

using namespace std;

#define CLR_BG       0x001A1A1A
#define CLR_PANEL    0x00252525
#define CLR_GREEN    0x0033AA55
#define CLR_TEXT     0x00FFFFFF
#define CLR_MUTED    0x00888888
#define CLR_BORDER   0x00333333

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

int seconds = 0;
int sets = 0;


__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
    Color = CLR_BG;

    Label1->Font->Color = CLR_MUTED;
    Label2->Font->Color = CLR_MUTED;
    Label3->Font->Color = CLR_MUTED;

    lblIntensity->Font->Color = CLR_GREEN;
    lblIntensity->Font->Size = 12;

    lblSets->Font->Color = CLR_GREEN;
    lblSets->Font->Size = 14;
    lblSets->Font->Style = TFontStyles() << fsBold;

    lblTime->Font->Color = CLR_GREEN;
    lblTime->Font->Size = 20;
    lblTime->Font->Style = TFontStyles() << fsBold;

    ComboBox1->Color = CLR_PANEL;
    ComboBox1->Font->Color = CLR_TEXT;

    RadioGroup1->Color = CLR_BG;
    RadioGroup1->Font->Color = CLR_TEXT;

    Button1->Color = CLR_GREEN;
    Button1->Font->Color = CLR_TEXT;
    Button1->Font->Style = TFontStyles() << fsBold;

    Button2->Color = CLR_PANEL;
    Button2->Font->Color = CLR_TEXT;

    Button3->Color = CLR_GREEN;
    Button3->Font->Color = CLR_TEXT;
    Button3->Font->Style = TFontStyles() << fsBold;

    Button4->Color = CLR_PANEL;
    Button4->Font->Color = CLR_MUTED;

    Button2->Enabled = false;
}

void __fastcall TForm3::Button1Click(TObject *Sender)
{
    if (ComboBox1->ItemIndex == -1)
    {
        MessageDlg("Выберите упражнение!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    if (RadioGroup1->ItemIndex == -1)
    {
        MessageDlg("Выберите тип нагрузки!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    seconds = 0;
    sets++;
    lblSets->Caption = "Подходы: " + IntToStr(sets);
    Timer1->Enabled = true;
    Button1->Enabled = false;
    Button2->Enabled = true;
}

void __fastcall TForm3::Button2Click(TObject *Sender)
{
    Timer1->Enabled = false;
    Button1->Enabled = true;
    Button2->Enabled = false;
}

void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
    seconds++;
    int m = seconds / 60;
    int s = seconds % 60;
    AnsiString time = (m < 10 ? "0" : "") + IntToStr(m) + ":" + (s < 10 ? "0" : "") + IntToStr(s);
    lblTime->Caption = "Время: " + time;
}

void __fastcall TForm3::TrackBar1Change(TObject *Sender)
{
    lblIntensity->Caption = IntToStr(TrackBar1->Position);
}

void __fastcall TForm3::Button3Click(TObject *Sender)
{
    if (ComboBox1->ItemIndex == -1)
    {
        MessageDlg("Нечего сохранять!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    AnsiString exercise = ComboBox1->Text;
    AnsiString load = RadioGroup1->Items->Strings[RadioGroup1->ItemIndex];
    AnsiString intensity = IntToStr(TrackBar1->Position);
    AnsiString setsStr = IntToStr(sets);
    AnsiString time = lblTime->Caption;

    Form4->AddRecord(exercise, load, intensity, setsStr, time);
    MessageDlg("Тренировка сохранена!", mtInformation, TMsgDlgButtons() << mbOK, 0);

    Timer1->Enabled = false;
    seconds = 0;
    sets = 0;
    lblSets->Caption = "Подходы: 0";
    lblTime->Caption = "Время: 00:00";
    Button1->Enabled = true;
    Button2->Enabled = false;
}

void __fastcall TForm3::Button4Click(TObject *Sender)
{
    Timer1->Enabled = false;
    this->Close();
}