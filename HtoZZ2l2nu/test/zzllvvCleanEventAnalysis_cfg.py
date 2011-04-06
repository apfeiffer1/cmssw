import FWCore.ParameterSet.Config as cms

process = cms.Process("HtoZZto2l2nuAN")

from CMGTools.HtoZZ2l2nu.localPatTuples_cff import configureFromCommandLine
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring()
                            )
dtag, process.source.fileNames, outputFile = configureFromCommandLine(process)
print process.source.fileNames

#load the analyzer
process.load('CMGTools.HtoZZ2l2nu.PileupNormalizationProducer_cfi')
process.load('CMGTools.HtoZZ2l2nu.CleanEventAnalyzer_cfi')
process.evAnalyzer.dtag=cms.string(dtag)
process.TFileService = cms.Service("TFileService", fileName = cms.string(outputFile) )
process.p = cms.Path(process.puWeights+process.evAnalyzer)

# message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('/tmp/psilva/tmp.root'),
                               outputCommands = cms.untracked.vstring('keep *'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') )
                               )
process.e = cms.EndPath(process.out)
