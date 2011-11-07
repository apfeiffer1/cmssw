#ifndef MacroUtils_h
#define MacroUtils_h

#include<iostream>
#include<vector>
#include <ext/hash_map>

#include "Math/LorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "CondFormats/JetMETObjects/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;
typedef std::vector<LorentzVector> LorentzVectorCollection;



LorentzVector min(const LorentzVector& a, const LorentzVector& b);
double weightVBF(std::string SampleName, double m_gen, double mass);


namespace jet
{
    enum UncertaintyVariations { JES_UP, JES_DOWN, JER };
    void computeVariation(LorentzVectorCollection &jets, LorentzVector &met,  std::vector<LorentzVectorCollection>& jetsVar, LorentzVectorCollection& metsVar, JetResolution* ptResol, JetResolution* etaResol, JetResolution* phiResol, JetCorrectionUncertainty* jecUnc);
}






// CODE FOR DUPLICATE EVENTS CHECKING
namespace __gnu_cxx{
        template<> struct hash< std::string >{
                size_t operator()( const std::string& x ) const{ return hash< const char* >()( x.c_str() );  }
        };
}

class DuplicatesChecker{
   private :
  typedef __gnu_cxx::hash_map<std::string, bool > RunEventHashMap;
      RunEventHashMap map;
   public :
        DuplicatesChecker(){}
        ~DuplicatesChecker(){}
        void Clear(){map.clear();}
        bool isDuplicate(unsigned int Run, unsigned int Lumi, unsigned int Event){
           char tmp[255];sprintf(tmp,"%i_%i_%i",Run,Lumi,Event);
           RunEventHashMap::iterator it = map.find(tmp);
           if(it==map.end()){
              map[tmp] = true;
              return false;
           }
           return true;
        }
        bool isDuplicate(unsigned int Run, unsigned int Lumi, unsigned int Event,unsigned int cat){
	  char tmp[255];sprintf(tmp,"%i_%i_%i_%i",Run,Lumi,Event,cat);
	  RunEventHashMap::iterator it = map.find(tmp);
	  if(it==map.end()){
	    map[tmp] = true;
	    return false;
	  }
	  return true;
        }
};


#endif
