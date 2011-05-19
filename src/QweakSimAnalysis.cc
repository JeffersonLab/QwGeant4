//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimAnalysis.cc

   $Revision: 1.4 $	
   $Date: 2006/01/06 19:12:25 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <ctime>  //jpan@nuclear.uwinnipeg.ca for using time lib

// user includes
#include "QweakSimAnalysis.hh"
#include "QweakSimUserMainEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimAnalysis::QweakSimAnalysis()
{
    // Initialize 
    QweakSimG4_RootEvent    = NULL;
    QweakSimG4_RootNtuple   = NULL;
    QweakSimG4_RootBranch   = NULL;
    QweakSimG4_RootFile     = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimAnalysis::~QweakSimAnalysis() 
{
  Finish();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::Init()
{;}                       

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::Finish()
{
  if (QweakSimG4_RootEvent)    delete QweakSimG4_RootEvent;
  if (QweakSimG4_RootNtuple)   delete QweakSimG4_RootNtuple;
  if (QweakSimG4_RootBranch)   delete QweakSimG4_RootBranch;
  if (QweakSimG4_RootFile)     delete QweakSimG4_RootFile;
}   

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::BeginOfRun() 
{ 
  QweakSimG4_RootFile = new TFile( "QweakSim.root","RECREATE","Qweak ROOT file");

  ConstructRootNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::EndOfRun() 
{

  QweakSimG4_RootFile->Write(); // Writing the data to the ROOT file
  QweakSimG4_RootFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::EndOfEvent(G4int flag) 
{
// This member is called at the end of every event
  if(!flag) return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::ConstructRootNtuple() 
{

  // create ROOT tree

  QweakSimG4_RootNtuple = new TTree("QweakSimG4_Tree","QweakSimG4_Tree");

  // save the file after so many bytes. Avoids complete data loss after crash 
  //QweakSimG4_RootNtuple ->SetAutoSave(1000000);  //AutoSave after every 1 Mbyte written to disk 

  // Instance of data structure to be written into ROOT file
  QweakSimG4_RootEvent  = new QweakSimUserMainEvent();

  // Create a branch with the data structure defined by QweakSimG4_Event

//jpan@nuclear.uwinnipeg.ca
//  int bufsize = 64000;
//  int split   = 10; 
//  int split   = 99; 

  QweakSimG4_RootBranch = QweakSimG4_RootNtuple->Branch("QweakSimUserMainEvent", "QweakSimUserMainEvent", &QweakSimG4_RootEvent, 64000, 99);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimAnalysis::AutoSaveRootNtuple() 
{
    // save the current ntuple:
    // In case your program crashes before closing the file holding this tree,
    // the file will be automatically recovered when you will connect the file
    // in UPDATE mode.
    // The Tree will be recovered at the status corresponding to the last AutoSave.
    //
    // if option contains "SaveSelf", gDirectory->SaveSelf() is called.
    // This allows another process to analyze the Tree while the Tree is being filled.
    //
    // see http://root.cern.ch/root/html/TTree.html#TTree:AutoSave

     // QweakSimG4_RootNtuple -> AutoSave("SaveSelf");
     QweakSimG4_RootNtuple -> AutoSave();
     gDirectory -> Purge(); //jpan: Purge old trees

//jpan@nuclear.uwinnipeg.ca
//print the timestamp on screen, test code, add by Jie

//     time_t ltime;     // calendar time  
//     ltime=time(NULL); // get current cal time  
//     cout<<"=====>> Data saved at "<< asctime( localtime(&ltime) ) <<G4endl;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

