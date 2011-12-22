#include "QweakSimUserInformation.hh"

QweakSimUserInformation::QweakSimUserInformation()
{
  cerenkovSecondaryParticleCount = 0;
  Initialize();
}

QweakSimUserInformation::~QweakSimUserInformation()
{
}

void QweakSimUserInformation::Print() const
{
}

void QweakSimUserInformation::Initialize()
{

  TargetCenterPositionZ = -650*cm;
  PrimaryEventNumber = 0;
  ReactionType = 0;         // assign a number to which kind of reaction,e.g. 1 = elastic ep,
  PDGcode = 0;              // particle data code/number for the primary particle, e.g. 3=electron
  TrackID = 0;
  GlobalTime = 0.0;
  PrimaryQ2 = 0.0;
  CrossSection = 0.0;
  CrossSectionWeight = 0.0;
  Asymmetry = 0.0;
  OriginVertexPositionX = 0.0;
  OriginVertexPositionY = 0.0;
  OriginVertexPositionZ = 0.0;
  OriginVertexThetaAngle = 0.0;
  OriginVertexPhiAngle = 0.0;
  OriginVertexMomentumDirectionX = 0.0;
  OriginVertexMomentumDirectionY = 0.0;
  OriginVertexMomentumDirectionZ = 0.0;
  OriginVertexKineticEnergy = 0.0;
  OriginVertexTotalEnergy = 0.0;

  CerEngDep                      = 0.0;
  
  leftPMTHitValid                = 0;
  rightPMTHitValid               = 0;
  StoreStepVolumeName("none");
  SetEdgeEventDetected(0);

  if(cerenkovSecondaryParticleCount){
    delete[] cerenkovSecondaryPartOrig;
    delete[] cerenkovSecondaryPartMom;
    delete[] cerenkovSecondaryPartEng;
    delete[] cerenkovSecondaryPartCharge;
  }
  cerenkovSecondaryParticleCount = 0;
  cerenkovSecondaryElectronCount = 0;
  cerenkovSecondaryPhotonCount = 0;

  cerenkovOpticalPhotonCount = 0;
  CerenkovPhotonEnergy.clear();
  CerenkovPhotonEnergy.resize(0);

  cerenkovSecondaryPositronCount = 0;
  cerenkovSecondaryPartOrig      = NULL;
  cerenkovSecondaryPartMom      = NULL;
  cerenkovSecondaryPartEng      = NULL;
  cerenkovSecondaryPartCharge      = NULL;

  G4ThreeVector tmp(1000,1000,1000);
  cerenkovEventExitPos = tmp;
  
  G4double D753WKBS20_QE[65][2] = {
    {200.0*nanometer, 0.68},
    {210.0*nanometer, 3.55},
    {220.0*nanometer, 7.40},
    {230.0*nanometer, 10.4},
    {240.0*nanometer, 14.6},
    {250.0*nanometer, 17.8},
    {260.0*nanometer, 20.6},
    {270.0*nanometer, 22.6},
    {280.0*nanometer, 22.4},
    {290.0*nanometer, 21.8},
    {300.0*nanometer, 21.1},
    {310.0*nanometer, 20.5},
    {320.0*nanometer, 19.7},
    {330.0*nanometer, 19.2},
    {340.0*nanometer, 18.4},
    {350.0*nanometer, 18.0},
    {360.0*nanometer, 18.2},
    {370.0*nanometer, 18.8},
    {380.0*nanometer, 18.3},
    {390.0*nanometer, 17.6},
    {400.0*nanometer, 17.7},
    {410.0*nanometer, 17.6},
    {420.0*nanometer, 17.5},
    {430.0*nanometer, 17.1},
    {440.0*nanometer, 16.7},
    {450.0*nanometer, 15.8},
    {460.0*nanometer, 15.0},
    {470.0*nanometer, 14.4},
    {480.0*nanometer, 13.7},
    {490.0*nanometer, 13.1},
    {500.0*nanometer, 12.4},
    {510.0*nanometer, 11.7},
    {520.0*nanometer, 11.0},
    {530.0*nanometer, 10.4},
    {540.0*nanometer, 9.77},
    {550.0*nanometer, 9.15},
    {560.0*nanometer, 8.53},
    {570.0*nanometer, 7.95},
    {580.0*nanometer, 7.39},
    {590.0*nanometer, 6.87},
    {600.0*nanometer, 6.38},
    {610.0*nanometer, 5.90},
    {620.0*nanometer, 5.45},
    {630.0*nanometer, 5.07},
    {640.0*nanometer, 4.71},
    {650.0*nanometer, 4.39},
    {660.0*nanometer, 4.10},
    {670.0*nanometer, 3.79},
    {680.0*nanometer, 3.51},
    {690.0*nanometer, 3.25},
    {700.0*nanometer, 2.98},
    {710.0*nanometer, 2.68},
    {720.0*nanometer, 2.40},
    {730.0*nanometer, 2.13},
    {740.0*nanometer, 1.88},
    {750.0*nanometer, 1.65},
    {760.0*nanometer, 1.47},
    {770.0*nanometer, 1.30},
    {780.0*nanometer, 1.13},
    {790.0*nanometer, 0.96},
    {800.0*nanometer, 0.80},
    {810.0*nanometer, 0.65},
    {820.0*nanometer, 0.48},
    {830.0*nanometer, 0.33},
    {840.0*nanometer, 0.18}
  };

// if quantum efficiency is processed in the Cerenkov detector class,
// set it to 100% here
//   G4double D753WKBS20_QE[65][2] = {
//     {200.0*nanometer, 100},
//     {210.0*nanometer, 100},
//     {220.0*nanometer, 100},
//     {230.0*nanometer, 100},
//     {240.0*nanometer, 100},
//     {250.0*nanometer, 100},
//     {260.0*nanometer, 100},
//     {270.0*nanometer, 100},
//     {280.0*nanometer, 100},
//     {290.0*nanometer, 100},
//     {300.0*nanometer, 100},
//     {310.0*nanometer, 100},
//     {320.0*nanometer, 100},
//     {330.0*nanometer, 100},
//     {340.0*nanometer, 100},
//     {350.0*nanometer, 100},
//     {360.0*nanometer, 100},
//     {370.0*nanometer, 100},
//     {380.0*nanometer, 100},
//     {390.0*nanometer, 100},
//     {400.0*nanometer, 100},
//     {410.0*nanometer, 100},
//     {420.0*nanometer, 100},
//     {430.0*nanometer, 100},
//     {440.0*nanometer, 100},
//     {450.0*nanometer, 100},
//     {460.0*nanometer, 100},
//     {470.0*nanometer, 100},
//     {480.0*nanometer, 100},
//     {490.0*nanometer, 100},
//     {500.0*nanometer, 100},
//     {510.0*nanometer, 100},
//     {520.0*nanometer, 100},
//     {530.0*nanometer, 100},
//     {540.0*nanometer, 100},
//     {550.0*nanometer, 100},
//     {560.0*nanometer, 100},
//     {570.0*nanometer, 100},
//     {580.0*nanometer, 100},
//     {590.0*nanometer, 100},
//     {600.0*nanometer, 100},
//     {610.0*nanometer, 100},
//     {620.0*nanometer, 100},
//     {630.0*nanometer, 100},
//     {640.0*nanometer, 100},
//     {650.0*nanometer, 100},
//     {660.0*nanometer, 100},
//     {670.0*nanometer, 100},
//     {680.0*nanometer, 100},
//     {690.0*nanometer, 100},
//     {700.0*nanometer, 100},
//     {710.0*nanometer, 100},
//     {720.0*nanometer, 100},
//     {730.0*nanometer, 100},
//     {740.0*nanometer, 100},
//     {750.0*nanometer, 100},
//     {760.0*nanometer, 100},
//     {770.0*nanometer, 100},
//     {780.0*nanometer, 100},
//     {790.0*nanometer, 100},
//     {800.0*nanometer, 100},
//     {810.0*nanometer, 100},
//     {820.0*nanometer, 100},
//     {830.0*nanometer, 100},
//     {840.0*nanometer, 100}
//   };


  G4double XP4572_QE[15][2] = {
    {200.0*nanometer ,  0.0} ,
    {250.0*nanometer ,  0.0} ,
    {280.0*nanometer ,  0.1} ,
    {290.0*nanometer ,  0.3} ,
    {300.0*nanometer ,  3.0} ,
    {315.0*nanometer , 10.0} ,
    {330.0*nanometer , 20.0} ,
    {350.0*nanometer , 27.5} ,
    {400.0*nanometer , 26.0} ,
    {480.0*nanometer , 20.0} ,
    {540.0*nanometer , 10.0} ,
    {590.0*nanometer ,  3.0} ,
    {615.0*nanometer ,  1.0} ,
    {640.0*nanometer ,  0.3} ,
    {660.0*nanometer ,  0.1}
  };

  PMTQE_XP4572      = new G4MaterialPropertyVector();
  PMTQED753WKBS20   = new G4MaterialPropertyVector();
  G4double E_value;

  for (G4int kk=0; kk<65 ; kk++) 
    {    
      if(kk < 15 ){
	E_value= 2*pi*hbarc/( XP4572_QE[kk][0] *nanometer);
	G4cout << "E_value " << kk << " = " << E_value << " QE = " << XP4572_QE[kk][1] << G4endl;
	PMTQE_XP4572->AddElement(E_value, XP4572_QE[kk][1]/100.);
      }
      
      E_value= 2*pi*hbarc/( D753WKBS20_QE[kk][0] *nanometer);
      PMTQED753WKBS20->AddElement(E_value, D753WKBS20_QE[kk][1]/100.);
    }
}

G4double QweakSimUserInformation::GetNumberOfPhotoelectrons(G4double eng)
{
  return PMTQE_XP4572->GetProperty(eng);
}

G4double QweakSimUserInformation::GetNumberOfPhotoelectronsS20(G4double eng)
{
  return PMTQED753WKBS20->GetProperty(eng);  
}

void QweakSimUserInformation::StoreCerenkovSecondaryParticleInfo(G4ThreeVector ev,
								 G4ThreeVector em,
								 G4double eng,
								 G4double charge) 
{
  G4int cnt = cerenkovSecondaryParticleCount;
  G4ThreeVector *tmp1 = NULL;
  G4ThreeVector *tmp2 = NULL;
  G4double      *tmp3 = NULL;
  G4double      *tmp4 = NULL;
 
  if(cnt){
    tmp1 = new G4ThreeVector[cnt];
    tmp2 = new G4ThreeVector[cnt];
    tmp3 = new G4double[cnt];
    tmp4 = new G4double[cnt];
  }

  for(G4int i = 0; i < cnt; i++){
    tmp1[i] = cerenkovSecondaryPartOrig[i];
    tmp2[i] = cerenkovSecondaryPartMom[i];
    tmp3[i] = cerenkovSecondaryPartEng[i];
    tmp4[i] = cerenkovSecondaryPartCharge[i];
  }

  if(cnt && cerenkovSecondaryPartOrig) delete[] cerenkovSecondaryPartOrig;
  if(cnt && cerenkovSecondaryPartMom) delete[] cerenkovSecondaryPartMom;
  if(cnt && cerenkovSecondaryPartEng) delete[] cerenkovSecondaryPartEng;
  if(cnt && cerenkovSecondaryPartCharge) delete[] cerenkovSecondaryPartCharge;

  cerenkovSecondaryPartOrig = new G4ThreeVector[cnt+1];
  cerenkovSecondaryPartMom = new G4ThreeVector[cnt+1];
  cerenkovSecondaryPartEng = new G4double[cnt+1];
  cerenkovSecondaryPartCharge = new G4double[cnt+1];

  for(G4int i = 0; i < cnt; i++) {
    cerenkovSecondaryPartOrig[i] = tmp1[i];
    cerenkovSecondaryPartMom[i] = tmp2[i];
    cerenkovSecondaryPartEng[i] = tmp3[i];
    cerenkovSecondaryPartCharge[i] = tmp4[i];
  }

  cerenkovSecondaryPartOrig[cnt] = ev;
  cerenkovSecondaryPartMom[cnt] = em;
  cerenkovSecondaryPartEng[cnt] = eng;
  cerenkovSecondaryPartCharge[cnt] = charge;

  if(cnt){
    delete[] tmp1;
    delete[] tmp2;
    delete[] tmp3;
    delete[] tmp4;
  }

  if(charge == -1)   cerenkovSecondaryElectronCount++;  
  if(charge == 0)   cerenkovSecondaryPhotonCount++;  
  if(charge == 1)   cerenkovSecondaryPositronCount++;  
  cerenkovSecondaryParticleCount++;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4ThreeVector QweakSimUserInformation::GetCerenkovSecondaryParticleOrigin(G4int idx) 
{
  G4ThreeVector tmp(1000,1000,1000);
  if(!cerenkovSecondaryParticleCount) return tmp;
  if(idx < 0 || idx >= cerenkovSecondaryParticleCount) return tmp;
  return cerenkovSecondaryPartOrig[idx];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4ThreeVector QweakSimUserInformation::GetCerenkovSecondaryParticleMomentum(G4int idx) 
{
  G4ThreeVector tmp(1000,1000,1000);
  if(!cerenkovSecondaryParticleCount) return tmp;
  if(idx < 0 || idx >= cerenkovSecondaryParticleCount) return tmp;
  return cerenkovSecondaryPartMom[idx];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4double QweakSimUserInformation::GetCerenkovSecondaryParticleEnergy(G4int idx) 
{
  if(!cerenkovSecondaryParticleCount) return 0;
  if(idx < 0 || idx >= cerenkovSecondaryParticleCount) return 0;
  return cerenkovSecondaryPartEng[idx];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4double QweakSimUserInformation::GetCerenkovSecondaryParticleCharge(G4int idx) 
{
  if(!cerenkovSecondaryParticleCount) return 0;
  if(idx < 0 || idx >= cerenkovSecondaryParticleCount) return 0;
  return cerenkovSecondaryPartCharge[idx];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserInformation::ResetCerenkovSecondaryParticleInfo()
{
  if(cerenkovSecondaryParticleCount){
    delete[] cerenkovSecondaryPartOrig;
    delete[] cerenkovSecondaryPartMom;
    delete[] cerenkovSecondaryPartEng;
    delete[] cerenkovSecondaryPartCharge;
  }
  cerenkovOpticalPhotonCount = 0;
  CerenkovPhotonEnergy.clear();
  CerenkovPhotonEnergy.resize(0);

  cerenkovSecondaryParticleCount = 0;
  cerenkovSecondaryElectronCount = 0;
  cerenkovSecondaryPhotonCount = 0;
  cerenkovSecondaryPositronCount = 0;
  cerenkovSecondaryPartOrig      = NULL;
  cerenkovSecondaryPartMom      = NULL;
  cerenkovSecondaryPartEng      = NULL;  
  cerenkovSecondaryPartCharge   = NULL;  
}
