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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4int QweakSimPrimaryGeneratorAction::kActiveOctantNumber = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI)
//  : myUserInfo(myUI)
QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( )
{

  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;

  // default octant [1,,8]
  kActiveOctantNumber = 1;

  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentumX  = 0.0;
  myNormMomentumY  = 0.0;
  myNormMomentumZ  = 0.0;
 
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
  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

//jpan@nuclear.uwinnipeg.ca
//  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  particleGun->SetParticleDefinition(particle);

  G4double PositionX_min = -2.0*mm;
  G4double PositionX_max =  2.0*mm;
  myPositionX =  (G4UniformRand()-0.5)*(PositionX_max-PositionX_min);

  G4double PositionY_min = -2.0*mm;
  G4double PositionY_max =  2.0*mm;
  myPositionY =  (G4UniformRand()-0.5)*(PositionY_max-PositionY_min);

  myPositionZ = -700.0*cm;

  particleGun->SetParticlePosition(G4ThreeVector(myPositionX,
						 myPositionY,
						 myPositionZ ));

  myNormMomentumX  = 0.0;
  myNormMomentumY  = 0.0;
  myNormMomentumZ  = 1.0;
  myNormMomentum = G4ThreeVector(myNormMomentumX, myNormMomentumY, myNormMomentumZ);
  particleGun->SetParticleMomentumDirection(myNormMomentum); 

  particleGun->SetParticleEnergy(1.165*GeV);

  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::GeneratePrimaries, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);

  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


