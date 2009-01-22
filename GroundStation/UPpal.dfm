object FPpal: TFPpal
  Left = 79
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 
    '                                                       SLUGS Gro' +
    'und Station'
  ClientHeight = 716
  ClientWidth = 576
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 697
    Width = 576
    Height = 19
    Panels = <
      item
        Width = 200
      end
      item
        Text = 'Graphical Components by: Abakus VCL (www.abaecker.biz)'
        Width = 355
      end>
    SimplePanel = False
    SizeGrip = False
  end
  object pc_main: TPageControl
    Left = 201
    Top = 25
    Width = 375
    Height = 672
    ActivePage = ts_pid
    Align = alClient
    MultiLine = True
    TabIndex = 1
    TabOrder = 1
    object ts_ge: TTabSheet
      Caption = 'Google Earth'
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
        Left = 338
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
        Left = 338
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
        Top = 592
        Width = 350
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
        Width = 111
        Height = 13
        Hint = 
          'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
          'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
          ' which such path is refreshed'
        Caption = 'AC Trajectory Color'
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
        Left = 151
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
        Left = 333
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
        Left = 333
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
        Width = 330
        Height = 21
        DataField = 'kmlFile'
        DataSource = fte_config
        TabOrder = 0
      end
      object DBEdit2: TDBEdit
        Left = 8
        Top = 72
        Width = 330
        Height = 21
        DataField = 'planePathFile'
        DataSource = fte_config
        TabOrder = 1
      end
      object rg_uprate: TDBRadioGroup
        Left = 8
        Top = 104
        Width = 345
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
        Width = 113
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
        Width = 113
        Height = 22
        NoneColorColor = clWhite
        Style = [cbStandardColors, cbExtendedColors]
        ItemHeight = 16
        TabOrder = 5
        OnExit = cb_color2Exit
      end
      object kb_tessalate: TTrackBar
        Left = 135
        Top = 272
        Width = 212
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
        Width = 326
        Height = 21
        DataField = 'iconFile'
        DataSource = fte_config
        TabOrder = 7
      end
      object rg_tail: TDBRadioGroup
        Left = 135
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
        Width = 326
        Height = 21
        DataField = 'waypointFile'
        DataSource = fte_config
        TabOrder = 9
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 424
        Width = 353
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
          Left = 119
          Top = 24
          Width = 90
          Height = 13
          Caption = 'Longitude (deg)'
        end
        object Label30: TLabel
          Left = 232
          Top = 23
          Width = 59
          Height = 13
          Caption = 'Height (m)'
        end
        object bt_gspos: TSpeedButton
          Left = 8
          Top = 72
          Width = 339
          Height = 22
          Caption = 'Grab Current AP Position as GS  Location'
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
          Width = 106
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
          Left = 119
          Top = 40
          Width = 106
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
          Left = 232
          Top = 39
          Width = 106
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
    object ts_pid: TTabSheet
      Caption = 'PID'
      ImageIndex = 2
      object gb_pid1: TGroupBox
        Left = 8
        Top = 9
        Width = 169
        Height = 97
        Caption = ' PID Loop 1  '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label88: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label89: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label90: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object bt_up1: TSpeedButton
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object bt_down1: TSpeedButton
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p1: TCurrencyEdit
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i1: TCurrencyEdit
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d1: TCurrencyEdit
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object et_p1: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object et_i1: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object et_d1: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid2: TGroupBox
        Tag = 1
        Left = 192
        Top = 9
        Width = 169
        Height = 97
        Caption = ' PID Loop 2'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label91: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label92: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label93: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton1: TSpeedButton
          Tag = 1
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton2: TSpeedButton
          Tag = 1
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p2: TCurrencyEdit
          Tag = 1
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i2: TCurrencyEdit
          Tag = 1
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d2: TCurrencyEdit
          Tag = 1
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText1: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText2: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText3: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid3: TGroupBox
        Tag = 2
        Left = 8
        Top = 113
        Width = 169
        Height = 97
        Caption = ' PID Loop 3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        object Label94: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label95: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label96: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton4: TSpeedButton
          Tag = 2
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton5: TSpeedButton
          Tag = 2
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p3: TCurrencyEdit
          Tag = 2
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i3: TCurrencyEdit
          Tag = 2
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d3: TCurrencyEdit
          Tag = 2
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText4: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText5: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText6: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid4: TGroupBox
        Tag = 3
        Left = 190
        Top = 113
        Width = 169
        Height = 97
        Caption = ' PID Loop 4'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        object Label97: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label98: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label99: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton6: TSpeedButton
          Tag = 3
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton7: TSpeedButton
          Tag = 3
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p4: TCurrencyEdit
          Tag = 3
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i4: TCurrencyEdit
          Tag = 3
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d4: TCurrencyEdit
          Tag = 3
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText7: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText8: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText9: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid5: TGroupBox
        Tag = 4
        Left = 8
        Top = 217
        Width = 169
        Height = 97
        Caption = ' PID Loop 5'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        object Label100: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label101: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label102: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton8: TSpeedButton
          Tag = 4
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton9: TSpeedButton
          Tag = 4
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p5: TCurrencyEdit
          Tag = 4
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i5: TCurrencyEdit
          Tag = 4
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d5: TCurrencyEdit
          Tag = 4
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText10: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText11: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText12: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid6: TGroupBox
        Tag = 5
        Left = 190
        Top = 217
        Width = 169
        Height = 97
        Caption = ' PID Loop 6'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
        object Label103: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label104: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label105: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton10: TSpeedButton
          Tag = 5
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton11: TSpeedButton
          Tag = 5
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p6: TCurrencyEdit
          Tag = 5
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i6: TCurrencyEdit
          Tag = 5
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d6: TCurrencyEdit
          Tag = 5
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText13: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText14: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText15: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid7: TGroupBox
        Tag = 6
        Left = 8
        Top = 321
        Width = 169
        Height = 97
        Caption = ' PID Loop 7'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        object Label106: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label107: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label108: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton12: TSpeedButton
          Tag = 6
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton13: TSpeedButton
          Tag = 6
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p7: TCurrencyEdit
          Tag = 6
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i7: TCurrencyEdit
          Tag = 6
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d7: TCurrencyEdit
          Tag = 6
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText16: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText17: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText18: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid8: TGroupBox
        Tag = 7
        Left = 190
        Top = 321
        Width = 169
        Height = 97
        Caption = ' PID Loop 8'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        object Label109: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label110: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label111: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton14: TSpeedButton
          Tag = 7
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton15: TSpeedButton
          Tag = 7
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p8: TCurrencyEdit
          Tag = 7
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i8: TCurrencyEdit
          Tag = 7
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d8: TCurrencyEdit
          Tag = 7
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText19: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText20: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText21: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid9: TGroupBox
        Tag = 8
        Left = 8
        Top = 425
        Width = 169
        Height = 97
        Caption = ' PID Loop 9'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
        object Label112: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label113: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label114: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton16: TSpeedButton
          Tag = 8
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton17: TSpeedButton
          Tag = 8
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p9: TCurrencyEdit
          Tag = 8
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i9: TCurrencyEdit
          Tag = 8
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d9: TCurrencyEdit
          Tag = 8
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText22: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText23: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText24: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object gb_pid10: TGroupBox
        Tag = 9
        Left = 190
        Top = 425
        Width = 169
        Height = 97
        Caption = ' PID Loop 10  '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
        object Label115: TLabel
          Left = 8
          Top = 19
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label116: TLabel
          Left = 8
          Top = 51
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'D'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label117: TLabel
          Left = 8
          Top = 35
          Width = 5
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'I'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object SpeedButton18: TSpeedButton
          Tag = 9
          Left = 9
          Top = 69
          Width = 70
          Height = 22
          Caption = 'Set'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003C3333339333
            337437FFF3337F3333F73CCC33339333344437773F337F33377733CCC3339337
            4447337F73FF7F3F337F33CCCCC3934444433373F7737F773373333CCCCC9444
            44733337F337773337F3333CCCCC9444443333373F337F3337333333CCCC9444
            473333337F337F337F333333CCCC94444333333373F37F33733333333CCC9444
            7333333337F37F37F33333333CCC944433333333373F7F373333333333CC9447
            33333333337F7F7F3333333333CC94433333333333737F7333333333333C9473
            33333333333737F333333333333C943333333333333737333333333333339733
            3333333333337F33333333333333933333333333333373333333}
          NumGlyphs = 2
          OnClick = bt_up1Click
        end
        object SpeedButton19: TSpeedButton
          Tag = 9
          Left = 91
          Top = 67
          Width = 70
          Height = 22
          Caption = 'Get'
          Flat = True
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
            333333333337F3333333333333397333333333333337FF333333333333C94333
            3333333333737F333333333333C9473333333333337373F3333333333CC94433
            3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
            333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
            33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
            4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
            443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
            444377733337F333777FC3333339333337437333333733333373}
          NumGlyphs = 2
          OnClick = bt_down1Click
        end
        object ed_p10: TCurrencyEdit
          Tag = 9
          Left = 24
          Top = 17
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 0
          OnChange = ed_p1Change
        end
        object ed_i10: TCurrencyEdit
          Tag = 9
          Left = 24
          Top = 33
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 1
          OnChange = ed_p1Change
        end
        object ed_d10: TCurrencyEdit
          Tag = 9
          Left = 24
          Top = 49
          Width = 65
          Height = 18
          AutoSize = False
          DisplayFormat = ' ,00.0000;- ,00.0000'
          TabOrder = 2
          OnChange = ed_p1Change
        end
        object StaticText25: TStaticText
          Left = 92
          Top = 17
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object StaticText26: TStaticText
          Left = 92
          Top = 33
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object StaticText27: TStaticText
          Left = 92
          Top = 49
          Width = 67
          Height = 18
          AutoSize = False
          BevelInner = bvNone
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSunken
          Caption = '0.0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
      end
      object GroupBox8: TGroupBox
        Left = 5
        Top = 536
        Width = 350
        Height = 72
        Caption = ' Diagnostic Messages'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 10
        object Fl1: TLabel
          Left = 8
          Top = 16
          Width = 18
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Fl1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label53: TLabel
          Left = 8
          Top = 32
          Width = 18
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Fl2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label54: TLabel
          Left = 8
          Top = 48
          Width = 18
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Fl3'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label55: TLabel
          Left = 176
          Top = 14
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Sh1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label56: TLabel
          Left = 176
          Top = 30
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Sh2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label57: TLabel
          Left = 176
          Top = 46
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Sh3'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_fl1: TStaticText
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
        object et_fl2: TStaticText
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
        object et_fl3: TStaticText
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
        object et_sh1: TStaticText
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
        object et_sh2: TStaticText
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
        object et_sh3: TStaticText
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
      end
    end
    object ts_export: TTabSheet
      Caption = 'Export'
      ImageIndex = 5
      object GroupBox5: TGroupBox
        Left = 8
        Top = 16
        Width = 353
        Height = 97
        Caption = ' In-Flight Exporting '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label43: TLabel
          Left = 8
          Top = 45
          Width = 155
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Directory for Exported Files'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object cb_inflight: TCheckBox
          Left = 8
          Top = 24
          Width = 273
          Height = 17
          Caption = 'Export Telemetry as it Comes from the UAV'
          TabOrder = 0
          OnClick = cb_inflightClick
        end
        object ed_liveLog: TFilenameEdit
          Left = 8
          Top = 59
          Width = 329
          Height = 21
          OnAfterDialog = ed_liveLogAfterDialog
          Filter = 'Log Files (*.txt)|*.txt'
          DialogTitle = 'Select Log File...'
          Enabled = False
          GlyphKind = gkCustom
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
            333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
            0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
            0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
            33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
            B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
            3BB33773333773333773B333333B3333333B7333333733333337}
          NumGlyphs = 2
          TabOrder = 1
          Text = 'C:\Mariano\UCSC\APCode\GroundStation\FlightLogs\cartTest'
        end
      end
      object GroupBox6: TGroupBox
        Left = 8
        Top = 152
        Width = 353
        Height = 145
        Caption = ' Exporting Log Files '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label44: TLabel
          Left = 8
          Top = 21
          Width = 86
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Select Log File'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object bt_importLog: TSpeedButton
          Left = 7
          Top = 112
          Width = 330
          Height = 22
          Caption = 'Process Log File'
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
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            333333333333333333FF33333333333330003333333333333777333333333333
            300033FFFFFF3333377739999993333333333777777F3333333F399999933333
            3300377777733333337733333333333333003333333333333377333333333333
            3333333333333333333F333333333333330033333F33333333773333C3333333
            330033337F3333333377333CC3333333333333F77FFFFFFF3FF33CCCCCCCCCC3
            993337777777777F77F33CCCCCCCCCC399333777777777737733333CC3333333
            333333377F33333333FF3333C333333330003333733333333777333333333333
            3000333333333333377733333333333333333333333333333333}
          NumGlyphs = 2
          ParentFont = False
          OnClick = bt_importLogClick
        end
        object Label45: TLabel
          Left = 10
          Top = 68
          Width = 95
          Height = 13
          Caption = 'CSV Output File '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object ed_importLog: TFilenameEdit
          Left = 8
          Top = 35
          Width = 329
          Height = 21
          Filter = 'Log Files (*.txt)|*.txt'
          DialogTitle = 'Select Log File...'
          GlyphKind = gkCustom
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
            333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
            0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
            0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
            33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
            B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
            3BB33773333773333773B333333B3333333B7333333733333337}
          NumGlyphs = 2
          TabOrder = 0
          Text = 'E:\LOG4.TXT'
        end
        object ed_exportMat: TFilenameEdit
          Left = 7
          Top = 83
          Width = 330
          Height = 21
          Filter = 'CSV Files (*.csv)|*.csv'
          DialogTitle = 'Select Log File...'
          GlyphKind = gkCustom
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
            333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
            0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333337F33333337F333330FFFFFFFF07333337F33333337F333330FFFFFFFF
            07333FF7F33333337FFFBBB0FFFFFFFF0BB37777F3333333777F3BB0FFFFFFFF
            0BBB3777F3333FFF77773330FFFF000003333337F333777773333330FFFF0FF0
            33333337F3337F37F3333330FFFF0F0B33333337F3337F77FF333330FFFF003B
            B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
            3BB33773333773333773B333333B3333333B7333333733333337}
          NumGlyphs = 2
          TabOrder = 1
          Text = 'C:\Mariano\UCSC\APCode\GroundStation\FlightLogs\ST.csv'
        end
      end
    end
    object tsHil: TTabSheet
      Caption = 'HIl Config'
      ImageIndex = 6
      object GroupBox11: TGroupBox
        Left = 8
        Top = 112
        Width = 353
        Height = 97
        Caption = ' UDP Send  Connection '
        TabOrder = 0
        object et_connSend: TLabel
          Left = 8
          Top = 54
          Width = 75
          Height = 13
          Caption = 'Not Connected '
        end
        object Label64: TLabel
          Left = 224
          Top = 27
          Width = 44
          Height = 13
          Caption = 'UDP port'
        end
        object Label65: TLabel
          Left = 232
          Top = 51
          Width = 31
          Height = 13
          Caption = 'Server'
        end
        object et_sent: TLabel
          Left = 8
          Top = 70
          Width = 65
          Height = 13
          Caption = 'No Data Sent'
        end
        object bt_startSend: TButton
          Left = 8
          Top = 24
          Width = 75
          Height = 25
          Caption = '&Start'
          Default = True
          TabOrder = 0
          OnClick = bt_startSendClick
        end
        object bt_stopSend: TButton
          Left = 88
          Top = 24
          Width = 75
          Height = 25
          Caption = 'S&top'
          TabOrder = 1
          OnClick = bt_stopSendClick
        end
        object ed_portSend: TEdit
          Left = 280
          Top = 24
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5678'
        end
        object ed_hostSend: TEdit
          Left = 280
          Top = 48
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '255.255.255.255'
        end
      end
      object GroupBox12: TGroupBox
        Left = 8
        Top = 8
        Width = 353
        Height = 97
        Caption = ' UDP Receive  Connection '
        TabOrder = 1
        object DataAvailableLabel: TLabel
          Left = 8
          Top = 72
          Width = 86
          Height = 13
          Caption = 'No Data Available'
        end
        object InfoLabel: TLabel
          Left = 8
          Top = 56
          Width = 75
          Height = 13
          Caption = 'Not Connected '
        end
        object Label66: TLabel
          Left = 224
          Top = 27
          Width = 44
          Height = 13
          Caption = 'UDP port'
        end
        object Label67: TLabel
          Left = 232
          Top = 51
          Width = 31
          Height = 13
          Caption = 'Server'
        end
        object StartButton: TButton
          Left = 8
          Top = 24
          Width = 75
          Height = 25
          Caption = '&Start'
          Default = True
          TabOrder = 0
          OnClick = StartButtonClick
        end
        object StopButton: TButton
          Left = 88
          Top = 24
          Width = 75
          Height = 25
          Caption = 'S&top'
          TabOrder = 1
          OnClick = StopButtonClick
        end
        object PortEdit: TEdit
          Left = 280
          Top = 24
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '5679'
        end
        object ServerEdit: TEdit
          Left = 280
          Top = 48
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '172.20.89.85'
        end
        object AnyServerCheckBox: TCheckBox
          Left = 280
          Top = 72
          Width = 49
          Height = 17
          Caption = 'Any'
          TabOrder = 4
          OnClick = AnyServerCheckBoxClick
        end
      end
    end
    object ts_sensors: TTabSheet
      Caption = 'Sensors'
      ImageIndex = 1
      object bt_serial: TSpeedButton
        Left = 167
        Top = 595
        Width = 193
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
        Left = 199
        Top = 590
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
      object bt_filter: TSpeedButton
        Left = 10
        Top = 595
        Width = 137
        Height = 22
        Caption = 'HIL On'
        Flat = True
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00370777033333
          3330337F3F7F33333F3787070003333707303F737773333373F7007703333330
          700077337F3333373777887007333337007733F773F333337733700070333333
          077037773733333F7F37703707333300080737F373333377737F003333333307
          78087733FFF3337FFF7F33300033330008073F3777F33F777F73073070370733
          078073F7F7FF73F37FF7700070007037007837773777F73377FF007777700730
          70007733FFF77F37377707700077033707307F37773F7FFF7337080777070003
          3330737F3F7F777F333778080707770333333F7F737F3F7F3333080787070003
          33337F73FF737773333307800077033333337337773373333333}
        NumGlyphs = 2
        OnClick = bt_filterClick
      end
      object ld_filter: TAbLED
        Left = 33
        Top = 589
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
        Top = 2
        Width = 350
        Height = 103
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
          Left = 284
          Top = 64
          Width = 59
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
        Top = 116
        Width = 350
        Height = 107
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
          Left = 176
          Top = 70
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
          Top = 86
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
        object Label52: TLabel
          Left = 176
          Top = 86
          Width = 40
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'TimeSt'
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
          Left = 224
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
          TabOrder = 7
        end
        object et_magz: TStaticText
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
          TabOrder = 8
        end
        object et_timeStamp: TStaticText
          Left = 224
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
          TabOrder = 9
        end
      end
      object GroupBox9: TGroupBox
        Left = 8
        Top = 232
        Width = 350
        Height = 52
        Caption = ' Air Data '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        object Label58: TLabel
          Left = 8
          Top = 16
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Dyn'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label59: TLabel
          Left = 168
          Top = 16
          Width = 32
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Temp'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label60: TLabel
          Left = 8
          Top = 32
          Width = 24
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Stat'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_dyn: TStaticText
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
        object et_temp: TStaticText
          Left = 216
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
          TabOrder = 1
        end
        object et_sta: TStaticText
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
          TabOrder = 2
        end
      end
      object GroupBox10: TGroupBox
        Left = 8
        Top = 296
        Width = 350
        Height = 52
        Caption = 'MCU Status '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        object Label61: TLabel
          Left = 8
          Top = 16
          Width = 40
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Sensor'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label62: TLabel
          Left = 168
          Top = 16
          Width = 44
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Voltage'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label63: TLabel
          Left = 8
          Top = 32
          Width = 41
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Control'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_load: TStaticText
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
        object et_volt: TStaticText
          Left = 216
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
          TabOrder = 1
        end
        object et_vdetect: TStaticText
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
          TabOrder = 2
        end
      end
      object GroupBox14: TGroupBox
        Left = 8
        Top = 357
        Width = 350
        Height = 47
        Caption = 'Protocol Status'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        object Label78: TLabel
          Left = 8
          Top = 19
          Width = 75
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Lost Packets'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_fail: TStaticText
          Left = 94
          Top = 19
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
      end
      object GroupBox15: TGroupBox
        Left = 7
        Top = 412
        Width = 350
        Height = 103
        Caption = ' PWM Commands '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
        object Label68: TLabel
          Left = 8
          Top = 16
          Width = 27
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Thro'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label79: TLabel
          Left = 8
          Top = 32
          Width = 26
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'L Ail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label80: TLabel
          Left = 8
          Top = 48
          Width = 28
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'R Ail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label81: TLabel
          Left = 176
          Top = 14
          Width = 39
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'R Elev'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label82: TLabel
          Left = 176
          Top = 30
          Width = 36
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'L Flap'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label83: TLabel
          Left = 176
          Top = 47
          Width = 38
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'R Flap'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label84: TLabel
          Left = 8
          Top = 64
          Width = 31
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Rudd'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label85: TLabel
          Left = 176
          Top = 64
          Width = 33
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Aux 1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label86: TLabel
          Left = 8
          Top = 80
          Width = 37
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'L Elev'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label87: TLabel
          Left = 176
          Top = 81
          Width = 33
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Aux 2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_dtc: TStaticText
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
        object et_dlac: TStaticText
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
        object et_drac: TStaticText
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
        object et_drec: TStaticText
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
        object et_dlfc: TStaticText
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
        object et_drfc: TStaticText
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
        object et_drc: TStaticText
          Left = 56
          Top = 66
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
        object et_a1c: TStaticText
          Left = 224
          Top = 65
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
        object et_dlec: TStaticText
          Left = 56
          Top = 82
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
        object et_a2c: TStaticText
          Left = 224
          Top = 81
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
          TabOrder = 9
        end
      end
    end
    object ts_filter: TTabSheet
      Caption = 'Attitude'
      ImageIndex = 7
      object GroupBox4: TGroupBox
        Left = 4
        Top = 7
        Width = 350
        Height = 124
        Caption = 'Position and Attitude '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label31: TLabel
          Left = 8
          Top = 16
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'X'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label32: TLabel
          Left = 8
          Top = 32
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Y'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label33: TLabel
          Left = 8
          Top = 48
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Z'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label34: TLabel
          Left = 176
          Top = 14
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Roll'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label35: TLabel
          Left = 176
          Top = 30
          Width = 30
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Pitch'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label36: TLabel
          Left = 176
          Top = 46
          Width = 25
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Yaw'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label37: TLabel
          Left = 176
          Top = 70
          Width = 9
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'P'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label38: TLabel
          Left = 176
          Top = 86
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Q'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label39: TLabel
          Left = 176
          Top = 102
          Width = 10
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'R'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label40: TLabel
          Left = 8
          Top = 71
          Width = 15
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Vx'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label41: TLabel
          Left = 8
          Top = 87
          Width = 15
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Vy'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label42: TLabel
          Left = 8
          Top = 103
          Width = 15
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Vz'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_x: TStaticText
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
        object et_y: TStaticText
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
        object et_z: TStaticText
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
        object et_phi: TStaticText
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
        object et_theta: TStaticText
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
        object et_psi: TStaticText
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
        object et_p: TStaticText
          Left = 224
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
        object et_q: TStaticText
          Left = 224
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
        object et_r: TStaticText
          Left = 224
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
        object et_vx: TStaticText
          Left = 56
          Top = 71
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
          TabOrder = 9
        end
        object et_vy: TStaticText
          Left = 56
          Top = 87
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
          TabOrder = 10
        end
        object et_vz: TStaticText
          Left = 56
          Top = 103
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
          TabOrder = 11
        end
      end
      object GroupBox7: TGroupBox
        Left = 5
        Top = 142
        Width = 350
        Height = 72
        Caption = ' Sensor Biases '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label46: TLabel
          Left = 8
          Top = 16
          Width = 22
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Axb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label47: TLabel
          Left = 8
          Top = 32
          Width = 22
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Ayb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label48: TLabel
          Left = 8
          Top = 48
          Width = 22
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Azb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label49: TLabel
          Left = 176
          Top = 14
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gxb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label50: TLabel
          Left = 176
          Top = 30
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gyb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label51: TLabel
          Left = 176
          Top = 46
          Width = 23
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Gzb'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_axb: TStaticText
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
        object et_ayb: TStaticText
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
        object et_azb: TStaticText
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
        object et_gxb: TStaticText
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
        object et_gyb: TStaticText
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
        object et_gzb: TStaticText
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
      end
    end
    object ts_graphical: TTabSheet
      Caption = 'Graphical Instruments'
      ImageIndex = 4
      object ai_att: TAbVCInd
        Left = -3
        Top = 16
        Width = 273
        Height = 273
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
      object gr_batt: TAbTank
        Left = 0
        Top = 536
        Width = 353
        Height = 33
        Digit = 10000
        LimitUpper = 13000
        LimitLower = 7000
        SectorSettings.Sector1From = 9999
        SectorSettings.Sector1To = 9000
        SectorSettings.Sector2From = 10000
        SectorSettings.Sector2To = 13000
        SectorSettings.Sector3From = 8999
        SectorSettings.Sector3To = 7000
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.DigitalFrom = 7000
        SignalSettings.DigitalTo = 13000
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '###00'
        SignalSettings.ValueFrom = 7000
        SignalSettings.ValueTo = 13000
        SignalSettings.ValueUnit = 'mV'
        Value = 10000
        PPHColor = clAqua
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBtnShadow
        BevelValue.ColorShadowFrom = clBlack
        BevelValue.ColorShadowTo = clBlack
        BevelValue.ColorHighLightFrom = clBtnFace
        BevelValue.ColorHighLightTo = clBtnFace
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        TankSettings.Style = tsRoundRect
        TankSettings.CraterWidth = 40
        TankSettings.BkColor = clBtnShadow
        TankSettings.Color = clBackground
        TankSettings.PenWidth = 2
        TankSettings.PenColor = clBlack
        Options = [opUseSectorColors, opValue, opUnit]
        FontUnitCol = clWhite
        VIndOffsX = 0
        VIndOffsY = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBtnHighlight
        Font.Height = -13
        Font.Name = 'System'
        Font.Style = []
      end
      object gr_height: TAbVBar
        Left = 280
        Top = 24
        Width = 76
        Height = 274
        Digit = 75
        LimitUpper = 2000
        LimitLower = 100
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '####.0'
        SignalSettings.ValueTo = 2000
        SignalSettings.ValueUnit = 'm'
        Value = 150
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        AutoSize = False
        FontValue.Charset = DEFAULT_CHARSET
        FontValue.Color = clLime
        FontValue.Height = -13
        FontValue.Name = 'System'
        FontValue.Style = []
        BarSettings.Style = bsBar
        BarSettings.Font.Charset = DEFAULT_CHARSET
        BarSettings.Font.Color = clBtnHighlight
        BarSettings.Font.Height = -11
        BarSettings.Font.Name = 'MS Sans Serif'
        BarSettings.Font.Style = []
        BarSettings.Options = []
        BarSettings.Color = clLime
        BarSettings.BkColor = clBlack
        BarSettings.BkBrightness = 40
        BarSettings.BkAuto = False
        BarSettings.Bevel.Style = bsLowered
        BarSettings.Bevel.Spacing = 1
        BarSettings.Bevel.BevelLine = blNone
        BarSettings.Bevel.Width = 1
        BarSettings.Bevel.Color = clBlack
        BarSettings.Bevel.SurfaceGrad.Visible = False
        BarSettings.Bevel.SurfaceGrad.Style = gsHorizontal1
        BarSettings.minHeight = 205
        BarSettings.minWidth = 9
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 5
        BevelInner.BevelLine = blInner
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 5
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBlack
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        Options = [opValue, opOverflow, opUnit]
      end
      object gr_dt: TAbVBar
        Left = 14
        Top = 304
        Width = 76
        Height = 100
        HelpType = htKeyword
        Digit = 474
        LimitUpper = 2000
        LimitLower = 1050
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '####.0'
        SignalSettings.ValueFrom = 1050
        SignalSettings.ValueTo = 2000
        SignalSettings.ValueUnit = 'm'
        MinMax.UseSectorCol = False
        MinMax.MinVisible = False
        MinMax.MaxVisible = False
        Value = 1500
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        AutoSize = False
        FontValue.Charset = DEFAULT_CHARSET
        FontValue.Color = clLime
        FontValue.Height = -13
        FontValue.Name = 'System'
        FontValue.Style = []
        BarSettings.Style = bsPoint
        BarSettings.Font.Charset = DEFAULT_CHARSET
        BarSettings.Font.Color = clBtnHighlight
        BarSettings.Font.Height = -11
        BarSettings.Font.Name = 'MS Sans Serif'
        BarSettings.Font.Style = []
        BarSettings.Options = []
        BarSettings.Color = clLime
        BarSettings.BkColor = clBlack
        BarSettings.BkBrightness = 40
        BarSettings.BkAuto = False
        BarSettings.Bevel.Style = bsLowered
        BarSettings.Bevel.Spacing = 1
        BarSettings.Bevel.BevelLine = blNone
        BarSettings.Bevel.Width = 1
        BarSettings.Bevel.Color = clBlack
        BarSettings.Bevel.SurfaceGrad.Visible = False
        BarSettings.Bevel.SurfaceGrad.Style = gsHorizontal1
        BarSettings.minHeight = 20
        BarSettings.minWidth = 9
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 5
        BevelInner.BevelLine = blInner
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 5
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBlack
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        Options = [opOverflow, opUnit]
      end
      object gr_dr: TAbHBar
        Left = 2
        Top = 400
        Width = 100
        Height = 24
        HelpType = htKeyword
        Digit = 1500
        LimitUpper = 2000
        LimitLower = 1050
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.DigitalFrom = 1050
        SignalSettings.DigitalTo = 2000
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '##0.0'
        SignalSettings.ValueFrom = 1050
        SignalSettings.ValueTo = 2000
        SignalSettings.ValueUnit = '%'
        MinMax.UseSectorCol = False
        MinMax.MinVisible = False
        MinMax.MaxVisible = False
        Value = 1500
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        AutoSize = False
        FontValue.Charset = DEFAULT_CHARSET
        FontValue.Color = clLime
        FontValue.Height = -13
        FontValue.Name = 'System'
        FontValue.Style = []
        BarSettings.Style = bsPoint
        BarSettings.Font.Charset = DEFAULT_CHARSET
        BarSettings.Font.Color = clBtnHighlight
        BarSettings.Font.Height = -11
        BarSettings.Font.Name = 'MS Sans Serif'
        BarSettings.Font.Style = []
        BarSettings.Options = []
        BarSettings.Color = clLime
        BarSettings.BkColor = clBlack
        BarSettings.BkBrightness = 40
        BarSettings.BkAuto = False
        BarSettings.Bevel.Style = bsLowered
        BarSettings.Bevel.Spacing = 1
        BarSettings.Bevel.BevelLine = blNone
        BarSettings.Bevel.Width = 1
        BarSettings.Bevel.Color = clBlack
        BarSettings.Bevel.SurfaceGrad.Visible = False
        BarSettings.Bevel.SurfaceGrad.Style = gsHorizontal1
        BarSettings.minHeight = 10
        BarSettings.minWidth = 9
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 0
        BevelInner.BevelLine = blInner
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 5
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBlack
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        Options = []
      end
      object gr_de: TAbVBar
        Left = 127
        Top = 304
        Width = 76
        Height = 100
        HelpType = htKeyword
        Digit = 474
        LimitUpper = 2000
        LimitLower = 1050
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '####.0'
        SignalSettings.ValueFrom = 1050
        SignalSettings.ValueTo = 2000
        SignalSettings.ValueUnit = 'm'
        MinMax.UseSectorCol = False
        MinMax.MinVisible = False
        MinMax.MaxVisible = False
        Value = 1500
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        AutoSize = False
        FontValue.Charset = DEFAULT_CHARSET
        FontValue.Color = clLime
        FontValue.Height = -13
        FontValue.Name = 'System'
        FontValue.Style = []
        BarSettings.Style = bsPoint
        BarSettings.Font.Charset = DEFAULT_CHARSET
        BarSettings.Font.Color = clBtnHighlight
        BarSettings.Font.Height = -11
        BarSettings.Font.Name = 'MS Sans Serif'
        BarSettings.Font.Style = []
        BarSettings.Options = []
        BarSettings.Color = clLime
        BarSettings.BkColor = clBlack
        BarSettings.BkBrightness = 40
        BarSettings.BkAuto = False
        BarSettings.Bevel.Style = bsLowered
        BarSettings.Bevel.Spacing = 1
        BarSettings.Bevel.BevelLine = blNone
        BarSettings.Bevel.Width = 1
        BarSettings.Bevel.Color = clBlack
        BarSettings.Bevel.SurfaceGrad.Visible = False
        BarSettings.Bevel.SurfaceGrad.Style = gsHorizontal1
        BarSettings.minHeight = 20
        BarSettings.minWidth = 9
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 5
        BevelInner.BevelLine = blInner
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 5
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBlack
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        Options = [opOverflow, opUnit]
      end
      object gr_da: TAbHBar
        Left = 115
        Top = 400
        Width = 100
        Height = 24
        HelpType = htKeyword
        Digit = 1500
        LimitUpper = 2000
        LimitLower = 1050
        SectorSettings.Offset = 0
        SectorSettings.WidthOffset = 0
        SignalSettings.DigitalFrom = 1050
        SignalSettings.DigitalTo = 2000
        SignalSettings.Name1 = 'SignalName1'
        SignalSettings.Name2 = 'SignalName2'
        SignalSettings.ValueFormat = '##0.0'
        SignalSettings.ValueFrom = 1050
        SignalSettings.ValueTo = 2000
        SignalSettings.ValueUnit = '%'
        MinMax.MinVisible = False
        MinMax.MaxVisible = False
        Value = 1500
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        AutoSize = False
        FontValue.Charset = DEFAULT_CHARSET
        FontValue.Color = clLime
        FontValue.Height = -13
        FontValue.Name = 'System'
        FontValue.Style = []
        BarSettings.Style = bsPoint
        BarSettings.Font.Charset = DEFAULT_CHARSET
        BarSettings.Font.Color = clBtnHighlight
        BarSettings.Font.Height = -11
        BarSettings.Font.Name = 'MS Sans Serif'
        BarSettings.Font.Style = []
        BarSettings.Options = []
        BarSettings.Color = clLime
        BarSettings.BkColor = clBlack
        BarSettings.BkBrightness = 40
        BarSettings.BkAuto = False
        BarSettings.Bevel.Style = bsLowered
        BarSettings.Bevel.Spacing = 1
        BarSettings.Bevel.BevelLine = blNone
        BarSettings.Bevel.Width = 1
        BarSettings.Bevel.Color = clBlack
        BarSettings.Bevel.SurfaceGrad.Visible = False
        BarSettings.Bevel.SurfaceGrad.Style = gsHorizontal1
        BarSettings.minHeight = 10
        BarSettings.minWidth = 9
        BevelInner.Style = bsLowered
        BevelInner.Spacing = 0
        BevelInner.BevelLine = blInner
        BevelInner.Width = 2
        BevelInner.SurfaceGrad.Visible = False
        BevelInner.SurfaceGrad.Style = gsHorizontal1
        BevelOuter.Style = bsRaised
        BevelOuter.Spacing = 5
        BevelOuter.BevelLine = blOuter
        BevelOuter.Width = 2
        BevelOuter.SurfaceGrad.Visible = False
        BevelOuter.SurfaceGrad.Style = gsHorizontal1
        BevelValue.Style = bsLowered
        BevelValue.Spacing = 0
        BevelValue.BevelLine = blNone
        BevelValue.Width = 2
        BevelValue.Color = clBlack
        BevelValue.SurfaceGrad.Visible = False
        BevelValue.SurfaceGrad.Style = gsHorizontal1
        Options = []
      end
      object Label74: TLabel
        Left = 32
        Top = 421
        Width = 42
        Height = 13
        Caption = 'Rudder'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label75: TLabel
        Left = 142
        Top = 421
        Width = 46
        Height = 13
        Caption = 'Ailerons'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label76: TLabel
        Left = 32
        Top = 293
        Width = 45
        Height = 13
        Caption = 'Throttle'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label77: TLabel
        Left = 144
        Top = 293
        Width = 48
        Height = 13
        Caption = 'Elevator'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object GroupBox13: TGroupBox
        Left = 222
        Top = 309
        Width = 145
        Height = 110
        Caption = ' Pilot Commands '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label69: TLabel
          Left = 8
          Top = 19
          Width = 14
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Dt'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label70: TLabel
          Left = 8
          Top = 35
          Width = 20
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Dla'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label71: TLabel
          Left = 8
          Top = 51
          Width = 21
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Dra'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label72: TLabel
          Left = 8
          Top = 65
          Width = 14
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'Dr'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object Label73: TLabel
          Left = 8
          Top = 81
          Width = 17
          Height = 13
          Hint = 
            'The Main KML file is the one opnened '#13#10'in Google Earth. This con' +
            'tains a link to'#13#10'the Plane Path KML File and the update'#13#10'rate at' +
            ' which such path is refreshed'
          Caption = 'De'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
        end
        object et_dt: TStaticText
          Left = 35
          Top = 19
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
        object et_dla: TStaticText
          Left = 35
          Top = 35
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
        object et_dra: TStaticText
          Left = 35
          Top = 51
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
        object et_dr: TStaticText
          Left = 35
          Top = 65
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
        object et_de: TStaticText
          Left = 35
          Top = 81
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
      end
    end
    object ts_plots: TTabSheet
      Caption = 'Data Plots'
      ImageIndex = 3
      object mt_x: TAbMiniTrend
        Left = 0
        Top = 72
        Width = 365
        Height = 161
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -16
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsBold]
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
        DigitCh1 = 5394
        DigitCh2 = 0
        SignalSettingsCh1.DigitalFrom = 1500
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 150
        TimeScale = 1
        Options = [opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'X Axis'
        Flow = False
      end
      object mt_y: TAbMiniTrend
        Left = 0
        Top = 240
        Width = 365
        Height = 161
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -16
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsBold]
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
        DigitCh1 = 5394
        DigitCh2 = 0
        SignalSettingsCh1.DigitalFrom = 1500
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 150
        TimeScale = 1
        Options = [opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'Y Axis'
        Flow = False
      end
      object mt_z: TAbMiniTrend
        Left = 0
        Top = 408
        Width = 365
        Height = 161
        CaptionFont.Charset = DEFAULT_CHARSET
        CaptionFont.Color = clWindowText
        CaptionFont.Height = -16
        CaptionFont.Name = 'Arial'
        CaptionFont.Style = [fsBold]
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
        DigitCh1 = 5394
        DigitCh2 = 0
        SignalSettingsCh1.DigitalFrom = 1500
        SignalSettingsCh1.DigitalTo = 4096
        SignalSettingsCh1.Name1 = 'Name1'
        SignalSettingsCh1.Name2 = 'Name2'
        SignalSettingsCh1.ValueFormat = '##0'
        SignalSettingsCh1.ValueTo = 100
        SignalSettingsCh1.ValueUnit = '%'
        SignalSettingsCh2.Name1 = 'Name1'
        SignalSettingsCh2.Name2 = 'Name2'
        SignalSettingsCh2.ValueFormat = '##0'
        SignalSettingsCh2.ValueTo = 100
        SignalSettingsCh2.ValueUnit = '%'
        ValueCh1 = 150
        TimeScale = 1
        Options = [opCaption, opScaleCh1, opTimeLine]
        SignalColorCh2 = clBlack
        Caption = 'Z Axis'
        Flow = False
      end
      object rg_plot: TRadioGroup
        Left = 8
        Top = 8
        Width = 359
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
    Top = 25
    Width = 201
    Height = 672
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
      Top = 640
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
      Width = 185
      Height = 601
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 576
    Height = 25
    Align = alTop
    TabOrder = 3
    object et_warning: TLabel
      Left = 200
      Top = 2
      Width = 377
      Height = 19
      Hint = 'Double Click to Aknowledge Message'
      Alignment = taCenter
      AutoSize = False
      Caption = 'No Message'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnDblClick = et_warningDblClick
    end
  end
  object FormStorage1: TFormStorage
    IniFileName = '.\ap.ini'
    StoredProps.Strings = (
      'mm_diagnose.Lines'
      'pc_main.ActivePage'
      'cb_color1.Color'
      'cb_color2.Color'
      'cb_inflight.Checked')
    StoredValues = <>
    Left = 32
    Top = 520
  end
  object ad_main: TABSDatabase
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
      end
      item
        Name = 'ExportLocation'
        DataType = ftString
        Size = 500
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
    object tb_configExportLocation: TStringField
      FieldName = 'ExportLocation'
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
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 136
    Top = 400
  end
  object cp_serial: TApdComPort
    Baud = 115200
    AutoOpen = False
    TraceName = 'APRO.TRC'
    LogName = 'APRO.LOG'
    OnTriggerAvail = cp_serialTriggerAvail
    Left = 64
    Top = 272
  end
  object skt_send: TWSocket
    LineMode = False
    LineLimit = 65536
    LineEnd = #13#10
    LineEcho = False
    LineEdit = False
    Addr = '0.0.0.0'
    Port = '600'
    Proto = 'udp'
    LocalAddr = '0.0.0.0'
    LocalPort = '0'
    LastError = 0
    MultiThreaded = False
    MultiCast = False
    MultiCastIpTTL = 1
    ReuseAddr = False
    ComponentOptions = []
    ListenBacklog = 5
    ReqVerLow = 1
    ReqVerHigh = 1
    FlushTimeout = 60
    SendFlags = wsSendNormal
    LingerOnOff = wsLingerOn
    LingerTimeout = 0
    KeepAliveOnOff = wsKeepAliveOnSystem
    KeepAliveTime = 30000
    KeepAliveInterval = 1000
    SocksLevel = '5'
    SocksAuthentication = socksNoAuthentication
    Left = 128
    Top = 168
  end
  object skt_rcv: TWSocket
    LineMode = False
    LineLimit = 65536
    LineEnd = #13#10
    LineEcho = False
    LineEdit = False
    Addr = '0.0.0.0'
    Port = '600'
    Proto = 'udp'
    LocalAddr = '0.0.0.0'
    LocalPort = '0'
    LastError = 0
    MultiThreaded = False
    MultiCast = False
    MultiCastIpTTL = 1
    ReuseAddr = False
    ComponentOptions = []
    ListenBacklog = 5
    ReqVerLow = 1
    ReqVerHigh = 1
    OnDataAvailable = skt_rcvDataAvailable
    OnSessionClosed = skt_rcvSessionClosed
    OnSessionConnected = skt_rcvSessionConnected
    FlushTimeout = 60
    SendFlags = wsSendNormal
    LingerOnOff = wsLingerOn
    LingerTimeout = 0
    KeepAliveOnOff = wsKeepAliveOnSystem
    KeepAliveTime = 30000
    KeepAliveInterval = 1000
    SocksLevel = '5'
    SocksAuthentication = socksNoAuthentication
    Left = 136
    Top = 64
  end
  object cp_hil: TApdComPort
    ComNumber = 3
    Baud = 115200
    PromptForPort = False
    AutoOpen = False
    TraceName = 'APRO.TRC'
    LogName = 'APRO.LOG'
    Left = 152
    Top = 272
  end
end
