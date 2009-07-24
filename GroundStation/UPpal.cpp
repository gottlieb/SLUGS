//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UPpal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "ABSMain"
#pragma link "AdPort"
#pragma link "OoMisc"
#pragma link "_GClass"
#pragma link "AbLED"
#pragma link "AbOpHour"
#pragma link "AbMTrend"
#pragma link "AbVCInd"
#pragma link "AbCBitBt"
#pragma link "ToolEdit"
#pragma link "WSocket"
#pragma link "OoMisc"
#pragma link "AbTank"
#pragma link "AbVBar"
#pragma link "AbHBar"
#pragma link "CurrEdit"
#pragma link "OoMisc"
#pragma link "RxCombos"
#pragma link "RXSlider"
#pragma resource "*.dfm"


TFPpal *FPpal;
//---------------------------------------------------------------------------
__fastcall TFPpal::TFPpal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFPpal::FormShow(TObject *Sender)
{
  cb_color1->Selected = RGB(tb_configtrajectoryColorR->AsInteger,
                            tb_configtrajectoryColorG->AsInteger,
                            tb_configtrajectoryColorB->AsInteger);

  cb_color2->Selected = RGB(tb_configtessalateColorR->AsInteger,
                            tb_configtessalateColorG->AsInteger,
                            tb_configtessalateColorB->AsInteger);


  kb_tessalate->Position = tb_configtessalateTransparency->AsInteger;

  cb_inflightClick(NULL);

  //bt_serialClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_clearClick(TObject *Sender)
{
 mm_diagnose->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::FormCreate(TObject *Sender)
{
 // Open the table
 tb_config->Open();

 // initialize the GPS position history with zeros.
 memset(gpsSamples,0,sizeof(gpsSamples));
 //memset(rawSample,0,sizeof(rawSample));

 protParserInit ();

 logIsOpen = false;

 // Create the label arrays for configuration
 PGains[0] = ed_p1;
 PGains[1] = ed_p2;
 PGains[2] = ed_p3;
 PGains[3] = ed_p4;
 PGains[4] = ed_p5;
 PGains[5] = ed_p6;
 PGains[6] = ed_p7;
 PGains[7] = ed_p8;
 PGains[8] = ed_p9;
 PGains[9] = ed_p10;

 IGains[0] = ed_i1;
 IGains[1] = ed_i2;
 IGains[2] = ed_i3;
 IGains[3] = ed_i4;
 IGains[4] = ed_i5;
 IGains[5] = ed_i6;
 IGains[6] = ed_i7;
 IGains[7] = ed_i8;
 IGains[8] = ed_i9;
 IGains[9] = ed_i10;

 DGains[0] = ed_d1;
 DGains[1] = ed_d2;
 DGains[2] = ed_d3;
 DGains[3] = ed_d4;
 DGains[4] = ed_d5;
 DGains[5] = ed_d6;
 DGains[6] = ed_d7;
 DGains[7] = ed_d8;
 DGains[8] = ed_d9;
 DGains[9] = ed_d10;

 BoxCont[0] = gb_pid1;
 BoxCont[1] = gb_pid2;
 BoxCont[2] = gb_pid3;
 BoxCont[3] = gb_pid4;
 BoxCont[4] = gb_pid5;
 BoxCont[5] = gb_pid6;
 BoxCont[6] = gb_pid7;
 BoxCont[7] = gb_pid8;
 BoxCont[8] = gb_pid9;
 BoxCont[9] = gb_pid10;

  EtPGains[0] = et_p1;
 EtPGains[1] = et_p2;
 EtPGains[2] = et_p3;
 EtPGains[3] = et_p4;
 EtPGains[4] = et_p5;
 EtPGains[5] = et_p6;
 EtPGains[6] = et_p7;
 EtPGains[7] = et_p8;
 EtPGains[8] = et_p9;
 EtPGains[9] = et_p10;

 EtIGains[0] = et_i1;
 EtIGains[1] = et_i2;
 EtIGains[2] = et_i3;
 EtIGains[3] = et_i4;
 EtIGains[4] = et_i5;
 EtIGains[5] = et_i6;
 EtIGains[6] = et_i7;
 EtIGains[7] = et_i8;
 EtIGains[8] = et_i9;
 EtIGains[9] = et_i10;

 EtDGains[0] = et_d1;
 EtDGains[1] = et_d2;
 EtDGains[2] = et_d3;
 EtDGains[3] = et_d4;
 EtDGains[4] = et_d5;
 EtDGains[5] = et_d6;
 EtDGains[6] = et_d7;
 EtDGains[7] = et_d8;
 EtDGains[8] = et_d9;
 EtDGains[9] = et_d10;

 // WP Arrays
 // =========
 latVals[0] = ed_lat1;
 latVals[1] = ed_lat2;
 latVals[2] = ed_lat3;
 latVals[3] = ed_lat4;
 latVals[4] = ed_lat5;
 latVals[5] = ed_lat6;
 latVals[6] = ed_lat7;
 latVals[7] = ed_lat8;
 latVals[8] = ed_lat9;
 latVals[9] = ed_lat10;

 lonVals[0] = ed_lon1;
 lonVals[1] = ed_lon2;
 lonVals[2] = ed_lon3;
 lonVals[3] = ed_lon4;
 lonVals[4] = ed_lon5;
 lonVals[5] = ed_lon6;
 lonVals[6] = ed_lon7;
 lonVals[7] = ed_lon8;
 lonVals[8] = ed_lon9;
 lonVals[9] = ed_lon10;

 heiVals[0] = ed_hei1;
 heiVals[1] = ed_hei2;
 heiVals[2] = ed_hei3;
 heiVals[3] = ed_hei4;
 heiVals[4] = ed_hei5;
 heiVals[5] = ed_hei6;
 heiVals[6] = ed_hei7;
 heiVals[7] = ed_hei8;
 heiVals[8] = ed_hei9;
 heiVals[9] = ed_hei10;

 valVals[0] = ed_val1;
 valVals[1] = ed_val2;
 valVals[2] = ed_val3;
 valVals[3] = ed_val4;
 valVals[4] = ed_val5;
 valVals[5] = ed_val6;
 valVals[6] = ed_val7;
 valVals[7] = ed_val8;
 valVals[8] = ed_val9;
 valVals[9] = ed_val10;


 boxWP[0] = gb_wp1;
 boxWP[1] = gb_wp2;
 boxWP[2] = gb_wp3;
 boxWP[3] = gb_wp4;
 boxWP[4] = gb_wp5;
 boxWP[5] = gb_wp6;
 boxWP[6] = gb_wp7;
 boxWP[7] = gb_wp8;
 boxWP[8] = gb_wp9;
 boxWP[9] = gb_wp10;

 etLatVals[0] = et_lat1;
 etLatVals[1] = et_lat2;
 etLatVals[2] = et_lat3;
 etLatVals[3] = et_lat4;
 etLatVals[4] = et_lat5;
 etLatVals[5] = et_lat6;
 etLatVals[6] = et_lat7;
 etLatVals[7] = et_lat8;
 etLatVals[8] = et_lat9;
 etLatVals[9] = et_lat10;

 etLonVals[0] = et_lon1;
 etLonVals[1] = et_lon2;
 etLonVals[2] = et_lon3;
 etLonVals[3] = et_lon4;
 etLonVals[4] = et_lon5;
 etLonVals[5] = et_lon6;
 etLonVals[6] = et_lon7;
 etLonVals[7] = et_lon8;
 etLonVals[8] = et_lon9;
 etLonVals[9] = et_lon10;

 etHeiVals[0] = et_hei1;
 etHeiVals[1] = et_hei2;
 etHeiVals[2] = et_hei3;
 etHeiVals[3] = et_hei4;
 etHeiVals[4] = et_hei5;
 etHeiVals[5] = et_hei6;
 etHeiVals[6] = et_hei7;
 etHeiVals[7] = et_hei8;
 etHeiVals[8] = et_hei9;
 etHeiVals[9] = et_hei10;

 cbStat[0] = cb_stat1;
 cbStat[1] = cb_stat2;
 cbStat[2] = cb_stat3;
 cbStat[3] = cb_stat4;
 cbStat[4] = cb_stat5;
 cbStat[5] = cb_stat6;
 cbStat[6] = cb_stat7;
 cbStat[7] = cb_stat8;
 cbStat[8] = cb_stat9;
 cbStat[9] = cb_stat10;

 etValVals[0] = et_val1;
 etValVals[1] = et_val2;
 etValVals[2] = et_val3;
 etValVals[3] = et_val4;
 etValVals[4] = et_val5;
 etValVals[5] = et_val6;
 etValVals[6] = et_val7;
 etValVals[7] = et_val8;
 etValVals[8] = et_val9;
 etValVals[9] = et_val10;

 cbRepStat[0] = cb_repstat1;
 cbRepStat[1] = cb_repstat2;
 cbRepStat[2] = cb_repstat3;
 cbRepStat[3] = cb_repstat4;
 cbRepStat[4] = cb_repstat5;
 cbRepStat[5] = cb_repstat6;
 cbRepStat[6] = cb_repstat7;
 cbRepStat[7] = cb_repstat8;
 cbRepStat[8] = cb_repstat9;
 cbRepStat[9] = cb_repstat10;


 // Mode Texts
 str_modes[CTRL_TYPE_MANUAL] = "Pilot Control";
 str_modes[CTRL_TYPE_PASS] = "Passthrough";
 str_modes[CTRL_TYPE_SEL_PIL] = "Selective Passthrough from Pilot";
 str_modes[CTRL_TYPE_AP_COMM] = "Direct Commands";
 str_modes[CTRL_TYPE_AP_WP] = "WayPoint Navigation";
 str_modes[CTRL_TYPE_SEL_AP] = "Selective Passthrough from AP";

 allGains = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::FormClose(TObject *Sender, TCloseAction &Action)
{

  // edit color changes
  tb_config->Edit();

  // save colors
  tb_configtrajectoryColorR->AsInteger = (int) GetRValue(cb_color1->Selected);
  tb_configtrajectoryColorG->AsInteger = (int) GetGValue(cb_color1->Selected);
  tb_configtrajectoryColorB->AsInteger = (int) GetBValue(cb_color1->Selected);

  tb_configtessalateColorR->AsInteger = (int) GetRValue(cb_color2->Selected);
  tb_configtessalateColorG->AsInteger = (int) GetGValue(cb_color2->Selected);
  tb_configtessalateColorB->AsInteger = (int) GetBValue(cb_color2->Selected);

  // commit changes
  tb_config->Post();

 tb_config->Close();

 if (bt_serial->Tag != 0){
    bt_serialClick(Sender);
 }
}
//---------------------------------------------------------------------------




void __fastcall TFPpal::bt_ppKmlClick(TObject *Sender)
{
  if (od_mainKml->Execute()){
  tb_config->Edit();
  switch (((TComponent*)Sender)->Tag){
         case 0:
              tb_configkmlFile->AsString = od_mainKml->FileName;
         break;
         case 1:
              tb_configplanePathFile->AsString = od_mainKml->FileName;
         break;
         case 2:
              tb_configiconFile->AsString = od_mainKml->FileName;
         break;
         case 3:
              tb_configwaypointFile->AsString = od_mainKml->FileName;
         break;
         case 4:
              ed_gs_file->Text = od_mainKml->FileName;
         break;
  }
    tb_config->Post();
 }
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::bt_gearthClick(TObject *Sender)
{
 createBlankKML(1);
 Timer1->Enabled = True;
}
//---------------------------------------------------------------------------

void TFPpal::createBlankKML(char KMLType){
   TiXmlDocument doc;

   // Create the document header
   TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );


   // Create the document root
   TiXmlElement * kmlRoot = new TiXmlElement( "kml" );
   // Set the the attribute for the tag
   kmlRoot->SetAttribute("xmlns","http://earth.google.com/kml/2.2");

   // create the network tag
   TiXmlElement * netTag = new TiXmlElement("NetworkLink");

   // add the basic structure
   addAndAppendNode("name","UAV Path", netTag);
   addAndAppendNode("open","1", netTag);
   addAndAppendNode("description","Path of the UAV as it Flies", netTag);
   addAndAppendNode("flyToView","0", netTag);

   // create the link tag
   TiXmlElement * linkTag = new TiXmlElement("Link");
   // add the basic structure
   addAndAppendNode("refreshMode","onInterval", linkTag);
   addAndAppendNode("refreshInterval", tb_configupdateRate->AsString.c_str(), linkTag);
   addAndAppendNode("refreshVisibility", "1", linkTag);
   addAndAppendNode("href",tb_configplanePathFile->AsString.c_str(), linkTag);

   // add the link tag to the net tag
   netTag->LinkEndChild(linkTag);

   // link it to the root
   kmlRoot->LinkEndChild(netTag);

   // Form the document
   doc.LinkEndChild( decl );
   doc.LinkEndChild( kmlRoot );

   // Write it
   doc.SaveFile( tb_configkmlFile->AsString.c_str() );

   // no clean-up necessary, doc owns decl and kmlRoot and KmlRoot owns netTag
   // so this is cleaned at stack cleanup
   // ref: http://sourceforge.net/forum/forum.php?thread_id=1794451&forum_id=172103
}
//---------------------------------------------------------------------------

void TFPpal::addAndAppendNode(char* name, char* value, TiXmlNode* appendTo){
   TiXmlElement* currentTag = new TiXmlElement(name);
   TiXmlText*  textNode = new TiXmlText(value);
   currentTag->LinkEndChild(textNode);
   appendTo->LinkEndChild(currentTag);
}

//---------------------------------------------------------------------------

void __fastcall TFPpal::cb_color1Exit(TObject *Sender)
{
    tb_config->Edit();
    tb_configtrajectoryColorR->AsInteger = (int) GetRValue(cb_color1->Selected);
    tb_configtrajectoryColorG->AsInteger = (int) GetGValue(cb_color1->Selected);
    tb_configtrajectoryColorB->AsInteger = (int) GetBValue(cb_color1->Selected);
    tb_config->Post();
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::cb_color2Exit(TObject *Sender)
{
   tb_config->Edit();
    tb_configtessalateColorR->AsInteger = (int) GetRValue(cb_color2->Selected);
    tb_configtessalateColorG->AsInteger = (int) GetGValue(cb_color2->Selected);
    tb_configtessalateColorB->AsInteger = (int) GetBValue(cb_color2->Selected);
    tb_config->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::kb_tessalateExit(TObject *Sender)
{
 tb_config->Edit();
 tb_configtessalateTransparency->AsInteger = kb_tessalate->Position;
 tb_config->Post();
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_serialClick(TObject *Sender)
{
 // if the tag is zero means the port is closed
 if  (bt_serial->Tag == 0){
   cp_serial->Open = True;
   bt_serial->Tag = 1;
   bt_serial->Caption = "Close Serial Port";
   ld_serial->StatusInt = 1;
   Timer2->Enabled = true;
   mt_x->Flow = true;
   mt_y->Flow = true;
   mt_z->Flow = true;
 } else {
   cp_serial->Open = False;
   bt_serial->Tag = 0;
   bt_serial->Caption = "Open Serial Port";
   ld_serial->StatusInt = 0;
   Timer2->Enabled = false;
   mt_x->Flow = false;
   mt_y->Flow = false;
   mt_z->Flow = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Timer2Timer(TObject *Sender)
{
   tGpsData temp = getGpsStruct();

   // if the lat and lon are within the distance limit
   if (computeDistance(temp.lat.flData, temp.lon.flData) < DISLIMIT ){
      // if there was a change in lat or lon
      //if (!compare_float(temp.lat.flData, gpsSamples[0].lat.flData) ||
      //    !compare_float(temp.lon.flData, gpsSamples[0].lon.flData)){
      if ((temp.lat.flData != gpsSamples[0].lat.flData) ||
          (temp.lon.flData != gpsSamples[0].lon.flData)){
           //replace the history
          for (int i = 13; i>=0; i--){
             gpsSamples[i+1] = gpsSamples[i];
          }
      } else {// if update
         // mm_diagnose->Lines->Add("Failed update " + FloatToStr(temp.lat.flData)
         //  + " " + FloatToStr(gpsSamples[0].lat.flData));
      }
   } else {//if within distance
      //mm_diagnose->Lines->Add("Distance bigger than 30 Km: " +
      //FloatToStr(computeDistance(temp.lat.flData, temp.lon.flData)));
   }

   gpsSamples[0] = temp;
   rawSample = getRawStruct();
   attitudeSample = getAttStruct();
   xyzSample  = getXYZStruct();
   dynSample  = getDynStruct();
   biasSample = getBiasStruct();
   diagSample = getDiagStruct();
   statusSample = getSensStruct();
   pilControlSample = getPilotStruct();
   pwmSample =  getPWMStruct();
   aknSample = getAknStruct();
   pidSample = getPidStruct();
   wpsSample = getWPStruct();
   apsSample = getAPSStruct();
   comSample = getComStruct();

   updateAkn();

   updateGPSLabels();                 
   updateRawLabels();
   updateAttitudeLabels();

   updateBiasLabels();
   updateDynLabels();
   updateDiagLabels();
   updatePilotLabels();

   updatePlots();
   updateAttitude();

   updatePWM();
   updatePID();
   updateWP();
   updateStatus();

   et_fail ->Caption = FormatFloat("0.0000E+00",csFail);


}
//---------------------------------------------------------------------------
void TFPpal::updateAkn(void){
  // COntrol MCU Reboot
  if (aknSample.reboot == 1){
      //ShowMessage("WARNING: S Reboot");
      if (et_warning ->Color != clBtnFace)
          et_warning->Caption = et_warning->Caption + ". Control MCU Reset Detected";
      else
          et_warning->Caption = "Control MCU Reset Detected";
      et_warning->Color = clRed;
      setAknReboot (0);
   }

   // Sensor MCU Reboot
     if (aknSample.sensorReboot == 1){
      //ShowMessage("WARNING: S Reboot");
      if (et_warning ->Color != clBtnFace)
          et_warning->Caption = et_warning->Caption + ". Sensor MCU Reset Detected";
      else
          et_warning->Caption = "Sensor MCU Reset Detected";
      setAknSensorReboot (0);
      et_warning->Color = clRed;      
   }

   if (aknSample.pidCal >= 1 ){
      if (aknSample.pidCal <=10){
         BoxCont[aknSample.pidCal-1]->Color = clGreen;
      } else {
         switch (aknSample.pidCal){
             case PIDEEP_WRITE_FAIL: // WRITE FAILED
                et_warning->Color = clYellow;
                et_warning->Caption = "EEPROM Write Failed. Value Changed Only in Structs";
             break;
             case PIDEEP_PAGE_EXP: // INIT FAILED. ALL PAGES EXPIRED
                et_warning->Color = clYellow;
                et_warning->Caption = "All EEPROM Pages Have expired";
             break;
             case PIDEEP_MEMORY_CORR: // INIT FAILED. EEPROM CORRUPTED
                et_warning->Color = clRed;
                et_warning->Caption = "EEPROM Corrupted. Need to Reinitialize";
             break;
         }
      }

      setAknPidCal(0);
   }

   if (aknSample.WP >= 1 ){
      if (aknSample.WP <=11){
         if (aknSample.WP < 11)
            boxWP[aknSample.WP-1]->Color = clGreen;
         else
            ed_gs_file ->Color = clGreen;

      } else {
         switch (aknSample.WP){
             case WPSEEP_WRITE_FAIL: // WRITE FAILED
                et_warning->Color = clYellow;
                et_warning->Caption = "EEPROM Write Failed. Value Changed Only in Structs";
             break;
             case WPSEEP_PAGE_EXP: // INIT FAILED. ALL PAGES EXPIRED
                et_warning->Color = clYellow;
                et_warning->Caption = "All EEPROM Pages Have expired";
             break;
             case WPSEEP_MEMORY_CORR: // INIT FAILED. EEPROM CORRUPTED
                et_warning->Color = clRed;
                et_warning->Caption = "EEPROM Corrupted. Need to Reinitialize";
             break;
         }
      }

      setAknWpCal(0);
   }

    if (aknSample.commands >= 1 ){
       switch (aknSample.commands){
        case COMM_TYPE_HEIGHT:
          ed_height->Color = clWhite;
        break;

        case COMM_TYPE_TURNRATE:
          ed_r->Color = clWhite;
        break;

        case COMM_TYPE_AIRSPEED:
          ed_airspeed->Color = clWhite;
        break;

        case COMM_TYPE_GOTO_WP:
          ed_gotowp->Color = clWhite;
        break;

       }
       setAknComCal(0);
    }
}
//---------------------------------------------------------------------------
void TFPpal::updateGPSLabels(void){
   // update the display
   // ========= GPS =============
   et_date->Caption = IntToStr(gpsSamples[0].month) + "/" +
                      IntToStr(gpsSamples[0].day) + "/" +
                      IntToStr(gpsSamples[0].year);
   et_time->Caption = IntToStr(gpsSamples[0].hour) + ":" +
                      IntToStr(gpsSamples[0].min) + ":" +
                      IntToStr(gpsSamples[0].sec);

   et_lat->Caption = FormatFloat("0.0000000",gpsSamples[0].lat.flData);
   et_lon->Caption = FormatFloat("0.0000000",gpsSamples[0].lon.flData);
   et_height->Caption = FormatFloat("0.000",gpsSamples[0].height.flData);

   et_cog->Caption = IntToStr(gpsSamples[0].cog.usData);
   et_sog->Caption = IntToStr(gpsSamples[0].sog.usData);
   et_airspeed_cmds->Caption = FormatFloat("0.00",pwmSample.da2_c.usData/1000.0);

   et_hdop->Caption = IntToStr(gpsSamples[0].hdop.usData);
   et_fix->Caption = (gpsSamples[0].fix == 1)? "Yes": "No";

   et_sats->Caption = IntToStr(gpsSamples[0].sats);

}

void TFPpal::updateRawLabels(void){
   // update the display
   // ========= Raw =============
   et_accelx->Caption = IntToStr(rawSample.accelX.shData);
   et_accely->Caption = IntToStr(rawSample.accelY.shData);
   et_accelz->Caption = IntToStr(rawSample.accelZ.shData);

   et_gyrox->Caption = IntToStr(rawSample.gyroX.shData);
   et_gyroy->Caption = IntToStr(rawSample.gyroY.shData);
   et_gyroz->Caption = IntToStr(rawSample.gyroZ.shData);

   et_magx->Caption = IntToStr(rawSample.magX.shData);
   et_magy->Caption = IntToStr(rawSample.magY.shData);
   et_magz->Caption = IntToStr(rawSample.magZ.shData);

   et_baro->Caption = IntToStr(rawSample.baro.shData);
   et_pitot->Caption = IntToStr(rawSample.pito.shData);
   et_therm->Caption = IntToStr(rawSample.ther.shData);
   et_power->Caption = IntToStr(rawSample.powr.shData);
}

void TFPpal::updateAttitudeLabels(void){
   // update the display
   // ========= Raw =============
   /*et_x->Caption = FloatToStr(-RAD2DEG*xyzSample.Xcoord.flData);
   et_y->Caption = FloatToStr(RAD2DEG*xyzSample.Ycoord.flData);
   et_z->Caption = FloatToStr(RAD2DEG*xyzSample.Zcoord.flData);

   et_vx->Caption = FloatToStr(-RAD2DEG*xyzSample.VX.flData);
   et_vy->Caption = FloatToStr(RAD2DEG*xyzSample.VY.flData);
   et_vz->Caption = FloatToStr(RAD2DEG*xyzSample.VZ.flData);

   et_p->Caption = FloatToStr(-RAD2DEG*attitudeSample.p.flData);
   et_q->Caption = FloatToStr(RAD2DEG*attitudeSample.q.flData);
   et_r->Caption = FloatToStr(RAD2DEG*attitudeSample.r.flData);

   et_phi->Caption = FloatToStr(-RAD2DEG*attitudeSample.roll.flData);
   et_theta->Caption = FloatToStr(RAD2DEG*attitudeSample.pitch.flData);
   et_psi->Caption = FloatToStr(RAD2DEG*attitudeSample.yaw.flData);*/


   et_x->Caption = FormatFloat("0.00",xyzSample.Xcoord.flData);
   et_y->Caption = FormatFloat("0.00",xyzSample.Ycoord.flData);
   et_z->Caption = FormatFloat("0.00",xyzSample.Zcoord.flData);
   et_height_cmds->Caption = FormatFloat("0.00",xyzSample.Zcoord.flData);

   gr_height->Value = xyzSample.Zcoord.flData;

   et_vx->Caption = FormatFloat("0.00",xyzSample.VX.flData);
   et_vy->Caption = FormatFloat("0.00",xyzSample.VY.flData);
   et_vz->Caption = FormatFloat("0.00",xyzSample.VZ.flData);

   et_p->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.p.flData);
   et_q->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.q.flData);
   et_r->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.r.flData);
   et_turnrate_cmds->Caption = FormatFloat("0.00",attitudeSample.r.flData);


   et_phi->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.roll.flData);
   et_theta->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.pitch.flData);
   et_psi->Caption = FormatFloat("0.0000",RAD2DEG*attitudeSample.yaw.flData);

   et_timeStamp->Caption =  IntToStr(attitudeSample.timeStamp.usData);
}

void TFPpal::updatePlots(void){
   mt_x->ValueCh1 = xyzSample.Zcoord.flData;
   mt_x->ValueCh2 = comSample.hCommand.flData;

   mt_y->ValueCh1 = pwmSample.da2_c.usData/1000.0;
   mt_y->ValueCh2 = comSample.airspeedCommand.flData;

   mt_z->ValueCh1 = RAD2DEG*attitudeSample.roll.flData;
   mt_z->ValueCh2 = RAD2DEG*((pwmSample.dre_c.usData - 32768.0)/1000.0);
}

void TFPpal::updateBiasLabels(void){
  et_axb->Caption = FormatFloat("0.0000",biasSample.axb.flData);
  et_ayb->Caption = FormatFloat("0.0000",biasSample.ayb.flData);
  et_azb->Caption = FormatFloat("0.0000",biasSample.azb.flData);
  et_gxb->Caption = FormatFloat("0.0000",biasSample.gxb.flData);
  et_gyb->Caption = FormatFloat("0.0000",biasSample.gyb.flData);
  et_gzb->Caption = FormatFloat("0.0000",biasSample.gzb.flData);

}
void TFPpal::updateDynLabels(void){
  et_dyn->Caption = FormatFloat("0.00",dynSample.dynamic.flData);
  et_sta->Caption = FormatFloat("0.00",dynSample.stat.flData);
  et_temp->Caption = FormatFloat("0.00",dynSample.temp.shData/10.0);

  // sensor mcu status
  et_load->Caption = IntToStr(statusSample.load);
  et_vdetect->Caption = IntToStr(statusSample.vdetect);
  et_volt->Caption = FormatFloat("0.00",statusSample.bVolt.usData/1000.0);

  gr_batt->Value = statusSample.bVolt.usData;

  // THIS IS HACK and need to be solved currently using the PWMCommand AUX2 to
  // report airspeed back
  // ==================================================
  et_a2c->Caption  =  FormatFloat("0.00",pwmSample.da2_c.usData/1000.0);
}
void TFPpal::updateDiagLabels(void){
  et_fl1->Caption = FormatFloat("0.0000",diagSample.fl1.flData);
  et_fl2->Caption = FormatFloat("0.0000",diagSample.fl2.flData);
  et_fl3->Caption = FormatFloat("0.0000",diagSample.fl3.flData);
  et_sh1->Caption = IntToStr( diagSample.sh1.shData);
  et_sh2->Caption = IntToStr( diagSample.sh2.shData);
  et_sh3->Caption = IntToStr( diagSample.sh3.shData);
}

void TFPpal::updatePilotLabels(void){
  et_dla->Caption =  IntToStr(Floor(pilControlSample.dla.usData*0.2+20.0));
  et_dt->Caption = IntToStr(Floor(pilControlSample.dt.usData*0.2+20.0));
  et_dra->Caption = IntToStr(Floor(pilControlSample.dra.usData*0.2+20.0));
  et_de->Caption =  IntToStr(Floor(pilControlSample.de.usData*0.2+20.0));
  et_dr->Caption =  IntToStr(Floor(pilControlSample.dr.usData*0.2+20.0));

  gr_dt->Value = StrToInt(et_dt->Caption);
  gr_dr->Value = StrToInt(et_dr->Caption);
  gr_da->Value = StrToInt(et_dla->Caption);
  gr_de->Value = StrToInt(et_dra->Caption);


  et_dla->Caption = IntToStr(pilControlSample.dla.usData);
  et_dt->Caption =  IntToStr(pilControlSample.dt.usData);
  et_dra->Caption = IntToStr(pilControlSample.dra.usData);
  et_de->Caption =  pilControlSample.de.usData > 6000 ? "Manual":"Auto";
  et_dr->Caption =  IntToStr(pilControlSample.dr.usData);
}


void TFPpal::updatePWM(void){
  et_dtc->Caption  =  IntToStr(pwmSample.dt_c.usData);
  et_dlac->Caption =  IntToStr(pwmSample.dla_c.usData);
  et_drac->Caption =  IntToStr(pwmSample.dra_c.usData);
  et_drc->Caption  =  IntToStr(pwmSample.dr_c.usData);
  et_dlec->Caption =  IntToStr(pwmSample.dle_c.usData);
  et_drec->Caption =  IntToStr(pwmSample.dre_c.usData);
  et_dlfc->Caption =  IntToStr(pwmSample.dlf_c.usData);
  et_drfc->Caption =  IntToStr(pwmSample.drf_c.usData);
  et_a1c->Caption  =  IntToStr(pwmSample.da1_c.usData);

}


void TFPpal::updatePID(void){
unsigned char i;
  for (i=0; i<10;i++){
     EtPGains[i]->Caption  =  FloatToStr(pidSample.P[i].flData);
     EtIGains[i]->Caption  =  FloatToStr(pidSample.I[i].flData);
     EtDGains[i]->Caption  =  FloatToStr(pidSample.D[i].flData);
  }
}


void TFPpal::updateWP(void){
unsigned char i;
  for (i=0; i<10;i++){
     etLatVals[i]->Caption  =  FloatToStr(wpsSample.lat[i].flData);
     etLonVals[i]->Caption  =  FloatToStr(wpsSample.lon[i].flData);
     etHeiVals[i]->Caption  =  FloatToStr(wpsSample.hei[i].flData);
     cbRepStat[i]->Checked  =  wpsSample.typ[i]==1?true:false;
     etValVals[i]->Caption  =  wpsSample.val[i].shData;
  }
}

void TFPpal::updateStatus(void){
   // update Status Panel
   et_status ->Caption = "Status: " +  str_modes[apsSample.controlType];
   if (apsSample.controlType != rg_modes->Tag ) {
      pn_status->Color = clRed;
   } else {
      pn_status->Color = clActiveBorder;
   }

   if (apsSample.controlType == CTRL_TYPE_MANUAL) {
      bt_mode->Enabled = false;
      rb_manual->Checked = true;
   } else {
      bt_mode->Enabled = true;
      rb_auto->Checked = true;
   }
   rb_manualClick(NULL);

      
   bt_mode->Enabled =  !(apsSample.controlType == CTRL_TYPE_MANUAL);


   // update the passtrough config
   cb_repptpdt->Checked = apsSample.dt_pass;
   cb_repptpdla->Checked = apsSample.dla_pass;
   cb_repptpdra->Checked = apsSample.dra_pass;
   cb_repptpdr->Checked = apsSample.dr_pass;
   cb_repptpdle->Checked = apsSample.dle_pass;
   cb_repptpdre->Checked = apsSample.dre_pass;
   cb_repptpdlf->Checked = apsSample.dlf_pass;
   cb_repptpdrf->Checked = apsSample.drf_pass;

   // update the Commands Labels
   et_gotowp->Caption = IntToStr(comSample.currWPCommand);
   et_heightcomm->Caption = FloatToStr(comSample.hCommand.flData);
   et_airspeed->Caption = FloatToStr(comSample.airspeedCommand.flData);
   et_rcommand->Caption = FloatToStr(comSample.rCommand.flData);
}


void __fastcall TFPpal::cp_serialTriggerAvail(TObject *CP, WORD Count)
{
  int logSize = 254;
  unsigned char fromSerial[254+1];
  int bytesRemain = Count;
  //et_count->Caption = IntToStr(Count);
  try {
    while (bytesRemain > 0) {
       if (bytesRemain <= logSize) {
         cp_serial->GetBlock(&fromSerial[1], bytesRemain);
         fromSerial[0] = Count;
         bytesRemain = 0;
       } else{
         cp_serial->GetBlock(&fromSerial[1], logSize);
         fromSerial[0] = logSize;
         bytesRemain -= logSize;
       }
       if (logIsOpen==true)
         csFail = protParseDecode (&fromSerial[0], liveLog);
       else
         csFail = protParseDecode (&fromSerial[0],  NULL);
    }
  }
   catch (...) {
      mm_diagnose->Lines->Add("Exception Caught");
  }

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Timer1Timer(TObject *Sender)
{
   // Timer 1 Updates Google Earth Data;
   updateKML();
}
//---------------------------------------------------------------------------

void TFPpal::updateKML(void){
   String tmp ="";

   TiXmlDocument doc;

   // Create the document header
   TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );

   // Create the document root
   TiXmlElement * kmlRoot = new TiXmlElement( "kml" );
   // Set the the attribute for the tag
   kmlRoot->SetAttribute("xmlns","http://earth.google.com/kml/2.2");

   // create the Document tag
   TiXmlElement * docTag = new TiXmlElement("Document");

   // ============== DOCUMENT STYLES ===========================
   // ----------- Trajectory Style------------------
   TiXmlElement * styleTag = new TiXmlElement("Style");
   styleTag->SetAttribute("id", "planeTrajectory");

   // create the Line Style
   TiXmlElement * lineStyleTag = new TiXmlElement("LineStyle");

   // Add the sytles
   tmp =  getHexColor(1);
   addAndAppendNode("color",tmp.c_str(), lineStyleTag);
   addAndAppendNode("width","4", lineStyleTag);
   styleTag->LinkEndChild(lineStyleTag);

   // create the Poly Style
   TiXmlElement * polyStyleTag = new TiXmlElement("PolyStyle");
   // add the color
   tmp = getHexColor(2);
   addAndAppendNode("color",tmp.c_str(), polyStyleTag);
   styleTag->LinkEndChild(polyStyleTag);

   // Add them to the document
   docTag->LinkEndChild(styleTag);

   // ----------- Icon Style------------------
   TiXmlElement * iconStyleTag = new TiXmlElement("Style");
   iconStyleTag->SetAttribute("id", "planeIcon");

   addAndAppendNode("scale","1.0", iconStyleTag);

   // Create the icon tag
   TiXmlElement * iconTag = new TiXmlElement("Icon");
   addAndAppendNode("href",tb_configiconFile->AsString.c_str(), iconTag);

   // Add the icon to the iconstyle
   iconStyleTag->LinkEndChild(iconTag);
   // Add the iconStyle to the document
   docTag->LinkEndChild(iconStyleTag);

   // ============== PLANE TRAJECTORY ==================
   // create the Placemark node
   TiXmlElement * placemarkTag = new TiXmlElement("Placemark");
   // add the Name
   addAndAppendNode("name","UAV Path", placemarkTag);
   // add the style used to plot tha trajectory
   addAndAppendNode("styleUrl","#planeTrajectory", placemarkTag);

   // Add the line string
   TiXmlElement * lineStringTag = new TiXmlElement("LineString");
   // configure the lineString
   addAndAppendNode("tessalate",tb_configtessellate->AsString.c_str(), lineStringTag);
   addAndAppendNode("extrude","1", lineStringTag);
//   addAndAppendNode("altitudeMode","absolute", lineStringTag);
   addAndAppendNode("altitudeMode","clampToGround", lineStringTag);
   tmp = getPlaneCoordinates();
   addAndAppendNode("coordinates",tmp.c_str(), lineStringTag);

   // add the lineString to the placemark
   placemarkTag->LinkEndChild(lineStringTag);
   // add the placemark to the document
   docTag->LinkEndChild(placemarkTag);


   // ============== AIRPLANE ICON ===========================
   // create the UAV Icon Placemark node
   TiXmlElement * iconPlacemarkTag = new TiXmlElement("Placemark");
   // add the Name
   addAndAppendNode("name","", iconPlacemarkTag);
   // add the style used to plot the last known position
   addAndAppendNode("styleUrl","#planeIcon", iconPlacemarkTag);

   // Add the line string
   TiXmlElement * pointTag = new TiXmlElement("Point");

   // configure the Point
   addAndAppendNode("altitudeMode","clampToGround", pointTag);
   tmp = FloatToStr(gpsSamples[0].lon.flData)  + ", "
         + FloatToStr(gpsSamples[0].lat.flData)  + ", " +
         FloatToStr(gpsSamples[0].height.flData);

   addAndAppendNode("coordinates",tmp.c_str(), pointTag);

   // add the lineString to the placemark
   iconPlacemarkTag->LinkEndChild(pointTag);
   // add the placemark to the document
   docTag->LinkEndChild(iconPlacemarkTag);


   // ==================  DOCUMENT ========================
   // add the document to the root
   kmlRoot->LinkEndChild(docTag);

   // include the declaration in the document
   doc.LinkEndChild(decl);
   // include the root in the document
   doc.LinkEndChild(kmlRoot);

   // write the file
   doc.SaveFile(tb_configplanePathFile->AsString.c_str() );

}
//---------------------------------------------------------------------------

String TFPpal::getHexColor(unsigned char whichColor){
   String strVal = "";
   switch (whichColor){
       case 1: // AC Trajectory
            strVal = IntToHex(255,2) +
                     IntToHex(tb_configtrajectoryColorB->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorG->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorR->AsInteger,2);
       break;
       case 2:
            strVal = IntToHex(tb_configtessalateTransparency->AsInteger,2) +
                     IntToHex(tb_configtessalateColorB->AsInteger,2) +
                     IntToHex(tb_configtessalateColorG->AsInteger,2) +
                     IntToHex(tb_configtessalateColorR->AsInteger,2);
       break;
   }

   return strVal;

}
//---------------------------------------------------------------------------

String TFPpal::getPlaneCoordinates(void){
  // freeze the data in case the interrupt changes at mid update
  tGpsData tmpPos[15];
  String strVal = "";
  char i;

  for (i = 0; i< tb_configtailLength->AsInteger; i++){
     tmpPos[i] = gpsSamples[i];
  }

  for (i = 0; i< tb_configtailLength->AsInteger; i++){
     strVal = strVal + FloatToStr(tmpPos[i].lon.flData)  + ", "
              + FloatToStr(tmpPos[i].lat.flData)  + ", " +
               FloatToStr(tmpPos[i].height.flData)  + " ";
//               250  + " ";
  }



  return strVal;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::rg_tailExit(TObject *Sender)
{
 if (tb_config->State == dsEdit){
    tb_config->Post();
 }
}
//---------------------------------------------------------------------------




void __fastcall TFPpal::bt_gsposClick(TObject *Sender)
{
TiXmlDocument doc(ed_gs_file->Text.c_str());
TiXmlHandle hDoc (&doc);
TiXmlElement* root;
TiXmlElement* pElem;
TiXmlHandle hRoot(0);
char coordVals [1000];

float latGs[5], lonGs[5], heiGs[5];
char* pch;
unsigned char i;


unsigned char filtMsg[25];
unsigned char rawMsg[16];
tFloatToChar lat, lon, hei;




  // if loading the file succeeds
  if( doc.LoadFile()){
     // get the Root node (<kml>)
     root= hDoc.FirstChildElement().Element();
     mm_diagnose->Lines->Add(root->Value());
     hRoot = TiXmlHandle(root);

     // get the Document node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());

     // Get the children of Document
     hRoot = TiXmlHandle(pElem);
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "Placemark") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case placemark is never found
     }

     // Placemark node has been found
     hRoot = TiXmlHandle(pElem);


     // Now find the Point node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "Point") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case point is never found
     }

     // Point node has been found
     hRoot = TiXmlHandle(pElem);

     // Now find the coordinates node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "coordinates") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case coordinates is never found
     }

     // Get the actual coordinates
     mm_diagnose->Lines->Add(pElem->GetText());

     strcpy((char *)&coordVals,pElem->GetText());

     pch = strtok((char *)&coordVals, ", ");
     mm_diagnose->Lines->Add("==============");
     mm_diagnose->Lines->Add(pch);

     //memset(&coordinate, '\0', sizeof(coordinate));
     i = 0;

     while (pch != NULL || i > 4)
     {
       lonGs[i] = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       latGs[i] = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       heiGs[i] = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       i++;
     }

     // change the color to red to aknowledge that it need to be uploaded
     ed_gs_file->Color = clRed;

     // =============== Save data to DB  =====================
     tb_config->Edit();
     tb_configlatGS->AsFloat = latGs[0];
     tb_configlonGS->AsFloat = lonGs[0];
     tb_configheightGS->AsFloat = heiGs[0];
     tb_config->Post();

     // =========== Send Data to Autopilot ====================


     // Collect the values
     lat.flData =  latGs[0];
     lon.flData =  lonGs[0];
     hei.flData =  heiGs[0];


     rawMsg[0]    =    10;
     rawMsg[1]    =    lat.chData[0];
     rawMsg[2]    =    lat.chData[1];
     rawMsg[3]    =    lat.chData[2];
     rawMsg[4]    =    lat.chData[3];
     rawMsg[5]    =    lon.chData[0];
     rawMsg[6]    =    lon.chData[1];
     rawMsg[7]    =    lon.chData[2];
     rawMsg[8]    =    lon.chData[3];
     rawMsg[9]    =    hei.chData[0];
     rawMsg[10]    =   hei.chData[1];
     rawMsg[11]   =    hei.chData[2];
     rawMsg[12]   =    hei.chData[3];
     rawMsg[13]   =    0;
     rawMsg[14]   =    0;
     rawMsg[15]   =    0;

     assembleMsg(&rawMsg[0],WPSMSG_LEN,WPSMSG_ID,&filtMsg[0]);

     cp_serial->PutBlock(&filtMsg[0],(WPSMSG_LEN+7));

  }  // if filed opened succesfully
  else {
    ShowMessage("WayPoint File Not Found");
  }



 
}
//---------------------------------------------------------------------------
// formula from:
// http://www.codeguru.com/cpp/cpp/algorithms/article.php/c5115
float TFPpal::computeDistance(float lat, float lon){
 float lat2 = tb_configlatGS->AsFloat;
 float lon2 = tb_configlonGS->AsFloat;

 try{

     return EARTHRADIUS*acos(cos(deg2Rad(90.0-lat))*cos(deg2Rad(90.0-lat2))+
     sin(deg2Rad(90.0-lat))*sin(deg2Rad(90.0-lat2))*cos(deg2Rad(lon-lon2)));
 }
 catch (...) {
     mm_diagnose->Lines->Add("ComputeDistance exception");
     return DISLIMIT + 1.0;
 }

}

float TFPpal::deg2Rad(float mDeg){
 return mDeg*PI/180.0;
}

//---------------------------------------------------------------------------

void TFPpal::updateAttitude(void)
{
try{

  if ( abs((int)attitudeSample.roll.flData) < 7 &&
       abs((int)attitudeSample.pitch.flData) < 7  &&
       abs((int)attitudeSample.yaw.flData) < 7){
          ai_att->Roll = -RAD2DEG*attitudeSample.roll.flData;
          ai_att->Pitch = RAD2DEG*attitudeSample.pitch.flData;
          ai_att->Course = RAD2DEG*attitudeSample.yaw.flData;
  }
 }
 catch (...) {
     mm_diagnose->Lines->Add("ComputeDistance exception");
 }

/*
  ai_copy->Roll = -RAD2DEG*attitudeSample.p.flData;
  ai_copy->Pitch = RAD2DEG*attitudeSample.q.flData;
  ai_copy->Course = RAD2DEG*attitudeSample.r.flData;
 */
}
//---------------------------------------------------------------------------


void TFPpal::assembleMsg(unsigned char* rawData , unsigned char size, unsigned char type, unsigned char* protMsg ){
	unsigned char i;
	// start the header
	*(protMsg+0) = DOLLAR;
	*(protMsg+1) = AT;
	*(protMsg+2) = type;
	*(protMsg+3) = size;
	for( i = 0; i < size; i += 1 )
	{
		*(protMsg+i+4) = *(rawData +i);
	}
	*(protMsg+size+4) = STAR;
	*(protMsg+size+5) = AT;
	*(protMsg+size+6) = getChecksum(protMsg, (size+5));
}
//---------------------------------------------------------------------------
void __fastcall TFPpal::bt_filterClick(TObject *Sender)
{
 // 32 64 205 1 1 42 64 141

 unsigned char filtMsg[8];
 unsigned char rawMsg[2];

 rawMsg[0] = bt_filter->Tag?0:1;

 bt_filter->Tag ^=1;

 if (!bt_filter->Tag){

    if (StartButton->Enabled){
       StartButtonClick(Sender);
       }

    if (bt_startSend->Enabled){
       bt_startSendClick(Sender);
    }
 }

 ld_filter->StatusInt= bt_filter->Tag;

 bt_filter->Caption = bt_filter->Tag? "HIL Off":"HIL On";

 assembleMsg(&rawMsg[0],FILMSG_LEN,FILMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(FILMSG_LEN+7));

}
//---------------------------------------------------------------------------





void __fastcall TFPpal::bt_onflightexpClick(TObject *Sender)
{
/* if (od_exports->Execute()){
  tb_config->Edit();
  switch (((TComponent*)Sender)->Tag){
         case 0:
              tb_configExportLocation->AsString = od_exports->FileName;
         break;
         case 1:
              tb_configplanePathFile->AsString = od_mainKml->FileName;
         break;
         case 2:
              tb_configiconFile->AsString = od_mainKml->FileName;
         break;
         case 3:
              tb_configwaypointFile->AsString = od_mainKml->FileName;
         break;
  }
    tb_config->Post();
 }             */
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_exportAfterDialog(TObject *Sender,
      AnsiString &Name, bool &Action)
{
 tb_config->Edit();
 tb_configExportLocation->AsString = Name;
 tb_config->Post();

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::cb_inflightClick(TObject *Sender)
{
 if (cb_inflight->Checked){
    String logFileName;
    if (cb_over->Checked == false){
       logFileName = ed_liveLog->FileName +
                           FormatDateTime("_dd_mm_yy_hh_nn_ss", Now()) + ".log";
    } else {
       logFileName = ed_liveLog->FileName + ".log";
    }

    cb_over->Enabled = false;
    ed_liveLog->Enabled = True;
    liveLog = fopen(logFileName.c_str(), "wt");

	if (!liveLog)
	{
		ShowMessage("Unable to create Live Log file, continuing without logging");
        cb_inflight->Checked = false;
        cb_over->Enabled = true;
        cb_inflightClick(NULL);
	} else{
        logIsOpen = true;
        printFileHeader(liveLog);
    }
} else {
    ed_liveLog->Enabled = False;
    cb_over->Enabled = true;
    if(logIsOpen) fclose(liveLog);
    logIsOpen = false;
}
}
//---------------------------------------------------------------------------


void __fastcall TFPpal::bt_importLogClick(TObject *Sender)
{
    FILE* logFile;
    FILE* matFile;

    unsigned char buffer[97];
    unsigned long fileLen;
    unsigned long i;
    //unsigned char amountToRead = 24;
    String toMatFile;

    //Open files
    logFile = fopen(ed_importLog->FileName.c_str(), "rb");
    matFile = fopen(ed_exportMat->FileName.c_str(), "wt");

    if (!logFile){
       ShowMessage("Unable to open Log file");
    }else {
        if (!matFile){
               ShowMessage("Unable to create CSV file");
        } else {
	       //Get file length
	       fseek(logFile, 0, SEEK_END);
	       fileLen=ftell(logFile);
	       fseek(logFile, 0, SEEK_SET);

               // print header into MatFile
               printFileHeader(matFile);

	       //Read file contents into buffer and write to file
               i = 0;
               while (i<fileLen-96){
	         fread(&(buffer[0]) + 1, sizeof(unsigned char), 96, logFile);
                 i+=96;
                 buffer[0] = 96;
                 protParseDecode(buffer, matFile);
               } // while

           // close th files
           fclose(logFile);
           fclose(matFile);
        }// else !matfile
    } // else !logfile
    // E:\LOG4.TXT
    // C:\Mariano\UCSC\APCode\GroundStation\FlightLogs\ST.csv
}
//---------------------------------------------------------------------------


void __fastcall TFPpal::FormDestroy(TObject *Sender)
{
  if(logIsOpen) fclose(liveLog);
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_liveLogAfterDialog(TObject *Sender,
      AnsiString &Name, bool &Action)
{
    if(logIsOpen) fclose(liveLog);
    String logFileName = Name +
                           FormatDateTime("_dd_mm_yy_hh_nn_ss", Now());
    liveLog = fopen(logFileName.c_str(), "wt");

	if (!liveLog)
	{
		ShowMessage("Unable to create Live Log file, continuing without logging");
        cb_inflight->Checked = False;
        cb_inflightClick(NULL);
	} else{
        logIsOpen = true;
    }
}
//---------------------------------------------------------------------------

void TFPpal::printFileHeader(FILE* fileLog){
           fprintf(fileLog,"% This is a log File for the UCSC AP data is organized as follows:\n" );
           fprintf(fileLog,"%\n" );
           fprintf(fileLog,"% (1)Time Stamp in Ticks (multiply by AP Sampling time to get Seconds) \n" );
           fprintf(fileLog,"% (2)Roll (rad)  \n" );
           fprintf(fileLog,"% (3)Pitch (rad)  \n" );
           fprintf(fileLog,"% (4)Yaw (rad)   \n" );
           fprintf(fileLog,"% (5)P (rad)   \n" );
           fprintf(fileLog,"% (6)Q (rad)   \n" );
           fprintf(fileLog,"% (7)R (rad)   \n" );
           fprintf(fileLog,"% (8)X (m)   \n" );
           fprintf(fileLog,"% (9)Y (m)  \n" );
           fprintf(fileLog,"% (10)Z (m)   \n" );
           fprintf(fileLog,"% (11)Vx (m/s)  \n" );
           fprintf(fileLog,"% (12)Vy (m/s)  \n" );
           fprintf(fileLog,"% (13)Vz (m/s)  \n" );
           fprintf(fileLog,"% (14)GPS Year   \n" );
           fprintf(fileLog,"% (15)GPS Month  \n" );
           fprintf(fileLog,"% (16)GPS Day  \n" );
           fprintf(fileLog,"% (17)GPS Hour   \n" );
           fprintf(fileLog,"% (18)GPS min  \n" );
           fprintf(fileLog,"% (19)GPS sec  \n" );
           fprintf(fileLog,"% (20)GPS Lat (deg)  \n" );
           fprintf(fileLog,"% (21)GPS Lon (deg) \n" );
           fprintf(fileLog,"% (22)GPS Height (m)  \n" );
           fprintf(fileLog,"% (23)GPS COG (deg)  \n" );
           fprintf(fileLog,"% (24)GPS SOG (m/s)  \n" );
           fprintf(fileLog,"% (25)GPS Hdop (in hundreths of unit)  \n" );
           fprintf(fileLog,"% (26)GPS fix? (yes or no) \n" );
           fprintf(fileLog,"% (27)GPS Number of Sats Used  \n" );
           fprintf(fileLog,"% (28)GPS New Val? \n" );
           fprintf(fileLog,"% (29)Raw Gyro X  \n" );
           fprintf(fileLog,"% (30)Raw Gyro Y \n" );
           fprintf(fileLog,"% (31)Raw Gyro Z  \n" );
           fprintf(fileLog,"% (32)Raw Accel X  \n" );
           fprintf(fileLog,"% (33)Raw Accel Y  \n" );
           fprintf(fileLog,"% (34)Raw Accel Z  \n" );
           fprintf(fileLog,"% (35)Raw Mag X  \n" );
           fprintf(fileLog,"% (36)Raw Mag Y \n" );
           fprintf(fileLog,"% (37)Raw Mag Z \n" );
           fprintf(fileLog,"% (38)Raw Barometer \n" );
           fprintf(fileLog,"% (39)Raw Pitot \n" );
           fprintf(fileLog,"% (40)Raw Powr \n" );
           fprintf(fileLog,"% (41)Raw Thermistor \n" );
           fprintf(fileLog,"% (42)Bias Accel X (m/s) \n" );
           fprintf(fileLog,"% (43)Bias Accel Y (m/s) \n" );
           fprintf(fileLog,"% (44)Bias Accel Z (m/s) \n" );
           fprintf(fileLog,"% (45)Bias Gyro X  (rad/s) \n" );
           fprintf(fileLog,"% (46)Bias Gyro Y  (rad/s) \n" );
           fprintf(fileLog,"% (47)Bias Gyro Z  (rad/s) \n" );
           fprintf(fileLog,"% (48)Dynamic Pressure (Pa) \n" );
           fprintf(fileLog,"% (49)Static Pressure (Pa)  \n" );
           fprintf(fileLog,"% (50)Temperature (C)  \n" );
           fprintf(fileLog,"% (51)Diagnostic Float 1  \n" );
           fprintf(fileLog,"% (52)Diagnostic Float 2  \n" );
           fprintf(fileLog,"% (53)Diagnostic Float 3  \n" );
           fprintf(fileLog,"% (54)Diagnositc Short 1   \n" );
           fprintf(fileLog,"% (55)Diagnostic Short 2   \n" );
           fprintf(fileLog,"% (56)Diagnostic Short 3 \n");
           fprintf(fileLog,"% (57)Sensor MCU Load\n" );
           fprintf(fileLog,"% (58)Control MCU Load\n" );
           fprintf(fileLog,"% (59)Voltage\n" );
           fprintf(fileLog,"% (60)Pilot Console Throttle\n" );
           fprintf(fileLog,"% (61)Pilot Console Left Aileron\n");
           fprintf(fileLog,"% (62)Pilot Console Failsafe\n" );
           fprintf(fileLog,"% (63)Pilot Console Rudder\n" );
           fprintf(fileLog,"% (64)Pilot Console Elevator\n" );
           fprintf(fileLog,"% (65)PWM Throttle\n" );
           fprintf(fileLog,"% (66)PWM Left Aileron\n");
           fprintf(fileLog,"% (67)PWM Right Aileron\n" );
           fprintf(fileLog,"% (68)PWM Rudder\n" );
           fprintf(fileLog,"% (69)PWM Left Elevator\n" );
           fprintf(fileLog,"% (70)PWM Right Elevator\n" );
           fprintf(fileLog,"% (71)PWM Left Flap\n");
           fprintf(fileLog,"% (72)PWM Right Flap\n" );
           fprintf(fileLog,"% (73)PWM Aux 1\n" );
           fprintf(fileLog,"% (74)PWM Aux 2\n" );
           fprintf(fileLog,"% (75)AP Control Type\n" );
           fprintf(fileLog,"% (76)AP Beacon Status\n");
           fprintf(fileLog,"% (77)AP HIL status\n" );
           fprintf(fileLog,"% (78)Throttle Passtrhough\n" );
           fprintf(fileLog,"% (79)Left Aileron Passtrhough\n" );
           fprintf(fileLog,"% (80)Right Aileron Passtrhough\n" );
           fprintf(fileLog,"% (81)Rudder Passtrhough\n");
           fprintf(fileLog,"% (82)Left Elevator Passtrhough\n" );
           fprintf(fileLog,"% (83)Right Elevator Passtrhough\n" );
           fprintf(fileLog,"% (84)Left Flap Passtrhough\n" );
           fprintf(fileLog,"% (85)Right Flap Passtrhough\n" );
           fprintf(fileLog,"% (86)Height Command\n");
           fprintf(fileLog,"% (87)Airspeed Command\n" );
           fprintf(fileLog,"% (88)Phi Command\n" );
           fprintf(fileLog,"% (89)Theta Command\n" );
           fprintf(fileLog,"% (90)Psi Command\n" );
           fprintf(fileLog,"% (91)P Command\n");
           fprintf(fileLog,"% (92)Q Command\n" );
           fprintf(fileLog,"% (93)R Command\n" );
           fprintf(fileLog,"% (94)Current WP\n" );
           fprintf(fileLog,"% (95)Next WP\n");
           fprintf(fileLog,"% ======================================");
           
          
}

/*
It is very usual for the C programming language beginners to compare a floating
point number using the "==" operator. Floating point numbers must not be
compared with the "==" operator.

That is mainly because when you compute a float number you will get a result
like 1.543645274878272 and if you compare 1.543645274878272 with 1.5436,
the result will always be false

http://howto.wikia.com/wiki/Howto_compare_floating_point_numbers_in_the_C_programming_language

*/

//---------------------------------------------------------------------------

 //compares if the float f1 is equal with f2 and returns 1 if true and 0 if false
char TFPpal::compare_float(float f1, float f2){
  float precision = 0.00001;

  if (((f1 - FLPRECISION) < f2) &&
      ((f1 + FLPRECISION) > f2))
   {
    return 1;
   }
  else
   {
    return 0;
   }
}

void __fastcall TFPpal::skt_rcvSessionClosed(TObject *Sender, WORD ErrCode)
{
    StartButton->Enabled        = TRUE;
    StopButton->Enabled         = FALSE;
    PortEdit->Enabled           = TRUE;
    ServerEdit->Enabled         = TRUE;
    AnyServerCheckBox->Enabled  = TRUE;
    InfoLabel->Caption          = "Disconnected";
    DataAvailableLabel->Caption = "";    
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::skt_rcvSessionConnected(TObject *Sender,
      WORD ErrCode)
{
   StartButton->Enabled = FALSE;
    StopButton->Enabled  = TRUE;
    InfoLabel->Caption   = "Connected";    
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::skt_rcvDataAvailable(TObject *Sender, WORD ErrCode)
{
    char        Buffer[113];
    int         Len;
    Winsock::TSockAddrIn Src;
    //TSockAddrIn Src;
    int         SrcLen;

    memset(&Buffer, 0, 113);

    SrcLen = sizeof(Src);
    Len    = skt_rcv->ReceiveFrom(Buffer, sizeof(Buffer), Src, SrcLen);
    if (Len >= 0) {
        if ((FServerAddr.s_addr == INADDR_ANY) ||
            (FServerAddr.s_addr == Src.sin_addr.s_addr)) {
            if (bt_filter->Tag){
               processUdpMsg(&Buffer[0]);
            }
            DataAvailableLabel->Caption =
                IntToStr(atoi(DataAvailableLabel->Caption.c_str()) + 1) +
                " Packets Received";
        }
       TxPWMMsg ();
    }
}
//---------------------------------------------------------------------------
void  TFPpal::processUdpMsg (unsigned char * buffer)
{
  unsigned char hilMsg [50];


  // GPS Sentence
  // ============

  // reset message variable
  memset(&hilMsg,0, 50);
  // Assemble the message for transmission
  assembleMsg(&buffer[HIL_GPS_START],GPSMSG_LEN,GPSMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(GPSMSG_LEN+7));


  // Air Data Sentence
  // =================

  // reset message variable
  memset(&hilMsg,0, 50);
  // Assemble the message for transmission
  assembleMsg(&buffer[HIL_DYN_START],DYNMSG_LEN,DYNMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(DYNMSG_LEN+7));


  // Raw Data Sentence
  // =================

  // reset message variable
  memset(&hilMsg,0, 50);
  // Assemble the message for transmission
  assembleMsg(&buffer[HIL_RAW_START],RAWMSG_LEN,RAWMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(RAWMSG_LEN+7));


  // Att Data Sentence
  // =================

  // reset message variable
  memset(&hilMsg,0, 50);
  // Assemble the message for transmission
  assembleMsg(&buffer[HIL_ATT_START],ATTMSG_LEN,ATTMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(ATTMSG_LEN+7));

  // XYZ Data Sentence
  // =================

  // reset message variable
  memset(&hilMsg,0, 50);
  // Assemble the message for transmission
  assembleMsg(&buffer[HIL_XYZ_START],XYZMSG_LEN,XYZMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(XYZMSG_LEN+7));

}
//---------------------------------------------------------------------------
void TFPpal::TxPWMMsg (void){
   char send_buffer[22];
   tUnsignedShortToChar sampleTime;

   // Freeze the PWM data to avoid changing data in the
   // middle of a send UDP
   tPWMData pwmSampleLocal = getPWMStruct();
   sampleTime.usData = getAttTimeStamp();

   send_buffer[0] 	= pwmSampleLocal.dt_c.chData[0];
   send_buffer[1] 	= pwmSampleLocal.dt_c.chData[1];
   send_buffer[2] 	= pwmSampleLocal.dla_c.chData[0];
   send_buffer[3] 	= pwmSampleLocal.dla_c.chData[1];
   send_buffer[4] 	= pwmSampleLocal.dra_c.chData[0];
   send_buffer[5] 	= pwmSampleLocal.dra_c.chData[1];
   send_buffer[6] 	= pwmSampleLocal.dr_c.chData[0];
   send_buffer[7] 	= pwmSampleLocal.dr_c.chData[1];
   send_buffer[8] 	= pwmSampleLocal.dle_c.chData[0];
   send_buffer[9] 	= pwmSampleLocal.dle_c.chData[1];


   send_buffer[10] 	= pwmSampleLocal.dre_c.chData[0];
   send_buffer[11] 	= pwmSampleLocal.dre_c.chData[1];
   send_buffer[12] 	= pwmSampleLocal.dlf_c.chData[0];
   send_buffer[13] 	= pwmSampleLocal.dlf_c.chData[1];
   send_buffer[14] 	= pwmSampleLocal.drf_c.chData[0];
   send_buffer[15] 	= pwmSampleLocal.drf_c.chData[1];
   send_buffer[16] 	= pwmSampleLocal.da1_c.chData[0];
   send_buffer[17] 	= pwmSampleLocal.da1_c.chData[1];
   send_buffer[18] 	= pwmSampleLocal.da2_c.chData[0];
   send_buffer[19] 	= pwmSampleLocal.da2_c.chData[1];
   send_buffer[20] 	= sampleTime.chData[0];
   send_buffer[21] 	= sampleTime.chData[1];


  skt_send->Send(&send_buffer[0],22);
  et_sent->Caption = IntToStr(atoi(et_sent->Caption.c_str()) + 1) + " Packets Sent";

}

//---------------------------------------------------------------------------

void __fastcall TFPpal::StartButtonClick(TObject *Sender)
{
    FServerAddr                = WSocketResolveHost(ServerEdit->Text);
    if (FServerAddr.s_addr == htonl(INADDR_LOOPBACK)) {
        // Replace loopback address by real localhost IP addr
        FServerAddr            = WSocketResolveHost(LocalHostName());
    }
    skt_rcv->Proto             = "udp";
    skt_rcv->Addr              = "0.0.0.0";
    skt_rcv->Port              = PortEdit->Text;
    skt_rcv->Listen();
    PortEdit->Enabled          = FALSE;
    ServerEdit->Enabled        = FALSE;
    AnyServerCheckBox->Enabled = FALSE;

    cp_hil->Open = True;

    if (!bt_filter->Tag) bt_filterClick(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::StopButtonClick(TObject *Sender)
{
    StartButton->Enabled       = TRUE;
    StopButton->Enabled        = FALSE;
    PortEdit->Enabled          = TRUE;
    ServerEdit->Enabled        = TRUE;
    AnyServerCheckBox->Enabled = TRUE;
    skt_rcv->Close();

    if (bt_filter->Tag) bt_filterClick(Sender);
    cp_hil->Open = False;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_startSendClick(TObject *Sender)
{
    skt_send->Proto = "udp";
    skt_send->Addr  = ed_hostSend->Text;
    skt_send->Port  = ed_portSend->Text;
    skt_send->Connect();
    bt_startSend->Enabled = FALSE;
    bt_stopSend->Enabled  = TRUE;
    ed_portSend->Enabled = FALSE;
    ed_hostSend->Enabled = FALSE;
    et_connSend->Caption   = "Connected";
    
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_stopSendClick(TObject *Sender)
{
    skt_send->Close();
    bt_startSend->Enabled        = TRUE;
    bt_stopSend->Enabled         = FALSE;
    ed_portSend->Enabled         = TRUE;
    ed_hostSend->Enabled         = TRUE;
    ed_portSend->Enabled         = TRUE;
    ed_hostSend->Enabled         = TRUE;
    et_connSend->Caption         = "Disconnected";
    et_sent->Caption             = "";    
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::AnyServerCheckBoxClick(TObject *Sender)
{
    if (AnyServerCheckBox->Checked)
        ServerEdit->Text = "0.0.0.0";      
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Button1Click(TObject *Sender)
{
     unsigned char hilMsg [50];
     unsigned char buffer [30];

  static unsigned char sec = 1;
  // GPS Sentence
  // ============

  // reset message variable
  memset(&hilMsg,0, 50);
  memset(&buffer,0, 30);

  buffer[0] = 8;
  buffer[1] = 11;
  buffer[2] = 24;
  buffer[4] = sec++;



  // Assemble the message for transmission
  assembleMsg(&buffer[0],GPSMSG_LEN,GPSMSG_ID,&hilMsg[0]);
  // Send the data
  cp_hil->PutBlock(&hilMsg[0],(GPSMSG_LEN+7));
  //cp_hil->PutBlock(&hilMsg[0],7);
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::et_warningDblClick(TObject *Sender)
{
  et_warning->Color = clBtnFace;
  et_warning->Caption = "No Message";
}

//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_up1Click(TObject *Sender)
{

 unsigned char filtMsg[25];
 unsigned char rawMsg[13], indx;
 tFloatToChar P, I, D;

 indx = ((TComponent*)Sender)->Tag;

 // Collect the values
 P.flData =  (float)PGains[indx]->Value;
 I.flData =  (float)IGains[indx]->Value;
 D.flData =  (float)DGains[indx]->Value;

 rawMsg[0]    =    indx;
 rawMsg[1]    =    P.chData[0];
 rawMsg[2]    =    P.chData[1];
 rawMsg[3]    =    P.chData[2];
 rawMsg[4]    =    P.chData[3];
 rawMsg[5]    =    I.chData[0];
 rawMsg[6]    =    I.chData[1];
 rawMsg[7]    =    I.chData[2];
 rawMsg[8]    =    I.chData[3];
 rawMsg[9]    =    D.chData[0];
 rawMsg[10]    =   D.chData[1];
 rawMsg[11]   =    D.chData[2];
 rawMsg[12]   =    D.chData[3];

 assembleMsg(&rawMsg[0],PIDMSG_LEN,PIDMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(PIDMSG_LEN+7));


}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_p1Change(TObject *Sender)
{
  BoxCont[((TComponent*)Sender)->Tag]->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_down1Click(TObject *Sender)
{
 unsigned char filtMsg[17];
 unsigned char rawMsg[10], indx;

 memset(&rawMsg[0],0,10);

 indx = ((TComponent*)Sender)->Tag;

 rawMsg[0]    =    PIDTYPE_ID; // Value ID (1 is PID)
 rawMsg[1]    =    indx; // Index

 assembleMsg(&rawMsg[0],QUEMSG_LEN,QUEMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(QUEMSG_LEN+7));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_allpidClick(TObject *Sender)
{
  pidRequestQueue = 0;
  Timer3->Enabled = true;
  bt_allpid->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Timer3Timer(TObject *Sender)
{
  switch (pidRequestQueue){
     // get PID gains
     case 0:
          bt_down1Click(bt_down1);
     break;
     case 1:
          bt_down1Click(bt_down2);
     break;
     case 2:
          bt_down1Click(bt_down3);
     break;
     case 3:
          bt_down1Click(bt_down4);
     break;
     case 4:
          bt_down1Click(bt_down5);
     break;
     case 5:
          bt_down1Click(bt_down6);
     break;
     case 6:
          bt_down1Click(bt_down7);
     break;
     case 7:
          bt_down1Click(bt_down8);
     break;
     case 8:
          bt_down1Click(bt_down9);
     break;
     case 9:
          bt_down1Click(bt_down10);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_allpid->Enabled = true;
     break;

     // Get WPs

     case 10:
          bt_getwp1Click(bt_getwp1);
     break;
     case 11:
          bt_getwp1Click(bt_getwp2);
     break;
     case 12:
          bt_getwp1Click(bt_getwp3);
     break;
     case 13:
          bt_getwp1Click(bt_getwp4);
     break;
     case 14:
          bt_getwp1Click(bt_getwp5);
     break;
     case 15:
          bt_getwp1Click(bt_getwp6);
     break;
     case 16:
          bt_getwp1Click(bt_getwp7);
     break;
     case 17:
          bt_getwp1Click(bt_getwp8);
     break;
     case 18:
          bt_getwp1Click(bt_getwp9);
     break;
     case 19:
          bt_getwp1Click(bt_getwp10);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_allwp->Enabled = true;
     break;

     // Set WPs

     case 20:
          bt_setwp1Click(bt_setwp1);
     break;
     case 21:
          bt_setwp1Click(bt_setwp2);
     break;
     case 22:
          bt_setwp1Click(bt_setwp3);
     break;
     case 23:
          bt_setwp1Click(bt_setwp4);
     break;
     case 24:
          bt_setwp1Click(bt_setwp5);
     break;
     case 25:
          bt_setwp1Click(bt_setwp6);
     break;
     case 26:
          bt_setwp1Click(bt_setwp7);
     break;
     case 27:
          bt_setwp1Click(bt_setwp8);
     break;
     case 28:
          bt_setwp1Click(bt_setwp9);
     break;
     case 29:
          bt_setwp1Click(bt_setwp10);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_sendwps->Enabled = true;
     break;

     // Set PID Gains
     case 30:
          bt_up1Click(bt_up1);
     break;
     case 31:
          bt_up1Click(bt_up2);
     break;
     case 32:
          bt_up1Click(bt_up3);
     break;
     case 33:
          bt_up1Click(bt_up4);
     break;
     case 34:
          bt_up1Click(bt_up5);
     break;
     case 35:
          bt_up1Click(bt_up6);
     break;
     case 36:
          bt_up1Click(bt_up7);
     break;
     case 37:
          bt_up1Click(bt_up8);
     break;
     case 38:
          bt_up1Click(bt_up9);
     break;
     case 39:
          bt_up1Click(bt_up10);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_setallpid->Enabled = true;
     break;

     // Set Commands
     case 40:
          bt_sethClick(bt_seth);
     break;
     case 41:
          bt_sethClick(bt_setu);
     break;
     case 42:
          bt_sethClick(bt_setr);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_setallcommands->Enabled = true;
     break;

      // Get Commands
    case 50:
          bt_gethClick(bt_geth);
     break;
     case 51:
          bt_gethClick(bt_getu);
     break;
     case 52:
          bt_gethClick(bt_getr);
          if (allGains != 1)
             Timer3->Enabled = false;
          bt_getallcommands->Enabled = true;
     break;


     case 53:
          // Upload the GS Positions
          bt_gsposClick(NULL);
     break;
     case 54:
          allGains = 0;
          bt_allgains->Enabled = true;
          Timer3->Enabled = false;
     break;



  }
  pidRequestQueue++;
  mm_diagnose->Lines->Add(IntToStr(pidRequestQueue));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::SpeedButton33Click(TObject *Sender)
{
TiXmlDocument doc(tb_configwaypointFile->AsString.c_str());
TiXmlHandle hDoc (&doc);
TiXmlElement* root;
TiXmlElement* pElem;
TiXmlHandle hRoot(0);
char coordVals [1000];
char* pch;
unsigned char i;



  // if loading the file succeeds
  if( doc.LoadFile()){
     // get the Root node (<kml>)
     root= hDoc.FirstChildElement().Element();
     mm_diagnose->Lines->Add(root->Value());
     hRoot = TiXmlHandle(root);

     // get the Document node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());

     // Get the children of Document
     hRoot = TiXmlHandle(pElem);
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "Placemark") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case placemark is never found
     }

     // Placemark node has been found
     hRoot = TiXmlHandle(pElem);

     // Now find the LineString node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "LineString") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case placemark is never found
     }

     // LineString node has been found
     hRoot = TiXmlHandle(pElem);

     // Now find the coordinates node
     pElem = hRoot.FirstChild().Element();
     mm_diagnose->Lines->Add(pElem->Value());


     while (strcmp(pElem->Value(), "coordinates") != 0 ){
       pElem = pElem->NextSiblingElement();
       mm_diagnose->Lines->Add(pElem->Value());
       // TODO: Add validation in case placemark is never found
     }

     // Get the actual coordinates
     mm_diagnose->Lines->Add(pElem->GetText());

     strcpy((char *)&coordVals,pElem->GetText());

     pch = strtok((char *)&coordVals, ", ");
     mm_diagnose->Lines->Add("==============");
     mm_diagnose->Lines->Add(pch);

     //memset(&coordinate, '\0', sizeof(coordinate));
     i = 0;
     
     while (pch != NULL || i > 9)
     {
       lonVals[i]->Value = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       latVals[i]->Value = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       heiVals[i]->Value = atof(pch);
       pch = strtok (NULL, ", ");
       mm_diagnose->Lines->Add(pch);

       i++;
     }

  }
  else {
    ShowMessage("WayPoint File Not Found");
  }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_allwpClick(TObject *Sender)
{
  pidRequestQueue = 10;
  Timer3->Enabled = true;
  bt_allwp->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TFPpal::bt_setwp1Click(TObject *Sender)
{


 unsigned char filtMsg[25];
 unsigned char rawMsg[16], indx;
 tFloatToChar lat, lon, hei;
 tShortToChar val;

 indx = ((TComponent*)Sender)->Tag;

 // Collect the values
 lat.flData =  (float)latVals[indx]->Value;
 lon.flData =  (float)lonVals[indx]->Value;
 hei.flData =  (float)heiVals[indx]->Value;
 val.shData =  (short)valVals[indx]->Value;

 rawMsg[0]    =    indx;
 rawMsg[1]    =    lat.chData[0];
 rawMsg[2]    =    lat.chData[1];
 rawMsg[3]    =    lat.chData[2];
 rawMsg[4]    =    lat.chData[3];
 rawMsg[5]    =    lon.chData[0];
 rawMsg[6]    =    lon.chData[1];
 rawMsg[7]    =    lon.chData[2];
 rawMsg[8]    =    lon.chData[3];
 rawMsg[9]    =    hei.chData[0];
 rawMsg[10]    =   hei.chData[1];
 rawMsg[11]   =    hei.chData[2];
 rawMsg[12]   =    hei.chData[3];
 rawMsg[13]   =    (char)cbStat[indx]->Checked;
 rawMsg[14]   =    val.chData[0];
 rawMsg[15]   =    val.chData[1];

 assembleMsg(&rawMsg[0],WPSMSG_LEN,WPSMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(WPSMSG_LEN+7));

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_getwp1Click(TObject *Sender)
{
 unsigned char filtMsg[17];
 unsigned char rawMsg[10], indx;

 memset(&rawMsg[0],0,10);

 indx = ((TComponent*)Sender)->Tag;

 rawMsg[0]    =    WPSTYPE_ID; // Value ID (2 is WP)
 rawMsg[1]    =    indx; // Index

 assembleMsg(&rawMsg[0],QUEMSG_LEN,QUEMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(QUEMSG_LEN+7));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_lat1Change(TObject *Sender)
{
  boxWP[((TComponent*)Sender)->Tag]->Color = clRed;     
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_sendwpsClick(TObject *Sender)
{
  pidRequestQueue = 20;
  Timer3->Enabled = true;
  bt_sendwps->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::cb_stat1Click(TObject *Sender)
{
  ed_lat1Change(Sender);

  if (((TCheckBox*)Sender)->Checked){
    valVals[((TComponent*)Sender)->Tag]->Enabled = true;
  } else {
    valVals[((TComponent*)Sender)->Tag]->Enabled = false;
  }
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::rb_manualClick(TObject *Sender)
{
 if (rb_manual->Checked == true){
    /*rg_modes->Caption = " Manual ";
    rg_modes->Items->Clear();
    rg_modes->Items->Add("Pilot Control");
    rg_modes->Items->Add("Passthrough");
    rg_modes->Items->Add("Selective Passthrough");     */
    rg_modes->Tag = CTRL_TYPE_MANUAL;
    rg_modes->Visible = false;
    pc_commands->ActivePage = ts_none;
 } else {
    rg_modes->Visible = true;
    /*rg_modes->Caption = " Automatic ";
    rg_modes->Items->Clear();
    rg_modes->Items->Add("Direct Commands");
    rg_modes->Items->Add("Way Point Nav");
    rg_modes->Items->Add("Selective Passthrough");*/
    //rg_modes->Tag = CTRL_TYPE_AP_COMM;
    //rg_modes->ItemIndex = 0;
    rg_modesClick(rg_modes);
 }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::rg_modesClick(TObject *Sender)
{
 switch (((TRadioGroup*)Sender)->ItemIndex){

    case 0:
          pc_commands->ActivePage = ts_direct;
          rg_modes->Tag = CTRL_TYPE_AP_COMM;
    break;

    case 1:
          pc_commands->ActivePage = ts_wp;
          rg_modes->Tag = CTRL_TYPE_AP_WP;
    break;

    case 2:
         pc_commands->ActivePage = ts_none;
         rg_modes->Tag = CTRL_TYPE_PASS;
    break;
    case 3:
       pc_commands->ActivePage = ts_ptpil;
       rg_modes->Tag = CTRL_TYPE_SEL_PIL;
    break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_modeClick(TObject *Sender)
{
 unsigned char filtMsg[18];
 unsigned char rawMsg[9];

  memset(rawMsg,0,9);

  if  (rb_manual->Checked == true) {
       rawMsg[0] = CTRL_TYPE_MANUAL;
  } else {
       switch (rg_modes->ItemIndex){

       case 0:
            rawMsg[0] = CTRL_TYPE_AP_COMM;
       break;

       case 1:
            rawMsg[0] = CTRL_TYPE_AP_WP;
       break;

       case 2:
            rawMsg[0] = CTRL_TYPE_PASS;
       break;

       case 3:
            rawMsg[0]    =     CTRL_TYPE_SEL_PIL;
            rawMsg[1]    =    (unsigned char)cb_ptpdt->Checked;
            rawMsg[2]    =    (unsigned char)cb_ptpdla->Checked;;
            rawMsg[3]    =    (unsigned char)cb_ptpdra->Checked;;
            rawMsg[4]    =    (unsigned char)cb_ptpdr->Checked;;
            rawMsg[5]    =    (unsigned char)cb_ptpdle->Checked;;
            rawMsg[6]    =    (unsigned char)cb_ptpdre->Checked;;
            rawMsg[7]    =    (unsigned char)cb_ptpdlf->Checked;;
            rawMsg[8]    =    (unsigned char)cb_ptpdrf->Checked;;
       break;

       }
  }

 assembleMsg(&rawMsg[0],CHSMSG_LEN,CHSMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(CHSMSG_LEN+7));


}
//---------------------------------------------------------------------------

void __fastcall TFPpal::SpeedButton2Click(TObject *Sender)
{
//
 unsigned char filtMsg[17];
 unsigned char rawMsg[10], indx;

 memset(&rawMsg[0],0,10);


 rawMsg[0]    =    PASTYPE_ID;

 assembleMsg(&rawMsg[0],QUEMSG_LEN,QUEMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(QUEMSG_LEN+7));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_sethClick(TObject *Sender)
{
//
 unsigned char filtMsg[17];
 unsigned char rawMsg[11], indx;
 tFloatToChar temp;

 memset(&rawMsg[0],0,10);

 // init the value
 switch (((TSpeedButton*)Sender)->Tag){
   case 0:
     temp.flData = ed_height->Value;
     rawMsg[0]   = COMM_TYPE_HEIGHT;
   break;

   case 1:
     temp.flData = ed_airspeed->Value;
     rawMsg[0]   = COMM_TYPE_AIRSPEED;
   break;

   case 2:
     temp.flData = ed_r->Value;
     rawMsg[0]   = COMM_TYPE_TURNRATE;
   break;

   case 4:
     temp.chData[0] = (unsigned char)ed_gotowp->Value;
     rawMsg[0]      = COMM_TYPE_GOTO_WP;
   break;
 }



 rawMsg[1]    =    temp.chData[0];
 rawMsg[2]    =    temp.chData[1];
 rawMsg[3]    =    temp.chData[2];
 rawMsg[4]    =    temp.chData[3];


 assembleMsg(&rawMsg[0],COMMSG_LEN,COMMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(COMMSG_LEN+7));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_heightChange(TObject *Sender)
{
  ((TCurrencyEdit*)Sender)->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_gethClick(TObject *Sender)
{
 unsigned char filtMsg[17];
 unsigned char rawMsg[10], indx;

 memset(&rawMsg[0],0,10);

 indx = ((TComponent*)Sender)->Tag;

 rawMsg[0]    =    COMTYPE_ID; // Value ID (1 is PID)
 rawMsg[1]    =    indx; // Index

 assembleMsg(&rawMsg[0],QUEMSG_LEN,QUEMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(QUEMSG_LEN+7));
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::CheckBox1Click(TObject *Sender)
{
if (((TCheckBox*)Sender)->Checked){
   Timer2->Interval = 95;
} else {
   Timer2->Interval = 200;
}
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::bt_setallpidClick(TObject *Sender)
{
 pidRequestQueue = 30;
  Timer3->Enabled = true;
  bt_setallpid->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_setallcommandsClick(TObject *Sender)
{
  pidRequestQueue = 40;
  Timer3->Enabled = true;
  bt_setallcommands->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_getallcommandsClick(TObject *Sender)
{
  pidRequestQueue = 50;
  Timer3->Enabled = true;
  bt_getallcommands->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_allgainsClick(TObject *Sender)
{
 if (0!=bt_serial->Tag){
    if (MessageDlg("Do you Want to Configure All the Gains?", mtWarning,TMsgDlgButtons() << mbYes << mbNo,0) == mrYes){

    // dummy delay
    pidRequestQueue = 1;
    allGains = 1;
    bt_allgains->Enabled = false;
    Timer3->Enabled = true;

    }
 }
}
//---------------------------------------------------------------------------





void __fastcall TFPpal::ed_minhExit(TObject *Sender)
{
mt_x->SignalSettingsCh1->DigitalFrom = ed_minh->Value;
mt_x->SignalSettingsCh1->ValueFrom = ed_minh->Value;
mt_x->SignalSettingsCh2->DigitalFrom = ed_minh->Value;
mt_x->SignalSettingsCh2->ValueFrom = ed_minh->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_maxhExit(TObject *Sender)
{
mt_x->SignalSettingsCh1->DigitalTo = ed_maxh->Value;
mt_x->SignalSettingsCh1->ValueTo = ed_maxh->Value;
mt_x->SignalSettingsCh2->DigitalTo = ed_maxh->Value;
mt_x->SignalSettingsCh2->ValueTo = ed_maxh->Value;

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_minairspeedChange(TObject *Sender)
{
mt_y->SignalSettingsCh1->DigitalFrom = ed_minairspeed->Value;
mt_y->SignalSettingsCh1->ValueFrom = ed_minairspeed->Value;
mt_y->SignalSettingsCh2->DigitalFrom = ed_minairspeed->Value;
mt_y->SignalSettingsCh2->ValueFrom = ed_minairspeed->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_maxairspeedExit(TObject *Sender)
{
mt_y->SignalSettingsCh1->DigitalTo = ed_maxairspeed->Value;
mt_y->SignalSettingsCh1->ValueTo = ed_maxairspeed->Value;
mt_y->SignalSettingsCh2->DigitalTo = ed_maxairspeed->Value;
mt_y->SignalSettingsCh2->ValueTo = ed_maxairspeed->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_minturnrateExit(TObject *Sender)
{
mt_z->SignalSettingsCh1->DigitalFrom = ed_minturnrate->Value;
mt_z->SignalSettingsCh1->ValueFrom = ed_minturnrate->Value;
mt_z->SignalSettingsCh2->DigitalFrom = ed_minturnrate->Value;
mt_z->SignalSettingsCh2->ValueFrom = ed_minturnrate->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::ed_maxturnrateExit(TObject *Sender)
{
mt_z->SignalSettingsCh1->DigitalTo = ed_maxturnrate->Value;
mt_z->SignalSettingsCh1->ValueTo = ed_maxturnrate->Value;
mt_z->SignalSettingsCh2->DigitalTo = ed_maxturnrate->Value;
mt_z->SignalSettingsCh2->ValueTo = ed_maxturnrate->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::cb_comExit(TObject *Sender)
{
mt_x->SignalColorCh2 = cb_com->ColorValue;
mt_y->SignalColorCh2 = cb_com->ColorValue;
mt_z->SignalColorCh2 = cb_com->ColorValue;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::cb_meaExit(TObject *Sender)
{
mt_x->SignalColorCh1 = cb_mea->ColorValue;
mt_y->SignalColorCh1 = cb_mea->ColorValue;
mt_z->SignalColorCh1 = cb_mea->ColorValue;
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::RxSlider1Changed(TObject *Sender)
{
mt_x->TimeScale = RxSlider1->Value;
mt_y->TimeScale = RxSlider1->Value;
mt_z->TimeScale = RxSlider1->Value;
}
//---------------------------------------------------------------------------

