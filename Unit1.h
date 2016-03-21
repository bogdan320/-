//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CommPort.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TCommPort *CommPort1;
        TButton *OpenButton;
        TButton *SendButton;
        TEdit *UpTextEdit;
        TTrackBar *TimeoutBar;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *PortNumberBox;
        TButton *SearchButton;
        TUpDown *BrightUpDown;
        TEdit *BrightEdit;
        TButton *BrightnessButton;
        TComboBox *AlignBox;
        TLabel *Label3;
        TUpDown *FontUpDown;
        TEdit *FontEdit;
        TLabel *Label4;
        TEdit *DownTextEdit;
        TTimer *ReadTimer;
        TCheckBox *UpTextEn;
        TCheckBox *DownTextEn;
        TCheckBox *BlinkingEn;
        TEdit *BlinkInterval;
        TLabel *Label5;
        TTimer *BlinkingTimer;
        void __fastcall OpenButtonClick(TObject *Sender);
        void __fastcall SendButtonClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall TimeoutBarChange(TObject *Sender);
        void __fastcall SearchButtonClick(TObject *Sender);
        void __fastcall SearchPorts();
        void __fastcall BrightnessButtonClick(TObject *Sender);
        void __fastcall CommPort1DataReceived(TObject *Sender,
          const char *Buffer, unsigned Length);
        void __fastcall ReadTimerTimer(TObject *Sender);
        void __fastcall SendProtocol(int State);
        void __fastcall BlinkingTimerTimer(TObject *Sender);
        void __fastcall BlinkingEnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};

class Protocol{
    public:
        AnsiString data;
        unsigned char command;
        unsigned char subcommand;
        unsigned char string_number;
        unsigned char font;
        unsigned char align;
        unsigned char adress;
        vector<unsigned char> get();
    private:
        void CountCS(vector<unsigned char> *Buff);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
