//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimPrimaryGeneratorAction.cc

   $Revision: 1.4 $	
   $Date: 2006/05/05 21:35:07 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:35:07 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//G4int QweakSimPrimaryGeneratorAction::kActiveOctantNumber = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI)
  : myUserInfo(myUI)
{

  G4cout << "###### Calling QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;

  // default octant [1,,8]
  kActiveOctantNumber = 1;

  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentumX  = 0.0;
  myNormMomentumY  = 0.0;
  myNormMomentumZ  = 0.0;
 
  // get my messenger
  myMessenger = new QweakSimPrimaryGeneratorActionMessenger(this);

  // initialize my own event counter
  myEventCounter = 0;

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

//jpan@nuclear.uwinnipeg.ca
  std::ofstream EventDataFile("Event.dat", std::ios::out);

  G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::QweakSimPrimaryGeneratorAction " << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction()
{

  G4cout << "###### Calling/Leaving QweakSimPrimaryGeneratorAction::~QweakSimPrimaryGeneratorAction " << G4endl;

  if (particleGun) delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
   G4cout << "###### Calling QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

  G4cout << "************************************************ myEventCounter = " << myEventCounter << G4endl;

//jpan@nuclear.uwinnipeg.ca
//  
      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition* particle = particleTable->FindParticle("e-");
      particleGun->SetParticleDefinition(particle);

   //define target geometry, these parameters will be acquired from QweakSimG4Target class in the future
   G4double TargetCenterPositionZ = -650.0*cm;
   G4double TargetLength = 35.0*cm;

   // definition of a mil = inch/1000
   static const G4double mil = 0.001*2.54*cm;
   G4double TargetWindowThickness = 5.0*mil;

   G4double PositionX_min = -1.0*mm;
   G4double PositionX_max =  1.0*mm;
   myPositionX =  (G4UniformRand()-0.5)*(PositionX_max-PositionX_min);

   G4double PositionY_min = -1.0*mm;
   G4double PositionY_max =  1.0*mm;
   myPositionY =  (G4UniformRand()-0.5)*(PositionY_max-PositionY_min);
   
		   
//   G4double meanThetaAngle =  8.4*degree;
//   G4double sigmaThetaAngle = 5.0*degree;
//   G4double ThetaAngle =  (meanThetaAngle + ((G4UniformRand()-0.5)*2.0*sigmaThetaAngle));

   G4double ThetaAngle_Min =  4.0*degree;
   G4double ThetaAngle_Max = 18.0*degree;
   G4double ThetaAngle =  ThetaAngle_Min + G4UniformRand()*(ThetaAngle_Max - ThetaAngle_Min);  

   G4double meanPhiAngle = 0.0*degree;
   G4double sigmaPhiAngle = 18.0*degree;
   G4double PhiAngle =  (meanPhiAngle + ((G4UniformRand()-0.5)*2.0*sigmaPhiAngle));

//   G4cout << "=====================> Theta Angle = " << ThetaAngle/degree << " degree" << G4endl;
//   G4cout << "=====================> Phi   Angle = " << PhiAngle/degree   << " degree" << G4endl;
  
   particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(ThetaAngle)*sin(PhiAngle),
 							  sin(ThetaAngle)*cos(PhiAngle),
 							  cos(ThetaAngle) )); 

   G4double E_in = 1165.0*MeV;
   G4double A;  // mass number A, Al_A = 27.0
   G4double Z;  // charge number Z, Al_Z = 13.0

   G4double M_n = 939.5656*MeV; //neutron mass in MeV/c^2
   G4double M_p = 938.2796*MeV;  // proton mass in MeV/c^2
   G4double Mass;
   G4double weight_n;

   G4int ReactionType = 1; // 1 - LH2 elastic
                           // 2 - Al window elastic
                           // 3 - Al window quasi-elastic proton
                           // 4 - Al window quasi-elastic neutron

   if(ReactionType==1) //LH2 target
      {
       A = 1.0;
       Z = 1.0;
       Mass = Z*M_p+(A-Z)*M_n;
       myPositionZ =  TargetCenterPositionZ + (G4UniformRand()-0.5)*TargetLength;
       weight_n = Elastic_Cross_Section_Proton(E_in, ThetaAngle)*sin(ThetaAngle);
      }
   else if(ReactionType==2) // Aluminum window
      {
       A = 27.0;
       Z = 13.0;
       Mass = Z*M_p+(A-Z)*M_n;
       //randomly select the front window or back window
       if(G4UniformRand() >0.5) //front entrance window
           {
             myPositionZ =  TargetCenterPositionZ - 0.5*TargetLength - TargetWindowThickness*G4UniformRand();
           }
       else  //back exit window
           {
             myPositionZ =  TargetCenterPositionZ + 0.5*TargetLength + TargetWindowThickness*G4UniformRand();
           }

       weight_n = Elastic_Cross_Section_Aluminum(E_in, ThetaAngle)*sin(ThetaAngle);
      }

   else if(ReactionType==3) // Aluminum window quasi-elastic proton (assume free proton)
      {
       A = 1.0;
       Z = 1.0;   
       Mass = M_p;    
       //randomly select the front window or back window
       if(G4UniformRand() >0.5) //front entrance window
           {
             myPositionZ =  TargetCenterPositionZ - 0.5*TargetLength - TargetWindowThickness*G4UniformRand();
           }
       else  //back exit window
           {
             myPositionZ =  TargetCenterPositionZ + 0.5*TargetLength + TargetWindowThickness*G4UniformRand();
           }
       weight_n = Elastic_Cross_Section_Proton(E_in, ThetaAngle)*sin(ThetaAngle);
      }

   else if(ReactionType==4) // Aluminum window quasi-elastic neutron (assume free neutron)
      {
       A = 1.0;
       Z = 1.0;   // Z needs to be set to 1 for neutron quasi elastic scattering
       Mass = M_n;    
       //randomly select the front window or back window
       if(G4UniformRand() >0.5) //front entrance window
           {
             myPositionZ =  TargetCenterPositionZ - 0.5*TargetLength - TargetWindowThickness*G4UniformRand();
           }
       else  //back exit window
           {
             myPositionZ =  TargetCenterPositionZ + 0.5*TargetLength + TargetWindowThickness*G4UniformRand();
           }

       weight_n = Quasi_Elastic_Neutron(E_in, ThetaAngle)*sin(ThetaAngle);
      }

   particleGun->SetParticlePosition(G4ThreeVector( myPositionX,
 						   myPositionY,
						   myPositionZ ));

  G4double E_f = E_in/(1.0+E_in/Mass*(1.0-cos(ThetaAngle)));
  particleGun->SetParticleEnergy(E_f);

  std::ofstream EventDataFile("Event.dat", std::ios::app);
//  EventDataFile << "event generator data file " << G4endl;
   EventDataFile<<E_f<<"      "<<ThetaAngle/degree<<"      "<<PhiAngle/degree<<"      "<<weight_n<<G4endl;

//*************************************
 
//  myNormMomentumX =  myPE.Momentum[0]/myPE.KineticEnergy;
//  myNormMomentumY =  myPE.Momentum[1]/myPE.KineticEnergy;
//  myNormMomentumZ =  myPE.Momentum[2]/myPE.KineticEnergy;

//  myNormMomentum = G4ThreeVector(myNormMomentumX,myNormMomentumY,myNormMomentumZ);


  G4cout <<"%%%%> QweakSimPrimaryGeneratorAction::GeneratePrimaries, kActiveOctantNumber = " << kActiveOctantNumber << G4endl;

  myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);

//  particleGun->SetParticleMomentumDirection(G4ThreeVector(myNormMomentum));
  
  
  // finally : fire !!!
  particleGun->GeneratePrimaryVertex(anEvent);

  // fill user track info: store Q2 value of this primary 

  G4double myQ2 = 4.0*E_in*E_f*sin(ThetaAngle/2.0)*sin(ThetaAngle/2.0);
  myUserInfo->SetPrimaryQ2( myQ2 );

  // fill user track info: store cross section weight (micro barn) of this primary 
  myUserInfo->SetCrossSectionWeight( (G4double) weight_n);

  // fill user track info: store primary event number 
  myUserInfo->SetPrimaryEventNumber( (G4int) myEventCounter );
  
  // print the stored values
  myUserInfo->Print();
  
  // increase my own event counter for next primary
  myEventCounter += 1;


   G4cout << "###### Leaving QweakSimPrimaryGeneratorAction::GeneratePrimaries" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca

G4double QweakSimPrimaryGeneratorAction::Elastic_Cross_Section_Proton(G4double E_in, G4double Theta)
{
//     calculate proton cross sections using the dipole fits to the form factors.
     
//     Angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.
      G4double Theta_Min = 1.745329E-4;
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
      G4double EF = E_in/ETA;
//    MeV^2
      G4double Q2 = 4.0*E_in*EF*STH*STH;
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
      return Sigma_Dipole;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca

G4double QweakSimPrimaryGeneratorAction::Elastic_Cross_Section_Aluminum(G4double E_in, G4double Theta)
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
      G4double E_f = E_in/ETA;
   
      G4double q2 = 4*E_in*E_f*STH*STH;     //unit: MeV^2
      q2 = q2/1000000*(1.0/0.197)*(1.0/0.197);  //convert MeV^2 into fm^(-2)
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

      return SigmaMott*F_2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//jpan@nuclear.uwinnipeg.ca Sat Apr 18 11:28:18 CDT 2009

G4double QweakSimPrimaryGeneratorAction::Quasi_Elastic_Neutron(G4double E_in, G4double Theta)
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
      G4double EF = E_in/ETA;
//    MeV^2
      G4double Q2 = 4.*E_in*EF*STH*STH;
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPrimaryGeneratorAction.cc,v $
//      Revision 1.4  2006/05/05 21:35:07  grimm
//      Added the rotation of the generated tracks into any chosen octant.
//
//      Revision 1.3  2006/01/31 20:15:19  grimm
//      Implemented the usage of the ROOT input event file generated by Michael's Eventgenerator. This will replace the usage of the Root input event file based on the Geant3 output ntuple.
//
//      Revision 1.2  2005/12/27 19:14:12  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
