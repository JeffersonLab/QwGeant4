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

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:35:07 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4int QweakSimPrimaryGeneratorAction::kActiveOctantNumber = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI)
  : myUserInfo(myUI)
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
  myEventCounter = 0;

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

  G4double PositionX_min = -1.0*mm;
  G4double PositionX_max =  1.0*mm;
  myPositionX =  (G4UniformRand()-0.5)*(PositionX_max-PositionX_min);

  G4double PositionY_min = -1.0*mm;
  G4double PositionY_max =  1.0*mm;
  myPositionY =  (G4UniformRand()-0.5)*(PositionY_max-PositionY_min);

  myPositionZ = -700.0*cm;

  particleGun->SetParticlePosition(G4ThreeVector(myPositionX,
						 myPositionY,
						 myPositionZ ));

  particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1)); 

  particleGun->SetParticleEnergy(1.165*GeV);

  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::GeneratePrimaries, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);

  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPrimaryGeneratorAction.cc,v $
//      Revision 1.4  2006/05/05 21:35:07  grimm
//      Added the rotation of the generated tracks into any chosen octant.
//
//      Revision 1.3  2006/01/31 20:15:19  grimm
//      Implemented the usage of the ROOT input event file generated by Michael's Eventgenerator. This will replace the usage of the Root input event file based on the Geant3 output ntuple.
//
//      Revision 1.2  2005/12/27 19:14:12  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
