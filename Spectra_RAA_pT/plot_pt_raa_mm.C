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

char buf[1024];

/* void plot_raa_pt_0_10(); */
/* void plot_raa_pt_30_50(); */
/* void plot_raa_pt_0_10_30_50(); */

void plot_raa_pt_0_20();
void plot_raa_pt_20_40();
void plot_raa_pt_40_90();
void plot_raa_pt_all();

//bool 
double NormUncert1   = 0.0072; // 0-10  %
//double NormUncert2   = 0.0069; // 10-30 %
double NormUncert3   = 0.016; // 30-50 %
//xdouble NormUncert_Fw = 0.040; // 0-20  %

double common_un=0.022;
//sqrt(0.022*0.022+0.021*0.021+0.0053*0.0053)

double NormUncert1_fwdy_0_20=0.025;
double NormUncert1_fwdy_20_40=0.0256;
double NormUncert1_fwdy_40_90=0.0399;


inline TGraphErrors *GetPtRaaStat5020_00_20();
inline TGraphErrors *GetPtRaaSyst5020_00_20();

inline TGraphErrors *GetPtRaaStat5020_20_40();
inline TGraphErrors *GetPtRaaSyst5020_20_40();

inline TGraphErrors *GetPtRaaStat5020_40_90();
inline TGraphErrors *GetPtRaaSyst5020_40_90();



TFile *final_results_pt_fwdy_00_20;
TFile *final_results_pt_fwdy_20_40;
TFile *final_results_pt_fwdy_40_90;



const char *fileTAMU_pt_raa_00_20;
const char *fileTAMU_pt_raa_20_40;
const char *fileTAMU_pt_raa_40_90;

const char *fileTHUA_pt_raa_00_20;
const char *fileTHUA_pt_raa_20_40;
const char *fileTHUA_pt_raa_40_90;

const char *fileSHM_pt_raa_00_20;
const char *fileSHM_pt_raa_20_40;
const char *fileSHM_pt_raa_40_90;

const char *fileEnergy_loss_model;



void plot_pt_raa_mm()
{
  SetStyle();
  gStyle->SetOptStat(0);

  final_results_pt_fwdy_00_20 =new TFile("input/data/mumu/RAA_0-20.root","READ");
  final_results_pt_fwdy_20_40 =new TFile("input/data/mumu/RAA_20-40.root","READ");
  final_results_pt_fwdy_40_90 =new TFile("input/data/mumu/RAA_40-90.root","READ");

  
  fileTAMU_pt_raa_00_20 = "../models/Ralf_Rapp/data/f0-20RAA.dat";
  fileTAMU_pt_raa_20_40 = "../models/Ralf_Rapp/data/f20-40RAA.dat";
  fileTAMU_pt_raa_40_90 = "../models/Ralf_Rapp/data/f40-90RAA.dat";


  fileTHUA_pt_raa_00_20 = "../models/PengfeiTM2/fig--forward-rapidity-2022_sigmacc718/cent020-RAA-pt-forwdY-2022/theory-RAA-pt-b48.dat";
  fileTHUA_pt_raa_20_40 = "../models/PengfeiTM2/fig--forward-rapidity-2022_sigmacc718/cent2040-RAA-pt-forwdY-2022/theory-RAA-pt-b84.dat";
  fileTHUA_pt_raa_40_90 = "../models/PengfeiTM2/fig--forward-rapidity-2022_sigmacc718/cent4090-RAA-pt-forwdY-2022/theory-RAA-pt-b114.dat";

  fileSHM_pt_raa_00_20 = "../models/SHMc/gRaaSHMc_fwdy_0_20.txt";
  fileSHM_pt_raa_20_40 = "../models/SHMc/gRaaSHMc_fwdy_20_40.txt";
  fileSHM_pt_raa_40_90 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";


  //energy losse mdoel

  fileEnergy_loss_model= "../models/energy-loss-model/ElossPredictions.root";

  plot_raa_pt_0_20();
  plot_raa_pt_20_40();
  plot_raa_pt_40_90();
  plot_raa_pt_all();
}
void plot_raa_pt_0_20(){
  
  TGraphErrors *gr_PtRaaStat5020_00_20 = (TGraphErrors*)GetPtRaaStat5020_00_20();
  TGraphErrors *gr_PtRaaSyst5020_00_20  = (TGraphErrors*)GetPtRaaSyst5020_00_20();

  TGraph * gr_PtRaaTM15020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTAMU_pt_raa_00_20);
  TGraph * gr_PtRaaTM25020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTHUA_pt_raa_00_20);
  TGraph * gr_PtRaaSHM5020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileSHM_pt_raa_00_20);

  TGraphAsymmErrors * gr_PtRaaEL5020_00_20_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEnergy_loss_model,"RAA_binned_centrality_0_20_ForwardRap");
  //  gr_PtRaaEL5020_00_20_model->Draw();

  //  return;

  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_00_20_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_00_20_model->SetLineColor(ci1);

  gr_PtRaaTM15020_00_20_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_00_20_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_00_20_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_00_20_model->SetLineColor(kBlue+1);

  gr_PtRaaEL5020_00_20_model->SetFillColorAlpha(kPink+1,0.4);
  gr_PtRaaEL5020_00_20_model->SetLineColor(kPink+9);

  
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.95,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0020    = new TBox(19.3,1.-NormUncert1_fwdy_0_20 ,20,1.+NormUncert1_fwdy_0_20);
  boxEle0020->SetFillColor(kRed);

  SetTGraphError(gr_PtRaaStat5020_00_20,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_20,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_00_20,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_00_20_model->Draw("FL same");
  gr_PtRaaTM25020_00_20_model->Draw("FL same");
  gr_PtRaaEL5020_00_20_model->Draw("same E2F");
  gr_PtRaaSHM5020_00_20_model->Draw("FL same");

  gr_PtRaaStat5020_00_20->Draw("samePE");
  gr_PtRaaSyst5020_00_20->Draw("sameE2");
    
  
  boxEle0020->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.6,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.45,0.84,"Pb#font[122]{-}Pb, 0#font[122]{-}20%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.45,0.77,"Inclusive J/#psi, 2.5 < #it{y} < 4");

  TLegend *legend = new TLegend(0.43,0.41,0.8,0.70);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_00_20,lg_data,"P");
  legend->AddEntry(gr_PtRaaTM15020_00_20_model,lg_TM1,"f");
  legend->AddEntry(gr_PtRaaTM25020_00_20_model,lg_TM2,"f");
  legend->AddEntry(gr_PtRaaSHM5020_00_20_model,lg_SHM,"f");
  legend->AddEntry(gr_PtRaaEL5020_00_20_model,lg_EL,"f");
    
  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_00_20_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;

  TFile *file=new TFile("Jpsi_RAA_Npart.root","UPDATE");
  file->cd();
 
  /* gr_PtRaaTM15020_0_20_model->Write("gr_RaaPt_Ralf_Rapp_5020_midy_0_10_model"); */
  /* gr_PtRaaTM25020_0_20_model->Write("gr_RaaPt_Pengfei_5020_midy_0_10_model"); */
  /* gr_PtRaaSHM5020_0_20_model->Write("gr_RaaPt_SHM_5020_midy_0_10_model"); */

  gr_PtRaaTM15020_00_20_model->Write("gr_RaaPt_Ralf_Rapp_5020_fwdy_0_20_model"); 
  gr_PtRaaTM25020_00_20_model->Write("gr_RaaPt_pengfei_5020_fwdy_0_20_model"); 
  gr_PtRaaEL5020_00_20_model->Write("gr_RaaPt_Eloss_5020_fwdy_0_20_model"); 
  gr_PtRaaSHM5020_00_20_model->Write("gr_RaaPt_SHM_5020_fwdy_0_20_model"); 

  
}


void plot_raa_pt_20_40(){
  
  TGraphErrors *gr_PtRaaStat5020_20_40 = (TGraphErrors*) GetPtRaaStat5020_20_40();
  TGraphErrors *gr_PtRaaSyst5020_20_40  = (TGraphErrors*)GetPtRaaSyst5020_20_40();

  
  TGraph * gr_PtRaaTM15020_20_40_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTAMU_pt_raa_20_40);
  TGraph * gr_PtRaaTM25020_20_40_model=  (TGraph *) GetPtRaaTM25020_model(28,fileTHUA_pt_raa_20_40);
  TGraph * gr_PtRaaSHM5020_20_40_model=  (TGraph *) GetPtRaaTM15020_model(28,fileSHM_pt_raa_20_40);
  //  TGraph * gr_PtRaaSHM5020_20_40_model=  (TGraph *) GetPtRaaSHM5020_model(100,fileSHM_pt_raa_20_40);

  TGraphAsymmErrors * gr_PtRaaEL5020_20_40_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEnergy_loss_model,"RAA_binned_centrality_20_40_ForwardRap");
    
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_20_40_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_20_40_model->SetLineColor(ci1);

  gr_PtRaaTM15020_20_40_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_20_40_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_20_40_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_20_40_model->SetLineColor(kBlue+1);

  gr_PtRaaEL5020_20_40_model->SetFillColorAlpha(kPink+1,0.4);
  gr_PtRaaEL5020_20_40_model->SetLineColor(kPink+9);
  
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.88,0.06,0.06,0.015,0.015,504,504);
  
  
  TBox *boxEle2040    = new TBox(19.3,1.-NormUncert1_fwdy_20_40 ,20,1.+NormUncert1_fwdy_20_40);
  boxEle2040->SetFillColor(kRed);

  
  SetTGraphError(gr_PtRaaStat5020_20_40,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_20_40,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_20_40,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_20_40_model->Draw("FL same");
  gr_PtRaaTM25020_20_40_model->Draw("FL same");
  gr_PtRaaEL5020_20_40_model->Draw("same E2");

  gr_PtRaaSHM5020_20_40_model->Draw("FL same");

  gr_PtRaaStat5020_20_40->Draw("samePE");
  gr_PtRaaSyst5020_20_40->Draw("sameE2");

   boxEle2040 ->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.46,0.82,"Pb#font[122]{-}Pb, 20#font[122]{-}40%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.45,0.75,"Inclusive J/#psi, 2.5 < #it{y} < 4");

  


  TLegend *legend = new TLegend(0.45,0.44,0.85,0.77);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtRaaStat5020_20_40,lg_data,"P");
  legend->AddEntry(gr_PtRaaTM15020_20_40_model,lg_TM1,"f");
  legend->AddEntry(gr_PtRaaTM25020_20_40_model,lg_TM2,"f");
  legend->AddEntry(gr_PtRaaSHM5020_20_40_model,lg_SHM,"f");
  legend->AddEntry(gr_PtRaaEL5020_20_40_model,lg_EL,"f");
    

  //  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_20_40_015_model_mm.pdf");

  
  delete mh2Dummy;
  delete c_temp;
}


void plot_raa_pt_40_90(){
  
  TGraphErrors *gr_PtRaaStat5020_40_90 = (TGraphErrors*) GetPtRaaStat5020_40_90();
  TGraphErrors *gr_PtRaaSyst5020_40_90  = (TGraphErrors*)GetPtRaaSyst5020_40_90();

  
  TGraph * gr_PtRaaTM15020_40_90_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTAMU_pt_raa_40_90);
  TGraph * gr_PtRaaTM25020_40_90_model=  (TGraph *) GetPtRaaTM25020_model(28,fileTHUA_pt_raa_40_90);
  TGraph * gr_PtRaaSHM5020_40_90_model=  (TGraph *) GetPtRaaSHM5020_model(100,fileSHM_pt_raa_40_90);

  TGraphAsymmErrors * gr_PtRaaEL5020_40_90_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEnergy_loss_model,"RAA_binned_centrality_40_90_ForwardRap");
    
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_40_90_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_40_90_model->SetLineColor(ci1);

  gr_PtRaaTM15020_40_90_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_40_90_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_40_90_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_40_90_model->SetLineColor(kBlue+1);

  gr_PtRaaEL5020_40_90_model->SetFillColorAlpha(kPink+1,0.4);
  gr_PtRaaEL5020_40_90_model->SetLineColor(kPink+9);

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.88,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(19.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  TBox *boxEle4090    = new TBox(19.3,1.-NormUncert1_fwdy_40_90 ,20,1.+NormUncert1_fwdy_40_90);
  boxEle4090->SetFillColor(kRed);

  
  SetTGraphError(gr_PtRaaStat5020_40_90,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_40_90,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_40_90,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_40_90_model->Draw("FL same");

  gr_PtRaaTM25020_40_90_model->Draw("FL same");
  gr_PtRaaEL5020_40_90_model->Draw("same E2");

  //gr_PtRaaSHM5020_40_90_model->Draw("FL same");

  gr_PtRaaStat5020_40_90->Draw("samePE");
  gr_PtRaaSyst5020_40_90->Draw("sameE2");

   boxEle4090->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  /* tex1.DrawLatex(0.45,0.84,"Pb-Pb, 40-90%, #sqrt{#it{s}_{NN}} = 5.02 TeV"); */
  /* tex1.DrawLatex(0.51,0.77,"Inclusive J/#psi, 2.5<#it{y}<4"); */

  tex1.DrawLatex(0.46,0.82,"Pb#font[122]{-}Pb, 40#font[122]{-}90%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.45,0.75,"Inclusive J/#psi, 2.5 < #it{y} < 4");
  
  TLegend *legend = new TLegend(0.13,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_40_90,lg_data,"P");
  legend->AddEntry(gr_PtRaaTM15020_40_90_model,lg_TM1,"f");
  legend->AddEntry(gr_PtRaaTM25020_40_90_model,lg_TM2,"f");
  legend->AddEntry(gr_PtRaaSHM5020_40_90_model,lg_SHM,"f");
  legend->AddEntry(gr_PtRaaEL5020_40_90_model,lg_EL,"f");

  //  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_40_90_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;
}
void plot_raa_pt_all()
{


  TGraphErrors *gr_PtRaaStat5020_00_20 = (TGraphErrors*)GetPtRaaStat5020_00_20();
  TGraphErrors *gr_PtRaaSyst5020_00_20  = (TGraphErrors*)GetPtRaaSyst5020_00_20();

  TGraphErrors *gr_PtRaaStat5020_20_40 = (TGraphErrors*)GetPtRaaStat5020_20_40();
  TGraphErrors *gr_PtRaaSyst5020_20_40  = (TGraphErrors*)GetPtRaaSyst5020_20_40();

  TGraphErrors *gr_PtRaaStat5020_40_90 = (TGraphErrors*)GetPtRaaStat5020_40_90();
  TGraphErrors *gr_PtRaaSyst5020_40_90  = (TGraphErrors*)GetPtRaaSyst5020_40_90();
  

  SetTGraphError(gr_PtRaaStat5020_00_20,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_20,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_00_20,0.3);

  SetTGraphError(gr_PtRaaStat5020_20_40,20,2.5,4,4,2,0);
  SetTGraphError(gr_PtRaaSyst5020_20_40,20,2.5,4,4,2,0);

  SetErrorX(gr_PtRaaSyst5020_20_40,0.3);

  
  SetTGraphError(gr_PtRaaStat5020_40_90,20,2.5,1,1,2,0);
  SetTGraphError(gr_PtRaaSyst5020_40_90,20,2.5,1,1,2,0);

  SetErrorX(gr_PtRaaSyst5020_40_90,0.3);

  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2.2);
  //  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.88,0.06,0.06,0.015,0.015,504,504);
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.9,0.06,0.06,0.015,0.015,504,504);  


  TBox *boxEle0020    = new TBox(18.5,1.-NormUncert1_fwdy_0_20 ,19,1.+NormUncert1_fwdy_0_20);
  boxEle0020->SetFillColor(kRed);

  

  TBox *boxEle2040    = new TBox(19,1.-NormUncert1_fwdy_20_40 ,19.5,1.+NormUncert1_fwdy_20_40);
  boxEle2040->SetFillColor(kBlue);

  TBox *boxEle4090    = new TBox(19.5,1.-NormUncert1_fwdy_40_90 ,20,1.+NormUncert1_fwdy_40_90);
  boxEle4090->SetFillColor(kBlack);
  
 
  pad1->cd();
  mh2Dummy->Draw();


  gr_PtRaaStat5020_00_20->Draw("samePE");
  gr_PtRaaSyst5020_00_20->Draw("sameE2");
  
  
  gr_PtRaaStat5020_20_40->Draw("samePE");
  gr_PtRaaSyst5020_20_40->Draw("sameE2");

  gr_PtRaaStat5020_40_90->Draw("samePE");
  gr_PtRaaSyst5020_40_90->Draw("sameE2");

  boxEle0020->Draw("sameE2");
  boxEle2040->Draw("sameE2");
  boxEle4090->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.052);

  tex1.DrawLatex(0.47,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, 2.5 < #it{y} < 4");

  
  TLegend *legend = new TLegend(0.17,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_00_20,"0#font[122]{-}20%","P");
  legend->AddEntry( gr_PtRaaStat5020_20_40,"20#font[122]{-}40%","P");
  legend->AddEntry( gr_PtRaaStat5020_40_90,"40#font[122]{-}90%","P");
    
  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_all_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;

  

}

TGraphErrors *GetPtRaaStat5020_00_20(){

  TGraphErrors* grAPtRaaStat5020_0_20= (TGraphErrors *) final_results_pt_fwdy_00_20 ->Get("gr_RAA_centbin1");
  return grAPtRaaStat5020_0_20;

}
TGraphErrors *GetPtRaaSyst5020_00_20(){

  TGraphErrors* grAPtRaaSyst5020_0_20= (TGraphErrors *) final_results_pt_fwdy_00_20 ->Get("gr_RAA_syst_centbin1");
  return grAPtRaaSyst5020_0_20;
}

TGraphErrors *GetPtRaaStat5020_20_40(){

  TGraphErrors* grAPtRaaStat5020_20_40= (TGraphErrors *) final_results_pt_fwdy_20_40 ->Get("gr_RAA_centbin2");
  return grAPtRaaStat5020_20_40;

}
TGraphErrors *GetPtRaaSyst5020_20_40(){

  TGraphErrors* grAPtRaaSyst5020_20_40= (TGraphErrors *) final_results_pt_fwdy_20_40 ->Get("gr_RAA_syst_centbin2");
  return grAPtRaaSyst5020_20_40;
}

TGraphErrors *GetPtRaaStat5020_40_90(){

  TGraphErrors* grAPtRaaStat5020_40_90= (TGraphErrors *) final_results_pt_fwdy_40_90 ->Get("gr_RAA_centbin3");
  return grAPtRaaStat5020_40_90;

}
TGraphErrors *GetPtRaaSyst5020_40_90(){

  TGraphErrors* grAPtRaaSyst5020_40_90= (TGraphErrors *) final_results_pt_fwdy_40_90 ->Get("gr_RAA_syst_centbin3");
  return grAPtRaaSyst5020_40_90;
}



