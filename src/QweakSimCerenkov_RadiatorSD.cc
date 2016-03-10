#include "QweakSimCerenkov_RadiatorSD.hh"

// user includes
#include "QweakSimSensitiveDetectorDefinition.hh"
#include "QweakSimCerenkov_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"

QweakSimCerenkov_RadiatorSD::QweakSimCerenkov_RadiatorSD(G4String name)
: G4VSensitiveDetector(name),
  CerenkovRadiatorHitsCollection(0),
  CerenkovRadiatorCollectionID(-1)
{
  collectionName.insert("CerenkovRadiatorCollection"); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_RadiatorSD::~QweakSimCerenkov_RadiatorSD() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkov_RadiatorSD::Initialize(G4HCofThisEvent* HCE)
{
  CerenkovRadiatorHitsCollection = new QweakSimCerenkovRadiatorHitsCollection(SensitiveDetectorName,collectionName[0]);

  CerenkovRadiatorCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  HCE->AddHitsCollection(CerenkovRadiatorCollectionID , CerenkovRadiatorHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool QweakSimCerenkov_RadiatorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{

//G4cout << G4endl << "###### Calling QweakSimCerenkov_RadiatorSD::ProcessHits() " << G4endl << G4endl;

  G4double charge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
  if(charge==0. && aStep->GetTrack()->GetTotalEnergy()/MeV < 0.1) {

    //G4cout << "Return on charge = 0" << G4endl;
    return false;
  }

  if( aStep->GetTrack()->GetDefinition()->GetParticleName() == "opticalphoton") {

    //std::cout << "Return on optical photon" << std::endl;
    return false;
  }
  
  G4StepPoint*        preStepPoint  = aStep->GetPreStepPoint();
//   G4StepPoint*        postStepPoint = aStep->GetPostStepPoint();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume*  physVol      = theTouchable->GetVolume();

//   if(strcmp(physVol->GetName(),"CerenkovDetector_Physical")) {
  if(strcmp(physVol->GetName(),"Radiator_Physical")) {
    return false;
  }

  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

  //======================================================================================
  // for test purpose only : print out all the source and primary info of this track 

//   G4cout << "Printing Track Info inside QweakSimCerenkov_RadiatorSD " << G4endl;
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
      //       G4cout << ">>>> QweakSimCerenkov_RadiatorSD: We are NOT crossing a boundary  <<<<<<" << G4endl;
      //       G4cout << ">>>>       Aborting QweakSimCerenkov_RadiatorSD::ProcessHits      <<<<<<" << G4endl;
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
  G4ThreeVector currentPolarization      = aStep->GetTrack()->GetPolarization();

  G4int trackID = aStep->GetTrack()->GetTrackID();
  G4int parentID = aStep->GetTrack()->GetParentID();
//   G4String processName = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
  G4String processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

   G4ParticleDefinition*  fpParticleDefinition = aStep->GetTrack()->GetDefinition();
   G4String ParticleName      = fpParticleDefinition->GetParticleName();
//   G4double PDGCharge         = fpParticleDefinition->GetPDGCharge();
   G4int PDGEncoding          = fpParticleDefinition->GetPDGEncoding();
   G4double particlemass = fpParticleDefinition->GetPDGMass()/MeV;

  G4int    MotherCopyNo   = theTouchable->GetVolume(1)->GetCopyNo();   // one Mother Volume
//  G4int DetectorCopyNo    = theTouchable->GetVolume()->GetCopyNo();    // but several detectors per MV
//  G4int DetectorReplicaNo = theTouchable->GetReplicaNumber();          // but several detectors per MV
//  G4int MotherReplicaNo   = theTouchable->GetReplicaNumber(1);        // Several MotherVolumes
//  G4int    MotherCopyNo2  = theTouchable->GetVolume(2)->GetCopyNo();  // Several MotherVolumes
//  G4int MotherReplicaNo2  = theTouchable->GetReplicaNumber(2);        // Several MotherVolumes


//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV    CopyNumber  :" << MotherCopyNo      << G4endl;
//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov       CopyNumber  :" << DetectorCopyNo    << G4endl;
//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov    ReplicaNumber  :" << DetectorReplicaNo << G4endl;
//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV ReplicaNumber  :" << MotherReplicaNo << G4endl;
//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov MV    CopyNumber2 :" << MotherCopyNo2     << G4endl;
//    G4cout << "%%%%%%%%%%%%%%%%%%%  Cerenkov    ReplicaNumber2 :" << MotherReplicaNo2  << G4endl;


  // get User Track Info
//  QweakSimTrackInformation* info = (QweakSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());

//   G4int    primaryTrackID                 = info->GetPrimaryTrackID();
//   G4double primaryQ2                      = info->GetPrimaryQ2();
//   G4double crossSection                   = info->GetCrossSection();
//   G4double crossSectionWeight             = info->GetCrossSectionWeight();

  QweakSimCerenkov_RadiatorHit* aHit = new QweakSimCerenkov_RadiatorHit(MotherCopyNo);

  aHit->StoreTrackID(trackID);
  aHit->StoreParentID(parentID);
  aHit->StoreCreatorProcessName(processName);

  aHit->StoreDetectorID(MotherCopyNo);

  aHit->StoreGlobalTime(preStepPoint->GetGlobalTime());

  aHit->StoreWorldPosition(worldPos);
  aHit->StoreLocalPosition(localPos);

  aHit->StoreWorldMomentum(worldMomentum);
  aHit->StoreLocalMomentum(localMomentum);

  aHit->StoreOriginVertexPosition(originVertexPosition);
  aHit->StoreOriginVertexKineticEnergy(originVertexKineticEnergy);
  //aHit->StoreOriginVertexTotalEnergy(originVertexKineticEnergy);   /// \todo beware: total.neq.kinetic (testing only)
  aHit->StoreOriginVertexTotalEnergy(originVertexKineticEnergy + particlemass);
  aHit->StoreOriginVertexMomentumDirection(originVertexMomentumDirection);

  aHit->StoreMomentumDirection(currentMomentumDirection);
  aHit->StoreKineticEnergy(currentKineticEnergy);
  aHit->StoreTotalEnergy(currentTotalEnergy);
  aHit->StorePolarization(currentPolarization);

  aHit->StoreParticleName(ParticleName);
  aHit->StoreParticleType(PDGEncoding);
  
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

  CerenkovRadiatorHitsCollection->insert(aHit);
  
//   G4cout << G4endl << "###### Leaving QweakSimCerenkovRadiatorSD::ProcessHits() " << G4endl << G4endl;

// Peiqing: comment this disable geting secondary info
//  info->StoreCerenkovHitEnergy(info->GetParticleHistoryLength()-1,currentTotalEnergy);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkov_RadiatorSD::EndOfEvent(G4HCofThisEvent* )
{
  //G4cout << G4endl << "###### Calling QweakSimCerenkov_RadiatorSD::EndOfEvent() " << G4endl << G4endl;
  
//   G4int NbDCHits = DC_hitsCollection->entries();
  
//   G4cout << "\n-------->Hits Collection: in this event they are " << NbDCHits
// 	 << " hits in the Drift Cells : " << G4endl;
//   for (G4int i=0;i<NbDCHits;i++) (*DC_hitsCollection)[i]->Print();

   //G4cout << G4endl << "###### Leaving QweakSimCerenkov_RadiatorSD::EndOfEvent() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
