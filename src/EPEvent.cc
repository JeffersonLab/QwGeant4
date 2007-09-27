#include "EPEvent.hh"

ClassImp(EPEvent)

EPEvent::EPEvent()
{
  numhits    = 0;
  ipart_det  = 0;
  q__2       = 0.0;
  weight_n   = 0.0;
  vertx_o    = 0.0;
  verty_o    = 0.0;
  vertz_o    = 0.0;
  px_o       = 0.0;
  py_o       = 0.0;
  pz_o       = 0.0;
  theta_o    = 0.0;
  phi_o      = 0.0;
  ptot_o     = 0.0;
  en_o       = 0.0;
  beamEnergy = 0.0;
  diffXSec   = 0.0;
  GEP        = 0.0;
  GMP        = 0.0;
  EPFF       = 0.0;
} 

EPEvent::~EPEvent()
{
}

void EPEvent::SetEventData(Int_t hits, Int_t partt, Double_t q2, Double_t xsecw, 
			   Double_t vxorig, Double_t vyorig, Double_t vzorig,
			   Double_t pxorig, Double_t pyorig, Double_t pzorig, 
			   Double_t thorig, Double_t phorig, Double_t ptorig, 
			   Double_t enorig, Double_t beamEng, Double_t diffxsec,
			   Double_t gep, Double_t gmp, Double_t epff)
{

  numhits    = hits;   
  ipart_det  = partt; 
  q__2       = q2;      
  weight_n   = xsecw;  
  vertx_o    = vxorig;   
  verty_o    = vyorig;   
  vertz_o    = vzorig;   
  px_o       = pxorig;      
  py_o       = pyorig;      
  pz_o       = pzorig;      
  theta_o    = thorig;   
  phi_o      = phorig;     
  ptot_o     = ptorig;    
  en_o       = enorig;      
  beamEnergy = beamEng;
  diffXSec   = diffxsec;
  GEP        = gep;
  GMP        = gmp;
  EPFF       = epff;

}
