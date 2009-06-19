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

  ClassDef(EPEvent,1);
};

#endif
