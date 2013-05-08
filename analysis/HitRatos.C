/***********************************************************
Programmer: Valerie Gray
Purpose:

To get out the ratio of the number of events fired in
   a certian octant with the number of event in a different octant

Also gets the ratio of the asymmetry fired in
   a certian octant with the asymmetry in a different octant

Also gets the ratio of the total number of PEs fired in
   a certian octant with the total number of PEs in a different octant

Calculates the ratio of the aysmmetry and number of PEs weighted
   by the Cross section

-------USEFUL DEFINITIONS-----

Active octant - the octant that the electrons are being fired into
   AKA - for active octant 1, I cut on position of all the scattered
         electrons so that they are only going into that active octant
         (1) in this example

in the final table I use

pos only - means I am cutting on the position of the incomming electrons
     or cutting to get the active octant

CS - means weighting by cross section

PE - means weighting by PE number

------------------------------

This outputs the numbers in a table and in HTML so it can be
   put into an elog with ease.

Entry Conditions:
  Axis - the axis of MD9 is moved along
  pos - the position of MD9
Date: 02-18-2013
Modified: 04-01-2013
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"

#include "TH1D.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "QweakSimUserMainEvent.hh"

using namespace std;

//angle distribution around 0 deg in Phi of MD1
double MD1_phi_angle_range = 22.5;
double MD_bars_phi_angle[9] = {0, 0, 45, 90, 135, 180, -135, -90, -45};

void HitRatios (string axis, double pos)
{

  // groups root files for a run together
  TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

  //add the root files to the chain the event_tree branches
  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct1_%s_%.2Fcm/*.root", axis.c_str(), pos));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct7_%s_%.2Fcm/*.root", axis.c_str(), pos));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct8_%s_%.2Fcm/*.root", axis.c_str(), pos));

//------------
  //define the needed histograms
  std::vector < vector <TH1D*> > h_asymmetry; //[active oct][hits in MD for that actove octant]
  h_asymmetry.resize(9);

  for (size_t i = 0; i < h_asymmetry.size() ; i ++)
  {
    h_asymmetry[i].resize(10);
    for (size_t j = 0; j < h_asymmetry[i].size() ;j++)
    {
      h_asymmetry[i][j]= new TH1D (Form("h_asymmetry[%d][%d]",i,j),Form("Asymmetry in MD %d for active octant %d", j, i), 1000, -1, 1);
      h_asymmetry[i][j]->GetYaxis()->SetTitle("Frequency");
      h_asymmetry[i][j]->GetXaxis()->SetTitle("Asymmetry (ppm)");
    }
  }

  std::vector < vector <TH1D*> > h_PE; //[active oct][hits in MD for that actove octant]
  h_PE.resize(9);

  for (size_t i = 0; i < h_PE.size() ; i ++)
  {
    h_PE[i].resize(10);
    for (size_t j = 0; j < h_PE[i].size() ;j++)
    {
      h_PE[i][j]= new TH1D (Form("h_PE[%d][%d]",i,j),Form("Number of PEs in octant %d for active octant %d", j, i), 1000, 0, 500);
      h_PE[i][j]->GetYaxis()->SetTitle("Frequency");
      h_PE[i][j]->GetXaxis()->SetTitle("Number of PEs");
    }
  }

//-----------
  //define the histograms for the weighting histograms (need to cut into chuncks)
  //number of chunks
  Int_t nchunks = 1000;

  //define vector of histograms
  std::vector < vector < vector <TH1D*> > >  h_asymmetry_cs; //[chunk #][active octant][MD]
  h_asymmetry_cs.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_asymmetry_cs_pe; //[chunk #][active octant][MD]
  h_asymmetry_cs_pe.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_PE_cs; //[chunk #][active octant][MD]
  h_PE_cs.resize(nchunks+1);

  // Asymmerty histpgram weighed by coross Section
  for (size_t i = 0; i<h_asymmetry_cs.size();i++)
  {
     h_asymmetry_cs[i].resize(9);
     for (size_t j = 0; j<h_asymmetry_cs[i].size();j++)
     {
       h_asymmetry_cs[i][j].resize(10);
       for (size_t k = 0;k< h_asymmetry_cs[i][j].size();k++)
       {
         //set the histogram for the h_asymmetry_cs
         h_asymmetry_cs[i][j][k]= new TH1D (Form("h_asymmetry_cs[%d][%d][%d]",i,j,k),Form("Cross Section Werighting Asymmetry in MD %d for active octant %d- chunk %d",k,j,i),1000,-1,1);
         h_asymmetry_cs[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

  // Asymmerty histpgram weighed by coross Section and PEs
  for (size_t i = 0; i<h_asymmetry_cs_pe.size();i++)
  {
     h_asymmetry_cs_pe[i].resize(9);
     for (size_t j = 0; j<h_asymmetry_cs_pe[i].size();j++)
     {
       h_asymmetry_cs_pe[i][j].resize(10);
       for (size_t k = 0;k< h_asymmetry_cs_pe[i][j].size();k++)
       {
         //set the histogram for the h_asymmetry_cs
         h_asymmetry_cs_pe[i][j][k]= new TH1D (Form("h_asymmetry_cs_pe[%d][%d][%d]",i,j,k),Form("Cross Section and PE Werighted Asymmetry in MD %d for active octant %d- chunk %d",k,j,i),1000,-1,1);
         h_asymmetry_cs_pe[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_cs_pe[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

  //PEs
  for (size_t i = 0; i<h_PE_cs.size();i++)
  {
     h_PE_cs[i].resize(9);
     for (size_t j = 0; j<h_PE_cs[i].size();j++)
     {
       h_PE_cs[i][j].resize(10);
       for (size_t k = 0;k< h_PE_cs[i][j].size();k++)
       {
         //set the histogram for the h_PEs_cs
         h_PE_cs[i][j][k]= new TH1D (Form("h_PE_cs[%d][%d][%d]",i,j,k),Form("Cross Section Werighting PEs in MD %d for active octant %d- chunk %d",k,j,i),1000, 0, 500);
         h_PE_cs[i][j][k]->GetXaxis()->SetTitle("Number of PEs ");
         h_PE_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

//----------

  // make arrays to store mean values and stuff to get the error

  //define an array  for the mean and sigma of all the histograms
  //this will allow to get the proper mean - initalze all values to zero.
  //mean it the mean
  //sigma is the mean squared at this point (sorry for the bad naming)

  std::vector<std::vector<Double_t> > mean_asymmetry, sigma_asymmetry, mean_PEs, sigma_PEs, mean_asymmetry_cs_pe, sigma_asymmetry_cs_pe;
  mean_asymmetry.resize(9);
  sigma_asymmetry.resize(9);
  mean_asymmetry_cs_pe.resize(9);
  sigma_asymmetry_cs_pe.resize(9);
  mean_PEs.resize(9);
  sigma_PEs.resize(9);
  for (size_t i = 0; i < mean_asymmetry.size(); i++) {
    mean_asymmetry[i].resize(10,0);
    sigma_asymmetry[i].resize(10,0);
    mean_asymmetry_cs_pe[i].resize(10,0);
    sigma_asymmetry_cs_pe[i].resize(10,0);
    mean_PEs[i].resize(10,0);
    sigma_PEs[i].resize(10,0);
  }

//----------
  //To fill weighted histograms and get errors we need to
  //divide the number of entries up
  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / nchunks;

//----------
  //now that the chain is defined (first lines) and the file(s) are connected
  //right away so accoring to the Deconinck loop ove events script the next thing
  //to do is to set the addresses of the leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);

//fill unweighted histograms - weighted and cut up I have no idea how...
  //loop over chunks
  for(int ichunk = 0; ichunk < nchunks; ichunk++)
  {
    //loop over entries
    for(int i = 0; i < step; i++)
    {
      QweakSimG4_Tree->GetEntry(i + ichunk*step);

     for(size_t nhit=0; nhit< event->Cerenkov.Detector.NbOfHits; nhit++)
     {
       Int_t octant = 0;
       if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[1])<MD1_phi_angle_range)
       {
         octant = 1;

       }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[2])<MD1_phi_angle_range)
         {
           octant = 2;

         }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[3])<MD1_phi_angle_range)
           {
             octant = 3;

           }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[4])<MD1_phi_angle_range)
             {
               octant = 4;

             }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[5])<MD1_phi_angle_range)
               {
                  octant = 5;

                }else if(abs(event->Primary.GetOriginVertexPhiAngle()+MD_bars_phi_angle[5])<MD1_phi_angle_range)
                 {
                    octant = 5;

                 }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[6])<MD1_phi_angle_range)
                   {
                     octant = 6;

                   }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[7])<MD1_phi_angle_range)
                     {
                       octant = 7;

                     }else if (abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[8])<MD1_phi_angle_range)
                       {
                         octant = 8;

                       }
        //unweighted histograms
        h_asymmetry[octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Primary.GetAsymmetry());
        h_PE[octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Cerenkov.PMT.GetPMTTotalNbOfPEs());

        //weightined histograms cross section only
        h_asymmetry_cs[ichunk][octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Primary.GetAsymmetry(),event->Primary.GetCrossSection());
        h_PE_cs[ichunk][octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Cerenkov.PMT.GetPMTTotalNbOfPEs(),event->Primary.GetCrossSection());

        //weightined histograms cross section and PE
        h_asymmetry_cs_pe[ichunk][octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Primary.GetAsymmetry(),
          (event->Primary.GetCrossSection()) * (event->Cerenkov.PMT.GetPMTTotalNbOfPEs()));

     }
   }

   //fill the arrays to get the mean and proper error of a weighting histogram
   for (size_t oct1 = 0; oct1 < 9; oct1++)
   {
     for (size_t oct2 = 0; oct2 < 10; oct2++)
     {
       mean_asymmetry[oct1][oct2] += h_asymmetry_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry[oct1][oct2] +=
         h_asymmetry_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_cs[ichunk][oct1][oct2]->GetMean();

       mean_asymmetry_cs_pe[oct1][oct2] += h_asymmetry_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_cs_pe[oct1][oct2] +=
         h_asymmetry_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_cs[ichunk][oct1][oct2]->GetMean();

       mean_PEs[oct1][oct2] += h_PE_cs[ichunk][oct1][oct2]->GetMean();
       sigma_PEs[oct1][oct2] +=
         h_PE_cs[ichunk][oct1][oct2]->GetMean() * h_PE_cs[ichunk][oct1][oct2]->GetMean();
     }
    }
  }
//---------
  //output the data I have gatered
  //write out the ratios of the hits and aymmetries to the screen
  cout << "Active Oct  \t " << "MD # \t"  << "ratio hits (pos only) \t" << "ratio asymmetry (pos only) \t" << "PE ratio (pos only) \t" <<
     "ratio asymmetry Weight (pos & CS) \t" << "PE ratio Weight (pos & CS) \t" << "ratio asymmetry Weight (pos & CS & PE)" <<  endl;
  for (size_t oct = 1; oct < h_asymmetry.size(); oct ++)
  {
    cout << "Active Oct " << oct << endl;

    for (size_t oct2 = 1; oct2 < h_asymmetry[oct].size(); oct2++)
    {
     //FOR NO WEIGHTING
      // caluculate the hit ratio and the error on that ratio
      Double_t hit_entries1 = h_asymmetry[oct][oct2]->GetEntries();
      Double_t dhit_entries1 = sqrt(hit_entries1);
      Double_t hit_entries2 = h_asymmetry[oct][oct]->GetEntries();
      Double_t dhit_entries2 = sqrt(dhit_entries2);
      Double_t hit_ratio = hit_entries1/hit_entries2;
      Double_t dhit_ratio = sqrt(pow(dhit_entries1/hit_entries2,2) + pow(hit_entries1*dhit_entries2/hit_entries2/hit_entries2,2));

      // Calucate the asymmerty and the error on that
      Double_t a_mean1 = h_asymmetry[oct][oct2]->GetMean();
      Double_t da_mean1 = h_asymmetry[oct][oct2]->GetRMS()/ sqrt(h_asymmetry[oct][oct2]->GetEntries());
      Double_t a_mean2 = h_asymmetry[oct][oct]->GetMean();
      Double_t da_mean2 = h_asymmetry[oct][oct]->GetRMS()/ sqrt(h_asymmetry[oct][oct]->GetEntries());
      Double_t a_ratio = a_mean1/a_mean2;
      Double_t da_ratio = sqrt(pow(da_mean1/a_mean2,2) + pow(a_mean1*da_mean2/a_mean2/a_mean2,2));

      // Calucate the PE and the error on that
      Double_t PE_mean1 = h_PE[oct][oct2]->GetMean();
      Double_t dPE_mean1 = h_PE[oct][oct2]->GetRMS()/ sqrt(h_PE[oct][oct2]->GetEntries());
      Double_t PE_mean2 = h_PE[oct][oct]->GetMean();
      Double_t dPE_mean2 = h_PE[oct][oct]->GetRMS()/ sqrt(h_PE[oct][oct]->GetEntries());
      Double_t PE_ratio = PE_mean1/PE_mean2;
      Double_t dPE_ratio = sqrt(pow(dPE_mean1/PE_mean2,2) + pow(PE_mean1*dPE_mean2/PE_mean2/PE_mean2,2));
     //FOR WEIGHTING
      // Calucate the asymmerty and the error on that (CS only)
      Double_t a_mean1_w = mean_asymmetry[oct][oct2] / nchunks;
      Double_t da_mean1_w = sqrt(sigma_asymmetry[oct][oct2] / nchunks - mean_asymmetry[oct][oct2] / nchunks * mean_asymmetry[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t a_mean2_w = mean_asymmetry[oct][oct]/ nchunks;
      Double_t da_mean2_w = sqrt(sigma_asymmetry[oct][oct]/nchunks - mean_asymmetry[oct][oct] / nchunks * mean_asymmetry[oct][oct] / nchunks) / sqrt(nchunks);
      Double_t a_ratio_w = a_mean1_w/a_mean2_w;
      Double_t da_ratio_w = sqrt(pow(da_mean1_w/a_mean2_w,2) + pow(a_mean1_w*da_mean2_w/a_mean2_w/a_mean2_w,2));

      // Calucate the asymmerty and the error on that (CS and PE)
      Double_t a_mean1_w2 = mean_asymmetry_cs_pe[oct][oct2] / nchunks;
      Double_t da_mean1_w2 = sqrt(sigma_asymmetry_cs_pe[oct][oct2] / nchunks - mean_asymmetry_cs_pe[oct][oct2] / nchunks * mean_asymmetry_cs_pe[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t a_mean2_w2 = mean_asymmetry_cs_pe[oct][oct]/ nchunks;
      Double_t da_mean2_w2 = sqrt(sigma_asymmetry_cs_pe[oct][oct]/nchunks - mean_asymmetry_cs_pe[oct][oct] / nchunks * mean_asymmetry_cs_pe[oct][oct] / nchunks) / sqrt(nchunks);
      Double_t a_ratio_w2 = a_mean1_w2/a_mean2_w2;
      Double_t da_ratio_w2 = sqrt(pow(da_mean1_w2/a_mean2_w2,2) + pow(a_mean1_w2*da_mean2_w2/a_mean2_w2/a_mean2_w2,2));

      // Calucate the PEs and the error on that
      Double_t PE_mean1_w = mean_PEs[oct][oct2] / nchunks;
      Double_t dPE_mean1_w = sqrt(sigma_PEs[oct][oct2] / nchunks - mean_PEs[oct][oct2] / nchunks * mean_PEs[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t PE_mean2_w = mean_PEs[oct][oct] / nchunks;
      Double_t dPE_mean2_w = sqrt(sigma_PEs[oct][oct]/nchunks - mean_PEs[oct][oct] / nchunks * mean_PEs[oct][oct] / nchunks)/ sqrt(nchunks);
      Double_t PE_ratio_w = PE_mean1_w/PE_mean2_w;
      Double_t dPE_ratio_w = sqrt(pow(dPE_mean1_w/PE_mean2_w,2) + pow(PE_mean1_w*dPE_mean2_w/PE_mean2_w/PE_mean2_w,2));


      //Double_t dratio = ratio * sqrt((dn1/n1)^2 + (dn2/n2)^2);
      cout << oct << " \t" << oct2 << " \t" << std::setprecision(5)  << hit_ratio << " +/- " <<  dhit_ratio <<
          " \t \t " << std::setprecision(5)  << a_ratio << " +/- " <<  da_ratio <<
          " \t \t " << std::setprecision(5)  << PE_ratio << " +/- " <<  dPE_ratio <<
          " \t \t " << std::setprecision(5)  << a_ratio_w << " +/- " <<  da_ratio_w <<
          " \t \t " << std::setprecision(5)  << PE_ratio_w << " +/- " <<  dPE_ratio_w <<
          " \t \t " << std::setprecision(5)  << a_ratio_w2 << " +/- " <<  da_ratio_w2 << endl;
//        "\t" << h_asymmetry[oct][oct2]->GetEntries() << " \t " << h_asymmetry[oct][oct]->GetEntries() << endl;
    }
  }

  //write out the ratios of the hits and aymmetries to the screen in HTML so that it can be imported to the elong with ease
  cout << "<table border = \"1\">" << endl;
  cout << "<tr><td align=\"center\" >Active Oct </td><td align=\"center\"> MD # </td><td align=\"center\"> ratio hits (pos only)"
          "</td><td align=\"center\"> ratio asymmetry (pos only) </td><td align=\"center\"> PE ratio (pos only) </td><td align=\"center\">"
          "ratio asymmetry (pos & CS) </td><td align=\"center\"> PE ratio (pos & CS) </td><td align=\"center\"> asymmetry ratio (pos & CS & PE) </td></tr>" << endl;
  for (size_t oct = 1; oct < h_asymmetry.size(); oct ++)
  {
    cout << "<tr><td colspan = \"8\" align=\"center\" >Active Oct " << oct << "</td></tr>" << endl;

    for (size_t oct2 = 1; oct2 < h_asymmetry[oct].size(); oct2++)
    {
     //FOR NO WEIGHTING
      // caluculate the hit ratio and the error on that ratio
      Double_t hit_entries1 = h_asymmetry[oct][oct2]->GetEntries();
      Double_t dhit_entries1 = sqrt(hit_entries1);
      Double_t hit_entries2 = h_asymmetry[oct][oct]->GetEntries();
      Double_t dhit_entries2 = sqrt(dhit_entries2);
      Double_t hit_ratio = hit_entries1/hit_entries2;
      Double_t dhit_ratio = sqrt(pow(dhit_entries1/hit_entries2,2) + pow(hit_entries1*dhit_entries2/hit_entries2/hit_entries2,2));

      // Calucate the asymmerty and the error on that
      Double_t a_mean1 = h_asymmetry[oct][oct2]->GetMean();
      Double_t da_mean1 = h_asymmetry[oct][oct2]->GetRMS()/ sqrt(h_asymmetry[oct][oct2]->GetEntries());
      Double_t a_mean2 = h_asymmetry[oct][oct]->GetMean();
      Double_t da_mean2 = h_asymmetry[oct][oct]->GetRMS()/ sqrt(h_asymmetry[oct][oct]->GetEntries());
      Double_t a_ratio = a_mean1/a_mean2;
      Double_t da_ratio = sqrt(pow(da_mean1/a_mean2,2) + pow(a_mean1*da_mean2/a_mean2/a_mean2,2));

      // Calucate the asymmerty and the error on that
      Double_t PE_mean1 = h_PE[oct][oct2]->GetMean();
      Double_t dPE_mean1 = h_PE[oct][oct2]->GetRMS()/ sqrt(h_PE[oct][oct2]->GetEntries());
      Double_t PE_mean2 = h_PE[oct][oct]->GetMean();
      Double_t dPE_mean2 = h_PE[oct][oct]->GetRMS()/ sqrt(h_PE[oct][oct]->GetEntries());
      Double_t PE_ratio = PE_mean1/PE_mean2;
      Double_t dPE_ratio = sqrt(pow(dPE_mean1/PE_mean2,2) + pow(PE_mean1*dPE_mean2/PE_mean2/PE_mean2,2));

     //FOR WEIGHTING
      // Calucate the asymmerty and the error on that Cross Section weighting only
      Double_t a_mean1_w = mean_asymmetry[oct][oct2] / nchunks;
      Double_t da_mean1_w = sqrt(sigma_asymmetry[oct][oct2] / nchunks - mean_asymmetry[oct][oct2] / nchunks * mean_asymmetry[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t a_mean2_w = mean_asymmetry[oct][oct]/ nchunks;
      Double_t da_mean2_w = sqrt(sigma_asymmetry[oct][oct]/nchunks - mean_asymmetry[oct][oct] / nchunks * mean_asymmetry[oct][oct] / nchunks)/ sqrt(nchunks);
      Double_t a_ratio_w = a_mean1_w/a_mean2_w;
      Double_t da_ratio_w = sqrt(pow(da_mean1_w/a_mean2_w,2) + pow(a_mean1_w*da_mean2_w/a_mean2_w/a_mean2_w,2));

      // Calucate the asymmerty and the error on that (CS and PE)
      Double_t a_mean1_w2 = mean_asymmetry_cs_pe[oct][oct2] / nchunks;
      Double_t da_mean1_w2 = sqrt(sigma_asymmetry_cs_pe[oct][oct2] / nchunks - mean_asymmetry_cs_pe[oct][oct2] / nchunks * mean_asymmetry_cs_pe[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t a_mean2_w2 = mean_asymmetry_cs_pe[oct][oct]/ nchunks;
      Double_t da_mean2_w2 = sqrt(sigma_asymmetry_cs_pe[oct][oct]/nchunks - mean_asymmetry_cs_pe[oct][oct] / nchunks * mean_asymmetry_cs_pe[oct][oct] / nchunks) / sqrt(nchunks);
      Double_t a_ratio_w2 = a_mean1_w2/a_mean2_w2;
      Double_t da_ratio_w2 = sqrt(pow(da_mean1_w2/a_mean2_w2,2) + pow(a_mean1_w2*da_mean2_w2/a_mean2_w2/a_mean2_w2,2));

      // Calucate the PEs and the error on that
      Double_t PE_mean1_w = mean_PEs[oct][oct2] / nchunks;
      Double_t dPE_mean1_w = sqrt(sigma_PEs[oct][oct2] / nchunks - mean_PEs[oct][oct2] / nchunks * mean_PEs[oct][oct2] / nchunks) / sqrt(nchunks);
      Double_t PE_mean2_w = mean_PEs[oct][oct]/ nchunks;
      Double_t dPE_mean2_w = sqrt(sigma_PEs[oct][oct]/nchunks - mean_PEs[oct][oct] / nchunks * mean_PEs[oct][oct] / nchunks)/ sqrt(nchunks);
      Double_t PE_ratio_w = PE_mean1_w/PE_mean2_w;
      Double_t dPE_ratio_w = sqrt(pow(dPE_mean1_w/PE_mean2_w,2) + pow(PE_mean1_w*dPE_mean2_w/PE_mean2_w/PE_mean2_w,2));

      //Double_t dratio = ratio * sqrt((dn1/n1)^2 + (dn2/n2)^2);
      cout << "<tr><td align=\"center\"> " << oct << " </td><td align=\"center\"> " << oct2 << 
          " </td><td align=\"center\"> " << std::setprecision(5) << hit_ratio << " &plusmn " << dhit_ratio <<
          " </td><td align=\"center\"> " << std::setprecision(5)  << a_ratio << " &plusmn " <<  da_ratio <<
          " </td><td align=\"center\"> " << std::setprecision(5)  << PE_ratio << " &plusmn " <<  dPE_ratio <<
          " </td><td align=\"center\"> " << std::setprecision(5)  << a_ratio_w << " &plusmn " <<  da_ratio_w <<
          " </td><td align=\"center\"> " << std::setprecision(5)  << PE_ratio_w << " &plusmn " <<  dPE_ratio_w <<
          " </td><td align=\"center\"> " << std::setprecision(5)  << a_ratio_w2 << " &plusmn " <<  da_ratio_w2 << " </td></tr> " << endl;
//        "\t" << h_asymmetry[oct][oct2]->GetEntries() << " \t " << h_asymmetry[oct][oct]->GetEntries() << endl;
    }
  }
  cout << "</table>" << endl;

  return;
}
