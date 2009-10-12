//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGDMLGeometryMessenger.cc

   $Revision: 1.0 $
   $Date: 2009/10/12 13:32:26 $

   \author Wouter Deconinck

*/
//=============================================================================

#include "QweakSimGDMLGeometryMessenger.hh"

// ----------------------------------------------------------------------------

QweakSimGDMLGeometryMessenger::QweakSimGDMLGeometryMessenger(QweakSimGDMLGeometry* aGDMLGeometry)
  : theGDMLGeometry(aGDMLGeometry)
{
  theGDMLGeometryDir = new G4UIdirectory( "/GDML/" );
  theGDMLGeometryDir->SetGuidance("GDML geometry control.");

  theReadCommand = new G4UIcmdWithAString("/GDML/Read", this);
  theReadCommand->SetGuidance("Read geometry from GDML file with given name");
  theReadCommand->SetParameterName("FileRead", false);
  theReadCommand->SetDefaultValue("GDML/qweak.gdml");
  theReadCommand->AvailableForStates(G4State_PreInit);

  theWriteCommand = new G4UIcmdWithAString("/GDML/Write", this);
  theWriteCommand->SetGuidance("Write geometry to GDML file with given name");
  theWriteCommand->SetParameterName("FileWrite", false);
  theWriteCommand->SetDefaultValue("GDML/qweak_out.gdml");
  theWriteCommand->AvailableForStates(G4State_Idle);
}

// ----------------------------------------------------------------------------

QweakSimGDMLGeometryMessenger::~QweakSimGDMLGeometryMessenger()
{
  if (theReadCommand)     delete theReadCommand;
  if (theWriteCommand)    delete theWriteCommand;
  if (theGDMLGeometryDir) delete theGDMLGeometryDir;
}

// ----------------------------------------------------------------------------

void QweakSimGDMLGeometryMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if ( command == theReadCommand )
  {
    theGDMLGeometry->SetReadFile(newValue);
//    theGDMLGeometry->Read();
  }
  if ( command == theWriteCommand )
  {
    theGDMLGeometry->SetWriteFile(newValue);
    theGDMLGeometry->Write();
  }
}
