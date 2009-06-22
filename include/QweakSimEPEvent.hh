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

#include "cpp_include.h"
#include "Geant4_include.hh"
//#include "QweakSimUserInformation.hh"

//class QweakSimUserInformation;

class QweakSimEPEvent {

 private:
   //define target geometry parameter, 
   //TODO: these parameters will be acquired from QweakSimG4Target
   static const G4double TargetCenterPositionZ;
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

   G4int ReactionType;     // 1 - LH2 elastic
                           // 2 - Al window elastic
                           // 3 - Al window quasi-elastic proton
                           // 4 - Al window quasi-elastic neutron
   G4int ReactionRegion;   // 1 - LH2 target
                           // 2 - entrance window
                           // 3 - exit window

  G4double meanPhiAngle;
  G4double sigmaPhiAngle;
  G4double ThetaAngle_Min;
  G4double ThetaAngle_Max;

  G4double ThetaAngle;
  G4double PhiAngle;
  G4double myPositionZ;

  G4ThreeVector GetMomentumDirection();

 public:

  //QweakSimEPEvent(QweakSimUserInformation* myUI);
  QweakSimEPEvent();
  virtual ~QweakSimEPEvent();

  G4int GetReactionType() {return ReactionType; };
  G4double GetVertexZ();
  void GetanEvent(G4double E_in, 
                  G4double &CrossSection, 
                  G4double &weight_n,
                  G4double &Q2,
                  G4double &E_out,
                  G4ThreeVector &MomentumDirection,
                  G4double &theta,
                  G4double &phi);

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

};

#endif
