import FWCore.ParameterSet.Config as cms
from CMGTools.External.JetIdParams_cfi import *

####################################################################################################################  
full_5x = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/TMVAClassification_5x_BDT_fullPlusRMS.weights.xml"),
 tmvaMethod  = cms.string("BDT_fullPlusRMS"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "dR2Mean",
    "nvtx",
    "nNeutrals",
    "beta",
    "betaStar",
    "dZ",
    "nCharged",
    ),
 tmvaSpectators = cms.vstring(
    "jetPt",
    "jetEta",
    ),
 JetIdParams = full_5x_wp,
 label = cms.string("full")
 )

####################################################################################################################  
simple_5x = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/TMVAClassification_5x_BDT_simpleNoVtxCat.weights.xml"),
 tmvaMethod  = cms.string("BDT_simpleNoVtxCat"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "nvtx",
    "beta",
    "betaStar",
    ),
 tmvaSpectators = cms.vstring(
    "jetPt",
    "jetEta",
    ),
 JetIdParams = simple_5x_wp,
 label = cms.string("simple")
 )

####################################################################################################################  
full = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/TMVAClassification_PuJetIdOptMVA.weights.xml"),
 tmvaMethod  = cms.string("PuJetIdOptMVA"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "nvtx",
    "nNeutrals",
    "beta",
    "betaStar",
    "dZ",
    "nCharged",
    ),
 tmvaSpectators = cms.vstring(
    "jetPt",
    "jetEta",
    ),
 JetIdParams = PuJetIdOptMVA_wp,
 label = cms.string("full")
 )

####################################################################################################################  
simple = cms.PSet( 
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/TMVAClassification_PuJetIdMinMVA.weights.xml"),
 tmvaMethod  = cms.string("PuJetIdMinMVA"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    "beta",
    "betaStar",
    ),
 tmvaSpectators = cms.vstring(
    "nvtx",
    "jetPt",
    "jetEta",
    ),
 JetIdParams = PuJetIdMinMVA_wp,
 label = cms.string("simple")
 )
####################################################################################################################  
cutbased = cms.PSet( 
 impactParTkThreshold = cms.double(1.) ,
 JetIdParams = PuJetIdCutBased_wp,
 label = cms.string("cutbased")
 )

####################################################################################################################  
PhilV0 = cms.PSet( 
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/mva_JetID.weights.xml"),
 tmvaMethod  = cms.string("JetID"),
 version = cms.int32(0),
 JetIdParams = EmptyJetIdParams
)


####################################################################################################################  
PhilV1 = cms.PSet(
 impactParTkThreshold = cms.double(1.) ,
 tmvaWeights = cms.string("CMGTools/External/data/mva_JetID_v1.weights.xml"),
 tmvaMethod  = cms.string("JetID"),
 version = cms.int32(-1),
 tmvaVariables = cms.vstring(
    "nvtx",
    "jetPt",
    "jetEta",
    "jetPhi",
    "dZ",
    "d0",
    "beta",
    "betaStar",
    "nCharged",
    "nNeutrals",
    "dRMean",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "frac05",
    ),
 tmvaSpectators = cms.vstring(),
 JetIdParams = JetIdParams,
 label = cms.string("philv1")
 )

