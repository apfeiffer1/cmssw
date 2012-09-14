
from CMGTools.Common.Tools.cmsswRelease import cmsswIs44X

def getGlobalTag(runOnMC, runOn52Sample):
    """Return the global tag, based on
    - the runOnMC flag
    - the file name
    - the CMSSW release

    Please have a look at the python source for more information
    """

    # we run on a 52 sample if:
    # - we have START52 in the name (52 MC)
    # - we have PromptReco and (2012A or 2012B) in the name (52 data)
##     runOn52Sample = file.find('START52') != -1 or \
##                     ( (file.find('2012A') != -1 or file.find('2012B') !=-1 ) and file.find('PromptReco') != -1 )
    
    if cmsswIs44X():
        if runOnMC:
            GT = 'START44_V13::All'
        else:
            GT = 'GR_R_44_V15::All'
    else:
        if runOnMC:
            if runOn52Sample:
                GT = 'START52_V10::All'
            else:
                GT = 'START53_V10::All' # for 53X MC in >= 533
                # GT = 'START53_V7E::All' # for 53X MC in < 533
        else:
            if runOn52Sample:
                GT = 'GR_R_52_V8::All'
            else:
                GT = 'GR_P_V41_AN1::All' # for 53X data in >= 533
                # GT = 'GR_P_V40_AN1::All' # for 53X data in < 533

    return GT


if __name__ == '__main__':

    print '52, data', getGlobalTag(False, True)
    print '52, MC', getGlobalTag(True, True)
    print 'the following depends on the release you are running in'
    print '44X or 53X, data', getGlobalTag(False, False)
    print '44X or 53X, MC', getGlobalTag(True, False)
