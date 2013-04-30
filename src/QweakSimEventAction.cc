//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimEventAction.cc

   $Date: Fri Jul  3 11:38:14 CDT 2009 $

   \author Klaus Hans Grimm
   \author Jie Pan

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimEventAction.hh"
#include "QweakSimEventActionMessenger.hh"

// geant4 includes
#include "G4Event.hh"
#include "G4UserEventAction.hh"
#include "G4SDManager.hh"

// user includes
#include "QweakSimAnalysis.hh"
#include "QweakSimUserInformation.hh"
//#include "QweakSimGEM_WirePlaneHit.hh"
#include "QweakSimHDC_WirePlaneHit.hh"
#include "QweakSimVDC_WirePlaneHit.hh"
#include "QweakSimVDC_DriftCellHit.hh"
#include "QweakSimTriggerScintillator_DetectorHit.hh"
#include "QweakSimTriggerScintillator_PMTHit.hh"
#include "QweakSimLeadGlass_DetectorHit.hh"
#include "QweakSimLeadGlass_PMTHit.hh"
#include "QweakSimCerenkov_DetectorHit.hh"
#include "QweakSimCerenkovDetector_PMTHit.hh"
#include "QweakSimTrajectory.hh"
#include "QweakSimUserMainEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimEventAction::QweakSimEventAction(QweakSimAnalysis* AN, QweakSimUserInformation* myUI)
{

//---------------------------------------------------------------------------------------------
//! Constructor of QweakSimEventAction
    /*!

    \param  AN     class containing the Geamt4 hit data structure
    \param  myUI   class containing user information like Q2 for this event or QE of some PMTs
                                         which is needed for processing/saving hit information


    */
//---------------------------------------------------------------------------------------------


    //GEM_WirePlane_CollID                  = -1;
    HDC_WirePlane_CollID                  = -1;
    VDC_WirePlane_CollID                  = -1;
    VDC_DriftCellFront_CollID             = -1;
    VDC_DriftCellBack_CollID              = -1;
    TriggerScintillatorDetector_CollID    = -1;
    //TriggerScintillatorPMT_CollID         = -1;
    LeadGlassDetector_CollID              = -1;
    //LeadGlassPMT_CollID                   = -1;
    CerenkovDetector_CollID               = -1;
    CerenkovDetectorPMT_CollID            = -1;

    analysis    = AN;
    myUserInfo  = myUI;

    // Event action messenger
    fEventActionMessenger = new QweakSimEventActionMessenger(this);

    // Initialize map from string to trigger mode
    fTrigger.resize(kNumTriggers, false);
    fTriggerName.resize(kNumTriggers);
    if (kMapTriggerMode.size() == 0) {
        kMapTriggerMode["all"]   = kTriggerAll;
        fTriggerName[kTriggerAll] = "all";
        kMapTriggerMode["4fold"] = kTrigger4Fold;
        fTriggerName[kTrigger4Fold] = "4fold";
        kMapTriggerMode["3fold"] = kTrigger3Fold;
        fTriggerName[kTrigger3Fold] = "3fold";
        kMapTriggerMode["scint"] = kTriggerScint;
        fTriggerName[kTriggerScint] = "scint";
        kMapTriggerMode["leadglass"] = kTriggerLeadGlass;  // trigger for the lead glass
        fTriggerName[kTriggerLeadGlass] = "leadglass";
        // kMapTriggerMode["gem"]   = kTriggerGEM;
        // fTriggerName[kTriggerGEM] = "gem";
        kMapTriggerMode["cer"]   = kTriggerCer;
        fTriggerName[kTriggerCer] = "cer";
    }
    if (kMapTriggerMode.size() != kNumTriggers)
        G4cout << "Number of software triggers is not defined correctly!" << G4endl;

    // Initialize software trigger to false
    for (size_t iTrigger = 0; iTrigger < fTrigger.size(); iTrigger++)
        fTrigger[iTrigger] = false;

    // By default enable only cerenkov trigger
    fTrigger[kTriggerCer] = true;

    // By default, enable print out of hit information
    printhits = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimEventAction::~QweakSimEventAction()
{
    // Delete the event action messenger
    if (fEventActionMessenger) delete fEventActionMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::ShowTrigger()
{
    for (size_t iTrigger = 0; iTrigger < fTrigger.size(); iTrigger++)
        G4cout << (fTrigger[iTrigger]? "Enabled":"Disabled")
        << " software trigger " << fTriggerName[iTrigger] << "." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::SetTrigger(const G4String value, const G4bool status)
{
    // No error checking here...
    //std::transform(value.begin(), value.end(), value.begin(), std::tolower);
    fTrigger[kMapTriggerMode[value]] = status;
    G4cout << (status? "Enabled":"Disabled") << " software trigger " << value << "." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::BeginOfEventAction(const G4Event* /*evt*/)
{
    G4SDManager * SDman = G4SDManager::GetSDMpointer();

    // check for existing GEM_WirePlane Collection ID (if it's -1 it will be assigned)
//     if (GEM_WirePlane_CollID==-1) {
//         GEM_WirePlane_CollID = SDman->GetCollectionID("GEMWirePlaneSD/GEMWirePlaneCollection");
//     }

    // check for existing HDC_WirePlane Collection ID (if it's -1 it will be assigned)
    if (HDC_WirePlane_CollID==-1) {
        HDC_WirePlane_CollID = SDman->GetCollectionID("HDCWirePlaneSD/HDCWirePlaneCollection");
    }

    // check for existing VDC_WirePlane Collection ID (if it's -1 it will be assigned)
    if (VDC_WirePlane_CollID==-1) {
        VDC_WirePlane_CollID = SDman->GetCollectionID("VDCWirePlaneSD/VDCWirePlaneCollection");
    }

    // check for existing VDC_DriftCellFront Collection ID (if it's -1 it will be assigned)
    if (VDC_DriftCellFront_CollID==-1) {
        VDC_DriftCellFront_CollID = SDman->GetCollectionID("VDCDriftCellFrontSD/DriftCellFrontCollection");
    }

    // check for existing VDC_DriftCellBack Collection ID (if it's -1 it will be assigned)
    if (VDC_DriftCellBack_CollID==-1) {
        VDC_DriftCellBack_CollID = SDman->GetCollectionID("VDCDriftCellBackSD/DriftCellBackCollection");
    }


    // check for existing TriggerScintillator Collection ID (if it's -1 it will be assigned)
    if (TriggerScintillatorDetector_CollID==-1) {
        TriggerScintillatorDetector_CollID = SDman->GetCollectionID("TriggerScintillatorSD/TriggerScintillatorCollection");
    }

	// check for existing LeadGlass Collection ID (if it's -1 it will be assigned)
    if (LeadGlassDetector_CollID==-1) {
        LeadGlassDetector_CollID = SDman->GetCollectionID("LeadGlassSD/LeadGlassCollection");
    }
	
    // check for existing CerenkovDetector Collection ID (if it's -1 it will be assigned)
    if (CerenkovDetector_CollID==-1) {
        CerenkovDetector_CollID = SDman->GetCollectionID("CerenkovDetectorSD/CerenkovDetectorCollection");
    }

    // check for existing CerenkovDetectorPMT Collection ID (if it's -1 it will be assigned)
    if (CerenkovDetectorPMT_CollID==-1) {
        CerenkovDetectorPMT_CollID = SDman->GetCollectionID("CerenkovPMTSD/PMTHitCollection");
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEventAction::EndOfEventAction(const G4Event* evt) {

//-----------------------------------------------------------------------------
// I'm playing with the QweakSimTrajectory
// Startup: LXe example
// Goal: sace track or track points into ROOT file
//
    G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();

    G4int n_trajectories = 0;

    if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

    // extract the trajectories and draw them
    if (G4VVisManager::GetConcreteInstance()) {

        for (G4int i=0; i<n_trajectories; i++) {

            QweakSimTrajectory* trj = (QweakSimTrajectory*) ((*(evt->GetTrajectoryContainer()))[i]);
            trj->DrawTrajectory(50);

        }
    }

//-----------------------------------------------------------------------------

    // preset variables for hit collection
    Initialize();

    // Get current Event Number
    //G4int event_id = evt->GetEventID();

    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();

    // initialize HitsCollection pointers
    //QweakSimGEM_WirePlane_HitsCollection*                    GEM_WirePlane_HC                   = 0;
    QweakSimHDC_WirePlane_HitsCollection*                    HDC_WirePlane_HC                   = 0;
    QweakSimVDC_WirePlane_HitsCollection*                    VDC_WirePlane_HC                   = 0;
    QweakSimVDC_DriftCellHitsCollection*                     VDC_DriftCellFront_HC              = 0;
    QweakSimVDC_DriftCellHitsCollection*                     VDC_DriftCellBack_HC               = 0;
    QweakSimTriggerScintillator_DetectorHitsCollection*      TriggerScintillatorDetector_HC     = 0;
    //QweakSimTriggerScintillator_PMTHitsCollection*           TriggerScintillatorPMT_HC          = 0;
    QweakSimLeadGlass_DetectorHitsCollection*                LeadGlassDetector_HC               = 0;
    //QweakSimLeadGlass_PMTHitsCollection*                   LeadGlassPMT_HC                    = 0;
    QweakSimCerenkovDetectorHitsCollection*                  CerenkovDetector_HC                = 0;
    QweakSimCerenkovDetector_PMTHitsCollection*              CerenkovDetectorPMT_HC             = 0;

    if (HCE) {

        // get  GEM_WirePlane Hit Collector pointer
        //GEM_WirePlane_HC       = (QweakSimGEM_WirePlane_HitsCollection*)(HCE->GetHC(GEM_WirePlane_CollID));
        //n_GEMhitWirePlane      = GEM_WirePlane_HC -> entries();

        // get  HDC_WirePlane Hit Collector pointer
        if (HDC_WirePlane_CollID > -1) {
            HDC_WirePlane_HC       = (QweakSimHDC_WirePlane_HitsCollection*)(HCE->GetHC(HDC_WirePlane_CollID));
            n_HDChitWirePlane      = HDC_WirePlane_HC  -> entries();
        }

        // get  VDC_WirePlane Hit Collector pointer
        if (VDC_WirePlane_CollID > -1) {
            VDC_WirePlane_HC       = (QweakSimVDC_WirePlane_HitsCollection*)(HCE->GetHC(VDC_WirePlane_CollID));
            n_VDChitWirePlane      = VDC_WirePlane_HC -> entries();
        }

        // get  VDC_DriftCellFront Hit Collector pointer
        if (VDC_DriftCellFront_CollID > -1) {
            VDC_DriftCellFront_HC  = (QweakSimVDC_DriftCellHitsCollection*)(HCE->GetHC(VDC_DriftCellFront_CollID));
            n_VDChitDCFront        = VDC_DriftCellFront_HC -> entries();
        }

        // get  VDC_DriftCellFront Hit Collector pointer
        if (VDC_DriftCellBack_CollID > -1) {
            VDC_DriftCellBack_HC   = (QweakSimVDC_DriftCellHitsCollection*)(HCE->GetHC(VDC_DriftCellBack_CollID));
            n_VDChitDCBack         = VDC_DriftCellBack_HC -> entries();
        }

        // get  TriggerScintillator Hit Collector pointer
        if (TriggerScintillatorDetector_CollID > -1) {
            TriggerScintillatorDetector_HC = (QweakSimTriggerScintillator_DetectorHitsCollection*)(HCE->GetHC(TriggerScintillatorDetector_CollID));
            n_hitTriggerScintillator       = TriggerScintillatorDetector_HC -> entries();
        }

        // get  TriggerScintillatorPMT Hit Collector pointer
        //if (TriggerScintillatorPMT_CollID > -1) {
        //    TriggerScintillatorPMT_HC   = (QweakSimTriggerScintillator_PMTHitsCollection*)(HCE->GetHC(TriggerScintillatorPMT_CollID));
        //    n_hitTriggerScintillatorPMT = TriggerScintillatorPMT_HC -> entries();
        //}
		
		// get  LeadGlass Hit Collector pointer
        if (LeadGlassDetector_CollID > -1) {
            LeadGlassDetector_HC  = (QweakSimLeadGlass_DetectorHitsCollection*)(HCE->GetHC(LeadGlassDetector_CollID));
            n_hitLeadGlass        = LeadGlassDetector_HC -> entries();
		}
		
        // get  LeadGlassPMT Hit Collector pointer
        //if (LeadGlassPMT_CollID > -1) {
        //    LeadGlassPMT_HC    = (QweakSimLeadGlass_PMTHitsCollection*)(HCE->GetHC(LeadGlassPMT_CollID));
        //    n_hitLeadGlassPMT  = LeadGlassPMT_HC -> entries();
        //}

        // get  CerenkovDetector Hit Collector pointer
        if (CerenkovDetector_CollID > -1) {
            CerenkovDetector_HC    = (QweakSimCerenkovDetectorHitsCollection*)(HCE->GetHC(CerenkovDetector_CollID));
            n_hitCerenkov          = CerenkovDetector_HC -> entries();
        }

        // get  CerenkovDetectorPMT Hit Collector pointer
        if (CerenkovDetectorPMT_CollID > -1) {
            CerenkovDetectorPMT_HC = (QweakSimCerenkovDetector_PMTHitsCollection*)(HCE->GetHC(CerenkovDetectorPMT_CollID));
            n_hitCerenkovPMT       = CerenkovDetectorPMT_HC -> entries();
        }
    }

    if (printhits) {
      G4cout <<",\tVDC_Front "<<n_VDChitDCFront<<",\tVDC_Back "<<n_VDChitDCBack<<",\tTS "<<n_hitTriggerScintillator;
      G4cout <<",\tLeadGlass "<<n_hitLeadGlass;
      G4cout <<",\tCerenkov "<<n_hitCerenkov<<"\tCerenkovPMT "<<n_hitCerenkovPMT<<G4endl;
    }

    // Initialize/Clear Event variables, initialize Cerenkov Detector with NoHit Flag
    analysis->fRootEvent->Cerenkov.Detector.Initialize();
    analysis->fRootEvent->Cerenkov.PMT.Initialize();

    //-------------------------------------------------------------------------------
    // Initialize/Clear Event variables in Region 1
    analysis->fRootEvent->Region1.ChamberFront.WirePlane.Initialize();
    analysis->fRootEvent->Region1.ChamberBack.WirePlane.Initialize();
    //-----------------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    // Initialize/Clear Event variables in Region 2
    analysis->fRootEvent->Region2.ChamberFront.WirePlane1.Initialize();
    analysis->fRootEvent->Region2.ChamberFront.WirePlane2.Initialize();
    analysis->fRootEvent->Region2.ChamberFront.WirePlane3.Initialize();
    analysis->fRootEvent->Region2.ChamberFront.WirePlane4.Initialize();
    analysis->fRootEvent->Region2.ChamberFront.WirePlane5.Initialize();
    analysis->fRootEvent->Region2.ChamberFront.WirePlane6.Initialize();

    analysis->fRootEvent->Region2.ChamberBack.WirePlane1.Initialize();
    analysis->fRootEvent->Region2.ChamberBack.WirePlane2.Initialize();
    analysis->fRootEvent->Region2.ChamberBack.WirePlane3.Initialize();
    analysis->fRootEvent->Region2.ChamberBack.WirePlane4.Initialize();
    analysis->fRootEvent->Region2.ChamberBack.WirePlane5.Initialize();
    analysis->fRootEvent->Region2.ChamberBack.WirePlane6.Initialize();

    //-------------------------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------------------------
    // initialize Region 3 wire planes (2: u,v ) with NoHit Flag
    analysis->fRootEvent->Region3.ChamberFront.WirePlaneU.Initialize();
    analysis->fRootEvent->Region3.ChamberFront.WirePlaneV.Initialize();
    //
    analysis->fRootEvent->Region3.ChamberBack.WirePlaneU.Initialize();
    analysis->fRootEvent->Region3.ChamberBack.WirePlaneV.Initialize();

    //
    // initialize DriftCells with NoHit Flag
    analysis->fRootEvent->Region3.ChamberFront.DriftCell.Initialize();
    //
    analysis->fRootEvent->Region3.ChamberBack.DriftCell.Initialize();
    //----------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

    // Initialize/Clear Event variables, initialize TriggerScintillator with NoHit Flag
//    for (int ndet=0;ndet<2;ndet++) {
//	analysis->fRootEvent->TriggerScintillator.Detector[ndet].Initialize();
//    }
    analysis->fRootEvent->TriggerScintillator.Detector.Initialize();
	
    // Initialize LeadGlass //--- with NoHit Flag
    analysis->fRootEvent->LeadGlass.Detector.Initialize();
    //analysis->fRootEvent->LeadGlass.Detector.StoreDetectorHasBeenHit(0);
    //-------------------------------------------------------------------------------------------------

    //#########################################################################################################################
    //#########################################################################################################################
    //
    //                                 ================================================================
    //                                  The Main "Software DAQ Trigger": setting the coincidence level
    //
    //                                  or: what is required for filling the Root ntuple for this event
    //                                 =================================================================
    //
    //##########################################################################################################################
    //##########################################################################################################################
    //
    if ( fTrigger[kTriggerAll] /* Trigger on every event */
            || (fTrigger[kTrigger4Fold] && (n_VDChitWirePlane == 4) && (n_VDChitDCFront > 0) && (n_VDChitDCBack > 0) && (n_hitCerenkov > 0) ) /* 4-fold coincidence */
            || (fTrigger[kTrigger3Fold] && (n_VDChitWirePlane >= 2) && (n_VDChitDCFront > 0) && (n_VDChitDCBack > 0) ) /* 3-fold coincidence */
            || (fTrigger[kTriggerScint] && (n_hitTriggerScintillator > 0) ) /* Qweak trigger on a hit in the trigger scintillator */
            || (fTrigger[kTriggerLeadGlass] && (n_hitLeadGlass >0))         /* a hit in the LeadGlass */
            || (fTrigger[kTriggerCer]   && (n_hitCerenkov > 0) )            /* Triggering on Main Detector */
       ) {

        //========================================
        // Store Primary Information into /Primary
        //========================================

        //-------------------------------------------------------------------------------------------
        G4int    PrimaryEventNumber = myUserInfo->GetPrimaryEventNumber();
        G4int    ReactionType = myUserInfo->GetReactionType();
        G4int    PDGcode = myUserInfo->GetPDGcode();
        G4int    TrackID = myUserInfo->GetTrackID();
        G4double GlobalTime = myUserInfo->GetGlobalTime();
        G4double PrimaryQ2 = myUserInfo->GetPrimaryQ2();
        G4double CrossSection = myUserInfo->GetCrossSection();
        G4double CrossSectionWeight = myUserInfo->GetCrossSectionWeight();
        G4double CrossSectionBornTotal     = myUserInfo->GetCrossSectionBornTotal();
        G4double CrossSectionBornInelastic = myUserInfo->GetCrossSectionBornInelastic();
        G4double CrossSectionBornQE        = myUserInfo->GetCrossSectionBornQE();
        G4double CrossSectionRadTotal      = myUserInfo->GetCrossSectionRadTotal();
        G4double CrossSectionRadElastic    = myUserInfo->GetCrossSectionRadElastic();
        G4double CrossSectionRadQE         = myUserInfo->GetCrossSectionRadQE();
        G4double CrossSectionRadDIS        = myUserInfo->GetCrossSectionRadDIS();
	G4double Asymmetry = myUserInfo->GetAsymmetry();
        G4double OriginVertexPositionX = myUserInfo->GetOriginVertexPositionX();
        G4double OriginVertexPositionY = myUserInfo->GetOriginVertexPositionY();
        G4double OriginVertexPositionZ = myUserInfo->GetOriginVertexPositionZ();
        G4double OriginVertexThetaAngle = myUserInfo->GetOriginVertexThetaAngle();
        G4double OriginVertexPhiAngle = myUserInfo->GetOriginVertexPhiAngle();
        G4double OriginVertexMomentumDirectionX = myUserInfo->GetOriginVertexMomentumDirectionX();
        G4double OriginVertexMomentumDirectionY = myUserInfo->GetOriginVertexMomentumDirectionY();
        G4double OriginVertexMomentumDirectionZ = myUserInfo->GetOriginVertexMomentumDirectionZ();
	G4double PreScatteringKineticEnergy = myUserInfo->GetPreScatteringKineticEnergy();
        G4double OriginVertexKineticEnergy = myUserInfo->GetOriginVertexKineticEnergy();
        G4double OriginVertexTotalEnergy = myUserInfo->GetOriginVertexTotalEnergy();

        G4double BeamEnergy              = myUserInfo->GetBeamEnergy();
        CalculateKinematicVariables();
        G4double OriginVertexKinematicNu = myUserInfo->GetOriginVertexKinematicNu();
        G4double OriginVertexKinematicQ2 = myUserInfo->GetOriginVertexKinematicQ2();
        G4double OriginVertexKinematicX  = myUserInfo->GetOriginVertexKinematicX();
        G4double OriginVertexKinematicW  = myUserInfo->GetOriginVertexKinematicW();
        G4double EffectiveKinematicNu    = myUserInfo->GetEffectiveKinematicNu();
        G4double EffectiveKinematicQ2    = myUserInfo->GetEffectiveKinematicQ2();
        G4double EffectiveKinematicX     = myUserInfo->GetEffectiveKinematicX();
        G4double EffectiveKinematicW     = myUserInfo->GetEffectiveKinematicW();
        //--- Get total deposited energy in the LeadGlass from myUserInfo
        G4double LeadGlassEngDep = myUserInfo->GetLeadGlassEnergyDeposit();

        analysis->fRootEvent->Primary.StoreTrackID((Int_t) TrackID);
        analysis->fRootEvent->Primary.StoreGlobalTime((Float_t) GlobalTime);
        analysis->fRootEvent->Primary.StoreOriginVertexPositionX((Float_t) OriginVertexPositionX);
        analysis->fRootEvent->Primary.StoreOriginVertexPositionY((Float_t) OriginVertexPositionY);
        analysis->fRootEvent->Primary.StoreOriginVertexPositionZ((Float_t) OriginVertexPositionZ);
        analysis->fRootEvent->Primary.StoreOriginVertexMomentumDirectionX((Float_t) OriginVertexMomentumDirectionX);
        analysis->fRootEvent->Primary.StoreOriginVertexMomentumDirectionY((Float_t) OriginVertexMomentumDirectionY);
        analysis->fRootEvent->Primary.StoreOriginVertexMomentumDirectionZ((Float_t) OriginVertexMomentumDirectionZ);
        analysis->fRootEvent->Primary.StoreOriginVertexThetaAngle((Float_t) OriginVertexThetaAngle);
        analysis->fRootEvent->Primary.StoreOriginVertexPhiAngle((Float_t) OriginVertexPhiAngle);
	analysis->fRootEvent->Primary.StorePreScatteringKineticEnergy((Float_t) PreScatteringKineticEnergy);
        analysis->fRootEvent->Primary.StoreOriginVertexKineticEnergy((Float_t) OriginVertexKineticEnergy);
        analysis->fRootEvent->Primary.StoreOriginVertexTotalEnergy((Float_t) OriginVertexTotalEnergy);
        analysis->fRootEvent->Primary.StorePrimaryQ2((Float_t) PrimaryQ2);
        analysis->fRootEvent->Primary.StoreCrossSection((Float_t) CrossSection);
        analysis->fRootEvent->Primary.StoreCrossSectionWeight((Float_t) CrossSectionWeight);
        analysis->fRootEvent->Primary.StoreCrossSectionBornTotal    ((Float_t) CrossSectionBornTotal);
        analysis->fRootEvent->Primary.StoreCrossSectionBornInelastic((Float_t) CrossSectionBornInelastic);
        analysis->fRootEvent->Primary.StoreCrossSectionBornQE       ((Float_t) CrossSectionBornQE);
        analysis->fRootEvent->Primary.StoreCrossSectionRadTotal     ((Float_t) CrossSectionRadTotal);
        analysis->fRootEvent->Primary.StoreCrossSectionRadElastic   ((Float_t) CrossSectionRadElastic);
        analysis->fRootEvent->Primary.StoreCrossSectionRadQE        ((Float_t) CrossSectionRadQE);
        analysis->fRootEvent->Primary.StoreCrossSectionRadDIS       ((Float_t) CrossSectionRadDIS);
	analysis->fRootEvent->Primary.StoreAsymmetry((Float_t) Asymmetry);
        analysis->fRootEvent->Primary.StorePrimaryEventNumber((Int_t) PrimaryEventNumber);
        analysis->fRootEvent->Primary.StoreReactionType((Int_t) ReactionType);
        analysis->fRootEvent->Primary.StorePDGcode((Int_t) PDGcode);
        analysis->fRootEvent->Primary.StoreBeamEnergy((Float_t) BeamEnergy);
        analysis->fRootEvent->Primary.StoreOriginVertexKinematicNu((Float_t) OriginVertexKinematicNu);
        analysis->fRootEvent->Primary.StoreOriginVertexKinematicQ2((Float_t) OriginVertexKinematicQ2);
        analysis->fRootEvent->Primary.StoreOriginVertexKinematicX((Float_t) OriginVertexKinematicX);
        analysis->fRootEvent->Primary.StoreOriginVertexKinematicW((Float_t) OriginVertexKinematicW);
        analysis->fRootEvent->Primary.StoreEffectiveKinematicNu((Float_t) EffectiveKinematicNu);
        analysis->fRootEvent->Primary.StoreEffectiveKinematicQ2((Float_t) EffectiveKinematicQ2);
        analysis->fRootEvent->Primary.StoreEffectiveKinematicX((Float_t) EffectiveKinematicX);
        analysis->fRootEvent->Primary.StoreEffectiveKinematicW((Float_t) EffectiveKinematicW);

	////////
	// store energy loss variables into rootfile
	//  all Elosses are in MeV (see QweakSimSteppingAction.cc)
	analysis->fRootEvent->Primary.StoredEIonIn((Float_t) myUserInfo->GetdEIonIn());
	analysis->fRootEvent->Primary.StoredEIonOut((Float_t) myUserInfo->GetdEIonOut());
	analysis->fRootEvent->Primary.StoredEIonTot((Float_t) myUserInfo->GetdEIonTot());
	analysis->fRootEvent->Primary.StoredEBremIn((Float_t) myUserInfo->GetdEBremIn());
	analysis->fRootEvent->Primary.StoredEBremOut((Float_t) myUserInfo->GetdEBremOut());
	analysis->fRootEvent->Primary.StoredEBremTot((Float_t) myUserInfo->GetdEBremTot());
	analysis->fRootEvent->Primary.StoredEMscIn((Float_t) myUserInfo->GetdEMscIn());
	analysis->fRootEvent->Primary.StoredEMscOut((Float_t) myUserInfo->GetdEMscOut());
	analysis->fRootEvent->Primary.StoredEMscTot((Float_t) myUserInfo->GetdEMscTot());
	analysis->fRootEvent->Primary.StoredETotIn((Float_t) myUserInfo->GetdETotIn());
	analysis->fRootEvent->Primary.StoredETotOut((Float_t) myUserInfo->GetdETotOut());
	analysis->fRootEvent->Primary.StoredETot((Float_t) myUserInfo->GetdETot());
	///////

        //--- Write total deposited energy in the LeadGlass to the rootfile
        analysis->fRootEvent->LeadGlass.Detector.StoreTotalEnergyDeposit((Float_t) LeadGlassEngDep);
        //--- force a reset to LeadGlassEngDep=0.0 to get ready for the next event
        myUserInfo->ResetLeadGlassEnergyDeposit();

        //==========================================================================================

        //===========================================
        // Store Number Of Hits of each Detector
        //===========================================

        // Store Number of Hits for: UPlane DriftCell of Front Chamber
        analysis->fRootEvent->Region3.ChamberFront.DriftCell.StoreUDriftCellNbOfHits(n_VDChitDCFront);

        // Store Number of Hits for: VPlane DriftCell of Front Chamber
        analysis->fRootEvent->Region3.ChamberFront.DriftCell.StoreVDriftCellNbOfHits(n_VDChitDCBack);

        // Store Number of Hits for: Cerenkov Detector
        analysis->fRootEvent->Cerenkov.Detector.StoreDetectorNbOfHits(n_hitCerenkov);
		
        // Store Number of Hits for: LeadGlass Detector
        analysis->fRootEvent->LeadGlass.Detector.StoreDetectorNbOfHits(n_hitLeadGlass);

        //==========================================================================================================


        //========================================
        // Store VDC Hit Information into /Region3
        //========================================

        int VDC_Chamber_Plane_NbOfHits[2][2];
        for (int chamber = 0; chamber < 2; chamber++)
          for (int plane = 0; plane < 2; plane++)
            VDC_Chamber_Plane_NbOfHits[chamber][plane] = 0;

        // loop over wire plane hits
        for (int i1=0;i1<n_VDChitWirePlane;i1++) {

            // get hit pointer for each hit
            QweakSimVDC_WirePlaneHit* aHit = (*VDC_WirePlane_HC)[i1];

            if (print_VDC_WirePlaneHit) aHit->Print();

            // get local position of hit
            localPosition  = aHit->GetLocalPosition();
            rLocalPositionX = (Float_t) localPosition.x() / cm;
            rLocalPositionY = (Float_t) localPosition.y() / cm;
            rLocalPositionZ = (Float_t) localPosition.z() / cm;

            // get world position of hit
            globalPosition  = aHit->GetWorldPosition();
            rGlobalPositionX = (Float_t) globalPosition.x() / cm;
            rGlobalPositionY = (Float_t) globalPosition.y() / cm;
            rGlobalPositionZ = (Float_t) globalPosition.z() / cm;

            // get local Momentum of hit
            localMomentum  = aHit->GetLocalMomentum();
            rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
            rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
            rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;

            // get world Momentum of hit
            globalMomentum  = aHit->GetWorldMomentum();
            rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
            rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
            rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
            rGlobalThetaAngle = (Float_t) globalMomentum.theta() / degree;
            rGlobalPhiAngle   = (Float_t) globalMomentum.phi() / degree - 90.0;

            // get total Energy of hit
            rTotalEnergy     = (Float_t) aHit->GetTotalEnergy() / MeV;

            // get kinetic Energy of hit
            rKineticEnergy     = (Float_t) aHit->GetKineticEnergy() / MeV;


            originVertexPosition  = aHit->GetOriginVertexPosition();
            rOriginVertexPositionX      = (Float_t) originVertexPosition.x() / cm;
            rOriginVertexPositionY      = (Float_t) originVertexPosition.y() / cm;
            rOriginVertexPositionZ      = (Float_t) originVertexPosition.z() / cm;


            originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
            rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
            rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
            rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
            rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
            rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;

            rOriginVertexKineticEnergy = (Float_t) aHit->GetOriginVertexKineticEnergy() / MeV;
            rOriginVertexTotalEnergy   = (Float_t) aHit->GetOriginVertexTotalEnergy() / MeV;

            rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;

            rParticleName = TString(aHit->GetParticleName());
            rParticleType = (Int_t) aHit->GetParticleType();

            //-----------------------------------
            int iVDCID = aHit->GetVDCID();
            QweakSimUserVDC_SingleVDCEvent* single_vdc_event = 0;
            if (iVDCID == 0)
              single_vdc_event = &(analysis->fRootEvent->Region3.ChamberFront);
            if (iVDCID == 1)
              single_vdc_event = &(analysis->fRootEvent->Region3.ChamberBack);

            //-----------------------------------
            if (single_vdc_event == 0) {
                G4cerr << "VDC hit with incorrect chamber ID." << G4endl;
                break;
            }

            //-----------------------------------
            int iWirePlaneID = aHit->GetWirePlaneID();
            QweakSimUserVDC_WirePlaneEvent* wire_plane_event = 0;
            if (iWirePlaneID == 0)
              wire_plane_event = &(single_vdc_event->WirePlaneU);
            if (iWirePlaneID == 1)
              wire_plane_event = &(single_vdc_event->WirePlaneV);

            //-----------------------------------
            if (wire_plane_event == 0) {
                G4cerr << "VDC hit with incorrect plane ID." << G4endl;
                break;
            }

            //-----------------------------------
            VDC_Chamber_Plane_NbOfHits[iVDCID][iWirePlaneID]++;
            wire_plane_event->StoreNbOfHits(VDC_Chamber_Plane_NbOfHits[iVDCID][iWirePlaneID]);

            // mark wire plane as been hit
            wire_plane_event->StoreHasBeenHit(5);

            wire_plane_event->StoreParticleName(rParticleName);
            wire_plane_event->StoreParticleType(rParticleType);

            // store total+kinetic energy of hit
            wire_plane_event->StoreTotalEnergy(rTotalEnergy);
            wire_plane_event->StoreKineticEnergy(rKineticEnergy);

            // store origin vertex info
            wire_plane_event->StoreOriginVertexPositionX(rOriginVertexPositionX);
            wire_plane_event->StoreOriginVertexPositionY(rOriginVertexPositionY);
            wire_plane_event->StoreOriginVertexPositionZ(rOriginVertexPositionZ);

            wire_plane_event->StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
            wire_plane_event->StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
            wire_plane_event->StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
            wire_plane_event->StoreOriginVertexPhiAngle(rOriginVertexPhiAngle);
            wire_plane_event->StoreOriginVertexThetaAngle(rOriginVertexThetaAngle);

            wire_plane_event->StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
            wire_plane_event->StoreOriginVertexTotalEnergy(rOriginVertexKineticEnergy);

            wire_plane_event->StoreGlobalTimeOfHit(rGlobalTime);

            // store wire plane hit position
            wire_plane_event->StoreLocalPositionX(rLocalPositionX);
            wire_plane_event->StoreLocalPositionY(rLocalPositionY);
            wire_plane_event->StoreLocalPositionZ(rLocalPositionZ);

            wire_plane_event->StoreGlobalPositionX(rGlobalPositionX);
            wire_plane_event->StoreGlobalPositionY(rGlobalPositionY);
            wire_plane_event->StoreGlobalPositionZ(rGlobalPositionZ);

            // store wire plane hit momentum
            wire_plane_event->StoreLocalMomentumX(rLocalMomentumX);
            wire_plane_event->StoreLocalMomentumY(rLocalMomentumY);
            wire_plane_event->StoreLocalMomentumZ(rLocalMomentumZ);

            wire_plane_event->StoreGlobalMomentumX(rGlobalMomentumX);
            wire_plane_event->StoreGlobalMomentumY(rGlobalMomentumY);
            wire_plane_event->StoreGlobalMomentumZ(rGlobalMomentumZ);

            // store global track angles Phi and Theta
            wire_plane_event->StoreGlobalPhiAngle(rGlobalPhiAngle);
            wire_plane_event->StoreGlobalThetaAngle(rGlobalThetaAngle);

        }

//=========================================================================================================

        //----------------------------------
        // Hit in Front VDC, Front DriftCells
        //----------------------------------
        if (n_VDChitDCFront) {

            // loop over DriftCell hits
            for (G4int i1 = 0; i1 < n_VDChitDCFront; i1++) {

                QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellFront_HC)[i1];
                if (print_VDC_DriftCellHit) aHit->Print();

            } // end for (G4int i1 = 0; i1 < n_VDChitDCFront; i1++)


            // Extract the DriftCell Config from the 1st DC hit
            QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellFront_HC)[0];


            rDCWidthOnFrame    = (Float_t) aHit->GetDCWidthOnFrame()/mm;
            rDCFullThickness   = (Float_t) aHit->GetDCFullThickness()/mm;
            rDCUPlaneWireAngle = (Float_t) aHit->GetDCUPlaneWireAngle()/degree;
            rDCVPlaneWireAngle = (Float_t) aHit->GetDCVPlaneWireAngle()/degree;

            // Store DriftCell Setup Parameter
            analysis->fRootEvent->Region3.Config.StoreDCWidthOnFrame(rDCWidthOnFrame);
            analysis->fRootEvent->Region3.Config.StoreDCFullThickness(rDCFullThickness);
            analysis->fRootEvent->Region3.Config.StoreDCUPlaneWireAngle(rDCUPlaneWireAngle);
            analysis->fRootEvent->Region3.Config.StoreDCVPlaneWireAngle(rDCVPlaneWireAngle);

        } // end of   if(n_VDChitDCFront)


        //----------------------------------
        // Hit in Front VDC, Back DriftCells
        //----------------------------------
        if (n_VDChitDCBack) {
            // loop over hits
            for (G4int i1=0;i1<n_VDChitDCBack;i1++) {

                QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellBack_HC)[i1];
                if (print_VDC_DriftCellHit) aHit->Print();

            } // end for(int i1=0;i1<n_hitBack;i1++


        } // end of if(n_VDChitDCBack)



        //===============================================================================================================

        //=========================================================
        // Store Cerenkov Detector hits into /Cerenkov
        //=========================================================


        if (n_hitCerenkov >0) {
            // loop over hits
            for (int i1=0;i1<n_hitCerenkov;i1++) {

                QweakSimCerenkov_DetectorHit* aHit = (*CerenkovDetector_HC)[i1];

                octantID = (Int_t) aHit->GetDetectorID() + 1;

                if (print_Cerenkov_DetectorHit) aHit->Print();

                // get local position of hit
                localPosition  = aHit->GetLocalPosition();
                rLocalPositionX = (Float_t) localPosition.x() / cm;
                rLocalPositionY = (Float_t) localPosition.y() / cm;
                rLocalPositionZ = (Float_t) localPosition.z() / cm;

                // get world position of hit
                globalPosition  = aHit->GetWorldPosition();
                rGlobalPositionX = (Float_t) globalPosition.x() / cm;
                rGlobalPositionY = (Float_t) globalPosition.y() / cm;
                rGlobalPositionZ = (Float_t) globalPosition.z() / cm;

                // get local Momentum of hit
                localMomentum  = aHit->GetLocalMomentum();
                rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
                rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
                rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;

                // get world Momentum of hit
                globalMomentum  = aHit->GetWorldMomentum();
                rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
                rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
                rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
                rGlobalThetaAngle = (Float_t) globalMomentum.theta() / degree;
                rGlobalPhiAngle   = (Float_t) globalMomentum.phi() / degree - 90.0;

                localExitPosition = myUserInfo->GetLocalCerenkovExitPosition();
                rLocalExitPositionX = (Float_t) localExitPosition.x() / cm;
                rLocalExitPositionY = (Float_t) localExitPosition.y() / cm;
                rLocalExitPositionZ = (Float_t) localExitPosition.z() / cm;

                originVertexPosition  = aHit->GetOriginVertexPosition();
                rOriginVertexPositionX      = (Float_t) originVertexPosition.x() / cm;
                rOriginVertexPositionY      = (Float_t) originVertexPosition.y() / cm;
                rOriginVertexPositionZ      = (Float_t) originVertexPosition.z() / cm;

                originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
                rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
                rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
                rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
                rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
                rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;

                rOriginVertexKineticEnergy = (Float_t) aHit->GetOriginVertexKineticEnergy() / MeV;
                rOriginVertexTotalEnergy   = (Float_t) aHit->GetOriginVertexTotalEnergy() / MeV;

                rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;

                rParticleName = TString(aHit->GetParticleName());
                rParticleType = (Int_t) aHit->GetParticleType();

                // get total Energy of hit
                rTotalEnergy     = (Float_t) aHit->GetTotalEnergy() / MeV;

                // get kinetic Energy of hit
                rKineticEnergy     = (Float_t) aHit->GetKineticEnergy() / MeV;


                // 	      edgeEvent = myUserInfo->GetEdgeEventDetected();

                //==========================================================
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorID(octantID);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorHasBeenHit(5);
                analysis->fRootEvent->Cerenkov.Detector.StoreParticleName(rParticleName);
                analysis->fRootEvent->Cerenkov.Detector.StoreParticleType(rParticleType);
                analysis->fRootEvent->Cerenkov.Detector.StoreGlobalTimeOfHit(rGlobalTime);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexPositionX(rOriginVertexPositionX);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexPositionY(rOriginVertexPositionY);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexPhiAngle(rOriginVertexPhiAngle);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexThetaAngle(rOriginVertexThetaAngle);

                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                analysis->fRootEvent->Cerenkov.Detector.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalPositionX(rLocalPositionX);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalPositionY(rLocalPositionY);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalPositionZ(rLocalPositionZ);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalExitPositionX(rLocalExitPositionX);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalExitPositionY(rLocalExitPositionY);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorGlobalPositionX(rGlobalPositionX);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorGlobalPositionY(rGlobalPositionY);
                analysis->fRootEvent->Cerenkov.Detector.StoreDetectorGlobalPositionZ(rGlobalPositionZ);

                // store global track angles Phi and Theta
                analysis->fRootEvent->Cerenkov.Detector.StoreGlobalPhiAngle(rGlobalPhiAngle);
                analysis->fRootEvent->Cerenkov.Detector.StoreGlobalThetaAngle(rGlobalThetaAngle);

                // store total+kinetic energy of a hit
                analysis->fRootEvent->Cerenkov.Detector.StoreTotalEnergy(rTotalEnergy);
                analysis->fRootEvent->Cerenkov.Detector.StoreKineticEnergy(rKineticEnergy);

                //-----------------------------------------------------------------------------
//
// Peiqing: comment out the followings for speeding up
//
//                 for (int sec = 0; sec < myUserInfo->GetCerenkovSecondaryParticleCount(); sec++) {
// 
//                     SecondaryParticleOrigin = myUserInfo->GetCerenkovSecondaryParticleOrigin(sec);
//                     rSecondaryPartOriginX = (Float_t) SecondaryParticleOrigin.x()/cm;
//                     rSecondaryPartOriginY = (Float_t) SecondaryParticleOrigin.y()/cm;
//                     rSecondaryPartOriginZ = (Float_t) SecondaryParticleOrigin.z()/cm;
// 
//                     SecondaryParticleMomentum = myUserInfo->GetCerenkovSecondaryParticleMomentum(sec);
//                     rSecondaryPartMomentumX = (Float_t) SecondaryParticleMomentum.x()/MeV;
//                     rSecondaryPartMomentumY = (Float_t) SecondaryParticleMomentum.y()/MeV;
//                     rSecondaryPartMomentumZ = (Float_t) SecondaryParticleMomentum.z()/MeV;
// 
//                     rSecondaryPartEnergy = (Float_t) myUserInfo->GetCerenkovSecondaryParticleEnergy(sec)/MeV;
//                     rSecondaryPartCharge = (Float_t) myUserInfo->GetCerenkovSecondaryParticleCharge(sec);
// 
//                     analysis->fRootEvent->Cerenkov.Detector.AddSecondaryParticleEvent(rSecondaryPartOriginX,
//                             rSecondaryPartOriginY,
//                             rSecondaryPartOriginZ,
//                             rSecondaryPartMomentumX,
//                             rSecondaryPartMomentumY,
//                             rSecondaryPartMomentumZ,
//                             rSecondaryPartEnergy,
//                             rSecondaryPartCharge);
//                 } // end for (int sec = 0; sec < myUserInfo->GetCerenkovSecondaryParticleCount(); sec++)
                //-----------------------------------------------------------------------------

                //--------------------------------------------------------------------------------------------
                // Check if the track passed entirely thru the cerenkov detector without getting stuck
                // or hitting an edge
                if (GetDistance(localPosition,localExitPosition)/cm < 1.15)
                    edgeEvent = 1;
                else
                    edgeEvent = 0;

                analysis->fRootEvent->Cerenkov.Detector.StoreEdgeEventFlag(edgeEvent);

                // G4cout << "Edge Event Flag = " << edgeEvent << G4endl;
                //--------------------------------------------------------------------------------------------


            } // end  for(int i1=0;i1<n_hitCerenkov;i1++)
        } // end    if (n_hitCerenkov >0)


        //=========================================================
        // Store Number of Photoelectrons of Cerenkov Detector hits
        //=========================================================

        if (n_hitCerenkovPMT >0) {
            // loop over hits
            for (int i1=0;i1<n_hitCerenkovPMT;i1++) {

                QweakSimCerenkovDetector_PMTHit* aHit = (*CerenkovDetectorPMT_HC)[i1];
                octantID = (Int_t) aHit->GetDetectorID() + 1;

                //------------------------------------------------------------------------
                if ( (aHit->GetPMTID() == 0) ) { // left PMT
                    //if(aHit->IsHitValid())
                    {
                        pmtHitsLeft =  pmtHitsLeft +1;
                        pmtNPELeft += myUserInfo->GetNumberOfPhotoelectronsS20(aHit->GetPhotonEnergy()*1.0e6);
                        // G4cout<<"pmtNPELeft: "<<pmtNPELeft<<G4endl;
                    }
                }

                if (  (aHit->GetPMTID() == 1)  ) { // right PMT
                    //if(aHit->IsHitValid())
                    {
                        pmtHitsRight =  pmtHitsRight +1;
                        pmtNPERight += myUserInfo->GetNumberOfPhotoelectronsS20(aHit->GetPhotonEnergy()*1.0e6);
                        // G4cout<<"pmtNPERight: "<<pmtNPERight<<G4endl;
                    }
                }
                //------------------------------------------------------------------------

            } // end for(int i1=0;i1<n_hitCerenkovPMT;i1++)
        } //end if (n_hitCerenkovPMT >0)


        //---------------------------------------------
        // store number of hits for left and right PMT
        //---------------------------------------------
        analysis->fRootEvent->Cerenkov.PMT.StorePMTLeftNbOfHits(pmtHitsLeft);
        analysis->fRootEvent->Cerenkov.PMT.StorePMTRightNbOfHits(pmtHitsRight);
        analysis->fRootEvent->Cerenkov.PMT.StorePMTTotalNbOfHits(pmtHitsLeft + pmtHitsRight);
        analysis->fRootEvent->Cerenkov.PMT.StorePMTLeftNbOfPEs(pmtNPELeft);
        analysis->fRootEvent->Cerenkov.PMT.StorePMTRightNbOfPEs(pmtNPERight);
        analysis->fRootEvent->Cerenkov.PMT.StorePMTTotalNbOfPEs(pmtNPELeft + pmtNPERight);


        //==============================================================================

        //==============================
        // Store HDC hits into /Region2
        //==============================

        if (n_HDChitWirePlane > 0) {

            // loop over wire plane hits
            for (int i1=0;i1<n_HDChitWirePlane;i1++) {

                int HDC_Chamber_Plane_NbOfHits[2][6];
                for (int chamber = 0; chamber < 2; chamber++)
                  for (int plane = 0; plane < 6; plane++)
                    HDC_Chamber_Plane_NbOfHits[chamber][plane] = 0;

                // get hit pointer for each hit
                QweakSimHDC_WirePlaneHit* aHit = (*HDC_WirePlane_HC)[i1];

                // get local position of hit
                localPosition  = aHit->GetLocalPosition();
                rLocalPositionX = (Float_t) localPosition.x() / cm;
                rLocalPositionY = (Float_t) localPosition.y() / cm;
                rLocalPositionZ = (Float_t) localPosition.z() / cm;

                // get world position of hit
                globalPosition  = aHit->GetWorldPosition();
                rGlobalPositionX = (Float_t) globalPosition.x() / cm;
                rGlobalPositionY = (Float_t) globalPosition.y() / cm;
                rGlobalPositionZ = (Float_t) globalPosition.z() / cm;

                // get local Momentum of hit
                localMomentum  = aHit->GetLocalMomentum();
                rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
                rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
                rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;

                // get world Momentum of hit
                globalMomentum  = aHit->GetWorldMomentum();
                rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
                rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
                rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
                rGlobalThetaAngle = (Float_t) globalMomentum.theta() / degree;
                rGlobalPhiAngle   = (Float_t) globalMomentum.phi() / degree - 90.0;

                originVertexPosition  = aHit->GetOriginVertexPosition();
                rOriginVertexPositionX      = (Float_t) originVertexPosition.x() / cm;
                rOriginVertexPositionY      = (Float_t) originVertexPosition.y() / cm;
                rOriginVertexPositionZ      = (Float_t) originVertexPosition.z() / cm;


                originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
                rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
                rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
                rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
                rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
                rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;

                rOriginVertexKineticEnergy = (Float_t) aHit->GetOriginVertexKineticEnergy() / MeV;
                rOriginVertexTotalEnergy   = (Float_t) aHit->GetOriginVertexTotalEnergy() / MeV;

                rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;

                // get total Energy of hit
                rTotalEnergy     = (Float_t) aHit->GetTotalEnergy() / MeV;

                // get kinetic Energy of hit
                rKineticEnergy     = (Float_t) aHit->GetKineticEnergy() / MeV;

                //-----------------------------------
                int iHDCID = aHit->GetHDCID();
                QweakSimUserHDC_SingleHDCEvent* single_hdc_event = 0;
                if (iHDCID == 0)
                  single_hdc_event = &(analysis->fRootEvent->Region2.ChamberFront);
                if (iHDCID == 1)
                  single_hdc_event = &(analysis->fRootEvent->Region2.ChamberBack);

                //-----------------------------------
                if (single_hdc_event == 0) {
                    G4cerr << "HDC hit with incorrect chamber ID." << G4endl;
                    break;
                }

                //-----------------------------------
                int iWirePlaneID = aHit->GetWirePlaneID();
                QweakSimUserHDC_WirePlaneEvent* wire_plane_event = 0;
                if (iWirePlaneID == 0)
                  wire_plane_event = &(single_hdc_event->WirePlane1);
                if (iWirePlaneID == 1)
                  wire_plane_event = &(single_hdc_event->WirePlane2);
                if (iWirePlaneID == 2)
                  wire_plane_event = &(single_hdc_event->WirePlane3);
                if (iWirePlaneID == 3)
                  wire_plane_event = &(single_hdc_event->WirePlane4);
                if (iWirePlaneID == 4)
                  wire_plane_event = &(single_hdc_event->WirePlane5);
                if (iWirePlaneID == 5)
                  wire_plane_event = &(single_hdc_event->WirePlane6);

                //-----------------------------------
                if (wire_plane_event == 0) {
                    G4cerr << "HDC hit with incorrect plane ID." << G4endl;
                    break;
                }

                //-----------------------------------
                // store number of hits
                HDC_Chamber_Plane_NbOfHits[iHDCID][iWirePlaneID]++;
                wire_plane_event->StoreNbOfHits(HDC_Chamber_Plane_NbOfHits[iHDCID][iWirePlaneID]);

                // mark wire plane as been hit
                wire_plane_event->StorePlaneHasBeenHit(5);

                // store origin vertex info
                wire_plane_event->StoreOriginVertexPositionX(rOriginVertexPositionX);
                wire_plane_event->StoreOriginVertexPositionY(rOriginVertexPositionY);
                wire_plane_event->StoreOriginVertexPositionZ(rOriginVertexPositionZ);
                wire_plane_event->StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                wire_plane_event->StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                wire_plane_event->StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
                wire_plane_event->StoreOriginVertexPhiAngle( rOriginVertexPhiAngle );
                wire_plane_event->StoreOriginVertexThetaAngle( rOriginVertexThetaAngle );

                wire_plane_event->StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                wire_plane_event->StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                wire_plane_event->StoreGlobalTimeOfHit(rGlobalTime);


                wire_plane_event->StorePlaneLocalPositionX(rLocalPositionX);
                wire_plane_event->StorePlaneLocalPositionY(rLocalPositionY);
                wire_plane_event->StorePlaneLocalPositionZ(rLocalPositionZ);

                wire_plane_event->StorePlaneGlobalPositionX(rGlobalPositionX);
                wire_plane_event->StorePlaneGlobalPositionY(rGlobalPositionY);
                wire_plane_event->StorePlaneGlobalPositionZ(rGlobalPositionZ);

                // store wire plane hit momentum
                wire_plane_event->StorePlaneLocalMomentumX(rLocalMomentumX);
                wire_plane_event->StorePlaneLocalMomentumY(rLocalMomentumY);
                wire_plane_event->StorePlaneLocalMomentumZ(rLocalMomentumZ);

                wire_plane_event->StorePlaneGlobalMomentumX(rGlobalMomentumX);
                wire_plane_event->StorePlaneGlobalMomentumY(rGlobalMomentumY);
                wire_plane_event->StorePlaneGlobalMomentumZ(rGlobalMomentumZ);

                // store global track angles Phi and Theta
                wire_plane_event->StoreGlobalPhiAngle(rGlobalPhiAngle);
                wire_plane_event->StoreGlobalThetaAngle(rGlobalThetaAngle);

                // store total+kinetic energy of hit
                wire_plane_event->StoreTotalEnergy(rTotalEnergy);
                wire_plane_event->StoreKineticEnergy(rKineticEnergy);

                //-----------------------------------

            } // end of  for(int i1=0;i1<n_HDChitWirePlane;i1++){

        } // end of if (n_HDChitWirePlane > 0)


        //===============================================================================================================

        //==============================
        // Store GEM hits into /Region1
        //==============================

/* start GEM comments

        if (n_GEMhitWirePlane > 0) {
            //========================================
            // Store GEM Hit Information into /Region1
            //========================================

            int GEM_ChamberFront_WirePlane_NbOfHits = 0;
            int GEM_ChamberBack_WirePlane_NbOfHits = 0;

            // loop over wire plane hits
            // up to now there should be only one GEM per octant
            for (int i1=0;i1<n_GEMhitWirePlane;i1++) {

                // get hit pointer for each hit
                QweakSimGEM_WirePlaneHit* aHit = (*GEM_WirePlane_HC)[i1];

                // G4cout << G4endl << "###### Printing GEM hit info within QweakSimEventAction::EndOfEventAction() " << G4endl << G4endl;
                if (print_GEM_WirePlaneHit) aHit->Print();

                // get local position of hit
                localPosition  = aHit->GetLocalPosition();
                rLocalPositionX = (Float_t) localPosition.x() / cm;
                rLocalPositionY = (Float_t) localPosition.y() / cm;
                rLocalPositionZ = (Float_t) localPosition.z() / cm;

                // get world position of hit
                globalPosition  = aHit->GetWorldPosition();
                rGlobalPositionX = (Float_t) globalPosition.x() / cm;
                rGlobalPositionY = (Float_t) globalPosition.y() / cm;
                rGlobalPositionZ = (Float_t) globalPosition.z() / cm;

                // get local Momentum of hit
                localMomentum  = aHit->GetLocalMomentum();
                rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
                rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
                rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;

                // get world Momentum of hit
                globalMomentum  = aHit->GetWorldMomentum();
                rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
                rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
                rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
                rGlobalThetaAngle = globalMomentum.theta() / degree;
                rGlobalPhiAngle   = globalMomentum.phi() / degree - 90.0;

                originVertexPosition  = aHit->GetOriginVertexPosition();
                rOriginVertexPositionX      = (Float_t) originVertexPosition.x() / cm;
                rOriginVertexPositionY      = (Float_t) originVertexPosition.y() / cm;
                rOriginVertexPositionZ      = (Float_t) originVertexPosition.z() / cm;

                originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
                rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
                rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
                rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
                rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
                rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;

                rOriginVertexKineticEnergy = (Float_t) aHit->GetOriginVertexKineticEnergy() / MeV;
                rOriginVertexTotalEnergy = (Float_t) aHit->GetOriginVertexTotalEnergy() / MeV;

                rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;

                // get total Energy of hit
                rtotalEnergy     = (Float_t) aHit->GetTotalEnergy() / MeV;

                // get kinetic Energy of hit
                rkineticEnergy     = (Float_t) aHit->GetKineticEnergy() / MeV;

                //-----------------------------------

                if ((aHit->GetGEMID()==0) && (aHit->GetWirePlaneID()==0)) {

                    GEM_ChamberFront_WirePlane_NbOfHits++;
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreNbOfHits(GEM_ChamberFront_WirePlane_NbOfHits++);

                    // mark wire plane as been hit
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneHasBeenHit(5);


                    // store origin vertex info
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPhiAngle( rOriginVertexPhiAngle );
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexThetaAngle( rOriginVertexThetaAngle );
                    //------------------------------------------------------------------------------------------------------------------------------------------

                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);


                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionX(rLocalPositionX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionY(rLocalPositionY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionZ(rLocalPositionZ);

                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionX(rGlobalPositionX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionY(rGlobalPositionY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionZ(rGlobalPositionZ);

                    // store wire plane hit momentum
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumX(rLocalMomentumX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumY(rLocalMomentumY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumZ(rLocalMomentumZ);

                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumX(rGlobalMomentumX);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumY(rGlobalMomentumY);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumZ(rGlobalMomentumZ);

                    // store global track angles Phi and Theta
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreGlobalPhiAngle(rGlobalPhiAngle);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreGlobalThetaAngle(rGlobalThetaAngle);

                    // store total+kinetic energy of hit
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreTotalEnergy(rtotalEnergy);
                    analysis->fRootEvent->Region1.ChamberFront.WirePlane.StoreKineticEnergy(rkineticEnergy);

                } //end of if((aHit->GetGEMID()==0) && (aHit->GetWirePlaneID()==0))


                //-----------------------------------

                if ((aHit->GetGEMID()==1) && (aHit->GetWirePlaneID()==0)) {

                    GEM_ChamberBack_WirePlane_NbOfHits++;
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreNbOfHits(GEM_ChamberBack_WirePlane_NbOfHits++);

                    // mark wire plane as been hit
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneHasBeenHit(5);

                    // store origin vertex info
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPhiAngle( rOriginVertexPhiAngle );
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexThetaAngle( rOriginVertexThetaAngle );

                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);



                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionX(rLocalPositionX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionY(rLocalPositionY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionZ(rLocalPositionZ);

                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionX(rGlobalPositionX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionY(rGlobalPositionY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionZ(rGlobalPositionZ);

                    // store wire plane hit momentum
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumX(rLocalMomentumX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumY(rLocalMomentumY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumZ(rLocalMomentumZ);

                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumX(rGlobalMomentumX);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumY(rGlobalMomentumY);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumZ(rGlobalMomentumZ);

                    // store global track angles Phi and Theta
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreGlobalPhiAngle(rGlobalPhiAngle);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreGlobalThetaAngle(rGlobalThetaAngle);

                    // store total+kinetic energy of hit
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreTotalEnergy(rtotalEnergy);
                    analysis->fRootEvent->Region1.ChamberBack.WirePlane.StoreKineticEnergy(rkineticEnergy);

                } // end of if((aHit->GetGEMID()==1) && (aHit->GetWirePlaneID()==0)) {

                //-----------------------------------


            } // end of  for(int i1=0;i1<n_GEMhitWirePlane;i1++){

        } // end of if ( (n_GEMhitWirePlane == 1)

*/  // end of GEM comments


        //===========================================================

        //===========================================================
        // Store Trigger Scintillator hits into /TriggerScintillator
        //===========================================================

        if (n_hitTriggerScintillator >0) {

            // loop over hits
            for (int i1=0;i1<n_hitTriggerScintillator;i1++) {

                QweakSimTriggerScintillator_DetectorHit* aHit = (*TriggerScintillatorDetector_HC)[i1];

                if (print_TriggerScintillator_DetectorHit) aHit->Print();

                // get local position of hit
                localPosition  = aHit->GetLocalPosition();
                rLocalPositionX = (Float_t) localPosition.x() / cm;
                rLocalPositionY = (Float_t) localPosition.y() / cm;
                rLocalPositionZ = (Float_t) localPosition.z() / cm;

                // get world position of hit
                globalPosition  = aHit->GetWorldPosition();
                rGlobalPositionX = (Float_t) globalPosition.x() / cm;
                rGlobalPositionY = (Float_t) globalPosition.y() / cm;
                rGlobalPositionZ = (Float_t) globalPosition.z() / cm;

                // get local Momentum of hit
                localMomentum  = aHit->GetLocalMomentum();
                rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
                rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
                rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;

                // get world Momentum of hit
                globalMomentum  = aHit->GetWorldMomentum();
                rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
                rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
                rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
                rGlobalThetaAngle = (Float_t) globalMomentum.theta() / degree;
                rGlobalPhiAngle   = (Float_t) globalMomentum.phi() / degree - 90.0;

                originVertexPosition  = aHit->GetOriginVertexPosition();
                rOriginVertexPositionX      = (Float_t) originVertexPosition.x() / cm;
                rOriginVertexPositionY      = (Float_t) originVertexPosition.y() / cm;
                rOriginVertexPositionZ      = (Float_t) originVertexPosition.z() / cm;

                originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
                rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
                rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
                rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
                rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
                rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;

                rOriginVertexKineticEnergy =  (Float_t) aHit->GetOriginVertexKineticEnergy() / MeV;
                rOriginVertexTotalEnergy = (Float_t) aHit->GetOriginVertexTotalEnergy() / MeV;

                rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;


                // 	      edgeEvent = myUserInfo->GetEdgeEventDetected();

//jpan@nuclear.uwinnipeg.ca
                /*
                	// mark TriggerScintillator detector as been hit
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorHasBeenHit(5);

                	// store global time of hit
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreGlobalTimeOfHit(rGlobalTime);

                	// store origin vertex info
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionX(rOriginVertexPositionX);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionY(rOriginVertexPositionY);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionZ(rOriginVertexPositionZ);

                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                	analysis->fRootEvent->TriggerScintillator.Detector[0].StorePrimaryQ2(rPrimaryQ2);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreCrossSectionWeight(rCrossSectionWeight);

                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionX(rLocalPositionX);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionY(rLocalPositionY);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionZ(rLocalPositionZ);

                //         analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionX(rLocalExitPositionX);
                //         analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionY(rLocalExitPositionY);
                //         analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);

                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionX(rGlobalPositionX);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionY(rGlobalPositionY);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionZ(rGlobalPositionZ);

                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalVertexTotalEnergy((Float_t ) aHit->GetTotalEnergy()/MeV);

                	// store global track angles Phi and Theta
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreGlobalPhiAngle(rGlobalPhiAngle);
                	analysis->fRootEvent->TriggerScintillator.Detector[0].StoreGlobalThetaAngle(rGlobalThetaAngle);
                */

                // mark TriggerScintillator detector as been hit
                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorHasBeenHit(5);

                // store global time of hit
                analysis->fRootEvent->TriggerScintillator.Detector.StoreGlobalTimeOfHit(rGlobalTime);

                // store origin vertex info
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexPositionX(rOriginVertexPositionX);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexPositionY(rOriginVertexPositionY);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexPhiAngle( rOriginVertexPhiAngle );
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexThetaAngle( rOriginVertexThetaAngle );

                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);

                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalPositionX(rLocalPositionX);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalPositionY(rLocalPositionY);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalPositionZ(rLocalPositionZ);

//         analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalExitPositionX(rLocalExitPositionX);
//         analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalExitPositionY(rLocalExitPositionY);
//         analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);

                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorGlobalPositionX(rGlobalPositionX);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorGlobalPositionY(rGlobalPositionY);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorGlobalPositionZ(rGlobalPositionZ);

                analysis->fRootEvent->TriggerScintillator.Detector.StoreDetectorLocalVertexTotalEnergy((Float_t ) aHit->GetTotalEnergy()/MeV);

                // store global track angles Phi and Theta
                analysis->fRootEvent->TriggerScintillator.Detector.StoreGlobalPhiAngle(rGlobalPhiAngle);
                analysis->fRootEvent->TriggerScintillator.Detector.StoreGlobalThetaAngle(rGlobalThetaAngle);
                //--------------------------------------------------------------------------------------------

            } // end  for(int i1=0;i1<n_hitTriggerScintillator;i1++)
        } // end    if (n_hitTriggerScintillator >0)


		
		
        //===========================================================
		
        //===========================================================
        // Store LeadGlass hits into /LeadGlass
        //===========================================================
		
        if (n_hitLeadGlass >0) {
			
            //--- loop over hits
            for (int i1=0;i1<n_hitLeadGlass;i1++) {
				
                QweakSimLeadGlass_DetectorHit* aHit = (*LeadGlassDetector_HC)[i1];
				
                //aHit->Print();
				
                //--- primary event number --- Done in previous code
                //G4int PrimaryEventNumber = myUserInfo->GetPrimaryEventNumber();
				
                //--- track ID
                rTrackID = (Float_t) aHit->GetTrackID();
				
                //--- particle name & type
                rParticleName = TString(aHit->GetParticleName());
                rParticleType = (Int_t) aHit->GetParticleType();
				
                //--- get global time of hit
                rGlobalTime = (Float_t) aHit->GetGlobalTime() / ns;
				
                //--- GetHasBeenHit();
                //GetEdgeEventFlag();
                //n_hitLeadGlass <---> GetNbOfHits();
				
                //--- get world position of hit
                globalPosition  = aHit->GetWorldPosition();
                rGlobalPositionX = (Float_t) globalPosition.x() / cm;
                rGlobalPositionY = (Float_t) globalPosition.y() / cm;
                rGlobalPositionZ = (Float_t) globalPosition.z() / cm;
				
                //--- get local position of hit
                localPosition  = aHit->GetLocalPosition();
                rLocalPositionX = (Float_t) localPosition.x() / cm;
                rLocalPositionY = (Float_t) localPosition.y() / cm;
                rLocalPositionZ = (Float_t) localPosition.z() / cm;
				
                //--- get local exit position of hit
                //localExitPosition = aHit->GetLocalExitPosition();
                //rLocalExitPositionX = (Float_t) localExitPosition.x() / cm;
                //rLocalExitPositionY = (Float_t) localExitPosition.y() / cm;
                //rLocalExitPositionZ = (Float_t) localExitPosition.z() / cm;
				
                //--- get origin vertex position
                originVertexPosition  = aHit->GetOriginVertexPosition(); 
                rOriginVertexPositionX = (Float_t) originVertexPosition.x() / cm;
                rOriginVertexPositionY = (Float_t) originVertexPosition.y() / cm;
                rOriginVertexPositionZ = (Float_t) originVertexPosition.z() / cm;
				
                //--- get world momentum of hit
                globalMomentum  = aHit->GetWorldMomentum();
                rGlobalMomentumX = (Float_t) globalMomentum.x() / MeV;
                rGlobalMomentumY = (Float_t) globalMomentum.y() / MeV;
                rGlobalMomentumZ = (Float_t) globalMomentum.z() / MeV;
				
                //--- get local momentum of hit  
                localMomentum  = aHit->GetLocalMomentum();
                rLocalMomentumX = (Float_t) localMomentum.x() / MeV;
                rLocalMomentumY = (Float_t) localMomentum.y() / MeV;
                rLocalMomentumZ = (Float_t) localMomentum.z() / MeV;
				
                //--- get local vertex momentum direction of hit
                localVertexMomentumDirection = aHit->GetMomentumDirection();
                rLocalVertexMomentumDirectionX = (Float_t) localVertexMomentumDirection.x();
                rLocalVertexMomentumDirectionY = (Float_t) localVertexMomentumDirection.y();
                rLocalVertexMomentumDirectionZ = (Float_t) localVertexMomentumDirection.z();
				
                //--- get origin vertex momentum direction of hit
                originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
                rOriginVertexMomentumDirectionX = (Float_t) originVertexMomentumDirection.x();
                rOriginVertexMomentumDirectionY = (Float_t) originVertexMomentumDirection.y();
                rOriginVertexMomentumDirectionZ = (Float_t) originVertexMomentumDirection.z();
				
                //--- get origin vertex theta & phi angle
                rOriginVertexThetaAngle = (Float_t) originVertexMomentumDirection.theta() / degree;
                rOriginVertexPhiAngle   = (Float_t) originVertexMomentumDirection.phi() / degree;
				
                //--- get origin vertex kinetic energy & total energy
                rOriginVertexKineticEnergy = (Float_t ) aHit->GetOriginVertexKineticEnergy() / MeV;
                rOriginVertexTotalEnergy   = (Float_t ) aHit->GetOriginVertexTotalEnergy() / MeV;
				
                //--- get total energy & total energy of hit
                rKineticEnergy = (Float_t) aHit->GetKineticEnergy() / MeV;
                rTotalEnergy = (Float_t) aHit->GetTotalEnergy() / MeV;
				
                //rPrimaryQ2 = (Float_t) aHit->GetPrimaryQ2();
                //rCrossSection = (Float_t) aHit->GetCrossSection();
                //rCrossSectionWeight = (Float_t) aHit->GetCrossSectionWeight();
				
                //--- get global theta & phi angle
                rGlobalThetaAngle = (Float_t) globalMomentum.theta() / degree;
                rGlobalPhiAngle   = (Float_t) globalMomentum.phi() / degree - 90.0;
				
                //--- get LeadGlass deposited energy
                rDepositedEnergy = (Float_t) aHit->GetDepositedEnergy() / MeV;
                //--- TotalDepositedEnergy --- Done in previous code
				
                //--------------------------------------------------------------------------------------------
				
                //--- store Primary Event Number
                analysis->fRootEvent->LeadGlass.Detector.StorePrimaryEventNumber((Int_t) PrimaryEventNumber);
				
                //--- store track ID
                analysis->fRootEvent->LeadGlass.Detector.StoreTrackID(rTrackID);
				
                //--- store particle name & type
                analysis->fRootEvent->LeadGlass.Detector.StoreParticleName(rParticleName);
                analysis->fRootEvent->LeadGlass.Detector.StoreParticleType(rParticleType);
				
                //--- store global time of hit
                analysis->fRootEvent->LeadGlass.Detector.StoreGlobalTimeOfHit(rGlobalTime);
				
                //--- mark LeadGlass detector as been hit
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorHasBeenHit(5);
                //--- edge event flag
                //--- Store Nb of hits  --- Done in previous code
                //analysis->fRootEvent->LeadGlass.Detector.StoreDetectorNbOfHits(n_hitLeadGlass);
				
                //--- store global position
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorGlobalPositionX(rGlobalPositionX);
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorGlobalPositionY(rGlobalPositionY);
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorGlobalPositionZ(rGlobalPositionZ);
				
                //--- store local position
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalPositionX(rLocalPositionX);
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalPositionY(rLocalPositionY);
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalPositionZ(rLocalPositionZ);
				
                //analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalExitPositionX(rLocalExitPositionX);
                //analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalExitPositionY(rLocalExitPositionY);
                //analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);
				
                //--- store origin vertex position
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexPositionX(rOriginVertexPositionX);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexPositionY(rOriginVertexPositionY);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
				
                //--- store local vertex momentum direction
                analysis->fRootEvent->LeadGlass.Detector.StoreLocalVertexMomentumDirectionX(rLocalVertexMomentumDirectionX);
                analysis->fRootEvent->LeadGlass.Detector.StoreLocalVertexMomentumDirectionY(rLocalVertexMomentumDirectionY);
                analysis->fRootEvent->LeadGlass.Detector.StoreLocalVertexMomentumDirectionZ(rLocalVertexMomentumDirectionZ);
				
                //--- store origin vertex momentum direction
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexMomentumDirectionX(rOriginVertexMomentumDirectionX);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexMomentumDirectionY(rOriginVertexMomentumDirectionY);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexMomentumDirectionZ(rOriginVertexMomentumDirectionZ);
				
                //--- store origin theta & phi angle
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexThetaAngle(rOriginVertexThetaAngle);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexPhiAngle(rOriginVertexPhiAngle);
				
                //--- store origin kinetic energy & total energy
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);
                analysis->fRootEvent->LeadGlass.Detector.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);
				
                //--- store local vertex kinetic & total energy
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalVertexKineticEnergy(rKineticEnergy);
                analysis->fRootEvent->LeadGlass.Detector.StoreDetectorLocalVertexTotalEnergy(rTotalEnergy);
				
                //analysis->fRootEvent->LeadGlass.Detector.StorePrimaryQ2(rPrimaryQ2);
                //analysis->fRootEvent->LeadGlass.Detector.StoreCrossSection(rCrossSection);
                //analysis->fRootEvent->LeadGlass.Detector.StoreCrossSectionWeight(rCrossSectionWeight);		
				
                //--- store global track theta & phi angle
                analysis->fRootEvent->LeadGlass.Detector.StoreGlobalThetaAngle(rGlobalThetaAngle);
                analysis->fRootEvent->LeadGlass.Detector.StoreGlobalPhiAngle(rGlobalPhiAngle);
				
                //--- sotre LeadGlass deposited energy
                analysis->fRootEvent->LeadGlass.Detector.StoreDepositedEnergy(rDepositedEnergy);
                //--- TotalDepositedEnergy --- Done in previous code

		//--------------------------------------------------------------------------------------------
				
            } // end  for(int i1=0;i1<n_hitLeadGlass;i1++)
        } // end    if (n_hitLeadGlass >0)
		
		
		

//  G4cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << G4endl;

        // Finally fill our event ntuple
        analysis->FillRootNtuple();

        //jpan@nuclear.uwinnipeg.ca
        //clear vector contents
        analysis->fRootEvent->Region3.Clear();
        analysis->fRootEvent->Region2.Clear();
        analysis->fRootEvent->Region1.Clear();
	
    } //end of if( (n_hitWirePlane == 2)&&(n_hitFront >0)&&(n_hitBack >0)&&(n_hitCerenkov >0) )

    myUserInfo->ResetCerenkovSecondaryParticleInfo();

    // print the Eloss for diagnostics
    if(ELOSS_DEBUG)    myUserInfo->PrintELoss();
    // clear the Eloss variables for even PrimaryEventNumber events only, 
    // after they have been stored in the rootfile
    //
    // odd PrimaryEventNumber events are used to generate physics 
    // up to the scattering vertex Z
    //
    // NOTE:: in QweakSimPrimaryGenerator.cc, the PrimaryEventNumber is increased 
    //   at the end of GeneratePrimaries. GeneratePrimaries is called before EnfOfEventAction.
    //   Therefore, even though, even events are used to generate physics events up to the 
    //   scattering vertex Z in GeneratePrimaries, the permuation is flipped inside this
    //   routine.
    if(myUserInfo->GetPrimaryEventNumber()%2==0){ 
      myUserInfo->ClearELoss();
    }

//=======================================================================
// Save the Ntuple periodically so we have some data in case of a crash

    G4int eventNumber = evt->GetEventID();

//jpan@nuclear.uwinnipeg.ca
// if (eventNumber%25000 == 1) analysis->AutoSaveRootNtuple();

    if (eventNumber%1000 == 1)
        analysis->AutoSaveRootNtuple();

    if(ELOSS_DEBUG)    G4cout << "***** End of analysis for PrimaryEventNumber " << myUserInfo->GetPrimaryEventNumber() << " *****"<<G4endl;

//=======================================================================

} // end of  QweakSimEventAction::EndOfEventAction()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::Initialize() {

    n_GEMhitWirePlane   = 0;
    n_HDChitWirePlane   = 0;
    n_VDChitWirePlane   = 0;
    n_VDChitDCFront     = 0;
    n_VDChitDCBack      = 0;
    n_hitTriggerScintillator = 0;
    n_hitTriggerScintillatorPMT = 0;
    n_hitCerenkov       = 0;
    n_hitCerenkovPMT    = 0;
    n_hitLeadGlass      = 0;
    n_hitLeadGlassPMT   = 0;

    // get local position of hit
    localPosition   = G4ThreeVector(0.,0.,0.);
    rLocalPositionX  = 0.;
    rLocalPositionY  = 0.;
    rLocalPositionZ  = 0.;

    // get world position of hit
    globalPosition   = G4ThreeVector(0.,0.,0.);
    rGlobalPositionX  = 0.;
    rGlobalPositionY  = 0.;
    rGlobalPositionZ  = 0.;


    originVertexPosition   = G4ThreeVector(0.,0.,0.);
    rOriginVertexPositionX  = 0.;
    rOriginVertexPositionY  = 0.;
    rOriginVertexPositionZ  = 0.;


    originVertexMomentumDirection = G4ThreeVector(0.,0.,0.);

    rOriginVertexKineticEnergy = 0.;
    rOriginVertexTotalEnergy = 0.;

    rGlobalThetaAngle = 0.0;
    rGlobalPhiAngle   = 0.0;


    rPrimaryQ2 = 0.;
    rCrossSection = 0.0;
    rCrossSectionWeight = 0.0;
    rAsymmetry = 0.0;
    
    rPrimaryEventNumber = 0;

    rGlobalTime = 0.;
	
    //--- LeadGlass
    rTrackID = 0.;
	
    localVertexMomentumDirection = G4ThreeVector(0.0,0.0,0.0);
    rLocalVertexMomentumDirectionX = 0.0;
    rLocalVertexMomentumDirectionY = 0.0;
    rLocalVertexMomentumDirectionZ = 0.0;
	
    rDepositedEnergy = 0.0;

    rDCWidthOnFrame     = 0.;
    rDCFullThickness    = 0.;
    rDCUPlaneWireAngle  = 0.;
    rDCVPlaneWireAngle  = 0.;

    //----------------------
    /*  pmtHitsLeft.clear();
      pmtHitsLeft.resize(8);

      pmtHitsRight.clear();
      pmtHitsRight.resize(8);

      pmtNPELeft.clear();
      pmtNPELeft.resize(8);

      pmtNPERight.clear();
      pmtNPERight.resize(8);

      for (int n=0;n<8;n++) {
          pmtHitsLeft[n]  = 0;
          pmtHitsRight[n] = 0;
          pmtNPELeft[n]   = 0.0;
          pmtNPERight[n]  = 0.0; }*/

    pmtHitsLeft=0;
    pmtHitsRight=0;
    pmtNPELeft=0;
    pmtNPERight=0;

    //----------------------


    rParticleType = -1;

    rKineticEnergy  = 0.;
    rTotalEnergy  = 0.;

    detectorID = 0;
    octantID   = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimEventAction::GetDistance(G4ThreeVector p1,G4ThreeVector p2) {
    return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+
                (p1.y()-p2.y())*(p1.y()-p2.y())+
                (p1.z()-p2.z())*(p1.z()-p2.z()));
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Calculates and stores the kinematic variables Nu, Q2,
//      x, and W.
// ---------------------------------------------------------
void QweakSimEventAction::CalculateKinematicVariables() 
{
  // Vertex Kinematic variables
  // These variables are only valid for events generated with the standard
  // generator (not the lookup table).
  G4double mp    = 938.2796*MeV;
  G4double E_in  = myUserInfo->GetPreScatteringKineticEnergy();
  G4double E_out = myUserInfo->GetOriginVertexTotalEnergy();
  G4double theta = myUserInfo->GetOriginVertexThetaAngle();

  G4double nu    = E_in - E_out;
  G4double q2    = 4.0*E_in*E_out*sin(theta*degree/2.0)*sin(theta*degree/2.0);
  G4double x     = q2/(2.0*mp*nu);
  G4double w     = sqrt(mp*mp+2.0*mp*nu-q2);

  myUserInfo->StoreOriginVertexKinematicNu(nu);
  myUserInfo->StoreOriginVertexKinematicQ2(q2*0.000001);
  myUserInfo->StoreOriginVertexKinematicX(x);
  myUserInfo->StoreOriginVertexKinematicW(w);

  //G4cout << "==== Vertex Kinematics ====" << G4endl;
  //G4cout << "E_in:         " << E_in  << G4endl;
  //G4cout << "E_out:        " << E_out << G4endl;
  //G4cout << "Theta:        " << theta << G4endl;
  //G4cout << "Nu:           " << nu << G4endl;
  //G4cout << "Q2:           " << q2 << G4endl;
  //G4cout << "X:            " << x << G4endl;
  //G4cout << "W:            " << w << G4endl;

  
  // "Effective" kinematic variables
  //  These kinematic variables are not calculated correctly yet.
  //  Need values for E_out and theta grabbed from just downstream 
  //  of the target, instead of the vertex quantities used below.
  //  They are still valid for any events generated using the 
  //  lookup table.
  E_in  = myUserInfo->GetBeamEnergy();
  E_out = myUserInfo->GetOriginVertexTotalEnergy(); 
  theta = myUserInfo->GetOriginVertexThetaAngle(); 

  nu    = E_in - E_out;
  q2    = 4.0*E_in*E_out*sin(theta*degree/2.0)*sin(theta*degree/2.0);
  x     = q2/(2.0*mp*nu);
  w     = sqrt(mp*mp+2.0*mp*nu-q2);

  myUserInfo->StoreEffectiveKinematicNu(nu);
  myUserInfo->StoreEffectiveKinematicQ2(q2*0.000001);
  myUserInfo->StoreEffectiveKinematicX(x);
  myUserInfo->StoreEffectiveKinematicW(w);

  //G4cout << "==== Effective Kinematics ====" << G4endl;
  //G4cout << "E_in:         " << E_in  << G4endl;
  //G4cout << "E_out:        " << E_out << G4endl;
  //G4cout << "Theta:        " << theta << G4endl;
  //G4cout << "Nu:           " << nu << G4endl;
  //G4cout << "Q2:           " << q2 << G4endl;
  //G4cout << "X:            " << x << G4endl;
  //G4cout << "W:            " << w << G4endl;
  //G4cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
