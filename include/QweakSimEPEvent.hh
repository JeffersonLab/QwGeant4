//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEvent.hh

   \author Jie Pan

*/
//=============================================================================

#ifndef QWEAKSIMEPEVENT_H
#define QWEAKSIMEPEVENT_H

// geant4 includes
#include "G4Types.hh"
#include "G4ThreeVector.hh"

// user includes
#include "QweakSimUserInformation.hh"

// user classes
class QweakSimEPEventMessenger;

class QweakSimEPEvent {

 private:
   //define target geometry parameter, 
   //TODO: these parameters will be acquired from QweakSimTarget

   static const G4double TargetLength;

   // definition of a mil = inch/1000
   static const G4double mil;
   static const G4double TargetWindowThickness;

   static const G4double M_n; //neutron mass in MeV/c^2
   static const G4double M_p;  // proton mass in MeV/c^2

   static const G4double Theta_Min;

   G4double A;  // mass number A, Al_A = 27.0
   G4double Z;  // charge number Z, Al_Z = 13.0

   G4double Mass;

   G4int TypeSetting;
   G4int ReactionType;     // 1 - LH2 elastic
                           // 2 - Al window elastic
                           // 3 - Al window quasi-elastic proton
                           // 4 - Al window quasi-elastic neutron
   G4int ReactionRegion;   // 1 - LH2 target
                           // 2 - entrance window
                           // 3 - exit window

  G4int kActiveOctantNumber;

  G4int Isotropy;
  G4double PhiAngle_Min;
  G4double PhiAngle_Max;
  G4double ThetaAngle_Min;
  G4double ThetaAngle_Max;

  G4double ThetaAngle;
  G4double PhiAngle;
  G4double myPositionZ;

  G4ThreeVector GetMomentumDirection();
  G4double ResMod507(G4int sf,G4double w2,G4double q2,G4double *xval);
  G4double Sigma_EEPrime(G4double eni,G4double eprime,G4double theta, G4double &q2);
  
  QweakSimEPEventMessenger *EventGen_Messenger;
  QweakSimUserInformation *myUserInfo;

 public:

  QweakSimEPEvent(QweakSimUserInformation* myUI);
  //QweakSimEPEvent();
  virtual ~QweakSimEPEvent();

  void SetActiveOctantNumber(G4int kaot) { kActiveOctantNumber = kaot; };
  G4int GetActiveOctantNumber( ) {return kActiveOctantNumber;};

  void SetIsotropy(G4int isot) { Isotropy = isot; };
  G4int GetIsotropy( ) {return Isotropy;};
  
  void SetThetaAngle_Min(G4double ang) {ThetaAngle_Min = ang;};
  G4double GetThetaAngle_Min() {return ThetaAngle_Min;};

  void SetThetaAngle_Max(G4double ang) {ThetaAngle_Max = ang;};
  G4double GetThetaAngle_Max() {return ThetaAngle_Max;};

  void SetPhiAngle_Min(G4double ang) {PhiAngle_Min = ang;};
  G4double GetPhiAngle_Min() {return PhiAngle_Min;};

  void SetPhiAngle_Max(G4double ang) {PhiAngle_Max = ang;};
  G4double GetPhiAngle_Max() {return PhiAngle_Max;};
  
  void  SetReactionType(G4int rt) { ReactionType = rt; TypeSetting = rt;};
  G4int GetReactionType() {return ReactionType; };

  void  SetReactionRegion(G4int rr) { ReactionRegion = rr; };
  G4int GetReactionRegion() {return ReactionRegion; };

  G4double GetVertexZ();
  void GetanEvent(G4double E_in, 
                  G4double &CrossSection, 
                  G4double &weight_n,
                  G4double &Q2,
                  G4double &E_out,
                  G4ThreeVector &MomentumDirection,
                  G4double &theta,
                  G4double &phi,
		  G4double &Asymmetry);

  G4double Elastic_Cross_Section_Proton( G4double E_in,
                                         G4double Theta,
                                         G4double &fWeightN,
                                         G4double &Q2,
                                         G4double &E_out);

  G4double Elastic_Cross_Section_Aluminum( G4double E_in,
                                           G4double Theta,
                                           G4double &fWeightN,
                                           G4double &Q2,
                                           G4double &E_out);

  G4double Quasi_Elastic_Neutron( G4double E_in,
                                  G4double Theta,
                                  G4double &fWeightN,
                                  G4double &Q2,
                                  G4double &E_out);
  
  G4double Delta_Resonance(G4double E_in,
                           G4double Theta,
                           G4double &fWeightN,
                           G4double &Q2,
                           G4double &E_out);
  
  G4double Moller_Scattering(G4double E_in, G4double theta1, 
                             G4double &E_out1, G4double &E_out2, G4double &theta2, 
                             G4double &q2, G4double &fWeightN, G4double &asymmetry);
  
  G4double GetAsymmetry_EP(G4double theta, G4double energy);
  G4double GetAsymmetry_EN(G4double theta, G4double energy);
  G4double GetAsymmetry_AL(G4double theta, G4double energy);
  G4double GetAsymmetry_Be(G4double theta, G4double energy);
  G4double GetAsymmetry_Pi(G4double Q2_pi);

};

#endif
