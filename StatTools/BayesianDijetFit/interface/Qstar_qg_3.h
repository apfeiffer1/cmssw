/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef __QSTAR_QG_3_H__
#define __QSTAR_QG_3_H__

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
#include <string>
#include "TH1F.h"

//--- Number of mass points = number of signal resonance shapes.
#define N_MASS_POINTS 44
#define MASS_STEPS 100.0
#define N_SHAPE_BINS 1075
#define SHAPE_BINS_MIN 280.0
#define SHAPE_BINS_STEPS 5

class Qstar_qg_3 : public RooAbsPdf {
public:
  Qstar_qg_3() { } ; 
  Qstar_qg_3(const char *name, const char *title,
	     RooAbsReal& _mjj,
	     RooAbsReal& _jes,
	     RooAbsReal& _jer,
	     RooAbsReal& _mass, RooAbsReal& iResonance);
  Qstar_qg_3(const Qstar_qg_3& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new Qstar_qg_3(*this,newname); }
  inline virtual ~Qstar_qg_3() { }


  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
  void generateEvent(Int_t code);

protected:

  RooRealProxy mjj ;
  RooRealProxy jes ;
  RooRealProxy jer ;
  RooRealProxy mass ;

  Double_t evaluate() const ;
  Int_t    findHistFast( double m ) const ;

private:
  
  double interpolate(double mass, Double_t* histarray) const;

  Double_t mass_points[ N_MASS_POINTS ];
  TH1D* hist[ N_MASS_POINTS ];
  TH1D* hist_cdf[ N_MASS_POINTS ];

  double M_CUT;
  double INIT_MASS;


  ClassDef(Qstar_qg_3,1) // Your description goes here...
};
 
#endif
