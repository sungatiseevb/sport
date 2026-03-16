#include <vcl.h>
#pragma hdrstop
#include "Unit5.h"

using namespace std;

#define CLR_BG       0x001A1A1A
#define CLR_PANEL    0x00252525
#define CLR_GREEN    0x0033AA55
#define CLR_TEXT     0x00FFFFFF
#define CLR_MUTED    0x00888888
#define CLR_BORDER   0x00333333

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;

__fastcall TForm5::TForm5(TComponent* Owner)
    : TForm(Owner)
{
    Color = CLR_BG;

    Label1->Font->Color = CLR_MUTED;
    Label2->Font->Color = CLR_MUTED;
    Label3->Font->Color = CLR_MUTED;
    Label4->Font->Color = CLR_MUTED;

    lblResult->Font->Color = CLR_GREEN;
    lblResult->Font->Size = 14;
    lblResult->Font->Style = TFontStyles() << fsBold;

    Edit1->Color = CLR_PANEL;
    Edit1->Font->Color = CLR_TEXT;

    Edit2->Color = CLR_PANEL;
    Edit2->Font->Color = CLR_TEXT;

    ComboBox1->Color = CLR_PANEL;
    ComboBox1->Font->Color = CLR_TEXT;

    RadioGroup1->Color = CLR_BG;
    RadioGroup1->Font->Color = CLR_TEXT;

    Button1->Color = CLR_GREEN;
    Button1->Font->Color = CLR_TEXT;
    Button1->Font->Style = TFontStyles() << fsBold;

    Button2->Color = CLR_PANEL;
    Button2->Font->Color = CLR_MUTED;
}

void __fastcall TForm5::Button1Click(TObject *Sender)
{
    if (Edit1->Text.IsEmpty() || Edit2->Text.IsEmpty())
    {
        MessageDlg("Заполните все поля!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    if (ComboBox1->ItemIndex == -1)
    {
        MessageDlg("Выберите упражнение!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    if (RadioGroup1->ItemIndex == -1)
    {
        MessageDlg("Выберите уровень нагрузки!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    double weight = StrToFloat(Edit1->Text);
    double time = StrToFloat(Edit2->Text);

    double met;
    switch (ComboBox1->ItemIndex)
    {
        case 0: met = 8.0; break;
        case 1: met = 7.0; break;
        case 2: met = 6.0; break;
        case 3: met = 9.0; break;
        case 4: met = 4.0; break;
        default: met = 6.0;
    }

    switch (RadioGroup1->ItemIndex)
    {
        case 0: met *= 0.8; break;
        case 1: met *= 1.0; break;
        case 2: met *= 1.2; break;
    }

    double calories = (met * weight * time) / 60.0;
    lblResult->Caption = "Сожжено калорий: " + FormatFloat("0.0", calories) + " ккал";
}

void __fastcall TForm5::Button2Click(TObject *Sender)
{
    this->Close();
}