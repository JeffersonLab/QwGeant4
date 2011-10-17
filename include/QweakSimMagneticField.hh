//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMagneticField_h
#define QweakSimMagneticField_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4String.hh"
#include "G4MagneticField.hh"

// user classes
template <class value_t, unsigned int value_n>
class QweakSimFieldMap;
class QweakSimMagneticFieldMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMagneticField: public G4MagneticField
{
  private:

    /// Number of field component in the map (x,y,z,r,phi)
    static const unsigned int value_n = 3;

    /// Field map storage data type
    typedef float value_t;

    /// Messenger
    QweakSimMagneticFieldMessenger* fMagneticFieldMessenger;

  public:

    /// Default constructor
    QweakSimMagneticField();
    /// Virtual destructor
    virtual ~QweakSimMagneticField();


    /// Get the field value
    void GetFieldValue(const G4double point[4], G4double *field) const;


    /// Set the scale factor
    void SetScaleFactor(const double scalefactor)
      { fScaleFactor = scalefactor; };
    /// Get the scale factor
    double GetScaleFactor() const { return fScaleFactor; };

    /// Set the field rotation around z
    void SetRotation(const double rotation) {
      fRotation = rotation;
      fRotationCos = cos(rotation);
      fRotationSin = sin(rotation);
    };
    /// Get the field rotation around z
    double GetRotation() const { return fRotation; };

    /// Set the field translation along z
    void SetTranslation(const double translation)
      { fTranslation = translation; };
    /// Get the field translation along z
    double GetTranslation() const { return fTranslation; };


    void ReadFieldMap(const G4String& filename);
    void ReadFieldMapText(const G4String& filename);
    void ReadFieldMapBinary(const G4String& filename);

    void TestFieldMap() const;

  private:

    QweakSimFieldMap<value_t,value_n>* fField;

    /// Field rotation and translation with respect to the z axis
    // Defined as rotation/translation of the map in the standard coordinate
    // system: rotation of +22.5 deg means that x in the map x is at +22.5 deg,
    // likewise a translation of +5 cm means that the zero in the map is at +5 cm
    // in the standard coordinate system.
    double fRotation, fRotationCos, fRotationSin;
    double fTranslation;
    double fScaleFactor;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
