object FPpal: TFPpal
  Left = 296
  Top = 133
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'UCSC - AP Ground Station'
  ClientHeight = 617
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
    Top = 598
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
    Height = 598
    ActivePage = TabSheet1
    Align = alClient
    TabIndex = 3
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
        OnClick = bt_ppKmlClick
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
        Tag = 1
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
      object bt_gearth: TSpeedButton
        Left = 8
        Top = 544
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
        OnClick = bt_gearthClick
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
      object bt_icon: TSpeedButton
        Tag = 2
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
        Tag = 3
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
      object rg_uprate: TDBRadioGroup
        Left = 8
        Top = 104
        Width = 377
        Height = 49
        Caption = ' Update Period (in Secs) '
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
        OnExit = rg_tailExit
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
      object cb_color1: TColorBox
        Left = 8
        Top = 216
        Width = 145
        Height = 22
        NoneColorColor = clWhite
        Style = [cbStandardColors, cbExtendedColors]
        ItemHeight = 16
        TabOrder = 4
        OnExit = cb_color1Exit
      end
      object cb_color2: TColorBox
        Left = 8
        Top = 272
        Width = 145
        Height = 22
        NoneColorColor = clWhite
        Style = [cbStandardColors, cbExtendedColors]
        ItemHeight = 16
        TabOrder = 5
        OnExit = cb_color2Exit
      end
      object kb_tessalate: TTrackBar
        Left = 168
        Top = 272
        Width = 225
        Height = 45
        Max = 255
        Orientation = trHorizontal
        Frequency = 25
        Position = 10
        SelEnd = 0
        SelStart = 0
        TabOrder = 6
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnExit = kb_tessalateExit
      end
      object DBEdit3: TDBEdit
        Left = 8
        Top = 344
        Width = 353
        Height = 21
        DataField = 'iconFile'
        DataSource = fte_config
        TabOrder = 7
      end
      object rg_tail: TDBRadioGroup
        Left = 168
        Top = 192
        Width = 193
        Height = 49
        Caption = ' Tail Length '
        Columns = 3
        DataField = 'tailLength'
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
        TabOrder = 8
        OnExit = rg_tailExit
      end
      object bt_wp: TDBEdit
        Left = 8
        Top = 392
        Width = 353
        Height = 21
        DataField = 'waypointFile'
        DataSource = fte_config
        TabOrder = 9
      end
    end
    object ts_telemetry: TTabSheet
      Caption = 'Telemetry'
      ImageIndex = 1
      object bt_serial: TSpeedButton
        Left = 8
        Top = 536
        Width = 401
        Height = 22
        Caption = 'Open Serial Port'
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003B3000000000
          003B37F77777777777F73BB09111111110BB3777F3F3F3F3F777311098080808
          10B33777F7373737377313309999999910337F373F3F3F3F3733133309808089
          03337F3373737373733313333099999033337FFFF7FFFFF7FFFFB011B0000000
          BBBB7777777777777777B01110BBBBB0BBBB77F37777777777773011108BB333
          333337F337377F3FFFF33099111BB3010033373F33777F77773F331999100101
          11033373FFF77773337F33300099991999033337773FFFF33373333BB7100199
          113333377377773FF7F333BB333BB7011B33337733377F7777FF3BB3333BB333
          3BB3377333377F33377FBB33333BB33333BB7733333773333377}
        NumGlyphs = 2
        OnClick = bt_serialClick
      end
      object ld_serial: TAbLED
        Left = 141
        Top = 531
        Width = 17
        Height = 33
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        LED_Position = lpLeft
        Spacing = 5
        Checked = False
        Flashing = False
        Frequency = ff1Hz
        StatusInt = 0
        StatusBit = 0
        GroupIndex = 0
        Mode = mIndicator
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 8
        Width = 401
        Height = 105
        Caption = ' GPS Data '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label9: TLabel
          Left = 8
          Top = 32
          Width = 28
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Time'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label10: TLabel
          Left = 8
          Top = 16
          Width = 32
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Date '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label11: TLabel
          Left = 176
          Top = 16
          Width = 47
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Latitude'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label12: TLabel
          Left = 176
          Top = 32
          Width = 57
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Longitude'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label13: TLabel
          Left = 176
          Top = 48
          Width = 38
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Height'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label14: TLabel
          Left = 8
          Top = 64
          Width = 27
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'COG'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label15: TLabel
          Left = 8
          Top = 80
          Width = 27
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'SOG'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label16: TLabel
          Left = 120
          Top = 64
          Width = 36
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'HDOP'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label17: TLabel
          Left = 120
          Top = 80
          Width = 24
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Fix?'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label18: TLabel
          Left = 240
          Top = 64
          Width = 38
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = '# Sats'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_date: TStaticText
          Left = 40
          Top = 16
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object et_time: TStaticText
          Left = 40
          Top = 32
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object et_lat: TStaticText
          Left = 240
          Top = 16
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object et_lon: TStaticText
          Left = 240
          Top = 32
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object et_height: TStaticText
          Left = 240
          Top = 48
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object et_sog: TStaticText
          Left = 40
          Top = 81
          Width = 73
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object et_cog: TStaticText
          Left = 40
          Top = 64
          Width = 73
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
        object et_hdop: TStaticText
          Left = 160
          Top = 64
          Width = 73
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object et_fix: TStaticText
          Left = 160
          Top = 81
          Width = 73
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
        end
        object et_sats: TStaticText
          Left = 288
          Top = 64
          Width = 73
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
      end
      object GroupBox2: TGroupBox
        Left = 7
        Top = 128
        Width = 401
        Height = 129
        Caption = ' Raw Sensor Data '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label20: TLabel
          Left = 8
          Top = 16
          Width = 45
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Accel X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label19: TLabel
          Left = 8
          Top = 32
          Width = 45
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Accel Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label24: TLabel
          Left = 8
          Top = 48
          Width = 45
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Accel Z'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label21: TLabel
          Left = 176
          Top = 14
          Width = 39
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gyro X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label22: TLabel
          Left = 176
          Top = 30
          Width = 39
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gyro Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label23: TLabel
          Left = 176
          Top = 46
          Width = 39
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gyro Z'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label25: TLabel
          Left = 8
          Top = 70
          Width = 37
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Mag X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label26: TLabel
          Left = 8
          Top = 86
          Width = 37
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Mag Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label27: TLabel
          Left = 8
          Top = 102
          Width = 37
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Mag Z'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_accelx: TStaticText
          Left = 56
          Top = 16
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object et_accely: TStaticText
          Left = 56
          Top = 32
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object et_accelz: TStaticText
          Left = 56
          Top = 48
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object et_gyrox: TStaticText
          Left = 224
          Top = 14
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object et_gyroy: TStaticText
          Left = 224
          Top = 30
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object et_gyroz: TStaticText
          Left = 224
          Top = 46
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object et_magx: TStaticText
          Left = 56
          Top = 70
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
        object et_magy: TStaticText
          Left = 56
          Top = 86
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object et_magz: TStaticText
          Left = 56
          Top = 102
          Width = 105
          Height = 17
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = 'No Data Available'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Ap Configuration'
      ImageIndex = 2
    end
    object TabSheet1: TTabSheet
      Caption = 'Data Plots'
      ImageIndex = 3
      object mt_x: TAbMiniTrend
        Left = 0
        Top = 72
        Width = 400
        Height = 159
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -19
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsUnderline]
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 0
        BevelInner.BevelLine = blNone
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 10
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 0
        DigitCh2 = 0
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '0000'
        SignalSettingsCh1.ValueTo = 4096
        SignalSettingsCh1.ValueUnit = ' '
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 4096
        SignalSettingsCh2.ValueUnit = 'Abs'
        TimeScale = 1
        Options = [opBevelInner, opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'X Axis'
        Flow = False
      end
      object mt_y: TAbMiniTrend
        Left = 0
        Top = 240
        Width = 400
        Height = 159
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -19
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsUnderline]
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 0
        BevelInner.BevelLine = blNone
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 10
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 0
        DigitCh2 = 0
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '0000'
        SignalSettingsCh1.ValueTo = 4096
        SignalSettingsCh1.ValueUnit = ' '
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 4096
        SignalSettingsCh2.ValueUnit = 'Abs'
        TimeScale = 1
        Options = [opBevelInner, opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'Y Axis'
        Flow = False
      end
      object mt_z: TAbMiniTrend
        Left = 0
        Top = 400
        Width = 400
        Height = 159
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -19
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsUnderline]
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 0
        BevelInner.BevelLine = blNone
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 10
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 0
        DigitCh2 = 0
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '0000'
        SignalSettingsCh1.ValueTo = 4096
        SignalSettingsCh1.ValueUnit = ' '
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 4096
        SignalSettingsCh2.ValueUnit = 'Abs'
        TimeScale = 1
        Options = [opBevelInner, opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'Z Axis'
        Flow = False
      end
      object rg_plot: TRadioGroup
        Left = 8
        Top = 8
        Width = 393
        Height = 57
        Caption = ' Select Sensor to Plot '
        Columns = 3
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ItemIndex = 0
        Items.Strings = (
          'Accelerometers'
          'Gyros'
          'Magnetometers')
        ParentFont = False
        TabOrder = 0
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 598
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
    OnTimer = Timer1Timer
    Left = 88
    Top = 400
  end
  object od_mainKml: TSaveDialog
    DefaultExt = '*.kml'
    Filter = 'Google Earth KML FIles|*.kml'
    InitialDir = '.'
    Left = 24
    Top = 400
  end
  object cp_serial: TApdComPort
    Baud = 115200
    AutoOpen = False
    DTR = False
    RTS = False
    Tracing = tlOn
    TraceName = 'APRO.TRC'
    TraceAllHex = True
    LogSize = 100000
    LogName = '.\ApLogHex.log'
    LogHex = False
    OnTriggerAvail = cp_serialTriggerAvail
    Left = 40
    Top = 328
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 200
    OnTimer = Timer2Timer
    Left = 136
    Top = 400
  end
end
