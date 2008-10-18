object FPpal: TFPpal
  Left = 292
  Top = 174
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'UCSC - AP Ground Station'
  ClientHeight = 616
  ClientWidth = 626
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
  object AbLED1: TAbLED
    Left = 400
    Top = 8
    Width = 73
    Height = 33
    Caption = 'AbLED1'
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
  object StatusBar1: TStatusBar
    Left = 0
    Top = 597
    Width = 626
    Height = 19
    Panels = <>
    SimplePanel = False
    SizeGrip = False
  end
  object pc_main: TPageControl
    Left = 201
    Top = 0
    Width = 425
    Height = 597
    ActivePage = TabSheet3
    Align = alClient
    TabIndex = 2
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
      object GroupBox3: TGroupBox
        Left = 8
        Top = 424
        Width = 385
        Height = 97
        Caption = ' Ground Station Location '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 10
        object Label28: TLabel
          Left = 8
          Top = 24
          Width = 80
          Height = 13
          Caption = 'Latitude (deg)'
        end
        object Label29: TLabel
          Left = 136
          Top = 24
          Width = 90
          Height = 13
          Caption = 'Longitude (deg)'
        end
        object Label30: TLabel
          Left = 260
          Top = 23
          Width = 59
          Height = 13
          Caption = 'Height (m)'
        end
        object bt_gspos: TSpeedButton
          Left = 8
          Top = 72
          Width = 369
          Height = 22
          Caption = 'Grab Current AP Position as Location'
          Flat = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003333330B7FFF
            FFB0333333777F3333773333330B7FFFFFB0333333777F3333773333330B7FFF
            FFB0333333777F3333773333330B7FFFFFB03FFFFF777FFFFF77000000000077
            007077777777777777770FFFFFFFF00077B07F33333337FFFF770FFFFFFFF000
            7BB07F3FF3FFF77FF7770F00F000F00090077F77377737777F770FFFFFFFF039
            99337F3FFFF3F7F777FF0F0000F0F09999937F7777373777777F0FFFFFFFF999
            99997F3FF3FFF77777770F00F000003999337F773777773777F30FFFF0FF0339
            99337F3FF7F3733777F30F08F0F0337999337F7737F73F7777330FFFF0039999
            93337FFFF7737777733300000033333333337777773333333333}
          NumGlyphs = 2
          ParentFont = False
          OnClick = bt_gsposClick
        end
        object DBEdit4: TDBEdit
          Left = 8
          Top = 40
          Width = 121
          Height = 21
          DataField = 'latGS'
          DataSource = fte_config
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
        end
        object DBEdit5: TDBEdit
          Left = 136
          Top = 40
          Width = 121
          Height = 21
          DataField = 'lonGS'
          DataSource = fte_config
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
        end
        object DBEdit6: TDBEdit
          Left = 260
          Top = 39
          Width = 121
          Height = 21
          DataField = 'heightGS'
          DataSource = fte_config
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
        end
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
        Left = 138
        Top = 531
        Width = 17
        Height = 33
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
      object ai_att: TAbVCInd
        Left = 80
        Top = 16
        Width = 225
        Height = 225
        BevelOuter.ColorFrom = clWhite
        BevelOuter.ColorTo = 7566195
        BevelOuter.Width = 2
        BevelMiddle.ColorFrom = 7566195
        BevelMiddle.ColorTo = clWhite
        BevelMiddle.Width = 2
        BevelInner.ColorFrom = clWhite
        BevelInner.ColorTo = 7566195
        BevelInner.Width = 2
        ArrShouldSize = 10
        ArrShouldOffs = 0
        ArrShouldCol = clRed
        ArrowSize = 10
        CourseScale.Font.Charset = DEFAULT_CHARSET
        CourseScale.Font.Color = clWhite
        CourseScale.Font.Height = -24
        CourseScale.Font.Name = 'Arial'
        CourseScale.Font.Style = [fsBold]
        CourseScale.StepLines.Pen.Color = clWhite
        CourseScale.StepLines.Pen.Width = 2
        CourseScale.StepLines.Length = 15
        CourseScale.SubStepLines.Pen.Color = clSilver
        CourseScale.SubStepLines.Length = 8
        CourseScale.TextAlignment = toMidCenter
        HorizonLine.Pen.Color = clWhite
        HorizonLine.Length = 100
        PitchLine.Pen.Color = clWhite
        PitchLine.Length = 50
        PitchScaleOffs = 10
        IndDeviation.FormatStr = '##0.0'
        IndDeviation.Bevel.ColorFrom = 7566195
        IndDeviation.Bevel.ColorTo = clWhite
        IndDeviation.Bevel.Width = 2
        IndDeviation.Caption.Text = 'Dev.'
        IndDeviation.Caption.Font.Charset = DEFAULT_CHARSET
        IndDeviation.Caption.Font.Color = clWindowText
        IndDeviation.Caption.Font.Height = -11
        IndDeviation.Caption.Font.Name = 'MS Sans Serif'
        IndDeviation.Caption.Font.Style = []
        IndDeviation.Caption.OffsetX = 0
        IndDeviation.Caption.OffsetY = 0
        IndDeviation.Caption.Pos = toBotCenter
        IndDeviation.Caption.Visible = True
        IndDeviation.Color = clBlack
        IndDeviation.Font.Charset = DEFAULT_CHARSET
        IndDeviation.Font.Color = clLime
        IndDeviation.Font.Height = -13
        IndDeviation.Font.Name = 'Arial'
        IndDeviation.Font.Style = [fsBold]
        IndDeviation.OffsetX = 0
        IndDeviation.OffsetY = 0
        IndDeviation.Visible = True
        IndCourse.FormatStr = '##0.0'
        IndCourse.Bevel.ColorFrom = 7566195
        IndCourse.Bevel.ColorTo = clWhite
        IndCourse.Bevel.Width = 2
        IndCourse.Caption.Text = 'Course'
        IndCourse.Caption.Font.Charset = DEFAULT_CHARSET
        IndCourse.Caption.Font.Color = clWindowText
        IndCourse.Caption.Font.Height = -11
        IndCourse.Caption.Font.Name = 'MS Sans Serif'
        IndCourse.Caption.Font.Style = []
        IndCourse.Caption.OffsetX = 0
        IndCourse.Caption.OffsetY = 0
        IndCourse.Caption.Pos = toTopCenter
        IndCourse.Caption.Visible = True
        IndCourse.Color = clBlack
        IndCourse.Font.Charset = DEFAULT_CHARSET
        IndCourse.Font.Color = clLime
        IndCourse.Font.Height = -13
        IndCourse.Font.Name = 'Arial'
        IndCourse.Font.Style = [fsBold]
        IndCourse.OffsetX = 0
        IndCourse.OffsetY = 0
        IndCourse.Visible = True
        IndPitch.FormatStr = '##0.0'
        IndPitch.Bevel.ColorFrom = 7566195
        IndPitch.Bevel.ColorTo = clWhite
        IndPitch.Bevel.Width = 2
        IndPitch.Caption.Text = 'Pitch'
        IndPitch.Caption.Font.Charset = DEFAULT_CHARSET
        IndPitch.Caption.Font.Color = clWindowText
        IndPitch.Caption.Font.Height = -11
        IndPitch.Caption.Font.Name = 'MS Sans Serif'
        IndPitch.Caption.Font.Style = []
        IndPitch.Caption.OffsetX = 0
        IndPitch.Caption.OffsetY = 0
        IndPitch.Caption.Pos = toTopCenter
        IndPitch.Caption.Visible = True
        IndPitch.Color = clBlack
        IndPitch.Font.Charset = DEFAULT_CHARSET
        IndPitch.Font.Color = clLime
        IndPitch.Font.Height = -13
        IndPitch.Font.Name = 'Arial'
        IndPitch.Font.Style = [fsBold]
        IndPitch.OffsetX = 0
        IndPitch.OffsetY = 0
        IndPitch.Visible = True
        IndRoll.FormatStr = '##0.0'
        IndRoll.Bevel.ColorFrom = 7566195
        IndRoll.Bevel.ColorTo = clWhite
        IndRoll.Bevel.Width = 2
        IndRoll.Caption.Text = 'Roll'
        IndRoll.Caption.Font.Charset = DEFAULT_CHARSET
        IndRoll.Caption.Font.Color = clWindowText
        IndRoll.Caption.Font.Height = -11
        IndRoll.Caption.Font.Name = 'MS Sans Serif'
        IndRoll.Caption.Font.Style = []
        IndRoll.Caption.OffsetX = 0
        IndRoll.Caption.OffsetY = 0
        IndRoll.Caption.Pos = toBotCenter
        IndRoll.Caption.Visible = True
        IndRoll.Color = clBlack
        IndRoll.Font.Charset = DEFAULT_CHARSET
        IndRoll.Font.Color = clLime
        IndRoll.Font.Height = -13
        IndRoll.Font.Name = 'Arial'
        IndRoll.Font.Style = [fsBold]
        IndRoll.OffsetX = 0
        IndRoll.OffsetY = 0
        IndRoll.Visible = True
        RollScale.Font.Charset = DEFAULT_CHARSET
        RollScale.Font.Color = clWhite
        RollScale.Font.Height = -24
        RollScale.Font.Name = 'Arial'
        RollScale.Font.Style = [fsBold]
        RollScale.StepLines.Pen.Color = clWhite
        RollScale.StepLines.Pen.Width = 2
        RollScale.StepLines.Length = 15
        RollScale.SubStepLines.Pen.Color = clSilver
        RollScale.SubStepLines.Length = 8
        RollScale.TextAlignment = toMidCenter
        ScaleHeight = 50
        Color = clBtnFace
        ColorSky = 16760767
        ColorGround = 36556
        CourseBkColor = clNavy
        RollBkColor = clMaroon
        OuterSpacing = 5
        InnerSpacing = 5
        PitchScale.SubStepAt = 1
        PitchScale.StepMulti = 5
        PitchScale.SubStepsVis = 15
        PitchScale.Font.Charset = DEFAULT_CHARSET
        PitchScale.Font.Color = clWhite
        PitchScale.Font.Height = -11
        PitchScale.Font.Name = 'Arial'
        PitchScale.Font.Style = [fsBold]
        PitchScale.FormatStr = '##0.#'
        PitchScale.StepLines.Pen.Color = clWhite
        PitchScale.StepLines.Pen.Width = 2
        PitchScale.StepLines.Length = 15
        PitchScale.SubStepLines.Pen.Color = clGray
        PitchScale.SubStepLines.Length = 8
        PitchScale.TextAlignment = toMidCenter
      end
      object ai_copy: TAbVCInd
        Left = 80
        Top = 280
        Width = 225
        Height = 225
        BevelOuter.ColorFrom = clWhite
        BevelOuter.ColorTo = 7566195
        BevelOuter.Width = 2
        BevelMiddle.ColorFrom = 7566195
        BevelMiddle.ColorTo = clWhite
        BevelMiddle.Width = 2
        BevelInner.ColorFrom = clWhite
        BevelInner.ColorTo = 7566195
        BevelInner.Width = 2
        ArrShouldSize = 10
        ArrShouldOffs = 0
        ArrShouldCol = clRed
        ArrowSize = 10
        CourseScale.Font.Charset = DEFAULT_CHARSET
        CourseScale.Font.Color = clWhite
        CourseScale.Font.Height = -24
        CourseScale.Font.Name = 'Arial'
        CourseScale.Font.Style = [fsBold]
        CourseScale.StepLines.Pen.Color = clWhite
        CourseScale.StepLines.Pen.Width = 2
        CourseScale.StepLines.Length = 15
        CourseScale.SubStepLines.Pen.Color = clSilver
        CourseScale.SubStepLines.Length = 8
        CourseScale.TextAlignment = toMidCenter
        HorizonLine.Pen.Color = clWhite
        HorizonLine.Length = 100
        PitchLine.Pen.Color = clWhite
        PitchLine.Length = 50
        PitchScaleOffs = 10
        IndDeviation.FormatStr = '##0.0'
        IndDeviation.Bevel.ColorFrom = 7566195
        IndDeviation.Bevel.ColorTo = clWhite
        IndDeviation.Bevel.Width = 2
        IndDeviation.Caption.Text = 'Dev.'
        IndDeviation.Caption.Font.Charset = DEFAULT_CHARSET
        IndDeviation.Caption.Font.Color = clWindowText
        IndDeviation.Caption.Font.Height = -11
        IndDeviation.Caption.Font.Name = 'MS Sans Serif'
        IndDeviation.Caption.Font.Style = []
        IndDeviation.Caption.OffsetX = 0
        IndDeviation.Caption.OffsetY = 0
        IndDeviation.Caption.Pos = toBotCenter
        IndDeviation.Caption.Visible = True
        IndDeviation.Color = clBlack
        IndDeviation.Font.Charset = DEFAULT_CHARSET
        IndDeviation.Font.Color = clLime
        IndDeviation.Font.Height = -13
        IndDeviation.Font.Name = 'Arial'
        IndDeviation.Font.Style = [fsBold]
        IndDeviation.OffsetX = 0
        IndDeviation.OffsetY = 0
        IndDeviation.Visible = True
        IndCourse.FormatStr = '##0.0'
        IndCourse.Bevel.ColorFrom = 7566195
        IndCourse.Bevel.ColorTo = clWhite
        IndCourse.Bevel.Width = 2
        IndCourse.Caption.Text = 'Course'
        IndCourse.Caption.Font.Charset = DEFAULT_CHARSET
        IndCourse.Caption.Font.Color = clWindowText
        IndCourse.Caption.Font.Height = -11
        IndCourse.Caption.Font.Name = 'MS Sans Serif'
        IndCourse.Caption.Font.Style = []
        IndCourse.Caption.OffsetX = 0
        IndCourse.Caption.OffsetY = 0
        IndCourse.Caption.Pos = toTopCenter
        IndCourse.Caption.Visible = True
        IndCourse.Color = clBlack
        IndCourse.Font.Charset = DEFAULT_CHARSET
        IndCourse.Font.Color = clLime
        IndCourse.Font.Height = -13
        IndCourse.Font.Name = 'Arial'
        IndCourse.Font.Style = [fsBold]
        IndCourse.OffsetX = 0
        IndCourse.OffsetY = 0
        IndCourse.Visible = True
        IndPitch.FormatStr = '##0.0'
        IndPitch.Bevel.ColorFrom = 7566195
        IndPitch.Bevel.ColorTo = clWhite
        IndPitch.Bevel.Width = 2
        IndPitch.Caption.Text = 'Pitch'
        IndPitch.Caption.Font.Charset = DEFAULT_CHARSET
        IndPitch.Caption.Font.Color = clWindowText
        IndPitch.Caption.Font.Height = -11
        IndPitch.Caption.Font.Name = 'MS Sans Serif'
        IndPitch.Caption.Font.Style = []
        IndPitch.Caption.OffsetX = 0
        IndPitch.Caption.OffsetY = 0
        IndPitch.Caption.Pos = toTopCenter
        IndPitch.Caption.Visible = True
        IndPitch.Color = clBlack
        IndPitch.Font.Charset = DEFAULT_CHARSET
        IndPitch.Font.Color = clLime
        IndPitch.Font.Height = -13
        IndPitch.Font.Name = 'Arial'
        IndPitch.Font.Style = [fsBold]
        IndPitch.OffsetX = 0
        IndPitch.OffsetY = 0
        IndPitch.Visible = True
        IndRoll.FormatStr = '##0.0'
        IndRoll.Bevel.ColorFrom = 7566195
        IndRoll.Bevel.ColorTo = clWhite
        IndRoll.Bevel.Width = 2
        IndRoll.Caption.Text = 'Roll'
        IndRoll.Caption.Font.Charset = DEFAULT_CHARSET
        IndRoll.Caption.Font.Color = clWindowText
        IndRoll.Caption.Font.Height = -11
        IndRoll.Caption.Font.Name = 'MS Sans Serif'
        IndRoll.Caption.Font.Style = []
        IndRoll.Caption.OffsetX = 0
        IndRoll.Caption.OffsetY = 0
        IndRoll.Caption.Pos = toBotCenter
        IndRoll.Caption.Visible = True
        IndRoll.Color = clBlack
        IndRoll.Font.Charset = DEFAULT_CHARSET
        IndRoll.Font.Color = clLime
        IndRoll.Font.Height = -13
        IndRoll.Font.Name = 'Arial'
        IndRoll.Font.Style = [fsBold]
        IndRoll.OffsetX = 0
        IndRoll.OffsetY = 0
        IndRoll.Visible = True
        RollScale.Font.Charset = DEFAULT_CHARSET
        RollScale.Font.Color = clWhite
        RollScale.Font.Height = -24
        RollScale.Font.Name = 'Arial'
        RollScale.Font.Style = [fsBold]
        RollScale.StepLines.Pen.Color = clWhite
        RollScale.StepLines.Pen.Width = 2
        RollScale.StepLines.Length = 15
        RollScale.SubStepLines.Pen.Color = clSilver
        RollScale.SubStepLines.Length = 8
        RollScale.TextAlignment = toMidCenter
        ScaleHeight = 50
        Color = clBtnFace
        ColorSky = 16760767
        ColorGround = 36556
        CourseBkColor = clNavy
        RollBkColor = clMaroon
        OuterSpacing = 5
        InnerSpacing = 5
        PitchScale.SubStepAt = 1
        PitchScale.StepMulti = 5
        PitchScale.SubStepsVis = 15
        PitchScale.Font.Charset = DEFAULT_CHARSET
        PitchScale.Font.Color = clWhite
        PitchScale.Font.Height = -11
        PitchScale.Font.Name = 'Arial'
        PitchScale.Font.Style = [fsBold]
        PitchScale.FormatStr = '##0.#'
        PitchScale.StepLines.Pen.Color = clWhite
        PitchScale.StepLines.Pen.Width = 2
        PitchScale.StepLines.Length = 15
        PitchScale.SubStepLines.Pen.Color = clGray
        PitchScale.SubStepLines.Length = 8
        PitchScale.TextAlignment = toMidCenter
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Data Plots'
      ImageIndex = 3
      object mt_x: TAbMiniTrend
        Left = 0
        Top = 64
        Width = 400
        Height = 160
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
        BevelOuter.BevelLine = blNone
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 2867
        DigitCh2 = 300
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'X Axis'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 70
        ValueCh2 = 30
        TimeScale = 1
        Options = [opBevelOuter, opCaption, opScaleCh1, opTimeLine]
        Caption = 'X Axis'
        Flow = False
      end
      object mt_y: TAbMiniTrend
        Left = 0
        Top = 226
        Width = 400
        Height = 160
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
        BevelOuter.BevelLine = blNone
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 2867
        DigitCh2 = 300
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'X Axis'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 70
        ValueCh2 = 30
        TimeScale = 1
        Options = [opBevelOuter, opCaption, opScaleCh1, opTimeLine]
        Caption = 'Y Axis'
        Flow = False
      end
      object mt_z: TAbMiniTrend
        Left = 8
        Top = 392
        Width = 400
        Height = 160
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
        BevelOuter.BevelLine = blNone
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        DigitCh1 = 2867
        DigitCh2 = 300
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'X Axis'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 70
        ValueCh2 = 30
        TimeScale = 1
        Options = [opBevelOuter, opCaption, opScaleCh1, opTimeLine]
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
    Height = 597
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
    StoreDefs = True
    FieldDefs = <
      item
        Name = 'kmlFile'
        DataType = ftString
        Size = 500
      end
      item
        Name = 'planePathFile'
        DataType = ftString
        Size = 500
      end
      item
        Name = 'updateRate'
        DataType = ftSmallint
      end
      item
        Name = 'tessellate'
        DataType = ftSmallint
      end
      item
        Name = 'trajectoryColorR'
        DataType = ftInteger
      end
      item
        Name = 'trajectoryColorG'
        DataType = ftInteger
      end
      item
        Name = 'trajectoryColorB'
        DataType = ftInteger
      end
      item
        Name = 'tailLength'
        DataType = ftSmallint
      end
      item
        Name = 'tessalateColorR'
        DataType = ftInteger
      end
      item
        Name = 'tessalateColorG'
        DataType = ftInteger
      end
      item
        Name = 'tessalateColorB'
        DataType = ftInteger
      end
      item
        Name = 'tessalateTransparency'
        DataType = ftInteger
      end
      item
        Name = 'iconFile'
        DataType = ftString
        Size = 500
      end
      item
        Name = 'waypointFile'
        DataType = ftString
        Size = 500
      end
      item
        Name = 'latGS'
        DataType = ftFloat
      end
      item
        Name = 'lonGS'
        DataType = ftFloat
      end
      item
        Name = 'heightGS'
        DataType = ftFloat
      end>
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
    object tb_configtessalateTransparency: TIntegerField
      FieldName = 'tessalateTransparency'
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
    object tb_configiconFile: TStringField
      FieldName = 'iconFile'
      Size = 500
    end
    object tb_configwaypointFile: TStringField
      FieldName = 'waypointFile'
      Size = 500
    end
    object tb_configlatGS: TFloatField
      FieldName = 'latGS'
    end
    object tb_configlonGS: TFloatField
      FieldName = 'lonGS'
    end
    object tb_configheightGS: TFloatField
      FieldName = 'heightGS'
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
    TraceName = '.\APRO.TRC'
    TraceAllHex = True
    Logging = tlOn
    LogSize = 100000
    LogName = '.\ApLogHex.log'
    LogAllHex = True
    OnTriggerAvail = cp_serialTriggerAvail
    Left = 40
    Top = 328
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 136
    Top = 400
  end
end
