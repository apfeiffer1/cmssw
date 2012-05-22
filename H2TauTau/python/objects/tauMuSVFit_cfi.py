import FWCore.ParameterSet.Config as cms

tauMuSVFit = cms.EDProducer(
    "TauMuWithSVFitProducer",
    diTauSrc = cms.InputTag("cmgTauMuCorPreSel"),
    # metSrc = cms.InputTag("cmgPFMET"),
    # metsigSrc = cms.InputTag("pfMetSignificance"),
    metsigSrc = cms.InputTag("mvaMETTauMu"),
    SVFitVersion =  cms.int32(1), # 1 for 2011 version , 2 for new 2012 (slow) version
    verbose = cms.untracked.bool( False )    
    )
