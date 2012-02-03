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
#include "../include/QweakSimEPEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   const G4double QweakSimEPEvent::TargetLength = 34.346*cm;

   // definition of a mil = inch/1000
   const G4double QweakSimEPEvent::mil = 0.001*2.54*cm;
   const G4double QweakSimEPEvent::TargetWindowThickness = 5.0*mil;

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

  ReactionType = 1;
  ReactionRegion = 1;
  kActiveOctantNumber = 1;  //default octant 1, choose from [1,8]

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

   if(ReactionRegion==1) // target
     myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*TargetLength;

       // select the front window or back window by ReactionRegion
   else if(ReactionRegion == 2) //front entrance window
     myPositionZ =  myUserInfo->TargetCenterPositionZ - 0.5*TargetLength - TargetWindowThickness*G4UniformRand();

   else if(ReactionRegion == 3) //back exit window
     myPositionZ =  myUserInfo->TargetCenterPositionZ + 0.5*TargetLength + TargetWindowThickness*G4UniformRand();

   else
     myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*TargetLength; //default region

  return myPositionZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector QweakSimEPEvent::GetMomentumDirection()
{

   // Generate flat phi distribution
    PhiAngle =  PhiAngle_Min + G4UniformRand()*(PhiAngle_Max - PhiAngle_Min);
    G4double cosPhi = cos(PhiAngle);
    G4double sinPhi = sin(PhiAngle);

    G4double cosTheta;
    G4double sinTheta;

    // Generate flat theta distribution
    if (Isotropy == 0) {
        ThetaAngle = ThetaAngle_Min + G4UniformRand()*(ThetaAngle_Max - ThetaAngle_Min);
	cosTheta = cos(ThetaAngle);
        sinTheta = sin(ThetaAngle);
    }
    
   // Generate uniform distribution on spherical surface. See for example
   // http://hypernews.slac.stanford.edu/HyperNews/geant4/get/particles/31/2.html
   // or more generally http://mathworld.wolfram.com/SpherePointPicking.html       
    else if (Isotropy == 1) {
        G4double cosThetaMax = cos(ThetaAngle_Max);
        G4double cosThetaMin = cos(ThetaAngle_Min);   
        cosTheta = cosThetaMin + G4UniformRand()*(cosThetaMax - cosThetaMin);
        sinTheta = sqrt(1. - cosTheta * cosTheta);
        ThetaAngle = acos(cosTheta);
    }
    else {
        std::cerr<<"Warning: unkown isotropy type, use type 0 instead."<<std::endl;
    }
    
    G4double ux= sinTheta * cosPhi;
    G4double uy= sinTheta * sinPhi;
    G4double uz =cosTheta;

    G4ThreeVector myNormMomentum(ux,uy,uz);
       
    myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

    return myNormMomentum; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::GetanEvent(G4double E_in, 
                                 G4double &fCrossSection, 
                                 G4double &fWeightN,
                                 G4double &Q2,
                                 G4double &E_out,
                                 G4ThreeVector &MomentumDirection,
                                 G4double &theta,
                                 G4double &phi,
				 G4double &Asymmetry)
{


   if(ReactionType==0) //straight-through beam
      {
       fCrossSection = 1.0;
       fWeightN = 1.0;
       Q2 = 0.0;
       E_out = E_in;
       //MomentumDirection = G4ThreeVector(0.0,0.0,1.0);
       //theta = 0.0;
       //phi = 0.0;
       theta = MomentumDirection.theta()/degree;
       phi = MomentumDirection.phi()/degree;
       Asymmetry = 0.0;
      }
   else
      {
	MomentumDirection = GetMomentumDirection();
        theta = ThetaAngle/degree;
        phi = PhiAngle/degree;
      }
    
   if(ReactionType==1) //LH2 target
      {
       A = 1.0;
       Z = 1.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection = Elastic_Cross_Section_Proton(E_in, ThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(ThetaAngle, E_in);
      }
      
   else if(ReactionType==2) // Aluminum window
      {
       A = 27.0;
       Z = 13.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection = Elastic_Cross_Section_Aluminum(E_in, ThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_AL(ThetaAngle, E_in);
      }

   else if(ReactionType==3) // Aluminum window quasi-elastic proton (assume free proton)
      {
       A = 1.0;
       Z = 1.0;   
       Mass = M_p;    
       fCrossSection = Elastic_Cross_Section_Proton(E_in, ThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(ThetaAngle, E_in);
      }

   else if(ReactionType==4) // Aluminum window quasi-elastic neutron (assume free neutron)
      {
       A = 1.0;
       Z = 1.0;   // Z needs to be set to 1 for neutron quasi elastic scattering
       Mass = M_n;    
       fCrossSection = Quasi_Elastic_Neutron(E_in, ThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EN(ThetaAngle, E_in);
      }

   else if(ReactionType==5) // Delta resonances
      {
       fCrossSection = Delta_Resonance(E_in, ThetaAngle, fWeightN, Q2, E_out);
       //std::cout<<E_in<<" "<<ThetaAngle/degree<<" "<<fWeightN<<" "<<Q2<<" "<<E_out<<std::endl;
       Asymmetry = GetAsymmetry_Pi(Q2);
      }
   else if(ReactionType==6) // Moller scattering
      {
	//  Peiqing, Dec 12, 2011
	//  Small angle recoil electrons are directly dumped for now.
       G4double E_recoil;
       G4double ThetaRecoil;
       fCrossSection = Moller_Scattering(E_in, ThetaAngle, E_out, 
					 E_recoil, ThetaRecoil, 
                                         Q2, fWeightN, Asymmetry);
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
      fWeightN = Sigma_Dipole*sin(ThetaAngle);
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
      fWeightN = Xsect*sin(ThetaAngle);
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
      fWeightN = Sigma_Dipole_n*sin(ThetaAngle);
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
  fWeightN = xsect*sin(Theta)*(E_beam - M_electron)/1000.0;

  std::cout<<"Q2="<<Q2<<std::endl;
  
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

      q2 = q2*1e6;  // convert to MeV^2 for Q2
      
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
    G4double gesg= 0;
    G4double gmsg= 0;

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
    G4double asym=-100*Q2_pi;
    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


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
