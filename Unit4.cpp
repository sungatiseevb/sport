

#include <vcl.h>
#pragma hdrstop
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
TForm4 *Form4;

__fastcall TForm4::TForm4(TComponent* Owner)
    : TForm(Owner)
{
    Color = CLR_BG;

    StringGrid1->Color = CLR_PANEL;
    StringGrid1->Font->Color = CLR_TEXT;
    StringGrid1->FixedColor = CLR_GREEN;
    StringGrid1->GridLineWidth = 1;

    Button1->Color = CLR_PANEL;
    Button1->Font->Color = CLR_MUTED;

    Button2->Color = CLR_GREEN;
    Button2->Font->Color = CLR_TEXT;
    Button2->Font->Style = TFontStyles() << fsBold;

    StringGrid1->Cells[0][0] = "Дата";
    StringGrid1->Cells[1][0] = "Упражнение";
    StringGrid1->Cells[2][0] = "Нагрузка";
    StringGrid1->Cells[3][0] = "Интенсивность";
    StringGrid1->Cells[4][0] = "Подходы";
    StringGrid1->Cells[5][0] = "Время";

    StringGrid1->ColWidths[0] = 100;
    StringGrid1->ColWidths[1] = 120;
    StringGrid1->ColWidths[2] = 90;
    StringGrid1->ColWidths[3] = 100;
    StringGrid1->ColWidths[4] = 80;
    StringGrid1->ColWidths[5] = 90;
}

void __fastcall TForm4::AddRecord(AnsiString exercise, AnsiString load,
    AnsiString intensity, AnsiString sets, AnsiString time)
{
    int row = StringGrid1->RowCount;
    StringGrid1->RowCount = row + 1;

    TDateTime now = Now();
    AnsiString date = DateTimeToStr(now);

    StringGrid1->Cells[0][row] = date;
    StringGrid1->Cells[1][row] = exercise;
    StringGrid1->Cells[2][row] = load;
    StringGrid1->Cells[3][row] = intensity;
    StringGrid1->Cells[4][row] = sets;
    StringGrid1->Cells[5][row] = time;
}

void __fastcall TForm4::Button1Click(TObject *Sender)
{
    if (MessageDlg("Очистить всю историю?", mtConfirmation,
        TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
    {
        StringGrid1->RowCount = 2;
        StringGrid1->Cells[0][1] = "";
        StringGrid1->Cells[1][1] = "";
        StringGrid1->Cells[2][1] = "";
        StringGrid1->Cells[3][1] = "";
        StringGrid1->Cells[4][1] = "";
        StringGrid1->Cells[5][1] = "";
    }
}

void __fastcall TForm4::Button2Click(TObject *Sender)
{
    this->Close();
}