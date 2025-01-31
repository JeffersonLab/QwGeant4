//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: G4WentzelVIModel.cc 81865 2014-06-06 11:32:58Z gcosmo $
//
// -------------------------------------------------------------------
//
// GEANT4 Class file
//
//
// File name:   G4WentzelVIModel
//
// Author:      V.Ivanchenko 
//
// Creation date: 09.04.2008 from G4MuMscModel
//
// Modifications:
// 27-05-2010 V.Ivanchenko added G4WentzelOKandVIxSection class to
//              compute cross sections and sample scattering angle
//
//
// Class Description:
//
// Implementation of the model of multiple scattering based on
// G.Wentzel, Z. Phys. 40 (1927) 590.
// H.W.Lewis, Phys Rev 78 (1950) 526.
// J.M. Fernandez-Varea et al., NIM B73 (1993) 447.
// L.Urban, CERN-OPEN-2006-077.

// -------------------------------------------------------------------
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "processes/electromagnetic/standard/QweakSimWentzelVIModel.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ParticleChangeForMSC.hh"
#include "G4PhysicsTableHelper.hh"
#include "G4ElementVector.hh"
#include "G4ProductionCutsTable.hh"
#include "G4LossTableManager.hh"
#include "G4Log.hh"
#include "G4Exp.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using namespace std;

QweakSimWentzelVIModel::QweakSimWentzelVIModel(const G4String& nam) :
  G4VMscModel(nam),
  numlimit(0.1),
  currentCouple(0),
  cosThetaMin(1.0),
  inside(false),
  singleScatteringMode(false)
{
  invsqrt12 = 1./sqrt(12.);
  tlimitminfix = 1.e-6*mm;
  lowEnergyLimit = 1.0*eV;
  particle = 0;
  nelments = 5;
  xsecn.resize(nelments);
  prob.resize(nelments);
  theManager = G4LossTableManager::Instance();
  wokvi = new G4WentzelOKandVIxSection();
  fixedCut = -1.0;

  preKinEnergy = tPathLength = zPathLength = lambdaeff = currentRange 
    = xtsec = 0;
  currentMaterialIndex = 0;
  cosThetaMax = cosTetMaxNuc = 1.0;

  fParticleChange = 0;
  currentCuts = 0;
  currentMaterial = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimWentzelVIModel::~QweakSimWentzelVIModel()
{
  delete wokvi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimWentzelVIModel::Initialise(const G4ParticleDefinition* p,
				  const G4DataVector& cuts)
{
  // reset parameters
  SetupParticle(p);
  currentRange = 0.0;

  cosThetaMax = cos(PolarAngleLimit());
  //G4cout << "QweakSimWentzelVIModel::Initialise " << p->GetParticleName() << G4endl;
  wokvi->Initialise(p, cosThetaMax);
  /*
  G4cout << "QweakSimWentzelVIModel: " << particle->GetParticleName()
         << "  1-cos(ThetaLimit)= " << 1 - cosThetaMax 
	 << G4endl;
  */
  currentCuts = &cuts;

  // set values of some data members
  fParticleChange = GetParticleChangeForMSC(p);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimWentzelVIModel::ComputeCrossSectionPerAtom( 
                             const G4ParticleDefinition* p,
			     G4double kinEnergy,
			     G4double Z, G4double,
			     G4double cutEnergy, G4double)
{
  G4double cross = 0.0;
  if(p != particle) { SetupParticle(p); }
  if(kinEnergy < lowEnergyLimit) { return cross; }
  if(!CurrentCouple()) {
    G4Exception("QweakSimWentzelVIModel::ComputeCrossSectionPerAtom", "em0011",
		FatalException, " G4MaterialCutsCouple is not defined");
    return 0.0;
  }
  DefineMaterial(CurrentCouple());
  cosTetMaxNuc = wokvi->SetupKinematic(kinEnergy, currentMaterial);
  if(cosTetMaxNuc < 1.0) {
    G4double cut = cutEnergy;
    if(fixedCut > 0.0) { cut = fixedCut; }
    cosTetMaxNuc = wokvi->SetupTarget(G4lrint(Z), cut);
    cross = wokvi->ComputeTransportCrossSectionPerAtom(cosTetMaxNuc);
    /*
    if(p->GetParticleName() == "e-")      
    G4cout << "QweakSimWentzelVIModel::CS: Z= " << G4int(Z) << " e(MeV)= " << kinEnergy 
	   << " 1-cosN= " << 1 - cosTetMaxNuc << " cross(bn)= " << cross/barn
	   << " " << particle->GetParticleName() << G4endl;
    */
  }
  return cross;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimWentzelVIModel::StartTracking(G4Track* track)
{
  SetupParticle(track->GetDynamicParticle()->GetDefinition());
  inside = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimWentzelVIModel::ComputeTruePathLengthLimit(
                             const G4Track& track,
			     G4double& currentMinimalStep)
{
  G4double tlimit = currentMinimalStep;
  const G4DynamicParticle* dp = track.GetDynamicParticle();
  G4StepPoint* sp = track.GetStep()->GetPreStepPoint();
  G4StepStatus stepStatus = sp->GetStepStatus();
  singleScatteringMode = false;

  // FIXME
  ePolarized=false;
  debugPrint=false;
  if(strcmp(track.GetParticleDefinition()->GetParticleName().data() , "e-") == 0)
    if(strcmp(track.GetMaterial()->GetName(),"PBA") == 0){
      if(track.GetPolarization().getR() >= 0.1) debugPrint=true;
      if(sqrt(pow(track.GetPolarization().getX(),2)+pow(track.GetPolarization().getY(),2))>0.01){
	ePolarized=true;
	polarization=track.GetPolarization();
	eEnergy=track.GetTotalEnergy();
      }
    }
  debugPrint=false;
  // FIXME

  //G4cout << "QweakSimWentzelVIModel::ComputeTruePathLengthLimit stepStatus= " 
  //	 << stepStatus << "  " << track.GetDefinition()->GetParticleName() 
  //	 << G4endl;

  // initialisation for each step, lambda may be computed from scratch
  preKinEnergy  = dp->GetKineticEnergy();
  DefineMaterial(track.GetMaterialCutsCouple());
  lambdaeff = GetTransportMeanFreePath(particle,preKinEnergy);
  currentRange = GetRange(particle,preKinEnergy,currentCouple);
  cosTetMaxNuc = wokvi->SetupKinematic(preKinEnergy, currentMaterial);

  //G4cout << "lambdaeff= " << lambdaeff << " Range= " << currentRange
  //	 << " tlimit= " << tlimit << " 1-cost= " << 1 - cosTetMaxNuc << G4endl;

  // extra check for abnormal situation
  // this check needed to run MSC with eIoni and eBrem inactivated
  if(tlimit > currentRange) { tlimit = currentRange; }

  // stop here if small range particle
  if(inside || tlimit < tlimitminfix) { 
    return ConvertTrueToGeom(tlimit, currentMinimalStep); 
  }

  // pre step
  G4double presafety = sp->GetSafety();
  // far from geometry boundary
  if(currentRange < presafety) {
    inside = true;  
    return ConvertTrueToGeom(tlimit, currentMinimalStep);
  }

  // compute presafety again if presafety <= 0 and no boundary
  // i.e. when it is needed for optimization purposes
  if(stepStatus != fGeomBoundary && presafety < tlimitminfix) {
    presafety = ComputeSafety(sp->GetPosition(), tlimit); 
    if(currentRange < presafety) {
      inside = true;  
      return ConvertTrueToGeom(tlimit, currentMinimalStep);
    }
  }
  /* 
  G4cout << "e(MeV)= " << preKinEnergy/MeV
	 << "  " << particle->GetParticleName() 
	 << " CurLimit(mm)= " << tlimit/mm <<" safety(mm)= " << presafety/mm
	 << " R(mm)= " <<currentRange/mm
	 << " L0(mm^-1)= " << lambdaeff*mm 
	 <<G4endl;
  */

  // natural limit for high energy
  G4double rlimit = std::max(facrange*currentRange, 
			     0.7*(1.0 - cosTetMaxNuc)*lambdaeff);

  // low-energy e-
  if(cosThetaMax > cosTetMaxNuc) {
    rlimit = std::min(rlimit, facsafety*presafety);
  }
   
  // cut correction
  G4double rcut = currentCouple->GetProductionCuts()->GetProductionCut(1);
  //G4cout << "rcut= " << rcut << " rlimit= " << rlimit << " presafety= " 
  // << presafety << " 1-cosThetaMax= " <<1-cosThetaMax 
  //<< " 1-cosTetMaxNuc= " << 1-cosTetMaxNuc << G4endl;
  if(rcut > rlimit) { rlimit = std::min(rlimit, rcut*sqrt(rlimit/rcut)); }
 
  if(rlimit < tlimit) { tlimit = rlimit; }

  tlimit = std::max(tlimit, tlimitminfix);

  // step limit in infinite media
  tlimit = std::min(tlimit, 50*currentMaterial->GetRadlen()/facgeom);

  //compute geomlimit and force few steps within a volume
  if (steppingAlgorithm == fUseDistanceToBoundary 
      && stepStatus == fGeomBoundary) {

    G4double geomlimit = ComputeGeomLimit(track, presafety, currentRange);
    tlimit = std::min(tlimit, geomlimit/facgeom);
  } 

  /*    
  G4cout << particle->GetParticleName() << " e= " << preKinEnergy
	 << " L0= " << lambdaeff << " R= " << currentRange
	 << "tlimit= " << tlimit  
  	 << " currentMinimalStep= " << currentMinimalStep << G4endl;
  */
  return ConvertTrueToGeom(tlimit, currentMinimalStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimWentzelVIModel::ComputeGeomPathLength(G4double truelength)
{
  tPathLength  = truelength;
  zPathLength  = tPathLength;

  if(lambdaeff > 0.0 && lambdaeff != DBL_MAX) {
    G4double tau = tPathLength/lambdaeff;
    //G4cout << "ComputeGeomPathLength: tLength= " << tPathLength
    //	 << " Leff= " << lambdaeff << " tau= " << tau << G4endl; 
    // small step
    if(tau < numlimit) {
      zPathLength *= (1.0 - 0.5*tau + tau*tau/6.0);

      // medium step
    } else {
      G4double e1 = 0.0;
      if(currentRange > tPathLength) {
	e1 = GetEnergy(particle,currentRange-tPathLength,currentCouple);
      }
      e1 = 0.5*(e1 + preKinEnergy);
      cosTetMaxNuc = wokvi->SetupKinematic(e1, currentMaterial);
      lambdaeff = GetTransportMeanFreePath(particle,e1);
      zPathLength = lambdaeff*(1.0 - G4Exp(-tPathLength/lambdaeff));
    }
  } else { lambdaeff = DBL_MAX; }
  //G4cout<<"Comp.geom: zLength= "<<zPathLength<<" tLength= "<<tPathLength<<G4endl;
  return zPathLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimWentzelVIModel::ComputeTrueStepLength(G4double geomStepLength)
{
  // initialisation of single scattering x-section
  xtsec = 0.0;
  cosThetaMin = cosTetMaxNuc;
  /*  
  G4cout << "ComputeTrueStepLength: Step= " << geomStepLength 
	 << "  Lambda= " <<  lambdaeff 
  	 << " 1-cosThetaMaxNuc= " << 1 - cosTetMaxNuc << G4endl;
  */
  // pathalogical case
  if(lambdaeff == DBL_MAX) { 
    singleScatteringMode = true;
    zPathLength  = geomStepLength;
    tPathLength  = geomStepLength;
    cosThetaMin = 1.0;

    // normal case
  } else {

    // small step use only single scattering
    static const G4double singleScatLimit = 1.0e-7;
    if(geomStepLength < lambdaeff*singleScatLimit*(1.0 - cosTetMaxNuc)) {
      singleScatteringMode = true;
      cosThetaMin = 1.0;
      zPathLength  = geomStepLength;
      tPathLength  = geomStepLength;

      // step defined by transportation 
    } else if(geomStepLength != zPathLength) { 

      // step defined by transportation 
      zPathLength  = geomStepLength;
      G4double tau = geomStepLength/lambdaeff;
      tPathLength  = zPathLength*(1.0 + 0.5*tau + tau*tau/3.0); 

      // energy correction for a big step
      if(tau > numlimit) {
	G4double e1 = 0.0;
	if(currentRange > tPathLength) {
	  e1 = GetEnergy(particle,currentRange-tPathLength,currentCouple);
	}
	e1 = 0.5*(e1 + preKinEnergy);
	cosTetMaxNuc = wokvi->SetupKinematic(e1, currentMaterial);
	lambdaeff = GetTransportMeanFreePath(particle,e1);
	tau = zPathLength/lambdaeff;
      
	if(tau < 0.999999) { tPathLength = -lambdaeff*G4Log(1.0 - tau); } 
	else               { tPathLength = currentRange; }
      }
    }
  }

  // check of step length
  // define threshold angle between single and multiple scattering 
  if(!singleScatteringMode) { cosThetaMin = 1.0 - 1.5*tPathLength/lambdaeff; }

  // recompute transport cross section - do not change energy
  // anymore - cannot be applied for big steps
  if(cosThetaMin > cosTetMaxNuc) {

    // new computation
    G4double cross = ComputeXSectionPerVolume();
    //G4cout << "%%%% cross= " << cross << "  xtsec= " << xtsec << G4endl;
    if(cross <= 0.0) {
      singleScatteringMode = true;
      tPathLength = zPathLength; 
      lambdaeff = DBL_MAX;
      cosThetaMin = 1.0;
    } else if(xtsec > 0.0) {

      lambdaeff = 1./cross; 
      G4double tau = zPathLength*cross;
      if(tau < numlimit) { 
	tPathLength = zPathLength*(1.0 + 0.5*tau + tau*tau/3.0); 
      } 
      else if(tau < 0.999999) { tPathLength = -lambdaeff*G4Log(1.0 - tau); } 
      else                    { tPathLength = currentRange; }

      if(tPathLength > currentRange) { tPathLength = currentRange; }
    } 
  }

  /*     
  G4cout <<"Comp.true: zLength= "<<zPathLength<<" tLength= "<<tPathLength
	 <<" Leff(mm)= "<<lambdaeff/mm<<" sig0(1/mm)= " << xtsec <<G4endl;
  G4cout << particle->GetParticleName() << " 1-cosThetaMin= " << 1-cosThetaMin
	 << " 1-cosTetMaxNuc= " << 1-cosTetMaxNuc 
	 << " e(MeV)= " << preKinEnergy/MeV << "  "  
	 << singleScatteringMode << G4endl;
  */
  return tPathLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector& 
QweakSimWentzelVIModel::SampleScattering(const G4ThreeVector& oldDirection,
				   G4double safety)
{
  fDisplacement.set(0.0,0.0,0.0);
  //G4cout << "!##! QweakSimWentzelVIModel::SampleScattering for " 
  //	 << particle->GetParticleName() << G4endl;

  // ignore scattering for zero step length and energy below the limit
  if(preKinEnergy < lowEnergyLimit || tPathLength <= 0.0) 
    { return fDisplacement; }
  
  G4double invlambda = 0.0;
  if(lambdaeff < DBL_MAX) { invlambda = 0.5/lambdaeff; }

  // use average kinetic energy over the step
  G4double cut = (*currentCuts)[currentMaterialIndex];
  if(fixedCut > 0.0) { cut = fixedCut; }
  /*  
  G4cout <<"SampleScat: E0(MeV)= "<< preKinEnergy/MeV
  	 << " Leff= " << lambdaeff <<" sig0(1/mm)= " << xtsec 
 	 << " xmsc= " <<  tPathLength*invlambda 
	 << " safety= " << safety << G4endl;
  */

  // step limit due msc
  G4int nMscSteps = 1;
  G4double x0 = tPathLength;
  G4double z0 = x0*invlambda;
  G4double zzz = 0.0;

  // large scattering angle case - two step approach

  if(!singleScatteringMode) {
    static const G4double zzmin = 0.05;
    if(z0 > zzmin && safety > tlimitminfix) { 
      x0 *= 0.5; 
      z0 *= 0.5;
      nMscSteps = 2;
    } 
    if(z0 > zzmin) { zzz = G4Exp(-1.0/z0); }
  } 

  // step limit due to single scattering
  G4double x1 = 2*tPathLength;
  if(0.0 < xtsec) { x1 = -G4Log(G4UniformRand())/xtsec; }

  // no scattering case
  if(singleScatteringMode && x1 > tPathLength)  
    { return fDisplacement; }

  const G4ElementVector* theElementVector = 
    currentMaterial->GetElementVector();
  G4int nelm = currentMaterial->GetNumberOfElements();

  // geometry
  G4double sint, cost, phi;
  G4ThreeVector temp(0.0,0.0,1.0);

  // current position and direction relative to the end point
  // because of magnetic field geometry is computed relatively to the 
  // end point of the step 
  G4ThreeVector dir(0.0,0.0,1.0);
  fDisplacement.set(0.0,0.0,-zPathLength);

  G4double mscfac = zPathLength/tPathLength;

  // start a loop 
  G4double x2 = x0;
  G4double step, z;
  G4bool singleScat;
  /*
    G4cout << "Start of the loop x1(mm)= " << x1 << "  x2(mm)= " << x2 
    << " 1-cost1= " << 1 - cosThetaMin << "  " << singleScatteringMode 
	   << " xtsec= " << xtsec << "  "  << nMscSteps << G4endl;
  */
  do {

    //G4cout << "# x1(mm)= "<< x1<< " x2(mm)= "<< x2 << G4endl;
    // single scattering case
    if(singleScatteringMode && x1 > x2) { break; }

    // what is next single of multiple?
    if(x1 <= x2) { 
      step = x1;
      singleScat = true;
    } else {
      step = x2;
      singleScat = false;
    }

    //G4cout << "# step(mm)= "<< step<< "  singlScat= "<< singleScat << G4endl;

    // new position
    fDisplacement += step*mscfac*dir;

    if(singleScat) {

      // select element
      G4int i = 0;
      if(nelm > 1) {
	G4double qsec = G4UniformRand()*xtsec;
	for (; i<nelm; ++i) { if(xsecn[i] >= qsec) { break; } }
      }
      G4double cosTetM = 
	wokvi->SetupTarget(G4lrint((*theElementVector)[i]->GetZ()), cut);
      //G4cout << "!!! " << cosThetaMin << "  " << cosTetM << "  " 
      //       << prob[i] << G4endl;
      temp = wokvi->SampleSingleScattering(cosThetaMin, cosTetM, prob[i]);

      //FIXME
      cost=cos(temp.getTheta());
      sint = sqrt((1.0 - cost)*(1.0 + cost));
      phi=temp.getPhi();
      if(ePolarized){
	if(debugPrint) G4cout<<" ~~sc~~ "<<nMscSteps<<G4endl;
	G4double _prob=G4UniformRand();
	G4double _amplitude=1.0/eEnergy * sint *
			     sqrt(pow(polarization.getX(),2)+pow(polarization.getY(),2));//scale by transvers polarization
	if(_amplitude > 1 ) _amplitude=1;
	if( _prob < _amplitude * sin(phi-pi) )
	  phi-=pi;
	phi+= polarization.getPhi() - oldDirection.getPhi();
	if(phi<0) phi+=twopi;
	else if(phi>twopi) phi=fmod(phi,twopi);
	G4double vx1 = sint*cos(phi);
	G4double vy1 = sint*sin(phi);
	temp.set(vx1,vy1,cost);
      }
      //FIXME

      // direction is changed
      temp.rotateUz(dir);
      dir = temp;

      // new proposed step length
      x2 -= step; 
      x1  = -G4Log(G4UniformRand())/xtsec; 

    // multiple scattering
    } else { 
      --nMscSteps;
      x1 -= step;
      x2  = x0;

      // sample z in interval 0 - 1
      do {
	z = -z0*G4Log(1.0 - (1.0 - zzz)*G4UniformRand());
      } while(z > 1.0);
      cost = 1.0 - 2.0*z/*factCM*/;
      if(cost > 1.0)       { cost = 1.0; }
      else if(cost < -1.0) { cost =-1.0; }
      sint = sqrt((1.0 - cost)*(1.0 + cost));
      phi  = twopi*G4UniformRand();
      //FIXME
      if(ePolarized){
	if(debugPrint) G4cout<<" ~~msc~~ "<<nMscSteps<<G4endl;
	G4double _prob=G4UniformRand();
	G4double _amplitude=1.0/eEnergy * sint* 
			     sqrt(pow(polarization.getX(),2)+pow(polarization.getY(),2));//scale by transvers polarization
	if(_amplitude > 1 ) _amplitude=1;
	if( _prob < _amplitude * sin(phi-pi) )
	  phi-=pi;
	phi+= polarization.getPhi() - oldDirection.getPhi();
	if(phi<0) phi+=twopi;
	else if(phi>twopi) phi=fmod(phi,twopi);
      }
      //FIXME
      G4double vx1 = sint*cos(phi);
      G4double vy1 = sint*sin(phi);

      // lateral displacement  
      if (latDisplasment && safety > tlimitminfix) {
	G4double rms = invsqrt12*sqrt(2*z0);
	G4double r   = x0*mscfac;
	G4double dx  = r*(0.5*vx1 + rms*G4RandGauss::shoot(0.0,1.0));
	G4double dy  = r*(0.5*vy1 + rms*G4RandGauss::shoot(0.0,1.0));
	G4double dz;
	G4double d   = r*r - dx*dx - dy*dy;

	// change position
	if(d >= 0.0)  { 
	  dz = sqrt(d) - r; 
	  temp.set(dx,dy,dz);
	  temp.rotateUz(dir); 
	  fDisplacement += temp;
	}
      }
      // change direction
      temp.set(vx1,vy1,cost);
      temp.rotateUz(dir);
      dir = temp;
    }
  } while (0 < nMscSteps);
    
  dir.rotateUz(oldDirection);

  //FIXME
  if(debugPrint){
    G4cout<<" WentzelMS cth, th, phi old.angle(new)" << cost << " " << acos(cost) << " " << phi << " " <<oldDirection.angle(dir) << G4endl;
    G4cout<<" WentzelMS old dir: R th phi "<<oldDirection.getR()<<" "<<oldDirection.getTheta()<<" "<<oldDirection.getPhi()<<G4endl;
    G4cout<<" WentzelMS new dir: R th phi "<<dir.getR()<<" "<<dir.getTheta()<<" "<<dir.getPhi()<<G4endl;
  }
  //FIXME

  //G4cout<<"QweakSimWentzelVIModel sampling is done 1-cost= "<< 1.-dir.z()<<G4endl;
  // end of sampling -------------------------------

  fParticleChange->ProposeMomentumDirection(dir);

  // lateral displacement  
  fDisplacement.rotateUz(oldDirection);

  /*            
	 G4cout << " r(mm)= " << fDisplacement.mag() 
		<< " safety= " << safety
		<< " trueStep(mm)= " << tPathLength
		<< " geomStep(mm)= " << zPathLength
		<< " x= " << fDisplacement.x() 
		<< " y= " << fDisplacement.y() 
		<< " z= " << fDisplacement.z()
		<< G4endl;
  */

  //G4cout<< "QweakSimWentzelVIModel::SampleScattering end NewDir= " << dir<< G4endl;
  return fDisplacement;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimWentzelVIModel::ComputeXSectionPerVolume()
{
  // prepare recomputation of x-sections
  const G4ElementVector* theElementVector = currentMaterial->GetElementVector();
  const G4double* theAtomNumDensityVector = 
    currentMaterial->GetVecNbOfAtomsPerVolume();
  G4int nelm = currentMaterial->GetNumberOfElements();
  if(nelm > nelments) {
    nelments = nelm;
    xsecn.resize(nelm);
    prob.resize(nelm);
  }
  G4double cut = (*currentCuts)[currentMaterialIndex];
  if(fixedCut > 0.0) { cut = fixedCut; }
  //  cosTetMaxNuc = wokvi->GetCosThetaNuc();

  // check consistency
  xtsec = 0.0;
  if(cosTetMaxNuc > cosThetaMin) { return 0.0; }

  // loop over elements
  G4double xs = 0.0;
  for (G4int i=0; i<nelm; ++i) {
    G4double costm = 
      wokvi->SetupTarget(G4lrint((*theElementVector)[i]->GetZ()), cut);
    G4double density = theAtomNumDensityVector[i];

    G4double esec = 0.0;
    if(costm < cosThetaMin) {  

      // recompute the transport x-section
      if(1.0 > cosThetaMin) {
	xs += density*wokvi->ComputeTransportCrossSectionPerAtom(cosThetaMin);
      }
      // recompute the total x-section
      G4double nucsec = wokvi->ComputeNuclearCrossSection(cosThetaMin, costm);
      esec = wokvi->ComputeElectronCrossSection(cosThetaMin, costm);
      nucsec += esec;
      if(nucsec > 0.0) { esec /= nucsec; }
      xtsec += nucsec*density;
    }
    xsecn[i] = xtsec;
    prob[i]  = esec;
    //G4cout << i << "  xs= " << xs << " xtsec= " << xtsec 
    //       << " 1-cosThetaMin= " << 1-cosThetaMin 
    //	   << " 1-cosTetMaxNuc2= " <<1-cosTetMaxNuc2<< G4endl;
  }
  
  //G4cout << "ComputeXS result:  xsec(1/mm)= " << xs 
  //	 << " txsec(1/mm)= " << xtsec <<G4endl; 
  return xs;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
