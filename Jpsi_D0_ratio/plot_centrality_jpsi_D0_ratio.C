//*******************************************************************************
// plot the results                                                             *
// by Xiaozhi Bai xiaozhi.bai@cern.ch x.bai@gsi.de                              *
// Wed Jul  8 20:02:05 CEST 2019                                                *
//*******************************************************************************

#include <iostream>
#include <fstream>

#include "TLatex.h"
#include "TStyle.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TLine.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"


#include  "../common/PlottingHelper.h"
//Phys. Lett. B 766 (2017) 212-224
//https://alice-notes.web.cern.ch/system/files/notes/public/711/2019-04-02-ALICE_public_note.pdf

double common_uncertainty=0.0736;
double common_uncertainty_fwdy=0.05;

//sqrt(0.039*0.039+0.058*0.058+0.021*0.021+0.01*0.01)

//pp from sts, sys, lumi, Jpis BR



char buf[1024];

void plot_raa_cent_model();
void plot_raa_cent_data();

TGraphErrors* GetCentRaa_5020_data_sts(int, const char *);
TGraphErrors* GetCentRaa_5020_data_sys(int, const char *);
TGraphAsymmErrors *Get_SHM_5020_model();
//bool 
double NormUncert1   = 0.0072; // 0-10  %
double NormUncert2   = 0.0069; // 10-30 %
double NormUncert3   = 0.012; // 30-50 %
double NormUncert_Fw = 0.040; // 0-20  %


inline TGraphErrors *GetCentRaaStat5020();
inline TGraphErrors *GetCentRaaSyst5020();



inline TGraph *GetCentRaaTM15020_model();
inline TGraph *GetCentRaaTM25020_model();
inline TGraph *GetCentRaaSHM5020_model();
inline TGraph *GetCentRaaComv020_model();

TFile *final_results_cent_midy;
const char *final_results_cent_fwdy;

/* const char *fileTAMU_cent_raa; */
/* const char *fileQinghua_cent_raa; */
/* const char *fileSHM_cent_raa; */
/* const char *fileComover_cent_raa; */

void plot_centrality_jpsi_D0_ratio()
{

  SetStyle();

  final_results_cent_midy=new TFile("input/data/D0_jpsi_ratio.root","READ");
  //  final_results_cent_fwdy= "input/data/Raa_vs_centrality_fwd.txt";

  /* fileTAMU_cent_raa = "../models/Ralf_Rapp/data/TAMU_5020_cent_RAA_mid.txt"; */
  /* fileQinghua_cent_raa = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-Np-2022Jan5/theory-RAA-Np.dat"; */
  /* fileComover_cent_raa = "input/models/comover_5020_midy.txt"; */
  /* fileSHM_cent_raa = "input/models/SHM_CentDep_PbPb5020_midy_11012019.txt";     */

  plot_raa_cent_model();
  //  plot_raa_cent_data();
}

void plot_raa_cent_model(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetCentRaaStat5020();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetCentRaaSyst5020();


  TGraphAsymmErrors *gr_SHM_5020_model = (TGraphAsymmErrors *) Get_SHM_5020_model(); 
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.15,0.0355);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";Centrality; D^{0}/J/#psi",2,2,6,100,30,152);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,1,0.0,0.06,0.015,0.015,2,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  SetErrorX(gr_CentRaaSyst5020,0.1);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_SHM_5020_model->SetFillColor(4);
  gr_SHM_5020_model->SetMarkerStyle(20);


  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  ci1 = TColor::GetColor("#33ccff");
  gr_SHM_5020_model->SetFillColorAlpha(ci1,0.7);
  gr_SHM_5020_model->SetLineColor(ci1);

  
  gr_SHM_5020_model->Draw("sameE2");
  
  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  TLatex tex0(0.5,0.5," ");
  tex0.SetTextFont(42);
  tex0.SetTextSize(0.07);
  tex0.SetNDC();

  tex0.DrawLatex(0.28,0.08,"0-10%");
  tex0.DrawLatex(0.7,0.08,"30-50%");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.280,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.18,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi, |#it{y}| < 0.9, 0.15 < #it{p}_{T} <15 GeV/#it{c}");
  tex1.DrawLatex(0.18,0.70,"Inclusive D^{0}, |#it{y}| < 0.5, 0 < #it{p}_{T} < 50 GeV/#it{c}");
  
  TLegend  *legend= new TLegend(0.2,0.55,0.56,0.65);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  

  legend->AddEntry(gr_CentRaaStat5020, lg_data,"P");
  legend->AddEntry(gr_SHM_5020_model,lg_SHM,"f");
  
  legend->Draw();
  
    gPad->RedrawAxis();
    c_temp->SaveAs("output/D0_jpsi_ratio_data.pdf");
    delete mh2Dummy;
  delete c_temp;
}


TGraphErrors *GetCentRaaStat5020(){

  TH1F * D0_jpsiratio_sts= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sts");
  TGraphErrors* gr_D0_jpsiratio_sts=new TGraphErrors(D0_jpsiratio_sts);

  D0_jpsiratio_sts->Print("all");
  return gr_D0_jpsiratio_sts;
}

TGraphErrors *GetCentRaaSyst5020(){

  TH1F * D0_jpsiratio_sys= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sys");
  TGraphErrors* gr_D0_jpsiratio_sys=new TGraphErrors(D0_jpsiratio_sys);
  return gr_D0_jpsiratio_sys;
}


TGraphAsymmErrors *Get_SHM_5020_model(){

  const int Npoints=2;
  
    
  Double_t x[Npoints]={3,5};
  Double_t y[Npoints]={56.8,76.3};
  Double_t exl[Npoints]={1,1};
  Double_t eyl[Npoints]={8.2,7.3};
  Double_t exh[Npoints]={1,1};
  Double_t eyh[Npoints]={11.8,8.4};

  TGraphAsymmErrors *gr_SHM_model = new TGraphAsymmErrors(Npoints,x,y,exl,exh,eyl,eyh);

  return gr_SHM_model;
}

