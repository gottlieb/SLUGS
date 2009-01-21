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

   // if the lat and lon are withing the distance limit
   if (computeDistance(temp.lat.flData, temp.lon.flData) < DISLIMIT ){
      // if there was a change in lat or lon
      if (!compare_float(temp.lat.flData, gpsSamples[0].lat.flData) ||
          !compare_float(temp.lon.flData, gpsSamples[0].lon.flData)){
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

   if (aknSample.reboot == 1){
      //ShowMessage("WARNING: Slugs Reboot");
      et_warning->Color = clRed;
      et_warning->Caption = "SLUGS Reset Detected";
      setAknReboot (0);
   }

   if (aknSample.pidCal > 1 ){
      if (aknSample.pidCal <=10){
         BoxCont[aknSample.pidCal-1]->Color = clGreen;
      } else {
         switch (aknSample.pidCal){
             case 11: // WRITE FAILED
                et_warning->Color = clYellow;
                et_warning->Caption = "EEPROM Write Failed. Value Changed Only in Structs";
             break;
             case 12: // INIT FAILED. ALL PAGES EXPIRED
                et_warning->Color = clYellow;
                et_warning->Caption = "All EEPROM Pages Have expired";
             break;
             case 13: // INIT FAILED. EEPROM CORRUPTED
                et_warning->Color = clRed;
                et_warning->Caption = "EEPROM Corrupted. Need to Reinitialize";
             break;
         }
      }

      setAknPidCal(0);

   }

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

   et_fail ->Caption = FormatFloat("0.0000E+00",csFail);
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

   et_lat->Caption = FloatToStr(gpsSamples[0].lat.flData);
   et_lon->Caption = FloatToStr(gpsSamples[0].lon.flData);
   et_height->Caption = FloatToStr(gpsSamples[0].height.flData);

   et_cog->Caption = IntToStr(gpsSamples[0].cog.usData);
   et_sog->Caption = IntToStr(gpsSamples[0].sog.usData);

   et_hdop->Caption = IntToStr(gpsSamples[0].hdop.usData);
   et_fix->Caption = (gpsSamples[0].fix == 1)? "Yes": "No";

   et_sats->Caption = IntToStr(gpsSamples[0].sats);

}

void TFPpal::updateRawLabels(void){
   // update the display
   // ========= Raw =============
   et_accelx->Caption = IntToStr(rawSample.accelX.usData);
   et_accely->Caption = IntToStr(rawSample.accelY.usData);
   et_accelz->Caption = IntToStr(rawSample.accelZ.usData);

   et_gyrox->Caption = IntToStr(rawSample.gyroX.usData);
   et_gyroy->Caption = IntToStr(rawSample.gyroY.usData);
   et_gyroz->Caption = IntToStr(rawSample.gyroZ.usData);

   et_magx->Caption = IntToStr(rawSample.magX.usData);
   et_magy->Caption = IntToStr(rawSample.magY.usData);
   et_magz->Caption = IntToStr(rawSample.magZ.usData);
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


   et_x->Caption = FloatToStr(xyzSample.Xcoord.flData);
   et_y->Caption = FloatToStr(xyzSample.Ycoord.flData);
   et_z->Caption = FloatToStr(xyzSample.Zcoord.flData);

   gr_height->Value = xyzSample.Zcoord.flData;

   et_vx->Caption = FloatToStr(xyzSample.VX.flData);
   et_vy->Caption = FloatToStr(xyzSample.VY.flData);
   et_vz->Caption = FloatToStr(xyzSample.VZ.flData);

   et_p->Caption = FloatToStr(RAD2DEG*attitudeSample.p.flData);
   et_q->Caption = FloatToStr(RAD2DEG*attitudeSample.q.flData);
   et_r->Caption = FloatToStr(RAD2DEG*attitudeSample.r.flData);

   et_phi->Caption = FloatToStr(RAD2DEG*attitudeSample.roll.flData);
   et_theta->Caption = FloatToStr(RAD2DEG*attitudeSample.pitch.flData);
   et_psi->Caption = FloatToStr(RAD2DEG*attitudeSample.yaw.flData);

   et_timeStamp->Caption =  IntToStr(attitudeSample.timeStamp.usData);
}

void TFPpal::updatePlots(void){
  switch (rg_plot->ItemIndex){
     case 0:
       mt_x->DigitCh1 = rawSample.accelX.usData;
       mt_y->DigitCh1 = rawSample.accelY.usData;
       mt_z->DigitCh1 = rawSample.accelZ.usData;
    break;
    case 1:
       mt_x->DigitCh1 = rawSample.gyroX.usData;
       mt_y->DigitCh1 = rawSample.gyroY.usData;
       mt_z->DigitCh1 = rawSample.gyroZ.usData;
    break;
    case 2:
       mt_x->DigitCh1 = rawSample.magX.usData;
       mt_y->DigitCh1 = rawSample.magY.usData;
       mt_z->DigitCh1 = rawSample.magZ.usData;
     break;
  } 

}

void TFPpal::updateBiasLabels(void){
  et_axb->Caption = FloatToStr(biasSample.axb.flData);
  et_ayb->Caption = FloatToStr(biasSample.ayb.flData);
  et_azb->Caption = FloatToStr(biasSample.azb.flData);
  et_gxb->Caption = FloatToStr(biasSample.gxb.flData);
  et_gyb->Caption = FloatToStr(biasSample.gyb.flData);
  et_gzb->Caption = FloatToStr(biasSample.gzb.flData);

}
void TFPpal::updateDynLabels(void){
  et_dyn->Caption = FloatToStr( dynSample.dynamic.flData);
  et_sta->Caption = FloatToStr( dynSample.stat.flData);
  et_temp->Caption = IntToStr( dynSample.temp.shData);

  // sensor mcu status
  et_load->Caption = IntToStr(statusSample.load);
  et_vdetect->Caption = IntToStr(statusSample.vdetect);
  et_volt->Caption = IntToStr(statusSample.bVolt.usData);

  gr_batt->Value = statusSample.bVolt.usData;
}
void TFPpal::updateDiagLabels(void){
  et_fl1->Caption = FloatToStr(diagSample.fl1.flData);
  et_fl2->Caption = FloatToStr(diagSample.fl2.flData);
  et_fl3->Caption = FloatToStr(diagSample.fl3.flData);
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
  gr_de->Value = StrToInt(et_de->Caption);
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
  et_a2c->Caption  =  IntToStr(pwmSample.da2_c.usData);
}


void TFPpal::updatePID(void){
  et_p1->Caption  =  FloatToStr(pidSample.P[0].flData);
  et_i1->Caption  =  FloatToStr(pidSample.I[0].flData);
  et_d1->Caption  =  FloatToStr(pidSample.D[0].flData);
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
   addAndAppendNode("altitudeMode","absolute", pointTag);
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
 tb_config->Edit();
 tb_configlatGS->AsFloat = gpsSamples[0].lat.flData;
 tb_configlonGS->AsFloat = gpsSamples[0].lon.flData;
 tb_configheightGS->AsFloat = gpsSamples[0].height.flData;
 tb_config->Post();
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

  ai_att->Roll = RAD2DEG*attitudeSample.roll.flData;
  ai_att->Pitch = RAD2DEG*attitudeSample.pitch.flData;
  ai_att->Course = RAD2DEG*attitudeSample.yaw.flData;
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
    String logFileName = ed_liveLog->FileName +
                           FormatDateTime("_dd_mm_yy_hh_nn_ss", Now());
    ed_liveLog->Enabled = True;
    liveLog = fopen(logFileName.c_str(), "wt");

	if (!liveLog)
	{
		ShowMessage("Unable to create Live Log file, continuing without logging");
        cb_inflight->Checked = False;
        cb_inflightClick(NULL);
	} else{
        logIsOpen = true;
        printFileHeader();
    }
} else {
    ed_liveLog->Enabled = False;
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

	if (!logFile)
	{
		ShowMessage("Unable to open Log file");
	}else {

        if (!matFile)
	    {
		   ShowMessage("Unable to create CSV file");
	    } else {
	       //Get file length
	       fseek(logFile, 0, SEEK_END);
	       fileLen=ftell(logFile);
	       fseek(logFile, 0, SEEK_SET);

	       //Read file contents into buffer
           i = 0;

           while (i<fileLen-96){
	         fread(&(buffer[0]) + 1, sizeof(unsigned char), 96, logFile);
             i+=96;
             buffer[0] = 96;
             protParseDecode(buffer, matFile);
           }
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

void TFPpal::printFileHeader(void){
		   fprintf(liveLog,"% This is a log File for the UCSC AP data is organized as follows:\n" );
           fprintf(liveLog,"%\n" );
           fprintf(liveLog,"% (1)Time Stamp in Ticks (multiply by AP Sampling time to get Seconds) \n" );
           fprintf(liveLog,"% (2)Roll (rad)  \n" );
           fprintf(liveLog,"% (3)Pitch (rad)  \n" );
           fprintf(liveLog,"% (4)Yaw (rad)   \n" );
           fprintf(liveLog,"% (5)P (rad)   \n" );
           fprintf(liveLog,"% (6)Q (rad)   \n" );
           fprintf(liveLog,"% (7)R (rad)   \n" );
           fprintf(liveLog,"% (8)X (m)   \n" );
           fprintf(liveLog,"% (9)Y (m)  \n" );
           fprintf(liveLog,"% (10)Z (m)   \n" );
           fprintf(liveLog,"% (11)Vx (m/s)  \n" );
           fprintf(liveLog,"% (12)Vy (m/s)  \n" );
           fprintf(liveLog,"% (13)Vz (m/s)  \n" );
           fprintf(liveLog,"% (14)GPS Year   \n" );
           fprintf(liveLog,"% (15)GPS Month  \n" );
           fprintf(liveLog,"% (16)GPS Day  \n" );
           fprintf(liveLog,"% (17)GPS Hour   \n" );
           fprintf(liveLog,"% (18)GPS min  \n" );
           fprintf(liveLog,"% (19)GPS sec  \n" );
           fprintf(liveLog,"% (20)GPS Lat (deg)  \n" );
           fprintf(liveLog,"% (21)GPS Lon (deg) \n" );
           fprintf(liveLog,"% (22)GPS Height (m)  \n" );
           fprintf(liveLog,"% (23)GPS COG (deg)  \n" );
           fprintf(liveLog,"% (24)GPS SOG (m/s)  \n" );
           fprintf(liveLog,"% (25)GPS Hdop (in hundreths of unit)  \n" );
           fprintf(liveLog,"% (26)GPS fix? (yes or no) \n" );
           fprintf(liveLog,"% (27)GPS Number of Sats Used  \n" );
           fprintf(liveLog,"% (28)GPS New Val? \n" );
           fprintf(liveLog,"% (29)Raw Gyro X  \n" );
           fprintf(liveLog,"% (30)Raw Gyro Y \n" );
           fprintf(liveLog,"% (31)Raw Gyro Z  \n" );
           fprintf(liveLog,"% (32)Raw Accel X  \n" );
           fprintf(liveLog,"% (33)Raw Accel Y  \n" );
           fprintf(liveLog,"% (34)Raw Accel Z  \n" );
           fprintf(liveLog,"% (35)Raw Mag X  \n" );
           fprintf(liveLog,"% (36)Raw Mag Y \n" );
           fprintf(liveLog,"% (37)Raw Mag Z \n" );
           fprintf(liveLog,"% (38)Bias Accel X (m/s) \n" );
           fprintf(liveLog,"% (39)Bias Accel Y (m/s) \n" );
           fprintf(liveLog,"% (40)Bias Accel Z (m/s) \n" );
           fprintf(liveLog,"% (41)Bias Gyro X  (rad/s) \n" );
           fprintf(liveLog,"% (42)Bias Gyro Y  (rad/s) \n" );
           fprintf(liveLog,"% (43)Bias Gyro Z  (rad/s) \n" );
           fprintf(liveLog,"% (44)Dynamic Pressure (Pa) \n" );
           fprintf(liveLog,"% (45)Static Pressure (Pa)  \n" );
           fprintf(liveLog,"% (46)Temperature (C)  \n" );
           fprintf(liveLog,"% (47)Diagnostic Float 1  \n" );
           fprintf(liveLog,"% (48)Diagnostic Float 2  \n" );
           fprintf(liveLog,"% (49)Diagnostic Float 3  \n" );
           fprintf(liveLog,"% (50)Diagnositc Short 1   \n" );
           fprintf(liveLog,"% (51)Diagnostic Short 2   \n" );
           fprintf(liveLog,"% (52)Diagnostic Short 3 \n%\n%\n%\n");
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
    char        Buffer[70];
    int         Len;
    Winsock::TSockAddrIn Src;
    int         SrcLen;

    memset(&Buffer, 0, 70);

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
        //TxCanMsg ();
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
 // 32 64 205 1 1 42 64 141

 unsigned char filtMsg[25];
 unsigned char rawMsg[13];
 tFloatToChar P, I, D;

 // Collect the values
 P.flData =  (float)PGains[((TComponent*)Sender)->Tag]->Value;
 I.flData =  (float)IGains[((TComponent*)Sender)->Tag]->Value;
 D.flData =  (float)DGains[((TComponent*)Sender)->Tag]->Value;

 rawMsg[0]    =    0; // Loop 0
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
 unsigned char rawMsg[10];

 rawMsg[0]    =    1; // Value ID (1 is PID)
 rawMsg[1]    =    ((TComponent*)Sender)->Tag; // Index

 assembleMsg(&rawMsg[0],QUEMSG_LEN,QUEMSG_ID,&filtMsg[0]);

 cp_serial->PutBlock(&filtMsg[0],(QUEMSG_LEN+7));
}
//---------------------------------------------------------------------------

