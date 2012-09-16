//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTriggerScintillator_DetectorSD.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:16:07 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:16:07 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTriggerScintillator_DetectorSD.hh"

// user classes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimTriggerScintillator_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 

  collectionName.insert("TriggerScintillatorCollection"); 
  TriggerScintillator_CollectionID = -1;

  //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorSD::~QweakSimTriggerScintillator_DetectorSD()
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::~QweakSimTriggerScintillator_DetectorSD() " << G4endl << G4endl; 

  //delete TriggerScintillator_HitsCollection;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator_DetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::Initialize() " << G4endl << G4endl; 

   TriggerScintillator_DetectorHitsCollection = new QweakSimTriggerScintillator_DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);

   //if(TriggerScintillator_CollectionID<0)

   TriggerScintillator_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 

   HCE->AddHitsCollection(TriggerScintillator_CollectionID , TriggerScintillator_DetectorHitsCollection);
   
  //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::Initialize() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//G4bool QweakSimTriggerScintillatorSD::ProcessHits(G4Step* aStep,G4TouchableHistory* /*ROhist*/)
G4bool QweakSimTriggerScintillator_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
//   G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::ProcessHits() " << G4endl << G4endl; 


    // Dismiss Photons
    G4Track *track = aStep->GetTrack();    
    if (fabs(track->GetDefinition()->GetPDGCharge())<0.1) return false;

    G4ThreeVector worldPos;
    G4ThreeVector localPos;
    G4ThreeVector worldMomentum;
    
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();
 
 if (aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary ){
     // Entering Geometry
     worldPos      = aStep->GetPreStepPoint()->GetPosition();
     localPos      = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
     worldMomentum = aStep->GetPreStepPoint()->GetMomentum();

//     G4cout << "=======================================================================================" << G4endl;
//     G4cout << ">>>>>>>          Particle entering TriggerScintillator_Physical               <<<<<<<<<" << G4endl;
//     G4cout << "  After PreStep Boundary Check: TriggerScintillator WorldPos.Z [cm]:" << worldPos.z()/cm << G4endl;
//     G4cout << "=======================================================================================" << G4endl;

 }
else { return false;}

//  else if (aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary ){
//      // Exiting Geometry
//      worldPos      = aStep->GetPostStepPoint()->GetPosition();
//      localPos      = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
//      worldMomentum = aStep->GetPreStepPoint()->GetMomentum();
//
//      G4cout << "===================================================================" << G4endl;
//      G4cout << ">>>>>>> Particle exiting TriggerScintillator_Physical     <<<<<<<<<" << G4endl;
//      G4cout << "===================================================================" << G4endl;
//
//      G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  After PostStep Boundary Check: TriggerScintillator WorldPos.Z [cm]:" << worldPos.z()/cm   << G4endl;
//
//      // if(std::fabs( localpos2.z() + boxSolid->GetZHalfLength())<kCarTolerance ){ return fCurrent_Out; }
//  }
// 

//  else {
//             G4cout << "===================================================================================" << G4endl;
//             G4cout << ">>>> QweakSimTriggerScintillator_DetectorSD: We are NOT crossing a boundary  <<<<<<" << G4endl;
//             G4cout << ">>>>       Aborting QweakSimTriggerScintillator_DetectorSD::ProcessHits      <<<<<<" << G4endl;
//             G4cout << "===================================================================================" << G4endl;
//
//             return false;
//  }





//   if( physVol->GetName().compare("TriggerScintillator_Physical") != 0 ) {
//     G4cout << "Not in TriggerScintillator_Physical" << G4endl;
//     return false;
//   }




//  G4cout << "-------------------------------------------------------------------------------------------------------" << G4endl;

//  G4ThreeVector worldPos = preStepPoint->GetPosition();
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  TriggerScintillator WorldPos.X [cm]:" << worldPos.x()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  TriggerScintillator WorldPos.Y [cm]:" << worldPos.y()/cm << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  TriggerScintillator WorldPos.Z [cm]:" << worldPos.z()/cm << G4endl;

//  G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);
//   G4cout << "TriggerScintillator LocalPos.X [cm]:" << localPos.x()/cm << G4endl;
//   G4cout << "TriggerScintillator LocalPos.Y [cm]:" << localPos.y()/cm << G4endl;
//   G4cout << "TriggerScintillator LocalPos.Z [cm]:" << localPos.z()/cm << G4endl;
//
//G4ThreeVector worldMomentum = postStepPoint->GetMomentum();
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.X [GeV]:" << worldMomentum.x()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.Y [GeV]:" << worldMomentum.y()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane WorldMomentum.Z [GeV]:" << worldMomentum.z()/GeV << G4endl;
    
  G4ThreeVector localMomentum = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.X [GeV]:" << localMomentum.x()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.Y [GeV]:" << localMomentum.y()/GeV << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  WirePlane LocalMomentum.Z [GeV]:" << localMomentum.z()/GeV << G4endl;
// 
// 
// 
 // Vertex: where this track was generated
  G4ThreeVector originVertexPosition          = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double      originVertexKineticEnergy     = aStep->GetTrack()->GetVertexKineticEnergy();

//   G4cout << "====> originVertexPosition_X [cm]     : " <<  originVertexPosition.x()/cm << G4endl;
//   G4cout << "====> originVertexPosition_Y [cm]     : " <<  originVertexPosition.y()/cm << G4endl;
//   G4cout << "====> originVertexPosition_Z [cm]     : " <<  originVertexPosition.z()/cm << G4endl;

//   G4cout << "====> originVertexMomentumDirection_X : " <<  originVertexMomentumDirection.x() << G4endl;
//   G4cout << "====> originVertexMomentumDirection_Y : " <<  originVertexMomentumDirection.y() << G4endl;
//   G4cout << "====> originVertexMomentumDirection_Z : " <<  originVertexMomentumDirection.z() << G4endl;

//   G4cout << "====> originVertexKineticEnergy [Mev] : " <<  originVertexKineticEnergy/MeV << G4endl;

  G4double      currentKineticEnergy     = aStep->GetTrack()->GetKineticEnergy();
  G4double      currentTotalEnergy       = aStep->GetTrack()->GetTotalEnergy();
  G4ThreeVector currentMomentumDirection = aStep->GetTrack()->GetMomentumDirection();

  G4int trackID = aStep->GetTrack()->GetTrackID();
//   G4cout << "====> Track ID     : " <<  trackID << G4endl;

//   G4int parentID = aStep->GetTrack()->GetParentID();
//   G4cout << "====> Parent ID    : " <<  parentID << G4endl;

  
  G4int    MotherCopyNo    = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume
//   G4int DriftCellCopyNo    = theTouchable->GetVolume()->GetCopyNo();    // but several Driftcells per MV
//   G4int DriftCellReplicaNo = theTouchable->GetReplicaNumber();          // but several Driftcells per MV

//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%   MV TriggerScintillator    CopyNumber :" <<    MotherCopyNo    << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%      TriggerScintillator    CopyNumber :" << DriftCellCopyNo    << G4endl;
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%      TriggerScintillator ReplicaNumber :" << DriftCellReplicaNo << G4endl;
    
//   // Get User Track Info
//   QweakSimTrackInformation* info = (QweakSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());

//   G4int    primaryTrackID                 = info->GetPrimaryTrackID();
//   G4double primaryQ2                      = info->GetPrimaryQ2();
//   G4double crossSection                   = info->GetCrossSection();
//   G4double crossSectionWeight             = info->GetCrossSectionWeight();


//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original Track ID                 : " << primaryTrackID                  << G4endl;
//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original Track Q2                 : " << primaryQ2                       << G4endl;
//   G4cout << " @@@@@@@@@@@@@@@@@@@@@@@ Original CrossSection Weight (ub) : " << crossSectionWeight              << G4endl;

//   G4cout << " =====> Storing Trigger Scintillator hit information into aHit" << G4endl;

  QweakSimTriggerScintillator_DetectorHit* aHit = new QweakSimTriggerScintillator_DetectorHit(MotherCopyNo);
   
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  got QweakSimTriggerScintillatorHit* aHit" << G4endl;

  aHit->StoreTrackID(trackID);

  aHit->StoreGlobalTime(aStep->GetPreStepPoint()->GetGlobalTime());

  aHit->StoreWorldPosition(worldPos);
  aHit->StoreLocalPosition(localPos);

  aHit->StoreWorldMomentum(worldMomentum);
  aHit->StoreLocalMomentum(localMomentum);

  aHit->StoreOriginVertexPosition(originVertexPosition);
  aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  aHit->StoreOriginVertexTotalEnergy(originVertexKineticEnergy);   /// \todo beware: total.neq.kinetic (testing only)
  aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);

  aHit->StoreMomentumDirection(currentMomentumDirection);
  aHit->StoreKineticEnergy(currentKineticEnergy);
  aHit->StoreTotalEnergy(currentTotalEnergy);

  // check if it is first touch
  if(!(aHit->GetLogVolume()))
    {
      // store translation and rotation matrix of the drift cell 
      // for the sake of drawing the hit 
      aHit->StoreLogVolume(theTouchable->GetVolume()->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->StoreCellRotation(aTrans.NetRotation());
      aHit->StoreCellPosition(aTrans.NetTranslation());
    }
 
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  before inserting the hit" << G4endl;

  TriggerScintillator_DetectorHitsCollection->insert(aHit); 
  
//   G4cout << G4endl << "###### Leaving QweakSimTriggerScintillatorSD::ProcessHits() " << G4endl << G4endl; 
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void QweakSimTriggerScintillatorSD::EndOfEvent(G4HCofThisEvent*  HCE)
void QweakSimTriggerScintillator_DetectorSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator_DetectorSD::EndOfEvent() " << G4endl << G4endl; 
  
//   G4int NbDCHits = DC_hitsCollection->entries();
  
//   G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
// 	 << " hits in the Drift Cells : " << G4endl;
//   for (G4int i=0;i<NbDCHits;i++) (*DC_hitsCollection)[i]->Print();
  


   //G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator_DetectorSD::EndOfEvent() " << G4endl << G4endl; 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_DetectorSD.cc,v $
//      Revision 1.2  2005/12/27 19:16:07  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
