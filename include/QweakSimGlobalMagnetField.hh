//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimGlobalMagnetField_h
#define QweakSimGlobalMagnetField_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "Geant4_include.hh" 

// user includes
//#include "QweakSimGlobalMagnetFieldMessenger.hh"
#include "QweakSimMagnetFieldMap.hh"

// user classes
//class QweakSimGlobalMagnetFieldMessenger;
class QweakSimMagnetFieldMap;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimGlobalMagnetField : public G4MagneticField
{
public:

   QweakSimGlobalMagnetField();
  ~QweakSimGlobalMagnetField();


  void GetFieldValue( const  G4double Point[4], G4double *Bfield ) const;  

private:

  //QweakSimGlobalMagnetFieldMessenger*      fGlobalMagnetFieldMessenger;

    QweakSimMagnetFieldMap*  fMagneticField_MainMagnet;


    G4double BFieldScalingFactor_MainMagnet;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
