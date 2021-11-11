// -*- C++ -*-
//
// Package:    Analysis/Analyzer
// Class:      Analyzer
//
/**\class Analyzer Analyzer.cc Analysis/Analyzer/plugins/Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Bibhuprasad Mahakud
//         Created:  Mon, 06 Sep 2021 18:04:25 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"

#include "RecoMuon/MuonIdentification/plugins/MuonIdProducer.h"

#include <TVector3.h>
#include<vector>

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class Analyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit Analyzer(const edm::ParameterSet&);
      ~Analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
     // edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file

      edm::EDGetTokenT<std::vector<reco::Muon>> offlineMuonToken_;
      edm::EDGetTokenT<std::vector<reco::Track>> tracksToken_;
      //edm::EDGetTokenT<std::vector<MuonIdProducer>> Muonid_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Analyzer::Analyzer(const edm::ParameterSet& iConfig)
 :
 // tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
 offlineMuonToken_(consumes<std::vector<reco::Muon>>(iConfig.getParameter<edm::InputTag>("muons"))),
 tracksToken_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("tracks")))
 //Muonid_(consumes<std::vector<MuonIdProducer>>(iConfig.getParameter<edm::InputTag>("muonid")))

{
   //now do what ever initialization is needed

}


Analyzer::~Analyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

  edm::Handle<std::vector<reco::Muon> > muons;  
  iEvent.getByToken(offlineMuonToken_, muons);

  edm::Handle<std::vector<reco::Track> > tracks;
  iEvent.getByToken(tracksToken_, tracks);

  /*edm::Handle<std::vector<MuonIdProducer> > muonid;
  iEvent.getByToken(Muonid_, muonid);*/


  std::cout<<"event ---"<<std::endl;

  for(std::vector<reco::Muon>::const_iterator itMu = muons->begin();

    itMu != muons->end();
    ++itMu) {

    
   //itMu->sharedHits();
   //std::cout<<"Match:"<<itMu->MuonIdProducer::sharedHits()<<std::endl;

   std::cout<<"mu pt:  "<<itMu->pt()<<std::endl;
   if(itMu->isGlobalMuon())std::cout<<"is a global muon"<<std::endl;   
   if(itMu->isDisplacedMuon())std::cout<<"is a Displaced muon"<<std::endl;
   if(itMu->isTrackerMuon())std::cout<<"is a Tracker muon"<<std::endl;
   if(itMu->isPFMuon())std::cout<<"is a PF muon"<<std::endl;


   }


/*  for(std::vector<reco::Track>::const_iterator itTracki = tracks->begin();
      itTracki != tracks->end();
      ++itTracki) {

	
      for(std::vector<reco::Track>::const_iterator itTrackj = tracks->begin();
      itTrackj != tracks->end();
      ++itTrackj) {



     int sharedhits = sharedHits(*itTracki,*itTrackj);

     std::cout<<"SharedHits:"<<sharedhits<<std::endl;


}
}*/


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
Analyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
Analyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Analyzer);
