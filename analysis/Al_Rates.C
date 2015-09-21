//=============================================================================
// Kurtis Bartlett
// 2015/7/23 Updated: 2015/9/21 for documentation
// Al_Rates.C
//
// A script designed to calculate the rates from a single aluminum generator
// The details of these generators can be found in Qweak Geant4 generator file
// under SVN control at the follow location: src/QwGeant4/QweakSimEPEvent.cc
//
// Generator 2: Aluminum Elastic (For on peak contribution, has 15 MeV window
// cut.)
// Generator 7: Christy-Bosted Radiative Look-Up Table (For the radiative
// elastic, quasi-elastic, and DIS contributions)
// Generator 9: Aluminum Giant Dipole Resonance
// Generator 11: Aluminum Nuclear Inelastic Single Particle Excited States
//
// How to use it: Run this script with QweakSimRoot found in the build dir.
// i.e. build/QweakSimRoot -l -b -q \(\"commands\"\)
// The script requires three parameters. The first is a naming label included
// to modify the labels of the output files. The second is the path of the 
// files. Note: This currently uses the my file naming convention. This will 
// have to be modified accordingly. The last parameter is the label used to 
// select which type of rate to calculate.
//
// Passing the following character does the following calculation:
//
// s - Schwinger Corrected Elastic with 15 MeV Cut
// e - Radiated Elastic from Generator 7 simulation
// q - Radiated Quasi-elastic from Generator 7 simulation
// d - Radiated Inelastic from Generator 7 simulation
// a - All other types of simulations (EX. InelasticSPS or GDR, could be used 
// for other simulations as well.)
//
// The rates are read out to a file set by the save path and name variables in
// the constants section.
//
// *NOTE: Make sure that you modify the source code to point to source files in
// you QwGeant4 dir.
//=============================================================================


//*****************************************************************************
//Include
//*****************************************************************************

//C,C++ associated
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

//Root associated
#include "TROOT.h"
#include </u/home/kbartlet/Qweak/QwGeant4/include/QweakSimUserMainEvent.hh>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLegend.h>
#include <TAttLine.h>
#include <TAttMarker.h>

//*****************************************************************************
//Constants
//*****************************************************************************
const int pane[8] = {4, 1, 2, 3, 6, 9, 8, 7 }; //Mapping for octant plots
const int np = 8;
const Int_t canvas_x = 600;
const Int_t canvas_y = 400;

const int kBins = 1000;
const double kLowX = 200.0;
const double kHighX = 1200.0;

const double ival = -1.0; //Array Initialization Value

//Set path to save canvases of rate histograms.
//Note - That the save_root_path variable must be the absolute dir, it can not
//include a ~ to start in your home directory.
const char* save_root_path = "/u/home/kbartlet/Qweak/AluminumSimulations/plots/";
//const char* save_root_file_name = "";
const char* save_output_file_name = "_rate_output.txt";
//*****************************************************************************
//Function Declaration
//*****************************************************************************
void graph_plots(const char* title, const char* y_label, std::vector<Double_t> octant, std::vector<Double_t> octant_err,
	std::vector<Double_t> rate, std::vector<Double_t> err);
void output_text(const char* label, std::ostream &outfile, std::vector<Double_t> rate, std::vector<Double_t> err);
void cal_rate(Int_t fnum, std::vector<TH1D*> hist, std::vector<Double_t> &rate, std::vector<Double_t> &err);
void rate_plots(TCanvas *can, const char* label, std::vector<TH1D*> hist);
void walk_tree(TChain *tree, const char tag, std::vector<TH1D*> &hist, const char* label);
TChain* chain_files(const char* rootfilepath, Int_t &fnum);

//*****************************************************************************
//Main
//*****************************************************************************
void Al_Rates(const char* name_label, const char* path, const char label){

	std::cout << "\n" << std::endl;

	//---------------------------------------------------------------------------
	//Format plots with the basic Hall A Root Style.
	//---------------------------------------------------------------------------
  gROOT->Macro("$ROOT_STYLES/kdb_style.cxx");

	//---------------------------------------------------------------------------
	//Open Text File to Write Output and Check File Status
	//---------------------------------------------------------------------------
	std::ofstream output_file;
	output_file.open(Form("%s%s_%s%s", save_root_path, path, name_label, save_output_file_name));
	if(!output_file.is_open()){
		std::cout << "File doesn't exist! \n" << Form("Generating file at the following location: %s%s%s \n", save_root_path, path, save_output_file_name) << std::endl;
		//return;
	}

	//---------------------------------------------------------------------------
	//Store the number of chained files
	//---------------------------------------------------------------------------
	Int_t filenum = 0;

	//---------------------------------------------------------------------------
	//Create Trees for simulation type.
	//---------------------------------------------------------------------------
	TChain* tree = chain_files(path, filenum);

	//---------------------------------------------------------------------------
	//Create Canvas for plot
	//---------------------------------------------------------------------------
	TCanvas* c_rate = new TCanvas("c_rate", "c_rate", 3*canvas_x, 3*canvas_y);
	c_rate->Divide(3,3);

	TCanvas* c_total = new TCanvas("c_total", "c_total", canvas_x, canvas_y);

	//---------------------------------------------------------------------------
	//Initialize Arrays of Histograms
	//---------------------------------------------------------------------------
	std::vector<TH1D*> hist_rate;
	hist_rate.resize(np);

	for(UInt_t oct = 0; oct < hist_rate.size(); oct++){
		hist_rate[oct] = new TH1D(Form("hist_rate[%d]", oct), Form("%s Oct:%d", 
		path, oct+1), kBins, kLowX, kHighX);
		hist_rate[oct]->Sumw2();
	}

	//---------------------------------------------------------------------------
	//Walk through the trees
	//Note: Type of simulation is now designated from the command line during
	//compiling.
	//---------------------------------------------------------------------------
	walk_tree(tree, label, hist_rate, Form("%s:", path));


	//---------------------------------------------------------------------------
	//Plot the rate weighted Vertex KE for post distribution check.
	//---------------------------------------------------------------------------
	rate_plots(c_rate, "Rates", hist_rate);

	//---------------------------------------------------------------------------
	//Initialize Rate and Error Vectors, Size Arrays
	//---------------------------------------------------------------------------
	std::vector<Double_t> octant;
	std::vector<Double_t> octant_err;

	std::vector<Double_t> rate;
	std::vector<Double_t> err;

	std::vector<Double_t> total_rate;
	std::vector<Double_t> total_err;

	//Resize with push_back function
	for(Int_t octt = 0; octt < np; octt++){
		octant.push_back(octt+1);
		octant_err.push_back(0.0);

		rate.push_back(ival);
		err.push_back(ival);

		total_rate.push_back(ival);
		total_err.push_back(ival);
	}

	//---------------------------------------------------------------------------
	//Call function to calculate the rate for each generator. Requires the number
	// of chained files stored in filenum array, vector of histograms, and
	// rate/err vector variables to fill.
	//---------------------------------------------------------------------------
	cal_rate(filenum, hist_rate, rate, err);

	//---------------------------------------------------------------------------
	//Calculate Total Rate
	//---------------------------------------------------------------------------
	for(UInt_t oct = 0; oct < total_rate.size(); oct++){
		total_rate[oct] = rate[oct];
		total_err[oct] = TMath::Sqrt(TMath::Power(err[oct],2));
	}

	//---------------------------------------------------------------------------
	//Write Rates to Output File
	//---------------------------------------------------------------------------
	output_file << Form("%s_%s \n", path, name_label) << std::endl;
	output_text(Form("%s:", path), output_file, rate, err);
	output_text("Total:", output_file, total_rate, total_err);

	output_file.close();
	std::cout << "\n" << Form("Writing Rates to file located: %s%s_%s%s \n", save_root_path, path, name_label, save_output_file_name) << std::endl;


	//---------------------------------------------------------------------------
	//Generate TGraph Plots
	//---------------------------------------------------------------------------
	c_rate->cd(5);
	graph_plots(Form("%s",path), "Rate [MHz/#muA]", octant, octant_err, rate, err);

	c_total->cd();
	graph_plots(Form("%s_%s Total Rate", path, name_label), "Total Rate [MHz/#muA]", octant, octant_err, total_rate, total_err);

	//---------------------------------------------------------------------------
	//Save Plots
	//---------------------------------------------------------------------------
	c_rate->SaveAs(Form("%s%s.png",save_root_path, path));
	c_total->SaveAs(Form("%s%s_%s_total_vs_octant.png",save_root_path, path, name_label));
	return;
}


//*****************************************************************************
//Functions
//*****************************************************************************

void graph_plots(const char* title, const char* y_label, std::vector<Double_t> octant, std::vector<Double_t> octant_err, 
	std::vector<Double_t> rate, std::vector<Double_t> err){

	TGraphErrors* graph = new TGraphErrors(octant.size(), octant.data(), rate.data(), octant_err.data(), err.data());
	graph->SetTitle(Form("%s",title));
	graph->GetXaxis()->SetTitle("Octant");
	graph->GetXaxis()->CenterTitle();
	graph->GetYaxis()->SetTitle(Form("%s",y_label));
	graph->GetYaxis()->CenterTitle();
	graph->SetMarkerColor(kBlue);
	graph->SetMarkerStyle(20);
	graph->Draw("ap");

	return;
}


void output_text(const char* label, std::ostream &outfile, std::vector<Double_t> rate, std::vector<Double_t> err){

	outfile << std::setprecision(5) << std::left << Form("%s \t",label)
		<< std::setw(12) << rate[0] << std::setw(12) << err[0]
		<< std::setw(12) << rate[1] << std::setw(12) << err[1]
		<< std::setw(12) << rate[2] << std::setw(12) << err[2]
		<< std::setw(12) << rate[3] << std::setw(12) << err[3]
		<< std::setw(12) << rate[4] << std::setw(12) << err[4]
		<< std::setw(12) << rate[5] << std::setw(12) << err[5]
		<< std::setw(12) << rate[6] << std::setw(12) << err[6]
		<< std::setw(12) << rate[7] << std::setw(12) << err[7] << "\n";

	return;
}

void cal_rate(Int_t fnum, std::vector<TH1D*> hist, std::vector<Double_t> &rate, std::vector<Double_t> &err){
	for(UInt_t oct = 0; oct < hist.size(); oct ++){
		if(fnum > 0){
			rate[oct] = hist[oct]->IntegralAndError(1,kBins, err[oct]);
			rate[oct] = rate[oct]/1000/fnum; //Factor of 1000 to convert from kHz to MHz
			err[oct] = err[oct]/1000/fnum;
		}
		else{
			std::cout << "WARNING: Attempted Division by Zero!!! \n" << "Check for proper file path or number of files chained." << std::endl;
		}
	}
	return;
}

void rate_plots(TCanvas *can, const char* label, std::vector<TH1D*> hist){
	for(UInt_t oct = 0; oct < hist.size(); oct++){
		can->cd(pane[oct]);
		hist[oct]->GetXaxis()->SetTitle("Vertex Kinetic Energy (Rate Weighted) [MeV]");
		hist[oct]->GetXaxis()->CenterTitle();
		hist[oct]->GetYaxis()->SetTitle("Entries");
		hist[oct]->GetYaxis()->CenterTitle();
		hist[oct]->SetLineColor(kBlue);
		hist[oct]->Draw();
	}
	return;
}

void walk_tree(TChain *tree, const char tag, std::vector<TH1D*> &hist, const char* label){
	QweakSimUserMainEvent *evt = 0;
  QweakSimUserPrimaryEvent *primary = 0;
  QweakSimUserCerenkov_DetectorEvent *detector = 0;
  QweakSimUserCerenkov_PMTEvent *pmt = 0;
	QweakSimUserTarget_DetectorEvent *target = 0;
	//Set the appropriate branch address
  tree->SetBranchAddress("QweakSimUserMainEvent",&evt);

	Int_t num_entries = tree->GetEntries();
	std::cout << "\n" << label << "\n" << std::endl;
  for(Int_t entry = 0; entry < num_entries; entry++ ) {
    if(entry%1000==0){
      std::cout << "Processing entry " << entry << std::endl;
    }
    // Retrieve the entry
    tree->GetEntry(entry);
    primary = &(evt->Primary);
    detector = &(evt->Cerenkov.Detector);
    pmt = &(evt->Cerenkov.PMT);
		target = &(evt->Target.Detector);
		//Test Lines For Debuging
		if( evt == 0 ) {
			std::cerr << "evt Null pointer, exiting:" << std::endl;
			return;
		}
		if( primary == 0 ) {
			std::cerr << "primary Null pointer, exiting:" << std::endl;
			return;
		}
		if( detector == 0 ) {
 			std::cerr << "detector Null pointer, exiting:" << std::endl;
			return;
		}
		if( pmt == 0 ) {
			std::cerr << "pmt Null pointer, exiting:" << std::endl;
			return;
		}
		if( target == 0 ) {
			std::cerr << "target Null pointer, exiting:" << std::endl;
			return;
		}

    // Fill appropriate histogram depending on passed tree
		if(tag == 's'){ //Schwinger Elastic Peak Region with 15MeV window cut
    	for(UInt_t oct = 1; oct < 9; oct++ ){
				if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTLeftNbOfPEs().size() > 8 && pmt->GetPMTLeftNbOfPEs()[oct]>0 && pmt->GetPMTRightNbOfPEs().size() > 8 && pmt->GetPMTRightNbOfPEs()[oct]>0){
        	for(UInt_t j = 0; j < target->GetElasticScatteredEnergy().size(); j++){
          	if((target->GetElasticScatteredEnergy()[j] - target->GetDetectorLocalVertexTotalEnergy()[j]) < 15){
            	if(pmt->GetPMTTotalRate().size() > 8 && pmt->GetPMTTotalRate()[oct]>0){
              	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalRate()[oct]);
            	}
          	}
        	}
      	}
			}
		}
	  else if(tag == 'e'){ //Radiated Elastic from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
				//std::cout << "Checking entry: " << entry << " -> passed" << std::endl;
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTLeftNbOfPEs().size() > 8 && pmt->GetPMTLeftNbOfPEs()[oct]>0 && pmt->GetPMTRightNbOfPEs().size() > 8 && pmt->GetPMTRightNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalRateEL().size() > 8 && pmt->GetPMTTotalRateEL()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalRateEL()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'q'){ //Radiated Quasi-Elastic from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTLeftNbOfPEs().size() > 8 && pmt->GetPMTLeftNbOfPEs()[oct]>0 && pmt->GetPMTRightNbOfPEs().size() > 8 && pmt->GetPMTRightNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalRateQE().size() > 8 && pmt->GetPMTTotalRateQE()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalRateQE()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'd'){ //Radiated DIS from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      		if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTLeftNbOfPEs().size() > 8 && pmt->GetPMTLeftNbOfPEs()[oct]>0 && pmt->GetPMTRightNbOfPEs().size() > 8 && pmt->GetPMTRightNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalRateDIS().size() > 8 && pmt->GetPMTTotalRateDIS()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalRateDIS()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'a'){ //All other rates
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTLeftNbOfPEs().size() > 8 && pmt->GetPMTLeftNbOfPEs()[oct]>0 && pmt->GetPMTRightNbOfPEs().size() > 8 && pmt->GetPMTRightNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalRate().size() > 8 && pmt->GetPMTTotalRate()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalRate()[oct]);
	       	}
      	}
    	}
		}
		else{
			std::cout << "Invalid Fill Cut Parameter Passed to Walk Function" << std::endl;
		}
  }
	return;
}

TChain* chain_files(const char* rootfilepath, Int_t &fnum){
	TChain* tree = new TChain("QweakSimG4_Tree");
	fnum = tree->Add(Form("/cache/mss/home/kbartlet/rootfiles/%s/%s_*.root",
		rootfilepath));
  std::cout << "For Path: " << rootfilepath << "\t" <<
		"Number of Files Found: " << fnum << "\n" <<std::endl;
	return tree;
}
