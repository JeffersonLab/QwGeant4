//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimPrimaryGeneratorActionMessenger.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:33:13 $
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
   \class QweakSimPrimaryGeneratorActionMessenger
    
   \brief Scans the input file for ...

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
//  Update Date:      $Date: 2006/05/05 21:33:13 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPrimaryGeneratorActionMessenger_h
#define QweakSimPrimaryGeneratorActionMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimPrimaryGeneratorAction.hh"

// system classes
// class G4UIdirectory;
// class G4UIcmdWithAnInteger;
// class G4UIcmdWithoutParameter;

// user classes
class QweakSimPrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimPrimaryGeneratorActionMessenger: public G4UImessenger
{
public:  
   QweakSimPrimaryGeneratorActionMessenger(QweakSimPrimaryGeneratorAction* );
  ~QweakSimPrimaryGeneratorActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:  
  
  QweakSimPrimaryGeneratorAction*     pPrimaryGeneratorAction;
  
  G4UIdirectory*           Dir;
  G4UIcmdWithAnInteger*    verboseCmd;
  G4UIcmdWithoutParameter* resetCmd;
  G4UIcmdWithAnInteger*    InitEventCounterCmd;
  G4UIcmdWithAnInteger*    SelectOctant_Cmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPrimaryGeneratorActionMessenger.hh,v $
//      Revision 1.3  2006/05/05 21:33:13  grimm
//      Added /PrimaryEvent/SelectOctant  #octant . This defines the octant of the generated tracks.
//
//      Revision 1.2  2005/12/27 19:26:24  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
