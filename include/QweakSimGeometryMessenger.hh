//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGeometryMessenger.hh

   $Revision: 1.0 $
   $Date: 2009/10/12 13:32:26 $

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
   \class QweakSimGeometryMessenger

   \brief Scans the input file for /GDML/ commands

   Placeholder for a long explaination

 */
//=============================================================================

#ifndef QweakSimGeometryMessenger_h
#define QweakSimGeometryMessenger_h 1

// system includes
#include "Geant4_include.hh"

// user include
#include "QweakSimGeometry.hh"

// user classes
class QweakSimGeometry;

// ----------------------------------------------------------------------------

class QweakSimGeometryMessenger: public G4UImessenger
{

  public:

    QweakSimGeometryMessenger(QweakSimGeometry*);
   ~QweakSimGeometryMessenger();

    void SetNewValue( G4UIcommand*, G4String );
    void SetNewValue( G4UIcommand*, G4int );

  private:

    QweakSimGeometry*          theGeometry;
    G4UIdirectory*             theGeometryDir;
    G4UIcmdWithAString*        theReadCommand;
    G4UIcmdWithAString*        theWriteCommand;
};

// ----------------------------------------------------------------------------

#endif
