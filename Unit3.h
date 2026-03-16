#ifndef Unit3H
#define Unit3H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

class TForm3 : public TForm
{
__published:
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *lblIntensity;
    TLabel *lblSets;
    TLabel *lblTime;
    TComboBox *ComboBox1;
    TRadioGroup *RadioGroup1;
    TTrackBar *TrackBar1;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TTimer *Timer1;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall TrackBar1Change(TObject *Sender);
private:
public:
    __fastcall TForm3(TComponent* Owner);
};

extern PACKAGE TForm3 *Form3;
#endif