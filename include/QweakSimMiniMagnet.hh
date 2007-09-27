//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimMiniMagnet.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:25:51 $
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
   \class QweakSimMiniMagnet
    
   \brief Mini Magnet solids like coils and support. No field.

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
//  Update Date:      $Date: 2005/12/27 19:25:51 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMiniMagnet_h
#define QweakSimMiniMagnet_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
//#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimMiniMagnetMessenger.hh"
#include "QweakSimMaterial.hh"
//#include "QweakSimMagnet_MiniTorusCoilParameterisation.hh"

// user classes
class QweakSimMiniMagnetMessenger;
class QweakSimMaterial;
//class QweakSimMagnet_MiniTorusCoilParameterisation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMiniMagnet
{
public:

   QweakSimMiniMagnet();
  ~QweakSimMiniMagnet();

  void ConstructComponent(G4VPhysicalVolume* MotherVolume);
  void DestroyComponent();

  void SetCenterPositionInZ(G4double myCenterPositionInZ);

  void SetSingleCoil_DiameterMax(G4double DiameterMax) { SingleCoil_MasterContainer_DiameterMax = DiameterMax; }
  void SetSingleCoil_DiameterMin(G4double DiameterMin) { SingleCoil_MasterContainer_DiameterMin = DiameterMin; }
  void SetSingleCoil_RadialCenterDistanceToBeamLine(G4double RadialDistance) { SingleCoil_CenterPositionInR = RadialDistance; }

  //G4LogicalVolume*   getMiniMagnetLogicalVolume()    {return MiniMagnet_MasterContainer_Logical;} 
  //G4VPhysicalVolume* getMiniMagnetPhysicalVolume()   {return MiniMagnet_MasterContainer_Physical;} 

private:

  QweakSimMiniMagnetMessenger*      MiniMagnet_Messenger;

  QweakSimMaterial* pMaterial;

//   G4LogicalVolume*   MiniMagnet_MasterContainer_Logical;
//   G4VPhysicalVolume* MiniMagnet_MasterContainer_Physical;
//   G4Material*        MiniMagnet_MasterContainer_Material;
//
//   G4double MiniMagnet_MasterContainer_FullLength_X;
//   G4double MiniMagnet_MasterContainer_FullLength_Y;
//   G4double MiniMagnet_MasterContainer_FullLength_Z;

  G4double MiniMagnet_CenterPositionInZ;

   // SingleCoil MasterContainer
   G4LogicalVolume*   SingleCoil_MasterContainer_Logical; 
   G4Material*        SingleCoil_MasterContainer_Material;

   G4double SingleCoil_MasterContainer_DiameterMin; 
   G4double SingleCoil_MasterContainer_DiameterMax;
   G4double SingleCoil_MasterContainer_FullThickness;
   G4double SingleCoil_MasterContainer_PhiAngleStart;
   G4double SingleCoil_MasterContainer_PhiAngleEnd;
 
   G4double SingleCoil_CenterPositionInR;

   // needed for manual coil placement
   std::vector< G4VPhysicalVolume* > SingleCoil_MasterContainer_Physical;
   std::vector< G4double >           Angle_SingleCoil;
   std::vector< G4ThreeVector >      Translation_SingleCoil;
   std::vector< G4RotationMatrix* >  Rotation_SingleCoil;




};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMiniMagnet.hh,v $
//      Revision 1.2  2005/12/27 19:25:51  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

