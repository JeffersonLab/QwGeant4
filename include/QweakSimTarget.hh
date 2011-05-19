
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTarget.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:27:07 $
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
   \class QweakSimTarget
    
   \brief Definition of the Target

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
//  Update Date:      $Date: 2005/12/27 19:27:07 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTarget_h
#define QweakSimTarget_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

// user classes
class QweakSimMaterial;
class QweakSimTargetMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimTarget
{
public:
  QweakSimTarget();
  ~QweakSimTarget();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();
  void SetTargetCenterPositionInZ(G4double);
  void SetTargetMaterial(G4String);
  void SetTargetCellMaterial(G4String);


  G4LogicalVolume*   getTargetLogicalVolume()    {return TargetMaterial_Logical;} 
  G4VPhysicalVolume* getTargetPhysicalVolume()   {return TargetMaterial_Physical;} 

private:

  QweakSimMaterial* pMaterial;

  G4LogicalVolume*   TargetCell_Logical; 
  G4VPhysicalVolume* TargetCell_Physical; 
  G4Material*        TargetCell_Material;  

  G4LogicalVolume*   TargetWindowFront_Logical; 
  G4VPhysicalVolume* TargetWindowFront_Physical; 
  G4LogicalVolume*   TargetWindowBack_Logical; 
  G4VPhysicalVolume* TargetWindowBack_Physical;

  G4LogicalVolume*   TargetMaterial_Logical; 
  G4VPhysicalVolume* TargetMaterial_Physical; 
  G4Material*        Target_Material;  

  G4double targetCellWindowThickness;
  G4double targetCellWallThickness;

  G4double targetCellInnerLength;               
  G4double targetCellOuterLength;

  G4double targetCellRadiusMin;
  G4double targetCellInnerRadiusMax;
  G4double targetCellOuterRadiusMax;

  G4double targetCellStartingPhi;
  G4double targetCellDeltaPhi;
  G4double targetCellZPos;

  QweakSimTargetMessenger* targetMessenger;  // pointer to the Messenger

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTarget.hh,v $
//      Revision 1.2  2005/12/27 19:27:07  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//





