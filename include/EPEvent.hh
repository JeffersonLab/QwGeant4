#ifndef EPEVENT_H
#define EPEVENT_H

#include "Root_include.h"

class EPEvent {

 private:

  Int_t   numhits;
  Int_t   ipart_det;
  Double_t q__2;
  Double_t weight_n;
  Double_t vertx_o;
  Double_t verty_o;
  Double_t vertz_o;
  Double_t px_o;
  Double_t py_o;
  Double_t pz_o;
  Double_t theta_o;
  Double_t phi_o;
  Double_t ptot_o;
  Double_t en_o;      
  Double_t beamEnergy;
  Double_t diffXSec;
  Double_t GEP;
  Double_t GMP;
  Double_t EPFF;

 public:

  EPEvent();
  virtual ~EPEvent();

  void SetEventData(Int_t, Int_t, Double_t, Double_t, Double_t, Double_t, Double_t,
		    Double_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t,
		    Double_t,Double_t,Double_t,Double_t,Double_t);

  Int_t Get_numhits()         { return numhits;}
  Int_t Get_ipart_det()       { return ipart_det;}

  Double_t Get_en_o()         { return en_o;}
  Double_t Get_q__2()         { return q__2;}
  Double_t Get_weight_n()     { return weight_n;}
  Double_t Get_vertx_o()      { return vertx_o;}
  Double_t Get_verty_o()      { return verty_o;}
  Double_t Get_vertz_o()      { return vertz_o;}
  Double_t Get_px_o()         { return px_o;}
  Double_t Get_py_o()         { return py_o;}
  Double_t Get_pz_o()         { return pz_o;}
  Double_t Get_theta_o()      { return theta_o;}
  Double_t Get_phi_o()        { return phi_o;}
  Double_t Get_ptot_o()       { return ptot_o;}
  Double_t Get_beamEnergy()   { return beamEnergy;}
  Double_t Get_diffXSec()     { return diffXSec;}
  Double_t Get_GEP()          { return GEP;}
  Double_t Get_GMP()          { return GMP;}
  Double_t Get_EPFF()         { return EPFF;}

  ClassDef(EPEvent,1)
};

#endif
