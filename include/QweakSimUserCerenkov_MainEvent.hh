/**
   \class QweakSimUserCerenkov_MainEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov main event
    
 */

#ifndef QweakSimUserCerenkov_MainEvent_h
#define QweakSimUserCerenkov_MainEvent_h

// system includes
#include <vector>

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserCerenkov_DetectorEvent.hh"
#include "QweakSimUserCerenkov_RadiatorEvent.hh"
#include "QweakSimUserCerenkov_PMTEvent.hh"

class QweakSimUserCerenkov_MainEvent: public TObject
{
  public:

    QweakSimUserCerenkov_DetectorEvent  Detector;                 ///< Cerenkov detector hit information
    QweakSimUserCerenkov_RadiatorEvent  Radiator;                 ///< Cerenkov radiator hit information
    QweakSimUserCerenkov_PMTEvent       PMT;                      ///< Cerenkov PMT hit information

  public:

    // Constructor
    QweakSimUserCerenkov_MainEvent();
    // Destructor
    virtual ~QweakSimUserCerenkov_MainEvent();

    // define a new Class known to ROOT
    ClassDef(QweakSimUserCerenkov_MainEvent,1)

};  // end class QweakSimCerenkov_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
