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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimSteppingAction::QweakSimSteppingAction(QweakSimUserInformation* myUInfo, QweakSimEPEvent* myEPEvent)
{ 

G4cout << "###### Calling QweakSimSteppingAction::QweakSimSteppingAction() " << G4endl;

  myEventCounter = 0;
  fSecondary = NULL;
  myUserInfo = myUInfo;

  myEvent = myEPEvent;

  evtGenStatus = 0;
  RandomPositionZ = myEvent->GetVertexZ();

//  std::ofstream EventDataFile("Event.dat", std::ios::out);

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


//jpan@nuclear.uwinnipeg.ca Thu Apr 16 01:33:14 CDT 2009
// I'd like to disregard all secondaries to speed up the primary particle simulation
// check if it is primary
  G4int parentID = theTrack->GetParentID();

  if( particleType==G4Electron::ElectronDefinition() && parentID==0 ){

//jpan: to account for the energy loss before the event generation,
//      force to change primary momentum direction here

    //scattering only occur inside reaction region of the target, only occur once
    G4ThreeVector thePosition = theTrack->GetPosition();
    G4double theX = thePosition.getX();
    G4double theY = thePosition.getY();
    G4double theZ = thePosition.getZ();

   if( theZ > -650*cm+35*cm*0.5+5*(2.54*cm*0.001) || sqrt(theX*theX+theY*theY)>2.54*cm) 
    {
       evtGenStatus = 0;
       RandomPositionZ = myEvent->GetVertexZ();
    }

    if(evtGenStatus == 0){

      G4double theStepLength = theStep->GetStepLength();

       //trap the particle
        if( abs(theZ - RandomPositionZ)<=theStepLength && sqrt(theX*theX+theY*theY)<2.54*cm)
           { 
             G4double CrossSection, WeightN, Q2, E_out, theta, phi;
             G4ThreeVector MomentumDirection;
             G4double E_in = theTrack->GetKineticEnergy()/MeV;  //Event generator needs units of MeV
             myEvent->GetanEvent(E_in, CrossSection, WeightN, Q2, E_out, MomentumDirection, theta, phi);
             theTrack->SetKineticEnergy(E_out*MeV);
             theTrack->SetMomentumDirection(MomentumDirection);

             evtGenStatus = 1;
             myEventCounter = myEventCounter + 1;

             // set track info
            theTrack->SetVertexPosition(thePosition);
            theTrack->SetVertexMomentumDirection(MomentumDirection);
            theTrack->SetVertexKineticEnergy(E_out);

            //fill user info
             myUserInfo->StoreTrackID(theTrack->GetTrackID());
             myUserInfo->StoreGlobalTime(theTrack->GetGlobalTime());
             myUserInfo->StoreOriginVertexPositionX(theX);
             myUserInfo->StoreOriginVertexPositionY(theY);
             myUserInfo->StoreOriginVertexPositionZ(theZ);
             myUserInfo->StoreOriginVertexMomentumDirectionX(MomentumDirection.getX());
             myUserInfo->StoreOriginVertexMomentumDirectionY(MomentumDirection.getY());
             myUserInfo->StoreOriginVertexMomentumDirectionZ(MomentumDirection.getZ());
             myUserInfo->StoreOriginVertexThetaAngle(theta);
             myUserInfo->StoreOriginVertexPhiAngle(phi);
             myUserInfo->StoreOriginVertexKineticEnergy(theTrack->GetKineticEnergy());
             myUserInfo->StoreOriginVertexTotalEnergy(theTrack->GetTotalEnergy());
             myUserInfo->StorePrimaryQ2(Q2*0.000001); //in units of GeV^2
             myUserInfo->StoreCrossSection(CrossSection);
             myUserInfo->StoreCrossSectionWeight(WeightN);
             myUserInfo->StorePrimaryEventNumber(myEventCounter);
             myUserInfo->StoreReactionType(myEvent->GetReactionType());
             myUserInfo->StorePDGcode(3);

             // print the stored values
//             G4cout << "*********** myEventCounter = " << myEventCounter << G4endl;

// std::ofstream EventDataFile("Event.dat", std::ios::app);
// EventDataFile << "Event: "<<myEventCounter<<std::endl;
// EventDataFile << "E_in : "<<E_in<<std::endl;
// EventDataFile << "E_out: "<<E_out<<std::endl;
// EventDataFile << "StepLength: "<<theStepLength/mm<<" mm"<<std::endl;
// EventDataFile << "myTrack ID: "<<theTrack->GetTrackID()<<std::endl;
// EventDataFile << "Eng_deposi: "<<theStep->GetTotalEnergyDeposit ()/MeV<<" MeV"<<std::endl;
// EventDataFile << "Material: "<<theTrack->GetMaterial()<<std::endl;
 
//             myUserInfo->Print();
      }
    }
  }
  else  //secondary
   { 
//      theTrack->SetTrackStatus(fStopAndKill); 
//      return;
   }

//jpan@nuclear.uwinnipeg
//kill a track if it is in collimators or shielding wall
  if(thePrePV->GetName()=="CollimatorHousing" || thePrePV->GetName()=="ShieldingWallHousing"){
  theTrack->SetTrackStatus(fStopAndKill); return;
  }

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

  


//jpan@nuclear.uwinnipeg.ca
// I commented out the cout statements for speeding up 

//  G4cout << "Particle Name = " << particleType->GetParticleName() << G4endl;

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
//  G4cout << "Particle History For This Particle" << G4endl;
//  G4cout << "Event ID = " << myUserInfo->GetPrimaryEventNumber() << G4endl;
  //   G4cout << "Hit ID = " << myUserInfo->GetCurrentPMTHit()->GetHitID() << G4endl;
//  for(int i = 0; i < TrackInfo->GetParticleHistoryLength(); i++){	  
//    G4cout << "Particle "<< i <<" = " << TrackInfo->GetParticleDefinitionAtIndex(i)->GetParticleName() << std::setw(9)
//           << " at position " << G4BestUnit(TrackInfo->GetOriginVertex(i),"Length") << std::setw(9);
//    if(i == TrackInfo->GetParticleHistoryLength()-1)
//      G4cout << " Parent Eng = " << theTrack->GetTotalEnergy()/MeV;
//    else
//      G4cout << " Parent Eng = " << TrackInfo->GetParentEnergyAtIndex(i+1)/MeV;
//    G4cout << std::setw(18);
//    G4cout << " Creator Process = " << TrackInfo->GetCreatorProcessAtIndex(i);
//    G4cout << std::setw(18);
//    G4cout << " Kinetic Energy = " <<TrackInfo->GetPrimaryKineticEnergy();
//    G4cout << " Cerenkov Hit Energy = " << TrackInfo->GetCerenkovHitEnergyAtIndex(i) << G4endl;
//  }
//   if(TrackInfo->GetParticleHistoryLength() > 1 &&
//      TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-1) == G4Gamma::GammaDefinition() &&
//      TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2) != G4Electron::ElectronDefinition() &&
//      TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2) != G4Positron::PositronDefinition())
//     {
//       G4cout << "Gamma Created by " << TrackInfo->GetParticleDefinitionAtIndex(TrackInfo->GetParticleHistoryLength()-2)->GetParticleName() << G4endl;
//     }

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

//jpan@nuclear.uwinnipeg.ca
//The following codes cause the electron tracks killed at the edge of magnetic field
//This must be avoid by increasing the 10000 steps to 100000. 

  if ( theStep->GetTrack()->GetCurrentStepNumber() > 100000 )
      theStep->GetTrack()->SetTrackStatus(fStopAndKill);

//
//======================================================================

  // G4cout << "###### Leaving QweakSimSteppingAction::UserSteppingAction() " << G4endl;

  return;

 //jpan@nuclear.uwinnipeg.ca

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


