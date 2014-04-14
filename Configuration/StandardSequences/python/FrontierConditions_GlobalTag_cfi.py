import FWCore.ParameterSet.Config as cms

from CondCore.DBCommon.CondDBSetup_cfi import *

gtDbName = 'oracle://cms_orcoff_prep/CMS_CONDITIONS'
print "CondDB setup to read GT from : ", gtDbName

GlobalTag = cms.ESSource("PoolDBESSource",
    CondDBSetup,
    connect = cms.string(gtDbName),
    globaltag = cms.string('UNSPECIFIED'),
    toGet = cms.VPSet( ),   # hook to override or add single payloads
)
