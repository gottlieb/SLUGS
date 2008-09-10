object FPpal: TFPpal
  Left = 31
  Top = 24
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'UCSC - AP Ground Station'
  ClientHeight = 620
  ClientWidth = 625
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 601
    Width = 625
    Height = 19
    Panels = <>
    SimplePanel = False
    SizeGrip = False
  end
  object pc_main: TPageControl
    Left = 201
    Top = 0
    Width = 424
    Height = 601
    ActivePage = ts_ge
    Align = alClient
    TabIndex = 0
    TabOrder = 1
    object ts_ge: TTabSheet
      Caption = 'Google Earth Config'
      object Label2: TLabel
        Left = 8
        Top = 16
        Width = 81
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Main KML File'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object bt_mainKml: TSpeedButton
        Left = 360
        Top = 32
        Width = 23
        Height = 21
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
          333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
          0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
          07333337F3FF3FFF7F333330F00F000F07333337F77377737F333330FFFFFFFF
          07333FF7F3FFFF3F7FFFBBB0F0000F0F0BB37777F7777373777F3BB0FFFFFFFF
          0BBB3777F3FF3FFF77773330F00F000003333337F773777773333330FFFF0FF0
          33333337F3FF7F37F3333330F08F0F0B33333337F7737F77FF333330FFFF003B
          B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
          3BB33773333773333773B333333B3333333B7333333733333337}
        NumGlyphs = 2
        OnClick = bt_mainKmlClick
      end
      object Label3: TLabel
        Left = 8
        Top = 56
        Width = 117
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Plane Path KML FIle'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object bt_ppKml: TSpeedButton
        Left = 360
        Top = 72
        Width = 23
        Height = 21
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
          333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
          0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
          07333337F3FF3FFF7F333330F00F000F07333337F77377737F333330FFFFFFFF
          07333FF7F3FFFF3F7FFFBBB0F0000F0F0BB37777F7777373777F3BB0FFFFFFFF
          0BBB3777F3FF3FFF77773330F00F000003333337F773777773333330FFFF0FF0
          33333337F3FF7F37F3333330F08F0F0B33333337F7737F77FF333330FFFF003B
          B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
          3BB33773333773333773B333333B3333333B7333333733333337}
        NumGlyphs = 2
        OnClick = bt_ppKmlClick
      end
      object SpeedButton1: TSpeedButton
        Left = 8
        Top = 496
        Width = 377
        Height = 22
        Caption = 'Generate Files and Start Updating Google Earth with Telemetry'
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
          555555555555555555555555555555555555555555FF55555555555559055555
          55555555577FF5555555555599905555555555557777F5555555555599905555
          555555557777FF5555555559999905555555555777777F555555559999990555
          5555557777777FF5555557990599905555555777757777F55555790555599055
          55557775555777FF5555555555599905555555555557777F5555555555559905
          555555555555777FF5555555555559905555555555555777FF55555555555579
          05555555555555777FF5555555555557905555555555555777FF555555555555
          5990555555555555577755555555555555555555555555555555}
        NumGlyphs = 2
        OnClick = SpeedButton1Click
      end
      object Label4: TLabel
        Left = 8
        Top = 200
        Width = 136
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Aircraft Trajectory Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object Label5: TLabel
        Left = 8
        Top = 256
        Width = 82
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Tessalet Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object Label6: TLabel
        Left = 184
        Top = 256
        Width = 137
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Tessalate Transparency'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object Label7: TLabel
        Left = 8
        Top = 328
        Width = 50
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Icon File'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object SpeedButton2: TSpeedButton
        Left = 360
        Top = 344
        Width = 23
        Height = 21
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
          333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
          0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
          07333337F3FF3FFF7F333330F00F000F07333337F77377737F333330FFFFFFFF
          07333FF7F3FFFF3F7FFFBBB0F0000F0F0BB37777F7777373777F3BB0FFFFFFFF
          0BBB3777F3FF3FFF77773330F00F000003333337F773777773333330FFFF0FF0
          33333337F3FF7F37F3333330F08F0F0B33333337F7737F77FF333330FFFF003B
          B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
          3BB33773333773333773B333333B3333333B7333333733333337}
        NumGlyphs = 2
        OnClick = bt_ppKmlClick
      end
      object Label8: TLabel
        Left = 8
        Top = 376
        Width = 247
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'Autopilot WayPoint File (from Google Earth)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
      end
      object SpeedButton3: TSpeedButton
        Left = 360
        Top = 392
        Width = 23
        Height = 21
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
          333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
          0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
          07333337F3FF3FFF7F333330F00F000F07333337F77377737F333330FFFFFFFF
          07333FF7F3FFFF3F7FFFBBB0F0000F0F0BB37777F7777373777F3BB0FFFFFFFF
          0BBB3777F3FF3FFF77773330F00F000003333337F773777773333330FFFF0FF0
          33333337F3FF7F37F3333330F08F0F0B33333337F7737F77FF333330FFFF003B
          B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
          3BB33773333773333773B333333B3333333B7333333733333337}
        NumGlyphs = 2
        OnClick = bt_ppKmlClick
      end
      object DBEdit1: TDBEdit
        Left = 8
        Top = 32
        Width = 353
        Height = 21
        DataField = 'kmlFile'
        DataSource = fte_config
        TabOrder = 0
      end
      object DBEdit2: TDBEdit
        Left = 8
        Top = 72
        Width = 353
        Height = 21
        DataField = 'planePathFile'
        DataSource = fte_config
        TabOrder = 1
      end
      object DBRadioGroup1: TDBRadioGroup
        Left = 8
        Top = 104
        Width = 377
        Height = 49
        Caption = ' Update Rate (in Secs) '
        Columns = 5
        DataField = 'updateRate'
        DataSource = fte_config
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Items.Strings = (
          '1'
          '2'
          '3'
          '4'
          '5')
        ParentFont = False
        TabOrder = 2
        Values.Strings = (
          '1'
          '2'
          '3'
          '4'
          '5')
      end
      object DBCheckBox1: TDBCheckBox
        Left = 8
        Top = 168
        Width = 97
        Height = 17
        Caption = 'Tesselate'
        DataField = 'tessellate'
        DataSource = fte_config
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        ValueChecked = '1'
        ValueUnchecked = '0'
      end
      object BitBtn1: TBitBtn
        Left = 24
        Top = 528
        Width = 75
        Height = 25
        Caption = 'BitBtn1'
        TabOrder = 4
        OnClick = BitBtn1Click
      end
      object cb_color1: TColorBox
        Left = 8
        Top = 216
        Width = 145
        Height = 22
        NoneColorColor = clWhite
        Style = [cbStandardColors, cbExtendedColors]
        ItemHeight = 16
        TabOrder = 5
        OnExit = cb_color1Exit
      end
      object ColorBox1: TColorBox
        Left = 8
        Top = 272
        Width = 145
        Height = 22
        NoneColorColor = clWhite
        Style = [cbStandardColors, cbExtendedColors]
        ItemHeight = 16
        TabOrder = 6
      end
      object TrackBar1: TTrackBar
        Left = 168
        Top = 272
        Width = 225
        Height = 45
        Max = 255
        Orientation = trHorizontal
        Frequency = 25
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 7
        TickMarks = tmBottomRight
        TickStyle = tsAuto
      end
      object DBEdit3: TDBEdit
        Left = 8
        Top = 344
        Width = 353
        Height = 21
        DataField = 'planePathFile'
        DataSource = fte_config
        TabOrder = 8
      end
      object DBRadioGroup2: TDBRadioGroup
        Left = 168
        Top = 192
        Width = 193
        Height = 49
        Caption = ' Tail Length '
        Columns = 3
        DataField = 'updateRate'
        DataSource = fte_config
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Items.Strings = (
          '5'
          '10'
          '15')
        ParentFont = False
        TabOrder = 9
        Values.Strings = (
          '1'
          '2'
          '3'
          '4'
          '5')
      end
      object DBEdit4: TDBEdit
        Left = 8
        Top = 392
        Width = 353
        Height = 21
        DataField = 'planePathFile'
        DataSource = fte_config
        TabOrder = 10
      end
      object BitBtn2: TBitBtn
        Left = 144
        Top = 528
        Width = 75
        Height = 25
        Caption = 'BitBtn1'
        TabOrder = 11
        OnClick = BitBtn2Click
      end
    end
    object ts_telemetry: TTabSheet
      Caption = 'Telemetry'
      ImageIndex = 1
    end
    object TabSheet3: TTabSheet
      Caption = 'Ap Configuration'
      ImageIndex = 2
    end
    object TabSheet1: TTabSheet
      Caption = 'Data Plots'
      ImageIndex = 3
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 601
    Align = alLeft
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 103
      Height = 13
      Caption = 'Diagnose Window'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object bt_clear: TSpeedButton
      Left = 8
      Top = 568
      Width = 185
      Height = 22
      Caption = 'Clear the Diagnose Window'
      Flat = True
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
        55555FFFFFFF5F55FFF5777777757559995777777775755777F7555555555550
        305555555555FF57F7F555555550055BB0555555555775F777F55555550FB000
        005555555575577777F5555550FB0BF0F05555555755755757F555550FBFBF0F
        B05555557F55557557F555550BFBF0FB005555557F55575577F555500FBFBFB0
        B05555577F555557F7F5550E0BFBFB00B055557575F55577F7F550EEE0BFB0B0
        B05557FF575F5757F7F5000EEE0BFBF0B055777FF575FFF7F7F50000EEE00000
        B0557777FF577777F7F500000E055550805577777F7555575755500000555555
        05555777775555557F5555000555555505555577755555557555}
      NumGlyphs = 2
      OnClick = bt_clearClick
    end
    object mm_diagnose: TMemo
      Left = 8
      Top = 32
      Width = 177
      Height = 529
      TabOrder = 0
    end
  end
  object FormStorage1: TFormStorage
    IniFileName = '.\ap.ini'
    StoredProps.Strings = (
      'mm_diagnose.Lines'
      'pc_main.ActivePage')
    StoredValues = <>
    Left = 32
    Top = 520
  end
  object ad_main: TABSDatabase
    Connected = True
    CurrentVersion = '5.18 '
    DatabaseFileName = '.\apConfig.ABS'
    DatabaseName = 'apMain'
    Exclusive = False
    MaxConnections = 500
    MultiUser = False
    SessionName = 'Default'
    Left = 24
    Top = 456
  end
  object tb_config: TABSTable
    CurrentVersion = '5.18 '
    DatabaseName = 'apMain'
    SessionName = 'Default'
    InMemory = False
    ReadOnly = False
    TableName = 'configuration'
    Exclusive = False
    Left = 88
    Top = 456
    object tb_configkmlFile: TStringField
      FieldName = 'kmlFile'
      Size = 500
    end
    object tb_configplanePathFile: TStringField
      FieldName = 'planePathFile'
      Size = 500
    end
    object tb_configupdateRate: TSmallintField
      FieldName = 'updateRate'
    end
    object tb_configtessellate: TSmallintField
      FieldName = 'tessellate'
    end
    object tb_configtrajectoryColorR: TIntegerField
      FieldName = 'trajectoryColorR'
    end
    object tb_configtrajectoryColorG: TIntegerField
      FieldName = 'trajectoryColorG'
    end
    object tb_configtrajectoryColorB: TIntegerField
      FieldName = 'trajectoryColorB'
    end
    object tb_configtailLength: TSmallintField
      FieldName = 'tailLength'
    end
    object tb_configtessalateColorR: TIntegerField
      FieldName = 'tessalateColorR'
    end
    object tb_configtessalateColorG: TIntegerField
      FieldName = 'tessalateColorG'
    end
    object tb_configtessalateColorB: TIntegerField
      FieldName = 'tessalateColorB'
    end
    object tb_configtessalateTransparency: TSmallintField
      FieldName = 'tessalateTransparency'
    end
    object tb_configiconFile: TStringField
      FieldName = 'iconFile'
      Size = 500
    end
    object tb_configwaypointFile: TStringField
      FieldName = 'waypointFile'
      Size = 500
    end
  end
  object fte_config: TDataSource
    DataSet = tb_config
    Left = 88
    Top = 520
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    Left = 96
    Top = 400
  end
  object od_mainKml: TSaveDialog
    DefaultExt = '*.kml'
    Filter = 'Google Earth KML FIles|*.kml'
    InitialDir = '.'
    Left = 64
    Top = 328
  end
end
