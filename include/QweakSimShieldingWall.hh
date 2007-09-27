
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimShieldingWall.hh
   $Revision: 1.4 $	
   $Date: 2006/04/26 20:02:17 $
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
   \class QweakSimShieldingWall
    
   \brief Defines the Shielding Wall with trapezoid cut outs
         (located after Main Magnet and before Region 3 VDCs)

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
//  Update Date:      $Date: 2006/04/26 20:02:17 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimShieldingWall_h
#define QweakSimShieldingWall_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimShieldingWallMessenger.hh"
#include "QweakSimMaterial.hh"

// user classes
class QweakSimMaterial;
class QweakSimShieldingWallMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//class QweakSimShieldingWall: public QweakSimVGeometryComponent
//class QweakSimShieldingWall: public G4VUserDetectorConstruction
class QweakSimShieldingWall
{
public:
  QweakSimShieldingWall();
  ~QweakSimShieldingWall();

  void ConstructShieldingWallHousing_UsingTrapezoids(G4VPhysicalVolume*);
  void ConstructShieldingWallHousing_UsingCones(G4VPhysicalVolume*);

  void DestroyComponent();
  void SetCollimatorWall_CenterPositionInZ(G4double);
  void SetCollimatorWallMaterial(G4String);

  void DefineOctantCutOut_UsingATrapezoid();
  void SetOctantCutOut_Trap_RadialDistance(G4double);
  void SetOctantCutOut_Trap_FullLengthFront(G4double);
  void SetOctantCutOut_Trap_FullLengthBack(G4double);
  void SetOctantCutOut_Trap_FullHeightFront(G4double);
  void SetOctantCutOut_Trap_FullHeightBack(G4double);
  void SetOctantCutOut_Trap_PolarAngle(G4double);


  void DefineOctantCutOut_UsingACone();
  void SetOctantCutOut_Cone_FrontInnerDiameter(G4double fid) {OctantCutOut_Cone_FrontInnerDiameter = fid;}
  void SetOctantCutOut_Cone_FrontOuterDiameter(G4double fod) {OctantCutOut_Cone_FrontOuterDiameter = fod;}
  void SetOctantCutOut_Cone_BackInnerDiameter(G4double bid)  {OctantCutOut_Cone_BackInnerDiameter  = bid;}
  void SetOctantCutOut_Cone_BackOuterDiameter(G4double bod)  {OctantCutOut_Cone_BackOuterDiameter  = bod;}
  void SetOctantCutOut_Cone_StartingPhiAngle(G4double spa)   {OctantCutOut_Cone_StartingPhiAngle   = spa;}
  void SetOctantCutOut_Cone_DeltaPhiAngle(G4double dpa)      {OctantCutOut_Cone_DeltaPhiAngle      = dpa;}

  void SetCollimatorWall_FullLengthInX(G4double);
  void SetCollimatorWall_FullLengthInY(G4double);
  void SetCollimatorWall_FullLengthInZ(G4double);

  G4LogicalVolume*   getShieldingWallHousingLogicalVolume()    {return ShieldingWallHousing_Logical;} 
  G4VPhysicalVolume* getShieldingWallHousingPhysicalVolume()   {return ShieldingWallHousing_Physical;} 


  //---------------------------------------------------------------
  void ConstructFrontWall(G4VPhysicalVolume* MotherVolume);
  void ConstructBackWall(G4VPhysicalVolume* MotherVolume);
  void ConstructBeamLeftSideWall(G4VPhysicalVolume* MotherVolume);
  void ConstructBeamRightSideWall(G4VPhysicalVolume* MotherVolume);
  void ConstructTopWall(G4VPhysicalVolume* MotherVolume);
  //-----
  void ShowCollimatorWall();
  void HideCollimatorWall();
  //-----  
  void ShowFrontWall();
  void HideFrontWall();
   //----- 
  void ShowBackWall();
  void HideBackWall();
  //-----
  void ShowBeamLeftSideWall();
  void HideBeamLeftSideWall();
  //-----
  void ShowBeamRightSideWall();
  void HideBeamRightSideWall();
  //-----
  void ShowTopWall();
  void HideTopWall();
  //---------------------------------------------------------------

private:

  QweakSimShieldingWallMessenger* ShieldingWallMessenger;  // pointer to the Messenger

  QweakSimMaterial* pMaterial;

  G4LogicalVolume*   ShieldingWallHousing_Logical; 
  G4VPhysicalVolume* ShieldingWallHousing_Physical; 
  G4Material*        ShieldingWallHousing_Material;

  G4double ShieldingWallHousing_FullLength_X;
  G4double ShieldingWallHousing_FullLength_Y;
  G4double ShieldingWallHousing_FullLength_Z;

  G4double ShieldingWallHousing_UpStreamWall_ZPosition;
  G4double ShieldingWallHousing_CenterZPosition;

  G4double OctantCutOut_Trap_RadialDistance;
  G4double OctantCutOut_Trap_FullLengthFront;
  G4double OctantCutOut_Trap_FullLengthBack;
  G4double OctantCutOut_Trap_FullHeightFront;
  G4double OctantCutOut_Trap_FullHeightBack;
  G4double OctantCutOut_Trap_PolarAngle;

  G4double OctantCutOut_Cone_FrontInnerDiameter;
  G4double OctantCutOut_Cone_FrontOuterDiameter;
  G4double OctantCutOut_Cone_BackInnerDiameter;
  G4double OctantCutOut_Cone_BackOuterDiameter;
  G4double OctantCutOut_Cone_StartingPhiAngle;
  G4double OctantCutOut_Cone_DeltaPhiAngle;

  // needed for octant cuts in the shielding wall
  std::vector< G4SubtractionSolid* >  MyShieldingWallHousing_Solid;

  // std::vector< G4ThreeVector >       OctantTranslationVector;
  // std::vector< G4RotationMatrix >    OctantRotationMatrix;
  // std::vector< G4Transform3D >       OctantTransform3D;

  G4Trap* OctantCutOut_Trap_Solid;
  G4Cons* OctantCutOut_Cone_Solid;

  G4ThreeVector    positionShieldingWallHousing;
  G4VisAttributes* ShieldingWallHousing_VisAtt;

  //--------------------
  // Hut area related
  //--------------------
  G4double InnerHut_FullLength_X; // horizontally
  G4double InnerHut_FullLength_Z; // along beam

  //--------------------
  // Front Wall related
  //--------------------
  G4LogicalVolume*   FrontWall_Logical; 
  G4VPhysicalVolume* FrontWall_Physical; 
  G4Material*        FrontWall_Material;

  G4double FrontWall_FullLength_X;
  G4double FrontWall_FullLength_Y;
  G4double FrontWall_FullLength_Z;

  G4double FrontWallBeamCutout_FullLength_X;
  G4double FrontWallBeamCutout_FullLength_Y;
  G4double FrontWallBeamCutout_FullLength_Z;

  G4SubtractionSolid* MyFrontWall_Solid;

  G4double DeltaZOffset_FrontWall_ShieldingWall;
  G4double FrontWall_UpStreamWall_ZPosition;
  G4double FrontWall_CenterZPosition;

  G4ThreeVector    positionFrontWall;
  G4VisAttributes* FrontWall_VisAtt;

  //--------------------
  // Back Wall related
  //--------------------
  G4LogicalVolume*   BackWall_Logical; 
  G4VPhysicalVolume* BackWall_Physical; 
  G4Material*        BackWall_Material;

  G4double BackWall_FullLength_X;
  G4double BackWall_FullLength_Y;
  G4double BackWall_FullLength_Z;

  G4double BackWallBeamCutout_FullLength_X;
  G4double BackWallBeamCutout_FullLength_Y;
  G4double BackWallBeamCutout_FullLength_Z;

  G4SubtractionSolid* MyBackWall_Solid;

  G4double DeltaZOffset_BackWall_ShieldingWall;
  G4double BackWall_UpStreamWall_ZPosition;
  G4double BackWall_CenterZPosition;

  G4ThreeVector    positionBackWall;
  G4VisAttributes* BackWall_VisAtt;

  //----------------------------
  // Beam Left Side Wall related
  //----------------------------
  G4LogicalVolume*   BeamLeftSideWall_Logical; 
  G4VPhysicalVolume* BeamLeftSideWall_Physical; 
  G4Material*        BeamLeftSideWall_Material;

  G4double BeamLeftSideWall_FullLength_X;
  G4double BeamLeftSideWall_FullLength_Y;
  G4double BeamLeftSideWall_FullLength_Z;

  G4double BeamLeftSideWall_CenterXPosition;
  G4double BeamLeftSideWall_CenterZPosition;

  G4ThreeVector    positionBeamLeftSideWall;
  G4VisAttributes* BeamLeftSideWall_VisAtt;

  //-----------------------------
  // Beam Right Side Wall related
  //-----------------------------
  G4LogicalVolume*   BeamRightSideWall_Logical; 
  G4VPhysicalVolume* BeamRightSideWall_Physical; 
  G4Material*        BeamRightSideWall_Material;

  G4double BeamRightSideWall_FullLength_X;
  G4double BeamRightSideWall_FullLength_Y;
  G4double BeamRightSideWall_FullLength_Z;

  G4double BeamRightSideWallBeamCutout_FullLength_X;
  G4double BeamRightSideWallBeamCutout_FullLength_Y;
  G4double BeamRightSideWallBeamCutout_FullLength_Z;

  G4double BeamRightSideWall_CenterXPosition;
  G4double BeamRightSideWall_CenterZPosition;

  G4ThreeVector    positionBeamRightSideWall;
  G4VisAttributes* BeamRightSideWall_VisAtt;

  //-----------------------------
  // Top Wall related
  //-----------------------------
  //
  G4LogicalVolume*   TopWall_Logical; 
  G4VPhysicalVolume* TopWall_Physical; 
  G4Material*        TopWall_Material;

  G4double TopWall_FullLength_X;
  G4double TopWall_FullLength_Y;
  G4double TopWall_FullLength_Z;

  G4double TopWall_CenterYPosition;
  G4double TopWall_CenterZPosition;

  G4ThreeVector    positionTopWall;
  G4VisAttributes* TopWall_VisAtt;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimShieldingWall.hh,v $
//      Revision 1.4  2006/04/26 20:02:17  grimm
//      The shielding wall has been extended to a shielding detector hut
//
//      Revision 1.3  2006/01/18 20:20:14  grimm
//      Added visibility functions: ShowShieldingWall(), HideShieldingWall()
//
//      Revision 1.2  2005/12/27 19:26:40  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

