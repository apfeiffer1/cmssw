#include "CondFormats/Common/interface/SerializationTest.h"

#include "CondFormats/EcalObjects/interface/Serialization.h"

int main()
{
    testSerialization<EcalADCToGeVConstant>();
    testSerialization<EcalChannelStatus>();
    testSerialization<EcalChannelStatusCode>();
    testSerialization<EcalClusterCrackCorrParameters>();
    testSerialization<EcalClusterEnergyCorrectionObjectSpecificParameters>();
    testSerialization<EcalClusterEnergyCorrectionParameters>();
    testSerialization<EcalClusterEnergyUncertaintyParameters>();
    testSerialization<EcalClusterLocalContCorrParameters>();
    testSerialization<EcalCondObjectContainer<EcalChannelStatusCode>>();
    testSerialization<EcalCondObjectContainer<EcalDQMStatusCode>>();
    testSerialization<EcalCondObjectContainer<EcalLaserAPDPNRatios::EcalLaserAPDPNpair>>();
    testSerialization<EcalCondObjectContainer<EcalMGPAGainRatio>>();
    testSerialization<EcalCondObjectContainer<EcalMappingElement>>();
    testSerialization<EcalCondObjectContainer<EcalPedestal>>();
    testSerialization<EcalCondObjectContainer<EcalTPGCrystalStatusCode>>();
    testSerialization<EcalCondObjectContainer<EcalTPGLinearizationConstant>>();
    testSerialization<EcalCondObjectContainer<EcalTPGPedestal>>();
    testSerialization<EcalCondObjectContainer<EcalTimeDependentCorrections::Values>>();
    testSerialization<EcalCondObjectContainer<EcalXtalGroupId>>();
    testSerialization<EcalCondObjectContainer<float>>();
    testSerialization<EcalCondTowerObjectContainer<EcalChannelStatusCode>>();
    testSerialization<EcalCondTowerObjectContainer<EcalDAQStatusCode>>();
    testSerialization<EcalCondTowerObjectContainer<EcalDQMStatusCode>>();
    testSerialization<EcalContainer<EBDetId,EcalChannelStatusCode>>();
    testSerialization<EcalContainer<EBDetId,EcalDQMStatusCode>>();
    testSerialization<EcalContainer<EBDetId,EcalLaserAPDPNRatios::EcalLaserAPDPNpair>>();
    testSerialization<EcalContainer<EBDetId,EcalMGPAGainRatio>>();
    testSerialization<EcalContainer<EBDetId,EcalMappingElement>>();
    testSerialization<EcalContainer<EBDetId,EcalPedestal>>();
    testSerialization<EcalContainer<EBDetId,EcalTPGCrystalStatusCode>>();
    testSerialization<EcalContainer<EBDetId,EcalTPGLinearizationConstant>>();
    testSerialization<EcalContainer<EBDetId,EcalTPGPedestal>>();
    testSerialization<EcalContainer<EBDetId,EcalTimeDependentCorrections::Values>>();
    testSerialization<EcalContainer<EBDetId,EcalXtalGroupId>>();
    testSerialization<EcalContainer<EBDetId,float>>();
    testSerialization<EcalContainer<EEDetId,EcalChannelStatusCode>>();
    testSerialization<EcalContainer<EEDetId,EcalDQMStatusCode>>();
    testSerialization<EcalContainer<EEDetId,EcalLaserAPDPNRatios::EcalLaserAPDPNpair>>();
    testSerialization<EcalContainer<EEDetId,EcalMGPAGainRatio>>();
    testSerialization<EcalContainer<EEDetId,EcalMappingElement>>();
    testSerialization<EcalContainer<EEDetId,EcalPedestal>>();
    testSerialization<EcalContainer<EEDetId,EcalTPGCrystalStatusCode>>();
    testSerialization<EcalContainer<EEDetId,EcalTPGLinearizationConstant>>();
    testSerialization<EcalContainer<EEDetId,EcalTPGPedestal>>();
    testSerialization<EcalContainer<EEDetId,EcalTimeDependentCorrections::Values>>();
    testSerialization<EcalContainer<EEDetId,EcalXtalGroupId>>();
    testSerialization<EcalContainer<EEDetId,float>>();
    testSerialization<EcalContainer<EcalScDetId,EcalChannelStatusCode>>();
    testSerialization<EcalContainer<EcalScDetId,EcalDAQStatusCode>>();
    testSerialization<EcalContainer<EcalScDetId,EcalDQMStatusCode>>();
    testSerialization<EcalContainer<EcalTrigTowerDetId,EcalChannelStatusCode>>();
    testSerialization<EcalContainer<EcalTrigTowerDetId,EcalDAQStatusCode>>();
    testSerialization<EcalContainer<EcalTrigTowerDetId,EcalDQMStatusCode>>();
    testSerialization<EcalDAQStatusCode>();
    testSerialization<EcalDAQTowerStatus>();
    testSerialization<EcalDCSTowerStatus>();
    testSerialization<EcalDCUTemperatures>();
    testSerialization<EcalDQMChannelStatus>();
    testSerialization<EcalDQMStatusCode>();
    testSerialization<EcalDQMTowerStatus>();
    testSerialization<EcalFloatCondObjectContainer>();
    testSerialization<EcalFunParams>();
    testSerialization<EcalGainRatios>();
    testSerialization<EcalIntercalibConstants>();
    testSerialization<EcalIntercalibConstantsMC>();
    testSerialization<EcalIntercalibErrors>();
    testSerialization<EcalLaserAPDPNRatios>();
    testSerialization<EcalLaserAPDPNRatios::EcalLaserAPDPNRatiosMap>();
    testSerialization<EcalLaserAPDPNRatios::EcalLaserAPDPNpair>();
    testSerialization<EcalLaserAPDPNRatios::EcalLaserTimeStamp>();
    testSerialization<EcalLaserAPDPNRatiosRef>();
    testSerialization<EcalLaserAlphas>();
    testSerialization<EcalLinearCorrections>();
    testSerialization<EcalMGPAGainRatio>();
    testSerialization<EcalMappingElectronics>();
    testSerialization<EcalMappingElement>();
    testSerialization<EcalPTMTemperatures>();
    testSerialization<EcalPedestal>();
    testSerialization<EcalPedestals>();
    testSerialization<EcalSRSettings>();
    testSerialization<EcalSampleMask>();
    testSerialization<EcalTBWeights>();
    testSerialization<EcalTPGCrystalStatus>();
    testSerialization<EcalTPGCrystalStatusCode>();
    testSerialization<EcalTPGFineGrainConstEB>();
    testSerialization<EcalTPGFineGrainEBGroup>();
    testSerialization<EcalTPGFineGrainEBIdMap>();
    testSerialization<EcalTPGFineGrainStripEE>();
    testSerialization<EcalTPGFineGrainStripEE::Item>();
    testSerialization<EcalTPGFineGrainTowerEE>();
    testSerialization<EcalTPGGroups>();
    testSerialization<EcalTPGLinearizationConst>();
    testSerialization<EcalTPGLinearizationConstant>();
    testSerialization<EcalTPGLut>();
    testSerialization<EcalTPGLutGroup>();
    testSerialization<EcalTPGLutIdMap>();
    testSerialization<EcalTPGPedestal>();
    testSerialization<EcalTPGPedestals>();
    testSerialization<EcalTPGPhysicsConst>();
    testSerialization<EcalTPGPhysicsConst::Item>();
    testSerialization<EcalTPGSlidingWindow>();
    testSerialization<EcalTPGSpike>();
    testSerialization<EcalTPGStripStatus>();
    testSerialization<EcalTPGTowerStatus>();
    testSerialization<EcalTPGWeightGroup>();
    testSerialization<EcalTPGWeightIdMap>();
    testSerialization<EcalTPGWeights>();
    testSerialization<EcalTimeCalibConstants>();
    testSerialization<EcalTimeCalibErrors>();
    testSerialization<EcalTimeDependentCorrections>();
    testSerialization<EcalTimeDependentCorrections::EcalValueMap>();
    testSerialization<EcalTimeDependentCorrections::Times>();
    testSerialization<EcalTimeDependentCorrections::Values>();
    testSerialization<EcalTimeOffsetConstant>();
    testSerialization<EcalWeightSet>();
    testSerialization<EcalWeightXtalGroups>();
    testSerialization<EcalXtalGroupId>();
    testSerialization<std::map<std::pair<EcalXtalGroupId, EcalTBWeights::EcalTDCId>, EcalWeightSet>>();
    testSerialization<std::map<uint32_t, EcalTPGFineGrainConstEB>>();
    testSerialization<std::map<uint32_t, EcalTPGFineGrainStripEE::Item>>();
    testSerialization<std::map<uint32_t, EcalTPGLut>>();
    testSerialization<std::map<uint32_t, EcalTPGPhysicsConst::Item>>();
    testSerialization<std::map<uint32_t, EcalTPGWeights>>();
    testSerialization<std::map<uint32_t, uint16_t>>();
    testSerialization<std::pair<EcalXtalGroupId, EcalTBWeights::EcalTDCId>>();
    testSerialization<std::pair<const std::pair<EcalXtalGroupId, EcalTBWeights::EcalTDCId>, EcalWeightSet>>();
    testSerialization<std::pair<const uint32_t, EcalTPGFineGrainConstEB>>();
    testSerialization<std::pair<const uint32_t, EcalTPGFineGrainStripEE::Item>>();
    testSerialization<std::pair<const uint32_t, EcalTPGLut>>();
    testSerialization<std::pair<const uint32_t, EcalTPGPhysicsConst::Item>>();
    testSerialization<std::pair<const uint32_t, EcalTPGWeights>>();
    testSerialization<std::pair<const uint32_t, uint16_t>>();
    testSerialization<std::vector<EcalChannelStatusCode>>();
    testSerialization<std::vector<EcalDAQStatusCode>>();
    testSerialization<std::vector<EcalDQMStatusCode>>();
    testSerialization<std::vector<EcalLaserAPDPNRatios::EcalLaserAPDPNpair>>();
    testSerialization<std::vector<EcalLaserAPDPNRatios::EcalLaserTimeStamp>>();
    testSerialization<std::vector<EcalMGPAGainRatio>>();
    testSerialization<std::vector<EcalMappingElement>>();
    testSerialization<std::vector<EcalPedestal>>();
    testSerialization<std::vector<EcalTPGCrystalStatusCode>>();
    testSerialization<std::vector<EcalTPGLinearizationConstant>>();
    testSerialization<std::vector<EcalTPGPedestal>>();
    testSerialization<std::vector<EcalTimeDependentCorrections::Times>>();
    testSerialization<std::vector<EcalTimeDependentCorrections::Values>>();
    testSerialization<std::vector<EcalXtalGroupId>>();

    return 0;
}