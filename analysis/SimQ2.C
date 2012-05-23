/*********************************************************** 
Programmer: Valerie Gray
Purpose: To Output the Q2 values for simulated data

Entry Conditions: octant, x and y position , x and y angle direction
Date: 04-11-2012
Modified:
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"

#include "TH1D.h"
#include <fstream>
#include <iostream>
#include <iomanip>


TH1D* q2;

void SimQ2 (int oct, int posx, int posy, int anglex, int angley)
{
// groups root files for a run together
TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

//add the root files to the chain the event_tree branches
QweakSimG4_Tree->Add(Form("~/QWGEANT4/rootfiles/Octant%d_PositionX_%dmm_PositionY_%dmm_DirectionX_%durad_DirectionY_%durad_3.root",oct,posx,posy, anglex, angley));

//define canvas
TCanvas c1("c1","Sim Q2");

//set the histogram for the q2
q2 = new TH1D ("q2","Q2 value",100,0.0,0.12);

//draw the q2 graph or not
QweakSimG4_Tree->Draw("Primary.PrimaryQ2>>q2","Primary.CrossSection");
q2->Draw();

//output the values for q2
cout << "q2: " <<  setprecision(5) << 1000*q2->GetMean() << " error RMS/sqrt(N): " <<  setprecision(4) << 1000*q2->GetRMS()/sqrt(q2->GetEntries()) << endl;

}
