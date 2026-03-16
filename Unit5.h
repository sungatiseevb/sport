#ifndef Unit5H
#define Unit5H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

class TForm5 : public TForm
{
__published:
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *lblResult;
    TEdit *Edit1;
    TEdit *Edit2;
    TComboBox *ComboBox1;
    TRadioGroup *RadioGroup1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:
public:
    __fastcall TForm5(TComponent* Owner);
};

extern PACKAGE TForm5 *Form5;
#endif