/*********************************************************** 
Programmer: Valerie Gray
Purpose: To graph that file data from a txt file and give me the stat for beam Position or angle and save that graph

Entry Conditions: file name, direction, what, and units for what and octant
Date: 05-23-2012
Modified:
Assisted By: Juan Carlos
*********************************************************/

#include <TGraphErrors.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TROOT.h>
#include <TCanvas.h>

using namespace std;

void SimAnal (string filename, string dir, string what, string units, int oct)
{

TCanvas c1(Form("Octant %d - Q2 vs %s beam position", oct, dir.c_str()));

//add a file to the TGraphErrors - which is at graph formed from data that has error bars
TGraphErrors * gr = new TGraphErrors (Form("%s.txt",filename.c_str()));

//set it so the errors print
gStyle->SetOptFit(1110);

//set markercolor - Blue
gr->SetMarkerColor(4);

//set Marker size
gr->SetMarkerSize(1);

//set marker style - filled circle
gr->SetMarkerStyle(8);

//set Title, and axis
gr->SetTitle(Form("Octant %d - Q2 vs %s beam %s", oct, dir.c_str(), what.c_str()));
gr->GetXaxis()->SetTitle(Form("%s beam %s (%s)",dir.c_str(),what.c_str(), units.c_str() ));
gr->GetYaxis()->SetTitle("Q2 (m(GeV)^2)");

//Draw this wonderfull data - A=Axis are drawn around the graph - P=Axis are drawn around the graph
gr->Draw("AP");

//firt this graph with a linear fit
gr->Fit("pol1","EX0");

c1.SaveAs(Form("Octant_%d_Q2_vs_%s_%s.png",oct, dir.c_str(),what.c_str()));

}
