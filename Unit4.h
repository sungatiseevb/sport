#ifndef Unit4H
#define Unit4H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

class TForm4 : public TForm
{
__published:
    TStringGrid *StringGrid1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:
public:
    __fastcall TForm4(TComponent* Owner);
    void __fastcall AddRecord(AnsiString exercise, AnsiString load,
        AnsiString intensity, AnsiString sets, AnsiString time);
};

extern PACKAGE TForm4 *Form4;
#endif