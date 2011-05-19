//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimMagnetFieldMap.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:25:23 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimMagnetFieldMap
    
   \brief Reads the field maps and calculates the field value for any space point.

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:25:23 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMagnetFieldMap_h
#define QweakSimMagnetFieldMap_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4ThreeVector.hh"
#include "G4MagneticField.hh"

// system includes
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMagnetFieldMap : public G4MagneticField
{
public:

  QweakSimMagnetFieldMap();
  
  virtual ~QweakSimMagnetFieldMap();

  void GetFieldValue(const G4double Point[4], G4double *Bfield) const;

  void InitializeGrid();
  void ReadFieldMap(const char* filename);


  void SetFieldMap_RMin      ( G4double Rmin      ) { rMinFromMap    = Rmin;      }
  void SetFieldMap_RMax      ( G4double Rmax      ) { rMaxFromMap    = Rmax;      }
  void SetFieldMap_RStepsize ( G4double Rstepsize ) { gridstepsize_r = Rstepsize; }

  void SetFieldMap_ZMin      ( G4double Zmin      ) { zMinFromMap    = Zmin;      }
  void SetFieldMap_ZMax      ( G4double Zmax      ) { zMaxFromMap    = Zmax;      }
  void SetFieldMap_ZStepsize ( G4double Zstepsize ) { gridstepsize_z = Zstepsize; }

  void SetFieldMap_PhiMin      ( G4double Phimin      ) { phiMinFromMap    = Phimin;      }
  void SetFieldMap_PhiMax      ( G4double Phimax      ) { phiMaxFromMap    = Phimax;      }
  void SetFieldMap_PhiStepsize ( G4double Phistepsize ) { gridstepsize_phi = Phistepsize; }

private:

  G4int nGridPointsInR;
  G4int nGridPointsInPhi;
  G4int nGridPointsInZ;  

  G4double rMinFromMap;
  G4double rMaxFromMap;
   
  G4double phiMinFromMap;
  G4double phiMaxFromMap;
   
  G4double zMinFromMap;
  G4double zMaxFromMap;
   
  G4double gridstepsize_r;
  G4double gridstepsize_phi;
  G4double gridstepsize_z;


  G4double Unit_Length;
  G4double Unit_Angle;
  G4double Unit_Bfield; // units of field map 

// Storage space for the table
//   std::vector< std::vector< std::vector< G4double > > > BFieldGridData_X;
//   std::vector< std::vector< std::vector< G4double > > > BFieldGridData_Y;
//   std::vector< std::vector< std::vector< G4double > > > BFieldGridData_Z;
  std::vector< G4double > BFieldGridData_X;
  std::vector< G4double > BFieldGridData_Y;
  std::vector< G4double > BFieldGridData_Z;

  G4double fZoffset;
  G4bool   invertX, invertY, invertZ;

  G4ThreeVector* BField_ANSYS;
  
  G4double BFieldScalingFactor;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnetFieldMap.hh,v $
//      Revision 1.2  2005/12/27 19:25:23  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

