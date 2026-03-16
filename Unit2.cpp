

#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
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
TForm2 *Form2;


__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
    Color = CLR_BG;

    Panel1->Color = CLR_PANEL;
    Panel1->Font->Color = CLR_MUTED;
    Panel1->Font->Size = 10;

    Label1->Font->Color = CLR_MUTED;
    Label1->Font->Size = 10;
    Label1->Caption = "WorkOut Planner © 2024";

    ListBox1->Color = CLR_PANEL;
    ListBox1->Font->Color = CLR_TEXT;
    ListBox1->Font->Size = 11;
    ListBox1->Items->Add("  Тренировка");
    ListBox1->Items->Add("  История");
    ListBox1->Items->Add("  Калории");

    Memo1->Color = CLR_BG;
    Memo1->Font->Color = CLR_MUTED;
    Memo1->Font->Size = 11;
    Memo1->Lines->Add("Добро пожаловать в WorkOut Planner!");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Выберите раздел в меню слева.");

    ToolBar1->Color = CLR_PANEL;
    ToolButton1->Font->Color = CLR_TEXT;
    ToolButton2->Font->Color = CLR_TEXT;
    ToolButton3->Font->Color = CLR_TEXT;
    ToolButton4->Font->Color = CLR_TEXT;
}

void __fastcall TForm2::N1Click(TObject *Sender)
{
    Form3->ShowModal();
}

void __fastcall TForm2::N2Click(TObject *Sender)
{
    Form4->ShowModal();
}

void __fastcall TForm2::N3Click(TObject *Sender)
{
    Form5->ShowModal();
}

void __fastcall TForm2::N4Click(TObject *Sender)
{
    Application->Terminate();
}

void __fastcall TForm2::ToolButton1Click(TObject *Sender)
{
    Form3->ShowModal();
}

void __fastcall TForm2::ToolButton2Click(TObject *Sender)
{
    Form4->ShowModal();
}

void __fastcall TForm2::ToolButton3Click(TObject *Sender)
{
    Form5->ShowModal();
}

void __fastcall TForm2::ToolButton4Click(TObject *Sender)
{
    Application->Terminate();
}

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
    switch (ListBox1->ItemIndex)
    {
        case 0: Form3->ShowModal(); break;
        case 1: Form4->ShowModal(); break;
        case 2: Form5->ShowModal(); break;
    }
}