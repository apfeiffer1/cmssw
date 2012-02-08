import operator 
from CMGTools.RootTools.fwlite.Analyzer import Analyzer
from CMGTools.RootTools.statistics.Counter import Counter, Counters
from CMGTools.RootTools.fwlite.AutoHandle import AutoHandle
from CMGTools.RootTools.physicsobjects.DiObject import DiObject
from CMGTools.RootTools.physicsobjects.PhysicsObjects import Lepton

class DiLeptonAnalyzer( Analyzer ):

    # The DiObject class will be used as the di-object class
    # and the Lepton class as the lepton class
    # Child classes override this choice, and can e.g. decide to use
    # the TauMuon class as a di-object class
    # ... not sure other people can understand this comment ;-)
    DiObjectClass = DiObject
    LeptonClass = Lepton 

    def beginLoop(self):
        super(DiLeptonAnalyzer,self).beginLoop()
        self.counters.addCounter('DiLepton')
        
    def process(self, iEvent, event):
        # access di-object collection
        # test first leg
        # test second leg
        # test di-lepton
        # apply lepton veto
        # choose best di-lepton
        # put in the event
        self.readCollections( iEvent )
        # trigger stuff could be put in a separate analyzer
        # event.triggerObject = self.handles['cmgTriggerObjectSel'].product()[0]
        event.diLeptons = map( self.__class__.DiObjectClass, self.handles['diLeptons'].product() )
        event.leptons = map( self.__class__.LeptonClass, self.handles['leptons'].product() ) 

        self.counters.counter('DiLepton').inc('all events ')
        # if not self.triggerList.triggerPassed(event.triggerObject):
        #    return False
        # self.counters.counter('DiLepton').inc('trigger passed ')
            
        if len(event.diLeptons) == 0:
            return False
        self.counters.counter('DiLepton').inc('> 0 di-lepton ')
        if not self.leptonAccept( event.leptons ):
            return False
        self.counters.counter('DiLepton').inc('lepton accept ')

        # testing leg1
        selDiLeptons = [ diL for diL in event.diLeptons if \
                         self.testLeg1( diL.leg1() ) ]
        if len(selDiLeptons) == 0:
            return False
        else:
            self.counters.counter('DiLepton').inc('leg 1 ok.')

        # testing leg2 
        selDiLeptons = [ diL for diL in event.diLeptons if \
                         self.testLeg2( diL.leg2() ) ]
        if len(selDiLeptons) == 0:
            return False
        else:
            self.counters.counter('DiLepton').inc('leg 2 ok.')

        # testing di-lepton itself 
        selDiLeptons = self.selectDiLeptons( selDiLeptons ) 
        if len(selDiLeptons)==0:
            return False
        elif len(selDiLeptons)==1:
            self.counters.counter('DiLepton').inc('exactly 1 di-lepton')
        
        event.diLepton = self.bestDiLepton( selDiLeptons )
        event.leg1 = event.diLepton.leg1()
        event.leg2 = event.diLepton.leg2()

        mass = event.diLepton.mass()
        if self.cfg_ana.m_min < mass and mass < self.cfg_ana.m_max:
            self.counters.counter('DiLepton').inc(
                '{min:3.1f} < m < {max:3.1f}'.format( min = self.cfg_ana.m_min,
                                                          max = self.cfg_ana.m_max )
                )
        else:
            return False
        return True


    def declareHandles(self):        
        super(DiLeptonAnalyzer, self).declareHandles()
        self.handles['cmgTriggerObjectSel'] =  AutoHandle(
            'cmgTriggerObjectSel',
            'std::vector<cmg::TriggerObject>'
            )

    
    def leptonAccept(self, leptons):
        '''Should implement a default version running on event.leptons.'''
        return True


    def selectDiLeptons(self, diLeptons, cutString=None):
        '''Returns the list of input di-leptons which verify the cutstring'''
        if cutString is None:
            if not hasattr( self.cfg_ana, 'diLeptonCutString' ):
                return diLeptons
            else:
                cutString = self.cfg_ana.diLeptonCutString 
        selDiLeptons = [ diL for diL in diLeptons if \
                         diL.getSelection(cutString) ]
        if len(selDiLeptons) > 0:
            self.counters.counter('DiLepton').inc( 'di-lepton {cut} ok'.format(
                cut=cutString
                ) )
        return selDiLeptons


    def testLeg(self, leg, pt, eta, iso):
        if leg.pt()>pt and \
           abs(leg.eta())<eta and \
           leg.relIso( 0.5 ) < iso:
            return True
        else:
            return False

    
    def testLeg1(self, leg):
        '''Overload according to type, see e.g. TauMuAnalyzer.'''
        return self.testLeg( leg,
                             pt = self.cfg_ana.pt1,
                             eta = self.cfg_ana.eta1,
                             iso = self.cfg_ana.iso1 )


    def testLeg2(self, leg):
        '''Overload according to type, see e.g. TauMuAnalyzer.'''
        return self.testLeg( leg,
                             pt = self.cfg_ana.pt2,
                             eta = self.cfg_ana.eta2,
                             iso = self.cfg_ana.iso2 )
        

    def testMuon(self, muon):
        '''Returns True if a muon passes a set of cuts.
        Can be used in testLeg1 and testLeg2, in child classes.'''
        return True

    
    def testElectron(self, electron):
        '''Returns True if an electron passes a set of cuts.
        Can be used in testLeg1 and testLeg2, in child classes.'''
        return True


    def testTau(self, tau):
        '''Returns True if a tau passes a set of cuts.
        Can be used in testLeg1 and testLeg2, in child classes.

        WARNING: the muon filter should be used only in the muon channel.'''
        return True

    
    def bestDiLepton(self, diLeptons):
        '''Returns the best diLepton (the one with highest pt1 + pt2).'''
        return max( diLeptons, key=operator.methodcaller( 'sumPt' ) )
    
