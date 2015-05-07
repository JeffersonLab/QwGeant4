/**
 
   \file QweakSimTungstenPlug.hh
   \author Wouter Deconinck
     
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimTungstenPlug_h
#define QweakSimTungstenPlug_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// geant4 includes
#include "G4LogicalVolume.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// user classes
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimTungstenPlug
{

private:

  QweakSimMaterial* pMaterial;
  
  // W-Plug
  G4LogicalVolume*   TungstenPlugLogical;
  G4VPhysicalVolume* TungstenPlugPhysical;

  G4Material*        TungstenPlug_Material;  

  // Sensitive Detectors
  G4VSensitiveDetector* TungstenPlugSD;

public:
  //! Constructor
  QweakSimTungstenPlug();

  //! Destructor
  virtual ~QweakSimTungstenPlug();

  void ConstructTungstenPlug(G4VPhysicalVolume*);

  G4VPhysicalVolume* getTungstenPlugPhysicalVolume()   {return TungstenPlugPhysical;}

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

