
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_DetectorEvent.hh
   $Revision: 1.3 $	
   $Date: 2006/01/06 20:31:24 $
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
   \class QweakSimUserCerenkov_DetectorEvent 
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov DetectorEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/06 20:31:24 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_DetectorEvent_h
#define QweakSimUserCerenkov_DetectorEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_DetectorEvent : public TObject
{

private:

  Int_t   DetectorID; ///< ID of the detector in which this hit was registered
  Int_t   TrackID;    ///< ID of the track from which this hit was generated

  Float_t GlobalTimeOfHit;      ///< Global time when this hit was generated (ns)

  Int_t HasBeenHit;             ///< Has this detector been hit? 0 = no, 5 = yes
  Int_t EdgeEventFlag;          ///< Was the distance between hit and exit position below 1.5 cm? 0 = no, 1 = yes
  Int_t NbOfHits;               ///< Number of hits in this detector

  Int_t SecondaryParticleCount; ///< Number of secondary particles
  Int_t SecondaryElectronCount; ///< Number of secondary electrons
  Int_t SecondaryPhotonCount;   ///< Number of secondary photons
  Int_t SecondaryPositronCount; ///< Number of secondary positrons

  Int_t OpticalPhotonCount;     ///< Number of optical photons

  /// \name Position in local coordinates of original vertex of the secondary in this event
  /// The global coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> SecPartLocalOriginX;
  std::vector<Float_t> SecPartLocalOriginY;
  std::vector<Float_t> SecPartLocalOriginZ;
  //@}

  /// \name Momentum in local coordinates of original vertex of the secondary in this event
  /// The global coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> SecPartLocalMomentumX;
  std::vector<Float_t> SecPartLocalMomentumY;
  std::vector<Float_t> SecPartLocalMomentumZ;
  //@}

  std::vector<Float_t> SecPartLocalEnergy;
  std::vector<Float_t> SecPartLocalType;

  std::vector<Double_t> CerenkovPhotonEnergy;
  
  /// \name Position of the hit in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  std::vector<Float_t> HitLocalPositionX; ///< (cm)
  std::vector<Float_t> HitLocalPositionY; ///< (cm)
  std::vector<Float_t> HitLocalPositionZ; ///< (cm)
  //@}

  /// \name Position where the track exits the volume in local coordinates (cm)
  /// The local coordinates are defined in the \ref local_coordinate_system.
  //@{
  Float_t HitLocalExitPositionX; ///< (cm)
  Float_t HitLocalExitPositionY; ///< (cm)
  Float_t HitLocalExitPositionZ; ///< (cm)
  //@}

  /// \name Position of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t HitGlobalPositionX;    ///< (cm)
  Float_t HitGlobalPositionY;    ///< (cm)
  Float_t HitGlobalPositionZ;    ///< (cm)
  //@}

  /// \name Position in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexPositionX; ///< (cm)
  Float_t OriginVertexPositionY; ///< (cm)
  Float_t OriginVertexPositionZ; ///< (cm)
  //@}

  /// \name Direction in global coordinates of original vertex of the track from which this hit was generated
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexMomentumDirectionX;
  Float_t OriginVertexMomentumDirectionY;
  Float_t OriginVertexMomentumDirectionZ;
  Float_t OriginVertexThetaAngle;       ///< (degrees)
  Float_t OriginVertexPhiAngle;         ///< (degrees)
  //@}

  Float_t OriginVertexKineticEnergy;
  Float_t OriginVertexTotalEnergy;

  /// \name Direction of the hit in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t GlobalThetaAngle;     ///< (degrees)
  Float_t GlobalPhiAngle;       ///< (degrees, but 90 degrees rotated to keep things interesting)
  //@}

  /// \name Particle name and type at the hit
  //@{
  TString ParticleName;         ///< Name of the particle type of this hit
  Int_t   ParticleType;         ///< \ref Lund_type of the particle type of this hit
  //@}

  /// \name Total and kinetic energy of the track at the hit
  //@{
  Float_t TotalEnergy;          ///< (MeV)
  Float_t KineticEnergy;        ///< (MeV)
  //@}

public:
  
  // Constructor
  QweakSimUserCerenkov_DetectorEvent();
  // Destructor 
  virtual ~QweakSimUserCerenkov_DetectorEvent();

  void Initialize();

  //-----------------
  void     StoreDetectorID(Int_t did)  { DetectorID = did; }
  Int_t      GetDetectorID() const {return DetectorID;}
  //-----------------

  void     StoreTrackID(Int_t tid)  { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}

  void     StoreParticleName(TString pn)    { ParticleName = pn; }
  TString    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType = pt; }
  Int_t      GetParticleType() const {return  ParticleType;}


  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit = gtime; }
  Float_t    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy = te; }
  Float_t    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy = ke; }
  Float_t    GetKineticEnergy() const {return KineticEnergy;}


  //-----------------
  void     StoreDetectorHasBeenHit(Int_t n)      { HasBeenHit = n; }
  Int_t      GetDetectorHasBeenHit() const {return HasBeenHit;}
  //-----------------
  void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
  Int_t      GetDetectorNbOfHits() const {return  NbOfHits;}
  //-----------------
  void     StoreDetectorLocalPositionX(Float_t lx)   { HitLocalPositionX.push_back(lx); }
  std::vector<Float_t>    GetDetectorLocalPositionX() const {return HitLocalPositionX;}

  void     StoreDetectorLocalPositionY(Float_t ly)   { HitLocalPositionY.push_back(ly); }
  std::vector<Float_t>    GetDetectorLocalPositionY() const {return HitLocalPositionY;}

  void     StoreDetectorLocalPositionZ(Float_t lz)   { HitLocalPositionZ.push_back(lz); }
  std::vector<Float_t>    GetDetectorLocalPositionZ() const {return HitLocalPositionZ;}
  //-----------------
  void     StoreDetectorLocalExitPositionX(Float_t lx)   { HitLocalExitPositionX = lx; }
  Float_t    GetDetectorLocalExitPositionX() const {return HitLocalExitPositionX;}

  void     StoreDetectorLocalExitPositionY(Float_t ly)   { HitLocalExitPositionY = ly; }
  Float_t    GetDetectorLocalExitPositionY() const {return HitLocalExitPositionY;}

  void     StoreDetectorLocalExitPositionZ(Float_t lz)   { HitLocalExitPositionZ = lz; }
  Float_t    GetDetectorLocalExitPositionZ() const {return HitLocalExitPositionZ;}
  //---
  void     StoreDetectorGlobalPositionX(Float_t lx)   { HitGlobalPositionX = lx; }
  Float_t    GetDetectorGlobalPositionX() const {return HitGlobalPositionX;}

  void     StoreDetectorGlobalPositionY(Float_t ly)   { HitGlobalPositionY = ly; }
  Float_t    GetDetectorGlobalPositionY() const {return HitGlobalPositionY;}

  void     StoreDetectorGlobalPositionZ(Float_t lz)   { HitGlobalPositionZ = lz; }
  Float_t    GetDetectorGlobalPositionZ() const {return HitGlobalPositionZ;}
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX = vx; }
  Float_t    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY = vy; }
  Float_t    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ = vz; }
  Float_t    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX = vx; }
  Float_t    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY = vy; }
  Float_t    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ = vz; }
  Float_t    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle = theta; }
  Float_t    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle = phi; }
  Float_t    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy = ekin; }
  Float_t    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy = etot; }
  Float_t    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //----------------
  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle = theta; }
  Float_t    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle = phi; }
  Float_t    GetGlobalPhiAngle() const {return GlobalPhiAngle;}


  void AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
				 Float_t XM, Float_t YM, Float_t ZM,
				 Float_t energy, Int_t type);

  void     StoreEdgeEventFlag(Int_t flag) {EdgeEventFlag = flag;};
  Int_t    GetEdgeEventFlag() {return EdgeEventFlag;};

  void     StoreOpticalPhotonCount(Int_t cnt){OpticalPhotonCount = cnt;};

  void StoreCerenkovPhotonEnergy(Double_t eng) {CerenkovPhotonEnergy.push_back(eng);};

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserCerenkov_DetectorEvent,1)

};  // end class QweakSimUserCerenkov_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_DetectorEvent.hh,v $
//      Revision 1.3  2006/01/06 20:31:24  grimm
//      Added KineticEnergy, TotalEnergy, ParticleType, and ParticleName into the root tree
//
//      Revision 1.2  2005/12/27 19:28:31  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

