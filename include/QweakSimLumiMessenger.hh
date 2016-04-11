/*

   \file QweakSimLumiMessenger.hh
   \author Wade Duvall

*/

#ifndef QweakSimLumiMessenger_h
#define QweakSimLumiMessenger_h 1

#include "QweakSimMessengerDeclaration.hh"

/* Forward declare. */
class QweakSimLumiDetector;

class QweakSimLumiMessenger: public G4UImessenger {
    public:
        QweakSimLumiMessenger(QweakSimLumiDetector*, G4String);
        ~QweakSimLumiMessenger();
        void SetNewValue(G4UIcommand*, G4String);

    private:
        QweakSimLumiDetector* myLumi;
        G4UIdirectory* LumiDir;

        G4UIcmdWithADoubleAndUnit* Lumi_SetPositionInX_Cmd;
        G4UIcmdWithADoubleAndUnit* Lumi_SetPositionInY_Cmd;
        G4UIcmdWithADoubleAndUnit* Lumi_SetPositionInZ_Cmd;

        G4UIcmdWithoutParameter* Lumi_SetEnabled_Cmd;
        G4UIcmdWithoutParameter* Lumi_SetDisabled_Cmd;
};
#endif
