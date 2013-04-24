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
  SetParticleType("e-");

  SetBeamEnergy();
  
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
  /** \page target_energy_loss target energy loss
   * Pre-scattering (external) target energy loss is simulated by throwing one primary particle
   * starting at 30 cm upstream of the target and letting it propagate to the actual z vertex position
   * in the target.  A second primary particle is then thrown with the angle and transverse position
   * of the first primary at that point.  Event time starts when the first primary is thrown.
   * \todo need to double-check that position and momentum are properly transferred to second primary
   */

  G4int myEventCounter = myUserInfo->GetPrimaryEventNumber();

  if (myEventCounter%1000==0) G4cout << "*=== Event number = " << myEventCounter << " ===*" << G4endl;

  G4double myPositionX, myPositionY, myPositionZ, myVertexZ;
  G4double myNormMomentumX, myNormMomentumY, myNormMomentumZ;
  G4double E_beam;  // Energy of the incoming and outgoing particle

  if (myEventCounter%2 == 0) { // for even myEventCounter
    // select position in x & y randomly
    myPositionX =  myUserInfo->GetBeamPositionX() + (G4UniformRand()-0.5)*(fPositionX_max-fPositionX_min)+(fPositionX_max+fPositionX_min)/2.0;
    myPositionY =  myUserInfo->GetBeamPositionY() + (G4UniformRand()-0.5)*(fPositionY_max-fPositionY_min)+(fPositionY_max+fPositionY_min)/2.0;
    // select the z position 30 cm upstream of the target center (this is basically a constant)
    myPositionZ = myUserInfo->TargetCenterPositionZ -30.0*cm;

    myNormMomentumX  = tan(myUserInfo->GetNormMomentumX()); // = 0
    myNormMomentumY  = tan(myUserInfo->GetNormMomentumY()); // = 0
    myNormMomentumZ  = sqrt(1.0 - myNormMomentumX * myNormMomentumX - myNormMomentumY * myNormMomentumY);  // = 1

    E_beam = fBeamEnergy;

    myUserInfo->StoreOriginVertexPositionZ(myEvent->GetVertexZ());
    myUserInfo->EvtGenStatus = 0; // checked in QweakSimSteppingAction.cc

    if(ELOSS_DEBUG){
      G4cout << "*=== Actual Event number (myEventCounter) = " << myEventCounter << " ===*" << G4endl;
      G4cout << "*=== Nominal Event number (PrimaryEventNumber)= " << myEventCounter+1 << " ===*" << G4endl;
      G4cout << "Position:: " << myPositionX <<"\t" << myPositionY <<"\t" << myPositionZ  << G4endl;
      G4cout << "Momentum:: " << myNormMomentumX <<"\t" << myNormMomentumY <<"\t" << myNormMomentumZ  << G4endl;
      G4cout << "Beam energy:: " << E_beam/GeV << G4endl;
      G4cout << "OriginVerPosZ:: " << myEvent->GetVertexZ() << G4endl;
    }
  }
  else{ // for odd myEventCounter

    myPositionX = myUserInfo->GetOriginVertexPositionX();
    myPositionY = myUserInfo->GetOriginVertexPositionY();
    myPositionZ = myUserInfo->GetOriginVertexPositionZ();

    myNormMomentumX  = myUserInfo->GetOriginVertexMomentumDirectionX();
    myNormMomentumY  = myUserInfo->GetOriginVertexMomentumDirectionY();
    myNormMomentumZ  = myUserInfo->GetOriginVertexMomentumDirectionZ();

    E_beam = myUserInfo->GetOriginVertexKineticEnergy();

    if(ELOSS_DEBUG){
      G4cout << "*=== Actual Event number (myEventCounter) = " << myEventCounter << " ===*" << G4endl;
      G4cout << "*=== Nominal Event number (PrimaryEventNumber)= " << myEventCounter+1 << " ===*" << G4endl;
      G4cout << "Position:: " << myPositionX <<"\t" << myPositionY <<"\t" << myPositionZ  << G4endl;
      G4cout << "Momentum:: " << myNormMomentumX <<"\t" << myNormMomentumY <<"\t" << myNormMomentumZ  << G4endl;
      G4cout << "Beam energy:: " << E_beam/GeV << G4endl;
      G4cout << "OriginVerPosZ:: " << myEvent->GetVertexZ() << G4endl;
    }

    if (myEvent->GetReactionType() == 7) {
      myVertexZ = myPositionZ;
      myPositionZ = myUserInfo->TargetCenterPositionZ + 0.5*myUserInfo->TargetLength 
	+ myUserInfo->TargetExitWindowThickness + 1.0*cm;
      
      // Project x & y positions from vertex to 1 cm downstream of the target exit window
      myPositionX += (myPositionZ-myVertexZ)*myNormMomentumX/myNormMomentumZ;
      myPositionY += (myPositionZ-myVertexZ)*myNormMomentumY/myNormMomentumZ;
    }
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
  particleGun->GeneratePrimaryVertex(anEvent);  // takes an event, generates primary vertex, and associates primary particles with the vertex
  myUserInfo->StorePrimaryEventNumber(myEventCounter+1);
  myUserInfo->StoreBeamEnergy(fBeamEnergy); 

  // rest of userInfo filled in QweakSimSteppingAction.cc

//  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void QweakSimPrimaryGeneratorAction::SetBeamEnergy(G4double energy) {
    if (energy>0) { 
      fBeamEnergy = energy; 
      myUserInfo->StoreBeamEnergy(energy); 
    }
    else {
      G4cout << G4endl << "##### Beam Energy must be greater than zero" << G4endl << G4endl;
    }
}
