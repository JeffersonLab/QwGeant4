//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGDMLGeometryMessenger.hh

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
   \class QweakSimGDMLGeometryMessenger

   \brief Scans the input file for /GDML/ commands

   Placeholder for a long explaination

 */
//=============================================================================

#ifndef QweakSimGDMLGeometryMessenger_h
#define QweakSimGDMLGeometryMessenger_h 1

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh"

// user include
#include "QweakSimGDMLGeometry.hh"

// user classes
class QweakSimGDMLGeometry;

// ----------------------------------------------------------------------------

class QweakSimGDMLGeometryMessenger: public G4UImessenger
{

  public:

    QweakSimGDMLGeometryMessenger(QweakSimGDMLGeometry*);
   ~QweakSimGDMLGeometryMessenger();

    void SetNewValue( G4UIcommand*, G4String );
    void SetNewValue( G4UIcommand*, G4int );

  private:

    QweakSimGDMLGeometry*      theGDMLGeometry;
    G4UIdirectory*             theGDMLGeometryDir;
    G4UIcmdWithAString*        theReadCommand;
    G4UIcmdWithAString*        theWriteCommand;
};

// ----------------------------------------------------------------------------

#endif
