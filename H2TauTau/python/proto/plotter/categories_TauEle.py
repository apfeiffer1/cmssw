import copy

from CMGTools.H2TauTau.proto.plotter.jetcategories import *
from CMGTools.H2TauTau.proto.plotter.cut import *

Te_inc_sig_tau = Cut('l1_looseMvaIso>0.5 && (l1_EOverp>0.2 || l1_decayMode!=0) && l1_byLooseIsoMVA > 0.5 && l1_againstElectronMVA > 0.5 && l1_againstElectronMedium > 0.5 && l1_againstMuonLoose > 0.5 && l1_dxy<0.045 && l1_dz<0.2')
#PG is the first one required for the eleTau channel as well?
Te_inc_sig_ele = Cut('l2_relIso05<0.1 && l2_tightId>0.5 && l2_dxy<0.045 && l2_dz<0.2 && l2_pt>20')
Te_inc_sig = inc_sig_ele & inc_sig_tau


## def cutstr_signal():
##     return inc_sig

## def cutstr_rlxmuiso(cutstr, muIsoCut):
##     '''WARNING: assumes mu iso cut is 0.1'''
##     return cutstr.replace( 'l2_relIso05<0.1',
##                            'l2_relIso05<{cut}'.format(cut=muIsoCut) )

## def cutstr_rlxtauiso(cutstr, tauIsoCut):
##     '''WARNING: assumes mu iso cut is 0.1'''
##     return cutstr.replace('l1_looseMvaIso>0.5',
##                           'l1_rawMvaIso>{cut}'.format(cut=tauIsoCut) )

## def cutstr_rlxtaumuiso(cutstr, tauIsoCut, muIsoCut):
##     '''WARNING: assumes mu iso cut is 0.1'''
##     cutstr = cutstr_rlxmuiso(cutstr, muIsoCut)
##     return cutstr_rlxtauiso(cutstr, tauIsoCut)


## cat_Inc_RlxMuIso = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05<1.0')
## cat_Inc_RlxTauIso = str(inc_sig).replace('l1_looseMvaIso>0.5', 'l1_rawMvaIso>0.')
## cat_Inc_RlxMuTauIso = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05<0.5').replace('l1_looseMvaIso>0.5', 'l1_rawMvaIso>-0.5')
## cat_Inc_AntiMuTauIso = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05>0.1').replace('l1_looseMvaIso>0.5', 'l1_looseMvaIso<0.5')
## cat_Inc_AntiMuTauIso_B = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05>0.2').replace('l1_looseMvaIso>0.5', 'l1_rawMvaIso>-0.75')

## cat_Inc_AntiMuTauIsoJosh = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05>0.2 && l2_relIso05<0.5').replace('l1_looseMvaIso>0.5', 'l1_rawMvaIso>0.7')
## cat_Inc_AntiMuIso = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05>0.1')
## cat_Inc_AntiTauIso = str(inc_sig).replace('l1_looseMvaIso>0.5', 'l1_looseMvaIso<0.5')
## cat_Inc_RlxMuTauIso_b = str(inc_sig).replace('l2_relIso05<0.1','l2_relIso05<0.5').replace('l1_looseMvaIso>0.5', 'l1_rawMvaIso>0.5')
## cat_Inc = str(inc_sig)

## categories = {
##     'Xcat_Inc_AntiMuTauIsoJoshX':cat_Inc_AntiMuTauIsoJosh,
##     'Xcat_Inc_RlxMuIsoX':cat_Inc_RlxMuIso,
##     'Xcat_IncX':cat_Inc,
##     'Xcat_VBFX':cat_VBF,
##     'Xcat_VHX':cat_VH,
##     'Xcat_J1X':cat_J1,
##     'Xcat_J1BX':cat_J1B,
##     'Xcat_J0X':cat_J0
##     }
