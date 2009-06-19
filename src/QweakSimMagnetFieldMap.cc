//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMagnetFieldMap.hh"
#include "TMath.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagnetFieldMap::QweakSimMagnetFieldMap() 
  :invertX(false),invertY(false),invertZ(false)
{    
   G4cout << G4endl << "###### Calling QweakSimMagnetFieldMap::QweakSimMagnetFieldMap " << G4endl << G4endl;

   // needed later for field rotation
   BField_ANSYS = new G4ThreeVector();

   // initialize field map parameters
   // here: from the QTOR field map file

   rMinFromMap =     2.0;
   rMaxFromMap =   300.0;

   // new field map boundaries
   phiMinFromMap =    0.0;
   phiMaxFromMap =  359.0;
   
   zMinFromMap = -250.0;
   zMaxFromMap =  250.0;
   
   gridstepsize_r   = 2.0;
   gridstepsize_phi = 1.0;
   gridstepsize_z   = 2.0;

   Unit_Length = mm;
   Unit_Angle  = degree;
   // Unit_Bfield = kilogauss; // units of old field map 
   Unit_Bfield = kilogauss;    // units of new field map ???? yes, tested it (1kG = 0.1T)
                               // used field unit tesla withs results in a too strong field

   printf("zMinFromMap = %f\n",zMinFromMap);
   printf("zMinFromMap = %f\n",zMaxFromMap);
   printf("rMinFromMap = %f\n",rMinFromMap);
   printf("rMinFromMap = %f\n",rMaxFromMap);
   printf("phiMinFromMap = %f\n",phiMinFromMap);
   printf("phiMinFromMap = %f\n",phiMaxFromMap);
   printf("degree = %f\n",degree);
   printf("mm = %f\n",mm);
   printf("cm = %f\n",cm);
   printf("nm = %f\n",nm);
   printf("m = %f\n",m);
   printf("km = %f\n",km);

   // initialize variables
   //Initialize();

   // reading the field map
   //ReadFieldMap();

  G4cout << G4endl << "###### Leaving QweakSimMagnetFieldMap::QweakSimMagnetFieldMap " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagnetFieldMap::InitializeGrid()
{
  G4cout << G4endl << "###### Calling QweakSimMagnetFieldMap::Initialize " << G4endl << G4endl;
  
  nGridPointsInR   =  G4int ( (rMaxFromMap   - rMinFromMap)   /gridstepsize_r   ) + 1;
  nGridPointsInZ   =  G4int ( (zMaxFromMap   - zMinFromMap)   /gridstepsize_z   ) + 1;
  nGridPointsInPhi =  G4int ( (phiMaxFromMap - phiMinFromMap) /gridstepsize_phi ) + 1;

  BFieldGridData_X.clear();
  BFieldGridData_Y.clear();
  BFieldGridData_Z.clear();
  
  BFieldGridData_X.resize((G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi));
  BFieldGridData_Y.resize((G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi));
  BFieldGridData_Z.resize((G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi));

  for (int i = 0; i < (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi); i++) {

    BFieldGridData_X[i] = 0.0;
    BFieldGridData_Y[i] = 0.0;
    BFieldGridData_Z[i] = 0.0;
  } 
  
    
  G4cout << G4endl << "###### Leaving QweakSimMagnetFieldMap::Initialize " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagnetFieldMap::ReadFieldMap(const char* filename)
{
  G4cout << G4endl << "###### Calling QweakSimMagnetFieldMap::ReadFieldMap " << G4endl << G4endl;

  G4cout << "--------------------------------------------------------------------------------" << G4endl;
  G4cout << " Magnetic field interpolation: Reading the field grid from " << filename          << G4endl; 
  G4cout << "--------------------------------------------------------------------------------" << G4endl;


  G4int r_index = 0;
  G4int phi_index = 0;
  G4int z_index = 0;
  G4int oct = 0;
  G4int ind = 0;

  G4int raw_R_cm = 0, raw_Z_cm = 0, raw_Phi_deg = 0;
  G4double val_R = 0, val_Z = 0, val_Phi = 0, bx = 0, by = 0, bz = 0;

  G4int nlines = 0;

  // open the field map file
  std::ifstream inputfile;
  inputfile.open(filename); // Open the file for reading.

  while(inputfile.good()){

    inputfile >> raw_R_cm >> raw_Z_cm >> raw_Phi_deg >> bx >> by >> bz;

    ind = (G4int)((raw_Phi_deg - phiMinFromMap)/gridstepsize_phi 
		  + nGridPointsInPhi*(raw_R_cm - rMinFromMap)/gridstepsize_r
		  + nGridPointsInPhi*nGridPointsInR*(raw_Z_cm - zMinFromMap)/gridstepsize_z);

    BFieldGridData_X[ind] = bx*Unit_Bfield;
    BFieldGridData_Y[ind] = by*Unit_Bfield;
    BFieldGridData_Z[ind] = bz*Unit_Bfield;
  };

  // close file
  inputfile.close();

//   fclose(fp);

  G4cout << "... done reading" << nlines << "lines" << G4endl;
  
  
  G4cout << G4endl << "###### Leaving QweakSimMagnetFieldMap::ReadFieldMap " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimMagnetFieldMap::~QweakSimMagnetFieldMap()
{
  delete BField_ANSYS ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagnetFieldMap::GetFieldValueFromGridCell( const G4int GridPoint_R,
							const G4int GridPoint_Phi, 
							const G4int GridPoint_Z, 
							G4double *BFieldGridValue ) const
{
  // get the value of the cell ix, iy,iz
//   BFieldGridValue[0] = BFieldGridData_X[GridPoint_R][GridPoint_Phi][GridPoint_Z]  ;
//   BFieldGridValue[1] = BFieldGridData_Y[GridPoint_R][GridPoint_Phi][GridPoint_Z]  ;
//   BFieldGridValue[2] = BFieldGridData_Z[GridPoint_R][GridPoint_Phi][GridPoint_Z]  ;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagnetFieldMap::GetFieldValue(const G4double Point[4], G4double *Bfield ) const
{
  G4double lpoint[3] = {Point[0]/cm,Point[1]/cm,Point[2]/cm};

  if(lpoint[2] < zMinFromMap || lpoint[2] > zMaxFromMap){
    Bfield[0] = 0.0;
    Bfield[1] = 0.0;
    Bfield[2] = 0.0;
    return;
  }

  G4double xyRadius;
  G4double phi;
  G4double z;

  xyRadius = sqrt(lpoint[0]*lpoint[0] + lpoint[1]*lpoint[1]);
  if(xyRadius < rMinFromMap || xyRadius > rMaxFromMap){
    Bfield[0] = 0.0;
    Bfield[1] = 0.0;
    Bfield[2] = 0.0;
    return;
  }

//   printf("zMinFromMap = %f\n",zMinFromMap);
//   printf("zMinFromMap = %f\n",zMaxFromMap);
//   printf("xs = %f, ys = %f, zs = %f\n",lpoint[0],lpoint[1],lpoint[2]);

  z = lpoint[2];
  G4double trPhy = TMath::Pi()/8.0;

  G4double fpoint[3]={lpoint[0]*TMath::Sin(trPhy)+lpoint[1]*TMath::Cos(trPhy),
                     -lpoint[0]*TMath::Cos(trPhy)+lpoint[1]*TMath::Sin(trPhy),
                      lpoint[2]};

//   printf("xf = %f, yf = %f, zf = %f\n",fpoint[0],fpoint[1],fpoint[2]);
  
  if(fpoint[0] == 0 && fpoint[1] > 0) phi =  90.0;//*degree;
  if(fpoint[0] < 0 && fpoint[1] == 0) phi = 180.0;//*degree;
  if(fpoint[0] == 0 && fpoint[1] < 0) phi = 270.0;//*degree;
  if(fpoint[0] > 0 && fpoint[1] == 0) phi = 360.0;//*degree;

  if(fpoint[0] > 0 && fpoint[1] > 0) phi = TMath::ATan(fpoint[1]/fpoint[0])*TMath::RadToDeg();//*degree;
  if(fpoint[0] < 0 && fpoint[1] > 0) phi = (TMath::Pi()+TMath::ATan(fpoint[1]/fpoint[0]))*TMath::RadToDeg();//*degree;
  if(fpoint[0] < 0 && fpoint[1] < 0) phi = (TMath::Pi()+TMath::ATan(fpoint[1]/fpoint[0]))*TMath::RadToDeg();//*degree;
  if(fpoint[0] > 0 && fpoint[1] < 0) phi = (2.0*TMath::Pi()+TMath::ATan(fpoint[1]/fpoint[0]))*TMath::RadToDeg();//*degree;
 
//   printf("phi = %f\n",phi);

  G4double r_int, phi_int, z_int;
  G4double r_frac,phi_frac,z_frac;

  r_frac = modf(xyRadius,&r_int);
  phi_frac = modf(phi,&phi_int);
  z_frac = modf(z,&z_int);

//   printf("r_frac %f, phi_frac %f, z_frac %f\n",r_frac,phi_frac,z_frac);
//   printf("r_int %f, phi_int %f, z_int %f\n",r_int,phi_int,z_int);
 
  G4double r_rem   = static_cast<G4int>(r_int)%static_cast<G4int>(gridstepsize_r)+r_frac;
  G4double phi_rem = static_cast<G4int>(phi_int)%static_cast<G4int>(gridstepsize_phi)+phi_frac;
  G4double z_rem   = static_cast<G4int>(z)%static_cast<G4int>(gridstepsize_z)+z_frac;

//   printf("r_rem %f, phi_rem %f, z_rem %f\n",r_rem,phi_rem,z_rem);

  G4double r_local   = (r_rem)/gridstepsize_r;
  G4double phi_local = (phi_rem)/gridstepsize_phi;
  G4double z_local   = (z_rem)/gridstepsize_z;

//   printf("r_rem %f, phi_rem %f, z_rem %f\n",r_rem,phi_rem,z_rem);

  G4int ind1 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi 
		       + nGridPointsInPhi*(xyRadius - r_rem - rMinFromMap)/gridstepsize_r
		       + nGridPointsInPhi*nGridPointsInR*(z - z_rem - zMinFromMap)/gridstepsize_z);

//   printf("ind 1 = %d, r = %f, z = %f, phi = %f\n",ind1, xyRadius - r_rem, z - z_rem, phi - phi_rem);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind1],BFieldGridData_Y[ind1],BFieldGridData_Z[ind1]);

  G4int ind2 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi 
		       + nGridPointsInPhi*(xyRadius - r_rem - rMinFromMap)/gridstepsize_r
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z+1));
  
//   printf("ind 2 = %d, r = %f, z = %f, phi = %f\n",ind2, xyRadius - r_rem, z - z_rem + gridstepsize_z, phi - phi_rem);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind2],BFieldGridData_Y[ind2],BFieldGridData_Z[ind2]);

  G4int ind3 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi + 1 
		       + nGridPointsInPhi*(xyRadius - r_rem - rMinFromMap)/gridstepsize_r
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z));

//   printf("ind 3 = %d, r = %f, z = %f, phi = %f\n",ind3, xyRadius - r_rem, z - z_rem, phi - phi_rem + gridstepsize_phi);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind3],BFieldGridData_Y[ind3],BFieldGridData_Z[ind3]);

  G4int ind4 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi + 1
		       + nGridPointsInPhi*(xyRadius - r_rem - rMinFromMap)/gridstepsize_r
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z + 1));

//   printf("ind 4 = %d, r = %f, z = %f, phi = %f\n",ind4, xyRadius - r_rem, z - z_rem + gridstepsize_z, phi - phi_rem + gridstepsize_phi);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind4],BFieldGridData_Y[ind4],BFieldGridData_Z[ind4]);

  G4int ind5 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi 
		       + nGridPointsInPhi*((xyRadius - r_rem - rMinFromMap)/gridstepsize_r + 1)
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z));

//   printf("ind 5 = %d, r = %f, z = %f, phi = %f\n",ind5, xyRadius - r_rem + gridstepsize_r, z - z_rem, phi - phi_rem);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind5],BFieldGridData_Y[ind5],BFieldGridData_Z[ind5]);

  G4int ind6 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi 
		       + nGridPointsInPhi*((xyRadius - r_rem - rMinFromMap)/gridstepsize_r + 1)
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z + 1));

//   printf("ind 6 = %d, r = %f, z = %f, phi = %f\n",ind6, xyRadius - r_rem + gridstepsize_r, z - z_rem + gridstepsize_z, phi - phi_rem);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind6],BFieldGridData_Y[ind6],BFieldGridData_Z[ind6]);

  G4int ind7 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi + 1 
		       + nGridPointsInPhi*((xyRadius - r_rem - rMinFromMap)/gridstepsize_r + 1)
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z));

//   printf("ind 7 = %d, r = %f, z = %f, phi = %f\n",ind7, xyRadius - r_rem + gridstepsize_r, z - z_rem, phi - phi_rem + gridstepsize_phi);
//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind7],BFieldGridData_Y[ind7],BFieldGridData_Z[ind7]);

  G4int ind8 = (G4int)((phi - phi_rem - phiMinFromMap)/gridstepsize_phi + 1 
		       + nGridPointsInPhi*((xyRadius - r_rem - rMinFromMap)/gridstepsize_r + 1)
		       + nGridPointsInPhi*nGridPointsInR*((z - z_rem - zMinFromMap)/gridstepsize_z + 1));

  if(ind1 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind2 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind3 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind4 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind5 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind6 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind7 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi) ||
     ind8 >= (G4int)(nGridPointsInR*nGridPointsInZ*nGridPointsInPhi)){

    Bfield[0] = 0.0;
    Bfield[1] = 0.0;
    Bfield[2] = 0.0;
    return;
  }

  G4double Bx_ANSYS, By_ANSYS, Bz_ANSYS;

//   Full 3-dimensional version: trilinear interpolation
  Bx_ANSYS =
    BFieldGridData_X[ind1] * (1-r_local) * (1-phi_local) * (1-z_local) +
    BFieldGridData_X[ind2] * (1-r_local) * (1-phi_local) *    z_local  +
    BFieldGridData_X[ind3] * (1-r_local) *    phi_local  * (1-z_local) +
    BFieldGridData_X[ind4] * (1-r_local) *    phi_local  *    z_local  +
    BFieldGridData_X[ind5] *    r_local  * (1-phi_local) * (1-z_local) +
    BFieldGridData_X[ind6] *    r_local  * (1-phi_local) *    z_local  +
    BFieldGridData_X[ind7] *    r_local  *    phi_local  * (1-z_local) +
    BFieldGridData_X[ind8] *    r_local  *    phi_local  *    z_local ;
	
	
  By_ANSYS =
    BFieldGridData_Y[ind1] * (1-r_local) * (1-phi_local) * (1-z_local) +
    BFieldGridData_Y[ind2] * (1-r_local) * (1-phi_local) *    z_local  +
    BFieldGridData_Y[ind3] * (1-r_local) *    phi_local  * (1-z_local) +
    BFieldGridData_Y[ind4] * (1-r_local) *    phi_local  *    z_local  +
    BFieldGridData_Y[ind5] *    r_local  * (1-phi_local) * (1-z_local) +
    BFieldGridData_Y[ind6] *    r_local  * (1-phi_local) *    z_local  +
    BFieldGridData_Y[ind7] *    r_local  *    phi_local  * (1-z_local) +
    BFieldGridData_Y[ind8] *    r_local  *    phi_local  *    z_local ;
  

  Bz_ANSYS =
    BFieldGridData_Z[ind1] * (1-r_local) * (1-phi_local) * (1-z_local) +
    BFieldGridData_Z[ind2] * (1-r_local) * (1-phi_local) *    z_local  +
    BFieldGridData_Z[ind3] * (1-r_local) *    phi_local  * (1-z_local) +
    BFieldGridData_Z[ind4] * (1-r_local) *    phi_local  *    z_local  +
    BFieldGridData_Z[ind5] *    r_local  * (1-phi_local) * (1-z_local) +
    BFieldGridData_Z[ind6] *    r_local  * (1-phi_local) *    z_local  +
    BFieldGridData_Z[ind7] *    r_local  *    phi_local  * (1-z_local) +
    BFieldGridData_Z[ind8] *    r_local  *    phi_local  *    z_local ;
  
  Bfield[0] = Bx_ANSYS*TMath::Sin(trPhy)-By_ANSYS*TMath::Cos(trPhy);
  Bfield[1] = Bx_ANSYS*TMath::Cos(trPhy)+By_ANSYS*TMath::Sin(trPhy);
  Bfield[2] = Bz_ANSYS;

//   printf("Bx %f, By %f, Bz %f\n",BFieldGridData_X[ind1],BFieldGridData_Y[ind1],BFieldGridData_Z[ind1]);
//   printf("Bix %f, Biy %f, Biz %f\n",Bx_ANSYS,By_ANSYS,Bz_ANSYS);
//   printf("Btx %f, Bty %f, Btz %f\n",Bfield[0],Bfield[1],Bfield[2]);
  
} //end of QweakSimMagnetFieldMap::GetFieldValue()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
