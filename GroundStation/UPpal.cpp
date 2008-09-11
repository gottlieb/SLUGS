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

// telemPort = (struct CircBuffer*)&mainSerial;
// newCircBuffer(telemPort);
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


void __fastcall TFPpal::BitBtn1Click(TObject *Sender)
{
  createBlankKML(1);
  BYTE tmp = GetRValue(cb_color1->Selected);
  tmp = GetGValue(cb_color1->Selected);
  tmp = GetBValue(cb_color1->Selected);
  ShowMessage(IntToHex(tmp,4));
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::BitBtn2Click(TObject *Sender)
{
   cb_color1->Selected = RGB(255,0,0);
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
 } else {
   cp_serial->Open = False;
   bt_serial->Tag = 0;
   bt_serial->Caption = "Open Serial Port";
   ld_serial->StatusInt = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Timer2Timer(TObject *Sender)
{
   //replace the history
   for (int i = 13; i>=0; i--){
     gpsSamples[i+1] = gpsSamples[i];
   }
   gpsSamples[0] = getGpsStruct();

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
//---------------------------------------------------------------------------

void __fastcall TFPpal::cp_serialTriggerAvail(TObject *CP, WORD Count)
{
  unsigned char fromSerial[128];

  for (int i=1;i<=Count;i++) {
    fromSerial[i] = cp_serial->GetChar();
  }

  fromSerial[0] = Count;
  protParseDecode (&fromSerial[0]);
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::Timer1Timer(TObject *Sender)
{
// Timer 1 Updates Google Earth Data;
    
}
//---------------------------------------------------------------------------

void TFPpal::updateKML(void){
  // freeze the data in case the interrup changes at mid update
  tGpsData tmpPos[15];
  for (int i = 0; i< tb_configtailLength->AsInteger; i++){
     tmpPos[i] = gpsSamples[i];
  }

  TiXmlDocument doc;

   // Create the document header
   TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );


   // Create the document root
   TiXmlElement * kmlRoot = new TiXmlElement( "kml" );
   // Set the the attribute for the tag
   kmlRoot->SetAttribute("xmlns","http://earth.google.com/kml/2.2");

   // create the Document tag
   TiXmlElement * docTag = new TiXmlElement("Document");

   // create the Plane Trajectory Style
   TiXmlElement * styleTag = new TiXmlElement("Style");
   styleTag->SetAttribute("id", "planeTrajectory");

   // create the Line Style
   TiXmlElement * lineStyleTag = new TiXmlElement("LineStyle");

   // Add the sytles
   addAndAppendNode("color",getHexColor(1), lineStyleTag);


   /*
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
    */

}
//---------------------------------------------------------------------------

unsigned char * TFPpal::getHexColor(unsigned char whichColor){
   String retVal = "";
   switch (whichColor){
       case 1: // AC Trajectory
            retVal = IntToHex(255,2) +
                     IntToHex(tb_configtrajectoryColorB->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorG->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorR->AsInteger,2);
       break;
       case 2:
            retVal = IntToHex(tb_configTransparency->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorB->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorG->AsInteger,2) +
                     IntToHex(tb_configtrajectoryColorR->AsInteger,2);

       break;
   }

   return retVal.c_str();

}
//---------------------------------------------------------------------------

