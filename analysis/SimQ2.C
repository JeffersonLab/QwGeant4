/*********************************************************** 
Programmer: Valerie Gray
Purpose: To Output the Q2 values for simulated data for all the octants
and each octant individually

Entry Conditions: x and y position , x and y angle direction
Date: 04-11-2012
Modified:11-21-2012
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"

#include "TH1D.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void SimQ2 (int posx, double posy, int anglex, int angley)
{
  // groups root files for a run together
  TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

  //add the root files to the chain the event_tree branches
  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_Al_DS/*.root");

  //number of chunks
  Int_t n = 1000;

  //define vector of histograms
  std::vector < vector<TH1D*> >  q2;
  q2.resize(n+1);

  std::vector<TH1D*> q2_tot;
  q2_tot.resize(9);

  for (size_t i = 0; i<q2.size();i++)
  {
     q2[i].resize(9);
     for (size_t j = 0; j<q2[i].size();j++)
     {
       //set the histogram for the q2 
       q2[i][j]= new TH1D (Form("q2[%d][%d]",i,j),Form("Sim Q2 for Octant number %d, set %d",i,j),100,0.0,0.12);
     }
	}
  for (size_t j = 0; j<q2_tot.size();j++)
  {
     q2_tot[j] = new TH1D (Form("q2_tot[%d]",j),Form("Sim Q2 for Octant number %d",j),100,0.0,0.12);
 	}

  // define a vector for the mean and sigma of all the histograms
  //this will allow to get the proper mean - initalze all values to zero.
  //std::vector <Double_t> mean_q2(9, 0.0);
  //std::vector <Double_t> sigma_q2(9, 0.0);

  Double_t mean_q2[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t sigma_q2[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//set the histogram for the q2
//q2 = new TH1D ("q2","Q2 value",100,0.0,0.12);

  //draw the q2 graph for all octants
  // c1->cd(9);

  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / n;


  for (Int_t i = 0; i < n; i++)
  {
    Int_t n1 = nentries / n * i;
    Int_t n2 = nentries / n * (i+1);

    QweakSimG4_Tree->Draw(Form("Primary.PrimaryQ2>>q2[%d][0]",i) ,"Primary.CrossSection * Cerenkov.PMT.PMTTotalNbOfPEs"," ", step ,n1 );
    mean_q2[0] += q2[i][0]->GetMean();
    sigma_q2[0] += q2[i][0]->GetMean() * q2[i][0]->GetMean();
    q2_tot[0]->Add(q2[i][0]);

    //draw the q2 graph for each octants
    for (size_t oct = 1; oct < q2[i].size(); oct ++)
    {
      QweakSimG4_Tree->Draw(Form("Primary.PrimaryQ2>>q2[%d][%d]",i,oct),
        Form("Primary.CrossSection*Cerenkov.PMT.PMTTotalNbOfPEs* (Cerenkov.Detector.DetectorID==%d)/Cerenkov.Detector.NbOfHits",oct), " ", step, n1 );
      mean_q2[oct] += q2[i][oct]->GetMean();
      sigma_q2[oct] += q2[i][oct]->GetMean() * q2[i][oct]->GetMean();
      q2_tot[oct]->Add(q2[i][oct]);
    }

  }

  //define canvas
  TCanvas* c1 = new TCanvas ("c1","Sim Q2");
  c1->Divide(3,3);
  c1->cd(9);
  q2_tot[0]->Draw();

  for (size_t oct = 1; oct < q2_tot.size(); oct ++)
    {
      c1->cd(oct);
      q2_tot[oct]->Draw();
    }

  //calaulate out the right error and mean
  for (size_t oct = 0; oct < q2_tot.size(); oct++)
  {
    cout << mean_q2[oct] << " " << sigma_q2[oct] << endl;
    mean_q2[oct] /= n;
    //the extra  factor of sqrt(n) is to get the error on the mean not just the error of the distibution
    sigma_q2[oct] = sqrt(sigma_q2[oct] / n - mean_q2[oct] * mean_q2[oct]) / sqrt(n);
  }


  //output the values for q2 for all octants together and indidually
  cout << "All Octants" <<endl;
  cout << "q2: " <<  setprecision(5) << 1000*mean_q2[0] << " error RMS/sqrt(N): " <<  setprecision(4) << 1000*sigma_q2[0] << " m(GeV)^2 " << endl;

  for (int oct = 1; oct < 9; oct ++)
  {
    cout << "Octant number " << oct <<endl;
    cout << "q2: " <<  std::setprecision(5) << 1000*mean_q2[oct] << " error RMS/sqrt(N): " <<  std::setprecision(4) << 1000*sigma_q2[oct]<< " m(GeV)^2 " << endl;
  }

  return;

}
