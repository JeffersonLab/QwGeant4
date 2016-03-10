#include "QweakSimCerenkov_PMTHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Allocator<QweakSimCerenkov_PMTHit> QweakSimCerenkov_PMTHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_PMTHit::QweakSimCerenkov_PMTHit()
{
  DetectorID          = -1;
  PMTID               = -1;
  currentPhotonEnergy = 0.;
  currentHitTime = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_PMTHit::QweakSimCerenkov_PMTHit(G4int pmt_id)
{
  PMTID  = pmt_id;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_PMTHit::~QweakSimCerenkov_PMTHit()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkov_PMTHit::QweakSimCerenkov_PMTHit(const QweakSimCerenkov_PMTHit &right)
: G4VHit()
{
  DetectorID          = right.DetectorID;
  PMTID               = right.PMTID;
  currentPhotonEnergy = right.currentPhotonEnergy;
  currentHitTime      = right.currentHitTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const QweakSimCerenkov_PMTHit& QweakSimCerenkov_PMTHit::operator=(const QweakSimCerenkov_PMTHit &right)
{
  DetectorID          = right.DetectorID;
  PMTID               = right.PMTID;
  currentPhotonEnergy = right.currentPhotonEnergy;
  currentHitTime      = right.currentHitTime;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int QweakSimCerenkov_PMTHit::operator==(const QweakSimCerenkov_PMTHit & ) const
{
  return 0;
}
