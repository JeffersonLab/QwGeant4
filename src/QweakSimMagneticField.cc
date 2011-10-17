//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimMagneticField.cc

   $Revision: 1.2 $
   $Date: 2005/12/27 19:10:21 $

   \author Klaus Hans Grimm

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:10:21 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
//
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMagneticField.hh"

// geant4 includes
#include "G4SystemOfUnits.hh"

// user includes
#include "QweakSimMagneticFieldMessenger.hh"
#include "QweakSimFieldMap.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagneticField::QweakSimMagneticField()
{
  G4cout << G4endl << "###### Calling QweakSimMagneticField::QweakSimMagneticField() " << G4endl << G4endl;

  // No field map
  fField = 0;

  // Messenger
  fMagneticFieldMessenger = new QweakSimMagneticFieldMessenger(this);

  // TODO needs to go into messenger
  SetRotation(0.0);
  SetTranslation(0.0);
  SetScaleFactor(1.0);

  G4cout << G4endl << "###### Leaving QweakSimMagneticField::QweakSimMagneticField " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimMagneticField::~QweakSimMagneticField()
{
  G4cout << G4endl << "###### Calling QweakSimMagneticField::~QweakSimMagneticField() " << G4endl << G4endl;

  // Delete existing magnetic field
  if (fField) delete fField;

  // Delete messenger
  if (fMagneticFieldMessenger) delete fMagneticFieldMessenger;

  G4cout << G4endl << "###### Leaving QweakSimMagneticField::~QweakSimMagneticField() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagneticField::ReadFieldMap(const G4String& filename)
{
  G4cout << G4endl << "###### Calling QweakSimMagneticField::ReadFieldMap() " << G4endl << G4endl;

  // Depending on form of filename, read regular/binary field map
  if (filename.find(".dat") != std::string::npos) {
    ReadFieldMapText(filename);
  }
  if (filename.find(".bin") != std::string::npos) {
    ReadFieldMapBinary(filename);
  }

  G4cout << G4endl << "###### Leaving QweakSimMagneticField::ReadFieldMap() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagneticField::TestFieldMap() const
{
  // Test field value at exact grid point (r = 100*cm, z = 100*cm, phi = 22.5*degree)
  //G4double point[4] = {38.2683432 * cm, 92.3879533 * cm, 100.0 * cm, 0.0};
  G4double point[4] = {100.0 * cm, 0.0 * cm, 100.0 * cm, 0.0};
  G4double exact[3] = {-0.0499845 * kilogauss, 3.28516 * kilogauss, -0.0112704 * kilogauss};

  // Calculate field value
  G4cout << "Calculating test field value at cartesian position "
    << "(" << point[0]/cm << "," << point[1]/cm << "," << point[2]/cm << ") cm "
    << G4endl;
  G4double value[3] = {0.0, 0.0, 0.0};
  GetFieldValue(point,value);

  // Calculate difference
  G4double diff[3] = {0.0, 0.0, 0.0};
  G4double norm = 0.0;
  for (size_t i = 0; i < 3; i++) {
    diff[i] = value[i] - exact[i];
    norm += diff[i] * diff[i];
  }
  norm = sqrt(norm);

  // Output
  G4cout << "  Value = "
    << "(" << value[0]/kilogauss << ", " << value[1]/kilogauss << ", " << value[2]/kilogauss << ") kG."
    << G4endl;
  G4cout << "  Exact = "
    << "(" << exact[0]/kilogauss << ", " << exact[1]/kilogauss << ", " << exact[2]/kilogauss << ") kG."
    << G4endl;
  G4cout << "  Diff  = "
    << "(" << diff[0]/kilogauss << ", " << diff[1]/kilogauss << ", " << diff[2]/kilogauss << ") kG."
    << G4endl;

  // Test difference (0.1 kilogauss is of the order of 2%)
  if (norm > 0.1 * kilogauss) {
    G4cerr << "Magnetic field is different from expected value by " << norm/kilogauss << " kG."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagneticField::ReadFieldMapBinary(const G4String& filename)
{
  // Delete old field map
  if (fField) delete fField;

  // Create new field map
  fField = new QweakSimFieldMap<value_t,value_n>(filename);
  //fField->SetDebugLevel(QweakSimFieldMap<value_t,value_n>::kDebug);

  // Test new field map
  TestFieldMap();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagneticField::ReadFieldMapText(const G4String& filename)
{
  // Delete old field map
  if (fField) delete fField;

  // Create new field map
  fField = new QweakSimFieldMap<value_t,value_n>(3);
  fField->SetDebugLevel(QweakSimFieldMap<value_t,value_n>::kDebug);

  // Fill vector of grid min, max, and step size
  std::vector<double> min, max, step;
  std::vector<size_t> wrap;
  min.push_back(-250.0); max.push_back(250.0); step.push_back(2.0); wrap.push_back(0);
  min.push_back(2.0);    max.push_back(300.0); step.push_back(2.0); wrap.push_back(0);
  min.push_back(-0.5 * degree/radian); max.push_back(360.5 * degree/radian); step.push_back(1.0 * degree/radian); wrap.push_back(2);
  fField->SetDimensions(min.size());
  fField->SetMinimumMaximumStep(min,max,step);
  fField->SetWrapCoordinate(wrap);
  //
  SetRotation(90.0 * degree - 22.5 * degree);
  SetTranslation(0.0 * cm);

  // Debug output
  G4cout << "Reading field grid: ";

  // Open the field map file
  std::ifstream inputfile;
  inputfile.open(filename);
  while (inputfile.good()) {
    // Progress bar
    if (fField->GetCurrentEntries() % (fField->GetMaximumEntries() / 10) == 0) {
      int pct = fField->GetCurrentEntries() / (fField->GetMaximumEntries() / 100);
      G4cout << pct << "%" << std::flush;
    }
    if (fField->GetCurrentEntries() % (fField->GetMaximumEntries() / 10) != 0
     && fField->GetCurrentEntries() % (fField->GetMaximumEntries() / 40) == 0) {
      G4cout << "." << std::flush;
    }

    // Read variables
    G4double r = 0.0, z = 0.0, phi = 0.0;
    value_t b[3] = {0.0, 0.0, 0.0};
    inputfile >> r >> z >> phi >> b[0] >> b[1] >> b[2];

    // Transform units into Geant4 system of units
    r *= cm;
    z *= cm;
    phi *= degree;
    b[0] *= kilogauss;
    b[1] *= kilogauss;
    b[2] *= kilogauss;

    // Translation
    z -= fTranslation;

    // Rotation
    phi -= fRotation;
    if (phi <   0.0 * degree) phi += 360.0 * degree;
    if (phi > 360.0 * degree) phi -= 360.0 * degree;
    value_t b_rot[2];
    b_rot[0] =  b[0] * fRotationCos + b[1] * fRotationSin;
    b_rot[1] = -b[0] * fRotationSin + b[1] * fRotationCos;
    b[0] = b_rot[0]; b[1] = b_rot[1];

    // Transform units into fieldmap system of units
    double  coord[3] = { z/cm, r/cm, phi/radian };
    value_t field[3] = { b[0]/tesla, b[1]/tesla, b[2]/tesla };

    // Store into fieldmap
    fField->Set(coord,field);
  }
  G4cout << G4endl;

  // Close file
  inputfile.close();

  // Test new field map
  TestFieldMap();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagneticField::GetFieldValue(const G4double point[4], G4double *field) const
{
  // Convert from cartesian to cylindrical coordinates
  G4double z   = point[2];
  G4double r   = sqrt(point[0] * point[0] + point[1] * point[1]);
  G4double phi = atan2(point[1], point[0]);

  // Retrieve field value
  field[0] = 0.0;
  field[1] = 0.0;
  field[2] = 0.0;
  if (fField) {
    // Get field value
    G4double coord[3] = {z/cm, r/cm, phi/radian};
    fField->GetValue(coord,field);

    // Units and scale factor
    field[0] *= fScaleFactor * tesla;
    field[1] *= fScaleFactor * tesla;
    field[2] *= fScaleFactor * tesla;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//      $Revisions$
//      $Log: QweakSimMagneticField.cc,v $
//      Revision 1.2  2005/12/27 19:10:21  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
