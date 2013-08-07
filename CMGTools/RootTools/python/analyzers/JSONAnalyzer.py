import json
from CMGTools.RootTools.fwlite.Analyzer import Analyzer

from FWCore.PythonUtilities.LumiList import LumiList
from CMGTools.RootTools.utils.RLTInfo import RLTInfo


class JSONAnalyzer( Analyzer ):
    '''Apply a json filter, and creates an RLTInfo TTree.
    See CMGTools.RootTools.utils.RLTInfo for more information

    example:
    
    jsonFilter = cfg.Analyzer(
      "JSONAnalyzer",
      )

    The path of the json file to be used is set as a component attribute.

    The process function returns:
      - True if
         - the component is MC or
         - if the run/lumi pair is in the JSON file
         - if the json file was not set for this component
      - False if the component is MC or embed (for H->tau tau),
          and if the run/lumi pair is not in the JSON file.
    '''

    def __init__(self, cfg_ana, cfg_comp, looperName):
        super(JSONAnalyzer, self).__init__(cfg_ana, cfg_comp, looperName)
        if not cfg_comp.isMC:
            if self.cfg_comp.json is None:
                raise ValueError('component {cname} is not MC, and contains no JSON file. Either remove the JSONAnalyzer for your path or set the "json" attribute of this component'.format(cname=cfg_comp.name))
            self.lumiList = LumiList(self.cfg_comp.json)
        else:
            self.lumiList = None
        

        self.rltInfo = RLTInfo()


    def beginLoop(self):
        super(JSONAnalyzer,self).beginLoop()
        self.counters.addCounter('JSON')
        self.count = self.counters.counter('JSON')
        self.count.register('All Lumis')
        self.count.register('Passed Lumis')

    def process(self, iEvent, event):
        self.readCollections( iEvent )
        run = iEvent.eventAuxiliary().id().run()
        lumi = iEvent.eventAuxiliary().id().luminosityBlock()
        eventId = iEvent.eventAuxiliary().id().event()

        event.run = run
        event.lumi = lumi
        event.eventId = eventId

        if self.cfg_comp.isMC:
            return True

        if self.lumiList is None:
            return True

        self.count.inc('All Lumis')
        if self.lumiList.contains(run,lumi):
            self.count.inc('Passed Lumis')
            self.rltInfo.add('dummy', run, lumi)
            return True
        else:
            return False
        

    def write(self):
        super(JSONAnalyzer, self).write()
        self.rltInfo.write( self.dirName )

