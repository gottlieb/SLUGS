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
#include "apDefinitions.h"
#include "protDecoder.h"
#include "AdPort.hpp"
#include "OoMisc.hpp"
#include "CircBuffer.h"
#include "_GClass.hpp"
#include "AbLED.hpp"
#include "AbOpHour.hpp"
#include "AbMTrend.hpp"
#include <math.h>
#include <exception.h>
#include "AbVCInd.hpp"
#include "gpsSplit.h"
#include "AbCBitBt.hpp"
#include "ToolEdit.hpp"
#include "gsDefinitions.h"
#include "WSocket.hpp"
#include <string>

#define  DISLIMIT      30.0


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
    TDBRadioGroup *rg_uprate;
    TDBCheckBox *DBCheckBox1;
    TSpeedButton *bt_gearth;
    TTimer *Timer1;
    TSaveDialog *od_mainKml;
    TColorBox *cb_color1;
    TLabel *Label4;
    TLabel *Label5;
    TColorBox *cb_color2;
    TTrackBar *kb_tessalate;
    TLabel *Label6;
    TLabel *Label7;
    TDBEdit *DBEdit3;
    TSpeedButton *bt_icon;
    TDBRadioGroup *rg_tail;
    TLabel *Label8;
    TDBEdit *bt_wp;
    TSpeedButton *SpeedButton3;
    TIntegerField *tb_configtrajectoryColorR;
    TIntegerField *tb_configtrajectoryColorG;
    TIntegerField *tb_configtrajectoryColorB;
    TSmallintField *tb_configtailLength;
    TIntegerField *tb_configtessalateColorR;
    TIntegerField *tb_configtessalateColorG;
    TIntegerField *tb_configtessalateColorB;
    TStringField *tb_configiconFile;
    TStringField *tb_configwaypointFile;
    TSpeedButton *bt_serial;
    TTimer *Timer2;
    TGroupBox *GroupBox1;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TStaticText *et_date;
    TStaticText *et_time;
    TStaticText *et_lat;
    TStaticText *et_lon;
    TStaticText *et_height;
    TStaticText *et_sog;
    TStaticText *et_cog;
    TStaticText *et_hdop;
    TStaticText *et_fix;
    TStaticText *et_sats;
    TGroupBox *GroupBox2;
    TLabel *Label20;
    TStaticText *et_accelx;
    TLabel *Label19;
    TStaticText *et_accely;
    TLabel *Label24;
    TStaticText *et_accelz;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TStaticText *et_gyrox;
    TStaticText *et_gyroy;
    TStaticText *et_gyroz;
    TLabel *Label25;
    TLabel *Label26;
    TStaticText *et_magx;
    TStaticText *et_magy;
    TLabel *Label27;
    TStaticText *et_magz;
    TRadioGroup *rg_plot;
    TGroupBox *GroupBox3;
    TDBEdit *DBEdit4;
    TLabel *Label28;
    TLabel *Label29;
    TDBEdit *DBEdit5;
    TLabel *Label30;
    TDBEdit *DBEdit6;
    TSpeedButton *bt_gspos;
    TFloatField *tb_configlatGS;
    TFloatField *tb_configlonGS;
    TFloatField *tb_configheightGS;
    TIntegerField *tb_configtessalateTransparency;
    TAbLED *AbLED1;
    TGroupBox *GroupBox4;
    TLabel *Label31;
    TLabel *Label32;
    TLabel *Label33;
    TLabel *Label34;
    TLabel *Label35;
    TLabel *Label36;
    TLabel *Label37;
    TLabel *Label38;
    TLabel *Label39;
    TStaticText *et_x;
    TStaticText *et_y;
    TStaticText *et_z;
    TStaticText *et_phi;
    TStaticText *et_theta;
    TStaticText *et_psi;
    TStaticText *et_p;
    TStaticText *et_q;
    TStaticText *et_r;
    TLabel *Label40;
    TLabel *Label41;
    TLabel *Label42;
    TStaticText *et_vx;
    TStaticText *et_vy;
    TStaticText *et_vz;
    TAbLED *ld_serial;
    TSpeedButton *bt_filter;
    TAbLED *ld_filter;
    TAbMiniTrend *mt_x;
    TAbMiniTrend *mt_y;
    TAbMiniTrend *mt_z;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet4;
    TAbVCInd *ai_att;
    TGroupBox *GroupBox5;
    TCheckBox *cb_inflight;
    TGroupBox *GroupBox6;
    TLabel *Label43;
    TStringField *tb_configExportLocation;
    TFilenameEdit *ed_importLog;
    TLabel *Label44;
    TSpeedButton *bt_importLog;
    TLabel *Label45;
    TFilenameEdit *ed_exportMat;
    TFilenameEdit *ed_liveLog;
    TApdComPort *cp_serial;
    TGroupBox *GroupBox7;
    TLabel *Label46;
    TLabel *Label47;
    TLabel *Label48;
    TLabel *Label49;
    TLabel *Label50;
    TLabel *Label51;
    TStaticText *et_axb;
    TStaticText *et_ayb;
    TStaticText *et_azb;
    TStaticText *et_gxb;
    TStaticText *et_gyb;
    TStaticText *et_gzb;
    TGroupBox *GroupBox8;
    TLabel *Fl1;
    TLabel *Label53;
    TLabel *Label54;
    TLabel *Label55;
    TLabel *Label56;
    TLabel *Label57;
    TStaticText *et_fl1;
    TStaticText *et_fl2;
    TStaticText *et_fl3;
    TStaticText *et_sh1;
    TStaticText *et_sh2;
    TStaticText *et_sh3;
    TGroupBox *GroupBox9;
    TLabel *Label58;
    TLabel *Label59;
    TLabel *Label60;
    TStaticText *et_dyn;
    TStaticText *et_temp;
    TStaticText *et_sta;
    TLabel *Label52;
    TStaticText *et_timeStamp;
    TGroupBox *GroupBox10;
    TLabel *Label61;
    TLabel *Label62;
    TLabel *Label63;
    TStaticText *et_load;
    TStaticText *et_volt;
    TStaticText *et_vdetect;
    TTabSheet *tsHil;
    TGroupBox *GroupBox11;
    TLabel *et_connSend;
    TLabel *Label64;
    TLabel *Label65;
    TLabel *et_sent;
    TButton *bt_startSend;
    TButton *bt_stopSend;
    TEdit *ed_portSend;
    TEdit *ed_hostSend;
    TWSocket *skt_send;
    TWSocket *skt_rcv;
    TGroupBox *GroupBox12;
    TLabel *DataAvailableLabel;
    TLabel *InfoLabel;
    TLabel *Label66;
    TLabel *Label67;
    TButton *StartButton;
    TButton *StopButton;
    TEdit *PortEdit;
    TEdit *ServerEdit;
    TCheckBox *AnyServerCheckBox;
    TApdComPort *cp_hil;
    TLabel *et_fail;
    TLabel *Label68;
        void __fastcall FormShow(TObject *Sender);
    void __fastcall bt_clearClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bt_ppKmlClick(TObject *Sender);
    void __fastcall bt_gearthClick(TObject *Sender);
    void __fastcall cb_color1Exit(TObject *Sender);
    void __fastcall cb_color2Exit(TObject *Sender);
    void __fastcall kb_tessalateExit(TObject *Sender);
    void __fastcall bt_serialClick(TObject *Sender);
    void __fastcall Timer2Timer(TObject *Sender);
    void __fastcall cp_serialTriggerAvail(TObject *CP, WORD Count);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall rg_tailExit(TObject *Sender);
    void __fastcall bt_gsposClick(TObject *Sender);
    void __fastcall bt_filterClick(TObject *Sender);
    void __fastcall bt_onflightexpClick(TObject *Sender);
    void __fastcall ed_exportAfterDialog(TObject *Sender, AnsiString &Name,
          bool &Action);
    void __fastcall cb_inflightClick(TObject *Sender);
    void __fastcall bt_importLogClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ed_liveLogAfterDialog(TObject *Sender,
          AnsiString &Name, bool &Action);
    void __fastcall skt_rcvSessionClosed(TObject *Sender, WORD ErrCode);
    void __fastcall skt_rcvSessionConnected(TObject *Sender, WORD ErrCode);
    void __fastcall skt_rcvDataAvailable(TObject *Sender, WORD ErrCode);
    void __fastcall StartButtonClick(TObject *Sender);
    void __fastcall StopButtonClick(TObject *Sender);
    void __fastcall bt_startSendClick(TObject *Sender);
    void __fastcall bt_stopSendClick(TObject *Sender);
    void __fastcall AnyServerCheckBoxClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFPpal(TComponent* Owner);
        void createBlankKML(char KMLType);
        void updateKML(void);
        void addAndAppendNode(char* name, char* value, TiXmlNode* appendTo);
        String getHexColor(unsigned char whichColor);
        String getPlaneCoordinates(void);
        void assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg );

        tGpsData gpsSamples[15];
        tRawData rawSample;
        tAttitudeData attitudeSample;
        tXYZData xyzSample;
        tDynTempData dynSample;
        tBiasData biasSample;
        tDiagData diagSample;
        tSensStatus	statusSample;

        float csFail;

        FILE* liveLog;
        bool logIsOpen;

        void updateGPSLabels(void);
        void updateRawLabels(void);
        void updateAttitudeLabels(void);
        void updatePlots(void);
        void updateAttitude(void);

        void updateBiasLabels(void);
        void updateDynLabels(void);
        void updateDiagLabels(void);

        void printFileHeader(void);

        float computeDistance(float lat, float lon);
        float deg2Rad(float mDeg);

        char compare_float(float f1, float f2);

        // HIL
        Winsock::TInAddr      FServerAddr;
        void processUdpMsg(unsigned char * buffer);
                
//        CircBuffer mainSerial;
//        CBRef telemPort;
};
//---------------------------------------------------------------------------
extern PACKAGE TFPpal *FPpal;
//---------------------------------------------------------------------------
#endif
