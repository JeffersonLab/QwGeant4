
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_PMTEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:20 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimUserCerenkov_PMTEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov PMTEvent
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_PMTEvent_h
#define QweakSimUserCerenkov_PMTEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_PMTEvent : public TObject
{

  private:

    Int_t NbOfHits;               ///< Number of hits in this detector

    std::vector<Int_t> PMTHasBeenHit;          ///< Has this PMT been hit? 0 = no, 5 = yes

    std::vector<Int_t> PMTLeftNbOfHits;        ///< Number of hits in left PMTs
    std::vector<Int_t> PMTRightNbOfHits;       ///< Number of hits in right PMTs
    std::vector<Int_t> PMTTotalNbOfHits;       ///< Number of hits in both PMTs

    std::vector<Float_t> PMTLeftNbOfPEs;       ///< Number of photo-electrons in left PMTs
    std::vector<Float_t> PMTRightNbOfPEs;      ///< Number of photo-electrons in right PMTs
    std::vector<Float_t> PMTTotalNbOfPEs;      ///< Number of photo-electrons in both PMTs

  public:

    // Constructor
    QweakSimUserCerenkov_PMTEvent() { Initialize(); };
    // Destructor
    virtual ~QweakSimUserCerenkov_PMTEvent() { };

    // Initialization
    void Initialize();

  public:

    //-----------------
    void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
    Int_t      GetDetectorNbOfHits() const { return NbOfHits;}

    //-----------------
    void StorePMTHasBeenHit(std::vector<Int_t> np)      { PMTHasBeenHit = np; }
    std::vector<Int_t> GetPMTHasBeenHit() const  { return PMTHasBeenHit;}

    //-----------------
    void StorePMTLeftNbOfHits(std::vector<Int_t> npl)    { PMTLeftNbOfHits = npl; }
    std::vector<Int_t> GetPMTLeftNbOfHits() const  {return PMTLeftNbOfHits;}

    void StorePMTRightNbOfHits(std::vector<Int_t> npr)   { PMTRightNbOfHits = npr; }
    std::vector<Int_t> GetPMTRightNbOfHits() const {return PMTRightNbOfHits;}

    void StorePMTTotalNbOfHits(std::vector<Int_t> npt)   { PMTTotalNbOfHits = npt; }
    std::vector<Int_t> GetPMTTotalNbOfHits() const {return PMTTotalNbOfHits;}
    //-----------------
    void StorePMTLeftNbOfPEs(std::vector<Float_t> npl)    { PMTLeftNbOfPEs = npl; }
    std::vector<Float_t> GetPMTLeftNbOfPEs() const  {return PMTLeftNbOfPEs;}

    void StorePMTRightNbOfPEs(std::vector<Float_t> npr)   { PMTRightNbOfPEs = npr; }
    std::vector<Float_t> GetPMTRightNbOfPEs() const {return PMTRightNbOfPEs;}

    void StorePMTTotalNbOfPEs(std::vector<Float_t> npt)   { PMTTotalNbOfPEs = npt; }
    std::vector<Float_t> GetPMTTotalNbOfPEs() const {return PMTTotalNbOfPEs;}


    // define a new Class known to ROOT
    ClassDef(QweakSimUserCerenkov_PMTEvent,2);

};  // end class QweakSimUserCerenkov_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
