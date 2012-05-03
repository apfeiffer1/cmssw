import FWCore.ParameterSet.Config as cms

from CMGTools.External.puJetIDAlgo_cff import PhilV1, full, simple, cutbased, full_5x, simple_5x

stdalgos_4x = cms.VPSet(simple,   full,   cutbased)
stdalgos_5x = cms.VPSet(simple_5x,full_5x,cutbased)
stdalgos    = stdalgos_5x

pileupJetIdProducer = cms.EDProducer('PileupJetIdProducer',
                         produceJetIds = cms.bool(True),
                         jetids = cms.InputTag(""),
                         runMvas = cms.bool(True),
                         jets = cms.InputTag("selectedPatJetsPFlow"),
                         vertexes = cms.InputTag("offlinePrimaryVertices"),
                         algos = cms.VPSet(stdalgos)
)

