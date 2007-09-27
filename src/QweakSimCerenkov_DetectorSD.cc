//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimCerenkov_DetectorSD.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:03:43 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:03:43 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkov_DetectorSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_DetectorSD::QweakSimCerenkov_DetectorSD(G4String name)
:G4VSensitiveDetector(name)
{
  //G4cout << G4endl << "###### Calling QweakSimCerenkov_DetectorSD::QweakSimCerenkov_DetectorSD() " << G4endl << G4endl; 

  collectionName.insert("CerenkovDetectorCollection"); 
  CerenkovDetector_CollectionID = -1;

  //G4cout << G4endl << "###### Leaving QweakSimCerenkov_DetectorSD::QweakSimCerenkov_DetectorSD() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_DetectorSD::~QweakSimCerenkov_DetectorSD()
{
  //G4cout << G4endl << "###### Calling QweakSimCerenkov_DetectorSD::~QweakSimCerenkov_DetectorSD() " << G4endl << G4endl; 

  //delete CerenkovDetector_HitsCollection;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkov_DetectorSD::Initialize(G4HCofThisEvent* HCE)
{
  //G4cout << G4endl << "###### Calling QweakSimCerenkov_DetectorSD::Initialize() " << G4endl << G4endl; 

   CerenkovDetector_HitsCollection = new QweakSimCerenkovDetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
   
   CerenkovDetector_CollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 

   HCE->AddHitsCollection(CerenkovDetector_CollectionID , CerenkovDetector_HitsCollection);



  //G4cout << G4endl << "###### Leaving QweakSimCerenkov_DetectorSD::Initialize() " << G4endl << G4endl; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//G4bool QweakSimCerenkovDetectorSD::ProcessHits(G4Step* aStep,G4TouchableHistory* /*ROhist*/)
G4bool QweakSimCerenkov_DetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{

//G4cout << G4endl << "###### Calling QweakSimCerenkov_DetectorSD::ProcessHits() " << G4endl << G4endl; 

  G4double charge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();

//   if(charge==0. && aStep->GetTrack()->GetTotalEnergy()/MeV < 0.1) {
//
//     G4cout << "Return on charge = 0" << G4endl;
//
//     return false;
//   }

  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
  G4StepPoint*        postStepPoint = aStep->GetPostStepPoint();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume*  physVol      = theTouchable->GetVolume();

//   if(strcmp(physVol->GetName(),"CerenkovDetector_Physical")) {
  if(strcmp(physVol->GetName(),"ActiveArea_Physical")) {
    return false;
  }

  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

  //======================================================================================
  // for test purpose only : print out all the source and primary info of this track 

//   G4cout << "Printing Track Info inside QweakSimCerenkov_DetectorSD " << G4endl;
//
//   QweakSimTrackInformation* trackInfo;
//
//   trackInfo = (QweakSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());
//   trackInfo->PrintSourceTrackInfo();
//   trackInfo->PrintPrimaryTrackInfo();

 //======================================================================================
   

  //G4cout << "PreStep  Process in the Cerenkov = " << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
  //G4cout << "PostStep Process in the Cerenkov = " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;

  // here we are only interested if the particle is crossing a boundary
  // If you want to identify the first step in a volume: pick fGeomBoundary status in preStepPoint
  // If you want to identify a step out of a volume    : pick fGeomBoundary status in postStepPoint

  if (preStepPoint->GetStepStatus() != fGeomBoundary) {

      //       G4cout << "=======================================================================" << G4endl; 
      //       G4cout << ">>>> QweakSimCerenkov_DetectorSD: We are NOT crossing a boundary  <<<<<<" << G4endl; 
      //       G4cout << ">>>>       Aborting QweakSimCerenkov_DetectorSD::ProcessHits      <<<<<<" << G4endl; 
      //       G4cout << "=======================================================================" << G4endl;   
    return false;
  }

  G4ThreeVector worldMomentum = preStepPoint->GetMomentum();
  G4ThreeVector localMomentum = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldMomentum);

 // Vertex: where this track was generated
  G4ThreeVector originVertexPosition          = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector originVertexMomentumDirection = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double      originVertexKineticEnergy     = aStep->GetTrack()->GetVertexKineticEnergy();

  G4double      currentKineticEnergy     = aStep->GetTrack()->GetKineticEnergy();
  G4double      currentTotalEnergy       = aStep->GetTrack()->GetTotalEnergy();
  G4ThreeVector currentMomentumDirection = aStep->GetTrack()->GetMomentumDirection();

  G4double trackID = aStep->GetTrack()->GetTrackID();

  
  G4int    MotherCopyNo   = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume
//   G4int DetectorCopyNo    = theTouchable->GetVolume()->GetCopyNo();    // but several detectors per MV
//   G4int DetectorReplicaNo = theTouchable->GetReplicaNumber();          // but several detectors per MV
//   G4int MotherReplicaNo   = theTouchable->GetReplicaNumber(1);        // Several MotherVolumes
//   G4int    MotherCopyNo2  = theTouchable->GetVolume(2)->GetCopyNo();  // Several MotherVolumes
//   G4int MotherReplicaNo2  = theTouchable->GetReplicaNumber(2);        // Several MotherVolumes
//

    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV    CopyNumber  :" << MotherCopyNo      << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov       CopyNumber  :" << DetectorCopyNo    << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov    ReplicaNumber  :" << DetectorReplicaNo << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV ReplicaNumber  :" << MotherReplicaNo << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV    CopyNumber2 :" << MotherCopyNo2     << G4endl;
//     G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov    ReplicaNumber2 :" << MotherReplicaNo2  << G4endl;


  // get User Track Info
  QweakSimTrackInformation* info = (QweakSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());

  G4int    primaryTrackID                 = info->GetPrimaryTrackID();
  G4double primaryQ2                      = info->GetPrimaryQ2();
  G4double crossSectionWeight             = info->GetCrossSectionWeight();

  QweakSimCerenkov_DetectorHit* aHit = new QweakSimCerenkov_DetectorHit(MotherCopyNo);

  aHit->StoreTrackID(trackID);

  aHit->StoreDetectorID(MotherCopyNo);

  aHit->StoreGlobalTime(preStepPoint->GetGlobalTime());

  aHit->StoreWorldPosition(worldPos);
  aHit->StoreLocalPosition(localPos);

  aHit->StoreWorldMomentum(worldMomentum);
  aHit->StoreLocalMomentum(localMomentum);

  aHit->StoreOriginVertexPosition(originVertexPosition);
  aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  aHit->StoreOriginVertexTotalEnergy(originVertexKineticEnergy);   // beware: total.neq.kinetic (testing only)
  aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);

  aHit->StoreMomentumDirection(currentMomentumDirection);
  aHit->StoreKineticEnergy(currentKineticEnergy);
  aHit->StoreTotalEnergy(currentTotalEnergy);

  aHit->StorePrimaryQ2(primaryQ2);
  aHit->StoreCrossSectionWeight(crossSectionWeight);

  // check if it is first touch
  if(!(aHit->GetLogVolume()))
    {
      // store translation and rotation matrix of the drift cell 
      // for the sake of drawing the hit 
      aHit->StoreLogVolume(physVol->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->StoreCellRotation(aTrans.NetRotation());
      aHit->StoreCellPosition(aTrans.NetTranslation());
    }
  
//   G4cout << "%%%%%%%%%%%%%%%%%%%%%%%  before inserting the hit" << G4endl;

  CerenkovDetector_HitsCollection->insert(aHit); 
  
//   G4cout << G4endl << "###### Leaving QweakSimCerenkovDetectorSD::ProcessHits() " << G4endl << G4endl; 
  
  
  info->StoreCerenkovHitEnergy(info->GetParticleHistoryLength()-1,currentTotalEnergy);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void QweakSimCerenkovDetectorSD::EndOfEvent(G4HCofThisEvent*  HCE)
void QweakSimCerenkov_DetectorSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimCerenkov_DetectorSD::EndOfEvent() " << G4endl << G4endl; 
  
//   G4int NbDCHits = DC_hitsCollection->entries();
  
//   G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
// 	 << " hits in the Drift Cells : " << G4endl;
//   for (G4int i=0;i<NbDCHits;i++) (*DC_hitsCollection)[i]->Print();
  


   //G4cout << G4endl << "###### Leaving QweakSimCerenkov_DetectorSD::EndOfEvent() " << G4endl << G4endl; 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCerenkov_DetectorSD.cc,v $
//      Revision 1.2  2005/12/27 19:03:43  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
