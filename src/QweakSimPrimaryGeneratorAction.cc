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
//QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI)
//  : myUserInfo(myUI)
QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( )
{

  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;

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
//  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

//jpan@nuclear.uwinnipeg.ca
//
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  particleGun->SetParticleDefinition(particle);

  G4double PositionX_min = -2.0*mm;
  G4double PositionX_max =  2.0*mm;
  myPositionX =  (G4UniformRand()-0.5)*(PositionX_max-PositionX_min)+(PositionX_max+PositionX_min)/2.0;

  G4double PositionY_min = -2.0*mm;
  G4double PositionY_max =  2.0*mm;
  myPositionY =  (G4UniformRand()-0.5)*(PositionY_max-PositionY_min)+(PositionX_max+PositionX_min)/2.0;

  myPositionZ = -700.0*cm;

  myNormMomentumX  = 0.0;
  myNormMomentumY  = 0.0;
  myNormMomentumZ  = 1.0;


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

  myNormMomentum = G4ThreeVector(myNormMomentumX, myNormMomentumY, myNormMomentumZ);
  particleGun->SetParticleMomentumDirection(myNormMomentum); 

  particleGun->SetParticleEnergy(1.165*GeV);

  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);

//  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


