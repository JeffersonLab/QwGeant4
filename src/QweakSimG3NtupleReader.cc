
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimG3NtupleReader.cc
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:09:23 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:09:23 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimG3NtupleReader.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimG3NtupleReader::QweakSimG3NtupleReader(TString FileName)
{

  //==================
  // start initilizing
  //==================

  SetDebugLevel(11);
  
  // initialize the pointers pointing to NULL
  Initialize();
  LoadInputRootFile(FileName);

   // initilize Root tree
  InitInputTree();

   // read entries
   //LoopEvents(0, 200000);

} //end of track::track

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimG3NtupleReader::~QweakSimG3NtupleReader()
{
  if (debug!=0) cout << "==> Destructor() called" << endl;
 
   if (fInputRootFile==0) return;
   fInputRootFile->Close();
   //delete fInputRootFile;
   
   delete myrand; 
   
   delete RotatedVertex;
   delete RotatedMomentum;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimG3NtupleReader::SetDebugLevel(Int_t debuglevel)
{
  debug = debuglevel;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Int_t QweakSimG3NtupleReader::Initialize() {

  if (debug!=0) cout << "==> Initilize() called" << endl; 

  // make sure that pointers not yet used really point to NULL
  // otherwise dealing with dangling pointers can be &*!@# (censored) ... 
  fInputRootFile = NULL;
  InputTree      = NULL; 

  myrand = new TRandom(); 
  myrand->SetSeed();

  NumberOfEntries = 0;

  RotatedVertex   = new G4ThreeVector();
  RotatedMomentum = new G4ThreeVector();


  cout << "==> initilizing pointers done" << endl;  

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Int_t QweakSimG3NtupleReader::LoadInputRootFile(TString FileName)
{
  if (debug!=0) cout << "==> LoadInputRootFile() called" << endl; 

  // e.g. "QweakTrack.1.root"
  //fInputFileName = TString("ep_m0_neven_larget_r5.root");
  fInputFileName = FileName;

// check if the root file exist for opening
 //
  if ((fInputRootFile = new TFile(fInputFileName,"READ","hehehe"))==NULL) {
    cout << "==> Error in creating TFile for Inputfile" << fInputFileName << endl;
  return 1;
  }

  // According to Fons Rademakers it is not possible
  // to check that we are opening a root file ...
  // ... at least we can check that the file exist
  if (fInputRootFile->IsZombie()) {
    cout << "==> Error in opening the root file " << fInputFileName << endl;
    return(1);
  }

  if (!(fInputRootFile->IsOpen())) {
    cout << "==> Error, Input rootfile is not open" << fInputFileName << endl;
    //fInputFileNumber=-1;
    return 1;
  }
  else {
    cout << "==> Input root file is open, current file number: " << fInputFileNumber << endl;
  }

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimG3NtupleReader::InitInputTree()
{
  if (debug!=0) cout << "==> InitInputTree() called" << endl; 

  // get the tree "h20"
  // created by h2root from Geant-PAW-Ntuple
  InputTree = (TTree*) fInputRootFile->Get("h8013");

  if (InputTree == NULL) {
    std::cout << "The Tree DOES NOT EXIST" << std::endl;
  } else if (InputTree->GetEntries() < 1) {
    std::cout << "The Tree IS EMPTY" << std::endl;
  }

  // map the branches we are interested in
//   InputTree->SetBranchAddress("numhits",&my_gt_numhits);
//   InputTree->SetBranchAddress("ipart_det",&my_gt_ipart_det);

//   InputTree->SetBranchAddress("q__2", &my_gt_q__2);
//   InputTree->SetBranchAddress("weight_n", &my_gt_weight_n);

//   InputTree->SetBranchAddress("vertx_o", &my_gt_vertx_o);
//   InputTree->SetBranchAddress("verty_o", &my_gt_verty_o);
//   InputTree->SetBranchAddress("vertz_o", &my_gt_vertz_o);

//   InputTree->SetBranchAddress("px_o", &my_gt_px_o);
//   InputTree->SetBranchAddress("py_o", &my_gt_py_o);
//   InputTree->SetBranchAddress("pz_o", &my_gt_pz_o);

//   InputTree->SetBranchAddress("theta_o", &my_gt_theta_o);
//   InputTree->SetBranchAddress("phi_o", &my_gt_phi_o);

//   InputTree->SetBranchAddress("ptot_o", &my_gt_ptot_o);
//   InputTree->SetBranchAddress("en_o", &my_gt_en_o);

  InputTree->SetBranchAddress("numhits",&my_gt_numhits);
  InputTree->SetBranchAddress("ipart_det",my_gt_ipart_det);

  InputTree->SetBranchAddress("q__2", &my_gt_q__2);
  InputTree->SetBranchAddress("weight_n", &my_gt_weight_n);

  InputTree->SetBranchAddress("vertx_o", my_gt_vertx_o);
  InputTree->SetBranchAddress("verty_o", my_gt_verty_o);
  InputTree->SetBranchAddress("vertz_o", my_gt_vertz_o);

  InputTree->SetBranchAddress("px_o", my_gt_px_o);
  InputTree->SetBranchAddress("py_o", my_gt_py_o);
  InputTree->SetBranchAddress("pz_o", my_gt_pz_o);

  InputTree->SetBranchAddress("theta_o",my_gt_theta_o);
  InputTree->SetBranchAddress("phi_o", my_gt_phi_o);

  InputTree->SetBranchAddress("ptot_o", my_gt_ptot_o);
  InputTree->SetBranchAddress("en_o", my_gt_en_o);



  // switch off all branches to gain speed in the analysis
  InputTree->SetBranchStatus("*",0);
   
  // only activate the needed branches
  //InputTree->SetBranchStatus("Neven_Ntuple",1);
  InputTree->SetBranchStatus("numhits",1);
  InputTree->SetBranchStatus("ipart_det",1);

  InputTree->SetBranchStatus("q__2",1);
  InputTree->SetBranchStatus("weight_n",1);

  InputTree->SetBranchStatus("vertx_o",1);
  InputTree->SetBranchStatus("verty_o",1);
  InputTree->SetBranchStatus("vertz_o",1);

  InputTree->SetBranchStatus("px_o",1);
  InputTree->SetBranchStatus("py_o",1);
  InputTree->SetBranchStatus("pz_o",1);

  InputTree->SetBranchStatus("theta_o",1);
  InputTree->SetBranchStatus("phi_o",1);

  InputTree->SetBranchStatus("ptot_o",1);
  InputTree->SetBranchStatus("en_o",1);


     
} // end of QweakSimG3NtupleReader::Init() 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimG3NtupleReader::check_events_to_be_read(Int_t &lastevent,Int_t &firstevent, TTree *tree)
{
  if (debug!=0) cout << "==> check_events_to_be_read() called" << endl; 

  Int_t nentries = Int_t(tree->GetEntries());  

  if(firstevent<0)
    firstevent=0;

  if(lastevent>nentries)
    {
      lastevent=nentries; 
      cerr<<"##> The number of events you want to display is larger" << endl;
      cerr<<"##> than the number of entries in the ntuple !"         << endl;
      cerr<<"##> This values has been set to the maximum available"  << endl;
      cerr<<"##> entries  = "<< lastevent << endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimG3NtupleReader::LoopEvents(Int_t firstevent, Int_t lastevent)
{  
  if (debug!=0) cout << "==> ReadNodes() called" << endl; 

  NumberOfEntries = (Int_t) InputTree->GetEntries();
  cout << "==> total number of Primary Nodes in the Geant ntuple: " 
       << NumberOfEntries << endl;


  // check for proper lastevent
  check_events_to_be_read(lastevent, firstevent, InputTree);

  // recalulate to number of events to be analysed
  NumberOfEntries = lastevent-firstevent+1;
  cout << "==> choosen number of TrackNodes in the Geant ntuple: " 
       << NumberOfEntries << endl;

  // loop over all entries, fill Track structures 
  for(Int_t jentry=firstevent; jentry<lastevent; jentry++) {

    cout << "jentry: " << jentry << endl;

    Int_t entryNumber = InputTree->GetEntryNumber(jentry);
    
    if (debug>10) {cout << "entryNumber: " << entryNumber << endl;}
    
    if(entryNumber<0) break;

    // load the activated branches
    InputTree->LoadTree(entryNumber);
    if (debug>10) {cout << "alive after LoadTree" << endl;}
    
    // get the current event()
    InputTree->GetEntry(entryNumber);
    if (debug>10) {cout << "alive after GetEntry" << endl;}

//-----------------------------------------------------------------------------
    if(debug>10){
      if(jentry<10) {
    cout << "==============================================================" << endl; 
    cout << " Event Number     : " << jentry             << endl; 
    cout << " Number of hits   : " << my_gt_numhits      << endl; 
    cout << " Paricle ID       : " << my_gt_ipart_det[0] << endl; 
    cout << " vertx_o [cm]     : " << my_gt_vertx_o[0]   << endl; 
    cout << " verty_o [cm]     : " << my_gt_verty_o[0]   << endl; 
    cout << " vertz_o [cm]     : " << my_gt_vertz_o[0]   << endl; 
    cout << " px_o    [MeV]    : " << my_gt_px_o[0]      << endl; 
    cout << " py_o    [MeV]    : " << my_gt_py_o[0]      << endl; 
    cout << " pz_o    [MeV]    : " << my_gt_pz_o[0]      << endl; 
    cout << " theta_o [deg]    : " << my_gt_theta_o[0]   << endl; 
    cout << " phi_o   [deg]    : " << my_gt_phi_o[0]     << endl; 
    cout << " ptot_o  [MeV]    : " << my_gt_ptot_o[0]    << endl; 
    cout << " en_o    [MeV]    : " << my_gt_en_o[0]      << endl; 
    cout << " q__2    [GeV^2]  : " << my_gt_q__2         << endl; 
    cout << " weight_n         : " << my_gt_weight_n     << endl; 
    cout << "==============================================================" << endl; 
      }
    }
    
  } // end for(Int_t jentry=firstevent; jentry<lastevent; jentry++)
  
} //end QweakSimG3NtupleReader::LoopEvents
    

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void QweakSimG3NtupleReader::GetRandomEvent(Double_t *primaryEvent)
void QweakSimG3NtupleReader::GetRandomEvent(QweakSimG3Ntuple *primaryEvent)
{  
  if (debug!=0) cout << "==> calling QweakSimG3NtupleReader::GetRandomEvent() " << endl; 

//   myrand->SetSeed(0);
//   Double_t mynumber = numberOfEntries * myrand->Rndm(nrandom);

  NumberOfEntries = (Int_t) InputTree->GetEntries();
  cout << "==> total number of Primary Nodes in the Geant ntuple: " 
       << NumberOfEntries << endl;



   Int_t myRandomNumber = (Int_t) (G4UniformRand()*NumberOfEntries);

  //Int_t jentry = (Int_t) mynumber;
  Int_t jentry = myRandomNumber;

  //ut << "Double_t mynumber = " << mynumber << endl;
  cout << "Int_t    jentry   = " << jentry   << endl;

    Int_t entryNumber = InputTree->GetEntryNumber(jentry);
    
    if (debug>10) {cout << "entryNumber: " << entryNumber << endl;}
    
    // load the activated branches
    InputTree->LoadTree(entryNumber);
    if (debug>10) {cout << "alive after LoadTree" << endl;}
    
    // get the current event()
    InputTree->GetEntry(entryNumber);
    //InputTree->GetEntry(jentry);
    if (debug>10) {cout << "alive after GetEntry" << endl;}


    //-----------------------------------------------------------------------------
    if(debug>10){
	cout << "=============================================" << endl; 
	cout << " >>>>> Randomly chosen Event in Ntuple <<<<<<" << endl; 
	cout << " Event Number     : " << jentry             << endl; 
	cout << " Number of hits   : " << my_gt_numhits      << endl; 
	cout << " Paricle ID       : " << my_gt_ipart_det[0] << endl; 
	cout << " vertx_o [cm]     : " << my_gt_vertx_o[0]   << endl; 
	cout << " verty_o [cm]     : " << my_gt_verty_o[0]   << endl; 
	cout << " vertz_o [cm]     : " << my_gt_vertz_o[0]   << endl; 
	cout << " px_o    [MeV]    : " << my_gt_px_o[0]      << endl; 
	cout << " py_o    [MeV]    : " << my_gt_py_o[0]      << endl; 
	cout << " pz_o    [MeV]    : " << my_gt_pz_o[0]      << endl; 
	cout << " theta_o [deg]    : " << my_gt_theta_o[0]   << endl; 
	cout << " phi_o   [deg]    : " << my_gt_phi_o[0]     << endl; 
	cout << " ptot_o  [MeV]    : " << my_gt_ptot_o[0]    << endl; 
	cout << " en_o    [MeV]    : " << my_gt_en_o[0]      << endl; 
	cout << " q__2    [GeV^2]  : " << my_gt_q__2         << endl; 
        cout << " weight_n         : " << my_gt_weight_n     << endl; 
	cout << "==============================================================" << endl; 
    }
    //-----------------------------------------------------------------------------

     // Neven's Ntuple contains only particle
     // for octant 3 (3:00 position looking upstream)
     // My wire chambers are positioned at octant 1 ...
     // Let's rotate vertex and momentum of Neven's Ntuple
     // 90 deg fron octant 3 to octant 1
 
    //---------------------------------
    RotatedVertex->setX(my_gt_vertx_o[0]);
    RotatedVertex->setY(my_gt_verty_o[0]);
    RotatedVertex->setZ(my_gt_vertz_o[0]);

    RotatedVertex->rotateZ(90*degree);
    
    primaryEvent->Vertex[0] = RotatedVertex->x();
    primaryEvent->Vertex[1] = RotatedVertex->y();
    primaryEvent->Vertex[2] = RotatedVertex->z();
    
    //---------------------------------

    RotatedMomentum->setX(my_gt_px_o[0]);
    RotatedMomentum->setY(my_gt_py_o[0]);
    RotatedMomentum->setZ(my_gt_pz_o[0]);

    RotatedMomentum->rotateZ(90*degree);
    
    primaryEvent->Momentum[0] = RotatedMomentum->x();
    primaryEvent->Momentum[1] = RotatedMomentum->y();
    primaryEvent->Momentum[2] = RotatedMomentum->z();
    //---------------------------------

    primaryEvent->Phi           = my_gt_phi_o[0];
    primaryEvent->Theta         = my_gt_theta_o[0];
        
    primaryEvent->KineticEnergy = my_gt_ptot_o[0];
    primaryEvent->TotalEnergy   = my_gt_en_o[0];
    primaryEvent->ParticleID    = my_gt_ipart_det[0];

    primaryEvent->Q2            = my_gt_q__2 ;
    primaryEvent->Weight        = my_gt_weight_n;

} //end QweakSimG3NtupleReader::GetRandomEvent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void QweakSimG3NtupleReader::GetPrimaryEvent(int myNumber, QweakSimG3Ntuple *primaryEvent)
{  
//   if (debug!=0) cout << "==> calling QweakSimG3NtupleReader::GetPrimaryEvent() " << endl; 

  NumberOfEntries = (Int_t) InputTree->GetEntries();
//   cout << "==> total number of Primary Nodes in the Geant ntuple: " 
//        << NumberOfEntries << endl;

  if (myNumber>NumberOfEntries) 
    { cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Error: myNumber>NumberOfEntries " << endl;
    myNumber = 0;
    }

  Int_t jentry = myNumber;

//   cout << "Int_t    jentry   = " << jentry   << endl;

  Int_t entryNumber = InputTree->GetEntryNumber(jentry);
    
  if (debug>10) {cout << "entryNumber: " << entryNumber << endl;}
    
  // load the activated branches
  InputTree->LoadTree(entryNumber);
  if (debug>10) {cout << "alive after LoadTree" << endl;}
    
  // get the current event()
  InputTree->GetEntry(entryNumber);
  if (debug>10) {cout << "alive after GetEntry" << endl;}

  //-----------------------------------------------------------------------------
  if(debug>10){
    cout << "=============================================" << endl; 
    cout << " >>>>> Sequentially chosen Event in Ntuple <<<<<<" << endl; 
    cout << " Event Number     : " << jentry             << endl; 
    cout << " Number of hits   : " << my_gt_numhits      << endl; 
    cout << " Paricle ID       : " << my_gt_ipart_det[0] << endl; 
    cout << " vertx_o [cm]     : " << my_gt_vertx_o[0]   << endl; 
    cout << " verty_o [cm]     : " << my_gt_verty_o[0]   << endl; 
    cout << " vertz_o [cm]     : " << my_gt_vertz_o[0]   << endl; 
    cout << " px_o    [MeV]    : " << my_gt_px_o[0]      << endl; 
    cout << " py_o    [MeV]    : " << my_gt_py_o[0]      << endl; 
    cout << " pz_o    [MeV]    : " << my_gt_pz_o[0]      << endl; 
    cout << " theta_o [deg]    : " << my_gt_theta_o[0]   << endl; 
    cout << " phi_o   [deg]    : " << my_gt_phi_o[0]     << endl; 
    cout << " ptot_o  [MeV]    : " << my_gt_ptot_o[0]    << endl; 
    cout << " en_o    [MeV]    : " << my_gt_en_o[0]      << endl; 
    cout << " q__2    [GeV^2]  : " << my_gt_q__2         << endl; 
    cout << " weight_n         : " << my_gt_weight_n     << endl; 
    cout << "==============================================================" << endl; 
  }
  //-----------------------------------------------------------------------------

  // Neven's Ntuple contains only particle
  // for octant 3 (3:00 position looking upstream)
  // My wire chambers are positioned at octant 1 ...
  // Let's rotate vertex and momentum of Neven's Ntuple
  // 90 deg fron octant 3 to octant 1
 
  primaryEvent->Phi           = my_gt_phi_o[0];
  primaryEvent->Theta         = my_gt_theta_o[0];
        
  primaryEvent->KineticEnergy = my_gt_ptot_o[0];
  primaryEvent->TotalEnergy   = my_gt_en_o[0];
  primaryEvent->ParticleID    = my_gt_ipart_det[0];

  primaryEvent->Q2            = my_gt_q__2;
  primaryEvent->Weight        = my_gt_weight_n;

  RotatedVertex->setX(my_gt_vertx_o[0]);
  RotatedVertex->setY(my_gt_verty_o[0]);
  RotatedVertex->setZ(my_gt_vertz_o[0]);

  RotatedVertex->rotateZ(90*degree);
    
  primaryEvent->Vertex[0]   = RotatedVertex->x();
  primaryEvent->Vertex[1]   = RotatedVertex->y();
  primaryEvent->Vertex[2]   = RotatedVertex->z();
    
  //----------------------------------------------------

  RotatedMomentum->setX(my_gt_px_o[0]);
  RotatedMomentum->setY(my_gt_py_o[0]);
  RotatedMomentum->setZ(my_gt_pz_o[0]);

  RotatedMomentum->rotateZ(90*degree);
    
  primaryEvent->Momentum[0]   = RotatedMomentum->x();
  primaryEvent->Momentum[1]   = RotatedMomentum->y();
  primaryEvent->Momentum[2]   = RotatedMomentum->z();


    cout << " Leaving QweakSimG3NtupleReader::GetPrimaryEvent()" << endl; 

} //end QweakSimG3NtupleReader::GetPrimaryEvent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimG3NtupleReader.cc,v $
//      Revision 1.2  2005/12/27 19:09:23  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 



