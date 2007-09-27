//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimSteppingAction.cc

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:46:05 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:46:05 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimSteppingAction::QweakSimSteppingAction(QweakSimUserInformation* myUInfo)
{ 

G4cout << "###### Calling QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;

  fSecondary = NULL;
  myUserInfo = myUInfo;

G4cout << "###### Leaving QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimSteppingAction::UserSteppingAction(const G4Step* theStep)
{ 

  //G4cout << "###### Calling QweakSimSteppingAction::UserSteppingAction() " << G4endl;

  fSecondary = fpSteppingManager->GetfSecondary();
  //G4cout << " got fSecondary" << G4endl;

  G4Track*              theTrack     = theStep->GetTrack();
  G4StepPoint*          thePrePoint  = theStep->GetPreStepPoint();
  G4VPhysicalVolume*    thePrePV     = thePrePoint->GetPhysicalVolume();
  G4StepPoint*          thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume*    thePostPV    = thePostPoint->GetPhysicalVolume(); 
  G4TouchableHistory*   theTouchable = (G4TouchableHistory*)(thePrePoint->GetTouchable());
  G4int                 ReplicaNo    = 0;
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  G4String              particleName = theTrack->GetDefinition()->GetParticleName();
  G4ProcessManager*     pm           = particleType->GetProcessManager();
  G4int                 nprocesses   = pm->GetProcessListLength();
  G4ProcessVector*      pv           = pm->GetProcessList();  
  G4VSteppingVerbose   *theVerbStep  = G4VSteppingVerbose::GetInstance();
  G4double              charge       = particleType->GetPDGCharge();


  G4int nSecAtRest       = GetNumOfAtRestSecondaries();
  G4int nSecAlong        = GetNumOfAlongStepSecondaries();
  G4int nSecPost         = GetNumOfPostStepSecondaries();
  G4int nSecTotal        = GetTotalNumOfSecondaries();

  QweakSimTrackInformation* info = (QweakSimTrackInformation*)(theTrack->GetUserInformation());

  for(G4int i = GetTrackVectorSize()-nSecTotal; i < GetTrackVectorSize(); i++){

    if((*fSecondary)[i]->GetUserInformation()==0){
      QweakSimTrackInformation* infoNew = new QweakSimTrackInformation(info);

      infoNew->StoreParticleDefinition(GetSecondaryParticleDefinition(i));
      infoNew->StoreParentEnergy(theTrack->GetTotalEnergy());
      infoNew->StorePrimaryKineticEnergy(GetSecondaryParticleKineticEnergy(i));
      infoNew->StoreCerenkovHitEnergy(-1,-1.0*MeV);
      infoNew->StoreCreatorProcess(GetSecondaryCreatorProcessName(i));
      infoNew->StoreOriginVertex(GetSecondaryParticleOrigin(i));
      (*fSecondary)[i]->SetUserInformation(infoNew);
    } 

    if(particleType==G4Electron::ElectronDefinition() && theTrack->GetParentID() == 0 &&
//        !strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")){
       (!strcmp(thePrePV->GetName(),"QuartzBar_PhysicalRight") || !strcmp(thePrePV->GetName(),"QuartzBar_PhysicalLeft") )){
      if(GetSecondaryParticleDefinition(i) == G4OpticalPhoton::OpticalPhotonDefinition() &&
	 GetSecondaryParticleTotalEnergy(i)/eV <= 4.9594){
	myUserInfo->IncrementCerenkovOpticalPhotonCount();
	myUserInfo->StoreCerenkovPhotonEnergy(GetSecondaryParticleTotalEnergy(i)); 
      }  
    }
  }

  


  G4cout << "Particle Name = " << particleType->GetParticleName() << G4endl;

//   if(!strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")){
//!strcmp(thePrePV->GetName(),"LightGuide_PhysicalRight") || !strcmp(thePrePV->GetName(),"LightGuide_PhysicalLeft")

  if(!strcmp(thePrePV->GetName(),"QuartzBar_PhysicalRight") || !strcmp(thePrePV->GetName(),"QuartzBar_PhysicalLeft")){

    myUserInfo->AddCerenkovEnergyDeposit(theStep->GetTotalEnergyDeposit());
    
    
    if(theTrack->GetParentID() > 0 && (particleType==G4Electron::ElectronDefinition() || 
				       particleType==G4Positron::PositronDefinition() ||
				       particleType==G4Gamma::GammaDefinition())){
	
//       if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"CerenkovContainer_Physical") &&
	 // 	 !strcmp(thePrePV->GetName(),"CerenkovDetector_Physical")
// 	 ){

      if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"ActiveArea_Physical")){
		
	myUserInfo->StoreCerenkovSecondaryParticleInfo(theTrack->GetVertexPosition(),
						       theTrack->GetMomentum(),
						       theTrack->GetTotalEnergy(),
						       charge);
      }
    }
  }



  if(particleType==G4Electron::ElectronDefinition()){

    G4ThreeVector worldPos = thePrePoint->GetPosition();
    G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

    if((!strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalRight") || 
	!strcmp(myUserInfo->GetStoredStepVolumeName(),"QuartzBar_PhysicalLeft")) &&
       (!strcmp(thePrePV->GetName(),"ActiveArea_Physical") || 
	!strcmp(thePrePV->GetName(),"CerenkovMasterContainer_Physical"))){
	 
      //     if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"CerenkovDetector_Physical") &&
      //        !strcmp(thePrePV->GetName(),"CerenkovContainer_Physical")){
      myUserInfo->StoreLocalCerenkovExitPosition(localPos);
      
    }
  }

  QweakSimTrackInformation *TrackInfo = (QweakSimTrackInformation*)theTrack->GetUserInformation();
  G4cout << "Particle History For This Particle" << G4endl;
  G4cout << "Event ID = " << myUserInfo->GetPrimaryEventNumber() << G4endl;
  //   G4cout << "Hit ID = " << myUserInfo->GetCurrentPMTHit()->GetHitID() << G4endl;
  for(int i = 0; i < TrackInfo->GetParticleHistoryLength(); i++){	  
    G4cout << "Particle "<< i <<" = " << TrackInfo->GetParticleDefinitionAtIndex(i)->GetParticleName() << std::setw(9)
           << " at position " << G4BestUnit(TrackInfo->GetOriginVertex(i),"Length") << std::setw(9);
    if(i == TrackInfo->GetParticleHistoryLength()-1)
      G4cout << " Parent Eng = " << theTrack->GetTotalEnergy()/MeV;
    else
      G4cout << " Parent Eng = " << TrackInfo->GetParentEnergyAtIndex(i+1)/MeV;
    G4cout << std::setw(18);
    G4cout << " Creator Process = " << TrackInfo->GetCreatorProcessAtIndex(i);
    G4cout << std::setw(18);
    G4cout << " Kinetic Energy = " <<TrackInfo->GetPrimaryKineticEnergy();
    G4cout << " Cerenkov Hit Energy = " << TrackInfo->GetCerenkovHitEnergyAtIndex(i) << G4endl;
  }
  if(TrackInfo->GetParticleHistoryLength() > 1 &&
     TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-1) == G4Gamma::GammaDefinition() &&
     TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2) != G4Electron::ElectronDefinition() &&
     TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2) != G4Positron::PositronDefinition())
    {
      G4cout << "Gamma Created by " << TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2)->GetParticleName() << G4endl;
    }

  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
  
    if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"PMTEntranceWindow_Physical")){
      if(!strcmp(thePrePV->GetName(),"Cathode_Physical")){
	

	
// 	G4int index = 0;
// 	if(TrackInfo->GetParticleHistoryLength() < 3)
// // 	  myUserInfo->SetPhotonFromPrimary(TrackInfo->GetParticleDefinitionAtIndex(index));
// 	else{
// 	  index = TrackInfo->GetParticleHistoryLength()-3;
// // 	  myUserInfo->SetPhotonFromParticle(TrackInfo->GetParticleDefinitionAtIndex(index));
// 	}

	myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
	// 	theTrack->SetTrackStatus(fStopAndKill);
      }
    }    
  } 

  myUserInfo->StoreStepVolumeName(thePrePV->GetName()); 

//======================================================================
//   Stolen from GATE code:
// 
//   In a few random cases, a particle gets 'stuck' in an
//   an infinite loop in the geometry. It then oscillates until GATE
//   crashes on some out-of-memory error.
//   To prevent this from happening, I've added below a quick fix where
//   particles get killed when their step number gets absurdely high

  if ( theStep->GetTrack()->GetCurrentStepNumber() > 10000 )
      theStep->GetTrack()->SetTrackStatus(fStopAndKill);
//
//======================================================================

  // G4cout << "###### Leaving QweakSimSteppingAction::UserSteppingAction() " << G4endl;

  return;
}       // end of QweakSimSteppingAction::UserSteppingAction
                
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int QweakSimSteppingAction::GetTrackVectorStartIndex()
{
  if(!fSecondary) return -1;

  return (*fSecondary).size() - GetTotalNumOfSecondaries();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int QweakSimSteppingAction::GetTrackVectorSize()
{
  if(!fSecondary) return 0;
  return (*fSecondary).size();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ParticleDefinition *QweakSimSteppingAction::GetSecondaryParticleDefinition(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return NULL; 

  return (*fSecondary)[idx]->GetDefinition();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 G4String QweakSimSteppingAction::GetSecondaryParticleName(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return "undefined"; 

  return (*fSecondary)[idx]->GetDefinition()->GetParticleName();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleTotalEnergy(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return -1; 

  return (*fSecondary)[idx]->GetTotalEnergy();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleKineticEnergy(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return -1; 

  return (*fSecondary)[idx]->GetKineticEnergy();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleXOrigin(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6; 

  return (*fSecondary)[idx]->GetPosition().x();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleYOrigin(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6; 

  return (*fSecondary)[idx]->GetPosition().y();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimSteppingAction::GetSecondaryParticleZOrigin(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6; 

  return (*fSecondary)[idx]->GetPosition().z();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreeVector QweakSimSteppingAction::GetSecondaryParticleOrigin(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6; 

  return (*fSecondary)[idx]->GetPosition();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......      
G4ThreeVector QweakSimSteppingAction::GetSecondaryParticleMomentum(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return 1e6; 

  return (*fSecondary)[idx]->GetMomentumDirection();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String QweakSimSteppingAction::GetSecondaryCreatorProcessName(G4int idx)
{
  if(!fSecondary || idx >= GetTrackVectorSize() || idx < GetTrackVectorStartIndex()) return "undefined"; 
  return (*fSecondary)[idx]->GetCreatorProcess()->GetProcessName();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



  //----------------------------------------------------------------------------------------------------------------------------------------------------------
  // here we are only interested if the particle is crossing a boundary
  // If you want to identify the first step in a volume: pick fGeomBoundary status in preStepPoint
  // If you want to identify a step out of a volume    : pick fGeomBoundary status in postStepPoint

//   if( (theStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) && (strcmp( theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName(),"CerenkovDetector_Physical") == 0) ) //OK
//   //if( (theStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) && (strcmp( theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName(),"CerenkovDetector_Physical") == 0) ) // crash
//    {
//       G4cout << "------------------------" << G4endl;
//       //G4cout << "PreStepVolumeName  = " << theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
//       //G4cout << "PostStepVolumeName = " << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
//       G4cout << "------------------------" << G4endl;

// //       QweakSimTrackInformation* trackInfo;
// //       trackInfo = (QweakSimTrackInformation*)(theTrack->GetUserInformation());
// //       trackInfo->SetTrackingStatus(1);
// //       trackInfo->SetImpactTrackInformationForCerenkov(theTrack);
      
//   }			

  //----------------------------------------------------------------------------------------------------------------------------------------------------------

//   if(particleType==G4Electron::ElectronDefinition())
//   {
//       G4ThreeVector worldPos = thePrePoint->GetPosition();
//       G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
      
//       if( (myUserInfo->GetStoredStepVolumeName().compare("CerenkovDetector_Physical")==0) &&
// 	  (thePrePV->GetName().compare("CerenkovContainer_Physical")==0) )
//       { 
// 	  myUserInfo->StoreLocalCerenkovExitPosition(localPos);
//       }
//   }
  //----------------------------------------------------------------------------------------------------------------------------------------------------------
  
//   if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
//     if(!strcmp(myUserInfo->GetStoredStepVolumeName(),"PMTEntranceWindow_Physical")){
//
//
//       if(!strcmp(thePrePV->GetName(),"Cathode_Physical")){
//
//         QweakSimTrackInformation *TrackInfo = (QweakSimTrackInformation*)theTrack->GetUserInformation();
//         G4cout << "Particle History For This Photon" << G4endl;
//         G4cout << "Event ID = " << myUserInfo->GetPrimaryEventNumber() << G4endl;
//         G4cout << "Hit ID = " << myUserInfo->GetCurrentPMTHit()->GetHitID() << G4endl;
//         for(int i = 0; i < TrackInfo->GetParticleHistoryLength(); i++){
//           G4cout << "Particle "<< i <<" = " << TrackInfo->GetParticleDefinitionAtIndex(i)->GetParticleName();
//           if(i == TrackInfo->GetParticleHistoryLength()-1)
//             G4cout << " Eng = " << theTrack->GetTotalEnergy()/MeV;
//           else
//             G4cout << " Eng = " << TrackInfo->GetParentEnergyAtIndex(i+1)/MeV;
//
//           G4cout << " Cerenkov Hit Energy = " << TrackInfo->GetCerenkovHitEnergyAtIndex(i) << G4endl;
//         }
// //      G4int index = 0;
// //      if(TrackInfo->GetParticleHistoryLength() < 3)
// // //     myUserInfo->SetPhotonFromPrimary(TrackInfo->GetParticleDefinitionAtIndex(index));
// //      else{
// //        index = TrackInfo->GetParticleHistoryLength()-3;
// // //     myUserInfo->SetPhotonFromParticle(TrackInfo->GetParticleDefinitionAtIndex(index));
// //      }
//
//         myUserInfo->GetCurrentPMTHit()->SetHitValid(True);
//         //      theTrack->SetTrackStatus(fStopAndKill);
//       }
//     }
//   }





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimSteppingAction.cc,v $
//      Revision 1.4  2006/05/05 21:46:05  grimm
//      Added Color control of tracks/particles in the visualization, e.g. neutrons appear as white tracks.
//
//      Revision 1.3  2006/03/01 16:58:20  grimm
//      Cosmetic changes
//
//      Revision 1.2  2005/12/27 19:14:57  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//


