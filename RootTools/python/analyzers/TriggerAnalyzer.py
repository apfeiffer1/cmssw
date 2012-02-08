from CMGTools.RootTools.fwlite.Analyzer import Analyzer
from CMGTools.RootTools.fwlite.AutoHandle import AutoHandle
from CMGTools.RootTools.statistics.Counter import Counter
from CMGTools.RootTools.fwlite.TriggerList import TriggerList

class TriggerAnalyzer( Analyzer ):
    '''Analyze vertices, add weight to MC events'''

    def declareHandles(self):
        super(TriggerAnalyzer, self).declareHandles()

        self.handles['cmgTriggerObjectSel'] =  AutoHandle(
            'cmgTriggerObjectSel',
            'std::vector<cmg::TriggerObject>'
            )

    def beginLoop(self):
        super(TriggerAnalyzer,self).beginLoop()
        self.triggerList = TriggerList( self.cfg_comp.triggers )
        self.counters.addCounter('Trigger')

    def process(self, iEvent, event):
        self.readCollections( iEvent )
        event.triggerObject = self.handles['cmgTriggerObjectSel'].product()[0]
        
        self.counters.counter('Trigger').inc('All events')
        if not self.triggerList.triggerPassed(event.triggerObject):
            return False
        self.counters.counter('Trigger').inc('trigger passed ')
        return True

    def __str__(self):
        tmp = super(TriggerAnalyzer,self).__str__()
        triglist = str( self.triggerList )
        return '\n'.join( [tmp, triglist ] )
