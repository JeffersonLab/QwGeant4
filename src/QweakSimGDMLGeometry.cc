//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGDMLGeometry.cc

   $Revision: 1.0 $
   $Date: 2009/09/02 19:37:26 $

   \author Wouter Deconinck

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGDMLGeometry.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGDMLGeometry::QweakSimGDMLGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimGDMLGeometry::QweakSimGDMLGeometry() " << G4endl << G4endl;

  fReadFile  = "GDML/qweak.gdml";
  fWriteFile = "GDML/qweak_out.gdml";

#ifdef G4LIB_USE_GDML
  fGDMLParser = NULL;
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif

  fGeometryMessenger = new QweakSimGDMLGeometryMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGDMLGeometry::~QweakSimGDMLGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimGDMLGeometry::~QweakSimGDMLGeometry() " << G4endl << G4endl;
  if (fGeometryMessenger) delete fGeometryMessenger;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGDMLGeometry::SetReadFile(const G4String& file)
{
  fReadFile = file;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGDMLGeometry::SetWriteFile(const G4String& file)
{
  fWriteFile = file;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGDMLGeometry::SetWorldVolume(G4VPhysicalVolume* worldvolume)
{
  fWorldVolume = worldvolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGDMLGeometry::Write()
{
  G4cout << G4endl << "###### Calling QweakSimGDMLGeometry::Write() " << G4endl << G4endl;

#ifdef G4LIB_USE_GDML
  fGDMLParser.SetAddPointerToName(true);
  fGDMLParser.Write(fWriteFile, fWorldVolume);
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* QweakSimGDMLGeometry::Read()
{
  G4cout << G4endl << "###### Calling QweakSimGDMLGeometry::Read() " << G4endl << G4endl;

#ifdef G4LIB_USE_GDML
  fGDMLParser.SetOverlapCheck(false);
  fGDMLParser.Read(fReadFile);

  G4cout << *(G4Element::GetElementTable()) << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  G4VPhysicalVolume* worldvolume = fGDMLParser.GetWorldVolume();
#else
  G4cout << "No support for GDML geometry!" << G4endl;
  G4VPhysicalVolume* worldvolume = NULL;
#endif

  return worldvolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
