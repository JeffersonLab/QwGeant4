/**
   \class QweakSimCerenkov_DetectorSD
    
   \brief Storing hit information of the Cerenkov detector
    
 */

#ifndef QweakSimCerenkov_DetectorSD_h
#define QweakSimCerenkov_DetectorSD_h 

// user includes
#include "QweakSimSensitiveDetectorDeclaration.hh"
#include "QweakSimCerenkov_DetectorHit.hh"

class QweakSimCerenkov_DetectorSD: public G4VSensitiveDetector
{
  public:

    QweakSimCerenkov_DetectorSD(G4String name);
    virtual ~QweakSimCerenkov_DetectorSD();

    void Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void EndOfEvent(G4HCofThisEvent* HCE);

  private:

    QweakSimCerenkovDetectorHitsCollection*  CerenkovDetectorHitsCollection;

    G4int CerenkovDetectorCollectionID;
};

#endif
