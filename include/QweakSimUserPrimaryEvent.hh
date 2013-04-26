//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserPrimaryEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:30:45 $
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
   \class QweakSimUserPrimaryEvent
    
   \ingroup root

   \brief Stores the PrimaryEvent information into the ROOT file for each event.

          Primary.xyz
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserPrimaryEvent_h
#define QweakSimUserPrimaryEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserPrimaryEvent : public TObject
{

private:

  Int_t   TrackID;      ///< ID of the primary track in this event
  Float_t GlobalTime;   ///< Time of primary interaction, starting 30 cm in front of the target, see \ref target_energy_loss (ns)

  /// \name Position of the primary vertex in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexPositionX;        ///< (mm)
  Float_t OriginVertexPositionY;        ///< (mm)
  Float_t OriginVertexPositionZ;        ///< (mm)
  //@}

  /// \name Direction right after the primary vertex in global coordinates
  /// The global coordinates are defined in the \ref global_coordinate_system.
  //@{
  Float_t OriginVertexMomentumDirectionX;
  Float_t OriginVertexMomentumDirectionY;
  Float_t OriginVertexMomentumDirectionZ;
  Float_t OriginVertexThetaAngle;       ///< (degrees)
  Float_t OriginVertexPhiAngle;         ///< (degrees)
  //@}

  Float_t PreScatteringKineticEnergy;   ///< Kinetic energy right before the primary vertex (after external target energy loss)
  Float_t OriginVertexKineticEnergy;    ///< Kinetic energy right after the primary vertex
  Float_t OriginVertexTotalEnergy;      ///< Total energy right after the primary vertex

  Float_t OriginVertexKinematicNu;
  Float_t OriginVertexKinematicQ2;
  Float_t OriginVertexKinematicX;
  Float_t OriginVertexKinematicW;

  Float_t BeamEnergy;

  Float_t EffectiveKinematicNu;
  Float_t EffectiveKinematicQ2;
  Float_t EffectiveKinematicX;
  Float_t EffectiveKinematicW;

  Float_t PrimaryQ2;            ///< Momentum transfer Q^2 for this event (GeV<sup>2</sup>)
  Float_t CrossSection;         ///< Cross section weight for events with these kinematics, assuming isotropic spherical picking (isotropy = 1, see \ref isotropy)
  Float_t CrossSectionWeight;   ///< Modified cross section weight for events with these kimematics, assuming flat-theta picking (isotropy = 0, see \ref isotropy)
  Float_t CrossSectionBornTotal;
  Float_t CrossSectionBornInelastic;
  Float_t CrossSectionBornQE;
  Float_t CrossSectionRadTotal;
  Float_t CrossSectionRadElastic;
  Float_t CrossSectionRadQE;
  Float_t CrossSectionRadDIS;
  Float_t Asymmetry;            ///< Asymmetry for events with these kinematics

  Int_t   PrimaryEventNumber;   ///< The primary event number (increments by two due to target energy loss simulation)

  Int_t   ReactionType;         ///< The \ref reaction_type used for this event, e.g. elastic ep = 1, e+p -> e'+p+pi = 2
  Int_t   PDGcode;              ///< The \ref Lund_type of the primary particle, e.g. electron = 11

  // various energy losses at the target
  Float_t dEIonIn, dEIonOut, dEIonTot;
  Float_t dEBremIn, dEBremOut, dEBremTot;
  Float_t dEMscIn, dEMscOut, dEMscTot;
  Float_t dETotIn, dETotOut, dETot;

public:
  
  // Constructor
  QweakSimUserPrimaryEvent();
  // Destructor 
  virtual ~QweakSimUserPrimaryEvent();

  void     Initialize();

  void     StoreTrackID(Int_t tid)    { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}

  void     StoreGlobalTime(Float_t gtime) { GlobalTime = gtime; }
  Float_t    GetGloablTime()  const {return GlobalTime;}

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
  void     StorePreScatteringKineticEnergy(Float_t ekin) { PreScatteringKineticEnergy = ekin; }
  Float_t    GetPreScatteringKineticEnergy() const {return PreScatteringKineticEnergy;}
  
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy = ekin; }
  Float_t    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy = etot; }
  Float_t    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //-----------------
  void     StoreOriginVertexKinematicNu(Float_t nu) { OriginVertexKinematicNu = nu; }
  Float_t    GetOriginVertexKinematicNu() const {return OriginVertexKinematicNu;}
  
  void     StoreOriginVertexKinematicQ2(Float_t q2) { OriginVertexKinematicQ2 = q2; }
  Float_t    GetOriginVertexKinematicQ2() const {return OriginVertexKinematicQ2;}
  
  void     StoreOriginVertexKinematicX(Float_t x) { OriginVertexKinematicX = x; }
  Float_t    GetOriginVertexKinematicX() const {return OriginVertexKinematicX;}
  
  void     StoreOriginVertexKinematicW(Float_t w) { OriginVertexKinematicW = w; }
  Float_t    GetOriginVertexKinematicW() const {return OriginVertexKinematicW;}
  
  //-----------------
  void     StoreBeamEnergy(Float_t energy) { BeamEnergy = energy; }
  Float_t    GetBeamEnergy() const {return BeamEnergy;}
  
  //-----------------
  void     StoreEffectiveKinematicNu(Float_t nu) { EffectiveKinematicNu = nu; }
  Float_t    GetEffectiveKinematicNu() const {return EffectiveKinematicNu;}
  
  void     StoreEffectiveKinematicQ2(Float_t q2) { EffectiveKinematicQ2 = q2; }
  Float_t    GetEffectiveKinematicQ2() const {return EffectiveKinematicQ2;}
  
  void     StoreEffectiveKinematicX(Float_t x) { EffectiveKinematicX = x; }
  Float_t    GetEffectiveKinematicX() const {return EffectiveKinematicX;}
  
  void     StoreEffectiveKinematicW(Float_t w) { EffectiveKinematicW = w; }
  Float_t    GetEffectiveKinematicW() const {return EffectiveKinematicW;}
  
  //-----------------
  void     StorePrimaryQ2(Float_t pq2)  { PrimaryQ2 = pq2; }
  Float_t    GetPrimaryQ2() const {return PrimaryQ2; }

  void     StoreCrossSection(Float_t cs)  {CrossSection = cs;}
  Float_t    GetCrossSection() const {return CrossSection; }

  void     StoreCrossSectionWeight(Float_t csw)  {CrossSectionWeight = csw;}
  Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }
  
  //-----------------
  void     StoreCrossSectionBornTotal(Float_t cs)  {CrossSectionBornTotal = cs;}
  Float_t    GetCrossSectionBornTotal() const {return CrossSectionBornTotal; }

  void     StoreCrossSectionBornInelastic(Float_t cs)  {CrossSectionBornInelastic = cs;}
  Float_t    GetCrossSectionBornInelastic() const {return CrossSectionBornInelastic; }

  void     StoreCrossSectionBornQE(Float_t cs)  {CrossSectionBornQE = cs;}
  Float_t    GetCrossSectionBornQE() const {return CrossSectionBornQE; }

  void     StoreCrossSectionRadTotal(Float_t cs)  {CrossSectionRadTotal = cs;}
  Float_t    GetCrossSectionRadTotal() const {return CrossSectionRadTotal; }

  void     StoreCrossSectionRadElastic(Float_t cs)  {CrossSectionRadElastic = cs;}
  Float_t    GetCrossSectionRadElastic() const {return CrossSectionRadElastic; }

  void     StoreCrossSectionRadQE(Float_t cs)  {CrossSectionRadQE = cs;}
  Float_t    GetCrossSectionRadQE() const {return CrossSectionRadQE; }

  void     StoreCrossSectionRadDIS(Float_t cs)  {CrossSectionRadDIS = cs;}
  Float_t    GetCrossSectionRadDIS() const {return CrossSectionRadDIS; }

  //-----------------
  void     StoreAsymmetry(Float_t asym)  {Asymmetry = asym;}
  Float_t    GetAsymmetry() const {return Asymmetry; }

  void     StorePrimaryEventNumber(Int_t pen)    { PrimaryEventNumber = pen; }
  Int_t      GetPrimaryEventNumber() const {return PrimaryEventNumber; }

  void     StoreReactionType(Int_t rt)  { ReactionType = rt; }
  Int_t      GetReactionType() const {return ReactionType; }

  void     StorePDGcode(Int_t code)  { PDGcode = code; }
  Int_t      GetPDGcode() const {return PDGcode; }

  // store various Elosses at the target
  void StoredEIonIn(Float_t dE){dEIonIn=dE;}
  void StoredEIonOut(Float_t dE){dEIonOut=dE;}
  void StoredEIonTot(Float_t dE){dEIonTot=dE;}
  void StoredEBremIn(Float_t dE){dEBremIn=dE;}
  void StoredEBremOut(Float_t dE){dEBremOut=dE;}
  void StoredEBremTot(Float_t dE){dEBremTot=dE;}
  void StoredEMscIn(Float_t dE){dEMscIn=dE;}
  void StoredEMscOut(Float_t dE){dEMscOut=dE;}
  void StoredEMscTot(Float_t dE){dEMscTot=dE;}
  void StoredETotIn(Float_t dE){dETotIn=dE;}
  void StoredETotOut(Float_t dE){dETotOut=dE;}
  void StoredETot(Float_t dE){dETot=dE;}
  ///

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserPrimaryEvent,1)

};  // end class QweakSimUserPrimaryEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

