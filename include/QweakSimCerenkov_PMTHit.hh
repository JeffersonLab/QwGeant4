#ifndef QweakSimCerenkov_PMTHit_h
#define QweakSimCerenkov_PMTHit_h 

// user includes
#include "QweakSimHit.hh"

class QweakSimCerenkov_PMTHit : public G4VHit
{
public:
  
  QweakSimCerenkov_PMTHit();
  virtual ~QweakSimCerenkov_PMTHit();
  
  QweakSimCerenkov_PMTHit(const QweakSimCerenkov_PMTHit &right);
  QweakSimCerenkov_PMTHit(G4int pmt_id);
  const QweakSimCerenkov_PMTHit & operator=(const QweakSimCerenkov_PMTHit &right);
  int operator==(const QweakSimCerenkov_PMTHit &right) const;
  
  inline void *operator new(size_t);
  inline void operator delete(void *aHit);
  
  inline float x();
  inline float y();
  
private:

  G4int    DetectorID;  // octant number
  G4int    PMTID;
  G4int    hitID;
  G4bool   hitValid;
  G4double currentPhotonEnergy;
  G4double currentHitTime;
  
  public:

  inline void  StoreDetectorID(G4int detector_ID)  { DetectorID = detector_ID; }
  inline G4int   GetDetectorID() const { return DetectorID; }

  inline void StorePMTID(G4int pmt_id) { PMTID = pmt_id; }
  inline G4int GetPMTID() const { return PMTID; }

  inline void StoreHitID(G4int hit_id) { hitID = hit_id; }
  inline G4int GetHitID() const { return hitID; }

  inline void SetHitValid(G4bool valid) { hitValid = valid; }
  inline G4bool IsHitValid() const { return hitValid; }

  inline void   StorePhotonEnergy(G4double eng) { currentPhotonEnergy  = eng; }
  inline G4double GetPhotonEnergy() const { return currentPhotonEnergy; }

  inline void StoreHitTime(G4double time) { currentHitTime = time; }
  inline G4double GetHitTime() const { return currentHitTime; }

 };

typedef G4THitsCollection<QweakSimCerenkov_PMTHit> QweakSimCerenkovDetector_PMTHitsCollection;

extern G4Allocator<QweakSimCerenkov_PMTHit>  QweakSimCerenkov_PMTHitAllocator;

inline void* QweakSimCerenkov_PMTHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) QweakSimCerenkov_PMTHitAllocator.MallocSingle();
  return aHit;
}

inline void QweakSimCerenkov_PMTHit::operator delete(void* aHit)
{
   QweakSimCerenkov_PMTHitAllocator.FreeSingle((QweakSimCerenkov_PMTHit*) aHit);
}

#endif
