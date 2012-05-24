//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimPrimaryGeneratorAction.cc

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:35:07 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorAction.hh"

// geant4 includes
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

// user includes
#include "QweakSimPrimaryGeneratorActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4int QweakSimPrimaryGeneratorAction::kActiveOctantNumber = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI, QweakSimEPEvent* myEPEvent)
{

  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;
  


  fPositionX_min = -2.0*mm;
  fPositionX_max =  2.0*mm;
  fPositionY_min = -2.0*mm;
  fPositionY_max =  2.0*mm;

  myUserInfo = myUI;
  myEvent = myEPEvent;
   
  // get my messenger
  myMessenger = new QweakSimPrimaryGeneratorActionMessenger(this);

  // initialize my own event counter
  // myEventCounter = 0;

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction()
{

  G4cout << "###### Calling/Leaving QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction " << G4endl;

  if (particleGun) delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
//  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

//jpan@nuclear.uwinnipeg.ca
//
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  particleGun->SetParticleDefinition(particle);
  
  G4double E_beam;
  G4int myEventCounter = myUserInfo->GetPrimaryEventNumber();
  G4double myPositionX, myPositionY, myPositionZ;
  G4double myNormMomentumX, myNormMomentumY, myNormMomentumZ;
  if ( myEventCounter%2==0)
  {
    //std::cout << "###### QweakSimPrimaryGeneratorAction::Generate Test Primaries: " << myEventCounter<<std::endl;
    myPositionX =  myUserInfo->GetBeamPositionX() + (G4UniformRand()-0.5)*(fPositionX_max-fPositionX_min)+(fPositionX_max+fPositionX_min)/2.0;
    myPositionY =  myUserInfo->GetBeamPositionY() + (G4UniformRand()-0.5)*(fPositionY_max-fPositionY_min)+(fPositionY_max+fPositionY_min)/2.0;
    myPositionZ = myUserInfo->TargetCenterPositionZ -30.0*cm;

    myNormMomentumX  = tan(myUserInfo->GetNormMomentumX());
    myNormMomentumY  = tan(myUserInfo->GetNormMomentumY());
    myNormMomentumZ  = sqrt(1.0 - myNormMomentumX * myNormMomentumX - myNormMomentumY * myNormMomentumY);
    
    E_beam = 1.160*GeV;

    myUserInfo->StoreOriginVertexPositionZ(myEvent->GetVertexZ());
    myUserInfo->EvtGenStatus = 0;
  }
  else
  {
    //std::cout << "###### QweakSimPrimaryGeneratorAction::Generate Normal Primaries: " << myEventCounter<< std::endl;
    myPositionX = myUserInfo->GetOriginVertexPositionX();
    myPositionY = myUserInfo->GetOriginVertexPositionY();
    myPositionZ = myUserInfo->GetOriginVertexPositionZ();
    	
    myNormMomentumX  = myUserInfo->GetOriginVertexMomentumDirectionX();
    myNormMomentumY  = myUserInfo->GetOriginVertexMomentumDirectionY();
    myNormMomentumZ  = myUserInfo->GetOriginVertexMomentumDirectionZ();
    
    E_beam = myUserInfo->GetOriginVertexKineticEnergy();
  }


//   //   Relocate the beam gun to the Cerenkov bar to test the light distributions
//   G4double PositionX_min = -100.0*cm;
//   G4double PositionX_max =  100.0*cm;
//   myPositionX =  (G4UniformRand()-0.5)*(PositionX_max-PositionX_min)+(PositionX_max+PositionX_min)/2.0;
// 
//   G4double PositionY_min = (328.-9.0)*cm;
//   G4double PositionY_max = (328.+9.0)*cm;
//   myPositionY =  (G4UniformRand()-0.5)*(PositionY_max-PositionY_min)+(PositionY_max+PositionY_min)/2.0;
// 
//   myPositionZ = 560.0*cm;
// 
//   myNormMomentumX  = 0.0;
//   myNormMomentumY  = 0.0;
//   myNormMomentumZ  = 1.0;
//   //

  particleGun->SetParticlePosition(G4ThreeVector(myPositionX,
						 myPositionY,
						 myPositionZ ));

  particleGun->SetParticleMomentumDirection(G4ThreeVector(myNormMomentumX,
                                                          myNormMomentumY,
                                                          myNormMomentumZ));

  particleGun->SetParticleEnergy(E_beam);

  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);
  myUserInfo->StorePrimaryEventNumber(myEventCounter+1);

//  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
