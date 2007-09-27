//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMiniMagnetMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:13:46 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:13:46 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMiniMagnetMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMiniMagnetMessenger::QweakSimMiniMagnetMessenger(QweakSimMiniMagnet* pMfield)
  : myMiniMagnet(pMfield)
{ 
  MiniMagnetDir = new G4UIdirectory("/MiniMagnet/");
  MiniMagnetDir->SetGuidance("Main MagnetControl for the MiniTorus");

  CenterPosInZCmd = new G4UIcmdWithADoubleAndUnit("/MiniMagnet/SetCenterPositionInZ",this);  
  CenterPosInZCmd->SetGuidance("Define Z Position of MiniMagnet Center");
  CenterPosInZCmd->SetParameterName("MiniMagnetCenterPositionInZ",false);
  CenterPosInZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  SingleCoilDir = new G4UIdirectory("/MiniMagnet/SingleCoil/");
  SingleCoilDir->SetGuidance("SingleCoil Control of MiniTorus");

  MinDiameterCmd = new G4UIcmdWithADoubleAndUnit("/MiniMagnet/SingleCoil/SetMinDiameter",this);  
  MinDiameterCmd->SetGuidance("Define minimal Diameter of SingleCoil");
  MinDiameterCmd->SetParameterName("min diameter",false,false);
  MinDiameterCmd->SetDefaultUnit("mm");
  MinDiameterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaxDiameterCmd = new G4UIcmdWithADoubleAndUnit("/MiniMagnet/SingleCoil/SetMaxDiameter",this);  
  MaxDiameterCmd->SetGuidance("Define maximal Diameter of SingleCoil");
  MaxDiameterCmd->SetParameterName("max diameter",false,false);
  MaxDiameterCmd->SetDefaultUnit("mm");
  MaxDiameterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  RadialDistanceCmd = new G4UIcmdWithADoubleAndUnit("/MiniMagnet/SingleCoil/SetDistanceCenterToBeamLine",this);  
  RadialDistanceCmd->SetGuidance("Define distance of SingleCoil center to the beamline");
  RadialDistanceCmd->SetParameterName("radial distance",false,false);
  RadialDistanceCmd->SetDefaultUnit("mm");
  RadialDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimMiniMagnetMessenger::~QweakSimMiniMagnetMessenger()
{
  delete CenterPosInZCmd;
  delete MinDiameterCmd;
  delete MaxDiameterCmd;
  delete RadialDistanceCmd;

  delete MiniMagnetDir;
  delete SingleCoilDir;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMiniMagnetMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimMiniMagnetMessenger::SetNewValue() " << newValue << G4endl;

  if( command == CenterPosInZCmd )
  { 
      G4cout << "#### Messenger: Setting Main Magnet CenterPositionInZ to " << newValue << G4endl;
      
      myMiniMagnet->SetCenterPositionInZ(CenterPosInZCmd->GetNewDoubleValue(newValue));
  }

  G4cout << "#### Leaving QweakSimMiniMagnetMessenger::SetNewValue() " << newValue << G4endl;

  
   if( command == MinDiameterCmd )
   { 
       G4cout << "#### Messenger: Setting MainMagnet SingleCoil Min Diameter to " << newValue << G4endl;
       
       myMiniMagnet->SetSingleCoil_DiameterMin(MinDiameterCmd->GetNewDoubleValue(newValue));
   }
   
   G4cout << "#### Leaving QweakSimMiniMagnetMessenger::SetNewValue() " << newValue << G4endl;


      if( command == MaxDiameterCmd )
   { 
       G4cout << "#### Messenger: Setting MainMagnet SingleCoil Max Diameter to " << newValue << G4endl;
       
       myMiniMagnet->SetSingleCoil_DiameterMax(MaxDiameterCmd->GetNewDoubleValue(newValue));
   }
   
   G4cout << "#### Leaving QweakSimMiniMagnetMessenger::SetNewValue() " << newValue << G4endl;

   
         if( command == RadialDistanceCmd )
   { 
       G4cout << "#### Messenger: Setting MainMagnet SingleCoil Radial Distance to " << newValue << G4endl;
       
       myMiniMagnet->SetSingleCoil_RadialCenterDistanceToBeamLine(RadialDistanceCmd->GetNewDoubleValue(newValue));
   }
   
   G4cout << "#### Leaving QweakSimMiniMagnetMessenger::SetNewValue() " << newValue << G4endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMiniMagnetMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:13:46  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
