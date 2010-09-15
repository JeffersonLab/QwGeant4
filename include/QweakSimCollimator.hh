
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimCollimator.hh
   $Revision: 1.11 $	
   $Date: 2005/12/28 22:46:48 $
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
   \class QweakSimCollimator
    
   \brief Definition of the Collimators

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
//  Update Date:      $Date: 2005/12/28 22:46:48 $
//  CVS/RCS Revision: $Revision: 1.11 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimCollimator_h
#define QweakSimCollimator_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "Geant4_include.hh" 

// user includes
//#include "QweakSimCollimatorMessenger.hh"
#include "QweakSimMaterial.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class QweakSimMaterial;
//class QweakSimCollimatorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimCollimator
{

private:

  G4int             CollNum;

  QweakSimMaterial* pMaterial;
  
  G4LogicalVolume*   CollimatorHousing_Logical; 
  G4VPhysicalVolume* CollimatorHousing_Physical; 

  G4double CollimatorHousing_FullLength_X;
  G4double CollimatorHousing_FullLength_Y;
  G4double CollimatorHousing_FullLength_Z;

  G4double CollimatorHousing_CenterZPosition;

  G4double OctantCutOutFrontFullLength_X1;
  G4double OctantCutOutFrontFullLength_X2;
  G4double OctantCutOutFrontFullLength_Y;
  G4double OctantCutOutBackFullLength_X1;
  G4double OctantCutOutBackFullLength_X2;
  G4double OctantCutOutBackFullLength_Y;

  G4double OctantCutOutFrontInnerDiameter;
  G4double OctantCutOutFrontOuterDiameter;
  G4double OctantCutOutBackInnerDiameter;
  G4double OctantCutOutBackOuterDiameter;
  G4double OctantCutOutStartingPhiAngle;
  G4double OctantCutOutDeltaPhiAngle;
  G4double OctantCutOutRadialOffset;
  G4double BeamlineCutoutDiameter;

public:
    //!Constructor
  QweakSimCollimator();

  //!Destructor
  ~QweakSimCollimator();


  void ConstructCollimator(G4VPhysicalVolume*);

  void DestroyComponent();

  void     SetCollimatorHousing_CenterPositionInZ(G4double zpos);
  G4double GetCollimatorHousing_CenterPositionInZ()     { return CollimatorHousing_CenterZPosition;}

  void SetCollimatorHousingMaterial(G4String);

  void SetCollimatorHousing_FullLengthInX(G4double dim) {       CollimatorHousing_FullLength_X = dim;}
  void SetCollimatorHousing_FullLengthInY(G4double dim) {       CollimatorHousing_FullLength_Y = dim;}
  void SetCollimatorHousing_FullLengthInZ(G4double dim) {       CollimatorHousing_FullLength_Z = dim;}

  G4double GetCollimatorHousing_FullLengthInX()         {return CollimatorHousing_FullLength_X;}
  G4double GetCollimatorHousing_FullLengthInY()         {return CollimatorHousing_FullLength_Y;}
  G4double GetCollimatorHousing_FullLengthInZ()         {return CollimatorHousing_FullLength_Z;}



  void SetOctantCutOutFrontFullLength_X1(G4double dim)  {OctantCutOutFrontFullLength_X1 = dim;}
  void SetOctantCutOutFrontFullLength_X2(G4double dim)  {OctantCutOutFrontFullLength_X2 = dim;}
  void SetOctantCutOutFrontFullLength_Y(G4double dim)   {OctantCutOutFrontFullLength_Y  = dim;}
  void SetOctantCutOutBackFullLength_X1(G4double dim)   {OctantCutOutBackFullLength_X1  = dim;}
  void SetOctantCutOutBackFullLength_X2(G4double dim)   {OctantCutOutBackFullLength_X2  = dim;}
  void SetOctantCutOutBackFullLength_Y(G4double dim)    {OctantCutOutBackFullLength_Y   = dim;}
							   
  void SetOctantCutOutFrontInnerDiameter(G4double fid)  {OctantCutOutFrontInnerDiameter = fid;}
  void SetOctantCutOutFrontOuterDiameter(G4double fod)  {OctantCutOutFrontOuterDiameter = fod;}
  void SetOctantCutOutBackInnerDiameter(G4double bid)   {OctantCutOutBackInnerDiameter  = bid;}
  void SetOctantCutOutBackOuterDiameter(G4double bod)   {OctantCutOutBackOuterDiameter  = bod;}
  void SetOctantCutOutStartingPhiAngle(G4double spa)    {OctantCutOutStartingPhiAngle   = spa;}
  void SetOctantCutOutDeltaPhiAngle(G4double dpa)       {OctantCutOutDeltaPhiAngle      = dpa;}
  void SetOctantCutOutRadialOffset(G4double dpa)        {OctantCutOutRadialOffset       = dpa;}
  void SetBeamlineCutoutDiameter(G4double dia)          {BeamlineCutoutDiameter         = dia;}

  void  SetCollimatorNumber(G4int n)                    {       CollNum = n;}
  G4int GetCollimatorNumber()                           {return CollNum;}

  G4LogicalVolume*   getCollimatorHousingLogicalVolume()    {return CollimatorHousing_Logical;} 
  G4VPhysicalVolume* getCollimatorHousingPhysicalVolume()   {return CollimatorHousing_Physical;} 

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCollimator.hh,v $
//      Revision 1.11  2005/12/28 22:46:48  grimm
//      Added Getter functions for retrieving Collimator position and size needed by QweakSimCollimatorSupport
//
//      Revision 1.10  2005/12/27 19:23:13  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//      Revision 1.9  2005/12/26 18:15:34  grimm
//      - another test with cvs revision and data info within doxygen
//
//      Revision 1.8  2005/12/26 18:03:39  grimm
//      - another test with cvs revision and data info within doxygen
//
//      Revision 1.7  2005/12/26 17:44:25  grimm
//      - Put the CVS Revision changes at the end of the file
//
//      Revision 1.6  2005/12/26 15:27:46  grimm
//      - Put the CVS Revision changes at the end of the file
//
//      Revision 1.5  2005/12/26 13:46:45  grimm
//      - Another test with CVS keywords within doxygen
//
//      Revision 1.4  2005/12/26 13:36:37  grimm
//      - CVS keywords within doxygen header
//
//      Revision 1.3  2005/12/26 02:00:46  grimm
//      - Just another CVS test
// 
//      Revision 1.2  2005/12/26 01:54:41  grimm
//      - First test with CVS info within doxygen file header
//
