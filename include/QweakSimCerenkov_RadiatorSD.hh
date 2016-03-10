/**
   \class QweakSimCerenkov_RadiatorSD

   \brief Storing hit information of the Cerenkov radiator

 */

#ifndef QweakSimCerenkov_RadiatorSD_h
#define QweakSimCerenkov_RadiatorSD_h

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimCerenkov_RadiatorHit.hh"

class QweakSimCerenkov_RadiatorSD: public G4VSensitiveDetector
{
  public:

    QweakSimCerenkov_RadiatorSD(G4String name);
    virtual ~QweakSimCerenkov_RadiatorSD();

    void Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void EndOfEvent(G4HCofThisEvent* HCE);

  private:

    QweakSimCerenkovRadiatorHitsCollection*  CerenkovRadiatorHitsCollection;

    G4int CerenkovRadiatorCollectionID;
};

#endif
