#include "CMGTools/H2TauTau/plugins/BaseFlatNtp.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenFilterInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

BaseFlatNtp::BaseFlatNtp(const edm::ParameterSet & iConfig):
  file_(0),
  tree_(0),
  genBoson_(0),
  genBosonL1_(0),
  genBosonL2_(0),
  sampleGenEventType_(0),
  sampleTruthEventType_(0),
  genEventType_(0),
  truthEventType_(0),
  deltaRTruth_(0.2),
  signalWeightHisto_(NULL),
  btagWP_(0.679),
  btagsf(12345),
  corrector_(iConfig.getParameter<std::string>("fileCorrectTo")),
  //corrector2012_(iConfig.getParameter<std::string>("fileCorrectTo")),
  mvaWeights_(iConfig.getParameter<std::string>("mvaWeights")),
  reader_(mvaWeights_.c_str()),
  mvaWeights2012_(iConfig.getParameter<std::string>("mvaWeights2012")),
  reader2012_(mvaWeights2012_.c_str())
{

  //for debugging
  printSelectionPass_ = iConfig.getParameter<int>("printSelectionPass");
  cout<<"printSelectionPass_  : "<<printSelectionPass_<<endl;

  dataPeriodFlag_=iConfig.getParameter<int>("dataPeriodFlag");
  cout<<"dataPeriodFlag_  : "<<dataPeriodFlag_<<endl;

  saveLHENUP_=iConfig.getParameter<int>("saveLHENUP");
  cout<<"saveLHENUP_  : "<<saveLHENUP_<<endl;

  verticesListTag_=iConfig.getParameter<edm::InputTag>("verticesListTag");
  cout<<"verticesListTag_  : "<<verticesListTag_.label()<<endl;

  trigPathsListTag_=iConfig.getParameter<edm::InputTag>("trigPathsListTag");
  cout<<"trigPathsListTag_  : "<<trigPathsListTag_.label()<<endl;

  trigObjsListTag_=iConfig.getParameter<edm::InputTag>("trigObjsListTag");
  cout<<"trigObjsListTag_  : "<<trigObjsListTag_.label()<<endl;

  pupWeightName_=iConfig.getParameter<edm::InputTag>("pupWeightName");
  cout<<"pupWeightName_  : "<<pupWeightName_.label()<<endl;

  pupWeightName_=iConfig.getParameter<edm::InputTag>("pupWeightName");
  cout<<"pupWeightName_  : "<<pupWeightName_.label()<<endl;

  for(long i=0;i<5;i++){
    pupWeightNames_[i]=iConfig.getParameter<edm::InputTag>((TString("pupWeightNames")+(i+1)).Data());
    cout<<"pupWeightNames_  : "<<pupWeightNames_[i].label()<<endl;
  }


  firstRun_=iConfig.getParameter<int>("firstRun");
  cout<<"firstRun_  : "<<firstRun_<<endl;

  lastRun_=iConfig.getParameter<int>("lastRun");
  cout<<"lastRun_  : "<<lastRun_<<endl;

  dataType_=iConfig.getParameter<int>("dataType");  
  cout<<"dataType_  : "<<dataType_<<endl;

  genParticlesTag_        = iConfig.getParameter<edm::InputTag>("genParticlesTag");
  cout<<"genParticlesTag_  : "<<genParticlesTag_.label()<<endl;
  
  sampleGenEventType_     = iConfig.getParameter<int>("sampleGenEventType");
  cout<<"sampleGenEventType  : "<<sampleGenEventType_<<endl;

  sampleTruthEventType_   = iConfig.getParameter<int>("sampleTruthEventType");
  cout<<"sampleTruthEventType : "<<sampleTruthEventType_<<endl;



  ////
  tauPtCut_=iConfig.getParameter<double>("tauPtCut");  
  cout<<"tauPtCut_  : "<<tauPtCut_<<endl;

  tauEtaCut_=iConfig.getParameter<double>("tauEtaCut");  
  cout<<"tauEtaCut_  : "<<tauEtaCut_<<endl;

  muPtCut_=iConfig.getParameter<double>("muPtCut");  
  cout<<"muPtCut_  : "<<muPtCut_<<endl;

  muEtaCut_=iConfig.getParameter<double>("muEtaCut");  
  cout<<"muEtaCut_  : "<<muEtaCut_<<endl;

  metType_ = iConfig.getParameter<int>("metType");
  cout<<"metType_  : "<<metType_<<endl;

  metscale_ = iConfig.getParameter<double>("metscale");
  cout<<"metscale_  : "<<metscale_<<endl;


  mvaMETTag_ = iConfig.getParameter<edm::InputTag>("mvaMETTag");
  cout<<"mvaMETTag_  : "<<mvaMETTag_.label()<<endl;

  mvaMETSigTag_ = iConfig.getParameter<edm::InputTag>("mvaMETSigTag");
  cout<<"mvaMETSigTag_  : "<<mvaMETSigTag_.label()<<endl;


  runSVFit_  =  iConfig.getParameter<int>("runSVFit");
  cout<<" runSVFit_ : "<<runSVFit_<<endl;

  smearSVFitMass0pi0_  =  iConfig.getParameter<double>("smearSVFitMass0pi0");
  cout<<"smearSVFitMass0pi0_ : "<<smearSVFitMass0pi0_<<endl;
  smearVisMass0pi0_  =  iConfig.getParameter<double>("smearVisMass0pi0");
  cout<<"smearVisMass0pi0_ : "<<smearVisMass0pi0_<<endl;

  smearSVFitMass1pi0_  =  iConfig.getParameter<double>("smearSVFitMass1pi0");
  cout<<"smearSVFitMass1pi0_ : "<<smearSVFitMass1pi0_<<endl;
  smearVisMass1pi0_  =  iConfig.getParameter<double>("smearVisMass1pi0");
  cout<<"smearVisMass1pi0_ : "<<smearVisMass1pi0_<<endl;



  //

  diTauTag_               = iConfig.getParameter<edm::InputTag>("diTauTag");
  cout<<"diTauTag_  : "<<diTauTag_.label()<<endl;
    
  muonVetoListTag_      = iConfig.getParameter<edm::InputTag>("muonVetoListTag");
  cout<<"muonVetoListTag : "<<muonVetoListTag_.label()<<endl;

  electronVetoListTag_      = iConfig.getParameter<edm::InputTag>("electronVetoListTag");
  cout<<"electronVetoListTag : "<<electronVetoListTag_.label()<<endl;

  tauVetoListTag_      = iConfig.getParameter<edm::InputTag>("tauVetoListTag");
  cout<<"tauVetoListTag : "<<tauVetoListTag_.label()<<endl;


  pfJetListTag_           = iConfig.getParameter<edm::InputTag>("pfJetListTag");
  cout<<"pfJetListTag_ : "<<pfJetListTag_.label()<<endl;


  pujetidname_  = iConfig.getParameter<std::string>("pujetidname");
  cout<<"pujetidname_ : "<<pujetidname_.c_str()<<endl;
  
  
  //
  recoilCorreciton_ =  iConfig.getParameter<int>("recoilCorrection");
  cout<<"recoilCorreciton_  : "<<recoilCorreciton_<<endl;

  fileZmmData_ = iConfig.getParameter<std::string>("fileZmmData");
  cout<<"fileZmmData_ : "<<fileZmmData_.c_str()<<endl;
  fileZmmMC_ = iConfig.getParameter<std::string>("fileZmmMC");
  cout<<"fileZmmMC_  : "<<fileZmmMC_.c_str()<<endl;

  corrector_.addDataFile( fileZmmData_);
  corrector_.addMCFile( fileZmmMC_);

  recoiliScale_ = iConfig.getParameter<double>("recoiliScale");
  cout<<"recoiliScale_   : "<<recoiliScale_<<endl;
   
  randsigma_              = iConfig.getParameter<double>("randsigma");
  cout<<"randsigma_  : "<<randsigma_<<endl;

  unscaledTauTag_        = iConfig.getParameter<edm::InputTag>("unscaledTauTag");
  cout<<"unscaledTauTag_  : "<<unscaledTauTag_.label()<<endl;

  //read in histogram with signal weights
  signalWeightDir_ = iConfig.getParameter<std::string>("signalWeightDir");
  cout<<"signalWeightDir_  : "<<signalWeightDir_.c_str()<<endl;
  signalWeightMass_ = iConfig.getParameter<std::string>("signalWeightMass");
  cout<<"signalWeightMass_  "<<signalWeightMass_.c_str()<<endl;
  if((int)(signalWeightMass_.compare("0"))!=0 ){//signal reweighting required
    TFile F(TString(signalWeightDir_)+"/weight_ptH_"+signalWeightMass_.c_str()+".root","read");
    TH1F* H=(TH1F*)F.Get(TString("powheg_weight/weight_hqt_fehipro_fit_")+signalWeightMass_.c_str());
    gROOT->cd();
    if(!H){
      cout<<"signalWeight requested but histogram not found in "<<F.GetName()<<endl;
      exit(0);
    }
    signalWeightHisto_=(TH1F*)H->Clone("signalWeightHisto");
  }

  cout<<"Trigger paths: "<<endl;
  for(long p=1;p<=10;p++){
    edm::InputTag path=iConfig.getParameter<edm::InputTag>((const char*)(TString("trigPath")+p));
    if(path.label()!=""){
      cout<<path.label()<<" "<<path.instance()<<" "<<path.process()<<endl;
      trigPaths_.push_back(new edm::InputTag(path));
    }
  }
  for(long p=1;p<=10;p++){
    edm::InputTag pathTest=iConfig.getParameter<edm::InputTag>((const char*)(TString("trigPathTest")+p));
    if(pathTest.label()!=""){
      cout<<pathTest.label()<<" "<<pathTest.instance()<<" "<<pathTest.process()<<endl;
      trigPathsTest_.push_back(new edm::InputTag(pathTest));
    }
  }



}

BaseFlatNtp::~BaseFlatNtp(){

  delete signalWeightHisto_;
  delete file_;
  for(std::vector<edm::InputTag *>::const_iterator path=trigPaths_.begin(); path!=trigPaths_.end(); path++){
    delete *path;
  }

}

void BaseFlatNtp::beginJob(){

  file_ = new edm::Service<TFileService>();
  //tree_->Branch("",&,"/I");

  tree_ = (*file_)->make<TTree>("tree","tree");

  tree_->Branch("pupWeight",&pupWeight_,"pupWeight/F");
  tree_->Branch("eventweight",&eventweight_,"eventweight/F");
  tree_->Branch("triggerEffWeight",&triggerEffWeight_,"triggerEffWeight/F"); 
  tree_->Branch("triggerEffWeightMu",&triggerEffWeightMu_,"triggerEffWeightMu/F"); 
  tree_->Branch("triggerEffWeightTau",&triggerEffWeightTau_,"triggerEffWeightTau/F"); 
  tree_->Branch("selectionEffWeight",&selectionEffWeight_,"selectionEffWeight/F"); 
  tree_->Branch("selectionEffWeightId",&selectionEffWeightId_,"selectionEffWeightId/F"); 
  tree_->Branch("selectionEffWeightIso",&selectionEffWeightIso_,"selectionEffWeightIso/F"); 
  tree_->Branch("embeddedGenWeight",&embeddedGenWeight_,"embeddedGenWeight/F"); 
  tree_->Branch("btagEffWeight",&btagEffWeight_,"btagEffWeight/F");
  tree_->Branch("signalWeight",&signalWeight_,"signalWeight/F");


  tree_->Branch("pupWeights1",&pupWeights_[0],"pupWeights1/F");
  tree_->Branch("pupWeights2",&pupWeights_[1],"pupWeights2/F");
  tree_->Branch("pupWeights3",&pupWeights_[2],"pupWeights3/F");
  tree_->Branch("pupWeights4",&pupWeights_[3],"pupWeights4/F");
  tree_->Branch("pupWeights5",&pupWeights_[4],"pupWeights5/F");

  tree_->Branch("triggerEffWeightsMu1",&triggerEffWeightsMu_[0],"triggerEffWeightsMu1/F"); 
  tree_->Branch("triggerEffWeightsMu2",&triggerEffWeightsMu_[1],"triggerEffWeightsMu2/F"); 
  tree_->Branch("triggerEffWeightsMu3",&triggerEffWeightsMu_[2],"triggerEffWeightsMu3/F"); 
  tree_->Branch("triggerEffWeightsMu4",&triggerEffWeightsMu_[3],"triggerEffWeightsMu4/F"); 
  tree_->Branch("triggerEffWeightsMu5",&triggerEffWeightsMu_[4],"triggerEffWeightsMu5/F"); 

  tree_->Branch("triggerEffWeightsTau1",&triggerEffWeightsTau_[0],"triggerEffWeightsTau1/F"); 
  tree_->Branch("triggerEffWeightsTau2",&triggerEffWeightsTau_[1],"triggerEffWeightsTau2/F"); 
  tree_->Branch("triggerEffWeightsTau3",&triggerEffWeightsTau_[2],"triggerEffWeightsTau3/F"); 
  tree_->Branch("triggerEffWeightsTau4",&triggerEffWeightsTau_[3],"triggerEffWeightsTau4/F"); 
  tree_->Branch("triggerEffWeightsTau5",&triggerEffWeightsTau_[4],"triggerEffWeightsTau5/F"); 

  tree_->Branch("selectionEffWeightsId1",&selectionEffWeightsId_[0],"selectionEffWeightsId1/F"); 
  tree_->Branch("selectionEffWeightsId2",&selectionEffWeightsId_[1],"selectionEffWeightsId2/F"); 
  tree_->Branch("selectionEffWeightsId3",&selectionEffWeightsId_[2],"selectionEffWeightsId3/F"); 
  tree_->Branch("selectionEffWeightsId4",&selectionEffWeightsId_[3],"selectionEffWeightsId4/F"); 
  tree_->Branch("selectionEffWeightsId5",&selectionEffWeightsId_[4],"selectionEffWeightsId5/F"); 

  tree_->Branch("selectionEffWeightsIso1",&selectionEffWeightsIso_[0],"selectionEffWeightsIso1/F"); 
  tree_->Branch("selectionEffWeightsIso2",&selectionEffWeightsIso_[1],"selectionEffWeightsIso2/F"); 
  tree_->Branch("selectionEffWeightsIso3",&selectionEffWeightsIso_[2],"selectionEffWeightsIso3/F"); 
  tree_->Branch("selectionEffWeightsIso4",&selectionEffWeightsIso_[3],"selectionEffWeightsIso4/F"); 
  tree_->Branch("selectionEffWeightsIso5",&selectionEffWeightsIso_[4],"selectionEffWeightsIso5/F"); 


  tree_->Branch("genbosonmass",&genbosonmass_,"genbosonmass/F");
  tree_->Branch("genbosonpt",&genbosonpt_,"genbosonpt/F");
  tree_->Branch("genbosoneta",&genbosoneta_,"genbosoneta/F");
  tree_->Branch("genbosonphi",&genbosonphi_,"genbosonphi/F");
  tree_->Branch("lhenup",&lhenup_,"lhenup/I");


  tree_->Branch("runnumber",&runnumber_,"runnumber/I");
  tree_->Branch("lumiblock",&lumiblock_,"lumiblock/I");
  tree_->Branch("eventid",&eventid_,"eventid/I");
  tree_->Branch("trigPath1",&trigPath_[0],"trigPath1/I");
  tree_->Branch("trigPath2",&trigPath_[1],"trigPath2/I");
  tree_->Branch("trigPath3",&trigPath_[2],"trigPath3/I");
  tree_->Branch("trigPath4",&trigPath_[3],"trigPath4/I");
  tree_->Branch("trigPath5",&trigPath_[4],"trigPath5/I");
  tree_->Branch("trigPath6",&trigPath_[5],"trigPath6/I");
  tree_->Branch("trigPath7",&trigPath_[6],"trigPath7/I");
  tree_->Branch("trigPath8",&trigPath_[7],"trigPath8/I");
  tree_->Branch("trigPath9",&trigPath_[8],"trigPath9/I");
  tree_->Branch("trigPath10",&trigPath_[9],"trigPath10/I");
  tree_->Branch("trigTest1",&trigTest_[0],"trigTest1/I");
  tree_->Branch("trigTest2",&trigTest_[1],"trigTest2/I");
  tree_->Branch("trigTest3",&trigTest_[2],"trigTest3/I");
  tree_->Branch("trigTest4",&trigTest_[3],"trigTest4/I");
  tree_->Branch("trigTest5",&trigTest_[4],"trigTest5/I");
  tree_->Branch("trigTest6",&trigTest_[5],"trigTest6/I");
  tree_->Branch("trigTest7",&trigTest_[6],"trigTest7/I");
  tree_->Branch("trigTest8",&trigTest_[7],"trigTest8/I");
  tree_->Branch("trigTest9",&trigTest_[8],"trigTest9/I");
  tree_->Branch("trigTest10",&trigTest_[9],"trigTest10/I");

  tree_->Branch("npu",&npu_,"npu/I");
  tree_->Branch("nvtx",&nvtx_,"nvtx/I");
  tree_->Branch("vtxx",&vtxx_,"vtxx/F");
  tree_->Branch("vtxy",&vtxy_,"vtxy/F");
  tree_->Branch("vtxz",&vtxz_,"vtxz/F");

  tree_->Branch("nditau",&nditau_,"nditau/I");
  tree_->Branch("ditaumass",&ditaumass_,"ditaumass/F");
  tree_->Branch("ditaucharge",&ditaucharge_,"ditaucharge/I");
  tree_->Branch("svfitmass",&svfitmass_,"svfitmass/F");
  tree_->Branch("ditaueta",&ditaueta_,"ditaueta/F");
  tree_->Branch("ditaupt",&ditaupt_,"ditaupt/F");
  tree_->Branch("ditauphi",&ditauphi_,"ditauphi/F");
  tree_->Branch("mutaucostheta",&mutaucostheta_,"mutaucostheta/F");
  tree_->Branch("ditaudeltaR",&ditaudeltaR_,"ditaudeltaR/F");
  tree_->Branch("ditaudeltaEta",&ditaudeltaEta_,"ditaudeltaEta/F");
  tree_->Branch("ditaudeltaPhi",&ditaudeltaPhi_,"ditaudeltaPhi/F");
  
  tree_->Branch("taumass",&taumass_,"taumass/F");
  tree_->Branch("taupt",&taupt_,"taupt/F");
  tree_->Branch("taupx",&taupx_,"taupx/F");
  tree_->Branch("taupy",&taupy_,"taupy/F");
  tree_->Branch("taueta",&taueta_,"taueta/F");
  tree_->Branch("tauphi",&tauphi_,"tauphi/F");
  tree_->Branch("tauehop",&tauehop_,"tauehop/F");
  tree_->Branch("taueop",&taueop_,"taueop/F");
  tree_->Branch("tauhoe",&tauhoe_,"tauhoe/F");
  tree_->Branch("tautruth",&tautruth_,"tautruth/I");
  tree_->Branch("tautruthstatus",&tautruthstatus_,"tautruthstatus/I");
  tree_->Branch("tautruthpt",&tautruthpt_,"tautruthpt/F");
  tree_->Branch("tautrutheta",&tautrutheta_,"tautrutheta/F");
  tree_->Branch("taudecaymode",&taudecaymode_,"taudecaymode/I");
  tree_->Branch("taudz",&taudz_,"taudz/F");
  tree_->Branch("taudxy",&taudxy_,"taudxy/F");
  tree_->Branch("tauantie",&tauantie_,"tauantie/I");
  tree_->Branch("tauantimu",&tauantimu_,"tauantimu/I");
  tree_->Branch("tauisodisc",&tauisodisc_,"tauisodisc/I");
  tree_->Branch("tauisodiscmva",&tauisodiscmva_,"tauisodiscmva/I");
  tree_->Branch("tauiso",&tauiso_,"tauiso/F");
  tree_->Branch("tauisomva",&tauisomva_,"tauisomva/F");
  tree_->Branch("taux",&taux_,"taux/F");
  tree_->Branch("tauy",&tauy_,"tauy/F");
  tree_->Branch("tauz",&tauz_,"tauz/F");
  tree_->Branch("taujetpt",&taujetpt_,"taujetpt/F");
  tree_->Branch("taujeteta",&taujeteta_,"taujeteta/F");
  tree_->Branch("taujetrefpt",&taujetrefpt_,"taujetrefpt/F");
  tree_->Branch("taujetrefeta",&taujetrefeta_,"taujetrefeta/F");
  tree_->Branch("tauleadpt",&tauleadpt_,"tauleadpt/F");
  tree_->Branch("tauleadhcal",&tauleadhcal_,"tauleadhcal/F");
  tree_->Branch("tauleadecal",&tauleadecal_,"tauleadecal/F");
  tree_->Branch("taucharge",&taucharge_,"taucharge/I");

  tree_->Branch("mupt",&mupt_,"mupt/F");
  tree_->Branch("mueta",&mueta_,"mueta/F");
  tree_->Branch("muphi",&muphi_,"muphi/F");
  tree_->Branch("muiso",&muiso_,"muiso/F");
  tree_->Branch("muisomva",&muisomva_,"muisomva/F");
  tree_->Branch("mudz",&mudz_,"mudz/F");
  tree_->Branch("mudxy",&mudxy_,"mudxy/F");
  tree_->Branch("mux",&mux_,"mux/F");
  tree_->Branch("muy",&muy_,"muy/F");
  tree_->Branch("muz",&muz_,"muz/F");
  tree_->Branch("mujetpt",&mujetpt_,"mujetpt/F");
  tree_->Branch("mujeteta",&mujeteta_,"mujeteta/F");
  tree_->Branch("mutruth",&mutruth_,"mutruth/I");
  tree_->Branch("mutruthstatus",&mutruthstatus_,"mutruthstatus/I");
  tree_->Branch("mutruthpt",&mutruthpt_,"mutruthpt/F");
  tree_->Branch("mutrutheta",&mutrutheta_,"mutrutheta/F");
  tree_->Branch("mucharge",&mucharge_,"mucharge/I");

  tree_->Branch("pfmetpt",&pfmetpt_,"pfmetpt/D");
  tree_->Branch("pfmetphi",&pfmetphi_,"pfmetphi/D");
  tree_->Branch("pftransversemass",&pftransversemass_,"pftransversemass/F");
  tree_->Branch("metptraw",&metptraw_,"metptraw/D");
  tree_->Branch("metphiraw",&metphiraw_,"metphiraw/D");
  tree_->Branch("metpt",&metpt_,"metpt/D");
  tree_->Branch("metphi",&metphi_,"metphi/D");
  tree_->Branch("transversemass",&transversemass_,"transversemass/F");
  tree_->Branch("metsigcov00",&metsigcov00_,"metsigcov00/F");
  tree_->Branch("metsigcov01",&metsigcov01_,"metsigcov01/F");
  tree_->Branch("metsigcov10",&metsigcov10_,"metsigcov10/F");
  tree_->Branch("metsigcov11",&metsigcov11_,"metsigcov11/F");

  tree_->Branch("pZeta",&pZeta_,"pZeta/F");
  tree_->Branch("pZetaVis",&pZetaVis_,"pZetaVis/F");


  tree_->Branch("pfMetForRegression",&pfMetForRegression_,"pfMetForRegression/F");
  tree_->Branch("tkMet",&tkMet_,"tkMet/F");
  tree_->Branch("nopuMet",&nopuMet_,"nopuMet/F");
  tree_->Branch("puMet",&puMet_,"puMet/F");
  tree_->Branch("pcMet",&pcMet_,"pcMet/F");


  tree_->Branch("njet",&njet_,"njet/I"); 
  tree_->Branch("njetLepLC",&njetLepLC_,"njetLepLC/I"); 
  tree_->Branch("leadJetPt",&leadJetPt_,"leadJetPt/F");
  tree_->Branch("leadJetPUIdMva",&leadJetPUIdMva_,"leadJetPUIdMva/F");
  tree_->Branch("leadJetRawFactor",&leadJetRawFactor_,"leadJetRawFactor/F");
  tree_->Branch("leadJetEta",&leadJetEta_,"leadJetEta/F");
  tree_->Branch("subleadJetPt",&subleadJetPt_,"subleadJetPt/F");
  tree_->Branch("subleadJetEta",&subleadJetEta_,"subleadJetEta/F");
  tree_->Branch("subleadJetRawFactor",&subleadJetRawFactor_,"subleadJetRawFactor/F");
  tree_->Branch("diJetMass",&diJetMass_,"diJetMass/F");
  tree_->Branch("diJetPt",&diJetPt_,"diJetPt/F"); 
  tree_->Branch("diJetDeltaEta",&diJetDeltaEta_,"diJetDeltaEta/F");
  tree_->Branch("diJetEta1Eta2",&diJetEta1Eta2_,"diJetEta1Eta2/F"); 
  tree_->Branch("njetingap",&njetingap_,"njetingap/I");

  tree_->Branch("njet20",&njet20_,"njet20/I");
  tree_->Branch("nbjet",&nbjet_,"nbjet/I");
  tree_->Branch("leadBJetPt",&leadBJetPt_,"leadBJetPt/F");
  tree_->Branch("leadBJetEta",&leadBJetEta_,"leadBJetEta/F");

  tree_->Branch("nbjetLoose",&nbjetLoose_,"nbjetLoose/I");

  tree_->Branch("jet20pt1",&jet20pt1_,"jet20pt1/F");
  tree_->Branch("jet20eta1",&jet20eta1_,"jet20eta1/F");
  tree_->Branch("jet20phi1",&jet20phi1_,"jet20phi1/F");
  tree_->Branch("jet20mass1",&jet20mass1_,"jet20mass1/F");
  tree_->Branch("jet20tagprob1",&jet20tagprob1_,"jet20tagprob1/F");
  tree_->Branch("jet20flavor1",&jet20flavor1_,"jet20flavor1/I");

  tree_->Branch("jet20pt2",&jet20pt2_,"jet20pt2/F");
  tree_->Branch("jet20eta2",&jet20eta2_,"jet20eta2/F");
  tree_->Branch("jet20phi2",&jet20phi2_,"jet20phi2/F");
  tree_->Branch("jet20mass2",&jet20mass2_,"jet20mass2/F");
  tree_->Branch("jet20tagprob2",&jet20tagprob2_,"jet20tagprob2/F");
  tree_->Branch("jet20flavor2",&jet20flavor2_,"jet20flavor2/I");

  tree_->Branch("jet20pt3",&jet20pt3_,"jet20pt3/F");
  tree_->Branch("jet20eta3",&jet20eta3_,"jet20eta3/F");
  tree_->Branch("jet20phi3",&jet20phi3_,"jet20phi3/F");
  tree_->Branch("jet20mass3",&jet20mass3_,"jet20mass3/F");
  tree_->Branch("jet20tagprob3",&jet20tagprob3_,"jet20tagprob3/F");
  tree_->Branch("jet20flavor3",&jet20flavor3_,"jet20flavor3/I");

  tree_->Branch("jet20pt4",&jet20pt4_,"jet20pt4/F");
  tree_->Branch("jet20eta4",&jet20eta4_,"jet20eta4/F");
  tree_->Branch("jet20phi4",&jet20phi4_,"jet20phi4/F");
  tree_->Branch("jet20mass4",&jet20mass4_,"jet20mass4/F");
  tree_->Branch("jet20tagprob4",&jet20tagprob4_,"jet20tagprob4/F");
  tree_->Branch("jet20flavor4",&jet20flavor4_,"jet20flavor4/I");


  tree_->Branch("vbfmva",&vbfmva_,"vbfmva/F");
  tree_->Branch("vbfvars0",&vbfvars_[0],"vbfvars0/D");
  tree_->Branch("vbfvars1",&vbfvars_[1],"vbfvars1/D");
  tree_->Branch("vbfvars2",&vbfvars_[2],"vbfvars2/D");
  tree_->Branch("vbfvars3",&vbfvars_[3],"vbfvars3/D");
  tree_->Branch("vbfvars4",&vbfvars_[4],"vbfvars4/D");
  tree_->Branch("vbfvars5",&vbfvars_[5],"vbfvars5/D");
  tree_->Branch("vbfvars6",&vbfvars_[6],"vbfvars6/D");
  tree_->Branch("vbfvars7",&vbfvars_[7],"vbfvars7/D");

  tree_->Branch("vbfmva2012",&vbfmva2012_,"vbfmva2012/F");
  tree_->Branch("vbfvars20120",&vbfvars2012_[0],"vbfvars20120/D");
  tree_->Branch("vbfvars20121",&vbfvars2012_[1],"vbfvars20121/D");
  tree_->Branch("vbfvars20122",&vbfvars2012_[2],"vbfvars20122/D");
  tree_->Branch("vbfvars20123",&vbfvars2012_[3],"vbfvars20123/D");
  
  tree_->Branch("muLCleadJetPt",&muLCleadJetPt_,"muLCleadJetPt/F");
  tree_->Branch("muLCleadJetEta",&muLCleadJetEta_,"muLCleadJetEta/F");

  tree_->Branch("categoryIso",&categoryIso_,"categoryIso/I");
  tree_->Branch("categorySM",&categorySM_,"categorySM/I");
  tree_->Branch("categorySM2012",&categorySM2012_,"categorySM2012/I");

  counterall_=0;
  countertrig_=0;
  counterruns_=0;
  countergoodvtx_=0;
  countergen_=0;
}


// void BaseFlatNtp::analyze(const edm::Event & iEvent, const edm::EventSetup & iSetup){
//   fillVariables(iEvent,iSetup);
//   if(!applySelections())return;
//   fill();
//   tree_->Fill();
// }

void BaseFlatNtp::endJob(){

  cout<<"counterall = "<<counterall_<<endl;
  cout<<"counterruns = "<<counterruns_<<endl;
  cout<<"countertrig = "<<countertrig_<<endl;
  cout<<"countergoodvtx = "<<countergoodvtx_<<endl;
  cout<<"countergen = "<<countergen_<<endl;

}



bool BaseFlatNtp::fillVariables(const edm::Event & iEvent, const edm::EventSetup & iSetup){
  //fill things one may need to apply selections

  iEvent_=&iEvent;

  runnumber_=iEvent_->run();
  lumiblock_=iEvent_->luminosityBlock();
  eventid_=iEvent_->id().event();
  
  iEvent_->getByLabel(verticesListTag_,vertices_);
  nvtx_=vertices_->size();  
  PV_=&(*(vertices_->begin()));
  
  lhenup_=-1;
  if(saveLHENUP_==1){  
    edm::Handle< LHEEventProduct > LHEEvent_;
    iEvent_->getByLabel(edm::InputTag("source"),LHEEvent_);
    lhenup_=LHEEvent_->hepeup().NUP;
  }


  iEvent_->getByLabel(trigPathsListTag_,trig_);
  //trig_->begin()->printSelections(cout);

  //get trigger object list for later
  iEvent_->getByLabel(trigObjsListTag_,trigObjs_);

  //get the unscaled taus
  iEvent_->getByLabel(unscaledTauTag_,unscaledTauList_);
  
  ///get the gen Boson and set the genEventType
  genBoson_ = NULL;
  genBosonL1_ = NULL;
  genBosonL2_ = NULL;
  genEventType_=0;
  genbosonpt_=0.;
  genbosoneta_=0.;
  genbosonphi_=0.;
  genbosonmass_=0.;
  if(dataType_==0){  
    iEvent_->getByLabel(genParticlesTag_,genParticles_);    
    for(std::vector<reco::GenParticle>::const_iterator g=genParticles_->begin(); g!=genParticles_->end(); ++g){
      if(g->status()==3){
	//cout<<g->pdgId()<<" "<<g->p4().pt()<<endl;
	if((abs(g->pdgId())==23 || abs(g->pdgId())==24 ||  abs(g->pdgId())==25 ||  abs(g->pdgId())==36 ) && genBoson_==NULL )
	  genBoson_=&(*g);
      }
    }
    //if(genBoson_)cout<<"genBoson_ ref = "<<genBoson_<<" "<<<genBoson_->pdgId()<<" "<<genBoson_->pt()<<endl;

    if(genBoson_){      

      genbosonpt_=genBoson_->pt();
      genbosoneta_=genBoson_->eta();
      genbosonphi_=genBoson_->phi();

      //determine type of generated event: Z-->ee,mumu,tautau,, W-->e nu, mu nu, tau mu
      int genTaus=0;
      int genMuons=0;
      int genElectrons=0;
      for(std::vector<reco::GenParticle>::const_iterator g=genParticles_->begin(); g!=genParticles_->end(); ++g){    
	if(g->status()==3){
	  if(abs(g->pdgId())==11 && g->mother()==genBoson_) genElectrons++;
	  if(abs(g->pdgId())==13 && g->mother()==genBoson_) genMuons++;
	  if(abs(g->pdgId())==15 && g->mother()==genBoson_) genTaus++;
	}
      }
      if(abs(genBoson_->pdgId())==23 && genElectrons==2)   genEventType_=1;
      if(abs(genBoson_->pdgId())==23 && genMuons==2)       genEventType_=3;
      if(abs(genBoson_->pdgId())==23 && genTaus==2)        genEventType_=5;
      if(abs(genBoson_->pdgId())==24 && genElectrons==1)   genEventType_=11;
      if(abs(genBoson_->pdgId())==24 && genMuons==1)       genEventType_=13;
      if(abs(genBoson_->pdgId())==24 && genTaus==1)        genEventType_=15;

      //get the leptons from the genBoson
      for(std::vector<reco::GenParticle>::const_iterator g=genParticles_->begin(); g!=genParticles_->end(); ++g){
	if(g->status()==3){    
	  if((g->pdgId()==11 || g->pdgId()==13 || g->pdgId()==15 ) && g->mother()==genBoson_) genBosonL1_=&(*g);
	  if((g->pdgId()==-11 || g->pdgId()==-13 || g->pdgId()==-15 ) && g->mother()==genBoson_) genBosonL2_=&(*g);
	}
      }      

      if(genBosonL1_ && genBosonL2_)
	genbosonmass_=(genBosonL1_->p4()+genBosonL2_->p4()).mass();
      //cout<<genbosonmass_<<" "<<genbosonpt_<<" "<<genbosonphi_<<endl;

    }

  }

 
  //get the muons for the di-lepton veto
  iEvent.getByLabel(muonVetoListTag_,leptonVetoListMuon_);
  iEvent.getByLabel(electronVetoListTag_,leptonVetoListElectron_);
  iEvent.getByLabel(tauVetoListTag_,leptonVetoListTau_);


  if(printSelectionPass_==2){
    cout<<runnumber_<<":"<<eventid_<<" List of initial Electrons : "<< leptonVetoListElectron_->size()<<endl; 
    for(std::vector<cmg::Electron>::const_iterator cand=leptonVetoListElectron_->begin(); cand!=leptonVetoListElectron_->end(); ++cand)
      printElectronInfo(&(*cand));

    cout<<runnumber_<<":"<<eventid_<<" List of initial Muons :"<< leptonVetoListMuon_->size()<<endl; 
    for(std::vector<cmg::Muon>::const_iterator cand=leptonVetoListMuon_->begin(); cand!=leptonVetoListMuon_->end(); ++cand)
      printMuonInfo(&(*cand));

    cout<<runnumber_<<":"<<eventid_<<" List of initial Taus :"<< leptonVetoListTau_->size()<<endl; 
    for(std::vector<cmg::Tau>::const_iterator cand=leptonVetoListTau_->begin(); cand!=leptonVetoListTau_->end(); ++cand)
      printTauInfo(&(*cand));

  }


  return 1;
}

bool BaseFlatNtp::applySelections(){
  counterall_++;

  if((firstRun_!=0 && runnumber_<firstRun_)
     || (lastRun_!=0 && lastRun_<runnumber_)){
    if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" fail counterruns"<<endl;
    return 0;
  }
  counterruns_++;
  if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" pass counterruns"<<endl;

  trigpass_=0;
  if(trigPaths_.size()==0)trigpass_=1;//no trigger requirement
  for(std::vector<edm::InputTag *>::const_iterator path=trigPaths_.begin(); path!=trigPaths_.end(); path++){//cmg ObjetSel
    //cout<<path->label()<<" "<<path->instance()<<" "<<path->process()<<endl;
    if(trig_->begin()->hasSelection((*path)->label()))
      if(trig_->begin()->getSelection((*path)->label()))
	if(trig_->begin()->getPrescale((*path)->label())==1 || dataType_==0){
	  trigpass_=1;
	}
  }
  //cout<<firstRun_<<" "<<lastRun_<<" "<<runnumber_<<" "<<trigpass_<<endl;
  if(!trigpass_){
    if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" fail countertrig"<<endl;
    return 0;
  }
  countertrig_++;
  if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" pass countertrig"<<endl;
  
  if(nvtx_==0){
    if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" fail countergoodvtx"<<endl;
    return 0;
  }
  countergoodvtx_++;
  if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" pass countergoodvtx"<<endl;

  if( sampleGenEventType_!=0 && sampleGenEventType_!=genEventType_){
    if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" fail countergen"<<endl;
    return 0;
  }
  countergen_++;
  if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" passcountergen "<<endl;

  if(printSelectionPass_)cout<<runnumber_<<":"<<eventid_<<" passed BaseFlatNtp selections "<<endl;
  return 1;
}

bool BaseFlatNtp::fill(){
 
  vtxx_=PV_->x();
  vtxy_=PV_->y();
  vtxz_=PV_->z();

  pupWeight_=1.;//do not comment out needs to be used.
  for(long i=0;i<5;i++)
    pupWeights_[i]=1.;
  npu_=-1;
  if(dataType_==0 && (pupWeightName_.label()).compare("")!=0){//if no vertex weight name is provided then leave weight to 1
    edm::Handle<double>  PupWeight;
    iEvent_->getByLabel(pupWeightName_,PupWeight);    
    pupWeight_=(*PupWeight);

    //get the number of pile up vertexes
    edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent_->getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      int BX = PVI->getBunchCrossing();
      if(BX == 0) {
	if(dataPeriodFlag_==2011)npu_ = PVI->getPU_NumInteractions();
	if(dataPeriodFlag_==2012)npu_ = PVI->getTrueNumInteractions();
      }
    }

    //extra pile-up weights
    for(long i=0;i<5;i++){
      if((pupWeightNames_[i].label()).compare("")!=0){
	edm::Handle<double>  PupWeight;
	iEvent_->getByLabel(pupWeightNames_[i],PupWeight);    
	pupWeights_[i]=(*PupWeight);
      }
    }


  }


  //embedded samples generator weight
  embeddedGenWeight_=1.0;
  if(dataType_==2){
    if(dataPeriodFlag_==2011){
      edm::Handle< double > embeddedGenWeight;
      iEvent_->getByLabel(edm::InputTag("generator","weight",""),embeddedGenWeight);
      embeddedGenWeight_=*embeddedGenWeight;
    }
    if(dataPeriodFlag_==2012){
      edm::Handle<GenFilterInfo> genInfoEmbedded;
      iEvent_->getByLabel(edm::InputTag("generator","minVisPtFilter","EmbeddedRECO"),genInfoEmbedded);
      if(genInfoEmbedded->numEventsTried()>0) embeddedGenWeight_ =  genInfoEmbedded->filterEfficiency(); 
    }
  }  


  //fill the signalWeight
  signalWeight_=1.;
  if(signalWeightHisto_){
    if(!genBoson_){
      cout<<"signal weight requested but no genboson found in event."<<endl;
      exit(0);
    }
    if(0.<genbosonpt_&&genbosonpt_<500.)
      signalWeight_=signalWeightHisto_->GetBinContent(((int)genbosonpt_)+1);//round the the pt value down
  }



  return 1;
}


const cmg::TriggerObject * BaseFlatNtp::trigObjMatch(float eta, float phi, std::string path, std::string filter, int pdgid){

  //cout<<filter.c_str()<<endl;
  //if(filter.compare("")==0) return 1;//no trigger matching required

  for(std::vector<cmg::TriggerObject>::const_iterator obj=trigObjs_->begin(); obj!=trigObjs_->end(); obj++){
    if(obj->hasSelection(path.c_str()))//HLT path name
      //obj->printSelections(cout);
      if(obj->hasSelection(filter.c_str()))//last filter
	if(reco::deltaR(eta,phi,obj->eta(),obj->phi())<0.5
	   && (abs(obj->pdgId())==pdgid || pdgid==-1)
	   ){
	  //obj->printSelections(cout);	  
	  //cout<<"pdg id "<<obj->pdgId()<<endl;
	  //cout<<obj->hasSelection(filter.c_str())<<endl;
	  return &(*obj);      
	}
  }
  
  return 0;
}


bool  BaseFlatNtp::checkPUJetId(const cmg::PFJet *jet){

  float eta=fabs(jet->eta());
  //float mva=jet->puMva("full");
  float mva=jet->puMva(pujetidname_.c_str());
  //cout<<"pujetid "<<pujetidname_.c_str()<<"   "<<mva<<endl;
  bool pass=1;
  if(0.00<=eta&&eta<2.50) if(mva<-0.80) pass=0;
  if(2.50<=eta&&eta<2.75) if(mva<-0.74) pass=0;
  if(2.75<=eta&&eta<3.00) if(mva<-0.68) pass=0;
  if(3.00<=eta&&eta<5.00) if(mva<-0.77) pass=0;

  return pass;
}

void BaseFlatNtp::fillPFJetList(std::vector<const cmg::PFJet * > * fulllist, std::vector<const cmg::PFJet * > * list){
  list->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=fulllist->begin(); jet!=fulllist->end(); ++jet){
    if((*jet)->pt()<30.0)continue;  
    if(fabs((*jet)->eta())>4.7)continue; 
    if(!checkPFJetId((*jet)))continue;
    if(!checkPUJetId((*jet)))continue;
    list->push_back((*jet));
  }
}

void BaseFlatNtp::fillPFJetList20(std::vector<const cmg::PFJet * > * fulllist, std::vector<const cmg::PFJet * > * list){
  list->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=fulllist->begin(); jet!=fulllist->end(); ++jet){
    if((*jet)->pt()<20.0)continue;  
    if(fabs((*jet)->eta())>4.7)continue; 
    if(!checkPFJetId((*jet)))continue;
    if(!checkPUJetId((*jet)))continue;
    list->push_back((*jet));
  }
}

void BaseFlatNtp::fillPFJetListBTag(std::vector<const cmg::PFJet * > * fulllist, std::vector<const cmg::PFJet * > * list){
  list->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=fulllist->begin(); jet!=fulllist->end(); ++jet){
    if(fabs((*jet)->eta())>2.4)continue; 
    //if((*jet)->btag("combinedSecondaryVertexBJetTags")<btagWP_)continue;//CSV medium

    ///btagWP value is now hard coded inside this class:
    if(!(btagsf.isbtagged((*jet)->pt(),
			(*jet)->eta(),
			(*jet)->btag("combinedSecondaryVertexBJetTags"),
			TMath::Abs((*jet)->partonFlavour()),
			dataType_==1
			,0 , 0,
			dataPeriodFlag_==2012))) continue;    
    

    list->push_back((*jet));
  }
}

///counter of loose b-jets for mT extrapolation factor
void BaseFlatNtp::fillPFJetListBTagLoose(std::vector<const cmg::PFJet * > * fulllist, std::vector<const cmg::PFJet * > * list){
  list->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=fulllist->begin(); jet!=fulllist->end(); ++jet){
    if(fabs((*jet)->eta())>2.4)continue; 
    if((*jet)->btag("combinedSecondaryVertexBJetTags")<0.244)continue;//CSV medium
    list->push_back((*jet));
  }
}


void BaseFlatNtp::fillPFJetListLC(float leg1eta, float leg1phi, float leg2eta, float leg2phi, std::vector<const cmg::PFJet * > * list, std::vector<const cmg::PFJet * > * listLC){
  listLC->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=list->begin(); jet!=list->end(); ++jet){
    if(reco::deltaR((*jet)->eta(),(*jet)->phi(),leg1eta,leg1phi)<0.5) continue;     
    if(reco::deltaR((*jet)->eta(),(*jet)->phi(),leg2eta,leg2phi)<0.5) continue;   
    listLC->push_back(*jet);
  }
}


void BaseFlatNtp::fillPFJetListLepLC(float lepeta, float lepphi,std::vector<const cmg::PFJet * > * list, std::vector<const cmg::PFJet * > * listLC){
  listLC->clear();
  for(std::vector<const cmg::PFJet *>::const_iterator jet=list->begin(); jet!=list->end(); ++jet){
    if(reco::deltaR((*jet)->eta(),(*jet)->phi(),lepeta,lepphi)<0.5) continue;   
    listLC->push_back(*jet);
  }  
}


int BaseFlatNtp::truthMatchLeg(float legeta, float legphi,float& truthpt,float& trutheta,int& truthstatus){
  if(dataType_!=0) return 0;

  truthpt=0.;
  trutheta=0.;
  truthstatus=-1;

  for(std::vector<reco::GenParticle>::const_iterator g=genParticles_->begin(); g!=genParticles_->end(); ++g){    
    if(abs(g->pdgId())==11) if(reco::deltaR(legeta,legphi,g->eta(),g->phi())<deltaRTruth_){truthpt=g->pt(); trutheta=g->eta(); truthstatus=g->status(); return 1;}
    if(abs(g->pdgId())==13) if(reco::deltaR(legeta,legphi,g->eta(),g->phi())<deltaRTruth_){truthpt=g->pt(); trutheta=g->eta(); truthstatus=g->status(); return 3;}
    if(abs(g->pdgId())==15) if(reco::deltaR(legeta,legphi,g->eta(),g->phi())<deltaRTruth_){truthpt=g->pt(); trutheta=g->eta(); truthstatus=g->status(); return 5;}
    if(abs(g->pdgId())==22) if(reco::deltaR(legeta,legphi,g->eta(),g->phi())<deltaRTruth_){truthpt=g->pt(); trutheta=g->eta(); truthstatus=g->status(); return 6;}
  }
  
  return 9;
}

const cmg::PFJet * BaseFlatNtp::findJet(std::vector<const cmg::PFJet * > * fulllist, float eta, float phi){
  for(std::vector<const cmg::PFJet *>::const_iterator jet=fulllist->begin(); jet!=fulllist->end(); ++jet)
    if(reco::deltaR((*jet)->eta(),(*jet)->phi(),eta,phi)<0.3) return *jet;
  return 0;
}

void BaseFlatNtp::printMCGen(edm::Handle< std::vector<reco::GenParticle> > & genList){
  cout<<" Begin MC print out for event: "<<runnumber_<<" "<<lumiblock_<<" "<<eventid_<<endl;
  for(std::vector<reco::GenParticle>::const_iterator g=genList->begin(); g!=genList->end(); ++g){    
    cout<<"pdgID = "<<g->pdgId()<<" , pt = "<<g->p4().pt()<<" motherRef="<<g->mother()<<endl;
  }
}



void BaseFlatNtp::printMuonInfo(const cmg::Muon * cand){
  cout<<" Muon info "<<endl;
  cout<<"   pt                             = "<<cand->pt()<<endl;
  cout<<"   eta                            = "<<cand->eta()<<endl;
  cout<<"   phi                            = "<<cand->phi()<<endl;
  cout<<"   charge                         = "<<cand->charge()<<endl;
  cout<<"   neutralHadronIso               = "<<cand->neutralHadronIso(-1)<<endl;
  cout<<"   chargedHadronIso               = "<<cand->chargedHadronIso(-1)<<endl;
  cout<<"   photonIso                      = "<<cand->photonIso(-1)<<endl;
  cout<<"   chargedAllIso                  = "<<cand->chargedAllIso(-1)<<endl;
  cout<<"   puChargedHadronIso             = "<<cand->puChargedHadronIso(-1)<<endl; 
  cout<<"   RelIso                         = "<<cand->relIso(0.5,1)<<endl;

  cout<<"   isGlobal                       = "<< cand->isGlobal() <<endl;
  cout<<"   isPFMuon                       = "<< (*(cand->sourcePtr()))->userFloat("isPFMuon") <<endl;
  cout<<"   normalizedChi2                 = "<< cand->normalizedChi2() <<endl;
  cout<<"   numberOfValidMuonHits          = "<< cand->numberOfValidMuonHits() <<endl;
  cout<<"   numberOfMatchedStations        = "<< cand->numberOfMatchedStations() <<endl;
  cout<<"   trackerLayersWithMeasurement   = "<< cand->trackerLayersWithMeasurement() <<endl;

  if(((*(cand->sourcePtr()))->innerTrack().isNonnull())
     &&((*(cand->sourcePtr()))->innerTrack().isAvailable())){
    cout<<"   dz                             = "<<(*(cand->sourcePtr()))->innerTrack()->dz(PV_->position()) <<endl;
    cout<<"   dxy                            = "<<(*(cand->sourcePtr()))->innerTrack()->dxy(PV_->position()) <<endl;
    cout<<"   numberOfValidPixelHits         = "<< (*(cand->sourcePtr()))->innerTrack()->hitPattern().numberOfValidPixelHits()  <<endl;
  }

  //
  const cmg::TriggerObject * trigobj=0;
  if(trigPaths_.size()!=0){
    for(std::vector<edm::InputTag*>::const_iterator path=trigPaths_.begin(); path!=trigPaths_.end(); path++){      
      trigobj=trigObjMatch(cand->eta(),cand->phi(),(*path)->label(),(*path)->process(),13);
    }
  }
  if(trigobj){
    cout<<"  trig object info:"<<endl;
    cout<<"    pt   = "<< trigobj->pt() <<endl;
    cout<<"    eta  = "<< trigobj->eta() <<endl;
    cout<<"    phi  = "<< trigobj->phi() <<endl;
    cout<<"   pdgid = "<< trigobj->pdgId()<<endl;
    trigobj->printSelections(cout);	  
  }
  
}


void BaseFlatNtp::printElectronInfo(const cmg::Electron * cand){
  cout<<" Electron info "<<endl;
  cout<<"   pt             = "<<cand->pt()<<endl;
  cout<<"   eta            = "<<cand->eta()<<endl;
  cout<<"   phi            = "<<cand->phi()<<endl;
  cout<<"   charge         = "<<cand->charge()<<endl;

  cout<<"   neutralHadronIso               = "<<cand->neutralHadronIso(-1)<<endl;
  cout<<"   photonIso                      = "<<cand->photonIso(-1)<<endl;
  cout<<"   chargedAllIso                  = "<<cand->chargedAllIso(-1)<<endl;
  cout<<"   puChargedHadronIso             = "<<cand->puChargedHadronIso(-1)<<endl; 

  cout<<"   RelIso         = "<<electronRelIsoDBCorr(cand)<<endl;

  if( ((*(cand->sourcePtr()))->gsfTrack().isNonnull())
      && ((*(cand->sourcePtr()))->gsfTrack().isAvailable())){
    cout<<"   dz             = "<<(*(cand->sourcePtr()))->gsfTrack()->dz(PV_->position()) <<endl;
    cout<<"   dxy            = "<<(*(cand->sourcePtr()))->gsfTrack()->dxy(PV_->position()) <<endl;
  }
  cout<<"   numberOfHits   = "<<cand->numberOfHits()<<endl;
  //cout<<"   passConversion = "<<cand->passConversionVeto()<<endl;
  cout<<"   passConversion = "<<(*(cand->sourcePtr()))->passConversionVeto()<<endl;
  cout<<"   mvaNonTrigV0   = "<<cand->mvaNonTrigV0()<<endl;
  cout<<"   passIDWP95     = "<<electronIDWP95(cand)<<endl;
  cout<<"   isEB           = "<<(*(cand->sourcePtr()))->isEB()<<endl;
  cout<<"   isEE           = "<<(*(cand->sourcePtr()))->isEE()<<endl;
  cout<<"   dEtaSCTkVtx    = "<<cand->deltaEtaSuperClusterTrackAtVtx()<<endl;
  cout<<"   dPhiSCTkVtx    = "<<cand->deltaPhiSuperClusterTrackAtVtx()<<endl;
  cout<<"   sigmaIetaIeta  = "<<cand->sigmaIetaIeta()<<endl;
  cout<<"   hadrOverEm     = "<<cand->hadronicOverEm()<<endl;

  const cmg::TriggerObject * trigobj=0;
  if(trigPaths_.size()!=0){
    for(std::vector<edm::InputTag*>::const_iterator path=trigPaths_.begin(); path!=trigPaths_.end(); path++){      
      trigobj=trigObjMatch(cand->eta(),cand->phi(),(*path)->label(),(*path)->process(),11);
    }
  }
  if(trigobj){
    cout<<"  trig object info:"<<endl;
    cout<<"    pt   = "<< trigobj->pt() <<endl;
    cout<<"    eta  = "<< trigobj->eta() <<endl;
    cout<<"    phi  = "<< trigobj->phi() <<endl;
    cout<<"   pdgid = "<< trigobj->pdgId()<<endl;
    trigobj->printSelections(cout);	  
  }
  

}

void BaseFlatNtp::printTauInfo(const cmg::Tau * cand){
  cout<<" Tau info "<<endl;
  cout<<"   pt                    = "<<cand->pt()<<endl;
  cout<<"   eta                   = "<<cand->eta()<<endl;
  cout<<"   phi                   = "<<cand->phi()<<endl;
  cout<<"   charge                = "<<cand->charge()<<endl;
  cout<<"   decaymode             = "<<cand->decayMode()<<endl;
  cout<<"   byLooseIsoMVA         = "<< cand->tauID("byLooseIsoMVA")<<endl;
  cout<<"   dz                    = "<< computeDz(cand->leadChargedHadrVertex(),cand->p4())<<endl;
  cout<<"   dxy                   = "<< computeDxy(cand->leadChargedHadrVertex(),cand->p4()) <<endl;
  cout<<"   againstMuonLoose      = "<< cand->tauID("againstMuonLoose")<<endl;
  cout<<"   againstMuonTight      = "<< cand->tauID("againstMuonTight")<<endl;
  cout<<"   againstElectronLoose  = "<< cand->tauID("againstElectronLoose") <<endl;
  cout<<"   againstElectronMedium      = "<< cand->tauID("againstElectronMedium")<<endl;
  cout<<"   againstElectronMVA      = "<< cand->tauID("againstElectronMVA")<<endl;
  cout<<"   againstElectronTightMVA2     = "<< cand->tauID("againstElectronTightMVA2")<<endl;

  //
  const cmg::TriggerObject * trigobj=0;
  if(trigPaths_.size()!=0){
    for(std::vector<edm::InputTag*>::const_iterator path=trigPaths_.begin(); path!=trigPaths_.end(); path++){      
      trigobj=trigObjMatch(cand->eta(),cand->phi(),(*path)->label(),(*path)->process(),15);
      if(!trigobj)trigobj=trigObjMatch(cand->eta(),cand->phi(),(*path)->label(),(*path)->process(),0);
    }
  }
  if(trigobj){
    cout<<"  trig object info:"<<endl;
    cout<<"    pt   = "<< trigobj->pt() <<endl;
    cout<<"    eta  = "<< trigobj->eta() <<endl;
    cout<<"    phi  = "<< trigobj->phi() <<endl;
    cout<<"   pdgid = "<< trigobj->pdgId()<<endl;
    trigobj->printSelections(cout);	  
  }
  
}


void BaseFlatNtp::printMETInfo(){
  cout<<" MET info "<<endl;
  cout<<"   pt                    = "<<metpt_<<endl;
  cout<<"   phi                   = "<<metphi_<<endl;  
  cout<<"   metsigcov00           = "<<metsigcov00_<<endl;  
  cout<<"   metsigcov01           = "<<metsigcov01_<<endl;  
  cout<<"   metsigcov10           = "<<metsigcov10_<<endl;  
  cout<<"   metsigcov11           = "<<metsigcov11_<<endl;  
}
