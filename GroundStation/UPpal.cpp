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
#pragma resource "*.dfm"

#define  _IN_PC_       1

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

 if (cp_serial->Open == true){
    cp_serial->Open = false;
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

   if (computeDistance(temp.lat.flData, temp.lon.flData) < DISLIMIT ){
      //replace the history
      for (int i = 13; i>=0; i--){
          gpsSamples[i+1] = gpsSamples[i];
      }
   }
   gpsSamples[0] = temp;
   rawSample = getRawStruct();
   attitudeSample = getAttStruct();
   xyzSample  = getXYZStruct();
   dynSample  = getDynStruct();
   biasSample = getBiasStruct();
   diagSample = getDiagStruct();

   updateGPSLabels();                 
   updateRawLabels();
   updateAttitudeLabels();

   updateBiasLabels();
   updateDynLabels();
   updateDiagLabels();

   updatePlots();
   updateAttitude();

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

   et_vx->Caption = FloatToStr(xyzSample.VX.flData);
   et_vy->Caption = FloatToStr(xyzSample.VY.flData);
   et_vz->Caption = FloatToStr(xyzSample.VZ.flData);

   et_p->Caption = FloatToStr(RAD2DEG*attitudeSample.p.flData);
   et_q->Caption = FloatToStr(RAD2DEG*attitudeSample.q.flData);
   et_r->Caption = FloatToStr(RAD2DEG*attitudeSample.r.flData);

   et_phi->Caption = FloatToStr(RAD2DEG*attitudeSample.roll.flData);
   et_theta->Caption = FloatToStr(RAD2DEG*attitudeSample.pitch.flData);
   et_psi->Caption = FloatToStr(RAD2DEG*attitudeSample.yaw.flData);
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
}
void TFPpal::updateDiagLabels(void){
  et_fl1->Caption = FloatToStr(diagSample.fl1.flData);
  et_fl2->Caption = FloatToStr(diagSample.fl2.flData);
  et_fl3->Caption = FloatToStr(diagSample.fl3.flData);
  et_sh1->Caption = IntToStr( diagSample.sh1.shData);
  et_sh2->Caption = IntToStr( diagSample.sh2.shData);
  et_sh3->Caption = IntToStr( diagSample.sh3.shData);
}


void __fastcall TFPpal::cp_serialTriggerAvail(TObject *CP, WORD Count)
{
  unsigned char fromSerial[4096];
  unsigned char tmp[2*MAXSEND];
  int bytesRemain = Count;

  try {
    while (bytesRemain > 0) {
       if (bytesRemain <= 4095) {
         cp_serial->GetBlock(&fromSerial[1], Count);
         fromSerial[0] = Count;
         bytesRemain = 0;
       } else{
         cp_serial->GetBlock(&fromSerial[1], 4095);
         fromSerial[0] = 4095;
         bytesRemain -= 4095;
       }
       if (logIsOpen==true)
         protParseDecode (&fromSerial[0], &tmp[0], liveLog);
       else
         protParseDecode (&fromSerial[0], &tmp[0], NULL);
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
   addAndAppendNode("altitudeMode","absolute", lineStringTag);
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
  // freeze the data in case the interrup changes at mid update
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
  ai_att->Roll = RAD2DEG*attitudeSample.roll.flData;
  ai_att->Pitch = RAD2DEG*attitudeSample.pitch.flData;
  ai_att->Course = RAD2DEG*attitudeSample.yaw.flData;
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

 bt_filter->Caption = bt_filter->Tag? "Filter Off":"Filter On";

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
    unsigned char myToLog[97];
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
             protParseDecode(buffer, myToLog, matFile);
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

