#ifndef SinglePATMuonPairProducer_h
#define SinglePATMuonNuPairProducer_h

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <algorithm>
#include <cmath>
#include <iostream>

namespace cmg{

/**
 * A class to select the events from 0 to index in a collection.
 * 
 * If the index is negative, or greater than the number of entries
 * in the collection, we copy all elements.
 * 
 */
template <class T>
class SingleObjectCollectionSelector : public edm::EDProducer {

 public:
  
  typedef std::vector<T> collection;
  typedef std::auto_ptr<collection> event_ptr;
  typedef edm::View<T> view;
  
  explicit SingleObjectCollectionSelector(const edm::ParameterSet& ps):
    src_(ps.getUntrackedParameter<edm::InputTag>("inputCollection")),
    index_(ps.getUntrackedParameter<int>("index",-1)),
    verbose_(ps.getUntrackedParameter<bool>("verbose",false)){
    produces<collection>("");
  }
  void produce(edm::Event& iEvent, const edm::EventSetup&);

 private:

  const edm::InputTag src_;
  const int index_;
  const bool verbose_ ;

};
}

template <class T>
void cmg::SingleObjectCollectionSelector<T>::produce(edm::Event& iEvent, const edm::EventSetup&){
   
    edm::Handle<view> cands;
    iEvent.getByLabel(src_,cands);
    
    if(verbose_){
      std::cout << "The collection " << src_.label() << " has " << cands->size() << " entries." << std::endl;
    }
    typename cmg::SingleObjectCollectionSelector<T>::event_ptr result(new collection());
    if(cands->size()){

        //the index
        unsigned int index = 0;
        if( (index_ < 0) || (static_cast<unsigned int>(index_) > cands->size()) ){
            index = cands->size();
        }else{
            index = static_cast<unsigned int>(index_);
        }
        if(verbose_){
            std::cout << "The selected index was " << index << std::endl;
        }
        for(unsigned int i = 0; i < index; i++){
            result->push_back(cands->at(i));
        }
        if(verbose_){
            std::cout << "Copied " << result->size() << " events" << std::endl;
        }
    }
    iEvent.put(result);
    return;
}


#endif //SinglePATMuonNuPairProducer_h
