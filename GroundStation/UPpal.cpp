//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UPpal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Placemnt"
#pragma link "ABSMain"
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

}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_clearClick(TObject *Sender)
{
 mm_diagnose->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::FormCreate(TObject *Sender)
{
 tb_config->Open();    
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

  // commit changes
  tb_config->Post();

 tb_config->Close();
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::bt_mainKmlClick(TObject *Sender)
{
 if (od_mainKml->Execute()){
    tb_config->Edit();
    tb_configkmlFile->AsString = od_mainKml->FileName;
    tb_config->Post();
 }
}
//---------------------------------------------------------------------------

void __fastcall TFPpal::bt_ppKmlClick(TObject *Sender)
{
  if (od_mainKml->Execute()){
    tb_config->Edit();
    tb_configplanePathFile->AsString = od_mainKml->FileName;
    tb_config->Post();
 }
}
//---------------------------------------------------------------------------



void __fastcall TFPpal::SpeedButton1Click(TObject *Sender)
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

