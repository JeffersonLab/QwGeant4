//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimGDMLGeometry.hh
   $Revision: 0.1 $
   $Date: 2009/09/02 19:37:26 $
   \author Wouter Deconinck

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimGDMLGeometry

   \brief main class of QweakSim.
    All passive elements are are read from the GDML files.

 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//  Last Update:      $Author: wdconinc $
//  Update Date:      $Date: 2009/09/02 19:37:26 $
//  CVS/RCS Revision: $Revision: 1.0 $
//  Status:           $State: Exp $
//
//=============================================================================

#ifndef QweakSimGDMLGeometry_h
#define QweakSimGDMLGeometry_h 1

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh"

// user includes
#include "QweakSimGDMLGeometryMessenger.hh"

// user classes
class QweakSimGDMLGeometryMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimGDMLGeometry
{
  public:

    QweakSimGDMLGeometry();
   ~QweakSimGDMLGeometry();

    void SetWorldVolume(G4VPhysicalVolume* worldvolume);

    // Reading and writing file name
    //
    void SetReadFile(const G4String& file);
    void SetWriteFile(const G4String& file);

    // Read and write GDML files
    //
    G4VPhysicalVolume* Read();
    void Write();

  private:

    // World volume
    //
    G4VPhysicalVolume* fWorldVolume;

    // Read and write file names
    //
    G4String fReadFile;
    G4String fWriteFile;

#ifdef G4LIB_USE_GDML
    // GDMLparser
    //
    G4GDMLParser fGDMLParser;
#endif

    // Geometry Messenger
    //
    QweakSimGDMLGeometryMessenger* fGeometryMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
