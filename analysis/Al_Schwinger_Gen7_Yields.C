//=============================================================================
// Kurtis Bartlett
// 2015/7/23 Updated: 2015/8/17 for documentation
// Al_Schwinger_Gen7_Yields.C
//
// A script designed to calculate the yields for the Schwinger corrected
// Aluminum elastic generator, the Christy-Bosted Radiative Look-Up table
// method generator, the Aluminum Inelastic Single Particle Excited States
// generator, and the Giant Dipole Resonance generator. The details of these
// generators can be found in Qweak Geant4 generator file under SVN control
// at the follow location: src/QwGeant4/QweakSimEPEvent.cc
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
// The script requires five input parameters. The first is a user defined label.
// This label is used to modify the name of the output files. The following 
// four parameters are the locations of the generator 2, 7, 11, and 9 
// repectively.
//
// The yields are read out to a file set by the save path and name variables in
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
const Int_t pane[8] = {4, 1, 2, 3, 6, 9, 8, 7 };
const Int_t np = 8;
const Int_t canvas_x = 600;
const Int_t canvas_y = 400;

const Int_t kBins = 1000;
const Double_t kLowX = 200.0;
const Double_t kHighX = 1200.0;

const Double_t ival = -1.0; //Array Initialization Value

//Set path to save canvases of yield histograms.
//Note - That the save_root_path variable must be the absolute dir, it can not 
//include a ~ to start in your home directory.
const char* save_root_path = "/u/home/kbartlet/Qweak/AluminumSimulations/dummy_el_peak/";
//const char* save_root_file_name = "Al_4p_DS_qtorscan_peak_test";
const char* save_output_file_name = "_yield_output.txt";
//*****************************************************************************
//Function Declaration
//*****************************************************************************
void graph_plots(const char* title, const char* y_label, std::vector<Double_t> octant, std::vector<Double_t> octant_err, 
	std::vector<Double_t> yield, std::vector<Double_t> err);
void output_text(const char* label, std::ostream &outfile, std::vector<Double_t> yield, std::vector<Double_t> err);
void cal_yield(Int_t fnum, std::vector<TH1D*> hist, std::vector<Double_t> &yield, std::vector<Double_t> &err);
void yield_plots(TCanvas *can, const char* label, std::vector<TH1D*> hist);
void walk_tree(TChain *tree, const char tag, std::vector<TH1D*> &hist, const char* label);
TChain* chain_files(const char* rootfilepath, Int_t &fnum);

//*****************************************************************************
//Main
//*****************************************************************************
void Al_Schwinger_Gen7_Yields(const char* save_root_file_name, const char* schwingerpath,
	const char* gen7path, const char* inelasticSPSpath, const char* GDRpath){

	std::cout << "\n" << std::endl;

	//---------------------------------------------------------------------------
	//Format plots with the basic Hall A Root Style.
	//---------------------------------------------------------------------------
  gROOT->Macro("$ROOT_STYLES/kdb_style.cxx");

	//---------------------------------------------------------------------------
	//Open Text File to Write Output and Check File Status
	//---------------------------------------------------------------------------
	std::ofstream output_file;
	output_file.open(Form("%s%s%s", save_root_path, save_root_file_name, save_output_file_name));
	if(!output_file.is_open()){
		std::cout << "File doesn't exist! \n" << Form("Generating file at the following location: %s%s%s \n", save_root_path, save_root_file_name, save_output_file_name) << std::endl;
		//return;
	}

	//---------------------------------------------------------------------------
	//Array for number of chained files
	// filenum[0] - Schwinger Elastic
	// filenum[1] - Rad Elastic, Rad Quasi-Elastic, and Rad DIS
	// filenum[2] - InelasticSPS
	// filenum[3] - GDR
	//---------------------------------------------------------------------------
	Int_t filenum[4] = {0, 0, 0, 0};

	//---------------------------------------------------------------------------
	//Create Trees for each generator type.
	//---------------------------------------------------------------------------
	TChain* schwinger_tree = chain_files(schwingerpath, filenum[0]);
	TChain* gen7_tree = chain_files(gen7path, filenum[1]);
	TChain* inelasticSPS_tree = chain_files(inelasticSPSpath, filenum[2]);
	TChain* GDR_tree = chain_files(GDRpath, filenum[3]);

	//---------------------------------------------------------------------------
	//Create Canvas for plot
	//---------------------------------------------------------------------------
	TCanvas* c_schwinger = new TCanvas("c_schwinger", "c_schwinger", 3*canvas_x, 3*canvas_y);
	c_schwinger->Divide(3,3);

	TCanvas* c_rad_elastic = new TCanvas("c_rad_elastic", "c_rad_elastic", 3*canvas_x, 3*canvas_y);
	c_rad_elastic->Divide(3,3);

	TCanvas* c_rad_quasielastic = new TCanvas("c_rad_quasielastic", "c_rad_quasielastic", 3*canvas_x, 3*canvas_y);
	c_rad_quasielastic->Divide(3,3);

	TCanvas* c_rad_DIS = new TCanvas("c_rad_DIS", "c_rad_DIS", 3*canvas_x, 3*canvas_y);
	c_rad_DIS->Divide(3,3);

	TCanvas* c_inelasticSPS = new TCanvas("c_inelasticSPS", "c_inelasticSPS", 3*canvas_x, 3*canvas_y);
	c_inelasticSPS->Divide(3,3);

	TCanvas* c_GDR = new TCanvas("c_GDR", "c_GDR", 3*canvas_x, 3*canvas_y);
	c_GDR->Divide(3,3);

	TCanvas* c_total = new TCanvas("c_total", "c_total", canvas_x, canvas_y);
	//---------------------------------------------------------------------------
	//Initialize Arrays of Histograms
	//---------------------------------------------------------------------------
	std::vector<TH1D*> hist_schwinger;
	hist_schwinger.resize(np);

	std::vector<TH1D*> hist_rad_elastic;
	hist_rad_elastic.resize(np);

	std::vector<TH1D*> hist_rad_quasielastic;
	hist_rad_quasielastic.resize(np);

	std::vector<TH1D*> hist_rad_DIS;
	hist_rad_DIS.resize(np);

	std::vector<TH1D*> hist_inelasticSPS;
	hist_inelasticSPS.resize(np);

	std::vector<TH1D*> hist_GDR;
	hist_GDR.resize(np);


	for(UInt_t oct = 0; oct < hist_rad_elastic.size(); oct++){
		hist_schwinger[oct] = new TH1D(Form("hist_schwinger[%d]", oct), Form("Schwinger El Peak Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_schwinger[oct]->Sumw2();

		hist_rad_elastic[oct] = new TH1D(Form("hist_rad_elastic[%d]", oct), Form("Radiated Elastic Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_rad_elastic[oct]->Sumw2();

		hist_rad_quasielastic[oct] = new TH1D(Form("hist_rad_quasielastic[%d]", oct), Form("Radiated Quasi-Elastic Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_rad_quasielastic[oct]->Sumw2();

		hist_rad_DIS[oct] = new TH1D(Form("hist_rad_DIS[%d]", oct), Form("Radiated DIS Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_rad_DIS[oct]->Sumw2();

		hist_inelasticSPS[oct] = new TH1D(Form("hist_inelasticSPS[%d]", oct), Form("InelasticSPS Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_inelasticSPS[oct]->Sumw2();

		hist_GDR[oct] = new TH1D(Form("hist_GDR[%d]", oct), Form("GDR Oct:%d", oct+1), kBins, kLowX, kHighX);
		hist_GDR[oct]->Sumw2();
	}

	//---------------------------------------------------------------------------
	//Walk through the trees
	//Note: walk_tree function requires to proper fill cut parameter to provide
	//the correct cuts and variables to fill your histograms. The code system is
	//as follows:
	// s - Schwinger Aluminum Elastic (Has 15 MeV Window Cut)
	// e - Generator 7 Radiated Elastic
	// q - Generator 7 Radiated Quasi-elastic
	// d - Generator 7 Radiated DIS
	// a - all others (Inelastic SPS and GDR)
	//---------------------------------------------------------------------------
	walk_tree(schwinger_tree, 's', hist_schwinger, "Schwinger:");
	walk_tree(gen7_tree, 'e', hist_rad_elastic, "Rad Elastic:");
	walk_tree(gen7_tree, 'q', hist_rad_quasielastic, "Rad Quasi-Elastic:");
	walk_tree(gen7_tree, 'd', hist_rad_DIS, "Rad DIS:");
	walk_tree(inelasticSPS_tree, 'a', hist_inelasticSPS, "InelasticSPS:");
	walk_tree(GDR_tree, 'a', hist_GDR, "GDR:");


	//---------------------------------------------------------------------------
	//Plot the yield weighted Vertex KE for post distribution check.
	//---------------------------------------------------------------------------
	yield_plots(c_schwinger, "Test", hist_schwinger);
	yield_plots(c_rad_elastic, "Test", hist_rad_elastic);
	yield_plots(c_rad_quasielastic, "Test", hist_rad_quasielastic);
	yield_plots(c_rad_DIS, "Test", hist_rad_DIS);
	yield_plots(c_inelasticSPS, "Test", hist_inelasticSPS);
	yield_plots(c_GDR, "Test", hist_GDR);

	//---------------------------------------------------------------------------
	//Initialize Yield and Error Vectors, Size Arrays
	//---------------------------------------------------------------------------
	std::vector<Double_t> octant;
	std::vector<Double_t> octant_err;

	std::vector<Double_t> schwinger_yield;
	std::vector<Double_t> schwinger_err;

	std::vector<Double_t> rad_elastic_yield;
	std::vector<Double_t> rad_elastic_err;

	std::vector<Double_t> rad_quasielastic_yield;
	std::vector<Double_t> rad_quasielastic_err;

	std::vector<Double_t> rad_DIS_yield;
	std::vector<Double_t> rad_DIS_err;

	std::vector<Double_t> inelasticSPS_yield;
	std::vector<Double_t> inelasticSPS_err;

	std::vector<Double_t> GDR_yield;
	std::vector<Double_t> GDR_err;

	std::vector<Double_t> total_yield;
	std::vector<Double_t> total_err;

	//Resize with push_back function
	for(Int_t octt = 0; octt < np; octt++){
		octant.push_back(octt+1);
		octant_err.push_back(0.0);

		schwinger_yield.push_back(ival);
		schwinger_err.push_back(ival);

		rad_elastic_yield.push_back(ival);
		rad_elastic_err.push_back(ival);

		rad_quasielastic_yield.push_back(ival);
		rad_quasielastic_err.push_back(ival);

		rad_DIS_yield.push_back(ival);
		rad_DIS_err.push_back(ival);

		inelasticSPS_yield.push_back(ival);
		inelasticSPS_err.push_back(ival);

		GDR_yield.push_back(ival);
		GDR_err.push_back(ival);

		total_yield.push_back(ival);
		total_err.push_back(ival);
	}

	//---------------------------------------------------------------------------
	//Call function to calculate the yield for each generator. Requires the number
	// of chained files stored in filenum array, vector of histograms, and
	// yield/err vector variables to fill.
	//---------------------------------------------------------------------------
	cal_yield(filenum[0], hist_schwinger, schwinger_yield, schwinger_err);
	cal_yield(filenum[1], hist_rad_elastic, rad_elastic_yield, rad_elastic_err);
	cal_yield(filenum[1], hist_rad_quasielastic, rad_quasielastic_yield, rad_quasielastic_err);
	cal_yield(filenum[1], hist_rad_DIS, rad_DIS_yield, rad_DIS_err);
	cal_yield(filenum[2], hist_inelasticSPS, inelasticSPS_yield, inelasticSPS_err);
	cal_yield(filenum[3], hist_GDR, GDR_yield, GDR_err);

	//---------------------------------------------------------------------------
	//Calculate Total Yield
	//
	// Total Yield is the sum of the Schwinger Elastic, Rad Elastic, Rad Quasi,
	// Rad DIS, InelasticSPS, and GDR.
	// Total Err is the Sqrt the sum of the squares.
	//---------------------------------------------------------------------------
	for(UInt_t oct = 0; oct < total_yield.size(); oct++){
		total_yield[oct] = schwinger_yield[oct] + rad_elastic_yield[oct] + rad_quasielastic_yield[oct] + rad_DIS_yield[oct] + inelasticSPS_yield[oct] + GDR_yield[oct];
		total_err[oct] = TMath::Sqrt(TMath::Power(schwinger_err[oct],2) + TMath::Power(rad_elastic_err[oct],2) + TMath::Power(rad_quasielastic_err[oct],2) + TMath::Power(rad_DIS_err[oct],2) + TMath::Power(inelasticSPS_err[oct],2) + TMath::Power(GDR_err[oct],2));
	}

	//---------------------------------------------------------------------------
	//Write Yields to Output File
	//---------------------------------------------------------------------------
	output_file << Form("%s_Yields \n", save_root_file_name) << std::endl;
	output_text("Schwinger:", output_file, schwinger_yield, schwinger_err);
	output_text("Rad Elastic:", output_file, rad_elastic_yield, rad_elastic_err);
	output_text("Rad Quasi:", output_file, rad_quasielastic_yield, rad_quasielastic_err);
	output_text("Rad DIS:", output_file, rad_DIS_yield, rad_DIS_err);
	output_text("InelasticSPS:", output_file, inelasticSPS_yield, inelasticSPS_err);
	output_text("GDR:", output_file, GDR_yield, GDR_err);
	output_text("Total:", output_file, total_yield, total_err);

	output_file.close();
	std::cout << "\n" << Form("Writing Yields to file located: %s%s%s \n", save_root_path, save_root_file_name, save_output_file_name) << std::endl;


	//---------------------------------------------------------------------------
	//Generate TGraph Plots
	//---------------------------------------------------------------------------
	c_schwinger->cd(5);
	graph_plots(Form("%s",schwingerpath), "Schwinger Yield [?/#muA]", octant, octant_err, schwinger_yield, schwinger_err);

	c_rad_elastic->cd(5);
	graph_plots(Form("%s Rad Elastic", gen7path), "Rad Elastic Yield [?/#muA]", octant, octant_err, rad_elastic_yield, rad_elastic_err);

	c_rad_quasielastic->cd(5);
	graph_plots(Form("%s Rad Quasi-Elastic", gen7path), "Rad Quasi Yield [?/#muA]", octant, octant_err, rad_quasielastic_yield, rad_quasielastic_err);

	c_rad_DIS->cd(5);
	graph_plots(Form("%s Rad DIS", gen7path), "Rad DIS Yield [?/#muA]", octant, octant_err, rad_DIS_yield, rad_DIS_err);

	c_inelasticSPS->cd(5);
	graph_plots(Form("%s Inelastic", inelasticSPSpath), "InelasticSPS Yield [?/#muA]", octant, octant_err, inelasticSPS_yield, inelasticSPS_err);

	c_GDR->cd(5);
	graph_plots(Form("%s GDR", GDRpath), "GDR Yield [?/#muA]", octant, octant_err, GDR_yield, GDR_err);

	c_total->cd();
	graph_plots(Form("%s Total Yields", save_root_file_name), "Total Yield [?/#muA]", octant, octant_err, total_yield, total_err);

	//---------------------------------------------------------------------------
	//Save Plots
	//---------------------------------------------------------------------------
	c_schwinger->SaveAs(Form("%s%s_yields.png",save_root_path, schwingerpath));
	c_rad_elastic->SaveAs(Form("%s%s_rad_elastic_yields.png",save_root_path, gen7path));
	c_rad_quasielastic->SaveAs(Form("%s%s_rad_quasi_yields.png",save_root_path, gen7path));
	c_rad_DIS->SaveAs(Form("%s%s_rad_DIS_yields.png",save_root_path, gen7path));
	c_inelasticSPS->SaveAs(Form("%s%s_yields.png",save_root_path, inelasticSPSpath));
	c_GDR->SaveAs(Form("%s%s_yields.png",save_root_path, GDRpath));
	c_total->SaveAs(Form("%s%s_total_vs_octant_yields.png",save_root_path, save_root_file_name));
	return;
}


//*****************************************************************************
//Functions
//*****************************************************************************

void graph_plots(const char* title, const char* y_label, std::vector<Double_t> octant, std::vector<Double_t> octant_err, 
	std::vector<Double_t> yield, std::vector<Double_t> err){

	TGraphErrors* graph = new TGraphErrors(octant.size(), octant.data(), yield.data(), octant_err.data(), err.data());
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


void output_text(const char* label, std::ostream &outfile, std::vector<Double_t> yield, std::vector<Double_t> err){

	outfile << std::setprecision(5) << std::left << Form("%s \t",label)
		<< std::setw(12) << yield[0] << std::setw(12) << err[0]
		<< std::setw(12) << yield[1] << std::setw(12) << err[1]
		<< std::setw(12) << yield[2] << std::setw(12) << err[2]
		<< std::setw(12) << yield[3] << std::setw(12) << err[3]
		<< std::setw(12) << yield[4] << std::setw(12) << err[4]
		<< std::setw(12) << yield[5] << std::setw(12) << err[5]
		<< std::setw(12) << yield[6] << std::setw(12) << err[6]
		<< std::setw(12) << yield[7] << std::setw(12) << err[7] << "\n";

	return;
}

void cal_yield(Int_t fnum, std::vector<TH1D*> hist, std::vector<Double_t> &yield, std::vector<Double_t> &err){
	for(UInt_t oct = 0; oct < hist.size(); oct ++){
		if(fnum > 0){
			yield[oct] = hist[oct]->IntegralAndError(1,kBins-1, err[oct]);
			yield[oct] = yield[oct]/1000/fnum; //Factor of 1000 to convert from kHz to MHz
			err[oct] = err[oct]/1000/fnum;
		}
		else{
			std::cout << "WARNING: Attempted Division by Zero!!! \n" << "Check for proper file path or number of files chained." << std::endl;
		}
	}
	return;
}

void yield_plots(TCanvas *can, const char* label, std::vector<TH1D*> hist){
	for(UInt_t oct = 0; oct < hist.size(); oct++){
		can->cd(pane[oct]);
		hist[oct]->GetXaxis()->SetTitle("Vertex Kinetic Energy (Yield Weighted) [MeV]");
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
	QweakSimUserTarget_DetectorEvent *target =0;
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
				if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTTotalNbOfPEs().size() > 8 && pmt->GetPMTTotalNbOfPEs()[oct]>0){
        	for(UInt_t j = 0; j < target->GetElasticScatteredEnergy().size(); j++){
          	if((target->GetElasticScatteredEnergy()[j] - target->GetDetectorLocalVertexTotalEnergy()[j]) < 15){
            	if(pmt->GetPMTTotalYield().size() > 8 && pmt->GetPMTTotalYield()[oct]>0){
              	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalYield()[oct]);
            	}
          	}
        	}
      	}
			}
		}
	  else if(tag == 'e'){ //Radiated Elastic from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
				//std::cout << "Checking entry: " << entry << " -> passed" << std::endl;
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTTotalNbOfPEs().size() > 8 && pmt->GetPMTTotalNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalYieldEL().size() > 8 && pmt->GetPMTTotalYieldEL()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalYieldEL()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'q'){ //Radiated Quasi-Elastic from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTTotalNbOfPEs().size() > 8 && pmt->GetPMTTotalNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalYieldQE().size() > 8 && pmt->GetPMTTotalYieldQE()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalYieldQE()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'd'){ //Radiated DIS from Gen7
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      		if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTTotalNbOfPEs().size() > 8 && pmt->GetPMTTotalNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalYieldDIS().size() > 8 && pmt->GetPMTTotalYieldDIS()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalYieldDIS()[oct]);
	       	}
      	}
    	}
		}
		else if(tag == 'a'){ //All other yields
    	for(UInt_t oct = 1; oct < 9; oct++ ) {
      	if(detector->GetDetectorHasBeenHit() == 5 && pmt->GetPMTTotalNbOfPEs().size() > 8 && pmt->GetPMTTotalNbOfPEs()[oct]>0){
        	if(pmt->GetPMTTotalYield().size() > 8 && pmt->GetPMTTotalYield()[oct]>0) {
          	hist[oct-1]->Fill(primary->OriginVertexKineticEnergy,pmt->GetPMTTotalYield()[oct]);
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
		rootfilepath, rootfilepath));
  std::cout << "For Path: " << rootfilepath << "\t" <<
		"Number of Files Found: " << fnum << "\n" <<std::endl;
	return tree;
}
