//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimGlobalMagnetField_h
#define QweakSimGlobalMagnetField_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMagnetFieldMap.hh"
#include "G4MagneticField.hh"

// user classes
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
