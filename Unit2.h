#ifndef Unit2H
#define Unit2H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

class TForm2 : public TForm
{
__published:
    TMainMenu *MainMenu1;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TPanel *Panel1;
    TLabel *Label1;
    TListBox *ListBox1;
    TMemo *Memo1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    void __fastcall N1Click(TObject *Sender);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall N3Click(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall ToolButton1Click(TObject *Sender);
    void __fastcall ToolButton2Click(TObject *Sender);
    void __fastcall ToolButton3Click(TObject *Sender);
    void __fastcall ToolButton4Click(TObject *Sender);
    void __fastcall ListBox1Click(TObject *Sender);
private:
public:
    __fastcall TForm2(TComponent* Owner);
};

extern PACKAGE TForm2 *Form2;
#endif