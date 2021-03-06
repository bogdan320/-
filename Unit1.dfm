object Form1: TForm1
  Left = 385
  Top = 247
  Width = 603
  Height = 271
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 168
    Top = 88
    Width = 18
    Height = 13
    Caption = '100'
  end
  object Label2: TLabel
    Left = 168
    Top = 104
    Width = 13
    Height = 13
    Caption = 'ms'
  end
  object Label3: TLabel
    Left = 256
    Top = 152
    Width = 75
    Height = 13
    Caption = #1042#1099#1088#1072#1074#1085#1080#1074#1072#1085#1080#1077
  end
  object Label4: TLabel
    Left = 256
    Top = 184
    Width = 76
    Height = 13
    Caption = #1053#1086#1084#1077#1088' '#1096#1088#1080#1092#1090#1072
  end
  object Label5: TLabel
    Left = 472
    Top = 120
    Width = 84
    Height = 13
    Caption = #1048#1085#1090#1077#1088#1074#1072#1083' ('#1084#1089#1077#1082')'
  end
  object OpenButton: TButton
    Left = 112
    Top = 24
    Width = 75
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100
    TabOrder = 0
    OnClick = OpenButtonClick
  end
  object SendButton: TButton
    Left = 312
    Top = 96
    Width = 75
    Height = 25
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
    Enabled = False
    TabOrder = 1
    OnClick = SendButtonClick
  end
  object UpTextEdit: TEdit
    Left = 264
    Top = 32
    Width = 201
    Height = 21
    TabOrder = 2
    Text = '1234'
  end
  object TimeoutBar: TTrackBar
    Left = 16
    Top = 88
    Width = 150
    Height = 45
    Max = 1000
    Min = 50
    Orientation = trHorizontal
    Frequency = 100
    Position = 100
    SelEnd = 0
    SelStart = 0
    TabOrder = 3
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TimeoutBarChange
  end
  object PortNumberBox: TComboBox
    Left = 16
    Top = 24
    Width = 65
    Height = 21
    ItemHeight = 13
    TabOrder = 4
  end
  object SearchButton: TButton
    Left = 112
    Top = 56
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082' '#1087#1086#1088#1090#1086#1074
    TabOrder = 5
    OnClick = SearchButtonClick
  end
  object BrightUpDown: TUpDown
    Left = 49
    Top = 152
    Width = 16
    Height = 21
    Associate = BrightEdit
    Min = 1
    Max = 10
    Position = 5
    TabOrder = 6
    Wrap = False
  end
  object BrightEdit: TEdit
    Left = 24
    Top = 152
    Width = 25
    Height = 21
    TabOrder = 7
    Text = '5'
  end
  object BrightnessButton: TButton
    Left = 80
    Top = 152
    Width = 75
    Height = 25
    Caption = #1059#1089#1090'. '#1103#1088#1082#1086#1089#1090#1100
    Enabled = False
    TabOrder = 8
    OnClick = BrightnessButtonClick
  end
  object AlignBox: TComboBox
    Left = 336
    Top = 152
    Width = 73
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 9
    Text = #1062#1077#1085#1090#1088
    Items.Strings = (
      #1057#1083#1077#1074#1072
      #1057#1087#1088#1072#1074#1072
      #1062#1077#1085#1090#1088)
  end
  object FontUpDown: TUpDown
    Left = 361
    Top = 176
    Width = 16
    Height = 21
    Associate = FontEdit
    Min = 1
    Max = 10
    Position = 2
    TabOrder = 10
    Wrap = False
  end
  object FontEdit: TEdit
    Left = 336
    Top = 176
    Width = 25
    Height = 21
    TabOrder = 11
    Text = '2'
  end
  object DownTextEdit: TEdit
    Left = 264
    Top = 64
    Width = 201
    Height = 21
    TabOrder = 12
    Text = '1234'
  end
  object UpTextEn: TCheckBox
    Left = 472
    Top = 32
    Width = 105
    Height = 17
    Caption = #1042#1077#1088#1093#1085#1103#1103' '#1089#1090#1088#1086#1082#1072
    Checked = True
    State = cbChecked
    TabOrder = 13
  end
  object DownTextEn: TCheckBox
    Left = 472
    Top = 64
    Width = 105
    Height = 17
    Caption = #1053#1080#1078#1085#1103#1103' '#1089#1090#1088#1086#1082#1072
    Checked = True
    State = cbChecked
    TabOrder = 14
  end
  object BlinkingEn: TCheckBox
    Left = 448
    Top = 104
    Width = 129
    Height = 17
    Caption = #1052#1077#1088#1094#1072#1102#1097#1072#1103' '#1089#1090#1088#1086#1082#1072
    TabOrder = 15
    OnClick = BlinkingEnClick
  end
  object BlinkInterval: TEdit
    Left = 480
    Top = 136
    Width = 65
    Height = 21
    TabOrder = 16
    Text = '1000'
  end
  object CommPort1: TCommPort
    SerialPort = spCustom
    CustomPortName = 'COM2'
    BaudRate = br38400
    StopBits = sbTwo
    OnDataReceived = CommPort1DataReceived
    Left = 40
    Top = 48
  end
  object ReadTimer: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = ReadTimerTimer
    Left = 80
    Top = 48
  end
  object BlinkingTimer: TTimer
    Tag = 1
    Enabled = False
    OnTimer = BlinkingTimerTimer
    Left = 560
    Top = 128
  end
end
