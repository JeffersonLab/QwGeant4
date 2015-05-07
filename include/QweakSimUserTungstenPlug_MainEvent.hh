
// QweakSimUserTungstenPlug_MainEvent.hh
// Martin McHugh
// 2013-07-20

/////// --------------------------------------------------------------------

#ifndef QweakSimUserTungstenPlug_MainEvent_h
#define QweakSimUserTungstenPlug_MainEvent_h

/////// --------------------------------------------------------------------

//--- system include
#include <vector>

//--- root include
#include "TObject.h"

//-- user include
#include "QweakSimUserTungstenPlug_DetectorEvent.hh"

/////// --------------------------------------------------------------------
class QweakSimUserTungstenPlug_MainEvent : public TObject
{
	
public:
	
    QweakSimUserTungstenPlug_MainEvent();
    virtual ~QweakSimUserTungstenPlug_MainEvent();
	
    ClassDef(QweakSimUserTungstenPlug_MainEvent,1);
	
public:
	
    QweakSimUserTungstenPlug_DetectorEvent  Detector;
	
private:
	
};

#endif

