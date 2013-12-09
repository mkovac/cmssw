///
/// \class l1t::L1TCaloStage1Producer
///
/// Description: Emulator for the stage 1 jet algorithms.
///
///
/// \author: R. Alex Barbieri MIT
///


// system include files
#include <boost/shared_ptr.hpp>

// user include files

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

//this doesn't exist yet 12/5/13 Alex
//#include "CondFormats/DataRecord/interface/CaloParamsRcd.h"
//this only exists in Jim's private repo?
//#include "CondFormats/L1TCalorimeter/interface/CaloParams.h"

#include "DataFormats/L1TCalorimeter/interface/CaloRegion.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include <vector>

//#include "L1Trigger/L1TCalorimeter/interface/CaloStage1JetAlgorithm.h"
#include "L1Trigger/L1TCalorimeter/interface/CaloStage1MainProcessor.h"
#include "L1Trigger/L1TCalorimeter/interface/CaloStage1FirmwareFactory.h"

using namespace std;
using namespace edm;

namespace l1t {

//
// class declaration
//

  class L1TCaloStage1Producer : public EDProducer {
  public:
    explicit L1TCaloStage1Producer(const ParameterSet&);
    ~L1TCaloStage1Producer();

    static void fillDescriptions(ConfigurationDescriptions& descriptions);

  private:
    virtual void produce(Event&, EventSetup const&);
    virtual void beginJob();
    virtual void endJob();
    virtual void beginRun(Run const&iR, EventSetup const&iE);
    virtual void endRun(Run const& iR, EventSetup const& iE);

    // ----------member data ---------------------------
    unsigned long long m_paramsCacheId; // Cache-ID from current parameters, to check if needs to be updated.
    //boost::shared_ptr<const CaloParams> m_dbpars; // Database parameters for the trigger, to be updated as needed.
    boost::shared_ptr<CaloStage1MainProcessor> m_fw; // Firmware to run per event, depends on database parameters.

    CaloStage1FirmwareFactory m_factory; // Factory to produce algorithms based on DB parameters

    // to be extended with other "consumes" stuff
    EDGetToken regionToken;
  };

  //
  // constructors and destructor
  //
  L1TCaloStage1Producer::L1TCaloStage1Producer(const ParameterSet& iConfig)
  {
    // register what you produce
    produces<std::vector<l1t::Jet>>();

    // register what you consume and keep token for later access:
    regionToken = consumes<std::vector<l1t::CaloRegion>>(iConfig.getParameter<InputTag>("uctDigis"));

    // set cache id to zero, will be set at first beginRun:
    m_paramsCacheId = 0;
  }


  L1TCaloStage1Producer::~L1TCaloStage1Producer()
  {
  }



//
// member functions
//

// ------------ method called to produce the data ------------
void
L1TCaloStage1Producer::produce(Event& iEvent, const EventSetup& iSetup)
{

  LogDebug("l1t|stage 1 jets") << "L1TCaloStage1Producer::produce function called...\n";

  Handle<std::vector<l1t::CaloRegion>> caloRegions;
  iEvent.getByToken(regionToken,caloRegions);

  std::auto_ptr<std::vector<l1t::Jet>> l1Jets (new std::vector<l1t::Jet>);

  //m_fw->processEvent(*caloRegions, *l1Jets);

  iEvent.put(l1Jets);

}

// ------------ method called once each job just before starting event loop ------------
void
L1TCaloStage1Producer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop ------------
void
L1TCaloStage1Producer::endJob() {
}

// ------------ method called when starting to processes a run ------------

void L1TCaloStage1Producer::beginRun(Run const&iR, EventSetup const&iE){

  LogDebug("l1t|stage 1 jets") << "L1TCaloStage1Producer::beginRun function called...\n";

  //unsigned long long id = iE.get<CaloParamsRcd>().cacheIdentifier();

  //if (id != m_paramsCacheId)
  { // Need to update:
    //m_paramsCacheId = id;

    //ESHandle<CaloParams> parameters;
    //iE.get<CaloParamsRcd>().get(parameters);

    //m_dbpars = boost::shared_ptr<const CaloParams>(parameters.product());

    // if (! m_dbpars){
    //   LogError("l1t|stage 1 jets") << "L1TCaloStage1Producer: could not retreive DB params from Event Setup\n";
    // }

    // Set the current algorithm version based on DB pars from database:
    m_fw = m_factory.create(/**m_dbpars*/);

    if (! m_fw) {
      // we complain here once per run
      LogError("l1t|stage 1 jets") << "L1TCaloStage1Producer: firmware could not be configured.\n";
    }
  }


}

// ------------ method called when ending the processing of a run ------------
void L1TCaloStage1Producer::endRun(Run const& iR, EventSetup const& iE){

}


// ------------ method fills 'descriptions' with the allowed parameters for the module ------------
void
L1TCaloStage1Producer::fillDescriptions(ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

} // namespace

//define this as a plug-in
DEFINE_FWK_MODULE(l1t::L1TCaloStage1Producer);
