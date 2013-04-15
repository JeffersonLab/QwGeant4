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

  Float_t PrimaryQ2;            ///< Momentum transfer Q^2 for this event (GeV<sup>2</sup>)
  Float_t CrossSection;         ///< Cross section weight for events with these kinematics, assuming isotropic spherical picking (isotropy = 1, see \ref isotropy)
  Float_t CrossSectionWeight;   ///< Modified cross section weight for events with these kimematics, assuming flat-theta picking (isotropy = 0, see \ref isotropy)
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
  void     StorePrimaryQ2(Float_t pq2)  { PrimaryQ2 = pq2; }
  Float_t    GetPrimaryQ2() const {return PrimaryQ2; }

  void     StoreCrossSection(Float_t cs)  {CrossSection = cs;}
  Float_t    GetCrossSection() const {return CrossSection; }

  void     StoreCrossSectionWeight(Float_t csw)  {CrossSectionWeight = csw;}
  Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }

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

