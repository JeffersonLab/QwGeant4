
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimInputRootFile_EventReader.cc
   $Revision: 1.1 $	
   $Date: 2006/01/31 20:22:58 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/31 20:22:58 $
//  CVS/RCS Revision: $Revision: 1.1 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimInputRootFile_EventReader.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimInputRootFile_EventReader::QweakSimInputRootFile_EventReader(TString FileName)
{

  //==================
  // start initilizing
  //==================

  SetDebugLevel(20);
  
  // initialize the pointers pointing to NULL
  Initialize();
  LoadInputRootFile(FileName);

   // initilize Root tree
  InitInputTree();

   // read entries
   //LoopEvents(0, 200000);

} //end of track::track

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimInputRootFile_EventReader::~QweakSimInputRootFile_EventReader()
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
void QweakSimInputRootFile_EventReader::SetDebugLevel(Int_t debuglevel)
{
  debug = debuglevel;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Int_t QweakSimInputRootFile_EventReader::Initialize() {

  if (debug!=0) cout << "==> Initilize() called" << endl; 

  // make sure that pointers not yet used really point to NULL
  // otherwise dealing with dangling pointers can be &*!@# (censored) ... 
  fInputRootFile = NULL;
  InputTree      = NULL; 
  branch         = NULL;

  event = NULL;
  //theCurrentEvent = new QweakSimInputRootTree_CurrentEvent();
  event = new EPEvent();

  myrand = new TRandom(); 
  myrand->SetSeed();

  NumberOfEntries = 0;

  RotatedVertex   = new G4ThreeVector();
  RotatedMomentum = new G4ThreeVector();

  eventcounter = 0;

  cout << "==> initilizing pointers done" << endl;  

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Int_t QweakSimInputRootFile_EventReader::LoadInputRootFile(TString FileName)
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

void QweakSimInputRootFile_EventReader::InitInputTree()
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

  branch = InputTree->GetBranch("CurrentEvent");  //getting the address of the EventBranch so we can access it through a pointer

  branch->SetAddress(&event);  //setting the address to which objects from that branch will be loaded 

} // end of QweakSimInputRootFile_EventReader::Init() 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimInputRootFile_EventReader::check_events_to_be_read(Int_t &lastevent,Int_t &firstevent, TBranch *branch)
{
  if (debug!=0) cout << "==> check_events_to_be_read() called" << endl; 

  Int_t nentries = Int_t(branch->GetEntries());  
  
  if(firstevent<0)
    firstevent=0;

  if(lastevent>nentries)
  {
      lastevent=nentries; 
      cerr<<"##> The number of events you want to display is larger" << endl;
      cerr<<"##> than the number of entries in the ntuple branch ! " << endl;
      cerr<<"##> This values has been set to the maximum available " << endl;
      cerr<<"##> entries  = "<< lastevent << endl;
  }
  
}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimInputRootFile_EventReader::LoopEvents(Int_t firstevent, Int_t lastevent)
{  
  if (debug!=0) cout << "==> ReadNodes() called" << endl; 

  NumberOfEntries = (Int_t) branch->GetEntries();

  cout << "==> total number of Primary Nodes in the Geant ntuple: " 
       << NumberOfEntries << endl;


  // check for proper lastevent
  check_events_to_be_read(lastevent, firstevent, branch);

  // recalulate to number of events to be analysed

  NumberOfEntries = lastevent-firstevent+1;


  cout << "==> choosen number of TrackNodes in the Geant ntuple: " 
       << NumberOfEntries << endl;

  // loop over all entries, fill Track structures 
  for(Int_t jentry = firstevent; jentry<lastevent; jentry++) {

    cout << "jentry: " << jentry << endl;

    Int_t entryNumber = branch->GetEntryNumber(); 
    
    if (debug>10) {cout << "entryNumber: " << entryNumber << endl;}
    
    if(entryNumber<0) break;
    
    // load the activated branches
    //InputTree->LoadTree(entryNumber);
    if (debug>10) {cout << "alive after LoadTree" << endl;}
    
    // get the current event()
    branch->GetEntry(entryNumber);
    
    if (debug>10) {cout << "alive after GetEntry" << endl;}
    
    FillLeavesFromCurrentEvent(event);

    eventcounter++;

    //--------------------
    if(debug>10){
	if(eventcounter < 10) { PrintLeavesFromCurrentEvent();} 
    } // end if(debug>10)
    //--------------------


  } // end for(Int_t jentry=firstevent; jentry<lastevent; jentry++)
} //end QweakSimInputRootFile_EventReader::LoopEvents

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void QweakSimInputRootFile_EventReader::GetRandomEvent(Double_t *primaryEvent)
void QweakSimInputRootFile_EventReader::GetRandomEvent(QweakSimG3Ntuple *primaryEvent)
{  
  if (debug!=0) cout << "==> calling QweakSimInputRootFile_EventReader::GetRandomEvent() " << endl; 

//   myrand->SetSeed(0);
//   Double_t mynumber = numberOfEntries * myrand->Rndm(nrandom);
  
  NumberOfEntries = (Int_t) branch->GetEntries();
  
  //cout << "==> total number of Primary Nodes in the Geant ntuple: " << NumberOfEntries << endl;

   Int_t myRandomNumber = (Int_t) (G4UniformRand()*NumberOfEntries);

   Int_t jentry = myRandomNumber;

   // cout << "Int_t    jentry   = " << jentry   << endl;

    Int_t entryNumber = branch->GetEntryNumber();
    
    if (debug>10) {cout << "entryNumber: " << entryNumber << endl;}
    
    // load the activated branches
    //InputTree->LoadTree(entryNumber);
    if (debug>10) {cout << "alive after LoadTree" << endl;}
    
    // get the current event()
    branch->GetEntry(entryNumber);

    FillLeavesFromCurrentEvent(event);

    eventcounter++;

    //--------------------
    if(debug>10){
	if( eventcounter <10) { PrintLeavesFromCurrentEvent();} 
    } // end if(debug>10)
    //--------------------
    

     // Neven's Ntuple contains only particle
     // for octant 3 (3:00 position looking upstream)
     // My wire chambers are positioned at octant 1 ...
     // Let's rotate vertex and momentum of Neven's Ntuple
     // 90 deg fron octant 3 to octant 1
 
    //---------------------------------
    RotatedVertex->setX(my_gt_vertx_o);
    RotatedVertex->setY(my_gt_verty_o);
    RotatedVertex->setZ(my_gt_vertz_o);

    RotatedVertex->rotateZ(90*degree);
    
    primaryEvent->Vertex[0] = RotatedVertex->x();
    primaryEvent->Vertex[1] = RotatedVertex->y();
    primaryEvent->Vertex[2] = RotatedVertex->z();
    
    //---------------------------------

    RotatedMomentum->setX(my_gt_px_o);
    RotatedMomentum->setY(my_gt_py_o);
    RotatedMomentum->setZ(my_gt_pz_o);

    RotatedMomentum->rotateZ(90*degree);
    
    primaryEvent->Momentum[0] = RotatedMomentum->x();
    primaryEvent->Momentum[1] = RotatedMomentum->y();
    primaryEvent->Momentum[2] = RotatedMomentum->z();
    //---------------------------------

    primaryEvent->Phi           = my_gt_phi_o;
    primaryEvent->Theta         = my_gt_theta_o;
        
    primaryEvent->KineticEnergy = my_gt_ptot_o;
    primaryEvent->TotalEnergy   = my_gt_en_o;
    primaryEvent->ParticleID    = my_gt_ipart_det;

    primaryEvent->Q2            = my_gt_q__2 ;
    primaryEvent->Weight        = my_gt_weight_n;

} //end QweakSimInputRootFile_EventReader::GetRandomEvent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimInputRootFile_EventReader::GetPrimaryEvent(int myNumber, QweakSimG3Ntuple *primaryEvent)
{  
//   if (debug!=0) cout << "==> calling QweakSimInputRootFile_EventReader::GetPrimaryEvent() " << endl; 

    NumberOfEntries = (Int_t) branch->GetEntries(); 
 
    // cout << "==> total number of Primary Nodes in the Geant ntuple: " << NumberOfEntries << endl;
    
    if (myNumber>NumberOfEntries) 
    { 
	cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Error: myNumber>NumberOfEntries " << endl;
	myNumber = 0;
    }

  if (debug>10) {cout << "alive after LoadTree" << endl;}
    
  // get the current event()
  branch->GetEntry(myNumber);

  eventcounter++;

  FillLeavesFromCurrentEvent(event);

  //--------------------
  if(debug>10){
      if( eventcounter < 10) { PrintLeavesFromCurrentEvent();} 
  } // end if(debug>10)
  //--------------------


  // Neven's Ntuple contains only particle
  // for octant 3 (3:00 position looking upstream)
  // My wire chambers are positioned at octant 1 ...
  // Let's rotate vertex and momentum of Neven's Ntuple
  // 90 deg fron octant 3 to octant 1

  // Michael's event: units in GeV
  // Geant3    event: energy, monentun in MeV

  primaryEvent->Phi           = my_gt_phi_o;
  primaryEvent->Theta         = my_gt_theta_o;
        
  primaryEvent->KineticEnergy = my_gt_ptot_o;
  primaryEvent->TotalEnergy   = my_gt_en_o;
  primaryEvent->ParticleID    = my_gt_ipart_det;

  primaryEvent->Q2            = my_gt_q__2;
  primaryEvent->Weight        = my_gt_weight_n;

  RotatedVertex->setX(my_gt_vertx_o);
  RotatedVertex->setY(my_gt_verty_o);
  RotatedVertex->setZ(my_gt_vertz_o);

  RotatedVertex->rotateZ(90*degree);
    
  primaryEvent->Vertex[0]   = RotatedVertex->x();
  primaryEvent->Vertex[1]   = RotatedVertex->y();
  primaryEvent->Vertex[2]   = RotatedVertex->z();
    
  //----------------------------------------------------

  RotatedMomentum->setX(my_gt_px_o);
  RotatedMomentum->setY(my_gt_py_o);
  RotatedMomentum->setZ(my_gt_pz_o);

  RotatedMomentum->rotateZ(90*degree);
    
  primaryEvent->Momentum[0]   = RotatedMomentum->x();
  primaryEvent->Momentum[1]   = RotatedMomentum->y();
  primaryEvent->Momentum[2]   = RotatedMomentum->z();


    cout << " Leaving QweakSimInputRootFile_EventReader::GetPrimaryEvent()" << endl; 

} //end QweakSimInputRootFile_EventReader::GetPrimaryEvent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimInputRootFile_EventReader::FillLeavesFromCurrentEvent(EPEvent* currentevent)
{
    // geant3 event generator: energy, momentum in MeV
    // Root event generator: energy, momentum in GeV
    // Up to now QweakSimG4 is compatible with Geant3 event energy  

    my_gt_numhits      = currentevent->Get_numhits();
    my_gt_en_o         = currentevent->Get_en_o()*1000.;   
    my_gt_ipart_det    = currentevent->Get_ipart_det();   
    my_gt_vertx_o      = currentevent->Get_vertx_o(); 
    my_gt_verty_o      = currentevent->Get_verty_o(); 
    my_gt_vertz_o      = currentevent->Get_vertz_o();   
    my_gt_px_o         = currentevent->Get_px_o()*1000.;   
    my_gt_py_o         = currentevent->Get_py_o()*1000.;   
    my_gt_pz_o         = currentevent->Get_pz_o()*1000.;   
    my_gt_theta_o      = currentevent->Get_theta_o();   
    my_gt_phi_o        = currentevent->Get_phi_o();   
    my_gt_ptot_o       = currentevent->Get_ptot_o()*1000.;   
    my_gt_q__2         = currentevent->Get_q__2(); 
    my_gt_weight_n     = currentevent->Get_weight_n();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimInputRootFile_EventReader::PrintLeavesFromCurrentEvent()
{

	  cout << "==============================================================" << endl; 
	  cout << " Event Number        : " << eventcounter       << endl; 
	  cout << " Number of hits      : " << my_gt_numhits      << endl; 
	  cout << " Paricle ID          : " << my_gt_ipart_det    << endl; 
	  cout << " vertx_o [cm]        : " << my_gt_vertx_o      << endl; 
	  cout << " verty_o [cm]        : " << my_gt_verty_o      << endl; 
	  cout << " vertz_o [cm]        : " << my_gt_vertz_o      << endl; 
	  cout << " px_o    [MeV]       : " << my_gt_px_o         << endl; 
	  cout << " py_o    [MeV]       : " << my_gt_py_o         << endl; 
	  cout << " pz_o    [MeV]       : " << my_gt_pz_o         << endl; 
	  cout << " theta_o [deg]       : " << my_gt_theta_o      << endl; 
	  cout << " phi_o   [deg]       : " << my_gt_phi_o        << endl; 
	  cout << " ptot_o  [MeV]       : " << my_gt_ptot_o       << endl; 
	  cout << " en_o    [MeV]       : " << my_gt_en_o         << endl; 
	  cout << " q__2    [GeV^2]     : " << my_gt_q__2         << endl; 
	  cout << " weight_n [ubarn/sr] : " << my_gt_weight_n     << endl; 
	  cout << "==============================================================" << endl; 
}


//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimInputRootFile_EventReader.cc,v $
//      Revision 1.1  2006/01/31 20:22:58  grimm
//      Reads the output root file of Michael's event generator.
//
//      Revision 1.2  2005/12/27 19:09:23  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 



