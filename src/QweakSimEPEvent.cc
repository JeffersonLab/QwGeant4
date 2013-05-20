//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEvent.cc

   \author Jie Pan

*/
//=============================================================================

#include "QweakSimEPEvent.hh"

// geant4 includes
#include "Randomize.hh"

// user includes
#include "QweakSimEPEventMessenger.hh"
#include "QweakSimUserInformation.hh"

#include "wiser_pion.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   const G4double QweakSimEPEvent::M_n = 939.5656*MeV; //neutron mass in MeV/c^2
   const G4double QweakSimEPEvent::M_p = 938.2796*MeV;  // proton mass in MeV/c^2

   const G4double QweakSimEPEvent::Theta_Min = 1.745329E-4;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEvent::QweakSimEPEvent( QweakSimUserInformation* myUI)
{
  G4cout << "###### Calling QweakSimEPEvent::QweakSimEPEvent () " << G4endl;

  Isotropy = 1;
  
  PhiAngle_Min = -16.0*degree;
  PhiAngle_Max =  16.0*degree;

  ThetaAngle_Min =  4.0*degree;
  ThetaAngle_Max = 13.5*degree;

  EPrime_Min = 0.4*GeV;
  EPrime_Max = 0.4*GeV;
  
  BeamEnergy = 1.16*GeV;

  TypeSetting = 1;
  ReactionType = 1;
  ReactionRegion = 1;
  kActiveOctantNumber = 0;  //default octant all, choose from [0,8]

  myUserInfo = myUI;
  EventGen_Messenger = new QweakSimEPEventMessenger(this);

  G4cout << "###### Leaving QweakSimEPEvent::QweakSimEPEvent () " << G4endl;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEvent::~QweakSimEPEvent()
{

  G4cout << "###### Calling QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;

 if( EventGen_Messenger) delete EventGen_Messenger;

  G4cout << "###### Leaving QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::GetVertexZ()
{
  /** \page reaction_region reaction region
   * There are a number of pre-set reaction regions.  These do not automatically set the
   * reaction type, so don't expect aluminum exit window simulations by setting reaction
   * region to 3...
   * \li 1: target
   * \li 2: front entrance window
   * \li 3: back exit window
   * \li else: target
   */

  if (ReactionRegion == 1) // target
    myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*(myUserInfo->TargetLength);

  else if (ReactionRegion == 2) // front entrance window
    myPositionZ =  myUserInfo->TargetCenterPositionZ - 0.5*(myUserInfo->TargetLength)
                   - (myUserInfo->TargetEntranceWindowThickness)*G4UniformRand();

  else if(ReactionRegion == 3) // back exit window
    myPositionZ =  myUserInfo->TargetCenterPositionZ + 0.5*(myUserInfo->TargetLength)
                   + (myUserInfo->TargetExitWindowNippleThickness)*G4UniformRand();

  else
    myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*(myUserInfo->TargetLength); //default region

  return myPositionZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector QweakSimEPEvent::GetMomentumDirection()
{

    // Generate flat phi distribution
    G4double PhiAngle =  PhiAngle_Min + G4UniformRand()*(PhiAngle_Max - PhiAngle_Min);
    // If active octant = 0, all octants are used
    if (kActiveOctantNumber == 0) PhiAngle += (G4RandFlat::shootInt(8) * 45.0 * degree);
    G4double cosPhi = cos(PhiAngle);
    G4double sinPhi = sin(PhiAngle);


    /** \page isotropy isotropy
     * The cross section used for weighting Monte Carlo events depends on how those
     * events are thrown.  There are two options in the Qweak Monte Carlo:
     * \li isotropy = 0: flat theta distribution, requires a modified weight for the cross section -> QweakSimUserPrimaryEvent::CrossSectionWeight
     * \li isotropy = 1: uniform spherical theta/phi distribution, use regular cross section -> QweakSimUserPrimaryEvent::CrossSection
     * \li else: not defined
     */

    G4double cosTheta;
    G4double sinTheta;

    if (Isotropy == 0) {
      // Generate flat theta distribution
      G4double ThetaAngle = ThetaAngle_Min + G4UniformRand()*(ThetaAngle_Max - ThetaAngle_Min);
      cosTheta = cos(ThetaAngle);
      sinTheta = sin(ThetaAngle);

    } else if (Isotropy == 1) {
      // Generate uniform distribution on spherical surface. See for example
      // http://hypernews.slac.stanford.edu/HyperNews/geant4/get/particles/31/2.html
      // or more generally http://mathworld.wolfram.com/SpherePointPicking.html
      G4double cosThetaMax = cos(ThetaAngle_Max);
      G4double cosThetaMin = cos(ThetaAngle_Min);
      cosTheta = cosThetaMin + G4UniformRand()*(cosThetaMax - cosThetaMin);
      sinTheta = sqrt(1. - cosTheta * cosTheta);

    } else {
      G4cerr << "Warning: unkown isotropy type.  Pick 0 or 1." << G4endl;
    }
    

    G4double ux = sinTheta * cosPhi;
    G4double uy = sinTheta * sinPhi;
    G4double uz = cosTheta;
    G4ThreeVector myNormMomentum(ux,uy,uz);
       
    // Rotate the momentum to the active octant (if octant = 0 all octants are used)
    if (kActiveOctantNumber > 0)
      myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

    return myNormMomentum; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::GetanEvent(G4double E_in, 
                                 std::vector< G4double > &fCrossSection, 
                                 G4double &fWeightN,
                                 G4double &Q2,
                                 G4double &E_out,
                                 G4ThreeVector &OutgoingMomentumDirection,
                                 G4double &theta,
                                 G4double &phi,
				 G4double &Asymmetry)
{

    // incoming momentum
    G4ThreeVector IncomingMomentumDirection = myUserInfo->GetNormMomentum();
    
    G4double IncomingMomentumDirectionMag = IncomingMomentumDirection.mag();

    
    // outgoing momentum
    OutgoingMomentumDirection = GetMomentumDirection();
    theta = OutgoingMomentumDirection.theta()/degree;
    phi = OutgoingMomentumDirection.phi()/degree;
    
    // relative theta angle
    
    G4double dot = OutgoingMomentumDirection.dot(IncomingMomentumDirection);
    
    G4double RelativeThetaAngle = acos(dot/IncomingMomentumDirectionMag);    


   if(ReactionType==0 || TypeSetting==0) // combination of all process, Random int [1,8]
      {
	TypeSetting = 0;
        ReactionType = G4int(G4UniformRand()*7.0+1.0+0.5);
      }
   else
      {
        TypeSetting = ReactionType;
      }

   //std::cout<<"ReactionType: "<<ReactionType<<", TypeSetting: "<<TypeSetting<<std::endl;

   /** \page reaction_type reaction type
    * There are a number of reaction types implemented in the Qweak Monte Carlo:
    * \li 0: random selection of some of these reaction types
    * \li 1: elastic scattering from hydrogen (see QweakSimEPEvent::Elastic_Cross_Section_Proton)
    * \li 2: elastic scattering from aluminum (see QweakSimEPEvent::Elastic_Cross_Section_Aluminum)
    * \li 3: quasi-elastic scattering from proton in aluminum (see QweakSimEPEvent::Elastic_Cross_Section_Proton)
    * \li 4: quasi-elastic scattering from neutron in aluminum (see QweakSimEPEvent::Quasi_Elastic_Neutron)
    * \li 5: Delta resonance (see QweakSimEPEvent::Delta_Resonance)
    * \li 6: Moller scattering (see QweakSimEPEvent::Moller_Scattering)
    * \li 7: radiative scattering from hydrogen (3.35 GeV) (see QweakSimEPEvent::Radiative_Cross_Section_Proton)
    * \li 8: Quasielastic scattering from aluminum using the Bosted fit
    */

   if(ReactionType==1) //LH2 target
      {
       A = 1.0;
       Z = 1.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection[0] = Elastic_Cross_Section_Proton(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }
      
   else if(ReactionType==2) // Aluminum window
      {
       A = 27.0;
       Z = 13.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection[0] = Elastic_Cross_Section_Aluminum(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_AL(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==3) // Aluminum window quasi-elastic proton (assume free proton)
      {
       A = 1.0;
       Z = 1.0;   
       Mass = M_p;    
       fCrossSection[0] = Elastic_Cross_Section_Proton(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==4) // Aluminum window quasi-elastic neutron (assume free neutron)
      {
       A = 1.0;
       Z = 1.0;   // Z needs to be set to 1 for neutron quasi elastic scattering
       Mass = M_n;    
       fCrossSection[0] = Quasi_Elastic_Neutron(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EN(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==5) // Delta resonances
      {
       fCrossSection[0] = Delta_Resonance(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       //std::cout<<E_in<<" "<<ThetaAngle/degree<<" "<<fWeightN<<" "<<Q2<<" "<<E_out<<std::endl;
       Asymmetry = GetAsymmetry_Pi(Q2);
      }
   else if(ReactionType==6) // Moller scattering
      {
	//  Peiqing, Dec 12, 2011
	//  Small angle recoil electrons are directly dumped for now.
       G4double E_recoil;
       G4double ThetaRecoil;
       fCrossSection[0] = Moller_Scattering(E_in, RelativeThetaAngle, E_out, 
					 E_recoil, ThetaRecoil, 
                                         Q2, fWeightN, Asymmetry);
      }      
   else if(ReactionType==7) //LH2 target, radiative cross section 3.35 GeV
      {
       fCrossSection = Radiative_Cross_Section_Proton(myUserInfo->GetBeamEnergy(), RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }
   else if(ReactionType==8) // Quasielastic Bosted - Aluminum
      {
         Z = 13;
         A = 27;
         fCrossSection[0] = Quasi_Elastic_Bosted(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2,
                                              E_out);
      }
	
   else if(ReactionType==88) //--- LH2 target, pion photo-production cross section 3.35 GeV
   {
       fCrossSection[0] = Pion_PhotoProduction(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in); //--- use the elastic asymmetry for now
   }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca
//     calculate proton cross sections using the dipole fits to the form factors.
//     Angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.

G4double QweakSimEPEvent::Elastic_Cross_Section_Proton(G4double E_in,
                                                       G4double Theta,
                                                       G4double &fWeightN,
                                                       G4double &Q2,
                                                       G4double &E_out)
{
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double mu = 2.793;
      G4double Z = 1.0;
      G4double A = 1.0;
      G4double M = M_p*A;
      G4double hbarc = 197.3269718;  // in MeV fm 
      G4double alpha = 1.0/137.035999074;
      G4double CC = hbarc*alpha/2.0;  // 0.719982242379

//    E_in units is MeV

      if (Theta<Theta_Min)
         Theta = Theta_Min;

      G4double CTH = cos(Theta/2.);
      G4double STH = sin(Theta/2.);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
      Q2 = 4.0*E_in*E_out*STH*STH;   // MeV^2
      G4double tau = Q2/4.0/M/M;
//    Mott scatering cross-section, including recoil correction
      G4double CrossSection = (Z*CC/E_in*CTH/STH/STH)*(Z*CC/E_in*CTH/STH/STH)/ETA;
//    Units: ub/sr
      G4double Mott = CrossSection*10000.0;
//    Cross section
      G4double GEP_DIPOLE = 1.0/(1.0+Q2/1.E6/Lamda_2)/(1.0+Q2/1.E6/Lamda_2);
      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
      G4double FAC = 1.0/(1.0+tau);

      G4double Sigma_Dipole = Mott*(GEP_DIPOLE*GEP_DIPOLE*FAC+tau*GMP_DIPOLE*GMP_DIPOLE*(FAC+2.*T2THE));
      fWeightN = Sigma_Dipole*sin(Theta);
      return Sigma_Dipole;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca
//     calculate Aluminum elastic cross sections

G4double QweakSimEPEvent::Elastic_Cross_Section_Aluminum(G4double E_in,
                                                         G4double Theta,
                                                         G4double &fWeightN,
                                                         G4double &Q2,
                                                         G4double &E_out)
{
      G4double Theta_Min = 1.745329E-4;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double Z = 13.0;
      G4double A = 27.0;
      G4double M = M_p*A;

//    harmonic oscillator well parameter a0 ~1.76 fm 
      G4double a = 2.98; //unit: fm
      G4double ap = sqrt(0.427);   //unit: fm 
      G4double a0 = sqrt((a*a-1.5*ap*ap)/(3.5-10/Z-1.5/A)); 

      G4double Q = 14.6;  //unit fm^(-2)
      G4double J = 5.0/2.0; 

      G4double gamma = 2.792847351; //This is the magnetic moment
//    G4double Omega = -3/2*(1+2*gamma)*a0*a0; 
//    G4double Gamma = 15/4*gamma*pow(a0,4);
      G4double mu = 3.69;  // This is NOT the magnetic moment
      G4double Omega_mu = -6.36; // Omega/mu 
      G4double Gamma_mu = 20.7;  // Gamma/mu

      if (Theta<Theta_Min)
           Theta = Theta_Min;

//    E_in unit is MeV, q2 unit is fm^(-2)   
      G4double CTH = cos(Theta/2.0);
      G4double STH = sin(Theta/2.0);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
   
      Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2
      G4double q2 = Q2/1000000*(1.0/0.197)*(1.0/0.197);  //convert MeV^2 into fm^(-2)
      G4double x = (1.0/4.0)*q2*a0*a0;

//  std::ofstream EventDataFile("Event.dat", std::ios::app);
//  EventDataFile<<"E_f="<<E_f<<"  q2="<<q2<<"  "<<"x="<<x<<G4endl;

//    Electric form factor (data fit)
      G4double F0 = (1.0/Z)*( Z-4.0/3.0*(Z-5.0)*x+4.0/15.0*(Z-8.0)*x*x)*exp(-x);
      G4double F2 = (1.0-2.0/7.0*x)*exp(-x);
      G4double Fe_2 = F0*F0+(7.0/450.0)*q2*q2*(Q*Q/Z/Z)*F2*F2;

//  EventDataFile<<"F0="<<F0<<"  "<<"F2="<<F2<<"  "<<"Fe_2="<<Fe_2<<G4endl;

//    Magnetic form factor (theoretical)
      G4double Fm1 = (1.0-2.0/5.0*(1.0+2.0*gamma)/(1.0+gamma/2.0)*x+6.0/35.0*gamma*x*x/(1.0+gamma/2.0))*exp(-x);
      G4double Fm3 = (1.0-2.0/3.0*gamma*x/(1.0+2.0*gamma))*exp(-x);
      G4double Fm5 = exp(-x);
      G4double Fm_2 = Fm1*Fm1+(4.0/525.0)*pow(q2*Omega_mu*Fm3,2)+(2.0/33075.0)*pow(q2,4)*pow(Gamma_mu*Fm5,2);

//  EventDataFile<<"Fm1="<<Fm1<<"  "<<"Fm3="<<Fm3<<"  "<<"Fm5="<<Fm5<<"  "<<"Fm_2="<<Fm_2<<G4endl;

//    form factor square
      G4double F_2 = Z*Z*Fe_2+(1.0+2.0*T2THE)*mu*mu/3.0*(J+1.0)/J*q2/4.0/pow((M_p/0.197),2)*Fm_2;

//  EventDataFile<<"F_2="<<F_2<<"  "<<G4endl;

//    cross section units: ub/sr
//    G4double SigmaMott = ((0.72/E_in)*cos(Theta/2)/(sin(Theta/2)^2))^2 /( 1+2*E_in/M*(sin(Theta/2)^2))*10000 ;
      G4double SigmaMott = pow(((0.72/E_in)*CTH/(STH*STH)),2)/(1+2*E_in/M*STH*STH)*10000 ;

//  EventDataFile<<"SigmaMott="<<SigmaMott<<"  "<<"SigmaMott*F_2="<<SigmaMott*F_2<<"  "<<"weight_n="<<SigmaMott*F_2*sin(Theta)<<G4endl;
      G4double Xsect = SigmaMott*F_2;
      fWeightN = Xsect*sin(Theta);
      return Xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//jpan@nuclear.uwinnipeg.ca Sat Apr 18 11:28:18 CDT 2009
//     In this subroutine units are MeV

G4double QweakSimEPEvent::Quasi_Elastic_Neutron(G4double E_in,
                                                G4double Theta,
                                                G4double &fWeightN,
                                                G4double &Q2,
                                                G4double &E_out)
{
//  cout<<"===>>>>Calling Quasi_Elastic_Neutron"<<endl;
      G4double Theta_Min = 1.745329E-4;
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
//      G4double mu = 2.793;
      G4double mu_n = -1.91;
      G4double Z = 1.0;
//      G4double A = 1.0;
      G4double M = M_p;

//    E_in units is MeV
      
      if (Theta<Theta_Min)
         Theta = Theta_Min;

      G4double CTH = cos(Theta/2.0);
      G4double STH = sin(Theta/2.0);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
//    MeV^2
      Q2 = 4.*E_in*E_out*STH*STH;
      G4double tau = Q2/4./M/M;
//    Mott scatering
      G4double CrossSection = (Z*0.72/E_in*CTH/STH/STH)*(Z*0.72/E_in*CTH/STH/STH)/ETA;
//    Units: ub/sr
      G4double Mott = CrossSection*10000.0;

//    Cross section
      G4double GEP_DIPOLE = 1.0/(1.0+Q2/1.E6/Lamda_2)*(1.0+Q2/1.E6/Lamda_2);
//      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
      G4double GEn_DIPOLE = 0.0;
      G4double GMn_DIPOLE = GEP_DIPOLE*mu_n;
      G4double FAC = 1.0/(1.0+tau);

//      G4double Sigma_Dipole_p = Mott*(GEP_DIPOLE*GEP_DIPOLE*FAC+tau*GMP_DIPOLE*GMP_DIPOLE*(FAC+2.*T2THE));
      G4double Sigma_Dipole_n = Mott*(GEn_DIPOLE*GEn_DIPOLE*FAC+tau*GMn_DIPOLE*GMn_DIPOLE*(FAC+2.*T2THE));
//      G4double Sigma_Dipole = Z*Sigma_Dipole_p + (A-Z)*Sigma_Dipole_n;

//  cout<<"===>>>>leaving Quasi_Elastic_Neutron"<<endl;
      fWeightN = Sigma_Dipole_n*sin(Theta);
      return Sigma_Dipole_n;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Inelastic generator interface
// Peiqing, Nov 30,2011

G4double QweakSimEPEvent::Delta_Resonance(G4double E_in,
                                          G4double Theta,
                                          G4double &fWeightN,
                                          G4double &Q2,
                                          G4double &E_out)
{
  G4double E_beam = 1165.0;    // maximum energy (beam energy) in MeV
  G4double M_electron = 0.511;  // minimum energy (electron mass) in MeV
  
  // G4double Theta_Min = 1.745329E-4;
  if (Theta<Theta_Min)
      Theta = Theta_Min;

  // Generate flat energy distribution of outgoing electron      
  E_out =  M_electron + G4UniformRand()*(E_beam - M_electron);

  // TODO: total energy phase space should be reduced to improve the efficiency.
  G4double xsect = Sigma_EEPrime(E_in/1000.0, E_out/1000.0, Theta, Q2);  // ub/sr/GeV
  Q2 = Q2*1e6;  // convert to MeV^2 for Q2

  //std::cout<<"Q2="<<Q2<<" xsect="<<xsect<<std::endl;
  xsect = xsect*(E_beam - M_electron)/1000.0;
  //std::cout<<"xsect*1.165 = "<<xsect<<std::endl;
  fWeightN = xsect*sin(Theta);
 
  if(xsect == 0)  // if E > E_max, reject the event
  {
     E_out = 0.0;
     Q2 = 0.0;
  }
  
  return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::Sigma_EEPrime(G4double eni, G4double eprime, G4double theta, G4double &q2)
{

// Peiqing, Nov 28, 2011
// This is adopted from QWGEANT3 SUBROUTINE SIGMA_EEPRIME (ENI,EPRIME,THETA,WVAL,SIGMA_EEP)
// 
//	Calculates the differential cross section for inelastic
//	ep scattering into unit solid angle and scattered
//	electron energy EPRIME.  The cross section is
//	returned in microbarns/sr/GeV.

      G4double w2,xval1[51],xvalL[51];
      G4double sigT,sigL,epsilon;
      G4int i;

      G4double t2,epmax,xneu,gamma;
 
      G4double mp = 0.9382727;
      G4double mp2 = mp*mp;   
      G4double pi = 3.141593;
      G4double alpha = 1.0/137.036;
      G4double mpion = 0.135;
    
      G4double xval[101]={ 0,
       0.12286E+01,0.15200E+01,0.15053E+01,0.16960E+01,0.16466E+01,
       0.14055E+01,0.12247E+00,0.22000E+00,0.84591E-01,0.90400E-01,
       0.16956E+00,0.29002E+00,0.74046E+01,0.65122E+01,0.58506E+01,
       0.16990E+01,0.45729E+01,0.53546E+03,-.97628E+03,0.82539E+05,
       0.29494E+01,0.20352E+01,0.12422E+00,0.19560E+01,0.22333E+01,
       -.32484E+00,0.24212E+00,0.57737E-01,0.30497E+01,0.63111E+01,
       0.37579E+00,0.41100E+01,0.20668E-01,0.45490E+03,0.54493E-01,
       0.22565E+01,0.40369E+01,0.43734E+00,0.65625E+00,0.36182E+00,
       0.55216E-01,0.41789E+00,0.18104E+00,0.91306E+00,0.18116E+01,
       0.24152E+03,0.19329E+01,0.38000E+00,0.28732E+01,-.53116E+00,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.00000E+00,0.00000E+00,0.99495E+01,0.70370E-02,0.16172E+01,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.20782E+05,0.79523E+04,0.54933E+00,0.00000E+00,0.68629E+01,
       0.10369E+01,0.88112E+00,0.00000E+00,0.35659E+03,0.20281E-02,
       0.40336E+02,0.00000E+00,0.45242E+00,0.20000E-01,0.28691E+00,
       0.00000E+00,0.25115E+03,0.10663E+01,0.55422E+01,0.30350E+00,
       0.10541E+01,0.20527E+01,0.00000E+00,0.00000E+00,0.13055E+02,
       0.27997E+01,0.39546E+00,0.46372E+00,0.49972E+01,0.00000E+00};

// Check that we are not above maximum allowed E assuming threshold W=Mp+Mpi
      t2 = theta/2.0;
      G4double sin_t2 = sin(t2);
      G4double tan_t2 = tan(t2);
      G4double sin2_t2 = sin_t2*sin_t2;
      G4double tan2_t2 = tan_t2*tan_t2;
      G4double sigma_eep = 0.0;
      epmax = eni-mpion*(1.0+0.5*mpion/mp);
      epmax = epmax/(1.0+(2.0*eni/mp)*sin2_t2);
      if (eprime>=epmax) 
        return 0; 

// Calculate Q**2, W**2, epsilon, gamma
      q2 = 4.0*eni*eprime*sin2_t2;
      xneu = eni-eprime;
      w2 = mp2 + 2.0*mp*xneu - q2;
      epsilon = 1.0/(1.0+2.0*(1.0+xneu*xneu/q2)*tan2_t2);
      gamma = alpha*eprime*(w2-mp2)/((2.0*pi)*(2.0*pi));
      gamma = gamma/(q2*mp*eni*(1.0-epsilon));
      // wval = sqrt(w2);
      
      for (i=1;i<=50;i++)
      {
        xval1[i] = xval[i];
        xvalL[i] = xval[50+i];
        if(i<=12) 
	  xvalL[i] = xval1[i];
      }
      
      xvalL[43] = xval1[47];
      xvalL[44] = xval1[48];
      xvalL[50] = xval1[50];
 
      sigT = ResMod507(1,w2,q2,&xval1[0]);
      sigL = ResMod507(2,w2,q2,&xvalL[0]);
      sigma_eep=sigT+epsilon*sigL;
      sigma_eep=sigma_eep*gamma;

      return sigma_eep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4double QweakSimEPEvent::ResMod507(G4int sf, G4double w2, G4double q2, G4double* xval)
{
      G4double xb,mass[8],width[8];
      G4double height[8],rescoef[7][5];
      G4double nr_coef[4][5],sigr[8],sig_nr;
      G4double intwidth[8],k,kcm,kr[8],kcmr[8],ppicm,ppi2cm;
      G4double petacm,ppicmr[8],ppi2cmr[8],petacmr[8],epicmr[8],epi2cmr[8];
      G4double eetacmr[8],epicm,epi2cm,eetacm,br[8][4],ang[8];
      G4double pgam[8],pwid[8][4],x0[8],q20;
      G4double sig_res,t,xpr[3],m0;
      G4int i,j,num;

      G4double xt,p1,p2,p3;

      G4double mp = 0.9382727;
      G4double mpi = 0.135;
      G4double meta = 0.547;
      G4double mp2 = mp*mp;
      G4double w = sqrt(w2);
      //wdif[1] = w - (mp + mpi);
      //wdif[2] = w - (mp + 2.*mpi);

      m0 = 0.125;
      if(sf==2) 
	m0 = xval[49];

      if(sf==1) 
      {
        q20 = 0.05;
      }
      else
      {
        q20 = 0.300;
      }
   
//   single pion branching ratios
      br[1][1] = 1.0;      //   P33(1232)       
      br[2][1] = 0.45;     //   S11(1535)   
      br[3][1] = 0.65;     //   D13(1520)
      br[4][1] = 0.65;     //   F15(1680)
      br[5][1] = 0.4;      //   S11(1650)
      br[6][1] = 0.65;     //   P11(1440) roper 
      br[7][1] = 0.50;     //   F37(1950)

//  eta branching ratios
      br[1][3] = 0.0;      // !!!  P33(1232)
      br[2][3] = 0.45;     // !!!  S11(1535) 
      br[3][3] = 0.0;      // !!!  D13(1520)
      br[4][3] = 0.0;      // !!!  F15(1680)
      br[5][3] = 0.1;      // !!!  S11(1650)
      br[6][3] = 0.0;      // !!!  P11(1440) roper   
      br[7][3] = 0.0;      // !!!  F37(1950)

//  2-pion branching ratios
      for (i=1;i<=7;i++)
      {
        br[i][2] = 1.-br[i][1]-br[i][3];
      }

//   Meson angular momentum
      ang[1] = 1.;      //  P33(1232)
      ang[2] = 0.;      //  S11(1535)
      ang[3] = 2.;      //  D13(1520)
      ang[4] = 3.;      //  F15(1680)
      ang[5] = 0.;      //  S15(1650)
      ang[6] = 1.;      //  P11(1440) roper   
      ang[7] = 3.;      //  F37(1950)

      for( i=1;i<=7;i++)     // resonance damping parameter
        {
	  x0[i] = 0.145;
	}

      x0[1] = 0.130;

      for (i=1;i<=7;i++)
      {
        br[i][2] = 1.-br[i][1]-br[i][3];
      }         
    
      // dip = 1./((1.+q2/0.71)*(1.+q2/0.71));         //  Dipole parameterization
      // mon = 1./(1.+q2/0.71);

      xb = q2/(q2+w2-mp2);
      xpr[1] = 1.+(w2-(mp+mpi)*(mp+mpi))/(q2+q20);
      xpr[1] = 1./xpr[1];
      xpr[2] = 1.+(w2-(mp+mpi+mpi)*(mp+mpi+mpi))/(q2+q20);
      xpr[2] = 1./xpr[2];

      t = log(log((q2+m0)/0.330*0.330)/log(m0/0.330*0.330));

//    Calculate kinematics needed for threshold Relativistic B-W

      k = (w2 - mp2)/2./mp;
      kcm = (w2-mp2)/2./w;

      epicm = (w2 + mpi*mpi -mp2 )/2./w;
      ppicm = sqrt(fmax(0.0,(epicm*epicm - mpi*mpi)));
      epi2cm = (w2 + (2.*mpi)*(2.*mpi) -mp2 )/2./w;
      ppi2cm = sqrt(fmax(0.0,(epi2cm*epi2cm - (2.*mpi)*(2.*mpi))));
      eetacm = (w2 + meta*meta -mp2 )/2./w;
      petacm =  sqrt(fmax(0.0,(eetacm*eetacm - meta*meta)));

      num = 0;

      for (i=1;i<=6;i++)            //  Read in resonance masses
      {
        num = num + 1;
        mass[i] = xval[i];
      }
      
      for (i=1;i<=6;i++)            //  Read in resonance widths
      {
	num = num + 1;
        intwidth[i] = xval[num];
        width[i] = intwidth[i];
      }

      if(sf==2)         //  Put in 4th resonance region 
      {
        mass[7] = xval[43];
        intwidth[7] = xval[44];
        width[7] = intwidth[7];
      }
      else
      {
        mass[7] = xval[47];
        intwidth[7] = xval[48];
        width[7] = intwidth[7];
      }

      for (i=1;i<=7;i++)
      {
        kr[i] = (mass[i]*mass[i]-mp2)/2./mp;
        kcmr[i] = (mass[i]*mass[i]-mp2)/2./mass[i];
        epicmr[i] = (mass[i]*mass[i] + mpi*mpi -mp2 )/2./mass[i];
        ppicmr[i] = sqrt(fmax(0.0,(epicmr[i]*epicmr[i] - mpi*mpi)));
        epi2cmr[i] = (mass[i]*mass[i] + (2.*mpi)*(2.*mpi) -mp2 )/2./mass[i];
        ppi2cmr[i] = sqrt(fmax(0.0,(epi2cmr[i]*epi2cmr[i] - (2.*mpi)*(2.*mpi))));
        eetacmr[i] = (mass[i]*mass[i] + meta*meta -mp2 )/2./mass[i];
        petacmr[i] =  sqrt(fmax(0.0,(eetacmr[i]*eetacmr[i] - meta*meta)));

        // Calculate partial widths
        pwid[i][1] = intwidth[i]*pow(ppicm/ppicmr[i],(2.*ang[i]+1.))
                     *pow((ppicmr[i]*ppicmr[i]+x0[i]*x0[i])/(ppicm*ppicm+x0[i]*x0[i]),ang[i]);
        // 1-pion decay mode

        pwid[i][2] = intwidth[i]*pow(ppi2cm/ppi2cmr[i],(2.*ang[i]+4.))
                     *pow((ppi2cmr[i]*ppi2cmr[i]+x0[i]*x0[i])/(ppi2cm*ppi2cm+x0[i]*x0[i]),(ang[i]+2));   
        // 2-pion decay mode

        pwid[i][2] = w/mass[i]*pwid[i][2];
        pwid[i][3] = 0.;         // !!!  eta decay mode

        if(i==2 || i==5) 
	{
          pwid[i][3]=intwidth[i]*pow(petacm/petacmr[i],(2.*ang[i]+1.))
	            *pow((petacmr[i]*petacmr[i]+x0[i]*x0[i])/(petacm*petacm+x0[i]*x0[i]),ang[i]);
          // eta decay only for S11's 
	}

        pgam[i] = (kcm/kcmr[i])*(kcm/kcmr[i])*(kcmr[i]*kcmr[i]+x0[i]*x0[i])/(kcm*kcm+x0[i]*x0[i]);
        pgam[i] = intwidth[i]*pgam[i];
        width[i] = br[i][1]*pwid[i][1]+br[i][2]*pwid[i][2]+br[i][3]*pwid[i][3];
      }
 //    End resonance kinematics and Widths calculations

 //    Begin resonance Q^2 dependence calculations         
      for (i=1;i<=6;i++)
      {
        for (j=1;j<=4;j++)
	{
          num = num + 1;
          rescoef[i][j]=xval[num];
	}

        if(sf==1)
	{
          height[i] = rescoef[i][1]*(1.+rescoef[i][2]*q2/(1.+rescoef[i][3]*q2))/ pow(1.+q2/0.91,rescoef[i][4]);
	}
        else
	{
          height[i] = rescoef[i][1]*q2/(1.+rescoef[i][2]*q2)*exp(-1.*rescoef[i][3]*q2);
	}

        height[i] = height[i]*height[i];
      }


      if(sf==2)      //  4th resonance region 
      {
        height[7] = xval[45]*q2/(1.+xval[46]*q2)*exp(-1.*xval[47]*q2);
      }
      else
      {
        height[7] = xval[49]/(1.+q2/0.91); 
      }

      height[7] = height[7]*height[7];

//    End resonance Q^2 dependence calculations 
     
      for (i=1;i<=3;i++)        //  Non-Res coefficients 
      {
        for (j=1;j<=4;j++)
	{
          num = num + 1;
          nr_coef[i][j]=xval[num];
	}
      }

//   Calculate Breit-Wigners for all resonances  

      sig_res = 0.0;
      for (i=1;i<=7;i++)
      {
         sigr[i] = width[i]*pgam[i]/((w2 - mass[i]*mass[i])*(w2 - mass[i]*mass[i]) 
	            + (mass[i]*width[i])*(mass[i]*width[i]));
         sigr[i] = height[i]*kr[i]/k*kcmr[i]/kcm*sigr[i]/intwidth[i];
         sig_res = sig_res + sigr[i];
      }
      sig_res = sig_res*w;

//    Finish resonances / start non-res background calculation

      sig_nr = 0.;
      if(sf==1)
      {
        xt = (q2+xval[37])/(w2-1.15+q2+xval[37]);
        p2 = xval[38]*exp(-1.*xval[39]*q2)+xval[40]*log(q2/xval[41]+1.);
        p3 = xval[42]*exp(-1.*xval[43]*q2)+xval[44]*log(q2/xval[45]+1.);
        p1 = xval[46]*(1.+xval[50]*q2/(1.+0.534*q2)); 

        sig_nr = p1*pow(xt,p2)*pow(1.-xt,p3);
      }
      else if(sf==2)
      {

        for (i=1;i<=1;i++)
	{
          sig_nr = sig_nr + nr_coef[i][1]*pow(1.-xpr[i],(nr_coef[i][3]+nr_coef[i][2]*t)) /(1.-xb)/(q2+q20)
                   *pow(q2/(q2+q20), nr_coef[i][4]) *pow(xpr[i],(xval[41]+xval[42]*t));
	}
      }
      
      G4double sig = sig_res + sig_nr;   
      return sig;
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//     Peiqing, Dec. 11, 2011, Moller elastic scattering
//
//     kinematic relations and cross section formulae 
//     are from Wagner, et al. NIMA294 (1990) 541-548 
//     and Arrington, et al. NIMA311 (1992) 39-48, etc.

G4double QweakSimEPEvent::Moller_Scattering(G4double E_in, G4double theta1, 
                                            G4double &E_out1, G4double &E_out2, G4double &theta2, 
                                            G4double &q2, G4double &fWeightN, G4double &asymmetry)
{
      G4double alpha = 1.0/137.036;
      G4double G_F = 1.166e-11;     // Fermi constant in MeV^(-2)
      G4double M_electron = 0.511;  // Incident Electron mass in MeV
      G4double sin2_theta_W = 0.02381;  // sin2_theta_W at 0.026 GeV, taken from E158

      G4double theta_CM = 2.0*atan(tan(theta1)*sqrt((E_in+M_electron)/(2.*M_electron)));
      E_out1 = M_electron+(E_in-M_electron)*(cos(theta_CM/2.0)*cos(theta_CM/2.0));
      E_out2 = E_in - E_out1 + M_electron;
      theta2 = atan(2.0*M_electron/(E_in+M_electron)/tan(theta1));
      //G4double momentum = sqrt(E_out1*E_out1 - M_electron*M_electron);
      // compute q2 in MeV^2
      //q2 = 4.0*E_in*momentum*sin(theta1/2.0)*sin(theta1/2.0);
      q2 = 2*M_electron*(M_electron+E_in)*sin(theta_CM/2.0)*sin(theta_CM/2.0);  
    
  //  calculate Moller cross-section (units are ub/sr)
      G4double Xsect = pow((1+cos(theta_CM))*(3+cos(theta_CM)*cos(theta_CM)),2); 
      // Xsect = pow(alpha/2.0/M_electron,2)*Xsect/pow(sin(theta_CM),4); // alpha^2/(4m^2) = 0.199 b/Sr
      Xsect = (1.99e4)*Xsect/pow(sin(theta_CM),4);
      fWeightN = Xsect*sin(theta1);
      asymmetry = -M_electron*E_in*(G_F/(sqrt(2.0)*alpha*3.1415927))
                  *16*sin(theta_CM)*sin(theta_CM)/(3+cos(theta_CM)*cos(theta_CM))*(1-4*sin2_theta_W);
      asymmetry = asymmetry*1e6;  // in [ppm]

      //std::cout<<"E_in  E1  E2  theta1  theta2  Xsect  Weight  Q2  asym"<<std::endl;
      //std::cout<<E_in<<"  "<<E_out1<<"  "<<E_out2<<"  "<<theta1*180/3.14<<"  "
      //         <<theta2*180/3.14<<"  "<<Xsect<<"  "<<fWeightN<<"  "<<q2*1e-6<<"  "<<asymmetry<<std::endl;
      
      return Xsect;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Calculates the Cross Section weighting factor for 
//      radiated scattering from the proton. 
// ---------------------------------------------------------
//
//  Beam Energy must be 3.35 GeV

const std::vector< G4double > QweakSimEPEvent::Radiative_Cross_Section_Proton(G4double E_in,
                                                         G4double Theta,
                                                         G4double &fWeightN,
                                                         G4double &Q2,
                                                         G4double &E_out)
{
    if (Theta<Theta_Min)
       Theta = Theta_Min;

    E_out = (G4UniformRand()*(EPrime_Max-EPrime_Min) + EPrime_Min);

    const Double_t pos[value_d]   = {myUserInfo->GetOriginVertexPositionZ(),E_in,E_out,Theta};
    Double_t       value[value_n] = {0.0};
    std::vector< G4double > CrossSection;
    
    fLookupTable->GetValue(pos,value);
    Q2       = value[1];
    fWeightN = value[6]*sin(Theta*degree);
    //fWeightN = value[6];

    CrossSection.push_back(value[6]);
    CrossSection.push_back(value[2]);
    CrossSection.push_back(value[3]);
    CrossSection.push_back(value[4]);
    CrossSection.push_back(value[6]);
    CrossSection.push_back(value[7]);
    CrossSection.push_back(value[8]);
    CrossSection.push_back(value[9]);

     return CrossSection;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Creates lookup table for calculating elastic radiative 
//      cross sections on hydrogen. 
// ---------------------------------------------------------

void QweakSimEPEvent::CreateLookupTable()
{
    G4double energy = BeamEnergy;
    if (energy != 3350*MeV /*&& energy != 1160*MeV && energy != 877*MeV*/) {
      G4cout << "#### Current beam energy is not a valid choice for lookup table"  << G4endl;
      G4cout << "#### Setting beam energy to default value for lookup table (3.35 GeV)" << G4endl;
      energy = 3350*MeV;
    }

    TString target = "lh2";
    
    TString filename =  "radiative_lookup_";
    filename += target;
    filename += "_";
    filename += (Int_t)energy;
    filename += "MeV.dat";

    TString filepath = "./";

    std::ifstream in;
    in.open(filepath + filename);
    if (!in.is_open())  
      G4cout << "#### Failed to open lookup table data file \"" << filepath << filename << "\"" << G4endl;
    else
    {
      in.close();
      G4cout << "#### Found lookup table data file \"" << filepath << filename << "\"" << G4endl;
      if (fLookupTable != 0) delete fLookupTable;
      fLookupTable = new QweakSimFieldMap<value_t,value_n>(value_d);
      fLookupTable->ReadTextFile((filepath +filename).Data());
    }
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;
    G4cout << "++ Lookup Table Parameters ++" << G4endl;
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;
    G4cout << "Beam Energy:       " << fLookupTable->GetMinimum(1)/1000 << " GeV" << G4endl;
    G4cout << "Target:            " << target << G4endl;
    G4cout << "E\' Lower Bound:    " << fLookupTable->GetMinimum(2)/1000 << " GeV" << G4endl;
    G4cout << "E\' Upper Bound:    " << fLookupTable->GetMaximum(2)/1000 << " GeV" << G4endl;
    G4cout << "Theta Lower Bound: " << fLookupTable->GetMinimum(3)/degree << " degrees" << G4endl;
    G4cout << "Theta Upper Bound: " << fLookupTable->GetMaximum(3)/degree << " degrees" << G4endl;
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;

    if (energy != GetBeamEnergy()) SetBeamEnergy(energy);
    else CheckLookupTableBounds();
    
    //********************************************************************
    
/*
    G4int entries = 1;

    coord_t coord[value_d] = {0.0};
    value_t field[value_n] = {0.0};
 
    //  Set min, max, and step size for each coordinate in the lookup table.
    //  Z position in radiation lengths
    fMin.push_back(myUserInfo->TargetCenterPositionZ - 0.5*myUserInfo->TargetLength);
    fMax.push_back(myUserInfo->TargetCenterPositionZ + 0.5*myUserInfo->TargetLength);
    fStep.push_back(myUserInfo->TargetLength/10.0);

    //  Beam Energy in GeV
    fMin.push_back(3.35*GeV);
    fMax.push_back(3.35*GeV);
    fStep.push_back(0.05*GeV);

    //  E prime in GeV
    fMin.push_back(0.15*GeV);
    fMax.push_back(1.55*GeV);
    fStep.push_back(0.05*GeV);

    //  Theta angle
    fMin.push_back(2.00*degree);
    fMax.push_back(20.0*degree);
    fStep.push_back(0.5*degree);

    G4cout << "Target Min:      " << fMin[0] << G4endl;
    G4cout << "Target Max:      " << fMax[0] << G4endl;
    
    
    for (Int_t n = 0; n < (Int_t)fStep.size(); n++) {
      entries *= (G4int)( (fMax[n]-fMin[n])/fStep[n] + 1.5 );
    }
    std::ifstream in;
    in.open("./radiative_lookup.dat");
    if (!in.is_open())  
        G4cout << "#### Failed to open data file for lookup table" << G4endl;
    else
    {
      G4cout << "#### Found lookup table data file"  << G4endl;
      if (fLookupTable != 0) delete fLookupTable;
      fLookupTable = new QweakSimFieldMap<value_t,value_n>(value_d);
      fLookupTable->SetMinimumMaximumStep(fMin,fMax,fStep);

      //  Filling Lookup Table
      for (Int_t line = 0; line <  entries; line++) {
        if (in.peek() == EOF) {
          G4cout << "#### Error reading \'elastic_lookup.dat\':  File contains only "
                 << line << " of " << entries << " expected lines. ####" << G4endl;
          break;
        }

        for (G4int i = 0; i < value_d; i++)  in >> coord[i];
        for (G4int j = 0; j < value_n; j++)  in >> field[j];
   
        //  Add units
                             // Z position converted from rad lengths to GEANT coords
        coord[0] = myUserInfo->TargetCenterPositionZ - 0.5*myUserInfo->TargetLength
                   + coord[0]*myUserInfo->TargetLength/0.0396;        
        coord[1] *= GeV;     // Beam Energy
        coord[2] *= GeV;     // E prime
        coord[3] *= degree;  // Theta

        //field[0]           // Bjorken x (unitless) // This value has too few sig figs
	field[1] *= GeV*GeV; // Q2                   // This value has too few sig figs
	//field[2]           // total born cross section (ub/Sr)
	//field[3]           // inelastic born cross section(ub/Sr)
	//field[4]           // quasi-elastic born cross section (ub/Sr)
	//field[5]           // quasi-elastic factor
	//field[6]           // total radiated cross section (ub/Sr)
	//field[7]           // elastic radiated cross section (ub/Sr)
	//field[8]           // quasi-elastic radiated cross section (ub/Sr)
	//field[9]           // deep-inelastic radiated cross section (ub/Sr)
	//field[10]          // charge correction

        fLookupTable->Set(coord,field);
      }
      G4cout << "===== Filling of Lookup Table complete! =====" << G4endl;
    }
    in.close();
    fLookupTable->WriteTextFile("./radiative_lookup.out");
    */
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Checks the ranges of input parameters (E, E', and theta)
//      and insures they are within the lookup table bounds.  
// ---------------------------------------------------------

void QweakSimEPEvent::CheckLookupTableBounds()
{
  if (fLookupTable == 0) return;
  if (BeamEnergy != (G4double)fLookupTable->GetMinimum(1) ) {
    G4cout << "!!!! Beam Energy is out of bounds" << G4endl;
    G4cout << "---> Changing Beam Energy to default value (" << fLookupTable->GetMinimum(1)/1000 << " GeV)" << G4endl;
    SetBeamEnergy(  (G4double)fLookupTable->GetMinimum(1) );
    CreateLookupTable();
    return;
  }
  
  if (EPrime_Min < fLookupTable->GetMinimum(2) || EPrime_Min > fLookupTable->GetMaximum(2)) {
    EPrime_Min = fLookupTable->GetMinimum(2);
    G4cout << "!!!! Minimum E\' is out of bounds" << G4endl;
    G4cout << "---> Changing Minimum E\' to lower bound (" << fLookupTable->GetMinimum(2)/1000 << " GeV)" << G4endl;      
  }
  if (EPrime_Max > fLookupTable->GetMaximum(2) || EPrime_Max < fLookupTable->GetMinimum(2)) {
    EPrime_Max = fLookupTable->GetMaximum(2);
    G4cout << "!!!! Maximum E\' is out of bounds" << G4endl;
    G4cout << "---> Changing Maximum E\' to upper bound (" << fLookupTable->GetMaximum(2)/1000 << " GeV)" << G4endl;      
  }
  if (EPrime_Min > EPrime_Max) {
    EPrime_Min = EPrime_Max;
    G4cout << "!!!! Minimum E\' greater than maximum E\'" << G4endl;
    G4cout << "---> Changing Minimum E\' to " << EPrime_Max/1000 << " GeV" << G4endl;
  }
  
  if (ThetaAngle_Min < fLookupTable->GetMinimum(3) || ThetaAngle_Min > fLookupTable->GetMaximum(3)) {
    ThetaAngle_Min = fLookupTable->GetMinimum(3);
    G4cout << "!!!! Minimum Theta is out of bounds" << G4endl;
    G4cout << "---> Changing Minimum Theta to lower bound (" << fLookupTable->GetMinimum(3)/degree << " degrees)" << G4endl;      
  }
  if (ThetaAngle_Max > fLookupTable->GetMaximum(3) || ThetaAngle_Max < fLookupTable->GetMinimum(3)) {
    ThetaAngle_Max = fLookupTable->GetMaximum(3);
    G4cout << "!!!! Maximum Theta is out of bounds" << G4endl;
    G4cout << "---> Changing Maximum Theta to upper bound (" << fLookupTable->GetMaximum(3)/degree << " degrees)" << G4endl;      
  }
  if (ThetaAngle_Min > ThetaAngle_Max) {
    ThetaAngle_Min = ThetaAngle_Max;
    G4cout << "!!!! Minimum Theta greater than maximum Theta" << G4endl;
    G4cout << "---> Changing Minimum Theta to " << ThetaAngle_Max << " degrees" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



/////// --------------------------------------------------------------------
//
//--- Fang Guo
//
//---   Calculates the Cross Section weighting factor for 
//---   pion photo-production with the wiser code. 
//
//--- Beam Energy must be 3.35 GeV

G4double QweakSimEPEvent::Pion_PhotoProduction(G4double E_in,
                                               G4double Theta,
                                               G4double &fWeightN,
                                               G4double &Q2,
                                               G4double &E_out)
{
    const G4double Mpi = 0.13957*GeV;   ///--- GeV
	
    if (Theta<Theta_Min)
        Theta = Theta_Min;
	
    Q2 = 0.026;	
	
    double Ebeam = 3.35*GeV;   //--- beam energy in GeV
	
    E_out = (G4UniformRand()*(EPrime_Max - EPrime_Min) + EPrime_Min);   //--- final total energy in GeV
    G4double pf = (sqrt(E_out * E_out - Mpi * Mpi));   //--- final momentum in GeV

    G4double thf = Theta*(3.1415926/180.0);  //--- degrees --> radians

    //---
    //--- radiation length from page 12 of "The Qweak target design and safety document"
    //--- http://qweak.jlab.org/DocDB/0010/001041/002/Qweak%20Target%20PDR.pdf
    //---
    G4double lh2_length = myPositionZ - (myUserInfo->TargetCenterPositionZ) + 0.5*(myUserInfo->TargetLength);
    G4double rad_len = myUserInfo->TargetEntranceWindowThickness/(8.896*cm) + lh2_length/(871.9*cm) + 0.0204;   //--- radiation length
    //G4cout << "radiation length: " << rad_len << G4endl;

    G4int type = 1; //--- pi-
	
    G4double xsect = (1.0/1000.00) * wiser_sigma(Ebeam, pf, thf, rad_len, type); //--- nanobarns/GeV/str --> ub/sr
	
    fWeightN = xsect*sin(Theta);
	
    if(xsect == 0)
    {
        E_out = 0.0;
        Q2 = 0.0;
    }
	
    return xsect;
	
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Quasielastic fit from Bosted et al
// Added 19/March kamyers@jlab.org

G4double QweakSimEPEvent::Quasi_Elastic_Bosted(G4double E_in,
                                               G4double Theta,
                                               G4int Zin,
                                               G4int Ain,
                                               G4double &fWeightN,
                                               G4double &Q2,
                                               G4double &E_out)
{

  G4double F1qe = 0.0;
  G4double F2qe = 0.0;
  G4double W1qe = 0.0;
  G4double W2qe = 0.0;
  G4double W2 = 0.0;
  G4double xsect = 0.0;
  G4double Ein = 0.0;
  G4double Eout = 0.0;

  // In this subroutine units are in GeV, so
  Ein = E_in/1000.;                // maximum energy in GeV
  G4double M_electron = 0.000511;  // minimum energy (electron mass) in GeV
  G4double Mp = 0.93828;

  // G4double Theta_Min = 1.745329E-4;
  if (Theta<Theta_Min)
      Theta = Theta_Min;

  // Generate flat energy distribution of outgoing electron      
  Eout =  M_electron + G4UniformRand()*(Ein - M_electron);

  G4double CTH = cos(Theta/2.0);
  G4double STH = sin(Theta/2.0);
  G4double T2THE = STH*STH/CTH/CTH;
  G4double Nu = Ein - Eout;
  Q2 = 4.0*Ein*Eout*STH*STH;
  W2 = Mp*Mp + 2.0*Mp*Nu - Q2;

  // Mott scattering
  G4double MOTT = pow((0.00072/Ein*CTH/STH/STH),2);
  MOTT = MOTT*1.0E4; // Units: ub/sr/GeV

  //G4cout << "Ein, Eout, Nu, Theta: " << Ein << ", " << Eout << ", " << Nu << ", " << Theta/degree << G4endl;
  //G4cout << "Q2, W2, Mott: " << Q2 << ", " << W2 << ", " << MOTT << G4endl;

  F1F2QE09(Zin, Ain, Q2, W2, F1qe, F2qe);
  W1qe = F1qe/Mp;
  W2qe = F2qe/Nu;

  xsect = MOTT*(W2qe + 2.0*T2THE*W1qe);
  //G4cout << "F1, F2, W1, W1: " << F1qe << ", " << F2qe << ", " << W1qe << ", " << W2qe << G4endl;

  // In some cases a negative F2 is returned giving a negative cross section
  if (xsect <= 0) xsect = 0.0;

  fWeightN = xsect*sin(Theta)*(Ein - M_electron);

  E_out = Eout*1000.;		// Convert back to MeV before leaving
  Q2 = Q2*1.0E6;		// Seems like this needs to be returned in MeV**2
  return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::F1F2QE09(G4int &Z, G4int &IA, G4double &QSQ,
                               G4double &wsq, G4double &F1, G4double &F2)
{
//=======================================================================
//      SUBROUTINE F1F2QE09(Z, A, QSQ, wsq, F1, F2)
//
// Calculates quasielastic A(e,e')X structure functions F1 and F2 PER NUCLEUS
// for A>2 uses superscaling from Sick, Donnelly, Maieron, nucl-th/0109032
// for A=2 uses pre-integrated Paris wave function (see ~bosted/smear.f)
// coded by P. Bosted August to October, 2006
//
// input: Z, A  (real*8) Z and A of nucleus (shoud be 2.0D0 for deueron)
//        Qsq (real*8) is 4-vector momentum transfer squared (positive in
//                     chosen metric)
//        Wsq (real*8) is invarinat mass squared of final state calculated
//                     assuming electron scattered from a free proton
//                 
// outputs: F1, F2 (real*8) are structure functions per nucleus
//
// Note: Deuteron agrees well with Laget (see ~bosted/eg1b/laget.f) for
// a) Q2<1 gev**2 and dsig > 1% of peak: doesnt describe tail at high W
// b) Q2>1 gev**2 on wings of q.e. peak. But, this model is up
//    to 50% too big at top of q.e. peak. BUT, F2 DOES agree very
//    nicely with Osipenko et al data from CLAS, up to 5 GeV**2

  G4double avgN, Pauli_sup1, Pauli_sup2, GEP, GEN, GMP, GMN, Q, Q3, Q4;
  G4double amp = 0.93828;
  G4double amd = 1.8756;
  G4double RMUP = 2.792782;
  G4double RMUN = -1.913148;
  G4double pz, Nu, dpz, pznom, pzmin;
  G4double QV, TAU, FY, dwmin, w2p;
  G4double kappa, lam, lamp, taup, squigglef, psi, psip, nuL, nuT;
  G4double kf, Es, GM2bar, GE2bar, W1bar, W2bar, Delta, GL, GT;
  G4int izz, izzmin, izp, izznom, izdif;

  // Look up tables for deuteron case
  G4double fyd[200] = {
    0.00001,0.00002,0.00003,0.00005,0.00006,0.00009,0.00010,0.00013,
    0.00015,0.00019,0.00021,0.00026,0.00029,0.00034,0.00038,0.00044,
    0.00049,0.00057,0.00062,0.00071,0.00078,0.00089,0.00097,0.00109,
    0.00119,0.00134,0.00146,0.00161,0.00176,0.00195,0.00211,0.00232,
    0.00252,0.00276,0.00299,0.00326,0.00352,0.00383,0.00412,0.00447,
    0.00482,0.00521,0.00560,0.00603,0.00648,0.00698,0.00747,0.00803,
    0.00859,0.00921,0.00985,0.01056,0.01126,0.01205,0.01286,0.01376,
    0.01467,0.01569,0.01671,0.01793,0.01912,0.02049,0.02196,0.02356,
    0.02525,0.02723,0.02939,0.03179,0.03453,0.03764,0.04116,0.04533,
    0.05004,0.05565,0.06232,0.07015,0.07965,0.09093,0.10486,0.12185,
    0.14268,0.16860,0.20074,0.24129,0.29201,0.35713,0.44012,0.54757,
    0.68665,0.86965,1.11199,1.43242,1.86532,2.44703,3.22681,4.24972,
    5.54382,7.04016,8.48123,9.40627,9.40627,8.48123,7.04016,5.54382,
    4.24972,3.22681,2.44703,1.86532,1.43242,1.11199,0.86965,0.68665,
    0.54757,0.44012,0.35713,0.29201,0.24129,0.20074,0.16860,0.14268,
    0.12185,0.10486,0.09093,0.07965,0.07015,0.06232,0.05565,0.05004,
    0.04533,0.04116,0.03764,0.03453,0.03179,0.02939,0.02723,0.02525,
    0.02356,0.02196,0.02049,0.01912,0.01793,0.01671,0.01569,0.01467,
    0.01376,0.01286,0.01205,0.01126,0.01056,0.00985,0.00921,0.00859,
    0.00803,0.00747,0.00698,0.00648,0.00603,0.00560,0.00521,0.00482,
    0.00447,0.00412,0.00383,0.00352,0.00326,0.00299,0.00276,0.00252,
    0.00232,0.00211,0.00195,0.00176,0.00161,0.00146,0.00134,0.00119,
    0.00109,0.00097,0.00089,0.00078,0.00071,0.00062,0.00057,0.00049,
    0.00044,0.00038,0.00034,0.00029,0.00026,0.00021,0.00019,0.00015,
    0.00013,0.00010,0.00009,0.00006,0.00005,0.00003,0.00002,0.00001};

  G4double avp2[200] = {
    1.0,0.98974,0.96975,0.96768,0.94782,0.94450,0.92494,0.92047,
    0.90090,0.89563,0.87644,0.87018,0.85145,0.84434,0.82593,0.81841,
    0.80021,0.79212,0.77444,0.76553,0.74866,0.73945,0.72264,0.71343,
    0.69703,0.68740,0.67149,0.66182,0.64631,0.63630,0.62125,0.61154,
    0.59671,0.58686,0.57241,0.56283,0.54866,0.53889,0.52528,0.51581,
    0.50236,0.49291,0.47997,0.47063,0.45803,0.44867,0.43665,0.42744,
    0.41554,0.40656,0.39511,0.38589,0.37488,0.36611,0.35516,0.34647,
    0.33571,0.32704,0.31656,0.30783,0.29741,0.28870,0.27820,0.26945,
    0.25898,0.25010,0.23945,0.23023,0.21943,0.20999,0.19891,0.18911,
    0.17795,0.16793,0.15669,0.14667,0.13553,0.12569,0.11504,0.10550,
    0.09557,0.08674,0.07774,0.06974,0.06184,0.05484,0.04802,0.04203,
    0.03629,0.03129,0.02654,0.02247,0.01867,0.01545,0.01251,0.01015,
    0.00810,0.00664,0.00541,0.00512,0.00512,0.00541,0.00664,0.00810,
    0.01015,0.01251,0.01545,0.01867,0.02247,0.02654,0.03129,0.03629,
    0.04203,0.04802,0.05484,0.06184,0.06974,0.07774,0.08674,0.09557,
    0.10550,0.11504,0.12569,0.13553,0.14667,0.15669,0.16793,0.17795,
    0.18911,0.19891,0.20999,0.21943,0.23023,0.23945,0.25010,0.25898,
    0.26945,0.27820,0.28870,0.29741,0.30783,0.31656,0.32704,0.33571,
    0.34647,0.35516,0.36611,0.37488,0.38589,0.39511,0.40656,0.41554,
    0.42744,0.43665,0.44867,0.45803,0.47063,0.47997,0.49291,0.50236,
    0.51581,0.52528,0.53889,0.54866,0.56283,0.57241,0.58686,0.59671,
    0.61154,0.62125,0.63630,0.64631,0.66182,0.67149,0.68740,0.69703,
    0.71343,0.72264,0.73945,0.74866,0.76553,0.77444,0.79212,0.80021,
    0.81841,0.82593,0.84434,0.85145,0.87018,0.87644,0.89563,0.90090,
    0.92047,0.92494,0.94450,0.94782,0.96768,0.96975,0.98974,1.0};

  // Peter Bosted's correction params
  G4double pb[20] = {
    0.1023E+02, 0.1052E+01, 0.2485E-01, 0.1455E+01,
    0.5650E+01,-0.2889E+00, 0.4943E-01,-0.8183E-01,
    -0.7495E+00, 0.8426E+00,-0.2829E+01, 0.1607E+01,
    0.1733E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00,
    0.0000E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00};
  G4double y,R;

  G4double P[24] = {
     5.1377e-03,   9.8071e-01,   4.6379e-02,   1.6433e+00,
     6.9826e+00,  -2.2655e-01,   1.1095e-01,   2.7945e-02,
     4.0643e-01,   1.6076e+00,  -7.5460e+00,   4.4418e+00,
     -3.7464e-01,   1.0414e-01,  -2.6852e-01,   9.6653e-01,
     -1.9055e+00,   9.8965e-01,   2.0613e+02,  -4.5536e-02,
     2.4902e-01,  -1.3728e-01,   2.9201e+01,   4.9280e-03};

  // return if proton: future change this to allow for
  // equivalent W resolution
  F1 = 0.;
  F2 = 0.;
  avgN = A - Z;
  if (IA==1) return;

  // some kinematic factors. Return if Nu or QSQ is negative
  Nu = (wsq - amp*amp + QSQ) / 2. / amp;

  //G4cout << "In call... IA, Nu, QSQ = " << IA << ", " << Nu << ", " << QSQ << G4endl;
  if(Nu <= 0.0 || QSQ < 0.) return;
  TAU   = QSQ / 4.0 / amp / amp;                                 
  QV = sqrt(Nu*Nu + QSQ);

  // Bosted fit for nucleon form factors Phys. Rev. C 51, p. 409 (1995)
  Q = sqrt(QSQ);
  Q3 = QSQ * Q;
  Q4 = QSQ*QSQ;
  GEP = 1./  (1. + 0.14 * Q + 3.01 * QSQ + 0.02 * Q3 + 1.20 * Q4 + 0.32 * pow(Q,5));
  GMP = RMUP * GEP;
  GMN = RMUN / (1.- 1.74 * Q + 9.29 * QSQ - 7.63 * Q3 + 4.63 * Q4);
  GEN = 1.25 * RMUN * TAU / (1. + 18.3 * TAU) / pow((1. + QSQ / 0.71),2);

  //G4cout << "Form Factors: " << GEP << ", " << GMP << ", " << GEN << ", " << GMN << G4endl;

  // Get kf and Es from superscaling from Sick, Donnelly, Maieron,
    // nucl-th/0109032
    if(IA==2) kf=0.085;
    if(IA==2) Es=0.0022;
    // changed 4/09
    if(IA==3) kf=0.115;
    if(IA==3) Es=0.001 ;
    // changed 4/09
    if(IA>3) kf=0.19;
    if(IA>3) Es=0.017; 
    if(IA>7) kf=0.228;
    if(IA>7) Es=0.020;
    // changed 5/09
    if(IA>7) Es=0.0165;
    if(IA>16) kf=0.230;
    if(IA>16) Es=0.025;
    if(IA>25) kf=0.236;
    if(IA>25) Es=0.018;
    if(IA>38) kf=0.241;
    if(IA>38) Es=0.028;
    if(IA>55) kf=0.241;
    if(IA>55) Es=0.023;
    if(IA>60) kf=0.245;
    if(IA>60) Es=0.028;
    // changed 5/09 
    if(IA>55) Es=0.018;

  // Pauli suppression model from Tsai RMP 46,816(74) eq.B54
  if ((QV > 2.* kf) || (IA == 1)) {
    Pauli_sup2 =1.0;
  } else {
    Pauli_sup2 = 0.75 * (QV / kf) * (1.0 - (pow((QV / kf),2))/12.);
  }
  Pauli_sup1 = Pauli_sup2;

  //G4cout << "kf, Es, Paulisup1,2: " << kf << ", " << Es << ", " << Pauli_sup1 << ", " << Pauli_sup2 << G4endl;
  
  // structure functions with off shell factors
  kappa = QV / 2. / amp;
  lam = Nu / 2. / amp;
  lamp = lam - Es / 2. / amp;
  taup = kappa*kappa - lamp*lamp;
  squigglef = sqrt(1. + pow((kf/amp),2)) -1.;

  // Very close to treshold, could have a problem
  if(1.+lamp <= 0.) return;
  if(taup * (1. + taup) <= 0.) return;

  psi =  (lam  - TAU ) / sqrt(squigglef) / sqrt((1.+lam )* TAU + kappa * sqrt(TAU * (1. + TAU)));
  psip = (lamp - taup) / sqrt(squigglef) / sqrt((1.+lamp)*taup + kappa * sqrt(taup * (1. + taup)));
  nuL = pow((TAU / kappa / kappa),2);

  // changed definition of nuT from
  // nuT = TAU / 2. / kappa**2 + tan(thr/2.)**2
  // to this, in order to separate out F1 and F2 (F1 prop. to tan2 term)
  nuT = TAU / 2. / kappa / kappa;

  GM2bar = Pauli_sup1 * (Z * GMP*GMP + avgN * GMN*GMN);
  GE2bar = Pauli_sup2 * (Z * GEP*GEP + avgN * GEN*GEN);
  W1bar = TAU * GM2bar;
  W2bar = (GE2bar + TAU * GM2bar) / (1. + TAU);

  Delta = squigglef * (1. - psi*psi) * (sqrt(TAU * (1.+TAU)) / kappa + squigglef/3. *
     (1. - psi*psi) * TAU / kappa / kappa);
  GL = kappa*kappa / TAU * (GE2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef * 
     (1. + psi*psi) / 2.);
  GT = (2. * TAU * GM2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef * 
     (1. + psi*psi) / 2.);

  //G4cout << "nuL, nuT, GL, GT: " << nuL << ", " << nuT << ", " << GL << ", " << GT << G4endl;

  // added to prevent negative xsections:
  if (GT < 0) {
    GT = 0;
    //G4cout << "Reset GT to zero" << G4endl;
  }

  // from Maria Barbaro: see Amaro et al., PRC71,015501(2005).
  FY = 1.5576 / (1. + 1.7720*1.7720 * pow((psip + 0.3014),2)) / (1. + exp(-2.4291 * psip)) / kf;

// == Note: Below is for deuteron and haven't == //
// == verified if code conversion is correct  == //
  // Use PWIA and Paris W.F. for deuteron to get better FY
  if (IA == 2) {
    // value assuming average p2=0.
    pz = (QSQ - 2. * amp * Nu ) / 2. / QV;
    izz = int((pz + 1.0) / 0.01) + 1;
    if (izz < 1) izz = 1;
    if (izz > 200) izz = 200;
    izznom = izz;

    // ignoring energy term, estimate change in pz to compensate
    //! for avp2 term
    dpz = avp2[izznom] / 2. / QV;
    izdif = dpz * 150.;
    dwmin=1.E6;
    izzmin=0;  

    G4int izpmax;
    if ((izznom + izdif) < 1) izpmax = 1;
    if (izpmax > 200) izpmax = 200;
    for (izp = izznom; izp <= izpmax; izp++) {
      pz = -1. + 0.01 * (izp-0.5);
      // *** this version gives worse agreement with laget than
      //         w2p = (amd + Nu - sqrt(amp**2 + avp2(izp)))**2 - 
      //    >      QV**2 + 2. * QV * pz - avp2(izp)
      // this version!
      w2p = pow((amd + Nu - amp ),2) - QV*QV + 2. * QV * pz - avp2[izp];

      // if passed first minimum, quit looking so don't find second one
      if (abs(w2p - amp*amp) > dwmin) {
        if (izzmin < 2) izzmin = 2;
        if (izzmin > 199) izzmin = 199;
        izz = izzmin;
      } else if (abs(w2p - amp*amp) < dwmin) {
          dwmin = abs(w2p - amp*amp);
          izzmin = izp;
      }
    }

    // search for minimum in 1/10th bins locally
    pznom = -1. + 0.01 * (izz-0.5);
    dwmin=1.E6;
    for (izp = 1; izp <= 19; izp++) {
      pz = pznom - 0.01 + 0.001 * izp;
      // *** this version gives worse agreement with laget than
      //        w2p = (amd + Nu - sqrt(amp**2 + avp2(izz)))**2 - 
      //   >      QV**2 + 2. * QV * pz - avp2(izz)
      // this version!
      w2p = pow((amd + Nu - amp ),2) - QV*QV + 2. * QV * pz - avp2[izz];
      if (abs(w2p - amp*amp) < dwmin) {
        dwmin = abs(w2p - amp*amp);
        pzmin = pz;
      }
    }

    if (dwmin >= 1.e6 || abs(pznom-pzmin) > 0.01) { 
      //     >     write(6,'(1x,''error in dwmin,pzmin'',3i4,6f7.3)')
      //     >     izznom,izzmin,izz,QSQ,wsq,w2p,dwmin/1.e6,pzmin,pznom
      if (pzmin < pznom) FY = fyd[izz] - (fyd[izz-1] - fyd[izz]) * (pzmin - pznom) / 0.01;
      else FY = fyd[izz] + (fyd[izz+1] - fyd[izz]) * (pzmin - pznom) / 0.01;
    }
  }
// == To here == //

  // final results
  F2 = Nu * FY * (nuL * GL + nuT * GT);
  F1 = amp * FY * GT / 2.;

  //G4cout << "nu, Fy, nuL, GL, nuT, GT, amp: " << G4endl;
  //G4cout << Nu << ", " << FY << ", " << nuL << ", " << GL << ", " << nuT << ", " << GT << ", " << amp << G4endl;

  if (F1 < 0.0) F1 = 0.;
  if (Nu > 0. && F1 > 0.) R = (F2 / Nu) / (F1 / amp) * (1. + Nu*Nu / QSQ) - 1.0;
  else R = 0.4/QSQ;


  // apply correction factors
  if ( A > 2 ) {
    y = (wsq -amp*amp) / QV;
    //         F1 = F1 * (1. + pb(8) + pb(9) * y +
    //     >        pb(10)*y**2 + pb(11)*y**3 + pb(12)*y**4 )
    //         R = R * (1. + pb(13))
    //         F2 = Nu * F1/amp * (1. + R) / (1. + Nu**2/QSQ)

    // correction to correction Vahe
    if (wsq > 0.0) {
      F1=F1*(1.0+P[7]+P[8]*y+P[9]*y*y +P[10]*pow(y,3) +P[11]*pow(y,4));
      R = R * ( 1.0 + P[12] );
      F2 = Nu * F1/amp * (1. + R) / (1. + Nu*Nu/QSQ);
      if (F1 < 0.0) F1=0.0;
    }
  }

  return;
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// ---------------------------------------------------------
//      Calculates the asymmetry weighting factor for elastic
//      scattering from the proton.  Asymmetry returned in ppm
// ---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_EP(G4double theta, G4double energy)
{

    const G4double Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    //const G4double s2tw=0.231;
    const G4double s2tw_low=0.2387;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    //const G4double NT=14.;
    //const G4double ZT=13.;

//     Radiative correction factors [from Musolf's Phys. Rep. 1994]
    //const G4double rpv=-0.054;
    //const G4double rnv=-0.0143;
    //const G4double rt0a=0.0;
    const G4double rt1a=-0.23;
    //const G4double r0a=0.023;

//     Check for minimum theta
    const G4double theta_min = 1.745329E-4;
    if (theta<theta_min)
        theta = theta_min;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy=energy/1000.0;

//     Calculate Q2
    G4double Q2_ep=4*energy*energy*sin(theta/2.0)*sin(theta/2.0);
    Q2_ep=Q2_ep/(1.0+2.0*energy/Mp*sin(theta/2.0)*sin(theta/2.0));

//     Proton Asymmetry
//     Kinematic Factors
    G4double tau=Q2_ep/4.0/(Mp*Mp);
    G4double epsilon=1.0/(1.0+2.0*(1.0+tau)*tan(theta/2.0)*tan(theta/2.0));
    G4double epsilonp=sqrt(tau*(1.0+tau)*(1.0-epsilon*epsilon));

//     Form factor calculations
//     Form Factors: Electromagetic
    G4double gvd=1.0/( (1.0+Q2_ep/0.71)*(1.0+Q2_ep/0.71) );
    G4double gepg=gvd;
    G4double gmpg=2.793*gvd;
    G4double geng=1.91*tau*gvd/(1.+5.6*tau);
    G4double gmng=-1.91*gvd;

//    Form Factors: Neutral-weak, Axial
//     Assume: Gs_E,M=0, G8_A,Gs_A=0
    //G4double gad=1/((1.0+Q2_ep/1.001/1.001)*(1.0+Q2_ep/1.001/1.001));
    //G4double gsa=-0.12/((1.+Q2_ep/1.06/1.06)*(1.+Q2_ep/1.06/1.06));
    G4double gt1a=1.2695/((1+Q2_ep/1.001/1.001)*(1+Q2_ep/1.001/1.001));
    //G4double g8a=0.0;
    //gsa=0.0;

//      Use SM radiative correction factors
//      Since we use SM values for Qw(p) and Qw(n)
//      we no longer need the radiative corrections
//      on those quantities.
//       gepz=(1.-4.*s2tw)*(1.+rpv)*gepg-(1.+rnv)*geng
//       gmpz=(1.-4.*s2tw)*(1.+rpv)*gmpg-(1.+rnv)*gmng

    G4double gepz=qwp*gepg+qwn*geng;
    G4double gmpz=qwp*gmpg+qwn*gmng;
    G4double gapz=-(1.0+rt1a)*gt1a;

    G4double asym=-gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
    asym=asym/(epsilon*gepg*gepg+tau*gmpg*gmpg);
    asym=asym*(epsilon*gepg*gepz+tau*gmpg*gmpz-(1.0-4.0*s2tw_low)*epsilonp*gmpg*gapz);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//---------------------------------------------------------
//     Calculates the asymmetry weighting factor for elastic
//     e-Al scattering using a formula from Donnelly.  Returns
//     the asymmetry in units of ppm.
//
//    Qw(p) value from J. Erler, Phys. Rev. D72, 073003 (2005)
//    Qw(n) value from using C_1u and C_1d values from PDG2008
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_AL (G4double theta, G4double energy)
{
//     Needed constants
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    const G4double NT=14.;
    const G4double ZT=13.;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy = energy/1000.0;

//     Claculate Q2
    G4double Q2=4*energy*energy*sin(theta/2.)*sin(theta/2.);

//     Correction for Coulomb distortion for Al
    Q2=Q2*(1.+(3.*ZT*0.197/137./(2.*energy*2.98)))*(1.+(3.*ZT*0.197/137./(2.*energy*2.98)));

//     Aluminum Asymmetry
    G4double asym=-gf/(4.*pi*alpha*sqrt(2.))*1e6*Q2*(qwp+qwn*NT/ZT);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//---------------------------------------------------------
//     Calculates the asymmetry weighting factor for elastic
//     e-Be scattering using a formula from Donnelly.  Returns
//     the asymmetry in units of ppm.
//
//    Qw(p) value from J. Erler, Phys. Rev. D72, 073003 (2005)
//    Qw(n) value from using C_1u and C_1d values from PDG2008
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_Be (G4double theta, G4double energy)
{
    const G4double Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    const G4double NT=5.;
    const G4double ZT=4.;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy = energy/1000.;

//     Claculate Q2
    G4double Q2=4*energy*energy*sin(theta/2.)*sin(theta/2.);
    Q2=Q2/(1.+2.*energy/(9.*Mp)*sin(theta/2.)*sin(theta/2.));

//     Correction for Coulomb distortion
    Q2=Q2*(1.+(3./2.*sqrt(3./5.)*ZT*0.197/137./(energy*1.77)))*(1.+(3./2.*sqrt(3./5.)*ZT*0.197/137./(energy*1.77)));

//     Beryllium Asymmetry
    G4double asym=-gf/(4.*pi*alpha*sqrt(2.))*1e6*Q2*(qwp+qwn*NT/ZT);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//    Calculates the asymmetry weighting factor for elastic
//    scattering from the neutron.

G4double QweakSimEPEvent::GetAsymmetry_EN(G4double theta, G4double energy)
{
  
    const G4double Mn= 0.939565; // Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    //const G4double s2tw=0.231;
    const G4double s2tw_low=0.2387;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    //const G4double NT=14.;
    //const G4double ZT=13.;

//     Radiative correction factors [from Musolf's Phys. Rep. 1994]
    //const G4double rpv=-0.054;
    //const G4double rnv=-0.0143;
    //const G4double rt0a=0.0;
    const G4double rt1a=-0.23;
    //const G4double r0a=0.023;

//     Check for minimum theta
    const G4double theta_min = 1.745329E-4;
    if (theta<theta_min)
        theta = theta_min;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy=energy/1000.0;

//     Calculate Q2
    G4double Q2_ep=4*energy*energy*sin(theta/2.0)*sin(theta/2.0);
    Q2_ep=Q2_ep/(1.0+2.0*energy/Mn*sin(theta/2.0)*sin(theta/2.0));

//     Proton Asymmetry
//     Kinematic Factors
    G4double tau=Q2_ep/4.0/(Mn*Mn);
    G4double epsilon=1.0/(1.0+2.0*(1.0+tau)*tan(theta/2.0)*tan(theta/2.0));
    G4double epsilonp=sqrt(tau*(1.0+tau)*(1.0-epsilon*epsilon));

//     Form factor calculations
//     Form Factors: Electromagetic
    G4double gvd=1.0/( (1.0+Q2_ep/0.71)*(1.0+Q2_ep/0.71) );
    G4double gepg=gvd;
    G4double gmpg=2.793*gvd;
    G4double geng=1.91*tau*gvd/(1.+5.6*tau);
    G4double gmng=-1.91*gvd;
    //G4double gesg= 0;
    //G4double gmsg= 0;

//    Form Factors: Neutral-weak, Axial
//     Assume: Gs_E,M=0, G8_A,Gs_A=0
    //G4double gad=1/((1.0+Q2_ep/1.001/1.001)*(1.0+Q2_ep/1.001/1.001));
    //G4double gsa=-0.12/((1.+Q2_ep/1.06/1.06)*(1.+Q2_ep/1.06/1.06));
    G4double gt1a=1.2695/((1+Q2_ep/1.001/1.001)*(1+Q2_ep/1.001/1.001));
    //G4double g8a=0.0;
    //gsa=0.0;

//      Use SM radiative correction factors
//      Since we use SM values for Qw(p) and Qw(n)
//      we no longer need the radiative corrections
//      on those quantities.
//       gepz=(1.-4.*s2tw)*(1.+rpv)*gepg-(1.+rnv)*geng
//       gmpz=(1.-4.*s2tw)*(1.+rpv)*gmpg-(1.+rnv)*gmng

    G4double gapz=-(1.0+rt1a)*gt1a;
    
//     G4double gepz=qwp*gepg+qwn*geng;
//     G4double gmpz=qwp*gmpg+qwn*gmng;   
//     G4double asym=-gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
//     asym=asym/(epsilon*gepg*gepg+tau*gmpg*gmpg);
//     asym=asym*(epsilon*gepg*gepz+tau*gmpg*gmpz-(1.0-4.0*s2tw_low)*epsilonp*gmpg*gapz);
//     //std::cout<<"asym_proton="<<asym<<std::endl;

    G4double genz=qwp*geng+qwn*gepg;
    G4double gmnz=qwp*gmng+qwn*gmpg;
    G4double asym_neutron = -gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
    asym_neutron =asym_neutron /(epsilon*geng*geng+tau*gmng*gmng);
    asym_neutron =asym_neutron *(epsilon*geng*genz+tau*gmng*gmnz-(1.0-4.0*s2tw_low)*epsilonp*gmng*gapz);
    //std::cout<<"asym_neutron="<<asym_neutron<<std::endl<<std::endl;

    return asym_neutron;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//---------------------------------------------------------
//    Calculates the asymmetry weighting factor for inelastic
//    scattering from the proton.  The simple approximation
//    		A_LR = -100 (ppm/GeV^2) * Q^2
//    is used.  Returns asymmetry in units of ppm.
//    Reference:
//    H.-W. Hammer and D. Drechsel, Z. Phys. A353, 321-331 (1995)
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_Pi(G4double Q2_pi)
{
//     Inelastic Asymmetry
    Q2_pi = Q2_pi/1e6;
    G4double asym=-100*Q2_pi;
    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::SetBeamEnergy(G4double energy) {
    if (energy>0) { 
      BeamEnergy = energy; 
      CheckLookupTableBounds();
      myUserInfo->StoreBeamEnergy(energy); 
      //G4cout << "#### Changing Beam Energy to " << energy/1000 << " GeV" << G4endl;
    }
    else {
      G4cout << G4endl << "##### Beam Energy must be greater than zero" << G4endl << G4endl;
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//jpan@nuclear.uwinnipeg.ca
//     To determine the energy of the electron incident on the scattering
//     vertex inside the target, the energy loss up to the scattering
//     event (inside the target material and walls) must be simulated.
//     The way this is done here is to first determine the scattering vertex
//     position, and find the path length of the electron, then calculate the
//     collision loss and radiation loss, which are added up to total energy
//     loss. 

/*
G4double QweakSimPrimaryGeneratorAction::PreTracking_Energy_Loss(G4double E_in, G4double Vertex_Z, G4double Target_A)
{
  //Incident energy E_in in units of MeV
  G4double E_Loss_Collision, E_Loss_Radiation, E_Loss;

  //part 1. energy loss by collision
  // Bethe-Bloch formula for electron collision energy loss, taken from Leo's eqn 2.66 and 2.26

  //define constant factor: Avagadro's Na=6.02e23; r=e*e/m/c/c is the classical electron radius;
  G4double 2_Pi_Na_re2_me_c2 = 0.1535; //units:[MeV cm^2/g]
 
  G4double m = 0.511; //electron mass in [MeV/c^2]
  G4double rho_H2 = 0.071; //density of H2, [g/cm^3]
  G4double rho_Al = 2.70; //density of Aluminum
  G4double I_H2 = 19.0; // mean excitation potential for H2, in units of [eV], 
                                   // I/Z = 12+7/Z [eV] if Z<13
  G4double I_Al = 166.0; // mean excitation potential for Aluminum, in units of [eV]
                                   // I/Z = 9.76+58.8*Z^(-1.19) [eV] if Z>=13

  // For relativistic electron: E = gamma*m*c^2
  // P = gamma*m*beta*c, E^2 = P^2*c^2 + m^2*c^4
  // => beta = sqrt(1-m^2/E^2)
  G4double beta = sqrt(1.0 - m*m/E_in/E_in) ;
  G4double gamma = E_in/m; 
  G4double eta = beta*gamma;

  G4double tau = E_in/m;   //kinetic energy of electron in units of [mc^2]

  //calculation for the density correction "delta", taken from Leo's 2.30
  // hnup = h*nu_p is the plasma frequency of the material
  G4double hnup_H2 = 28.816e-9 *sqrt(rho_H2*Z/A);
  G4double hnup_Al = 28.816e-9 *sqrt(rho_Al*Z/A);

  G4double C0_H2 = -(2.0*log(I_H2/(hnup_H2))+1.0);
  G4double delta_H2 = 4.6052*log10(eta)+C0_H2;

  G4double C0_Al = -(2.0*log(I_Al/(hnup_Al))+1.0);  //C0_Al = -4.24
  G4double delta_Al = 4.6052*log10(eta)+C0_Al;

  //calculation for the shell correction "C", taken from Leo's 2.33
  G4double C_H2 = (0.422377/eta/eta +0.0304043/eta/eta/eta/eta -0.00038106/eta/eta/eta/eta/eta/eta)*I_H2*I_H2*1.0e-6
                 + (3.850190/eta/eta -0.1667989/eta/eta/eta/eta +0.00157955/eta/eta/eta/eta/eta/eta)*I_H2*I_H2*1.0e-9;

  G4double C_Al = (0.422377/eta/eta +0.0304043/eta/eta/eta/eta -0.00038106/eta/eta/eta/eta/eta/eta)*I_Al*I_Al*1.0e-6
                 + (3.850190/eta/eta -0.1667989/eta/eta/eta/eta +0.00157955/eta/eta/eta/eta/eta/eta)*I_Al*I_Al*1.0e-9;

  G4double F_tau = 1-beta*beta+(tau*tau/8.0-(2*r+1)*log(2.0))/(tau+1.0)/(tau+1.0);
  G4double dE_dx_H2 = 2_Pi_Na_re2_me_c2*rho_H2*Z*A/beta/beta*(log(tau*tau*(tau+2.0)/2/(I_H2/m/c/c)/(I_H2/m/c/c))+F_tau-delta-2.0*C_H2/Z);
  G4double dE_dx_Al = 2_Pi_Na_re2_me_c2*rho_Al*Z*A/beta/beta*(log(tau*tau*(tau+2.0)/2/(I_Al/m/c/c)/(I_Al/m/c/c))+F_tau-delta-2.0*C_Al/Z);

  //Part 2. energy loss by radiation: Bremsstrahlung

  E_Loss = E_Loss_Collision + E_Loss_Radiation;
  return E_Loss;

}

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
