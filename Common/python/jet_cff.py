import FWCore.ParameterSet.Config as cms

from CMGTools.Common.factories.cmgPFJet_cfi import cmgPFJet
from CMGTools.Common.skims.cmgPFJetSel_cfi import cmgPFJetSel
from CMGTools.Common.skims.cmgPFJetCount_cfi import cmgPFJetCount
from CMGTools.Common.skims.cmgPFBaseJetSel_cfi import cmgPFBaseJetSel
from CMGTools.Common.factories.cmgBaseJet_cfi import cmgBaseJet
from CMGTools.Common.histograms.pfJetLorentzVector_cfi import pfJetLorentzVector
from CMGTools.Common.histograms.pfJetHistograms_cfi import pfJetHistograms
from CMGTools.Common.histograms.baseJetLorentzVector_cfi import baseJetLorentzVector
from CMGTools.Common.skims.leadingCMGBaseJetSelector_cfi import leadingCMGBaseJetSelector
from CMGTools.Common.skims.leadingCMGPFJetSelector_cfi import leadingCMGPFJetSelector


# PF jets -------------------------------------------------------

# leading jets 
cmgPFJetLead = leadingCMGPFJetSelector.clone()
cmgPFJetLead.inputCollection = 'cmgPFJet'

# PF base jets (light PF jets, do not store constituents) -------
cmgPFBaseJet = cmgBaseJet.clone()
cmgPFBaseJet.cfg.inputCollection = 'selectedPatJetsPFlow'

# leading jets 
cmgPFBaseJetLead = leadingCMGBaseJetSelector.clone()
cmgPFBaseJetLead.inputCollection = 'cmgPFBaseJet'

# Light calo jets -----------------------------------------------
cmgCaloBaseJet = cmgBaseJet.clone()
cmgCaloBaseJet.cfg.inputCollection = 'selectedPatJets'

cmgCaloBaseJetLead = leadingCMGBaseJetSelector.clone()
cmgCaloBaseJetLead.inputCollection = 'cmgCaloBaseJet'

caloJetLorentzVector = baseJetLorentzVector.clone()
caloJetLorentzVector.inputCollection = 'cmgCaloBaseJetLead'

jetHistograms = cms.Sequence(
    pfJetLorentzVector +
    pfJetHistograms +
    caloJetLorentzVector
    )

pfJetSequence = cms.Sequence(
    cmgPFJet +
    cmgPFJetSel + 
    cmgPFJetLead +
    cmgPFJetCount +  #SKIM!
    cmgPFBaseJet +
    cmgPFBaseJetSel + 
    cmgPFBaseJetLead + 
    pfJetLorentzVector +
    pfJetHistograms 
    )

caloJetSequence = cms.Sequence(
    cmgCaloBaseJet + 
    cmgCaloBaseJetLead + 
    caloJetLorentzVector
    )


jetSequence = cms.Sequence(
    pfJetSequence +
    caloJetSequence 
    ) 
