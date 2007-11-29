//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEventAction.cc

   $Revision: 1.5 $	
   $Date: 2006/05/05 21:37:16 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:37:16 $
//  CVS/RCS Revision: $Revision: 1.5 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "QweakSimEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimEventAction::QweakSimEventAction(QweakSimAnalysis* AN, QweakSimUserInformation* myUI)
{

//---------------------------------------------------------------------------------------------
//! Constructor of QweakSimEventAction
 /*!	
	
 \param  QweakSimAnalysis*          - class containing the Geamt4 hit data structure 
 \param  QweakSimUserInformation*   - class containing user information like Q2 for this event or QE of some PMTs
                                      which is needed for processing/saving hit information 


 */
//---------------------------------------------------------------------------------------------


    GEM_WirePlane_CollID                  = -1;
    HDC_WirePlane_CollID                  = -1;
    VDC_WirePlane_CollID                  = -1;
    VDC_DriftCellFront_CollID             = -1;
    VDC_DriftCellBack_CollID              = -1;
    TriggerScintillatorDetector_CollID    = -1; 
    //TriggerScintillatorPMT_CollID         = -1;
    CerenkovDetector_CollID               = -1; 
    CerenkovDetectorPMT_CollID            = -1;
    
    analysis    = AN;
    myUserInfo  = myUI;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimEventAction::~QweakSimEventAction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::BeginOfEventAction(const G4Event* evt)
{
 

  G4SDManager * SDman = G4SDManager::GetSDMpointer();

  // check for existing GEM_WirePlane Collection ID (if it's -1 it will be assigned)
  if (GEM_WirePlane_CollID==-1) {
      GEM_WirePlane_CollID = SDman->GetCollectionID("GEMWirePlaneSD/GEMWirePlaneCollection");
  }

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

//   // check for existing CerenkovDetectorPMT Collection ID (if it's -1 it will be assigned)
//   if (TriggerScintillatorPMT_CollID==-1) {
//       TriggerScintillatorPMT_CollID = SDman->GetCollectionID("TriggerScintillatorPMTSD/TriggerScintillatorPMTHitCollection");
//   }


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

void QweakSimEventAction::EndOfEventAction(const G4Event* evt)
{

//-----------------------------------------------------------------------------
// I'm playing with the QweakSimTrajectory
// Startup: LXe example
// Goal: sace track or track points into ROOT file
// 
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  
  G4int n_trajectories = 0;

  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  G4cout << "QweakSimEventAction::EndOfEventAction, we have so many trajectories stored :"<< n_trajectories << G4endl;


  // extract the trajectories and draw them
  if (G4VVisManager::GetConcreteInstance()){

      G4cout << "Inside G4VVisManager::GetConcreteInstance()"<< G4endl;

      for (G4int i=0; i<n_trajectories; i++){ 

	  QweakSimTrajectory* trj = (QweakSimTrajectory*) ((*(evt->GetTrajectoryContainer()))[i]);

	  //trj->SetForceNoDrawTrajectory(false);


//           if( trj->GetParticleDefinition() == G4OpticalPhoton ::OpticalPhotonDefinition() ){
//               //trj->SetForceDrawTrajectory(true);
//               trj->SetForceNoDrawTrajectory(true);
//           }
//           else {
//               trj->SetForceNoDrawTrajectory(false);
//	  }
// 

	//  trj->ShowTrajectory(); 
            trj->DrawTrajectory(50);

      }
  }

//-----------------------------------------------------------------------------


  // preset variables for hit collection
  Initialize();

  // Get current Event Number
  G4int event_id = evt->GetEventID();

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();

  // initialize HitsCollection pointers
  QweakSimGEM_WirePlane_HitsCollection*                    GEM_WirePlane_HC                   = 0;
  QweakSimHDC_WirePlane_HitsCollection*                    HDC_WirePlane_HC                   = 0;
  QweakSimVDC_WirePlane_HitsCollection*                    VDC_WirePlane_HC                   = 0;
  QweakSimVDC_DriftCellHitsCollection*                     VDC_DriftCellFront_HC              = 0;
  QweakSimVDC_DriftCellHitsCollection*                     VDC_DriftCellBack_HC               = 0;
  QweakSimTriggerScintillator_DetectorHitsCollection*      TriggerScintillatorDetector_HC     = 0;
  //QweakSimTriggerScintillator_PMTHitsCollection*           TriggerScintillatorPMT_HC          = 0;
  QweakSimCerenkovDetectorHitsCollection*                  CerenkovDetector_HC                = 0;
  QweakSimCerenkovDetector_PMTHitsCollection*              CerenkovDetectorPMT_HC             = 0;

  if(HCE){

    // get  GEM_WirePlane Hit Collector pointer
    GEM_WirePlane_HC       = (QweakSimGEM_WirePlane_HitsCollection*)(HCE->GetHC(GEM_WirePlane_CollID));

        // get  HDC_WirePlane Hit Collector pointer
    HDC_WirePlane_HC       = (QweakSimHDC_WirePlane_HitsCollection*)(HCE->GetHC(HDC_WirePlane_CollID));

    // get  VDC_WirePlane Hit Collector pointer
    VDC_WirePlane_HC       = (QweakSimVDC_WirePlane_HitsCollection*)(HCE->GetHC(VDC_WirePlane_CollID));
    
    // get  VDC_DriftCellFront Hit Collector pointer
    VDC_DriftCellFront_HC  = (QweakSimVDC_DriftCellHitsCollection*)(HCE->GetHC(VDC_DriftCellFront_CollID));
    
    // get  VDC_DriftCellFront Hit Collector pointer
    VDC_DriftCellBack_HC   = (QweakSimVDC_DriftCellHitsCollection*)(HCE->GetHC(VDC_DriftCellBack_CollID));

    // get  TriggerScintillator Hit Collector pointer
    TriggerScintillatorDetector_HC  = (QweakSimTriggerScintillator_DetectorHitsCollection*)(HCE->GetHC(TriggerScintillatorDetector_CollID));

    // get  TriggerScintillatorPMT Hit Collector pointer
    //TriggerScintillatorPMT_HC = (QweakSimTriggerScintillator_PMTHitsCollection*)(HCE->GetHC(TriggerScintillatorPMT_CollID));

    // get  CerenkovDetector Hit Collector pointer
    CerenkovDetector_HC    = (QweakSimCerenkovDetectorHitsCollection*)(HCE->GetHC(CerenkovDetector_CollID));
    
    // get  CerenkovDetectorPMT Hit Collector pointer
    CerenkovDetectorPMT_HC = (QweakSimCerenkovDetector_PMTHitsCollection*)(HCE->GetHC(CerenkovDetectorPMT_CollID));
  }  


  // Get number of entries for this event
  n_GEMhitWirePlane              = GEM_WirePlane_HC               -> entries();
  n_HDChitWirePlane              = HDC_WirePlane_HC               -> entries();
  n_VDChitWirePlane              = VDC_WirePlane_HC               -> entries();
  n_VDChitDCFront                = VDC_DriftCellFront_HC          -> entries();
  n_VDChitDCBack                 = VDC_DriftCellBack_HC           -> entries();
  n_hitTriggerScintillator       = TriggerScintillatorDetector_HC -> entries();
  //n_hitTriggerScintillatorPMT    = TriggerScintillatorPMT_HC      -> entries();
  n_hitCerenkov                  = CerenkovDetector_HC            -> entries();
  n_hitCerenkovPMT               = CerenkovDetectorPMT_HC         -> entries();

  cout << "==============================================================="   << endl;
  cout << "Current event                      = " << event_id                 << endl;
  cout << "Number of hit in the GEMs          = " << n_GEMhitWirePlane        << endl;
  cout << "Number of hit in the HDCs          = " << n_HDChitWirePlane        << endl;
  cout << "Number of hit in the VDCs          = " << n_VDChitWirePlane        << endl;
  cout << "Number of hit in the VDC DC Front  = " << n_VDChitDCFront          << endl;
  cout << "Number of hit in the VDC DC Back   = " << n_VDChitDCBack           << endl;
  cout << "Number of hit in the TS            = " << n_hitTriggerScintillator << endl;
  cout << "Number of hit in the Cerenkov      = " << n_hitCerenkov            << endl;
  cout << "==============================================================="   << endl;


  // Initialize/Clear Event variables, initialize Cerenkov Detector with NoHit Flag 
    for (int noctant=0;noctant<8;noctant++) {
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].Detector.Initialize();  
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.Initialize();  

	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].Detector.StoreDetectorHasBeenHit(0);        
    }

  //------------------------------------------------------------------------------------------------------------------------------------------
  // Initialize/Clear Event variables in Region 1 
  analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.Initialize();
  analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.Initialize();
  //
  // initialize Region 1 readout plane with NoHit Flag
  analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneHasBeenHit(0);        
  analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneHasBeenHit(0);        
  //------------------------------------------------------------------------------------------------------------------------------------------
   
  
  //------------------------------------------------------------------------------------------------------------------------------------------
  // Initialize/Clear Event variables in Region 2 
  analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane2.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane3.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane4.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane5.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane6.Initialize();
  //
  analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane2.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane3.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane4.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane5.Initialize();
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane6.Initialize();
  //
  // initialize Region 2 wire planes (6: xuv x'u'v') with NoHit Flag
  //
  analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneHasBeenHit(0);        
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane2.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane3.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane4.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane5.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane6.StorePlaneHasBeenHit(0);
  //
  analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneHasBeenHit(0);        
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane2.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane3.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane4.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane5.StorePlaneHasBeenHit(0);
  //   analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane6.StorePlaneHasBeenHit(0);
  //------------------------------------------------------------------------------------------------------------------------------------------


  //------------------------------------------------------------------------------------------------------------------------------------------
  // initialize Region 3 wire planes (2: u,v ) with NoHit Flag
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneHasBeenHit(0);        
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneHasBeenHit(0);        
  //
  analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneHasBeenHit(0);        
  analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneHasBeenHit(0);        
  //
  // initialize DriftCells with NoHit Flag
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreUDriftCellHasBeenHit(0);        
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreVDriftCellHasBeenHit(0);        
  //
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreUDriftCellHasBeenHit(0);        
  analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreVDriftCellHasBeenHit(0);        
  //------------------------------------------------------------------------------------------------------------------------------------------

 //------------------------------------------------------------------------------------------------------------------------------------------

  // Initialize/Clear Event variables, initialize TriggerScintillator with NoHit Flag 
    for (int ndet=0;ndet<2;ndet++) {
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[ndet].Initialize();    
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[ndet].StoreDetectorHasBeenHit(0);        
    }

  //------------------------------------------------------------------------------------------------------------------------------------------

  //###########################################################################################################################################################
  //###########################################################################################################################################################
  // 
  //
  //                                 ================================================================
  //                                  The Main "Software DAQ Trigger": setting the coincidence level
  // 
  //                                  or: what is required for filling the Root ntuple for this event
  //                                 =================================================================
  // 
  //###########################################################################################################################################################
  //###########################################################################################################################################################
  // 
  // if ( (n_hitWirePlane == 4)&&(n_hitDCFront >0)&&(n_hitDCBack >0)&&(n_hitCerenkov >0) )       // ask for 4 fold coincidence 
  // if ( (n_VDChitWirePlane >= 2)&&(n_VDChitDCFront >0)&&(n_VDChitDCBack >0) )                           //  ask for 3 fold coincidence 
  if (n_hitCerenkov > 0) 
//     if (n_GEMhitWirePlane > 0)  // Triggering on GEM only

  // if (n_hitTriggerScintillator > 0) // Qweak triggers DAQ on a hit in the trigger scintillator 
    {


    //========================================
    // Store Primary Information into /Primary
    //========================================


    G4PrimaryParticle* primary = evt->GetPrimaryVertex(0)->GetPrimary(0);
    //-------------------------------------------------------------------------------------------

    OriginVertexMomentumDirectionX = primary->GetMomentum().x();
    OriginVertexMomentumDirectionY = primary->GetMomentum().y();
    OriginVertexMomentumDirectionZ = primary->GetMomentum().z();
    
    rOriginVertexMomentumDirectionX = (Float_t) OriginVertexMomentumDirectionX/MeV;
    rOriginVertexMomentumDirectionY = (Float_t) OriginVertexMomentumDirectionY/MeV;
    rOriginVertexMomentumDirectionZ = (Float_t) OriginVertexMomentumDirectionZ/MeV;
    
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexMomentumDirectionX( rOriginVertexMomentumDirectionX );
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexMomentumDirectionY( rOriginVertexMomentumDirectionY );
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexMomentumDirectionZ( rOriginVertexMomentumDirectionZ ); 
    

    //-------------------------------------------------------------------------------------------
    OriginVertexPositionX = evt->GetPrimaryVertex(0)->GetPosition().x();
    OriginVertexPositionY = evt->GetPrimaryVertex(0)->GetPosition().y();
    OriginVertexPositionZ = evt->GetPrimaryVertex(0)->GetPosition().z();
    
    rOriginVertexPositionX = (Float_t) OriginVertexPositionX/mm;
    rOriginVertexPositionY = (Float_t) OriginVertexPositionY/mm;
    rOriginVertexPositionZ = (Float_t) OriginVertexPositionZ/mm;
    
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexPositionX( rOriginVertexPositionX );
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexPositionY( rOriginVertexPositionY );
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexPositionZ( rOriginVertexPositionZ );
    
    //-------------------------------------------------------------------------------------------
    // my phi determination that really works ....
    // (Beware: atan2 returns the arctangent of Y/X in the range -PI to PI) 
    // see also http://root.cern.ch/root/html/TVector2.h
    OriginVertexPhiAngle = (TMath::ATan2(-1.0*rOriginVertexMomentumDirectionY, -1.0*rOriginVertexMomentumDirectionX) )*TMath::RadToDeg()*degree + 90.0*degree; 
    rOriginVertexPhiAngle = OriginVertexPhiAngle/degree; 

    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexPhiAngle( rOriginVertexPhiAngle );
     
    //-------------------------------------------------------------------------------------------     
    OriginVertexThetaAngle = (TMath::ATan2( rOriginVertexMomentumDirectionY, rOriginVertexMomentumDirectionZ) )*TMath::RadToDeg()*degree; 
    rOriginVertexThetaAngle = OriginVertexThetaAngle/degree; 
     
    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexThetaAngle( rOriginVertexThetaAngle );


    //-------------------------------------------------------------------------------------------
    rOriginVertexKineticEnergy = TMath::Sqrt(    rOriginVertexMomentumDirectionX * rOriginVertexMomentumDirectionX 
					       + rOriginVertexMomentumDirectionY * rOriginVertexMomentumDirectionY 
					       + rOriginVertexMomentumDirectionZ * rOriginVertexMomentumDirectionZ );

    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexKineticEnergy( rOriginVertexKineticEnergy ); //MeV
    //-------------------------------------------------------------------------------------------

    OriginVertexParticleMass = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMass();
    rOriginVertexParticleMass = OriginVertexParticleMass/MeV;

    rOriginVertexTotalEnergy = TMath::Sqrt(rOriginVertexKineticEnergy*rOriginVertexKineticEnergy + rOriginVertexParticleMass*rOriginVertexParticleMass );

    analysis->QweakSimG4_RootEvent->Primary.StoreOriginVertexTotalEnergy( rOriginVertexTotalEnergy ); //MeV

    //-------------------------------------------------------------------------------------------
    OriginVertexPDGcode = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetPDGcode();
    rOriginVertexPDGcode = (Int_t) OriginVertexPDGcode;
  
    analysis->QweakSimG4_RootEvent->Primary.StorePDGcode( rOriginVertexPDGcode );
    //-------------------------------------------------------------------------------------------

    G4double primaryQ2          = myUserInfo->GetPrimaryQ2();
    G4double crossSectionWeight = myUserInfo->GetCrossSectionWeight();
    G4int    primaryEventNumber = myUserInfo->GetPrimaryEventNumber();

    analysis->QweakSimG4_RootEvent->Primary.StorePrimaryQ2          ( (Float_t) primaryQ2);  	   
    analysis->QweakSimG4_RootEvent->Primary.StoreCrossSectionWeight ( (Float_t) crossSectionWeight);  	   
    analysis->QweakSimG4_RootEvent->Primary.StorePrimaryEventNumber ( (Int_t)   primaryEventNumber);  	   

    //=====================================================================================================================================================
    
    //===========================================
    // Store Number Of Hits of each Detector
    //===========================================

 
    // Store Number of Hits for: UPlane DriftCell of Front Chamber
    analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreUDriftCellNbOfHits(n_VDChitDCFront);  	   

    // Store Number of Hits for: VPlane DriftCell of Front Chamber
    analysis->QweakSimG4_RootEvent->Region3.ChamberFront.DriftCell.StoreVDriftCellNbOfHits(n_VDChitDCBack);  	               

    // Store Number of Hits for: Cerenkov Detector
    //analysis->QweakSimG4_RootEvent->Cerenkov.Detector.StoreDetectorNbOfHits(n_hitCerenkov);  	   


    //=====================================================================================================================================================


    //========================================
    // Store VDC Hit Information into /Region3
    //========================================


    // loop over wire plane hits 
    for(int i1=0;i1<n_VDChitWirePlane;i1++){
	  
      // get hit pointer for each hit 
      QweakSimVDC_WirePlaneHit* aHit = (*VDC_WirePlane_HC)[i1];
      
      //aHit->Print();
      
      // get local position of hit 
       localPosition  = aHit->GetLocalPosition();
      rLocalPositionX = (Float_t) localPosition.x()/cm;
      rLocalPositionY = (Float_t) localPosition.y()/cm;
      rLocalPositionZ = (Float_t) localPosition.z()/cm;
      
      // get world position of hit 
       globalPosition  = aHit->GetWorldPosition();
      rGlobalPositionX = (Float_t) globalPosition.x()/cm;
      rGlobalPositionY = (Float_t) globalPosition.y()/cm;
      rGlobalPositionZ = (Float_t) globalPosition.z()/cm;
      
      // get local Momentum of hit 
       localMomentum  = aHit->GetLocalMomentum();
      rLocalMomentumX = (Float_t) localMomentum.x()/MeV;
      rLocalMomentumY = (Float_t) localMomentum.y()/MeV;
      rLocalMomentumZ = (Float_t) localMomentum.z()/MeV;
      
      // get world Momentum of hit 
       globalMomentum  = aHit->GetWorldMomentum();
      rGlobalMomentumX = (Float_t) globalMomentum.x()/MeV;
      rGlobalMomentumY = (Float_t) globalMomentum.y()/MeV;
      rGlobalMomentumZ = (Float_t) globalMomentum.z()/MeV;


      // get total Energy of hit 
       totalEnergy     = aHit->GetTotalEnergy();
      rtotalEnergy     = (Float_t) totalEnergy/MeV;

      // get kinetic Energy of hit 
       kineticEnergy     = aHit->GetKineticEnergy();
      rkineticEnergy     = (Float_t) kineticEnergy/MeV;


      originVertexPosition  = aHit->GetOriginVertexPosition();
      rOriginVertexPositionX      = (Float_t) originVertexPosition.x()/cm;
      rOriginVertexPositionY      = (Float_t) originVertexPosition.y()/cm;
      rOriginVertexPositionZ      = (Float_t) originVertexPosition.z()/cm;
	  
	  
      originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
	  
      originVertexKineticEnergy = aHit->GetOriginVertexKineticEnergy();
      rOriginVertexKineticEnergy = (Float_t ) originVertexKineticEnergy/MeV;	  
	  
      primaryQ2  = aHit->GetPrimaryQ2();	
      rPrimaryQ2  = (Float_t) primaryQ2;

      crossSectionWeight = aHit->GetCrossSectionWeight();
      rCrossSectionWeight = (Float_t) crossSectionWeight;

      primaryEventNumber = aHit->GetPrimaryEventNumber();	
      rPrimaryEventNumber = (Int_t) primaryEventNumber;

	  
      globalTime = aHit->GetGlobalTime();
      rGlobalTime = (Float_t) globalTime/ns;

       GlobalThetaAngle = globalMomentum.theta();
      rGlobalThetaAngle = (Float_t) GlobalThetaAngle/degree;

       GlobalPhiAngle   = globalMomentum.phi() -90.0*degree;
      rGlobalPhiAngle   = (Float_t) GlobalPhiAngle/degree;

//       G4cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << G4endl;
//       G4cout <<"  Global Theta Angle =  " << GlobalThetaAngle / degree << G4endl;
//       G4cout <<"  Global Phi   Angle =  " << GlobalPhiAngle   / degree << G4endl;
//       G4cout <<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << G4endl;


       particleName = aHit->GetParticleName();
      rParticleName = TString(particleName);

       particleType = aHit->GetParticleType();
      rParticleType = (Int_t) particleType;

//       G4cout <<" VDC wire Plane was hit by  =  " <<  particleName << G4endl;
//       G4cout <<" VDC wire Plane was hit by  =  " << rParticleName << G4endl;

      //----------------------------------
      // Hit in Front VDC, First WirePlane
      //----------------------------------
      if((aHit->GetVDCID()==0) && (aHit->GetWirePlaneID()==0)) {
	  
	// mark wire plane as been hit
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneHasBeenHit(5);  

        analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreParticleName(rParticleName);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreParticleType(rParticleType);  

	// store total+kinetic energy of hit
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreTotalEnergy(rtotalEnergy);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreKineticEnergy(rkineticEnergy);  

	// store origin vertex info
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     

	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StorePrimaryQ2(rPrimaryQ2);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreCrossSectionWeight(rCrossSectionWeight);
 
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StorePrimaryEventNumber(rPrimaryEventNumber);

	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);

	// store wire plane hit position
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalPositionX(rLocalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalPositionY(rLocalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalPositionZ(rLocalPositionZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalPositionX(rGlobalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalPositionY(rGlobalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalPositionZ(rGlobalPositionZ);  

	// store wire plane hit momentum
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalMomentumX(rLocalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalMomentumY(rLocalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalMomentumX(rGlobalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalMomentumY(rGlobalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalMomentumZ(rGlobalMomentumZ);  

	// store global track angles Phi and Theta 
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalPhiAngle(rGlobalPhiAngle);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreUPlaneGlobalThetaAngle(rGlobalThetaAngle);  
	      
      }
	  
	  
      //----------------------------------
      // Hit in Front VDC, Second WirePlane
      //----------------------------------  
      if((aHit->GetVDCID()==0) && (aHit->GetWirePlaneID()==1)) { // Front VDC, Back Wireplane
	      
	// mark wire plane as been hit	      	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneHasBeenHit(5);  

    	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalPositionX(rLocalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalPositionY(rLocalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalPositionZ(rLocalPositionZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalPositionX(rGlobalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalPositionY(rGlobalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalPositionZ(rGlobalPositionZ);  


	// store wire plane hit momentum
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalMomentumX(rLocalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalMomentumY(rLocalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalMomentumX(rGlobalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalMomentumY(rGlobalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalMomentumZ(rGlobalMomentumZ);  

	// store global track angles Phi and Theta 
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalPhiAngle(rGlobalPhiAngle);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberFront.WirePlane.StoreVPlaneGlobalThetaAngle(rGlobalThetaAngle);  

      }


      //----------------------------------
      // Hit in Back VDC, First WirePlane
      //----------------------------------
      if((aHit->GetVDCID()==1) && (aHit->GetWirePlaneID()==0)) { 
	      
	// mark wire plane as been hit
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneHasBeenHit(5);  

	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreParticleName(rParticleName);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreParticleType(rParticleType);  

	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);

	// store total+kinetic energy of hit
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreTotalEnergy(rtotalEnergy); 
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreKineticEnergy(rkineticEnergy);  

	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StorePrimaryQ2(rPrimaryQ2);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreCrossSectionWeight(rCrossSectionWeight);
	
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StorePrimaryEventNumber(rPrimaryEventNumber);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);
	
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalPositionX(rLocalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalPositionY(rLocalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalPositionZ(rLocalPositionZ);  
	
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalPositionX(rGlobalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalPositionY(rGlobalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalPositionZ(rGlobalPositionZ);  
	
	
	// store wire plane hit momentum
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalMomentumX(rLocalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalMomentumY(rLocalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneLocalMomentumZ(rLocalMomentumZ);  
	
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalMomentumX(rGlobalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalMomentumY(rGlobalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalMomentumZ(rGlobalMomentumZ);  

	// store global track angles Phi and Theta 
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalPhiAngle(rGlobalPhiAngle);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreUPlaneGlobalThetaAngle(rGlobalThetaAngle);  


      }
	  
	  
      //----------------------------------
      // Hit in Back VDC, Second WirePlane
      //----------------------------------
      if((aHit->GetVDCID()==1) && (aHit->GetWirePlaneID()==1)) { 
	  
	  // mark wire plane as been hit
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneHasBeenHit(5);  
	
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalPositionX(rLocalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalPositionY(rLocalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalPositionZ(rLocalPositionZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalPositionX(rGlobalPositionX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalPositionY(rGlobalPositionY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalPositionZ(rGlobalPositionZ);  

	// store wire plane hit momentum
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalMomentumX(rLocalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalMomentumY(rLocalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalMomentumX(rGlobalMomentumX);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalMomentumY(rGlobalMomentumY);
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalMomentumZ(rGlobalMomentumZ);  

	// store global track angles Phi and Theta 
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalPhiAngle(rGlobalPhiAngle);  
	analysis->QweakSimG4_RootEvent->Region3.ChamberBack.WirePlane.StoreVPlaneGlobalThetaAngle(rGlobalThetaAngle);  
      }
	  
    }

//=========================================================================================================

    //----------------------------------
    // Hit in Front VDC, Front DriftCells
    //----------------------------------
    if(n_VDChitDCFront){
	
	// loop over DriftCell hits 
	for(G4int i1=0;i1<n_VDChitDCFront;i1++)
	{
	    
	    QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellFront_HC)[i1];
	    
	    //aHit->Print();
	    
	} // end  for(int i1=0;i1<n_hitDCFront;i1++)
	
	
	// Extract the DriftCell Config from the 1st DC hit
	QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellFront_HC)[0];
	
	
	rDCWidthOnFrame    = (Float_t) aHit->GetDCWidthOnFrame()/mm; 
	rDCFullThickness   = (Float_t) aHit->GetDCFullThickness()/mm; 
	rDCUPlaneWireAngle = (Float_t) aHit->GetDCUPlaneWireAngle()/degree; 
	rDCVPlaneWireAngle = (Float_t) aHit->GetDCVPlaneWireAngle()/degree; 
	
	// Store DriftCell Setup Parameter
	analysis->QweakSimG4_RootEvent->Region3.Config.StoreDCWidthOnFrame(rDCWidthOnFrame);  	   
	analysis->QweakSimG4_RootEvent->Region3.Config.StoreDCFullThickness(rDCFullThickness);  	   
	analysis->QweakSimG4_RootEvent->Region3.Config.StoreDCUPlaneWireAngle(rDCUPlaneWireAngle);  	   
	analysis->QweakSimG4_RootEvent->Region3.Config.StoreDCVPlaneWireAngle(rDCVPlaneWireAngle);  	   

    } // end of   if(n_VDChitDCFront)


    //----------------------------------
    // Hit in Front VDC, Back DriftCells
    //----------------------------------
    if(n_VDChitDCBack){
      // loop over hits 
	for(G4int i1=0;i1<n_VDChitDCBack;i1++)
	{
	    
	  QweakSimVDC_DriftCellHit* aHit = (*VDC_DriftCellBack_HC)[i1];
	  
	  //aHit->Print();
	  
	} // end for(int i1=0;i1<n_hitBack;i1++

	
    } // end of if(n_VDChitDCBack)     



    //===============================================================================================================

    //=========================================================
    // Store Cerenkov Detector hits into /Cerenkov
    //=========================================================


    if (n_hitCerenkov >0){
      // loop over hits 
      for(int i1=0;i1<n_hitCerenkov;i1++){

	QweakSimCerenkov_DetectorHit* aHit = (*CerenkovDetector_HC)[i1];

 	rOctantID = G4IndexToOctantNumber[ (Int_t) aHit->GetDetectorID()];

//         //aHit->Print();
	      
	// get local position of hit 
	localPosition  = aHit->GetLocalPosition();
	rLocalPositionX = (Float_t) localPosition.x()/cm;
	rLocalPositionY = (Float_t) localPosition.y()/cm;
	rLocalPositionZ = (Float_t) localPosition.z()/cm;
	  
	// get world position of hit 
	globalPosition  = aHit->GetWorldPosition();
	rGlobalPositionX = (Float_t) globalPosition.x()/cm;
	rGlobalPositionY = (Float_t) globalPosition.y()/cm;
	rGlobalPositionZ = (Float_t) globalPosition.z()/cm;

	// get local Momentum of hit 
	localMomentum  = aHit->GetLocalMomentum();
	rLocalMomentumX = (Float_t) localMomentum.x()/MeV;
	rLocalMomentumY = (Float_t) localMomentum.y()/MeV;
	rLocalMomentumZ = (Float_t) localMomentum.z()/MeV;
      
	// get world Momentum of hit 
	globalMomentum  = aHit->GetWorldMomentum();
	rGlobalMomentumX = (Float_t) globalMomentum.x()/MeV;
	rGlobalMomentumY = (Float_t) globalMomentum.y()/MeV;
	rGlobalMomentumZ = (Float_t) globalMomentum.z()/MeV;
	      
	localExitPosition = myUserInfo->GetLocalCerenkovExitPosition();
	rLocalExitPositionX = (Float_t) localExitPosition.x()/cm;
	rLocalExitPositionY = (Float_t) localExitPosition.y()/cm;
	rLocalExitPositionZ = (Float_t) localExitPosition.z()/cm;	      
	      
	originVertexPosition  = aHit->GetOriginVertexPosition();
	rOriginVertexPositionX      = (Float_t) originVertexPosition.x()/cm;
	rOriginVertexPositionY      = (Float_t) originVertexPosition.y()/cm;
	rOriginVertexPositionZ      = (Float_t) originVertexPosition.z()/cm;
	      
	originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
	      
	originVertexKineticEnergy =   aHit->GetOriginVertexKineticEnergy();
	rOriginVertexKineticEnergy = (Float_t ) originVertexKineticEnergy/MeV;
	      
	originVertexTotalEnergy =   aHit->GetOriginVertexTotalEnergy();
	rOriginVertexTotalEnergy = (Float_t ) originVertexTotalEnergy/MeV;
	      
	primaryQ2  = aHit->GetPrimaryQ2();	
	rPrimaryQ2  = (Float_t) primaryQ2;

	crossSectionWeight =  aHit->GetCrossSectionWeight();
	rCrossSectionWeight = (Float_t) crossSectionWeight;


	globalTime = aHit->GetGlobalTime();
	rGlobalTime = (Float_t) globalTime/ns;


	 GlobalThetaAngle = globalMomentum.theta();
        rGlobalThetaAngle = (Float_t) GlobalThetaAngle/degree;

	 GlobalPhiAngle   = globalMomentum.phi() -90.0*degree;
	rGlobalPhiAngle   = (Float_t) GlobalPhiAngle/degree;


	 particleName = aHit->GetParticleName();
	rParticleName = TString(particleName);

	 particleType = aHit->GetParticleType();
	rParticleType = (Int_t) particleType;

	// get total Energy of hit 
	 totalEnergy     = aHit->GetTotalEnergy();
	rtotalEnergy     = (Float_t) totalEnergy/MeV;

	// get kinetic Energy of hit 
	 kineticEnergy     = aHit->GetKineticEnergy();
	rkineticEnergy     = (Float_t) kineticEnergy/MeV;


	// 	      edgeEvent = myUserInfo->GetEdgeEventDetected();

	//==========================================================

	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorID(rOctantID);  	   
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorHasBeenHit(5);  	   
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreParticleName(rParticleName);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreParticleType(rParticleType);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreGlobalTimeOfHit(rGlobalTime);  	   
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StorePrimaryQ2(rPrimaryQ2);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreCrossSectionWeight(rCrossSectionWeight);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalPositionX(rLocalPositionX);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalPositionY(rLocalPositionY);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalPositionZ(rLocalPositionZ);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalExitPositionX(rLocalExitPositionX);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalExitPositionY(rLocalExitPositionY);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorGlobalPositionX(rGlobalPositionX);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorGlobalPositionY(rGlobalPositionY);
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorGlobalPositionZ(rGlobalPositionZ);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreDetectorLocalVertexTotalEnergy((Float_t ) aHit->GetTotalEnergy()/MeV);
	     
	     // store global track angles Phi and Theta 
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreGlobalPhiAngle(rGlobalPhiAngle);  
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreGlobalThetaAngle(rGlobalThetaAngle);  
	     
	     // store total+kinetic energy of a hit
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreTotalEnergy(rtotalEnergy); 
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreKineticEnergy(rkineticEnergy);  
	     
	     //-----------------------------------------------------------------------------

	     for(int cp = 0; cp < myUserInfo->GetCerenkovOpticalPhotonCount(); cp ++){
	       analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreCerenkovPhotonEnergy((Double_t)myUserInfo->GetCerenkovPhotonEnergyAtIndex(cp));
	     }

	     for(int sec = 0; sec < myUserInfo->GetCerenkovSecondaryParticleCount(); sec++){
		 
		 SecondaryParticleOrigin = myUserInfo->GetCerenkovSecondaryParticleOrigin(sec);
		 rSecondaryPartOriginX = (Float_t) SecondaryParticleOrigin.x()/cm;
		 rSecondaryPartOriginY = (Float_t) SecondaryParticleOrigin.y()/cm;
		 rSecondaryPartOriginZ = (Float_t) SecondaryParticleOrigin.z()/cm;
		 
		 SecondaryParticleMomentum = myUserInfo->GetCerenkovSecondaryParticleMomentum(sec);
		 rSecondaryPartMomentumX = (Float_t) SecondaryParticleMomentum.x()/MeV;
		 rSecondaryPartMomentumY = (Float_t) SecondaryParticleMomentum.y()/MeV;
		 rSecondaryPartMomentumZ = (Float_t) SecondaryParticleMomentum.z()/MeV;
		 
		 rSecondaryPartEnergy = (Float_t) myUserInfo->GetCerenkovSecondaryParticleEnergy(sec)/MeV;
		 rSecondaryPartCharge = (Float_t) myUserInfo->GetCerenkovSecondaryParticleCharge(sec);
		 
		 analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.AddSecondaryParticleEvent(rSecondaryPartOriginX,
													       rSecondaryPartOriginY,
													       rSecondaryPartOriginZ,
													       rSecondaryPartMomentumX,
													       rSecondaryPartMomentumY,
													       rSecondaryPartMomentumZ,
													       rSecondaryPartEnergy,
													       rSecondaryPartCharge); 
		 
	     } // end for
	     //-----------------------------------------------------------------------------

	     //--------------------------------------------------------------------------------------------
	     // Check if the track passed entirely thru the cerenkov detector without getting stuck
	     // or hitting an edge
	     if(GetDistance(localPosition,localExitPosition)/cm < 1.15)
		 edgeEvent = 1;
	     else
		 edgeEvent = 0;
	     
	     analysis->QweakSimG4_RootEvent->Cerenkov.Octant[rOctantID].Detector.StoreEdgeEventFlag(edgeEvent);
	     // G4cout << "Edge Event Flag = " << edgeEvent << G4endl;
	     //--------------------------------------------------------------------------------------------


      } // end  for(int i1=0;i1<n_hitCerenkov;i1++)
    } // end    if (n_hitCerenkov >0)


    //=========================================================
    // Store Number of Photoelectrons of Cerenkov Detector hits
    //=========================================================

    if (n_hitCerenkov >0)
      {
	// loop over hits 
	for(int i1=0;i1<n_hitCerenkovPMT;i1++)
	  {
	      
	    QweakSimCerenkovDetector_PMTHit* aHit = (*CerenkovDetectorPMT_HC)[i1];

	    rOctantID = G4IndexToOctantNumber[(Int_t) aHit->GetDetectorID()];
	    //rOctantID = G4IndexToOctantNumber[6];
	    

	    //------------------------------------------------------------------------
	    if( (aHit->GetPMTID() == 0) ) // left PMT 
	      {
		pmtHitsLeft[rOctantID] =  pmtHitsLeft[rOctantID] +1;
		if(aHit->IsHitValid()){
		  pmtNPELeft[rOctantID] += myUserInfo->GetNumberOfPhotoelectronsS20(aHit->GetPhotonEnergy()*1.0e6); 
		}
	      }
	      
	    if(  (aHit->GetPMTID() == 1)  ) // right PMT
	      {
		pmtHitsRight[rOctantID] =  pmtHitsRight[rOctantID] +1;
		if(aHit->IsHitValid()){
		  pmtNPERight[rOctantID] += myUserInfo->GetNumberOfPhotoelectronsS20(aHit->GetPhotonEnergy()*1.0e6); 
		}
	      }
	    //------------------------------------------------------------------------


	  } // end for(int i1=0;i1<n_hitCerenkovPMT;i1++)
	  
      } //end if (n_hitCerenkov >0)
      

    //---------------------------------------------
    // store number of hits for left and right PMT
    //---------------------------------------------
    for(int noctant=0; noctant<8; noctant++) 
	{
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTLeftNbOfHits(pmtHitsLeft[noctant]);
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTRightNbOfHits(pmtHitsRight[noctant]);
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTTotalNbOfHits(pmtHitsLeft[noctant] + pmtHitsRight[noctant]);
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTLeftNbOfPEs(pmtNPELeft[noctant]);
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTRightNbOfPEs(pmtNPERight[noctant]);
	analysis->QweakSimG4_RootEvent->Cerenkov.Octant[noctant].PMT.StorePMTTotalNbOfPEs(pmtNPELeft[noctant] + pmtNPERight[noctant]);
    }
    
    //===============================================================================================================

    //==============================
    // Store HDC hits into /Region2
    //==============================

  if (n_HDChitWirePlane > 0)
  {

      // loop over wire plane hits 
      for(int i1=0;i1<n_HDChitWirePlane;i1++){
	  
	  // get hit pointer for each hit 
	  QweakSimHDC_WirePlaneHit* aHit = (*HDC_WirePlane_HC)[i1];

	  G4cout << G4endl << "###### Printing HDC hit info within QweakSimEventAction::EndOfEventAction() " << G4endl << G4endl;
	  aHit->Print();
      
	  // get local position of hit 
	   localPosition  = aHit->GetLocalPosition();
	  rLocalPositionX = (Float_t) localPosition.x()/cm;
	  rLocalPositionY = (Float_t) localPosition.y()/cm;
	  rLocalPositionZ = (Float_t) localPosition.z()/cm;
	  
	  // get world position of hit 
	   globalPosition  = aHit->GetWorldPosition();
	  rGlobalPositionX = (Float_t) globalPosition.x()/cm;
	  rGlobalPositionY = (Float_t) globalPosition.y()/cm;
	  rGlobalPositionZ = (Float_t) globalPosition.z()/cm;
	  
	  // get local Momentum of hit 
	   localMomentum  = aHit->GetLocalMomentum();
	  rLocalMomentumX = (Float_t) localMomentum.x()/MeV;
	  rLocalMomentumY = (Float_t) localMomentum.y()/MeV;
	  rLocalMomentumZ = (Float_t) localMomentum.z()/MeV;
      
	  // get world Momentum of hit 
	   globalMomentum  = aHit->GetWorldMomentum();
	  rGlobalMomentumX = (Float_t) globalMomentum.x()/MeV;
	  rGlobalMomentumY = (Float_t) globalMomentum.y()/MeV;
	  rGlobalMomentumZ = (Float_t) globalMomentum.z()/MeV;
	  
	   originVertexPosition  = aHit->GetOriginVertexPosition();
	  rOriginVertexPositionX      = (Float_t) originVertexPosition.x()/cm;
	  rOriginVertexPositionY      = (Float_t) originVertexPosition.y()/cm;
	  rOriginVertexPositionZ      = (Float_t) originVertexPosition.z()/cm;
	  
	  
	  originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
	  
	   originVertexKineticEnergy = aHit->GetOriginVertexKineticEnergy();
	  rOriginVertexKineticEnergy = (Float_t ) originVertexKineticEnergy/MeV;	  
	  
	   primaryQ2  = aHit->GetPrimaryQ2();	
	  rPrimaryQ2  = (Float_t) primaryQ2;

	   crossSectionWeight = aHit->GetCrossSectionWeight();
	  rCrossSectionWeight = (Float_t) crossSectionWeight;
	  
	   primaryEventNumber = aHit->GetPrimaryEventNumber();	
	  rPrimaryEventNumber = (Int_t) primaryEventNumber;
	  
	  
	   globalTime = aHit->GetGlobalTime();
	  rGlobalTime = (Float_t) globalTime/ns;
	  

	   GlobalThetaAngle = globalMomentum.theta();
	  rGlobalThetaAngle = (Float_t) GlobalThetaAngle/degree;
	  
	   GlobalPhiAngle   = globalMomentum.phi() -90.0*degree;
	  rGlobalPhiAngle   = (Float_t) GlobalPhiAngle/degree;

	  // get total Energy of hit 
	  totalEnergy     = aHit->GetTotalEnergy();
	 rtotalEnergy     = (Float_t) totalEnergy/MeV;

	  // get kinetic Energy of hit 
	  kineticEnergy     = aHit->GetKineticEnergy();
	 rkineticEnergy     = (Float_t) kineticEnergy/MeV;

	  //-----------------------------------
	  
	  if((aHit->GetHDCID()==0) && (aHit->GetWirePlaneID()==0)) { 
	      
	      // mark wire plane as been hit
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneHasBeenHit(5);  
	      
	      
	      // store origin vertex info
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     

	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePrimaryQ2(rPrimaryQ2);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreCrossSectionWeight(rCrossSectionWeight);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePrimaryEventNumber(rPrimaryEventNumber);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreGlobalTimeOfHit(rGlobalTime);
	      
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalPositionX(rLocalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalPositionY(rLocalPositionY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalPositionZ(rLocalPositionZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalPositionX(rGlobalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalPositionY(rGlobalPositionY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalPositionZ(rGlobalPositionZ);  
	      
	      // store wire plane hit momentum
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalMomentumX(rLocalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalMomentumY(rLocalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalMomentumX(rGlobalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalMomentumY(rGlobalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StorePlaneGlobalMomentumZ(rGlobalMomentumZ); 
	       
	      // store global track angles Phi and Theta 
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreGlobalPhiAngle(rGlobalPhiAngle);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreGlobalThetaAngle(rGlobalThetaAngle);  

	      // store total+kinetic energy of hit
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreTotalEnergy(rtotalEnergy);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberFront.WirePlane1.StoreKineticEnergy(rkineticEnergy);  

	  } //end of if((aHit->GetHDCID()==0) && (aHit->GetWirePlaneID()==0))
	  
	  
	  //-----------------------------------
	  
	  if((aHit->GetHDCID()==1) && (aHit->GetWirePlaneID()==0)) { 
	      
	      // mark wire plane as been hit
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneHasBeenHit(5);  
	      
	      // store origin vertex info
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePrimaryQ2(rPrimaryQ2);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreCrossSectionWeight(rCrossSectionWeight);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePrimaryEventNumber(rPrimaryEventNumber);
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreGlobalTimeOfHit(rGlobalTime);
	      
	      
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalPositionX(rLocalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalPositionY(rLocalPositionY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalPositionZ(rLocalPositionZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalPositionX(rGlobalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalPositionY(rGlobalPositionY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalPositionZ(rGlobalPositionZ);  
	      
	      // store wire plane hit momentum
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalMomentumX(rLocalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalMomentumY(rLocalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalMomentumX(rGlobalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalMomentumY(rGlobalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StorePlaneGlobalMomentumZ(rGlobalMomentumZ); 

	      // store global track angles Phi and Theta 
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreGlobalPhiAngle(rGlobalPhiAngle);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreGlobalThetaAngle(rGlobalThetaAngle);

	      // store total+kinetic energy of hit
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreTotalEnergy(rtotalEnergy);  
	      analysis->QweakSimG4_RootEvent->Region2.ChamberBack.WirePlane1.StoreKineticEnergy(rkineticEnergy);  

	  } // end of if((aHit->GetHDCID()==1) && (aHit->GetWirePlaneID()==0)) { 
	  
	  //-----------------------------------
	  
	  
      } // end of  for(int i1=0;i1<n_HDChitWirePlane;i1++){
      
  } // end of if ( (n_HDChitWirePlane == 6)
  

    //===============================================================================================================

    //==============================
    // Store GEM hits into /Region1
    //==============================

  if (n_GEMhitWirePlane > 0)
  {

      // loop over wire plane hits
      // up to now there should be only one GEM per octant
      for(int i1=0;i1<n_GEMhitWirePlane;i1++){
	  
	  // get hit pointer for each hit 
	  QweakSimGEM_WirePlaneHit* aHit = (*GEM_WirePlane_HC)[i1];

	  G4cout << G4endl << "###### Printing GEM hit info within QweakSimEventAction::EndOfEventAction() " << G4endl << G4endl;
	  aHit->Print();
      
	  // get local position of hit 
	   localPosition  = aHit->GetLocalPosition();
	  rLocalPositionX = (Float_t) localPosition.x()/cm;
	  rLocalPositionY = (Float_t) localPosition.y()/cm;
	  rLocalPositionZ = (Float_t) localPosition.z()/cm;
	  
	  // get world position of hit 
	   globalPosition  = aHit->GetWorldPosition();
	  rGlobalPositionX = (Float_t) globalPosition.x()/cm;
	  rGlobalPositionY = (Float_t) globalPosition.y()/cm;
	  rGlobalPositionZ = (Float_t) globalPosition.z()/cm;
	  
	  // get local Momentum of hit 
	   localMomentum  = aHit->GetLocalMomentum();
	  rLocalMomentumX = (Float_t) localMomentum.x()/MeV;
	  rLocalMomentumY = (Float_t) localMomentum.y()/MeV;
	  rLocalMomentumZ = (Float_t) localMomentum.z()/MeV;
      
	  // get world Momentum of hit 
	   globalMomentum  = aHit->GetWorldMomentum();
	  rGlobalMomentumX = (Float_t) globalMomentum.x()/MeV;
	  rGlobalMomentumY = (Float_t) globalMomentum.y()/MeV;
	  rGlobalMomentumZ = (Float_t) globalMomentum.z()/MeV;
	  
	   originVertexPosition  = aHit->GetOriginVertexPosition();
	  rOriginVertexPositionX      = (Float_t) originVertexPosition.x()/cm;
	  rOriginVertexPositionY      = (Float_t) originVertexPosition.y()/cm;
	  rOriginVertexPositionZ      = (Float_t) originVertexPosition.z()/cm;
	  
	  
	  originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
	  
	   originVertexKineticEnergy = aHit->GetOriginVertexKineticEnergy();
	  rOriginVertexKineticEnergy = (Float_t ) originVertexKineticEnergy/MeV;	  
	  
	   primaryQ2  = aHit->GetPrimaryQ2();	
	  rPrimaryQ2  = (Float_t) primaryQ2;

	   crossSectionWeight = aHit->GetCrossSectionWeight();
	  rCrossSectionWeight = (Float_t) crossSectionWeight;
	  
	   primaryEventNumber = aHit->GetPrimaryEventNumber();	
	  rPrimaryEventNumber = (Int_t) primaryEventNumber;
	  
	  
	   globalTime = aHit->GetGlobalTime();
	  rGlobalTime = (Float_t) globalTime/ns;
	  
	   GlobalThetaAngle = globalMomentum.theta();
	  rGlobalThetaAngle = (Float_t) GlobalThetaAngle/degree;

	   GlobalPhiAngle   = globalMomentum.phi() -90.0*degree;
	  rGlobalPhiAngle   = (Float_t) GlobalPhiAngle/degree;

	  // get total Energy of hit 
	  totalEnergy     = aHit->GetTotalEnergy();
	 rtotalEnergy     = (Float_t) totalEnergy/MeV;

	  // get kinetic Energy of hit 
	  kineticEnergy     = aHit->GetKineticEnergy();
	 rkineticEnergy     = (Float_t) kineticEnergy/MeV;

	 //-----------------------------------
	  
	  if((aHit->GetGEMID()==0) && (aHit->GetWirePlaneID()==0)) { 
	      
	      // mark wire plane as been hit
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneHasBeenHit(5);  
	      
	      
	      // store origin vertex info
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);

	      //------------------------------------------------------------------------------------------------------------------------------------------

	      for (int noctant=0;noctant<8;noctant++) {

	      }
	      //------------------------------------------------------------------------------------------------------------------------------------------

	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     

	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePrimaryQ2(rPrimaryQ2);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreCrossSectionWeight(rCrossSectionWeight);
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePrimaryEventNumber(rPrimaryEventNumber);
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);
	      
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionX(rLocalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionY(rLocalPositionY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalPositionZ(rLocalPositionZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionX(rGlobalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionY(rGlobalPositionY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalPositionZ(rGlobalPositionZ);  
	      
	      // store wire plane hit momentum
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumX(rLocalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumY(rLocalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumX(rGlobalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumY(rGlobalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StorePlaneGlobalMomentumZ(rGlobalMomentumZ); 
	      
	      // store global track angles Phi and Theta 
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreGlobalPhiAngle(rGlobalPhiAngle);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreGlobalThetaAngle(rGlobalThetaAngle);

	      // store total+kinetic energy of hit
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreTotalEnergy(rtotalEnergy);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberFront.WirePlane.StoreKineticEnergy(rkineticEnergy);  

	  } //end of if((aHit->GetGEMID()==0) && (aHit->GetWirePlaneID()==0))
	  
	  
	  //-----------------------------------
	  
	  if((aHit->GetGEMID()==1) && (aHit->GetWirePlaneID()==0)) { 
	      
	      // mark wire plane as been hit
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneHasBeenHit(5);  
	      
	      // store origin vertex info
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionX(rOriginVertexPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePrimaryQ2(rPrimaryQ2);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreCrossSectionWeight(rCrossSectionWeight);
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePrimaryEventNumber(rPrimaryEventNumber);
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreGlobalTimeOfHit(rGlobalTime);
	      
	      
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionX(rLocalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionY(rLocalPositionY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalPositionZ(rLocalPositionZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionX(rGlobalPositionX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionY(rGlobalPositionY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalPositionZ(rGlobalPositionZ);  
	      
	      // store wire plane hit momentum
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumX(rLocalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumY(rLocalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneLocalMomentumZ(rLocalMomentumZ);  
	      
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumX(rGlobalMomentumX);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumY(rGlobalMomentumY);
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StorePlaneGlobalMomentumZ(rGlobalMomentumZ); 

	      // store global track angles Phi and Theta 
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreGlobalPhiAngle(rGlobalPhiAngle);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreGlobalThetaAngle(rGlobalThetaAngle);

	      // store total+kinetic energy of hit
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreTotalEnergy(rtotalEnergy);  
	      analysis->QweakSimG4_RootEvent->Region1.ChamberBack.WirePlane.StoreKineticEnergy(rkineticEnergy);  

	  } // end of if((aHit->GetGEMID()==1) && (aHit->GetWirePlaneID()==0)) { 
	  
	  //-----------------------------------
	  
	  
      } // end of  for(int i1=0;i1<n_GEMhitWirePlane;i1++){
      
  } // end of if ( (n_GEMhitWirePlane == 1)


  //===============================================================================================================

  //===========================================================
  // Store Trigger Scintillator hits into /TriggerScintillator
  //===========================================================


  if (n_hitTriggerScintillator >0){
     
      // loop over hits 
      for(int i1=0;i1<n_hitTriggerScintillator;i1++){
	  
	  QweakSimTriggerScintillator_DetectorHit* aHit = (*TriggerScintillatorDetector_HC)[i1];
	  
	  //aHit->Print();
	  
	  // get local position of hit 
	   localPosition  = aHit->GetLocalPosition();
	  rLocalPositionX = (Float_t) localPosition.x()/cm;
	  rLocalPositionY = (Float_t) localPosition.y()/cm;
	  rLocalPositionZ = (Float_t) localPosition.z()/cm;
	  
	  // get world position of hit 
	   globalPosition  = aHit->GetWorldPosition();
	  rGlobalPositionX = (Float_t) globalPosition.x()/cm;
	  rGlobalPositionY = (Float_t) globalPosition.y()/cm;
	  rGlobalPositionZ = (Float_t) globalPosition.z()/cm;
	  
	  // get local Momentum of hit 
	  localMomentum  = aHit->GetLocalMomentum();
	  rLocalMomentumX = (Float_t) localMomentum.x()/MeV;
	  rLocalMomentumY = (Float_t) localMomentum.y()/MeV;
	  rLocalMomentumZ = (Float_t) localMomentum.z()/MeV;
      
	  // get world Momentum of hit 
	  globalMomentum  = aHit->GetWorldMomentum();
	  rGlobalMomentumX = (Float_t) globalMomentum.x()/MeV;
	  rGlobalMomentumY = (Float_t) globalMomentum.y()/MeV;
	  rGlobalMomentumZ = (Float_t) globalMomentum.z()/MeV;



	   originVertexPosition  = aHit->GetOriginVertexPosition();
	  rOriginVertexPositionX      = (Float_t) originVertexPosition.x()/cm;
	  rOriginVertexPositionY      = (Float_t) originVertexPosition.y()/cm;
	  rOriginVertexPositionZ      = (Float_t) originVertexPosition.z()/cm;
	  
	   originVertexMomentumDirection = aHit->GetOriginVertexMomentumDirection();
	  
	   originVertexKineticEnergy =   aHit->GetOriginVertexKineticEnergy();
	  rOriginVertexKineticEnergy = (Float_t ) originVertexKineticEnergy/MeV;
	      
	   originVertexTotalEnergy =   aHit->GetOriginVertexTotalEnergy();
	  rOriginVertexTotalEnergy = (Float_t ) originVertexTotalEnergy/MeV;
	  
	   primaryQ2  = aHit->GetPrimaryQ2();	
	  rPrimaryQ2  = (Float_t) primaryQ2;
	  
	   crossSectionWeight =  aHit->GetCrossSectionWeight();
	  rCrossSectionWeight = (Float_t) crossSectionWeight;

	  
	   globalTime = aHit->GetGlobalTime();
	  rGlobalTime = (Float_t) globalTime/ns;

	   GlobalThetaAngle = globalMomentum.theta();
	  rGlobalThetaAngle = (Float_t) GlobalThetaAngle/degree;

	   GlobalPhiAngle   = globalMomentum.phi() -90.0*degree;
	  rGlobalPhiAngle   = (Float_t) GlobalPhiAngle/degree;


	// 	      edgeEvent = myUserInfo->GetEdgeEventDetected();
	      
	// mark TriggerScintillator detector as been hit
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorHasBeenHit(5);  	   
	      
	// store global time of hit
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreGlobalTimeOfHit(rGlobalTime);  	   
	      
	// store origin vertex info
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionX(rOriginVertexPositionX);  
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionY(rOriginVertexPositionY);		    
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreOriginVertexPositionZ(rOriginVertexPositionZ);
	      
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreOriginVertexKineticEnergy(rOriginVertexKineticEnergy);	     
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreOriginVertexTotalEnergy(rOriginVertexTotalEnergy);
	      
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StorePrimaryQ2(rPrimaryQ2);
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreCrossSectionWeight(rCrossSectionWeight);
	      
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionX(rLocalPositionX);  
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionY(rLocalPositionY);
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalPositionZ(rLocalPositionZ);  
	      
//         analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionX(rLocalExitPositionX);
//         analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionY(rLocalExitPositionY);
//         analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalExitPositionZ(rLocalExitPositionZ);

	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionX(rGlobalPositionX);  
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionY(rGlobalPositionY);
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorGlobalPositionZ(rGlobalPositionZ);  
	  
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreDetectorLocalVertexTotalEnergy((Float_t ) aHit->GetTotalEnergy()/MeV);

	// store global track angles Phi and Theta 
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreGlobalPhiAngle(rGlobalPhiAngle);  
	analysis->QweakSimG4_RootEvent->TriggerScintillator.Detector[0].StoreGlobalThetaAngle(rGlobalThetaAngle);
       //--------------------------------------------------------------------------------------------
	      
      } // end  for(int i1=0;i1<n_hitTriggerScintillator;i1++)
    } // end    if (n_hitTriggerScintillator >0)



  G4cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << G4endl;
      
    // Finally fill our event ntuple
    analysis->Fill_RootNtuple();
      
  } //end of if( (n_hitWirePlane == 2)&&(n_hitFront >0)&&(n_hitBack >0)&&(n_hitCerenkov >0) ) 
  
  myUserInfo->ResetCerenkovSecondaryParticleInfo();



//=======================================================================
// Save the Ntuple periodically so we have some data in case of a crash

  G4int eventNumber = evt->GetEventID();

 if (eventNumber%25000 == 1) analysis->AutoSaveRootNtuple();
//=======================================================================


} // end of  QweakSimEventAction::EndOfEventAction()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimEventAction::Initialize()
{

  n_HDChitWirePlane   = 0;
  n_VDChitWirePlane   = 0;
  n_VDChitDCFront     = 0;
  n_VDChitDCBack      = 0;
  n_hitCerenkov       = 0;
  n_hitCerenkovPMT    = 0;

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
  
   originVertexKineticEnergy = 0.;
  rOriginVertexKineticEnergy = 0.;
  
   originVertexTotalEnergy = 0.;
  rOriginVertexTotalEnergy = 0.;
  
   GlobalThetaAngle = 0.0;
  rGlobalThetaAngle = 0.0;

   GlobalPhiAngle   = 0.0;
  rGlobalPhiAngle   = 0.0;


   primaryQ2 = 0.;
  rPrimaryQ2 = 0.;

   crossSectionWeight = 0.0;
  rCrossSectionWeight = 0.0;

   primaryEventNumber = 0;
  rPrimaryEventNumber = 0;

	  
   globalTime = 0.;
  rGlobalTime = 0.;
	  
  rDCWidthOnFrame     = 0.;
  rDCFullThickness    = 0.;
  rDCUPlaneWireAngle  = 0.;
  rDCVPlaneWireAngle  = 0.;

  //----------------------
  pmtHitsLeft.clear();
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
      pmtNPERight[n]  = 0.0; }
  //----------------------


   particleType = -1;
  rParticleType = -1;

   kineticEnergy  = 0.;
  rkineticEnergy  = 0.;

   totalEnergy  = 0.;
  rtotalEnergy  = 0.;


  // aHit->GetDetectorID() returnes the Geant4 index of the cerenkov MV copy numbers that needs to 
  // be converted in intuitive octant numbers. Octant #1 is at 12o'clock
  // So here I define some sort of lookup table:
  
  G4IndexToOctantNumber[6] = 0; // 12o'clock octant
  G4IndexToOctantNumber[7] = 1; 
  G4IndexToOctantNumber[0] = 2; 
  G4IndexToOctantNumber[1] = 3; 
  G4IndexToOctantNumber[2] = 4; 
  G4IndexToOctantNumber[3] = 5; 
  G4IndexToOctantNumber[4] = 6; 
  G4IndexToOctantNumber[5] = 7; 

   detectorID = 0;
   octantID   = 0;
  rOctantID   = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimEventAction::GetDistance(G4ThreeVector p1,G4ThreeVector p2)
{
  return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+
	      (p1.y()-p2.y())*(p1.y()-p2.y())+
	      (p1.z()-p2.z())*(p1.z()-p2.z()));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimEventAction.cc,v $
//      Revision 1.5  2006/05/05 21:37:16  grimm
//      Records now the kinetic and total energy of all drift chambers
//
//      Revision 1.4  2006/01/06 21:39:30  grimm
//      kineticEnergy and totalEnergy will be filled
//
//      Revision 1.3  2005/12/28 23:05:44  grimm
//      Testing: Extract trajectories collected with QweakSimTrajectory (following LXe example)
//
//      Revision 1.2  2005/12/27 19:08:00  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

