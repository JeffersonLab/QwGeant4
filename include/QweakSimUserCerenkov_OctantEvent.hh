/**
   \class QweakSimUserCerenkov_OctantEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov octant event
    
 */

#ifndef QweakSimUserCerenkov_OctantEvent_h
#define QweakSimUserCerenkov_OctantEvent_h

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserCerenkov_DetectorEvent.hh"
#include "QweakSimUserCerenkov_RadiatorEvent.hh"
#include "QweakSimUserCerenkov_PMTEvent.hh"

class QweakSimUserCerenkov_OctantEvent: public TObject
{
  public:

    QweakSimUserCerenkov_DetectorEvent  Detector; ///< Event information for hits in the detector
    QweakSimUserCerenkov_RadiatorEvent  Radiator; ///< Event information for hits in the radiator
    QweakSimUserCerenkov_PMTEvent       PMT;      ///< Event information for hits in the PMT

  public:

    // Constructor
    QweakSimUserCerenkov_OctantEvent();
    // Destructor
    virtual ~QweakSimUserCerenkov_OctantEvent();

    // define a new Class known to ROOT
    ClassDef(QweakSimUserCerenkov_OctantEvent,1)

}; // end class QweakSimCerenkov_OctantEvent

#endif
