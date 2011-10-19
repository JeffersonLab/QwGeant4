
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimBeamLine.hh
   $Revision: 1.2 $	
   $Date: 2011/10/19 12:44 $
   \author Peiqing Wang
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimBeamLine
    
   \brief Definition of the BeamLine

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimBeamLine_h
#define QweakSimBeamLine_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 
// geant4 includes
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

// user includes
#include "QweakSimBeamLineMessenger.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimMaterial.hh"

// system classes
// class G4Tubs;
// class G4LogicalVolume;
// class G4VPhysicalVolume;
// class G4Material;
// class G4VisAttributes;

// user classes
class QweakSimMaterial;
class QweakSimBeamLineMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimBeamLine
{
public:
  QweakSimBeamLine(QweakSimUserInformation *myUI);
  ~QweakSimBeamLine();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();
  
  void SetBeamLineCenterPositionInZ(G4double);
  G4double GetBeamLineCenterPositionInZ();
  
  void SetBeamLineMaterial(G4String);
  G4String GetBeamLineMaterial();
  
  G4LogicalVolume*   getBeamLineLogicalVolume()    {return BeamLineContainer_Logical;} 
  G4VPhysicalVolume* getBeamLinePhysicalVolume()   {return BeamLineContainer_Physical;} 
  
private:

  QweakSimMaterial* pMaterial;

  G4LogicalVolume*   BeamPipe_Logical; 
  G4VPhysicalVolume* BeamPipe_Physical; 
  G4Material*        BeamPipe_Material;  

  G4LogicalVolume*   BeamLineContainer_Logical; 
  G4VPhysicalVolume* BeamLineContainer_Physical; 
  G4Material*        BeamLineContainer_Material;  

  G4double beamline_ZPos;
  
  QweakSimBeamLineMessenger* beamlineMessenger;  // pointer to the Messenger
  QweakSimUserInformation *myUserInfo;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
