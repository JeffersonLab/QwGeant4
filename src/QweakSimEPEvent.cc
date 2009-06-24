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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   const G4double QweakSimEPEvent::TargetCenterPositionZ = -650.0*cm;
   const G4double QweakSimEPEvent::TargetLength = 35.0*cm;

   // definition of a mil = inch/1000
   const G4double QweakSimEPEvent::mil = 0.001*2.54*cm;
   const G4double QweakSimEPEvent::TargetWindowThickness = 5.0*mil;

   const G4double QweakSimEPEvent::M_n = 939.5656*MeV; //neutron mass in MeV/c^2
   const G4double QweakSimEPEvent::M_p = 938.2796*MeV;  // proton mass in MeV/c^2

   const G4double QweakSimEPEvent::Theta_Min = 1.745329E-4;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//QweakSimEPEvent::QweakSimEPEvent( QweakSimUserInformation* myUI)
//                : myUserInfo(myUI)
QweakSimEPEvent::QweakSimEPEvent()
{
  // G4cout << "###### Calling QweakSimEPEvent::QweakSimEPEvent () " << G4endl;

  meanPhiAngle = 0.0*degree;
  sigmaPhiAngle = 18.0*degree;
  ThetaAngle_Min =  4.0*degree;
  ThetaAngle_Max = 18.0*degree;

  ReactionType = 1;
  ReactionRegion = 1;

  // G4cout << "###### Leavinging QweakSimEPEvent::QweakSimEPEvent () " << G4endl;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEvent::~QweakSimEPEvent()
{

  // G4cout << "###### Calling QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;

  //G4cout << "###### Leavinging QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::GetVertexZ()
{

   if(ReactionType==1) //LH2 target
     myPositionZ =  TargetCenterPositionZ + (G4UniformRand()-0.5)*TargetLength;
   else if(ReactionType==2 || ReactionType==3 || ReactionType==4) {// Aluminum window
       // select the front window or back window by ReactionRegion
       if(ReactionRegion == 2) //front entrance window
             myPositionZ =  TargetCenterPositionZ - 0.5*TargetLength - TargetWindowThickness*G4UniformRand();
       else  //back exit window
             myPositionZ =  TargetCenterPositionZ + 0.5*TargetLength + TargetWindowThickness*G4UniformRand();
      }
  return myPositionZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector QweakSimEPEvent::GetMomentumDirection(){

   ThetaAngle =  ThetaAngle_Min + G4UniformRand()*(ThetaAngle_Max - ThetaAngle_Min);
   PhiAngle =  (meanPhiAngle + ((G4UniformRand()-0.5)*2.0*sigmaPhiAngle));

//   G4cout << "=====================> Theta Angle = " << ThetaAngle/degree << " degree" << G4endl;
//   G4cout << "=====================> Phi   Angle = " << PhiAngle/degree   << " degree" << G4endl;

   return G4ThreeVector(sin(ThetaAngle)*sin(PhiAngle),
                        sin(ThetaAngle)*cos(PhiAngle),
                        cos(ThetaAngle) ); 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::GetanEvent(G4double E_in, 
                                 G4double &fCrossSection, 
                                 G4double &fWeightN,
                                 G4double &Q2,
                                 G4double &E_out,
                                 G4ThreeVector &MomentumDirection,
                                 G4double &theta,
                                 G4double &phi)
{
   MomentumDirection = GetMomentumDirection();
   theta = ThetaAngle/degree;
   phi = PhiAngle/degree;

   if(ReactionType==1) //LH2 target
      {
       A = 1.0;
       Z = 1.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection = Elastic_Cross_Section_Proton(E_in, ThetaAngle, fWeightN, Q2, E_out);
      }
   else if(ReactionType==2) // Aluminum window
      {
       A = 27.0;
       Z = 13.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection = Elastic_Cross_Section_Aluminum(E_in, ThetaAngle, fWeightN, Q2, E_out);
      }

   else if(ReactionType==3) // Aluminum window quasi-elastic proton (assume free proton)
      {
       A = 1.0;
       Z = 1.0;   
       Mass = M_p;    
       fCrossSection = Elastic_Cross_Section_Proton(E_in, ThetaAngle, fWeightN, Q2, E_out);
      }

   else if(ReactionType==4) // Aluminum window quasi-elastic neutron (assume free neutron)
      {
       A = 1.0;
       Z = 1.0;   // Z needs to be set to 1 for neutron quasi elastic scattering
       Mass = M_n;    
       fCrossSection = Quasi_Elastic_Neutron(E_in, ThetaAngle, fWeightN, Q2, E_out);
      }


}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca

G4double QweakSimEPEvent::Elastic_Cross_Section_Proton(G4double E_in,
                                                       G4double Theta,
                                                       G4double &fWeightN,
                                                       G4double &Q2,
                                                       G4double &E_out)
{
//     calculate proton cross sections using the dipole fits to the form factors.
     
//     Angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double mu = 2.793;
      G4double Z = 1.0;
      G4double A = 1.0;
      G4double M = M_p*A;

//    E_in units is MeV

//     The Mott cross section blows up at small Theta.  For
//     the purposes of this routine, we arbitrarily restrict
//     angles to be greater than a minimum.
      if (Theta<Theta_Min)
         Theta = Theta_Min;

      G4double CTH = cos(Theta/2.);
      G4double STH = sin(Theta/2.);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
//    MeV^2
      Q2 = 4.0*E_in*E_out*STH*STH;
      G4double tau = Q2/4.0/M/M;
//    Mott scatering
      G4double CrossSection = (Z*0.72/E_in*CTH/STH/STH)*(Z*0.72/E_in*CTH/STH/STH)/ETA;
//    Units: ub/sr
      G4double Mott = CrossSection*10000.0;
//    Cross section
      G4double GEP_DIPOLE = 1.0/(1.0+Q2/1.E6/Lamda_2)*(1.0+Q2/1.E6/Lamda_2);
      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
      G4double FAC = 1.0/(1.0+tau);

      G4double Sigma_Dipole = Mott*(GEP_DIPOLE*GEP_DIPOLE*FAC+tau*GMP_DIPOLE*GMP_DIPOLE*(FAC+2.*T2THE));
      fWeightN = Sigma_Dipole*sin(ThetaAngle);
      return Sigma_Dipole;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca

G4double QweakSimEPEvent::Elastic_Cross_Section_Aluminum(G4double E_in,
                                                         G4double Theta,
                                                         G4double &fWeightN,
                                                         G4double &Q2,
                                                         G4double &E_out)
{
//     calculate Aluminum elastic cross sections
     
//     incident angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.
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
//     The Mott cross section blows up at small Theta. For
//     the purposes of this routine, we arbitrarily restrict
//     angles to be greater than a minimum.
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

G4double QweakSimEPEvent::Quasi_Elastic_Neutron(G4double E_in,
                                                G4double Theta,
                                                G4double &fWeightN,
                                                G4double &Q2,
                                                G4double &E_out)
{
//  cout<<"===>>>>Calling Quasi_Elastic_Neutron"<<endl;

//     Angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.
//     In this subroutine units are MeV

      G4double Theta_Min = 1.745329E-4;
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double mu = 2.793;
      G4double mu_n = -1.91;
      G4double Z = 1.0;
      G4double A = 1.0;
      G4double M = M_p;

//    E_in units is MeV

//     The Mott cross section blows up at small Theta.  For
//     the purposes of this routine, we arbitrarily restrict
//     angles to be greater than a minimum.
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
      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
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
