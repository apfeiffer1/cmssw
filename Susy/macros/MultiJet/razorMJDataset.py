#!/usr/bin/env python

import ROOT as rt
from ROOT import std
import os, sys, math, glob, pickle
from DataFormats.FWLite import Events, Handle
from CMGTools.RootTools import RootFile
from razorMJTopTag import topTag
from histoSMSTree import getBoxGenLevel, getBox

def listDirectory(dir, inputFiles, maxFiles):
    if not os.path.exists(dir):
        raise Exception("The directory '%s' does not exist" % dir)
    files = glob.glob('%s/*.root' % dir)
    if len(files) > maxFiles:
        files = files[:maxFiles]
    inputFiles.extend(files)
    return len(files)

def getFiles(datasets, user, pattern):
    
    from CMGTools.Production.datasetToSource import datasetToSource

    files = []
    for d in datasets:
        ds = datasetToSource(
                             user,
                             d,
                             pattern
                             )
        files.extend(ds.fileNames)

    return ['root://eoscms//eos/cms%s' % f for f in files]

def deltaR(a,b):
    deta = a.eta() - b.eta()
    dphi = a.phi() - b.phi()
    dr = deta*deta + dphi*dphi
    return math.sqrt(dr)

def mt(l1, l2):
    c = l1.p4() + l2.p4()
    t = (l1.pt()+l2.pt())**2
    x = (l1.px()+l2.px())**2
    y = (l1.py()+l2.py())**2
    s = t - x - y
    if s < 0:
        return -1*math.sqrt(abs(s))
    return math.sqrt(s)

def find_lepton_hemi(hemi_vector, leptons, best = None):
    """Find the best hemispheres that have the lepton on one side and at least 3 jets on the other"""

    for i in xrange(0,len(hemi_vector),2):
        
        hemi1 = hemi_vector.at(i)
        hemi2 = hemi_vector.at(i+1)
        
        nHemi1 = hemi1.numConstituents()
        nHemi2 = hemi2.numConstituents()
        
        for j in hemi1.sourcePtrs():
            for l in leptons:
                if deltaR(j,l) < 0.4:
                    nHemi1 -= 1
        for j in hemi2.sourcePtrs():
            for l in leptons:
                if deltaR(j,l) < 0.4:
                    nHemi2 -= 1

        #break out with the first hemi pair that is ok
        if (hemi1.numConstituents() >= 3 and nHemi1 == hemi1.numConstituents() and (best is None or best == 1) ):#can specify which must be hadronic side
            return (hemi1, hemi2, 1) #hemi 1 is the hadronic side
        elif (hemi2.numConstituents() >= 3 and nHemi2 == hemi2.numConstituents() and (best is None or best == 2) ):
            return (hemi1, hemi2, 2) #hemi 2 is the hadronic side
        
    return (None, None, -1)
    

if __name__ == '__main__':

    skimEvents = True
    runOnMC = False

    # https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideAboutPythonConfigFile#VarParsing_Example
    from FWCore.ParameterSet.VarParsing import VarParsing
    options = VarParsing ('python')
    options.outputFile = None
    options.register ('inputDirectory',
                  None, # default value
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.string,          # string, int, or float
                  "A directory to read root files from")
    options.register ('outputDirectory',
                  '.', # default value
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.string,          # string, int, or float
                  "A directory to write root files to")
    options.register ('datasetName',
                  None,
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.string,          # string, int, or float
                  "A directory to read root files from")
    options.register ('maxFiles',
                  -1, # default value
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.int,          # string, int, or float
                  "The maximum number of files to read")
    options.register ('index',
                  -1, # default value
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.int,          # string, int, or float
                  "The file index to run on")
    options.register ('model',
                  None,
                  VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.varType.string,          # string, int, or float
                  "The SMS model to use in the error calculation")

    
    options.parseArguments()
    if not options.inputFiles:
        if options.inputDirectory is not None:
            listDirectory(options.inputDirectory, options.inputFiles, options.maxFiles)
        
        if True:
            names = [f for f in options.datasetName.split('/') if f]
            if runOnMC:
                options.model = names[0].split('-')[1].split('_')[0]
            if options.index < 0:
                name = '%s-%s-%s.root' % (names[0],names[1],names[-1])
            else:
                name = '%s-%s-%s_%d.root' % (names[0],names[1],names[-1],options.index)
            options.outputFile = os.path.join(options.outputDirectory,name)
            print options.outputFile
        
        files = getFiles(
            [options.datasetName],
            'wreece',
            'susy_tree_CMG_[0-9]+.root'                
            )
        if options.maxFiles > 0:
            options.inputFiles = files[0:options.maxFiles]
        else:
            options.inputFiles = files
        print 'The number of files to run on is: %d' % len(files)

    if options.index > -1:
        chunks = []
        chunk = []
        for f in files:
            if len(chunk) <= options.maxFiles:
                chunk.append(f)
            if len(chunk) == options.maxFiles:
                chunks.append(chunk)
                chunk = []
        print 'Created %d chunks of length %s' % (len(chunks),options.maxFiles)
        options.inputFiles = chunks[options.index]
    
    pickleFile = options.outputFile.replace('.root','.pkl')

    rt.gROOT.ProcessLine("""
struct Variables{\
    Double_t MR;\
    Double_t MR_JES_UP;\
    Double_t MR_JES_DOWN;\
    Double_t RSQ;\
    Double_t RSQ_JES_UP;\
    Double_t RSQ_JES_DOWN;\
    Double_t met;\
    Double_t met_up;\
    Double_t met_down;\
    Double_t hemi1Mass;\
    Double_t hemi2Mass;\
    Double_t hemi1TopMass;\
    Double_t hemi1WMass;\
    Double_t hemi1ThetaH;\
    Double_t hemi2TopMass;\
    Double_t hemi2WMass;\
    Double_t hemi2ThetaH;\
    Double_t mStop;\
    Double_t mLSP;\
    Double_t diTopPt;\
    Double_t hemi1Pt;\
    Double_t hemi2Pt;\
    Double_t hemi1Eta;\
    Double_t hemi2Eta;\
    Double_t hemi1Phi;\
    Double_t hemi2Phi;\
};""")
    
    rt.gROOT.ProcessLine("""
struct Info{\
    Int_t event;\
    Int_t run;\
    Int_t lumi;\
    Int_t nJet;\
    Int_t nJetNoLeptons;\
    Int_t nCSVL;\
    Int_t nCSVM;\
    Int_t nCSVT;\
    Int_t NBJET;\
    Int_t nMuonLoose;\
    Int_t nMuonTight;\
    Int_t nElectronLoose;\
    Int_t nElectronTight;\
    Int_t nTauVeto;\
    Int_t nTauLoose;\
    Int_t nTauTight;\
    Int_t nLepton;\
    Int_t hemisphereBalance;\
    Int_t hemi1Count;\
    Int_t hemi2Count;\
    Int_t genInfo;\
    Int_t BOX_NUM;\
    Int_t BOX_NUM_GEN;\
    Int_t bestHemi;\
};""")
    
    rt.gROOT.ProcessLine("""
struct Filters{\
    Bool_t hadBoxFilter;\
    Bool_t eleBoxFilter;\
    Bool_t muBoxFilter;\
    Bool_t tauBoxFilter;\
    Bool_t eleTriggerFilter;\
    Bool_t hadTriggerFilter;\
    Bool_t muTriggerFilter;\
    Bool_t metFilter;\
};""")

    rt.gROOT.ProcessLine(".L /afs/cern.ch/user/w/wreece/work/CMGTools/V5_6_0/CMGTools/CMSSW_5_3_3_patch3/src/CMGTools/Susy/macros/MultiJet/calcVariables.C+")

    from ROOT import Variables, Info, Filters, mR, mRT

#    output = rt.TFile.Open(options.outputFile,'recreate')
    tree = rt.TTree('RMRTree','Multijet events')
    tree.SetDirectory(0)
    def setAddress(obj, flag):
        for branch in dir(obj):
            if branch.startswith('__'): continue
            tree.Branch(branch,rt.AddressOf(obj,branch),'%s/%s' % (branch,flag) )
    
    filters = Filters()
    info = Info()
    vars = Variables()
    
    setAddress(filters,'O')
    setAddress(info,'I')
    setAddress(vars,'D')

    CTEQ66_W = std.vector('double')()
    MRST2006NNLO_W = std.vector('double')()
    tree.Branch('CTEQ66_W',CTEQ66_W)
    tree.Branch('MRST2006NNLO_W',MRST2006NNLO_W)

    jet_pt = std.vector('double')()
    tree.Branch('jet_pt',jet_pt)
    jet_eta = std.vector('double')()
    tree.Branch('jet_eta',jet_eta)
    jet_phi = std.vector('double')()
    tree.Branch('jet_phi',jet_phi)
    jet_csv = std.vector('double')()
    tree.Branch('jet_csv',jet_csv)
    jet_fl = std.vector('double')()
    tree.Branch('jet_fl',jet_fl)
    jet_mult = std.vector('double')()
    tree.Branch('jet_mult',jet_mult)
    jet_girth = std.vector('double')()
    tree.Branch('jet_girth',jet_girth)

    tauveto_mt = std.vector('double')()
    tree.Branch('tauveto_mt',tauveto_mt)
    pftau_mt = std.vector('double')()
    tree.Branch('pftau_mt',pftau_mt)

    jet_veto = std.vector('int')()
    tree.Branch('jet_veto',jet_veto)

    # use Varparsing object
    events = Events(options)
    
    #make some handles
    jetSel30H = Handle("std::vector<cmg::PFJet>")
    hemiHadH = Handle("std::vector<cmg::DiObject<cmg::Hemisphere, cmg::Hemisphere> >")
    hemiLepH = Handle("std::vector<cmg::Hemisphere>")
    metH = Handle("std::vector<cmg::BaseMET>")
    lheH = Handle('LHEEventProduct')
    pdfH = Handle('std::vector<double>')
    candH = Handle("std::vector<reco::LeafCandidate>")

    electronH = Handle("std::vector<cmg::Electron>")
    muonH = Handle("std::vector<cmg::Muon>")
    tauH = Handle("std::vector<cmg::Tau>")
    
    triggerH = Handle('std::vector<cmg::TriggerObject>')
    countH = Handle('int')
    filterH = Handle('int')
    doubleH = Handle('std::vector<double>')
    
    pathTriggerH = Handle("edm::TriggerResults")
    lheH = Handle('LHEEventProduct')

    store = RootFile.RootFile(options.outputFile)
    store.add(tree)

    count = 0
    #for storing the counts of each model point
    bins = {}

    # loop over events
    for event in events:

        CTEQ66_W.clear()
        MRST2006NNLO_W.clear()
        
        jet_pt.clear()
        jet_eta.clear()
        jet_phi.clear()
        jet_csv.clear()
        jet_fl.clear()
        jet_mult.clear()
        jet_girth.clear()
        jet_veto.clear()

        tauveto_mt.clear()
        pftau_mt.clear()

        info.event = event.object().id().event()
        info.lumi = event.object().id().luminosityBlock()
        info.run = event.object().id().run()

        if (count % 1000) == 0:
            print count,'run/lumi/event',info.run,info.lumi,info.event
            tree.AutoSave()
        count += 1    

        #get the LHE product info
        vars.mStop = -1
        vars.mLSP = -1
        if runOnMC:
            event.getByLabel(('source'),lheH)
            if lheH.isValid():
                lhe = lheH.product()
                for i in xrange(lhe.comments_size()):
                    comment = lhe.getComment(i)
                    if 'model' not in comment: continue
                    comment = comment.replace('\n','')
                    parameters = comment.split(' ')[-1]
                    masses = map(float,parameters.split('_')[-2:])
                    vars.mStop = masses[0]
                    vars.mLSP = masses[1]

        #store how many of each model we see
        point = (vars.mStop,vars.mLSP)
        if bins.has_key(point):
            bins[point] = bins[point] + 1
        else:
            bins[point] = 1

        event.getByLabel(('TriggerResults','','MJSkim'),pathTriggerH)
        pathTrigger = pathTriggerH.product()
        pathTriggerNames = event.object().triggerNames(pathTrigger)

        #start by vetoing events that didn't pass the offline selection
        filters.hadBoxFilter = pathTrigger.accept(pathTriggerNames.triggerIndex('razorMJSkimSequenceHadPath'))
        filters.eleBoxFilter = pathTrigger.accept(pathTriggerNames.triggerIndex('razorMJSkimSequenceElePath'))
        filters.muBoxFilter = pathTrigger.accept(pathTriggerNames.triggerIndex('razorMJSkimSequenceMuPath'))
        filters.tauBoxFilter = pathTrigger.accept(pathTriggerNames.triggerIndex('razorMJSkimSequenceTauPath'))  
        path = filters.hadBoxFilter or filters.muBoxFilter or filters.eleBoxFilter or filters.tauBoxFilter
        if skimEvents and not path: continue

        #also get the MET filter
        event.getByLabel(('TriggerResults','','PAT'),pathTriggerH)
        pathTrigger = pathTriggerH.product()
        pathTriggerNames = event.object().triggerNames(pathTrigger)
        filters.metFilter = pathTrigger.accept(pathTriggerNames.triggerIndex('metNoiseCleaningPath'))

        event.getByLabel(('razorMJDiHemiHadBox'),hemiHadH)
        if hemiHadH.isValid() and len(hemiHadH.product()):
            hemi = hemiHadH.product()[0]
            vars.RSQ = hemi.Rsq()
            vars.MR = hemi.mR()
            vars.hemi1Mass = hemi.leg1().mass()
            vars.hemi2Mass = hemi.leg2().mass()
            info.hemisphereBalance = (10*hemi.leg1().numConstituents()) + hemi.leg2().numConstituents()

            #run the hadronic top tagger
            info.hemi1Count, vars.hemi1TopMass, vars.hemi1WMass, vars.hemi1ThetaH = topTag( hemi.leg1() )
            info.hemi2Count, vars.hemi2TopMass, vars.hemi2WMass, vars.hemi2ThetaH = topTag( hemi.leg2() )
            
            #calculate a chi2
            chi1 = (abs(vars.hemi1TopMass-173.5)/57.)+(abs(vars.hemi1WMass-80.385)/44.)
            chi2 = (abs(vars.hemi2TopMass-173.5)/57.)+(abs(vars.hemi2WMass-80.385)/44.)
            if chi1 <= chi2:
                info.bestHemi = 1
            else:
                info.bestHemi = 2

            vars.hemi1Pt = hemi.leg1().pt()
            vars.hemi1Eta = hemi.leg1().eta()
            vars.hemi1Phi = hemi.leg1().phi()
            vars.hemi2Pt = hemi.leg2().pt()
            vars.hemi2Eta = hemi.leg2().eta()
            vars.hemi2Phi = hemi.leg2().phi()

                        
        event.getByLabel(('razorMJDiHemiHadBoxUp'),hemiHadH)
        if hemiHadH.isValid() and len(hemiHadH.product()):
            hemi = hemiHadH.product()[0]
            vars.RSQ_JES_UP = hemi.Rsq()
            vars.MR_JES_UP = hemi.mR()

        event.getByLabel(('razorMJDiHemiHadBoxDown'),hemiHadH)
        if hemiHadH.isValid() and len(hemiHadH.product()):
            hemi = hemiHadH.product()[0]
            vars.RSQ_JES_DOWN = hemi.Rsq()
            vars.MR_JES_DOWN = hemi.mR()

        event.getByLabel(('razorMJHadTriggerSel'),triggerH)
        filters.hadTriggerFilter = len(triggerH.product()) > 0
        
        event.getByLabel(('razorMJEleTriggerSel'),triggerH)
        filters.eleTriggerFilter = len(triggerH.product()) > 0

        event.getByLabel(('razorMJMuTriggerSel'),triggerH)
        filters.muTriggerFilter = len(triggerH.product()) > 0
        
        #the number of lepton cleaned jets
        event.getByLabel(('razorMJJetCleanedLoose'),jetSel30H)
        info.nJetNoLeptons = len(jetSel30H.product())
        jet_param_veto = [ (j.pt(), j.eta()) for j in jetSel30H.product()]

        event.getByLabel(('razorMJPFJetSel30'),jetSel30H)
        if not jetSel30H.isValid(): continue
        jets = jetSel30H.product()
        info.nJet = len(jets)

        event.getByLabel(('razorMJJetGirth'),doubleH)
        if doubleH.isValid():
            for g in doubleH.product():
                #girth
                jet_girth.push_back(g)
        
        for jet in jets:
            jet_pt.push_back(jet.pt())
            jet_eta.push_back(jet.eta())
            jet_phi.push_back(jet.phi())
            jet_csv.push_back(jet.btag(6))
            jet_fl.push_back(jet.partonFlavour())
            #charged multiplicity
            jet_mult.push_back(jet.component(1).number() + jet.component(2).number() + jet.component(3).number() )
            #store whether or not this was removed from the lepton veto jets
            jet_veto.push_back( int( (jet.pt(), jet.eta() ) in jet_param_veto) )

        #store the number of btags at each working point
        csv = sorted([j.btag(6) for j in jets], reverse=True)
        info.nCSVL = len([c for c in csv if c >= 0.244])
        info.nCSVM = len([c for c in csv if c >= 0.679])
        info.nCSVT = len([c for c in csv if c >= 0.898])

        event.getByLabel(('cmgPFMET'),metH)
        met = metH.product()[0]
        vars.met = met.et()

        #set the number of btags
        if info.nCSVL == 0:
            info.NBJET = 0 #bjet veto
        else:
            info.NBJET = info.nCSVM #minimum is one medium

        #tau veto
        event.getByLabel(('razorMJTauVeto'),jetSel30H)
        if jetSel30H.isValid():
            info.nTauVeto = len(jetSel30H.product())
            for j in jets:
                tauveto_mt.push_back(mt(j,met))
        else:
            info.nTauVeto = -1

        #loose lepton ID
        event.getByLabel(('razorMJElectronLoose'),electronH)
        event.getByLabel(('razorMJMuonLoose'),muonH)
        event.getByLabel(('razorMJTauLoose'),tauH)
        #
        info.nElectronLoose = len(electronH.product())
        info.nMuonLoose = len(muonH.product())
        info.nTauLoose = len(tauH.product())
        
        for t in tauH.product():
            pftau_mt.push_back(mt(t,met))

        #tight lepton ID
        event.getByLabel(('razorMJElectronTight'),electronH)
        event.getByLabel(('razorMJMuonTight'),muonH)
        event.getByLabel(('razorMJTauTight'),tauH)
        #
        info.nElectronTight = len(electronH.product())
        info.nMuonTight = len(muonH.product())
        info.nTauTight = len(tauH.product())
        info.nLepton = info.nElectronTight + info.nMuonTight + info.nTauTight
        
        #store the leptons for future use
        leptons = [l for l in electronH.product()]
        leptons.extend([l for l in muonH.product()])
        leptons.extend([l for l in tauH.product()])

        info.BOX_NUM = getBox(info.NBJET,info.nElectronTight,info.nMuonTight,info.nTauTight)

        if info.nLepton == 1 and info.nJetNoLeptons >= 4:
            event.getByLabel(('razorMJHemiLepBox'),hemiLepH)
            if hemiLepH.isValid():
                hemi_vector = hemiLepH.product()
                hemi1, hemi2, info.bestHemi = find_lepton_hemi(hemi_vector, leptons)

                vars.MR = mR(hemi1.p4(), hemi2.p4())
                mrt = mRT(hemi1.p4(), hemi2.p4(), met.p4())
                vars.RSQ = (mrt/vars.MR)**2

                vars.hemi1Mass = hemi1.mass()
                vars.hemi2Mass = hemi2.mass()
                info.hemisphereBalance = (10*hemi1.numConstituents()) + hemi2.numConstituents()
                
                #run the hadronic top tagger
                info.hemi1Count, vars.hemi1TopMass, vars.hemi1WMass, vars.hemi1ThetaH = topTag( hemi1 )
                info.hemi2Count, vars.hemi2TopMass, vars.hemi2WMass, vars.hemi2ThetaH = topTag( hemi2 )

                vars.hemi1Pt = hemi1.pt()
                vars.hemi1Eta = hemi1.eta()
                vars.hemi1Phi = hemi1.phi()
                vars.hemi2Pt = hemi2.pt()
                vars.hemi2Eta = hemi2.eta()
                vars.hemi2Phi = hemi2.phi()

                #now need to take care of the systematics...
                #UP
                event.getByLabel(('razorMJMetUp'),metH)
                met = metH.product()[0]
                event.getByLabel(('razorMJHemiLepBoxUp'),hemiLepH)
                if hemiLepH.isValid():
                    hemi_vector = hemiLepH.product()
                    hemi1, hemi2, _ = find_lepton_hemi(hemi_vector, leptons)
                    if hemi1 is None or hemi2 is None:
                        vars.MR_JES_UP = vars.MR
                        vars.RSQ_JES_UP = vars.RSQ
                    else:
                        vars.MR_JES_UP = mR(hemi1.p4(), hemi2.p4())
                        mrt = mRT(hemi1.p4(), hemi2.p4(), met.p4())
                        vars.RSQ_JES_UP = (mrt/vars.MR_JES_UP)**2

                #DOWN
                event.getByLabel(('razorMJMetDown'),metH)
                met = metH.product()[0]
                event.getByLabel(('razorMJHemiLepBoxDown'),hemiLepH)
                if hemiLepH.isValid():
                    hemi_vector = hemiLepH.product()
                    hemi1, hemi2, _ = find_lepton_hemi(hemi_vector, leptons, best=info.bestHemi)
                    if hemi1 is None or hemi2 is None:
                        vars.MR_JES_DOWN = vars.MR
                        vars.RSQ_JES_DOWN = vars.RSQ
                    else:
                        vars.MR_JES_DOWN = mR(hemi1.p4(), hemi2.p4())
                        mrt = mRT(hemi1.p4(), hemi2.p4(), met.p4())
                        vars.RSQ_JES_DOWN = (mrt/vars.MR_JES_DOWN)**2

        event.getByLabel(('razorMJMetUp'),metH)
        met = metH.product()[0]
        vars.met_up = met.et()

        event.getByLabel(('razorMJMetDown'),metH)
        met = metH.product()[0]
        vars.met_down = met.et()

        #event.getByLabel(('vertexSize'),countH)
        #info.nVertex = countH.product()[0]

##        #dump the PDF weights
##        Event.getByLabel(('dumpPdfWeights','cteq66'),pdfH)
##        if pdfH.isValid():
##            for w in pdfH.product():
##                CTEQ66_W.push_back(w)
##        event.getByLabel(('dumpPdfWeights','MRST2006nnlo'),pdfH)
##        if pdfH.isValid():
##            for w in pdfH.product():
##                MRST2006NNLO_W.push_back(w)
        
        if runOnMC:
            event.getByLabel(('topGenInfo'),candH)
            if options.model is not None and candH.isValid() and len(candH.product()):
                if 'T2' in options.model:
                    diTop = candH.product()[1]
                elif 'T1' in options.model:
                    diTop = candH.product()[2]
                else:
                    diTop = candH.product()[0]
                vars.diTopPt = diTop.pt()

        
            event.getByLabel(('simpleGenInfo'),filterH)
            if filterH.isValid():
                info.genInfo = filterH.product()[0]
                info.BOX_NUM_GEN = getBoxGenLevel(info.genInfo)

        #TODO: Place some cut here
        if skimEvents and vars.RSQ < 0.03 or vars.MR < 350:
            continue

        tree.Fill()

#    tree.SetDirectory(output)
#    tree.Write()
#    output.Close()
    store.write()

    sample_counts = file(options.outputFile.replace('.root','.pkl'),'wb')
    pickle.dump(bins,sample_counts)
    sample_counts.close()
    
