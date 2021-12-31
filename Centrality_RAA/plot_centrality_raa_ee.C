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

const char *fileTAMU_cent_raa;
const char *fileQinghua_cent_raa;
const char *fileSHM_cent_raa;
const char *fileComover_cent_raa;

void plot_centrality_raa_ee()
{

  SetStyle();

  final_results_cent_midy=new TFile("input/data/results_centrality.root","READ");

  final_results_cent_fwdy= "input/data/Raa_vs_centrality_fwd.txt";

  fileTAMU_cent_raa = "input/models/TAMU_5020_cent_RAA_mid.txt";
  fileQinghua_cent_raa = "input/models/Raa_npart.dat";
  fileComover_cent_raa = "input/models/comover_5020_midy.txt";
  fileSHM_cent_raa = "input/models/SHM_CentDep_PbPb5020_midy_11012019.txt";    

  plot_raa_cent_model();
  plot_raa_cent_data();
}

void plot_raa_cent_model(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetCentRaaStat5020();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetCentRaaSyst5020();

  TGraph * gr_CentRaaTM15020_model=  (TGraph *)GetCentRaaTM1_5020_model(29,fileTAMU_cent_raa);
  TGraph * gr_CentRaaTM25020_model=  (TGraph *)GetCentRaaTM2_5020_model(26,fileQinghua_cent_raa);
  TGraph * gr_CentRaaSHM5020_model=  (TGraph *)GetCentRaaSHM_5020_model(40,fileSHM_cent_raa);
  TGraph * gr_CentRaaComv5020_model=  (TGraph *)GetCentRaaComv020_model(14,fileComover_cent_raa);  

  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_CentRaaSHM5020_model->SetFillColorAlpha(ci1,0.15);
  gr_CentRaaSHM5020_model->SetLineColor(ci1);

  gr_CentRaaComv5020_model ->SetFillColorAlpha(kGreen,0.15);
  gr_CentRaaComv5020_model ->SetLineColor(kGreen);

  gr_CentRaaTM15020_model  ->SetFillColorAlpha(kOrange+1,0.2);
  gr_CentRaaTM15020_model ->SetLineColor(kOrange+1);
  
  gr_CentRaaTM25020_model->SetFillColorAlpha(kBlue,0.15);
  gr_CentRaaTM25020_model->SetLineColor(kBlue);

  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.1,0.035);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#LT_{ }#it{N}_{part}_{ }#GT;#it{R}_{AA}",100,0,400,100,0.,2.5);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  SetErrorX(gr_CentRaaSyst5020,6);
  
  pad1->cd();
  mh2Dummy->Draw();
  gr_CentRaaTM15020_model->Draw("FL same");
  gr_CentRaaSHM5020_model->Draw("FL same");
  gr_CentRaaTM25020_model->Draw("FL same");
  
  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  box_comm ->Draw("sameE2");
    
  TLine *line_unity= (TLine *)GetLine(0,1.0,400,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.280,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.18,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi, |#it{y}|<0.9");
  tex1.DrawLatex(0.18,0.70,"#it{p}_{T} > 0.15 GeV/#it{c}");
  
  TLegend  *legend= new TLegend(0.65,0.7,0.92,0.92);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  
  legend->AddEntry( gr_CentRaaStat5020,"Data","P");
  legend->AddEntry(gr_CentRaaTM15020_model,"TAMU","f");
  legend->AddEntry(gr_CentRaaTM25020_model,"THU","f");
  legend->AddEntry(gr_CentRaaSHM5020_model,"SHM (old)","f");
  
  legend->Draw();

  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_cent_015_model.pdf");
  c_temp->SaveAs("output/Raa_Vs_cent_015_model.png");
  delete mh2Dummy;
  delete c_temp;
}

void plot_raa_cent_data(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetCentRaaStat5020();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetCentRaaSyst5020();

  TGraphErrors *gr_CentRaaStat5020_fwd=(TGraphErrors *)GetCentRaa_5020_data_sts(24,final_results_cent_fwdy);
  TGraphErrors *gr_CentRaaSyst5020_fwd=(TGraphErrors *)GetCentRaa_5020_data_sys(24,final_results_cent_fwdy);
  

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.1,0.035);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#LT_{ }#it{N}_{part}_{ }#GT;#it{R}_{AA}",100,0,410,100,0.,2.5);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  TBox *box_fwdy    = new TBox(400,1.-common_uncertainty_fwdy,408,1.+common_uncertainty_fwdy);
  box_fwdy ->SetFillColor(kBlue);
  
  
  SetTGraphError(gr_CentRaaStat5020,20,2,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2,2,2,2,0);
  SetErrorX(gr_CentRaaSyst5020,6);

  SetTGraphError(gr_CentRaaStat5020_fwd,20,2.,4,4,2,0);
  SetTGraphError(gr_CentRaaSyst5020_fwd,20,2.5,4,4,2,0);
  SetErrorX(gr_CentRaaSyst5020_fwd,6);

  
  pad1->cd();
  mh2Dummy->Draw();

  gr_CentRaaStat5020_fwd->Draw("samePE");
  gr_CentRaaSyst5020_fwd->Draw("sameE2");

  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  
  box_comm ->Draw("sameE2");
  box_fwdy ->Draw("sameE2");
  
    
  TLine *line_unity= (TLine *)GetLine(0,1.0,400,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.280,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.18,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi");
  //  tex1.DrawLatex(0.18,0.70,"#it{p}_{T} > 0.15 GeV/#it{c}");
  
  TLegend  *legend= new TLegend(0.5,0.65,0.8,0.8);
  SetLegend(legend,42,0.04,0.0,0.0,0.0,0.0);
  
  legend->AddEntry( gr_CentRaaStat5020,"|y| < 0.9 (#it{p}_{T} < 8 GeV/#it{c})","P");
  legend->AddEntry( gr_CentRaaStat5020_fwd,"2.5 < y < 4 (#it{p}_{T} > 0.15 GeV/#it{c})","P");
  legend->Draw();

  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_cent_015_data.pdf");
  c_temp->SaveAs("output/Raa_Vs_cent_015_data.png");
  delete mh2Dummy;
  delete c_temp;
}

TGraphErrors *GetCentRaaStat5020(){

  TGraphErrors* grCentRaaStat5020=(TGraphErrors*) final_results_cent_midy ->Get("gr_PbPb_Raa_N_part_sts");
  return grCentRaaStat5020;
}

TGraphErrors *GetCentRaaSyst5020(){

  TGraphErrors* grCentRaaSyst5020=(TGraphErrors*) final_results_cent_midy ->Get("gr_PbPb_Raa_N_part_sys");
  return grCentRaaSyst5020;
}

TGraphErrors* GetCentRaa_5020_data_sts(Int_t Npoint, const  char * input)
{
  ifstream myfiledata(input);
  const int ndata_sts = Npoint; // lines in the txt file

  double npart[ndata_sts];
  double raa[ndata_sts];
  double raa_sts[ndata_sts];
  double raa_sys_corr[ndata_sts];
  double raa_sys_uncorr[ndata_sts];
  double dummyErr_x[ndata_sts];

  double npart_temp = 0.;
  double raa_temp = 0.;
  double raa_sts_temp = 0.;
  double raa_sys_corr_temp = 0.;
  double raa_sys_uncorr_temp = 0.;

  
  int idata = 0; // counter

  while(myfiledata>>npart_temp >>raa_temp>> raa_sts_temp >> raa_sys_uncorr_temp >> raa_sys_corr_temp){
    
    npart[idata]     = npart_temp;
    raa[idata] = raa_temp;
    raa_sts[idata] = raa_sts_temp;
    dummyErr_x[idata]=0.0;
    idata++;
  }
  TGraphErrors *graadata_sts = new TGraphErrors(ndata_sts, npart, raa, dummyErr_x, raa_sts);
  return graadata_sts;
  

}

TGraphErrors* GetCentRaa_5020_data_sys(Int_t Npoint, const  char * input)
{
  ifstream myfiledata(input);
  const int ndata_sys = Npoint; // lines in the txt file

  double npart[ndata_sys];
  double raa[ndata_sys];
  double raa_sts[ndata_sys];
  double raa_sys[ndata_sys];

  double raa_sys_corr[ndata_sys];
  double raa_sys_uncorr[ndata_sys];
  double dummyErr_x[ndata_sys];

  double npart_temp = 0.;
  double raa_temp = 0.;
  double raa_sts_temp = 0.;
  double raa_sys_corr_temp = 0.;
  double raa_sys_uncorr_temp = 0.;

  
  int idata = 0; // counter

  while(myfiledata>>npart_temp >>raa_temp>> raa_sts_temp >> raa_sys_uncorr_temp >> raa_sys_corr_temp){

    npart[idata]     = npart_temp;
    raa[idata] = raa_temp;
    raa_sys[idata] = sqrt(raa_sys_uncorr_temp*raa_sys_uncorr_temp+raa_sys_corr_temp*raa_sys_corr_temp);
    dummyErr_x[idata]=0.0;
    raa_sys_uncorr[idata]=raa_sys_uncorr_temp;
    idata++;
  }

  TGraphErrors *graadata_sys = new TGraphErrors(ndata_sys, npart, raa, dummyErr_x, raa_sys_uncorr);
  return graadata_sys;
  

}
