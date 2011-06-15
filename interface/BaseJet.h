#ifndef _AnalysisDataFormats_CMGTools_BaseJet_H_
#define _AnalysisDataFormats_CMGTools_BaseJet_H_

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "AnalysisDataFormats/CMGTools/interface/TriBool.h"
#include "AnalysisDataFormats/CMGTools/interface/UnSet.h"

#include "AnalysisDataFormats/CMGTools/interface/PhysicsObject.h"
#include "AnalysisDataFormats/CMGTools/interface/PatTypes.h"

#include <string>
#include <boost/array.hpp>

namespace cmg {

  //forward def needed
  class BaseJet;

  class BaseJet : public PhysicsObjectWithPtr< pat::JetPtr > {
  public:

    BaseJet(){}
    BaseJet(const value& m):
      PhysicsObjectWithPtr<value>::PhysicsObjectWithPtr(m),
      rawFactor_(1),
      uncOnFourVectorScale_(0.){
        std::fill(btag_.begin(),btag_.end(),UnSet(double));
      }

    virtual ~BaseJet(){}
    /// \return btag discriminator
    double btag(unsigned int index = 0) const{ return index < btag_.size() ? btag_.at(index) : UnSet(double); }
    double btag(const char* s) const;
    
    /// \return a correction factor that can be applied to the jet energy or pT to bring
    /// it back to the uncorrected value
    Float_t rawFactor() const {return rawFactor_;}

    Float_t uncOnFourVectorScale() const {return uncOnFourVectorScale_;}

    friend class BaseJetFactory;

  private:
 
    /// b tagging discriminators
    typedef boost::array<double,6> TagArray;
    typedef boost::array<std::string,TagArray::static_size> TagNameArray;
    TagArray btag_;
    TagNameArray btagNames_;

    /// Correction factor that can be applied to the jet energy or pT
    /// to bring it back to the uncorrected value.
    Float_t rawFactor_;

    /// The uncertainty on the four-vector scale. This can be used to
    /// scale up/down the four-vector according to the scale
    /// uncertainty by multiplying by (1. +/- uncOnFourVectorScale_).
    Float_t uncOnFourVectorScale_;

  };
}

#endif /*JET_H_*/
