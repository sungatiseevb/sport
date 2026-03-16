#ifndef Unit1H
#define Unit1H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

class TForm1 : public TForm
{
__published:
    TLabel *Label1;
    TLabel *Label2;
    TTimer *Timer1;
    TTimer *Timer2;
    TProgressBar *ProgressBar1;
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall Timer2Timer(TObject *Sender);
private:
public:
    __fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;
#endif