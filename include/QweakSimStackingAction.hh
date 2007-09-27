
#ifndef QweakSimStackingAction_H
#define QweakSimStackingAction_H 1



// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

#include "QweakSimSteppingAction.hh"
//#include "QweakSimTrackInformation.hh"

class QweakSimStackingAction : public G4UserStackingAction
{
public:
  QweakSimStackingAction();
  ~QweakSimStackingAction();
  
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  virtual void PrepareNewEvent();

private:
};

#endif
