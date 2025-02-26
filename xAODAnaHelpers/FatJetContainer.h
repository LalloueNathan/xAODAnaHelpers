#ifndef xAODAnaHelpers_FatJetContainer_H
#define xAODAnaHelpers_FatJetContainer_H

#include <TTree.h>
#include <TLorentzVector.h>

#include <vector>
#include <string>

#include <xAODJet/JetContainer.h>

#include <xAODAnaHelpers/HelperClasses.h>
#include <xAODAnaHelpers/HelperFunctions.h>

#include <xAODAnaHelpers/FatJet.h>
#include <xAODAnaHelpers/ParticleContainer.h>
#include <xAODAnaHelpers/JetContainer.h>

#include "Math/Vector4D.h"

namespace xAH {

    class FatJetContainer : public ParticleContainer<FatJet,HelperClasses::JetInfoSwitch>
    {
    public:
      FatJetContainer(const std::string& name = "fatjet", const std::string& detailStr="", const std::string& subjetDetailStr="kinematic", const std::string& suffix="",
		      float units = 1e3, bool mc = false);
      virtual ~FatJetContainer();

      virtual void setTree    (TTree *tree);
      virtual void setBranches(TTree *tree);
      virtual void clear();
      virtual void FillFatJet( const xAOD::Jet* jet           , int pvLocation=0, const std::string& systName = "");
      virtual void FillFatJet( const xAOD::IParticle* particle, int pvLocation=0, const std::string& systName = "");
      using ParticleContainer::setTree; // make other overloaded version of execute() to show up in subclass

      float       m_trackJetPtCut  =10e3; // slimming pT cut on associated track jets
      float       m_trackJetEtaCut =2.5;  // slimmint eta cut on associated track jets

    protected:

      virtual void updateParticle(uint idx, FatJet& jet);

    private:

      bool SelectTrackJet(const xAOD::Jet* TrackJet);
      float GetEMFrac(const xAOD::Jet& jet);

    private:

      //
      // Vector branches
      //

      // scales
      std::vector<float> *m_JetConstitScaleMomentum_eta;
      std::vector<float> *m_JetConstitScaleMomentum_phi;
      std::vector<float> *m_JetConstitScaleMomentum_m;
      std::vector<float> *m_JetConstitScaleMomentum_pt;

      std::vector<float> *m_JetEMScaleMomentum_eta;
      std::vector<float> *m_JetEMScaleMomentum_phi;
      std::vector<float> *m_JetEMScaleMomentum_m;
      std::vector<float> *m_JetEMScaleMomentum_pt;

      // area
      std::vector<float> *m_GhostArea;
      std::vector<float> *m_ActiveArea;
      std::vector<float> *m_VoronoiArea;

      std::vector<float> *m_ActiveArea4vec_pt;
      std::vector<float> *m_ActiveArea4vec_eta;
      std::vector<float> *m_ActiveArea4vec_phi;
      std::vector<float> *m_ActiveArea4vec_m;

      // substructure
      std::vector<float> *m_Split12;
      std::vector<float> *m_Split23;
      std::vector<float> *m_Split34;
      std::vector<float> *m_tau1_wta;
      std::vector<float> *m_tau2_wta;
      std::vector<float> *m_tau3_wta;
      std::vector<float> *m_tau21_wta;
      std::vector<float> *m_tau32_wta;
      std::vector<float> *m_ECF1;
      std::vector<float> *m_ECF2;
      std::vector<float> *m_ECF3;
      std::vector<float> *m_C2;
      std::vector<float> *m_D2;
      std::vector<float> *m_NTrimSubjets;
      std::vector<int>   *m_NClusters;
      std::vector<int>   *m_nTracks;
      std::vector<int>   *m_ungrtrk500;
      //std::vector<std::vector<ROOT::Math::PtEtaPhiMVector>> *m_tracks_fourVec;
      std::vector<float> *m_EMFrac;
      std::vector<int>   *m_nChargedParticles;

      // constituent
      std::vector< int > *m_numConstituents;

      // constituentAll
      std::vector< std::vector<float> >  *m_constituentWeights;
      std::vector< std::vector<float> >  *m_constituent_pt;
      std::vector< std::vector<float> >  *m_constituent_eta;
      std::vector< std::vector<float> >  *m_constituent_phi;
      std::vector< std::vector<float> >  *m_constituent_e;

      // truth
      std::vector<float> *m_truth_m;
      std::vector<float> *m_truth_pt;
      std::vector<float> *m_truth_phi;
      std::vector<float> *m_truth_eta;

      // bosonCount
      std::vector< int > *m_nTQuarks;
      std::vector< int > *m_nHBosons;
      std::vector< int > *m_nWBosons;
      std::vector< int > *m_nZBosons;

      // Assocated Track Jets
      std::unordered_map<std::string, xAH::JetContainer*> m_trkJets;
      std::unordered_map<std::string, std::vector<std::vector<unsigned int>>* > m_trkJetsIdx;

      // muonCorrection
      std::vector<float> *m_muonCorrected_pt;
      std::vector<float> *m_muonCorrected_eta;
      std::vector<float> *m_muonCorrected_phi;
      std::vector<float> *m_muonCorrected_m;

    };
}



#endif // xAODAnaHelpers_FatJetContainer_H
