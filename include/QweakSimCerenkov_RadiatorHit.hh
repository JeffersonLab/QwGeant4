/**
   \class QweakSimCerenkov_RadiatorHit
    
   \brief Handling of a hit in the Cerenkov radiator

 */

#ifndef QweakSimCerenkov_RadiatorHit_h
#define QweakSimCerenkov_RadiatorHit_h 

// user includes
#include "QweakSimHit.hh"

class QweakSimCerenkov_RadiatorHit : public G4VHit
{
  public:

      QweakSimCerenkov_RadiatorHit();
      QweakSimCerenkov_RadiatorHit(G4int detector_id);
      virtual ~QweakSimCerenkov_RadiatorHit();
      QweakSimCerenkov_RadiatorHit(const QweakSimCerenkov_RadiatorHit &right);
      const QweakSimCerenkov_RadiatorHit& operator=(const QweakSimCerenkov_RadiatorHit &right);
      int operator==(const QweakSimCerenkov_RadiatorHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      inline float x();
      inline float y();

      virtual void Draw();
      virtual void Print();
  
private:

  G4int    DetectorID;  // octant number
  G4double time;

  G4int TrackID;
  G4int ParentID;
  G4String CreatorProcessName;

  G4ThreeVector localPos;
  G4ThreeVector worldPos;

  G4ThreeVector localMomentum;
  G4ThreeVector worldMomentum;

  G4ThreeVector    cellPos;
  G4RotationMatrix cellRot;
  const G4LogicalVolume* pLogV;

  G4ThreeVector originVertexPosition;        
  G4ThreeVector originVertexMomentumDirection;
  G4double      originVertexKineticEnergy;
  G4double      originVertexTotalEnergy;

  G4ThreeVector currentMomentumDirection;
  G4double      currentKineticEnergy;
  G4double      currentTotalEnergy;
  G4ThreeVector currentPolarization;

  G4double      primaryQ2;
  G4double      crossSection;
  G4double      crossSectionWeight;

  G4String      particleName;
  G4int         particleType;

public:
  
  inline void   StoreTrackID(G4int tid)    { TrackID = tid; }
  inline G4int GetTrackID() const { return TrackID; }

  inline void   StoreParentID(G4int tid)    { ParentID = tid; }
  inline G4int GetParentID() const { return ParentID; }
  
  inline void   StoreCreatorProcessName(G4String name)    { CreatorProcessName = name; }
  inline G4String GetCreatorProcessName() const { return CreatorProcessName; }

  inline void  StoreDetectorID(G4int detector_ID)  { DetectorID = detector_ID; }
  inline G4int   GetDetectorID() const { return DetectorID; }

  inline void   StoreGlobalTime(G4double t)    { time = t; }
  inline G4double GetGlobalTime() const { return time; }
  //------
  inline void        StoreLocalPosition(G4ThreeVector xyz) { localPos = xyz; }
  inline G4ThreeVector GetLocalPosition()     const { return localPos; }
  
  inline void        StoreWorldPosition(G4ThreeVector xyz) { worldPos = xyz; }
  inline G4ThreeVector GetWorldPosition()     const { return worldPos; }
  //------
  inline void          StoreLocalMomentum(G4ThreeVector lpxyz) { localMomentum = lpxyz; }
  inline G4ThreeVector   GetLocalMomentum()      const {  return localMomentum; }
  
  inline void          StoreWorldMomentum(G4ThreeVector gpxyz) { worldMomentum = gpxyz; }
  inline G4ThreeVector   GetWorldMomentum()       const { return worldMomentum; }

  //------
  inline void        StoreCellPosition(G4ThreeVector xyz) { cellPos = xyz; }
  inline G4ThreeVector GetCellPosition()     const { return cellPos; }
  
  inline void           StoreCellRotation(G4RotationMatrix rmat) { cellRot = rmat; }
  inline G4RotationMatrix GetCellRotation()         const { return cellRot; }
  
  inline void                 StoreLogVolume(G4LogicalVolume* val) { pLogV = val; }
  inline const G4LogicalVolume* GetLogVolume()        const { return pLogV; }
  //------
  inline void        StoreOriginVertexPosition(G4ThreeVector oxyz) { originVertexPosition  = oxyz; }
  inline G4ThreeVector GetOriginVertexPosition()     const { return  originVertexPosition; }
  
  inline void        StoreOriginVertexMomentumDirection(G4ThreeVector opxyz) { originVertexMomentumDirection  = opxyz; }
  inline G4ThreeVector GetOriginVertexMomentumDirection()      const { return  originVertexMomentumDirection; }

  inline void   StoreOriginVertexKineticEnergy(G4double oekin) { originVertexKineticEnergy  = oekin; }
  inline G4double GetOriginVertexKineticEnergy() const {  return originVertexKineticEnergy; }

  inline void   StoreOriginVertexTotalEnergy(G4double oetot) { originVertexTotalEnergy  = oetot; }
  inline G4double GetOriginVertexTotalEnergy() const {  return originVertexTotalEnergy; }

  //------

  inline void        StoreMomentumDirection(G4ThreeVector pxyz) { currentMomentumDirection  = pxyz; }
  inline G4ThreeVector GetMomentumDirection()      const { return currentMomentumDirection; }

  inline void   StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
  inline G4double GetKineticEnergy() const { return currentKineticEnergy; }

  inline void   StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
  inline G4double GetTotalEnergy() const { return currentTotalEnergy; }

  //------
 
  inline void   StorePolarization(G4ThreeVector p) { currentPolarization  = p; }
  inline G4ThreeVector GetPolarization() const { return currentPolarization; }

  //------

  inline void     StorePrimaryQ2(G4double q2)   { primaryQ2 = q2; }
  inline G4double   GetPrimaryQ2() const { return primaryQ2; }

  inline void     StoreCrossSection(G4double cs)  {crossSection = cs;}
  inline G4double   GetCrossSection() const {return crossSection;}

  inline void     StoreCrossSectionWeight(G4double csw)  {crossSectionWeight = csw;}
  inline G4double   GetCrossSectionWeight() const {return crossSectionWeight;}

  //------

  inline void     StoreParticleName(G4String pn)   {particleName = pn;}
  inline G4String   GetParticleName() const {return particleName;}

  inline void     StoreParticleType(G4int pt)   {particleType = pt;}
  inline G4int   GetParticleType() const {return particleType;}

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<QweakSimCerenkov_RadiatorHit> QweakSimCerenkovRadiatorHitsCollection;

extern G4Allocator<QweakSimCerenkov_RadiatorHit>  QweakSimCerenkovRadiatorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimCerenkov_RadiatorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) QweakSimCerenkovRadiatorHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimCerenkov_RadiatorHit::operator delete(void* aHit)
{
   QweakSimCerenkovRadiatorHitAllocator.FreeSingle((QweakSimCerenkov_RadiatorHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
