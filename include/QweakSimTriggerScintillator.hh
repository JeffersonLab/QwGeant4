//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTriggerScintillator.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:27:45 $
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
   \class QweakSimTriggerScintillator
    
   \brief Definition of the Trigger Scintillator detector

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
//  Update Date:      $Date: 2005/12/27 19:27:45 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

#ifndef QweakSimTriggerScintillator_h
#define QweakSimTriggerScintillator_h 

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh"

// user includes
#include "QweakSimTriggerScintillatorMessenger.hh"
#include "QweakSimTriggerScintillator_DetectorSD.hh"
#include "QweakSimTriggerScintillator_PMTSD.hh"
// #include "QweakSimPMTEntranceWindowSD.hh"
#include "QweakSimMaterial.hh"

// user classes
class QweakSimTriggerScintillatorMessenger;
//class QweakSimMaterial;

class QweakSimTriggerScintillator 
{
public:
  QweakSimTriggerScintillator();
  ~QweakSimTriggerScintillator();

  void ConstructComponent(G4VPhysicalVolume* MotherVolume);
  void DefineTriggerScintillatorGeometry();
  void DestroyComponent();
  void SetTriggerScintillatorMaterial(G4String materialName);

  void SetTriggerScintillatorCenterPositionInX(G4double xPos);
  void SetTriggerScintillatorCenterPositionInY(G4double yPos);
  void SetTriggerScintillatorCenterPositionInZ(G4double zPos) ;
  void SetTriggerScintillatorTiltAngle(G4double tiltangle);
  void SetTriggerScintillatorThickness(G4double thickness);

  void TriggerScintillatorGeometryUpdate();

  G4LogicalVolume*   GetTriggerScintillator_LogicalVolume()    {return TriggerScintillator_Logical;} 
  G4VPhysicalVolume* GetTriggerScintillator_PhysicalVolume()   {return TriggerScintillator_Physical;} 

private:

  QweakSimTriggerScintillatorMessenger* TriggerScintillatorMessenger;  // pointer to the Messenger

  QweakSimMaterial*  pMaterial;

  G4LogicalVolume*   TriggerScintillatorContainer_Logical; 
  G4VPhysicalVolume* TriggerScintillatorContainer_Physical; 
  G4Material*        TriggerScintillatorContainer_Material;

  G4LogicalVolume*   TriggerScintillator_Logical; 
  G4VPhysicalVolume* TriggerScintillator_Physical; 
  G4Material*        TriggerScintillator_Material;

  G4double Container_FullLength_X;
  G4double Container_FullLength_Y;
  G4double Container_FullLength_Z;

  G4double StraightBar_FullLength;
  G4double StraightBar_FullHeight;
  G4double StraightBar_FullThickness;

  G4double TriggerScintillatorCenterZPosition;

 
  G4double Tilting_Angle;      // total tilting angle towards mean track
  G4double Thickness;         


  // placing the container
  G4ThreeVector     Position_TriggerScintillatorContainer;
  G4RotationMatrix* Rotation_TriggerScintillatorContainer;  

  // placing the right SingleBar
  G4ThreeVector    Translation_SingleBarRight; 

 // pointer to the sensitive detector
  G4VSensitiveDetector* TriggerScintillatorSD;

  G4double Position_TriggerScintillatorContainer_X;
  G4double Position_TriggerScintillatorContainer_Y;
  G4double Position_TriggerScintillatorContainer_Z;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator.hh,v $
//      Revision 1.2  2005/12/27 19:27:45  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
