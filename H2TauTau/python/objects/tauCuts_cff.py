import FWCore.ParameterSet.Config as cms

tauCuts = cms.PSet(
    kinematics = cms.PSet(
      pt = cms.string('leg1().pt()>20'),
      eta = cms.string('abs(leg1().eta())<2.3')
    ),
    id = cms.PSet(
      decay = cms.string('leg1().tauID("decayModeFinding")'),
      muVeto = cms.PSet(
        tight = cms.string('leg1().tauID("againstMuonTight")'),
        calo = cms.string('(leg1().leadChargedHadrECalEnergy() + leg1().leadChargedHadrHCalEnergy()) * sin( leg1().theta() ) / leg1().leadChargedHadrPt()')
      ),
      eVeto = cms.string('leg1().tauID("againstElectronLoose")')
      ),
    iso = cms.string('leg1().tauID("byLooseCombinedIsolationDeltaBetaCorr")')
    )

