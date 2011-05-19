//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_WirePlaneHit.hh

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:40:49 $

   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimVDC_WirePlaneHit
    
   \brief Handling of a U-WirePlane and/or V-WirePlane Hit of the VDC.

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_WirePlaneHit_h
#define QweakSimVDC_WirePlaneHit_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimVDC_WirePlaneHit : public G4VHit
{
  public:

      QweakSimVDC_WirePlaneHit();
      QweakSimVDC_WirePlaneHit(G4int vdc_id, G4int wireplane_ID);
      virtual ~QweakSimVDC_WirePlaneHit();
      QweakSimVDC_WirePlaneHit(const QweakSimVDC_WirePlaneHit &right);
      const QweakSimVDC_WirePlaneHit& operator=(const QweakSimVDC_WirePlaneHit &right);
      int operator==(const QweakSimVDC_WirePlaneHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

	  inline float x();
	  inline float y();

      virtual void Draw();
      virtual void Print();

private:
  
  G4int         vdcID;
  G4int         wireplaneID;
  G4double      time;

  G4ThreeVector localPos;
  G4ThreeVector worldPos;

  G4ThreeVector localMomentum;
  G4ThreeVector worldMomentum;
  
  G4ThreeVector originVertexPosition;
  G4ThreeVector originVertexMomentumDirection;
  G4double      originVertexKineticEnergy;
  G4double      originVertexTotalEnergy;

  G4double      currentKineticEnergy;
  G4double      currentTotalEnergy;

  G4double      primaryQ2;
  G4double      crossSection;
  G4double      crossSectionWeight;

  G4int         primaryEventNumber;

  G4String      particleName;
  G4int         particleType;

public:

  inline void  StoreVDCID(G4int vdc_ID)  { vdcID = vdc_ID; }
  inline G4int   GetVDCID() const { return vdcID; }
  
  inline void  StoreWirePlaneID(G4int wireplane_ID) { wireplaneID = wireplane_ID; }
  inline G4int   GetWirePlaneID()      const { return wireplaneID; }
  //------  
  inline void     StoreGlobalTime(G4double t)    { time = t; }
  inline G4double   GetGlobalTime() const { return time; }
  //------
  inline void          StoreLocalPosition(G4ThreeVector lxyz) { localPos = lxyz; }
  inline G4ThreeVector   GetLocalPosition()      const { return localPos; }
  
  inline void          StoreWorldPosition(G4ThreeVector gxyz) {  worldPos = gxyz; }
  inline G4ThreeVector   GetWorldPosition()       const { return worldPos; }
  //------
  inline void          StoreLocalMomentum(G4ThreeVector lpxyz) { localMomentum = lpxyz; }
  inline G4ThreeVector   GetLocalMomentum()      const {  return localMomentum; }
  
  inline void          StoreWorldMomentum(G4ThreeVector gpxyz) { worldMomentum = gpxyz; }
  inline G4ThreeVector   GetWorldMomentum()       const { return worldMomentum; }
  //------
  inline void          StoreOriginVertexPosition(G4ThreeVector xyz) { originVertexPosition = xyz; }
  inline G4ThreeVector   GetOriginVertexPosition()     const { return originVertexPosition; }
  
  inline void          StoreOriginVertexMomentumDirection(G4ThreeVector pxyz) { originVertexMomentumDirection = pxyz; }
  inline G4ThreeVector   GetOriginVertexMomentumDirection()      const { return originVertexMomentumDirection; }
  
  inline void     StoreOriginVertexKineticEnergy(G4double ekin) { originVertexKineticEnergy = ekin; }
  inline G4double   GetOriginVertexKineticEnergy() const { return originVertexKineticEnergy; }
  
  inline void     StoreOriginVertexTotalEnergy(G4double et) { originVertexTotalEnergy = et; }
  inline G4double   GetOriginVertexTotalEnergy() const { return originVertexTotalEnergy; }

  //------
  inline void     StorePrimaryEventNumber(G4int en)   { primaryEventNumber = en; }
  inline G4int      GetPrimaryEventNumber() const { return  primaryEventNumber; }
  //------
  inline void     StorePrimaryQ2(G4double q2)   { primaryQ2 = q2; }
  inline G4double   GetPrimaryQ2() const { return primaryQ2; }

  inline void     StoreCrossSection(G4double cs)  {crossSection = cs;}
  inline G4double   GetCrossSection() const {return crossSection;}

  inline void     StoreCrossSectionWeight(G4double csw)  {crossSectionWeight = csw;}
  inline G4double   GetCrossSectionWeight() const {return crossSectionWeight;}


  inline void     StoreParticleName(G4String pn)   {particleName = pn;}
  inline G4String   GetParticleName() const {return particleName;}

  inline void     StoreParticleType(G4int pt)   {particleType = pt;}
  inline G4int   GetParticleType() const {return particleType;}

  inline void     StoreKineticEnergy(G4double ekin) { currentKineticEnergy  = ekin; }
  inline G4double   GetKineticEnergy() const { return currentKineticEnergy; }

  inline void     StoreTotalEnergy(G4double etot) { currentTotalEnergy  = etot; }
  inline G4double   GetTotalEnergy() const { return currentTotalEnergy; }


  };

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef G4THitsCollection<QweakSimVDC_WirePlaneHit> QweakSimVDC_WirePlane_HitsCollection;

extern G4Allocator<QweakSimVDC_WirePlaneHit> QweakSimVDC_WirePlane_HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* QweakSimVDC_WirePlaneHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)QweakSimVDC_WirePlane_HitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void QweakSimVDC_WirePlaneHit::operator delete(void* aHit)
{
  QweakSimVDC_WirePlane_HitAllocator.FreeSingle((QweakSimVDC_WirePlaneHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

