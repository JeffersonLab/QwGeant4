#ifndef QweakSimTrackHistory_h
#define QweakSimTrackHistory_h 1

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh"


class QweakSimTrackHistory {

 private:

     G4int                 sourceTrackID;
     G4ParticleDefinition* sourceDefinition;
     G4ThreeVector         sourcePosition;
     G4ThreeVector         sourceMomentum;
     G4double              sourceEnergy;
     G4double              sourceTime;

 public:

  QweakSimTrackHistory();
  virtual ~QweakSimTrackHistory();

  void Initialize();
  void Print() const ;

  void AddTrackInfo(const G4Track* aTrack);

  inline G4int                 GetSourceTrackID()  const {return sourceTrackID;}
  inline G4ParticleDefinition* GetSourceParticle() const {return sourceDefinition;}
  inline G4ThreeVector         GetSourcePosition() const {return sourcePosition;}
  inline G4ThreeVector         GetSourceMomentum() const {return sourceMomentum;}
  inline G4double              GetSourceEnergy()   const {return sourceEnergy;}
  inline G4double              GetSourceTime()     const {return sourceTime;}

//  ClassDef(QweakSimTrackHistory,1);
};

#endif
