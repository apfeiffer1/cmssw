from ROOT import TTree, TH1F, TH2F, TProfile, gDirectory

#COLIN need a base histogram class
class VertexHistograms:
    def __init__(self, name ):
        self.name = name

        self.h_nvertices = TH1F(name+'_h_nvertices', ';# vertices',
                                25,0,25)

        self.hists = []
        self.hists.append( self.h_nvertices )
        
    def fillVertices(self, vertices, weight=1):
        self.h_nvertices.Fill( len(vertices), weight)
        
    def formatHistos(self, style ):
        for hist in self.hists:
            style.formatHisto( hist )
            
    def Write(self, dir ):
        self.dir = dir.mkdir( self.name )
        self.dir.cd()
        for hist in self.hists:
            hist.Write()
        dir.cd()
