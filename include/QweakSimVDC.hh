//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC.hh
   $Revision: 1.5 $	
   $Date: 2006/05/05 21:41:14 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimVDC
    
   \brief Region 3 Vertical Drift Chamber

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:41:14 $
//  CVS/RCS Revision: $Revision: 1.5 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimVDC_h
#define QweakSimVDC_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimVDCMessenger.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimVDC_WirePlaneSD.hh"
#include "QweakSimVDC_DriftCellFrontSD.hh"
#include "QweakSimVDC_DriftCellBackSD.hh"
#include "QweakSimVDC_DriftCellParameterisation.hh"

// user classes
class QweakSimVDCMessenger;
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//class QweakSimVDC: public QweakSimVGeometryComponent
//class QweakSimVDC: public G4VUserDetectorConstruction
class QweakSimVDC
{
public:
  QweakSimVDC();
  ~QweakSimVDC();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();

  //=============
  // Set function
  //=============

  void SetVDC_MasterContainerMaterial(G4String);
  void SetVDC_SubContainerMaterial(G4String);
  void SetVDC_FoilMaterial(G4String);
  void SetVDC_WirePlaneMaterial(G4String);
  void SetVDC_G10FrameMaterial(G4String);
  void SetVDC_AluFrameMaterial(G4String);


  void SetVDC_DriftCellMaterial(G4String);
  void SetVDC_DriftCellFrontWireAngle(G4double frontWireAngle);
  void SetVDC_DriftCellBackWireAngle(G4double backWireAngle);
  void SetVDC_DriftCellFullHeight(G4double fullHeight);
  void SetVDC_DriftCellFullWidthOnFrame(G4double fullWidthOnFrame);
  void SetVDC_DriftCellFullThickness(G4double fullThickness);
  void SetVDC_DriftCellNumberPerPlane(G4int numberPerPlane);
  void SetVDC_DriftCellGeometryUpdate();

  void SetFrontVDC_CenterPositionInX(G4double xPos);
  void SetFrontVDC_CenterPositionInY(G4double yPos);
  void SetFrontVDC_CenterPositionInZ(G4double zPos);

  void SetVDC_RotationAngleInPhi(G4double vdc_phiangle);
  void SetVDC_MeanTrackAngleInTheta(G4double angle) {  MeanTrackAngle = angle; }


  //=============
  // Get function
  //=============
  
  G4LogicalVolume*   getVDC_LogicalVolume()    {return VDC_MasterContainer_Logical;} 

  G4VPhysicalVolume* getVDCFront_PhysicalVolume()   {return VDC_MasterContainerFront_Physical;} 
  G4VPhysicalVolume* getVDCBack_PhysicalVolume()   {return VDC_MasterContainerBack_Physical;} 

  G4LogicalVolume*   getVDC_WirePlane_LogicalVolume()    {return VDC_WirePlane_Logical;} 
  G4VPhysicalVolume* getVDC_UWirePlane_PhysicalVolume()   {return VDC_UPlane_Physical;} 
  G4VPhysicalVolume* getVDC_VWirePlane_PhysicalVolume()   {return VDC_VPlane_Physical;} 

  G4LogicalVolume*   getVDC_DriftCellMasterContainer_LogicalVolume()    {return VDC_DriftCellMasterContainer_Logical;} 
  G4VPhysicalVolume* getVDC_DriftCellMasterContainer_PhysicalVolume()   {return VDC_DriftCellMasterContainer_Physical;} 

  G4LogicalVolume*   getVDC_DriftCellFrontContainer_LogicalVolume()    {return VDC_DriftCellFrontContainer_Logical;} 
  G4VPhysicalVolume* getVDC_DriftCellFrontContainer_PhysicalVolume()   {return VDC_DriftCellFrontContainer_Physical;} 

  G4LogicalVolume*   getVDC_DriftCellBackContainer_LogicalVolume()    {return VDC_DriftCellBackContainer_Logical;} 
  G4VPhysicalVolume* getVDC_DriftCellBackContainer_PhysicalVolume()   {return VDC_DriftCellBackContainer_Physical;} 

  G4LogicalVolume*   getVDC_DriftCellFront_LogicalVolume()    {return VDC_DriftCellFront_Logical;} 
  G4VPhysicalVolume* getVDC_DriftCellFront_PhysicalVolume()   {return VDC_DriftCellFront_Physical;} 

  G4LogicalVolume*   getVDC_DriftCellBack_LogicalVolume()    {return VDC_DriftCellBack_Logical;} 
  G4VPhysicalVolume* getVDC_DriftCellBack_PhysicalVolume()   {return VDC_DriftCellBack_Physical;} 

  G4double GetDCWidthOnFrame()    {return DriftCell_FullWidthOnFrame;} 
  G4double GetDCFullThickness()   {return DriftCell_FullThickness;}
  G4double GetDCUPlaneWireAngle() {return DriftCell_WireAngleFront;} 
  G4double GetDCVPlaneWireAngle() {return DriftCell_WireAngleBack;} 

  G4double GetVDC_RotationAngleInPhi() {return VDC_RotationAngleInPhi;} 

private:

    void SetVDC_BackVDC_CenterPosition();
    void SetVDC_DriftCell_MasterContainer_CenterPosition();

    G4RotationMatrix*     Rotation_VDC_MasterContainer; // for Phi angle orientation
 
   // mean bending angle after MainMagnet
    G4double MeanTrackAngle;  // ~ 20.8*degree
    G4double VDC_RotationAngleInPhi;


    QweakSimVDCMessenger* VDC_Messenger;  // pointer to the Messenger

    QweakSimMaterial*  pMaterial;

  
  G4LogicalVolume*   VDC_DriftCellMasterContainer_Logical; 
  G4VPhysicalVolume* VDC_DriftCellMasterContainer_Physical; 

  G4LogicalVolume*   VDC_DriftCellFrontContainer_Logical; 
  G4VPhysicalVolume* VDC_DriftCellFrontContainer_Physical; 

  G4LogicalVolume*   VDC_DriftCellBackContainer_Logical; 
  G4VPhysicalVolume* VDC_DriftCellBackContainer_Physical; 

  G4Para*            VDC_DriftCellFront_Solid; 
  G4LogicalVolume*   VDC_DriftCellFront_Logical; 
  G4VPhysicalVolume* VDC_DriftCellFront_Physical; 

  G4Para*            VDC_DriftCellBack_Solid; 
  G4LogicalVolume*   VDC_DriftCellBack_Logical; 
  G4VPhysicalVolume* VDC_DriftCellBack_Physical; 

 

  G4double G10Frame_Thickness; 
  G4double G10Frame_OuterLength;
  G4double G10Frame_OuterWidth; 
  G4double G10Frame_InnerLength;
  G4double G10Frame_InnerWidth; 
  G4double G10Frame_BorderWidthInX; 
  G4double G10Frame_BorderWidthInY; 

  G4double AluFrame_Thickness; 
  G4double AluFrame_OuterLength;
  G4double AluFrame_OuterWidth; 
  G4double AluFrame_InnerLength;
  G4double AluFrame_InnerWidth; 

  G4double VDC_CenterFront_XPos;
  G4double VDC_CenterFront_YPos;
  G4double VDC_CenterFront_ZPos;

  G4double VDC_CenterBack_XPos;
  G4double VDC_CenterBack_YPos;
  G4double VDC_CenterBack_ZPos;

  G4double VDC_FrontBackDistance;

  G4double VDC_DriftCell_MasterContainer_XPos;
  G4double VDC_DriftCell_MasterContainer_YPos;
  G4double VDC_DriftCell_MasterContainer_ZPos;


  G4int    DriftCell_NumberPerPlane;
  G4double DriftCell_FullWidthOnFrame; // distance between wires projected on frame
  G4double DriftCell_FullHeight;
  G4double DriftCell_FullThickness;
  G4double DriftCell_WireAngleFront;
  G4double DriftCell_WireAngleBack;

  G4double  DriftCell_MasterContainer_FullLength;
  G4double  DriftCell_MasterContainer_FullHeight;
  G4double  DriftCell_MasterContainer_FullThickness;
  
  G4VisAttributes* VDC_DriftCellMasterContainer_VisAtt;
  G4VisAttributes* VDC_DriftCellFrontContainer_VisAtt;
  G4VisAttributes* VDC_DriftCellBackContainer_VisAtt;
  G4VisAttributes* VDC_DriftCellFront_VisAtt;
  G4VisAttributes* VDC_DriftCellBack_VisAtt;


  //  QweakSimVDCSD*  driftChamberSD; // pointer to the sensitive DC
  G4VSensitiveDetector* driftChamberSD;
  G4VSensitiveDetector* driftCellFrontSD;
  G4VSensitiveDetector* driftCellBackSD;


  // new VDC setup

  G4double              VDC_AluLayer_Thickness;
  G4double              VDC_MylarFoil_Thickness;

  

  G4LogicalVolume*      VDC_MasterContainer_Logical; 
  G4VPhysicalVolume*    VDC_MasterContainerFront_Physical;
  G4VPhysicalVolume*    VDC_MasterContainerBack_Physical;

  G4LogicalVolume*      VDC_SubContainer_Logical; 
  G4VPhysicalVolume*    VDC_SubContainer_Physical;

  G4SubtractionSolid*   VDC_G10Frame_Solid;
  G4LogicalVolume*      VDC_G10Frame_Logical;
  G4VPhysicalVolume*    VDC_G10Frame_Physical;

  G4SubtractionSolid*   VDC_AluFrame_Solid;
  G4LogicalVolume*      VDC_AluFrame_Logical;
  G4VPhysicalVolume*    VDC_AluTopFrame_Physical;
  G4VPhysicalVolume*    VDC_AluBottomFrame_Physical;


  G4LogicalVolume*      VDC_MylarFoil_Logical;
  G4LogicalVolume*      VDC_AluLayer_Logical;
  
  G4LogicalVolume*      VDC_WirePlane_Logical;
  G4VPhysicalVolume*    VDC_UPlane_Physical;
  G4VPhysicalVolume*    VDC_VPlane_Physical;


  G4LogicalVolume*      VDC_AMA_FoilContainer_Logical;
  G4LogicalVolume*      VDC_AM_FoilContainer_Logical;
  G4LogicalVolume*      VDC_MA_FoilContainer_Logical;

  G4VPhysicalVolume*    VDC_TopGasFoilContainer_Physical;
  G4VPhysicalVolume*    VDC_TopHVFoilContainer_Physical;
  G4VPhysicalVolume*    VDC_CenterHVFoilContainer_Physical;
  G4VPhysicalVolume*    VDC_BottomHVFoilContainer_Physical;
  G4VPhysicalVolume*    VDC_BottomGasFoilContainer_Physical;

  G4VisAttributes*      VDC_MasterContainer_VisAtt;
  G4VisAttributes*      VDC_SubContainer_VisAtt;
  G4VisAttributes*      VDC_G10Frame_VisAtt;
  G4VisAttributes*      VDC_AluFrame_VisAtt;

  G4VisAttributes*      VDC_AMA_FoilContainer_VisAtt;
  G4VisAttributes*      VDC_AM_FoilContainer_VisAtt;
  G4VisAttributes*      VDC_MA_FoilContainer_VisAtt;
  G4VisAttributes*      VDC_AluLayer_VisAtt;
  G4VisAttributes*      VDC_MylarFoil_VisAtt;
  G4VisAttributes*      VDC_WirePlane_VisAtt;


  // cuts for G4Region and PAIModel
  G4double    fGammaCut; 
  G4double    fElectronCut; 
  G4double    fPositronCut; 
  G4Region*   fRegGasDet;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC.hh,v $
//      Revision 1.5  2006/05/05 21:41:14  grimm
//      cosmetic changes
//
//      Revision 1.4  2006/04/26 20:04:59  grimm
//      Added some variables for an upcoming implementation of the PAI model
//
//      Revision 1.3  2006/01/06 21:36:15  grimm
//      Major changes: rewrote and updated the VDC geometry code
//      Added gas and HV foils with aluminum coatings (single or double sided).
//      Added alu top+bottom support frames.
//
//      Revision 1.2  2005/12/27 19:31:51  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//


