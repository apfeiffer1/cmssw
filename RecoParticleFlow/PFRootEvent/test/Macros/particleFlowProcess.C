{
// initialize the core of the framework, and load the PFRootEvent 
// library, which contains the ROOT interface

gSystem->Load("libFWCoreFWLite.so");
gSystem->Load("libRecoParticleFlowPFRootEvent.so");
// AutoLibraryLoader::enable();
gSystem->Load("libCintex.so");
ROOT::Cintex::Cintex::Enable();

// create a PFRootEventManager
PFRootEventManager em("particleFlow.opt");

// em.printRecHits_ = true;
if( em.ev_ && em.ev_->isValid() ) {
  int n =  em.ev_->size();
  for(unsigned i=0; i<n; i++) {
    em.processEntry(i);
    // em.print();
  }
  em.write();
  em.ev_->getTFile()->cd();
}
gApplication->Terminate(); 
}
