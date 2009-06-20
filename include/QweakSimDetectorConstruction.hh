//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimDetectorConstruction.hh
   $Revision: 1.4 $	
   $Date: 2006/05/02 00:58:26 $
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
   \class QweakSimDetectorConstruction
    
   \brief main class of QweakSim.
    All experiment components are are placed here.	

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
//  Update Date:      $Date: 2006/05/02 00:58:26 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

#ifndef QweakSimDetectorConstruction_h
#define QweakSimDetectorConstruction_h 1

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimDetectorMessenger.hh"

#include "QweakSimMaterial.hh"
#include "QweakSimTarget.hh"
#include "QweakSimTargetMessenger.hh"
#include "QweakSimCollimator.hh"
#include "QweakSimCollimatorSupport.hh"
#include "QweakSimShieldingWall.hh"
#include "QweakSimMainMagnet.hh"
#include "QweakSimVDC.hh"
#include "QweakSimVDCRotator.hh"
#include "QweakSimHDC.hh"
#include "QweakSimGEM.hh"
#include "QweakSimTriggerScintillator.hh"
#include "QweakSimCerenkovDetector.hh"
#include "QweakSimGlobalMagnetField.hh"
#include "QweakSimUserInformation.hh"

// user classes
class QweakSimDetectorMessenger;

class QweakSimMaterial;
class QweakSimTarget;
class QweakSimTargetMessenger;
class QweakSimCollimator;
class QweakSimCollimatorSupport;
class QweakSimShieldingWall;
class QweakSimMainMagnet;
class QweakSimVDC;
class QweakSimVDCRotator;
class QweakSimHDC;
class QweakSimGEM;
class QweakSimTriggerScintillator;
class QweakSimCerenkovDetector;
class QweakSimGlobalMagnetField;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
     QweakSimDetectorConstruction(QweakSimUserInformation*);
    ~QweakSimDetectorConstruction();

public:

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();
  void SetGlobalMagneticField();
  void ShowHallFloor();
  void HideHallFloor();

  G4double   GetWorldFullLengthInX()    {return fWorldLengthInX;}
  G4double   GetWorldFullLengthInY()    {return fWorldLengthInY;}
  G4double   GetWorldFullLengthInZ()    {return fWorldLengthInZ;}

private:

    QweakSimUserInformation* myUserInfo;
    G4VPhysicalVolume*       ConstructQweak();  

  void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);


  QweakSimMaterial*          pMaterial;
  QweakSimTarget*            pTarget;


  QweakSimCollimator*        pCollimator1;
  QweakSimCollimator*        pCollimator2;
  QweakSimCollimator*        pCollimator3;

  QweakSimCollimatorSupport* pCollimatorSupport;

  QweakSimShieldingWall*     pShieldingWall;

  QweakSimMainMagnet*        pMainMagnet; 


  QweakSimVDC*                  pVDC; 
  QweakSimHDC*                  pHDC;
  QweakSimGEM*                  pGEM;

  QweakSimVDCRotator*           pVDCRotator; 

  QweakSimTriggerScintillator*  pTriggerScintillator; 
  QweakSimCerenkovDetector*     pCerenkovDetector; 
  //G4VReadOutGeometry*        pROHitPlane;

  QweakSimDetectorMessenger*      detectorMessenger;  // pointer to the Messenger

     G4Box*             experimentalHall_Solid;     // pointer to the solid envelope 
     G4LogicalVolume*   experimentalHall_Logical;   // pointer to the logical envelope
     G4VPhysicalVolume* experimentalHall_Physical;  // pointer to the physical envelope
     G4Material*        experimentalHall_Material; 

     G4Box*             HallFloor_Solid;     // pointer to the solid envelope 
     G4LogicalVolume*   HallFloor_Logical;   // pointer to the logical envelope
     G4VPhysicalVolume* HallFloor_Physical;  // pointer to the physical envelope
     G4Material*        HallFloor_Material; 
     G4VisAttributes*   HallFloor_VisAtt;

     G4double fWorldLength;               // Full length of the world volume
     G4double fWorldLengthInX;            // Full length of the world volume
     G4double fWorldLengthInY;            // Full length of the world volume
     G4double fWorldLengthInZ;            // Full length of the world volume

     G4double fFloorLengthInX;         
     G4double fFloorLengthInY;         
     G4double fFloorLengthInZ;         
     G4double fFloorPositionInY;

  //----------------------
  // global magnet section
  //----------------------
  //
  QweakSimGlobalMagnetField*      pGlobalMagnetField;

     G4FieldManager*         fGlobalFieldManager;
     G4ChordFinder*          fGlobalChordFinder;
     G4Mag_UsualEqRhs*       fGlobalEquation; 
     G4MagIntegratorStepper* fGlobalStepper;

     G4double                fMinStep;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimDetectorConstruction.hh,v $
//      Revision 1.4  2006/05/02 00:58:26  grimm
//      Implemented VDC Rotator
//
//      Revision 1.3  2005/12/28 22:49:21  grimm
//      Added QweakSimCollimatorSupport into the world
//
//      Revision 1.2  2005/12/27 19:23:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
