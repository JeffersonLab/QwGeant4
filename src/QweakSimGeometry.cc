//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGeometry.cc

   $Revision: 1.0 $
   $Date: 2009/09/02 19:37:26 $

   \author Wouter Deconinck

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGeometry.hh"

// geant4 includes
#ifdef G4LIB_USE_GDML
#include "G4GDMLParser.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGeometry::QweakSimGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::QweakSimGeometry() " << G4endl << G4endl;

  fReadFile  = "GDML/qweak.gdml";
  fWriteFile = "GDML/qweak_out.gdml";

#ifdef G4LIB_USE_GDML
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif

  fGeometryMessenger = new QweakSimGeometryMessenger(this);

  G4cout << G4endl << "###### Leaving QweakSimGeometry::QweakSimGeometry() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGeometry::~QweakSimGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::~QweakSimGeometry() " << G4endl << G4endl;

  if (fGeometryMessenger) delete fGeometryMessenger;

  G4cout << G4endl << "###### Leaving QweakSimGeometry::~QweakSimGeometry() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGeometry::SetReadFile(const G4String& file)
{
  fReadFile = file;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGeometry::SetWriteFile(const G4String& file)
{
  fWriteFile = file;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGeometry::SetWorldVolume(G4VPhysicalVolume* worldvolume)
{
  fWorldVolume = worldvolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGeometry::Write()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::Write() " << G4endl << G4endl;

#ifdef G4LIB_USE_GDML
  fGDMLParser.Write(fWriteFile, fWorldVolume);
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif

  G4cout << G4endl << "###### Leaving QweakSimGeometry::Write() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* QweakSimGeometry::Read()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::Read() " << G4endl << G4endl;

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

  G4cout << G4endl << "###### Leaving QweakSimGeometry::Read() " << G4endl << G4endl;

  return worldvolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
