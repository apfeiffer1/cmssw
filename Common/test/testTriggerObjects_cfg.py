from PhysicsTools.PatAlgos.patTemplate_cfg import *
import FWCore.ParameterSet.Config as cms

# Unit test for the muon analysis sequence.

sep_line = "-" * 50
print
print sep_line
print "Trigger sequence test"
print sep_line

process.setName_('ANA')

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )
process.maxLuminosityBlocks = cms.untracked.PSet( 
        input = cms.untracked.int32(10)
        )
process.source.fileNames = ["/store/cmst3/user/cmgtools/CMG/RelValZMM/CMSSW_4_2_3-START42_V12-v2/GEN-SIM-RECO/patTuple_PF2PAT_6.root"]

extension = 'trigger'

# output module for EDM event (ntuple)
process.out.fileName = cms.untracked.string('tree_test_%s.root' % extension)
from CMGTools.Common.eventContent.everything_cff import everything 
process.out.outputCommands = cms.untracked.vstring( 'drop *')
process.out.outputCommands.extend( everything ) 
process.out.outputCommands.append('keep *_cmgTriggerObjectFull_*_*') 
    

#output file for histograms etc
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("histograms_test_%s.root" % extension))


# default analysis sequence    
process.load('CMGTools.Common.analysis_cff')
process.load("CMGTools.Common.trigger_cff")

from CMGTools.Common.physicsObjectPrinter_cfi import physicsObjectPrinter
process.cmgTriggerObjectInfo = physicsObjectPrinter.clone(
    inputCollection = cms.untracked.InputTag("cmgTriggerObjectSel"),
    printSelections = cms.untracked.bool(True)
    )
process.cmgTriggerObjectFull = process.cmgTriggerObject.clone()
process.cmgTriggerObjectFull.cfg.useTriggerObjects = cms.untracked.bool(True)

process.analysisSequence = cms.Sequence(
    process.triggerSequence+
    process.cmgTriggerObjectFull+
    process.cmgTriggerObjectInfo
    )

process.p = cms.Path(
    process.analysisSequence
)

process.schedule = cms.Schedule(
    process.p,
    process.outpath

    )

process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) ) 

print 'input  : ', process.source.fileNames
print 'output :'
print '  tree :', process.out.fileName
print '  hist :', process.TFileService.fileName
