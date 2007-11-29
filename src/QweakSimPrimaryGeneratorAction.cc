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

  // Neven's ntuple with errors due to internal bremsstrahlung,
  // errors: some events with wrong energy and momenta (e.g. 50GeV) 
  // TString myfile = TString("ep_m0_neven_larget_r5.root"); 

  // Juliette Mammei gave me a correct PAW Ntuple, so here is the h2root converted root file 
  //TString myfile = TString("minitorus.root");

//  TString myfile = TString("ep_elastic.root");
//   myNtuple = new QweakSimG3NtupleReader(myfile);

  TString myfile = TString("ep_event.root");
  myNtuple = new QweakSimInputRootFile_EventReader(myfile);

  //myNtuple->SetDebugLevel(20);
  //myNtuple->LoopEvents(0,10);


  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction()
{

  G4cout << "###### Calling/Leaving QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction " << G4endl;

  if (particleGun) delete particleGun;
  //if (myNtuple)    delete myNtuple;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
   G4cout << "###### Calling QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;



  G4cout << "************************************************ myEventCounter = " << myEventCounter << G4endl;


  // Two ways to retreve primary events:
  // choosing randomly a primary event in the root file:
  //myNtuple->GetRandomEvent(&myPE);

  // or loading it inthe order saved in the root file:
  myNtuple->GetPrimaryEvent( (int) myEventCounter, &myPE);

//   G4cout << "myPE.ParticleID            = " << myPE.ParticleID     << G4endl;
//   G4cout << "myPE.Vertex[0]     [cm]    = " << myPE.Vertex[0]      << G4endl;
//   G4cout << "myPE.Vertex[1]     [cm]    = " << myPE.Vertex[1]      << G4endl;
//   G4cout << "myPE.Vertex[2]     [cm]    = " << myPE.Vertex[2]      << G4endl;
//   G4cout << "myPE.Momentum[0]   [MeV]   = " << myPE.Momentum[0]    << G4endl;
//   G4cout << "myPE.Momentum[1]   [MeV]   = " << myPE.Momentum[1]    << G4endl;
//   G4cout << "myPE.Momentum[2]   [Mev]   = " << myPE.Momentum[2]    << G4endl;
//   G4cout << "myPE.Phi           [deg]   = " << myPE.Phi            << G4endl;
//   G4cout << "myPE.Theta         [deg]   = " << myPE.Theta          << G4endl;
//   G4cout << "myPE.KineticEnergy [MeV]   = " << myPE.KineticEnergy  << G4endl;
//   G4cout << "myPE.TotalEnergy   [MeV]   = " << myPE.TotalEnergy    << G4endl;
//   G4cout << "myPE.Q2            [GeV^2] = " << myPE.Q2             << G4endl;
//  G4cout << "myPE.Weight                = " << myPE.Weight         << G4endl;

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  // Translation of the Geant3 PDG code into the GEANT4 PDG code
  if(myPE.ParticleID==1)
    {
      G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
      particleGun->SetParticleDefinition(particle);
    }

  if(myPE.ParticleID==2)
    {
      G4ParticleDefinition* particle = particleTable->FindParticle("e+");
      particleGun->SetParticleDefinition(particle);
    }

  if(myPE.ParticleID==3)
    {
      G4ParticleDefinition* particle = particleTable->FindParticle("e-");
      //G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
      particleGun->SetParticleDefinition(particle);
    }

  if(myPE.ParticleID==14)
    {
      G4ParticleDefinition* particle = particleTable->FindParticle("proton");
      particleGun->SetParticleDefinition(particle);
    }

  G4double myEnergy = myPE.KineticEnergy *MeV;
  particleGun->SetParticleEnergy(myEnergy);

  myPositionX =  myPE.Vertex[0]*cm;
  myPositionY =  myPE.Vertex[1]*cm;
  myPositionZ =  myPE.Vertex[2]*cm;

  particleGun->SetParticlePosition(G4ThreeVector( myPositionX,
						  myPositionY,
						  myPositionZ ));

				   
//   G4double meanThetaAngle = 11.0*degree;
//   G4double sigmaThetaAngle = 4.0*degree;
//   G4double ThetaAngle =  (meanThetaAngle + ((G4UniformRand()-0.5)*2.0*sigmaThetaAngle));
  
//   G4double meanPhiAngle = 0.0*degree;
//   G4double sigmaPhiAngle = 8.0*degree;
//   G4double PhiAngle =  (meanPhiAngle + ((G4UniformRand()-0.5)*2.0*sigmaPhiAngle));

//   G4cout << "=====================> Theta Angle = " << ThetaAngle/degree << " degree" << G4endl;
//   G4cout << "=====================> Phi   Angle = " << PhiAngle/degree   << " degree" << G4endl;
  
//   particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(ThetaAngle)*sin(PhiAngle),
// 							  sin(ThetaAngle)*cos(PhiAngle),
// 							  cos(ThetaAngle) )); 

 
  myNormMomentumX =  myPE.Momentum[0]/myPE.KineticEnergy;
  myNormMomentumY =  myPE.Momentum[1]/myPE.KineticEnergy;
  myNormMomentumZ =  myPE.Momentum[2]/myPE.KineticEnergy;

  myNormMomentum = G4ThreeVector(myNormMomentumX,myNormMomentumY,myNormMomentumZ);


  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::GeneratePrimaries, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

  particleGun->SetParticleMomentumDirection(G4ThreeVector(myNormMomentum));
  
  
  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);


  // fill user track info: store Q2 value of this primary 
  myUserInfo->SetPrimaryQ2( (G4double) myPE.Q2);

  // fill user track info: store cross section weight (micro barn) of this primary 
  myUserInfo->SetCrossSectionWeight( (G4double) myPE.Weight);

  // fill user track info: store primary event number 
  myUserInfo->SetPrimaryEventNumber( (G4int) myEventCounter );
  
  // print the stored values
  myUserInfo->Print();
  
  // increase my own event counter for next primary
  myEventCounter += 1;


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
