
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_DriftCellParameterisation.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:32:20 $
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
   \class QweakSimVDC_DriftCellParameterisation
    
   \brief Parameterisation of the VDC Drift Cell locations

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
//  Update Date:      $Date: 2005/12/27 19:32:20 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_DriftCellParameterisation_H
#define QweakSimVDC_DriftCellParameterisation_H 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes


// Dummy declarations to get rid of warnings ...
// class G4Box;
// class G4Trd;
// class G4Trap;
// class G4Cons;
// class G4Orb;
// class G4Sphere;
// class G4Torus;
// class G4Para;
// class G4Hype;
// class G4Tubs;
// class G4Polycone;
// class G4Polyhedra;
//
// class G4VPhysicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimVDC_DriftCellParameterisation : public G4VPVParameterisation
{ 
public:
  
  QweakSimVDC_DriftCellParameterisation( G4int    NumberOfDriftCells, 
				     G4double SpacingInX);
  
  virtual ~QweakSimVDC_DriftCellParameterisation();
   
  void ComputeTransformation (const G4int copyNo,
			      G4VPhysicalVolume* physVol) const;
  
  
private:  // Dummy declarations to get rid of warnings ...
  
  void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
  
private:
  
  G4int    myNumberOfDriftCells; // Number DriftCells to be placed  
  G4double mySpacingInX;         //  The distance between the drift cell center
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellParameterisation.hh,v $
//      Revision 1.2  2005/12/27 19:32:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

