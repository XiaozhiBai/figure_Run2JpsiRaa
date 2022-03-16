//*******************************************************************************
// plot the results                                                             *
// by Xiaozhi Bai xiaozhi.bai@cern.ch baixiaozhi@ustc.edu.cn                    *
//  Mon Dec 27 14:23:20 CST 2021                                                *
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

void plot_spectrum_pt_0_10();
void plot_spectrum_pt_30_50();

inline TGraphErrors *GetPtSpecStat5020_00_10();
inline TGraphErrors *GetPtSpecSyst5020_00_10();


inline TGraphErrors *GetPtSpecStat5020_30_50();
inline TGraphErrors *GetPtSpecSyst5020_30_50();


TFile *final_results_pt_midy;
const char *fileTAMU_pt_spectrum_0_10;
const char *fileTinghua_pt_spectrum_0_10;
const char *fileSHM_pt_spectrum_0_10;

const char *fileTAMU_pt_spectrum_30_50;
const char *fileTinghua_pt_spectrum_30_50;
const char *fileSHM_pt_spectrum_30_50;

void plot_pt_spectrum_ee()
{
  SetStyle();
 
  final_results_pt_midy=new TFile("input/data/Raa_final.root","READ");

  fileTAMU_pt_spectrum_0_10 = "../models/Ralf_Rapp/data/m0-10dNdy.dat";
  fileTinghua_pt_spectrum_0_10 = "../models/PengfeiTM2/fig--central-rapidity-2022/spectrum/theory-spectrum-cent010.dat";  
  fileSHM_pt_spectrum_0_10 = "input/models/SHM_PtDep_5020_midy_Cent0_11012019.txt";    

  fileTAMU_pt_spectrum_30_50 = "../models/Ralf_Rapp/data/m30-50dNdy.dat";

  fileTinghua_pt_spectrum_30_50= "../models/PengfeiTM2/fig--central-rapidity-2022/spectrum/theory-spectrum-cent3050.dat";
  fileSHM_pt_spectrum_30_50 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";    

  
  gStyle->SetOptStat(0);
  plot_spectrum_pt_0_10();
  plot_spectrum_pt_30_50();

}
void plot_spectrum_pt_0_10(){

  TGraphErrors *gr_PtSpecStat5020_00_10 = (TGraphErrors*)GetPtSpecStat5020_00_10();
  TGraphErrors *gr_PtSpecSyst5020_00_10  = (TGraphErrors*)GetPtSpecSyst5020_00_10();


  TGraph * gr_PtSpecTM15020_00_10_model=  (TGraph *)GetPtSpecTM1_5020_model(16,fileTAMU_pt_spectrum_0_10);
  TGraph * gr_PtSpecTM25020_00_10_model=  (TGraph *)GetPtSpecTM2_5020_model(16,fileTinghua_pt_spectrum_0_10);
  TGraph * gr_PtSpecSHM5020_00_10_model=   (TGraph *)GetPtSpecSHM_5020_model(100,fileSHM_pt_spectrum_0_10);
  
  TGraph * gr_ratio_PtSpecTM1_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_00_10,gr_PtSpecSyst5020_00_10,gr_PtSpecTM15020_00_10_model);
  TGraph * gr_ratio_PtSpecTM2_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_00_10,gr_PtSpecSyst5020_00_10,gr_PtSpecTM25020_00_10_model);


  TGraphErrors * gr_ratio_uncertainty_data=(TGraphErrors *) GetRatioDataUncertainty(gr_PtSpecStat5020_00_10,gr_PtSpecSyst5020_00_10);
    
  gr_PtSpecTM15020_00_10_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_00_10_model->SetLineColor(kOrange+1);

  gr_PtSpecTM15020_00_10_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_00_10_model->SetLineColor(kOrange+1);

  gr_PtSpecTM25020_00_10_model  ->SetFillColorAlpha(kBlue,0.15);
  gr_PtSpecTM25020_00_10_model ->SetLineColor(kBlue);

  gr_ratio_PtSpecTM1_data  ->SetFillColorAlpha(kOrange+1,0.2);
  gr_ratio_PtSpecTM1_data->SetLineColor(kOrange+1);

  gr_ratio_PtSpecTM2_data  ->SetFillColorAlpha(kBlue,0.15);
  gr_ratio_PtSpecTM2_data->SetLineColor(kBlue);

  gr_ratio_uncertainty_data->SetFillColorAlpha(kRed,0.45);
  gr_ratio_uncertainty_data->SetLineColor(kRed);
  

  
 
  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtSpecSHM5020_00_10_model->SetFillColorAlpha(ci1,0.2);
  gr_PtSpecSHM5020_00_10_model->SetLineColor(ci1);

  TCanvas *c_temp=new TCanvas("c_temp","",1000,1000);
  TPad *pad1 = new TPad("pad1", "", 0, 0.4, 1, 1);
  TPad *pad2 = new TPad("pad2", "", 0, 0., 1, 0.4); 

  SetPad(pad1,0.02,0.,0.13,0.02);
  SetPad(pad2,0.,0.25,0.13,0.02);
  
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLogy();
  
  TH2F * h_dummy1=new TH2F("h_dummy1",";#it{p}_{T} (GeV/#it{c});1/#it{N}_{ev}d^{2}#it{N}/d#it{y}d#it{p}_{T} (GeV/#it{c})^{-1}",100,0,15,100,2e-6,0.3);
  TH2F * h_dummy2=new TH2F("h_dummy2",";#it{p}_{T} (GeV/#it{c}); Model/Data",100,0,15,100,1e-2,2.5);

  SetTH2F(h_dummy1,0.07,0.07,0.9,0.9,0.05,0.06,0.01,0.01,504,504);
  SetTH2F(h_dummy2,0.11,0.11, 1,0.5, 0.1,0.09, 0.02,0.02, 504,504);

  SetTGraphError(gr_PtSpecStat5020_00_10,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtSpecSyst5020_00_10,20,2.5,2,2,2,0);

  SetErrorX(gr_ratio_uncertainty_data,0.2);
  SetErrorX(gr_PtSpecSyst5020_00_10,0.5);
  
  h_dummy1->Draw();

  gr_PtSpecTM25020_00_10_model->Draw("FL");
  gr_PtSpecSHM5020_00_10_model->Draw("FL same");
  gr_PtSpecTM15020_00_10_model->Draw("FL same");
  gr_PtSpecTM25020_00_10_model->Draw("FL same");

  gr_PtSpecStat5020_00_10->Draw("samePE");
  gr_PtSpecSyst5020_00_10->Draw("sameE2");

  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.07);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.88,"ALICE");
  tex1.SetTextSize(0.058);

  tex1.DrawLatex(0.5,0.8,"Pb-Pb, 0-10%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.5,0.72,"Inclusive J/#psi, |#it{y}|<0.9");

  TLegend *legend = new TLegend(0.17,0.06,0.46,0.35);
  SetLegend(legend,42,0.06,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtSpecStat5020_00_10,lg_data,"P");
  legend->AddEntry(gr_PtSpecTM15020_00_10_model,lg_TM1,"f");
  legend->AddEntry(gr_PtSpecTM25020_00_10_model,lg_TM2,"f");
  legend->AddEntry(gr_PtSpecSHM5020_00_10_model,lg_SHM,"f");
  legend->Draw();

  pad2->cd();

  TLine *line_unity= (TLine *)GetLine(0,1.0,15,1.0,2,3,7);
  
  h_dummy2->Draw();
  line_unity->Draw("same");

  gr_ratio_PtSpecTM1_data->Draw("FL same");
  gr_ratio_PtSpecTM2_data->Draw("FL same");
  gr_ratio_uncertainty_data->Draw("sameE2");
  c_temp->SaveAs("output/Spectrum_Vs_pt_0_10_015_model_ee.pdf");
  
  delete h_dummy1;
  delete h_dummy2;
  delete c_temp;
}

void plot_spectrum_pt_30_50(){

  TGraphErrors *gr_PtSpecStat5020_30_50 = (TGraphErrors*)GetPtSpecStat5020_30_50();
  TGraphErrors *gr_PtSpecSyst5020_30_50  = (TGraphErrors*)GetPtSpecSyst5020_30_50();

  
  /* TGraph * gr_PtSpecTM15020_30_50_model=  (TGraph *)GetPtSpecTM15020_30_50_model(); */
  /* TGraph * gr_PtSpecTM25020_30_50_model=  (TGraph *)GetPtSpecTM25020_30_50_model(); */
  /* TGraph * gr_PtSpecSHM5020_30_50_model=  (TGraph *)GetPtSpecSHM5020_30_50_model(); */

  

  TGraph * gr_PtSpecTM15020_30_50_model=  (TGraph *)GetPtSpecTM1_5020_model(12,fileTAMU_pt_spectrum_30_50);
  TGraph * gr_PtSpecTM25020_30_50_model=  (TGraph *)GetPtSpecTM2_5020_model(12,fileTinghua_pt_spectrum_30_50);
  TGraph * gr_PtSpecSHM5020_30_50_model=   (TGraph *)GetPtSpecSHM_5020_model(100,fileSHM_pt_spectrum_30_50);

  
  TGraph * gr_ratio_PtSpecTM1_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_30_50,gr_PtSpecSyst5020_30_50,gr_PtSpecTM15020_30_50_model);
  TGraph * gr_ratio_PtSpecTM2_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_30_50,gr_PtSpecSyst5020_30_50,gr_PtSpecTM25020_30_50_model);

  TGraphErrors * gr_ratio_uncertainty_data=(TGraphErrors *) GetRatioDataUncertainty(gr_PtSpecStat5020_30_50,gr_PtSpecSyst5020_30_50);

  
  
  gr_PtSpecTM15020_30_50_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_30_50_model->SetLineColor(kOrange+1);

  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtSpecSHM5020_30_50_model->SetFillColorAlpha(ci1,0.2);
  gr_PtSpecSHM5020_30_50_model->SetLineColor(ci1);

  gr_PtSpecTM25020_30_50_model  ->SetFillColorAlpha(kBlue,0.15);
  gr_PtSpecTM25020_30_50_model ->SetLineColor(kBlue);

  gr_ratio_PtSpecTM1_data  ->SetFillColorAlpha(kOrange+1,0.2);
  gr_ratio_PtSpecTM1_data ->SetLineColor(kOrange+1);

  gr_ratio_PtSpecTM2_data  ->SetFillColorAlpha(kBlue,0.15);
  gr_ratio_PtSpecTM2_data ->SetLineColor(kBlue);
  
  gr_ratio_uncertainty_data->SetFillColorAlpha(kRed,0.45);
  gr_ratio_uncertainty_data->SetLineColor(kRed);

  

  TCanvas *c_temp=new TCanvas("c_temp","",1000,1000);
  TPad *pad1 = new TPad("pad1", "", 0, 0.4, 1, 1);
  TPad *pad2 = new TPad("pad2", "", 0, 0., 1, 0.4); 

  SetPad(pad1,0.02,0.,0.13,0.02);
  SetPad(pad2,0.,0.25,0.13,0.02);
  
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLogy();


  TH2F * h_dummy1=new TH2F("h_dummy1",";#it{p}_{T} (GeV/#it{c});1/#it{N}_{ev}d^{2}#it{N}/d#it{y}d#it{p}_{T} (GeV/#it{c})^{-1}",100,0,15,100,2e-6,3e-2);
  TH2F * h_dummy2=new TH2F("h_dummy2",";#it{p}_{T} (GeV/#it{c}); Model/Data",100,0,15,100,1e-2,2.1);

  SetTH2F(h_dummy1,0.07,0.07,0.9,0.9,0.05,0.06,0.01,0.01,504,504);
  SetTH2F(h_dummy2,0.11,0.11, 1,0.5, 0.1,0.09, 0.02,0.02, 504,504);

  SetTGraphError(gr_PtSpecStat5020_30_50,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtSpecSyst5020_30_50,20,2.5,2,2,2,0);

  //  SetTGraphError(gr_ratio_uncertainty_data,20,2.5,2,2,2,0);

  SetErrorX(gr_PtSpecSyst5020_30_50,0.5);
  SetErrorX(gr_ratio_uncertainty_data,0.2);
  

  
  
  h_dummy1->Draw();

  gr_PtSpecSHM5020_30_50_model->Draw("FL same");
  gr_PtSpecTM15020_30_50_model->Draw("FL same");
  gr_PtSpecStat5020_30_50->Draw("samePE");
  gr_PtSpecSyst5020_30_50->Draw("sameE2");

  gr_PtSpecTM25020_30_50_model->Draw("FL same");

  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.07);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.88,"ALICE");
  tex1.SetTextSize(0.058);

  tex1.DrawLatex(0.46,0.8,"Pb-Pb, 30-50%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.46,0.72,"Inclusive J/#psi, |#it{y}|<0.9");

  
  TLegend *legend = new TLegend(0.17,0.06,0.46,0.35);
  SetLegend(legend,42,0.06,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtSpecStat5020_30_50,lg_data,"P");
  legend->AddEntry(gr_PtSpecTM15020_30_50_model,lg_TM1,"f");
  legend->AddEntry(gr_PtSpecTM25020_30_50_model,lg_TM2,"f");  
  legend->AddEntry(gr_PtSpecSHM5020_30_50_model,lg_SHM,"f");
  legend->Draw();


  pad2->cd();
  TLine *line_unity= (TLine *)GetLine(0,1.0,15,1.0,2,3,7);
  h_dummy2->Draw();
  line_unity->Draw("same");

  gr_ratio_uncertainty_data->Draw("sameE2");

  gr_ratio_PtSpecTM2_data->Draw("FL same");
  gr_ratio_PtSpecTM1_data->Draw("FL same");
  
  c_temp->SaveAs("output/Spectrum_Vs_pt_30_50_015_model_ee.pdf");


  delete h_dummy1;
  delete h_dummy2;
  
  delete c_temp;
}



TGraphErrors *GetPtSpecStat5020_00_10(){
  TH1F *PtSpecStat5020_00_10 = (TH1F *) final_results_pt_midy->Get("PbPb_yields_pt_sts_0_10");
  TGraphErrors* grPtSpecStat5020_00_10=new TGraphErrors(PtSpecStat5020_00_10);

  return grPtSpecStat5020_00_10;
}

TGraphErrors *GetPtSpecSyst5020_00_10(){
  TH1F *PtSpecSyst5020_00_10 = (TH1F *) final_results_pt_midy->Get("PbPb_yields_pt_sys_0_10");
  TGraphErrors* grPtSpecSyst5020_00_10=new TGraphErrors(PtSpecSyst5020_00_10);

  return grPtSpecSyst5020_00_10;
}

TGraphErrors *GetPtSpecStat5020_30_50(){
  TH1F *PtSpecStat5020_30_50 = (TH1F *) final_results_pt_midy->Get("PbPb_yields_pt_sts_30_50");
  TGraphErrors* grPtSpecStat5020_30_50=new TGraphErrors(PtSpecStat5020_30_50);

  return grPtSpecStat5020_30_50;
}

TGraphErrors *GetPtSpecSyst5020_30_50(){
  TH1F *PtSpecSyst5020_30_50 = (TH1F *) final_results_pt_midy->Get("PbPb_yields_pt_sys_30_50");
  TGraphErrors* grPtSpecSyst5020_30_50=new TGraphErrors(PtSpecSyst5020_30_50);

  return grPtSpecSyst5020_30_50;
}

