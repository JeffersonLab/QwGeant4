//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimEPEventMessenger.hh
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
   \class QweakSimEPEventMessenger
    
   \brief UI control for the event generator 
    
 */


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimEPEventMessenger_h
#define QweakSimEPEventMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimEPEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimEPEventMessenger: public G4UImessenger
{
public:  
   QweakSimEPEventMessenger(QweakSimEPEvent* );
  ~QweakSimEPEventMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:  
  
  QweakSimEPEvent*     pQweakSimEPEvent;
  
  G4UIdirectory*           EventGenDir;
  G4UIcmdWithAnInteger*    verboseCmd;
  G4UIcmdWithAnInteger*    SelectReactionType_Cmd;
  G4UIcmdWithAnInteger*    SelectReactionRegion_Cmd;
  G4UIcmdWithAnInteger*    SelectOctant_Cmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


