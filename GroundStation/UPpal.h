//---------------------------------------------------------------------------

#ifndef UPpalH
#define UPpalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "tinyxml.h"
#include <ComCtrls.hpp>
#include "Placemnt.hpp"
#include <Buttons.hpp>
#include "ABSMain.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Dialogs.hpp>
#include <Mask.hpp>

//---------------------------------------------------------------------------
class TFPpal : public TForm
{
__published:	// IDE-managed Components
    TStatusBar *StatusBar1;
    TPageControl *pc_main;
    TTabSheet *ts_ge;
    TTabSheet *ts_telemetry;
    TTabSheet *TabSheet3;
    TTabSheet *TabSheet1;
    TPanel *Panel1;
    TLabel *Label1;
    TMemo *mm_diagnose;
    TFormStorage *FormStorage1;
    TSpeedButton *bt_clear;
    TABSDatabase *ad_main;
    TABSTable *tb_config;
    TLabel *Label2;
    TDataSource *fte_config;
    TDBEdit *DBEdit1;
    TSpeedButton *bt_mainKml;
    TStringField *tb_configkmlFile;
    TStringField *tb_configplanePathFile;
    TSmallintField *tb_configupdateRate;
    TSmallintField *tb_configtessellate;
    TLabel *Label3;
    TDBEdit *DBEdit2;
    TSpeedButton *bt_ppKml;
    TDBRadioGroup *DBRadioGroup1;
    TDBCheckBox *DBCheckBox1;
    TSpeedButton *SpeedButton1;
    TTimer *Timer1;
    TSaveDialog *od_mainKml;
    TBitBtn *BitBtn1;
    TColorBox *cb_color1;
    TLabel *Label4;
    TLabel *Label5;
    TColorBox *ColorBox1;
    TTrackBar *TrackBar1;
    TLabel *Label6;
    TLabel *Label7;
    TDBEdit *DBEdit3;
    TSpeedButton *SpeedButton2;
    TDBRadioGroup *DBRadioGroup2;
    TLabel *Label8;
    TDBEdit *DBEdit4;
    TSpeedButton *SpeedButton3;
    TBitBtn *BitBtn2;
    TIntegerField *tb_configtrajectoryColorR;
    TIntegerField *tb_configtrajectoryColorG;
    TIntegerField *tb_configtrajectoryColorB;
    TSmallintField *tb_configtailLength;
    TIntegerField *tb_configtessalateColorR;
    TIntegerField *tb_configtessalateColorG;
    TIntegerField *tb_configtessalateColorB;
    TSmallintField *tb_configtessalateTransparency;
    TStringField *tb_configiconFile;
    TStringField *tb_configwaypointFile;
        void __fastcall FormShow(TObject *Sender);
    void __fastcall bt_clearClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bt_mainKmlClick(TObject *Sender);
    void __fastcall bt_ppKmlClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall cb_color1Exit(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFPpal(TComponent* Owner);
        void createBlankKML(char KMLType);
        void addAndAppendNode(char* name, char* value, TiXmlNode* appendTo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPpal *FPpal;
//---------------------------------------------------------------------------
#endif
