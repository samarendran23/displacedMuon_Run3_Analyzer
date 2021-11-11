


import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
            'file:../../../AOD_1.root'
                )
                            )

process.demo = cms.EDAnalyzer('Analyzer',
    muons = cms.InputTag("muons"),
    tracks = cms.InputTag("tracks")

                              )
process.p = cms.Path(process.demo)
























































