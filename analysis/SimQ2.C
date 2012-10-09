/*********************************************************** 
Programmer: Valerie Gray
Purpose: To Output the Q2 values for simulated data for all the octants
and each octant individually

Entry Conditions: x and y position , x and y angle direction
Date: 04-11-2012
Modified:08-23-2012
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"

#include "TH1D.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void SimQ2 (double posx, double posy, int anglex, int angley)
{
  // groups root files for a run together
  TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

  //add the root files to the chain the event_tree branches
  QweakSimG4_Tree->Add(Form("~/QWGEANT4/rootfiles/PositionX_%gmm_PositionY_%gmm_DirectionX_%durad_DirectionY_%durad_1.root",posx,posy, anglex, angley));

  //define vector of histograms
  std::vector<TH1D*> q2;
  q2.resize(9);

  for (size_t i = 0; i<q2.size();i++)
  {
     //set the histogram for the q2 
     q2[i]= new TH1D (Form("q2[%d]",i),Form("Sim Q2 for Octant number %d",i),100,0.0,0.12);
  }

//set the histogram for the q2
//q2 = new TH1D ("q2","Q2 value",100,0.0,0.12);

  //define canvas
  TCanvas* c1 = new TCanvas ("c1","Sim Q2");
  c1->Divide(3,3);

  //draw the q2 graph for all octants
  c1->cd(9);
  QweakSimG4_Tree->Draw("Primary.PrimaryQ2>>q2[0]","Primary.CrossSection * Cerenkov.PMT.PMTTotalNbOfPEs");

  //draw the q2 graph for each octants
  for (size_t oct = 1; oct < q2.size(); oct ++)
  {
    c1->cd(oct);
    QweakSimG4_Tree->Draw(Form("Primary.PrimaryQ2>>q2[%d]",oct),Form("Primary.CrossSection* Cerenkov.PMT.PMTTotalNbOfPEs* (Cerenkov.Detector.DetectorID==%d)/Cerenkov.Detector.NbOfHits",oct));
  }

  //output the values for q2 for all octants together and indidually
  cout << "All Octants" <<endl;
  cout << "q2: " <<  setprecision(5) << 1000*q2[0]->GetMean() << " error RMS/sqrt(N): " <<  setprecision(4) << 1000*q2[0]->GetRMS()/sqrt(q2[0]->GetEntries()) << endl;

  for (int oct = 1; oct < 9; oct ++)
  {
    cout << "Octant number " << oct <<endl;
    cout << "q2: " <<  std::setprecision(5) << 1000*q2[oct]->GetMean() << " error RMS/sqrt(N): " <<  std::setprecision(4) << 1000*q2[oct]->GetRMS()/sqrt(q2[oct]->GetEntries()) << endl;
  }

  return;

}
