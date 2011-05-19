
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimMagnetFieldMapMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:25:29 $
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
   \class QweakSimMagnetFieldMapMessenger
    
   \brief Scans input file for /MagnetField/xyz commands

    Not used yet. Intended to set the StepperType and SetMinStep for the magnet fields.

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
//  Update Date:      $Date: 2005/12/27 19:25:29 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimMagnetFieldMapMessenger_h
#define QweakSimMagnetFieldMapMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimMagnetFieldMap;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimMagnetFieldMapMessenger: public G4UImessenger
{
  public:
    QweakSimMagnetFieldMapMessenger(QweakSimMagnetFieldMap* );
   ~QweakSimMagnetFieldMapMessenger();
    
  private:

    QweakSimMagnetFieldMap*    fMfieldSetup;
    
    G4UIdirectory*             MainMagnetDir;

    G4UIcmdWithAnInteger*      StepperCmd;
    G4UIcmdWithADoubleAndUnit* MagFieldCmd;
    G4UIcmdWithADoubleAndUnit* MinStepCmd;
    G4UIcmdWithoutParameter*   UpdateCmd;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnetFieldMapMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:25:29  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 



