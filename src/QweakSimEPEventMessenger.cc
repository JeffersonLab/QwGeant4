//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEventMessenger.cc

   \author Peiqing Wang

*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimEPEventMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEventMessenger::QweakSimEPEventMessenger(QweakSimEPEvent* pEPEvent)
:pQweakSimEPEvent(pEPEvent)
{
  std::cout << "###### Calling QweakSimEPEventMessenger::QweakSimEPEventMessenger () " << std::endl;

  EventGenDir = new G4UIdirectory("/EventGen/");
  EventGenDir->SetGuidance("Event generator control");
 
  verboseCmd = new G4UIcmdWithAnInteger("/EventGen/verbose",this);  
  verboseCmd->SetGuidance("set verbose for event generator");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SelectOctant_Cmd = new G4UIcmdWithAnInteger("/EventGen/SelectOctant",this);
  SelectOctant_Cmd->SetGuidance("Select octant for primaries");
  SelectOctant_Cmd->SetParameterName("SelectOctant",true);
  SelectOctant_Cmd->SetDefaultValue(1);
  SelectOctant_Cmd->SetRange("SelectOctant>=1 && SelectOctant<=8");
  SelectOctant_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//    ReactionType:            1 - LH2 elastic
//                             2 - Al window elastic
//                             3 - Al window quasi-elastic proton
//                             4 - Al window quasi-elastic neutron
//
//    ReactionRegion:          1 - LH2 target
//                             2 - entrance window
//                             3 - exit window

  SelectReactionType_Cmd = new G4UIcmdWithAnInteger("/EventGen/SeletReactionType",this);
  SelectReactionType_Cmd->SetGuidance("Select reaction type");
  SelectReactionType_Cmd->SetGuidance("1 - LH2 elastic (default)");
  SelectReactionType_Cmd->SetGuidance("2 - Al elastic");
  SelectReactionType_Cmd->SetGuidance("3 - Al quasi-elastic (proton)");
  SelectReactionType_Cmd->SetGuidance("4 - Al quasi-elastic (neutron)");
  SelectReactionType_Cmd->SetParameterName("SelectReactionType",true);
  SelectReactionType_Cmd->SetDefaultValue(1);
  SelectReactionType_Cmd->SetRange("SelectReactionType>=1");
  SelectReactionType_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SelectReactionRegion_Cmd = new G4UIcmdWithAnInteger("/EventGen/SeletReactionRegion",this);
  SelectReactionRegion_Cmd->SetGuidance("Select reaction region");
  SelectReactionRegion_Cmd->SetGuidance("1 - target (default)");
  SelectReactionRegion_Cmd->SetGuidance("2 - entrance target window");
  SelectReactionRegion_Cmd->SetGuidance("3 - exit target window");
  SelectReactionRegion_Cmd->SetParameterName("SelectReactionRegion",true);
  SelectReactionRegion_Cmd->SetDefaultValue(1);
  SelectReactionRegion_Cmd->SetRange("SelectReactionRegion>=1");
  SelectReactionRegion_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  std::cout << "###### Leavinging QweakSimEPEventMessenger::QweakSimEPEventMessenger () " << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEventMessenger::~QweakSimEPEventMessenger()
{
  std::cout << "###### Calling QweakSimEPEventMessenger::~QweakSimEPEventMessenger () " << std::endl;

  delete SelectOctant_Cmd;
  delete SelectReactionType_Cmd;
  delete SelectReactionRegion_Cmd;
  delete verboseCmd;
  delete EventGenDir;

  std::cout << "###### Leavinging QweakSimEPEventMessenger::~QweakSimEPEventMessenger () " << std::endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEventMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

  if( command == SelectOctant_Cmd )
    { 
      G4cout << "% % ===> Changing active octant number to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetActiveOctantNumber(SelectOctant_Cmd->GetNewIntValue(newValue)); 
    }

  if( command == SelectReactionType_Cmd )
    { 
      G4cout << "% % ===> Changing reaction type to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetReactionType(SelectReactionType_Cmd->GetNewIntValue(newValue)); 
    }

  if( command == SelectReactionRegion_Cmd )
    { 
      G4cout << "% % ===> Changing reaction region to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetReactionRegion(SelectReactionRegion_Cmd->GetNewIntValue(newValue)); 
    }

}
