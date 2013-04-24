//=============================================================================
/**

   \file QweakSimEventAction.hh
   $Revision: 1.4 $
   $Date: 2006/01/06 21:29:35 $
   \author Klaus Hans Grimm

*/
//=============================================================================
//
//=============================================================================
/**
   \class QweakSimEventAction

   \brief Mainly filling/storing the hit event structure at the end of an event

   Placeholder for a long explaination

 */
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimEventAction_h
#define QweakSimEventAction_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>
#include <map>

// root includes
#include "Rtypes.h"
#include "TString.h"

// geant4 includes
#include "G4Types.hh"
#include "G4String.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"

// user classes
class QweakSimAnalysis;
class QweakSimUserInformation;
class QweakSimEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

enum EQweakSimTriggerMode
  { kTriggerAll, kTrigger4Fold, kTrigger3Fold,
    kTriggerScint, kTriggerLeadGlass, kTriggerCer,
    kNumTriggers };

class QweakSimEventAction : public G4UserEventAction
{
public:
    //!Constructor
    QweakSimEventAction(QweakSimAnalysis* AN, QweakSimUserInformation* myUI);

    //!Destructor
    ~QweakSimEventAction();

public:

  void BeginOfEventAction(const G4Event* evt);
  void EndOfEventAction(const G4Event* evt);

  void ShowTrigger();
  void SetTrigger(const G4String value, const G4bool status);
  void EnableTrigger(const G4String value) { SetTrigger(value, true); };
  void DisableTrigger(const G4String value) { SetTrigger(value, false); };

private:

  void Initialize();
  G4double GetDistance(G4ThreeVector,G4ThreeVector);
  void CalculateKinematicVariables();

  // Event action messenger
  QweakSimEventActionMessenger* fEventActionMessenger;

  // Trigger mask
  std::vector<G4bool> fTrigger;
  std::vector<G4String> fTriggerName;
  std::map < G4String, EQweakSimTriggerMode > kMapTriggerMode;


  G4int GEM_WirePlane_CollID;
  G4int HDC_WirePlane_CollID;
  G4int VDC_WirePlane_CollID;
  G4int VDC_DriftCellFront_CollID;
  G4int VDC_DriftCellBack_CollID;
  G4int TriggerScintillatorDetector_CollID;
  G4int TriggerScintillatorPMT_CollID;
  G4int LeadGlassDetector_CollID;
  G4int LeadGlassPMT_CollID;
  G4int CerenkovDetector_CollID;
  G4int CerenkovDetectorPMT_CollID;

  QweakSimAnalysis*             analysis;
  QweakSimUserInformation*      myUserInfo;

  // Print hits for some subsystems during debugging
  //static const G4bool print_GEM_WirePlaneHit = false;
  static const G4bool print_VDC_WirePlaneHit = false;
  static const G4bool print_VDC_DriftCellHit = false;
  static const G4bool print_TriggerScintillator_DetectorHit = false;
  static const G4bool print_Cerenkov_DetectorHit = false;

  G4int n_GEMhitWirePlane;
  G4int n_HDChitWirePlane;
  G4int n_VDChitWirePlane;
  G4int n_VDChitDCFront;
  G4int n_VDChitDCBack;
  G4int n_hitTriggerScintillator;
  G4int n_hitTriggerScintillatorPMT;
  G4int n_hitLeadGlass;
  G4int n_hitLeadGlassPMT;
  G4int n_hitCerenkov;
  G4int n_hitCerenkovPMT;

  G4int  OriginVertexPDGcode;
  Int_t rOriginVertexPDGcode;


  G4double OriginVertexParticleMass;
  Float_t rOriginVertexParticleMass;

  G4double  OriginVertexThetaAngle;
  Float_t  rOriginVertexThetaAngle;

  G4double  OriginVertexPhiAngle;
  Float_t  rOriginVertexPhiAngle;

  // get local position of hit
  G4ThreeVector localPosition;
  Float_t      rLocalPositionX;
  Float_t      rLocalPositionY;
  Float_t      rLocalPositionZ;

  G4ThreeVector localExitPosition;
  Float_t      rLocalExitPositionX;
  Float_t      rLocalExitPositionY;
  Float_t      rLocalExitPositionZ;

  G4ThreeVector SecondaryParticleOrigin;
  Float_t       rSecondaryPartOriginX;
  Float_t       rSecondaryPartOriginY;
  Float_t       rSecondaryPartOriginZ;

  G4ThreeVector SecondaryParticleMomentum;
  Float_t       rSecondaryPartMomentumX;
  Float_t       rSecondaryPartMomentumY;
  Float_t       rSecondaryPartMomentumZ;

  Float_t       rSecondaryPartEnergy;
  Float_t       rSecondaryPartCharge;

  // get world position of hit
  G4ThreeVector globalPosition;
  Float_t      rGlobalPositionX;
  Float_t      rGlobalPositionY;
  Float_t      rGlobalPositionZ;

  // get local momentum of hit
  G4ThreeVector localMomentum;
  Float_t      rLocalMomentumX;
  Float_t      rLocalMomentumY;
  Float_t      rLocalMomentumZ;

  // get world momentum of hit
  G4ThreeVector globalMomentum;
  Float_t      rGlobalMomentumX;
  Float_t      rGlobalMomentumY;
  Float_t      rGlobalMomentumZ;


  G4ThreeVector originVertexPosition;
  Float_t rOriginVertexPositionX;
  Float_t rOriginVertexPositionY;
  Float_t rOriginVertexPositionZ;


  G4ThreeVector originVertexMomentumDirection;
  Float_t rOriginVertexMomentumDirectionX;
  Float_t rOriginVertexMomentumDirectionY;
  Float_t rOriginVertexMomentumDirectionZ;


  Float_t  rOriginVertexKineticEnergy;
  Float_t  rOriginVertexTotalEnergy;

  //---------------------------------
  Float_t   rGlobalThetaAngle;
  Float_t   rGlobalPhiAngle;
  //---------------------------------

  Float_t rPrimaryQ2;
  Float_t  rCrossSection;
  Float_t  rCrossSectionWeight;
  Float_t  rAsymmetry;
  
  Int_t rPrimaryEventNumber;

  Float_t rGlobalTime;
	
  //--- LeadGlass deposited energy
  Float_t  rTrackID;	
	
  G4ThreeVector localVertexMomentumDirection;
  Float_t      rLocalVertexMomentumDirectionX;
  Float_t      rLocalVertexMomentumDirectionY;
  Float_t      rLocalVertexMomentumDirectionZ;
	
  Float_t rDepositedEnergy;
	
  //-----------------------------------------

  G4double rDCWidthOnFrame;
  G4double rDCFullThickness;
  G4double rDCUPlaneWireAngle;
  G4double rDCVPlaneWireAngle;

//   vector <G4int>    pmtHitsLeft;
//   vector <G4int>    pmtHitsRight;
//   vector <G4double> pmtNPELeft;
//   vector <G4double> pmtNPERight;
  G4int    pmtHitsLeft;
  G4int    pmtHitsRight;
  G4double pmtNPELeft;
  G4double pmtNPERight;


  Int_t edgeEvent;

  TString   rParticleName;
  Int_t     rParticleType;

  Float_t   rTotalEnergy;
  Float_t   rKineticEnergy;

  G4int  detectorID;
  Int_t  octantID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

