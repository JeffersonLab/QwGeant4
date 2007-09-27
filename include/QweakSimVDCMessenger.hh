
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDCMessenger.hh
   $Revision: 1.4 $	
   $Date: 2006/05/05 21:42:14 $
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
   \class QweakSimVDCMessenger
    
   \brief Scans the input file for /VDC/xyz commands

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
//  Update Date:      $Date: 2006/05/05 21:42:14 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDCMessenger_h
#define QweakSimVDCMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
//#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimVDC.hh"

// user classes
class QweakSimVDC;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimVDCMessenger: public G4UImessenger
{
  public:
    QweakSimVDCMessenger(QweakSimVDC*);
   ~QweakSimVDCMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimVDC*               myVDC;
  
  G4UIdirectory*             VDCDir;

  G4UIcmdWithAString*        VDC_MasterContainerMatCmd;
  G4UIcmdWithAString*        VDC_SubContainerMatCmd;

  G4UIcmdWithAString*        VDC_G10FrameMatCmd;
  G4UIcmdWithAString*        VDC_AluFrameMatCmd;

  G4UIcmdWithAString*        VDC_FoilMatCmd;
  G4UIcmdWithAString*        VDC_WirePlaneMatCmd;

  G4UIcmdWithADoubleAndUnit* VDC_FrontCenterPositionInX_Cmd;
  G4UIcmdWithADoubleAndUnit* VDC_FrontCenterPositionInY_Cmd;
  G4UIcmdWithADoubleAndUnit* VDC_FrontCenterPositionInZ_Cmd;
  G4UIcmdWithADoubleAndUnit* VDC_RotationAngleInPhi_Cmd;
  G4UIcmdWithADoubleAndUnit* VDC_MeanTrackAngleInTheta_Cmd;
  
  G4UIdirectory*             DriftCellDir;

  G4UIcmdWithAString*        DCMatCmd;
  G4UIcmdWithADoubleAndUnit* DCFrontWireAngleCmd;
  G4UIcmdWithADoubleAndUnit* DCBackWireAngleCmd;
  G4UIcmdWithADoubleAndUnit* DCThicknessCmd;
  G4UIcmdWithADoubleAndUnit* DCHeightCmd;
  G4UIcmdWithADoubleAndUnit* DCWidthOnFrameCmd;
  G4UIcmdWithAnInteger*      DCNumberPerPlaneCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDCMessenger.hh,v $
//      Revision 1.4  2006/05/05 21:42:14  grimm
//      Added
//
//      G4UIcmdWithAString*        DCMatCmd;
//
//      Revision 1.3  2006/01/06 21:37:36  grimm
//      Trivial renaming of internal variables
//
//      Revision 1.2  2005/12/27 19:32:43  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

