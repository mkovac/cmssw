///
/// Description: Firmware headers
///
/// Implementation:
///    Concrete firmware implementations
///
/// \author: Jim Brooke - University of Bristol
///

//
//

#ifndef CaloStage1MainProcessorFirmware_H
#define CaloStage1MainProcessorFirmware_H

#include "L1Trigger/L1TCalorimeter/interface/CaloStage1MainProcessor.h"
#include "CaloStage1JetAlgorithm.h"

namespace l1t {

  class CaloStage1MainProcessorFirmwareImp1 : public CaloStage1MainProcessor {
  public:
    CaloStage1MainProcessorFirmwareImp1(/*const CaloParams & dbPars*/);
    virtual ~CaloStage1MainProcessorFirmwareImp1();
    virtual void processEvent(const CaloEmCand &,
                              const CaloRegion &,
			      BXVector<EGamma> & egammas,
			      BXVector<Tau> & taus,
			      BXVector<Jet> & jets,
			      BXVector<EtSum> & etsums);
  private:

    //CaloParams const & m_db;

    //CaloStage1EGammaAlgorithm* m_egAlgo;
    //CaloStage1TauAlgoritmh* m_tauAlgo;
    CaloStage1JetAlgorithm* m_jetAlgo;
    //CaloStage1EtSumAlgorithm* m_sumAlgo;

    //CaloStage1JetSumAlgorithm* m_jetSumAlgo;
    //CaloStage1TowerAlgorithm* m_towerAlgo;
    //CaloStage1ClusterAlgorithm* m_clusterAlgo;

  };

}

#endif
