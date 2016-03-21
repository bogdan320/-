//---------------------------------------------------------------------------
#include <windows.h>
#include <TCHAR.H >
#include <conio.h>

#include <vector.h>

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CommPort"
#pragma resource "*.dfm"
#define byte = unsigned char
TForm1 *Form1;
bool Ready = true;

const int STATE_FLUSH = 0;  //Протокол с пустыми строками данных
const int STATE_FILL = 1;   //Протокол с заполненными строками данных

const int SENDING_FALSE = 0;  //Передача протокола не осуществляется
const int SENDING_TRUE = 1;   //Передача протокола осуществляется

const int ADRESS = 0x0A;                //Адрес устройства
const int STRINGNUMBER_UP = 0x00;       //Верхняя строка
const int STRINGNUMBER_DOWN = 0x01;     //Нижняя строка
const int SUBCOMMAND_SHOWSTRING = 0x18; //Команда, задающая яркость
const int COMMAND_BRIGHTNESS = 0x17;    //Команда, задающая яркость
const int COMMAND_SHOWSTRING = 0x5A;    //Команда, выводящая текст на табло
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    SearchPorts();
    if(PortNumberBox->Items->Count > 0) {
        PortNumberBox->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OpenButtonClick(TObject *Sender)
{
    if( !Ready )  return;
    Ready = false;
    if( !CommPort1->Connected ) {
        CommPort1->CustomPortName = PortNumberBox->Items->Strings[PortNumberBox->ItemIndex];
        CommPort1->Open();
        OpenButton->Caption = "Закрыть";
        SearchButton->Enabled = false;
        SendButton->Enabled = true;
        BrightnessButton->Enabled = true;
        TimeoutBarChange(NULL);
    } else {
        OpenButton->Caption = "Открыть";
        SearchButton->Enabled = true;
        SendButton->Enabled = false;
        BrightnessButton->Enabled = false;
        CommPort1->Close();
    }
    Ready = true;
}

//----------------------------------------------------------------------------
void __fastcall TForm1::SearchPorts()
{
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    BOOL bGetVer = GetVersionEx(&osvi);

    if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)) {
        // Используем QueryDosDevice для просмотра всех устройств
        //  похожих на COMx.
       // Это наилучшее решение, так как порты не требуется открывать
        TCHAR szDevices[65535];
        DWORD dwChars = QueryDosDevice(NULL, szDevices, 65535);
        if(dwChars) {
            int i=0;
            for (;;) {
            // Получаем текущее имя устройства
                TCHAR* pszCurrentDevice = &szDevices[i];
                // Если похоже на "COMX" выводим на экран
                int nLen = _tcslen(pszCurrentDevice);
                if(nLen > 3 && nLen <6 && _tcsnicmp(pszCurrentDevice, _T("COM"), 3) == 0) {
                    PortNumberBox->Items->Add(pszCurrentDevice);
                }
                // Переходим к следующему символу терминатору
                while(szDevices[i] != _T('\0'))
                    i++;
                  // Перескакиваем на следующую строку
                    i++;

                  // Список завершается двойным симмволом терминатором,
                  // так что если символ
                  // NULL, мы дошли до конца
                  if(szDevices[i] == _T('\0'))
                    break;
            } // for (;;)
        } // if(dwChars)
    } // if(bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT))
}

//---------------------------------------------------------------------------

void Protocol::CountCS(vector<unsigned char> *Buff)
{
    unsigned int cs1, cs2;
    unsigned char k, m;
    k = 0;
    cs1 = 0;
    cs2 = 0;
    for (int i = 0; i < (*Buff).size(); i++) {
        m = (*Buff)[i];
        cs1 += m;
        m ^= 0x5A;
        if (k) m = (m >> k) | (m << (8 - k));
        k = (k + 1) & 0x07;
        cs2 += m;
    }
    (*Buff).insert((*Buff).begin(), cs2 & 0xFF);
    (*Buff).insert((*Buff).begin(), cs1 & 0xFF);
}
//---------------------------------------------------------------------------

// Получение протокола
vector<unsigned char> Protocol::get() {
    vector<unsigned char> prot;
    adress = ADRESS;
    switch(command) {
        case (COMMAND_BRIGHTNESS) : {       //Протокол изменения яркости
            prot.insert(prot.begin(), (unsigned char)StrToInt(data));
            prot.insert(prot.begin(), command);
            prot.insert(prot.begin(), adress);
            prot.insert(prot.begin(), 0x01);
            CountCS(&prot);
            prot.insert(prot.begin(), prot.size() + 1);
            break;
        }
        case (COMMAND_SHOWSTRING) : {       //Протокол вывода текста на табло
            prot.insert(prot.begin(), 0x00);
            for(int i = data.Length(); i > 0; i--) {
                unsigned char str = (int)data[i];
                prot.insert(prot.begin(), str);
            }
            prot.insert(prot.begin(), 0x20);
            prot.insert(prot.begin(), font);
            prot.insert(prot.begin(), align);
            prot.insert(prot.begin(), string_number);
            prot.insert(prot.begin(), subcommand);
            prot.insert(prot.begin(), command);
            prot.insert(prot.begin(), adress);
            prot.insert(prot.begin(), 0x01);
            CountCS(&prot);
            prot.insert(prot.begin(), prot.size() + 1);
            break;
        }
    }
    return prot;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SendProtocol(int state)
{

    unsigned char font = (StrToInt(FontEdit->Text) | 0xF0);
    Protocol showStringProt;
    showStringProt.command = COMMAND_SHOWSTRING;
    showStringProt.subcommand = SUBCOMMAND_SHOWSTRING;
    showStringProt.font = font;
    showStringProt.align = AlignBox->ItemIndex;

    if (UpTextEn->Checked) {
        showStringProt.data = ((state) ? UpTextEdit->Text : (AnsiString)"");
        showStringProt.string_number = STRINGNUMBER_UP;
        vector<unsigned char> data = showStringProt.get();
        CommPort1->Write(data.begin(), data.size());
    }
    if (DownTextEn->Checked) {
        showStringProt.data = ((state) ? DownTextEdit->Text : (AnsiString)"");
        showStringProt.string_number = STRINGNUMBER_DOWN;
        vector<unsigned char> data = showStringProt.get();
        CommPort1->Write(data.begin(), data.size());
    }
    ReadTimer->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::SendButtonClick(TObject *Sender)
{
    SendProtocol(STATE_FILL);
    if (BlinkingEn->Checked) {
        BlinkingTimer->Enabled = true;
        BlinkingTimer->Interval = StrToInt(BlinkInterval->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(CommPort1->Connected) {
        CommPort1->Close();
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TimeoutBarChange(TObject *Sender)
{
    TimeoutBar->Hint = AnsiString("Timeout ") + TimeoutBar->Position + " ms";
    Label1->Caption = TimeoutBar->Position;

    if( !Ready )  return;
    if( !CommPort1->Connected )  return;
    Ready = false;
    COMMTIMEOUTS to;
        to.ReadIntervalTimeout = 2;
        to.ReadTotalTimeoutConstant = TimeoutBar->Position;
        to.ReadTotalTimeoutMultiplier = 10;
        to.WriteTotalTimeoutConstant = 35;
        to.WriteTotalTimeoutMultiplier = 2;
    SetCommTimeouts(CommPort1->TimeOuts, &to);
    Ready = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SearchButtonClick(TObject *Sender)
{

    PortNumberBox->Clear();
    SearchPorts();
    // Нужно реализовать сортировку
    if(PortNumberBox->Items->Count > 0) {
        PortNumberBox->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BrightnessButtonClick(TObject *Sender)
{
    Protocol brightnessProt;
    brightnessProt.data = BrightEdit->Text;
    brightnessProt.command = COMMAND_BRIGHTNESS;
    vector<unsigned char> data = brightnessProt.get();
    CommPort1->Write(data.begin(), data.size());
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CommPort1DataReceived(TObject *Sender,
      const char *Buffer, unsigned Length)
{
    if (Length == 8) {
        ShowMessage("Данные переданы");
    } else {
        ShowMessage("Ошибка передачи данных");
    }
    ReadTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReadTimerTimer(TObject *Sender)
{
    ShowMessage("Время ожидания порта окончено");
    ReadTimer->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BlinkingTimerTimer(TObject *Sender)
{
    if (BlinkingTimer->Tag == STATE_FILL) {
        SendProtocol(STATE_FLUSH);
        BlinkingTimer->Tag = STATE_FLUSH;
    } else {
        SendProtocol(STATE_FILL);
        BlinkingTimer->Tag = STATE_FILL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BlinkingEnClick(TObject *Sender)
{

    if (BlinkingEn->Checked) {
        BlinkingTimer->Enabled = true;
    } else {
        BlinkingTimer->Enabled = false;
    }

}
//---------------------------------------------------------------------------




