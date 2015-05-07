
// QweakSimTungstenPlug_DetectorSD.hh
// Martin McHugh
// 2015-05-04

/////// --------------------------------------------------------------------

#ifndef QweakSimTungstenPlug_DetectorSD_h
#define QweakSimTungstenPlug_DetectorSD_h 

//--- user includes
#include "QweakSimTungstenPlug_DetectorHit.hh"
#include "QweakSimSensitiveDetectorDeclaration.hh"



/////// --------------------------------------------------------------------

class QweakSimTungstenPlug_DetectorSD : public G4VSensitiveDetector
{
	
public:
    QweakSimTungstenPlug_DetectorSD(G4String name);
    ~QweakSimTungstenPlug_DetectorSD();
	
    void   Initialize(G4HCofThisEvent* HCE);
    G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    void   EndOfEvent(G4HCofThisEvent* HCE);
	
private:
	
    QweakSimTungstenPlug_DetectorHitsCollection*  TungstenPlug_DetectorHitsCollection;
    G4int  TungstenPlug_CollectionID;
	
};



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
