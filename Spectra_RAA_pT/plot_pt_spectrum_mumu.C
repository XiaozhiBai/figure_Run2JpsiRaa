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

void plot_spectrum_pt_0_20();
void plot_spectrum_pt_20_40();
void plot_spectrum_pt_40_90();


inline TGraphErrors *GetPtSpecStat5020_00_20();
inline TGraphErrors *GetPtSpecSyst5020_00_20();

inline TGraphErrors *GetPtSpecSyst5020_20_40();
inline TGraphErrors *GetPtSpecStat5020_20_40();

inline TGraphErrors *GetPtSpecSyst5020_40_90();
inline TGraphErrors *GetPtSpecStat5020_40_90();

inline TGraph *GetPtSpecTM15020_00_20_model();
inline TGraph *GetPtSpecTM25020_00_20_model();
inline TGraph *GetPtSpecSHM5020_00_20_model();

inline TGraph *GetPtSpecTM15020_20_40_model();
inline TGraph *GetPtSpecTM25020_20_40_model();
inline TGraph *GetPtSpecSHM5020_20_40_model();

inline TGraph *GetPtSpecTM15020_40_90_model();
inline TGraph *GetPtSpecTM25020_40_90_model();
inline TGraph *GetPtSpecSHM5020_40_90_model();


TFile *final_results_pt_fwdy;
const char *fileTAMU_pt_spectrum_0_20;
const char *fileTinghua_pt_spectrum_0_20;
const char *fileSHM_pt_spectrum_0_20;

const char *fileTAMU_pt_spectrum_20_40;
const char *fileTinghua_pt_spectrum_20_40;
const char *fileSHM_pt_spectrum_20_40;

const char *fileTAMU_pt_spectrum_40_90;
const char *fileTinghua_pt_spectrum_40_90;
const char *fileSHM_pt_spectrum_40_90;


void plot_pt_spectrum_mumu()
{

  SetStyle();
 
  final_results_pt_fwdy=new TFile("input/data/mumu/Yields/Yields_vs_pT.root","READ");

  fileTAMU_pt_spectrum_0_20 = "../models/Ralf_Rapp/data/f0-20dNdy.dat";
  fileTinghua_pt_spectrum_0_20 = "../models/PengfeiTM2/spectrum--new-pp-input2022Feb/theory-spectrum-cent020-new-pp-input.dat";
  fileSHM_pt_spectrum_0_20 = "input/models/SHM_PtDep_5020_midy_Cent0_11012019.txt";    

  fileTAMU_pt_spectrum_20_40 = "../models/Ralf_Rapp/data/f20-40dNdy.dat";
  fileTinghua_pt_spectrum_20_40= "../models/PengfeiTM2/spectrum--new-pp-input2022Feb/theory-spectrum-cent2040-new-pp-input.dat";
  fileSHM_pt_spectrum_20_40 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";    

  fileTAMU_pt_spectrum_40_90 = "../models/Ralf_Rapp/data/f40-90dNdy.dat";
  fileTinghua_pt_spectrum_40_90= "../models/PengfeiTM2/spectrum--new-pp-input2022Feb/theory-spectrum-cent4090-new-pp-input.dat";
  fileSHM_pt_spectrum_40_90 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";    
  

  
  gStyle->SetOptStat(0);
  plot_spectrum_pt_0_20();
  plot_spectrum_pt_20_40();
  plot_spectrum_pt_40_90();

}
void plot_spectrum_pt_0_20(){

  TGraphErrors *gr_PtSpecStat5020_00_20 = (TGraphErrors*)GetPtSpecStat5020_00_20();
  TGraphErrors *gr_PtSpecSyst5020_00_20  = (TGraphErrors*)GetPtSpecSyst5020_00_20();

  TGraph * gr_PtSpecTM15020_00_20_model=  (TGraph *)GetPtSpecTM1_5020_model(28,fileTAMU_pt_spectrum_0_20);
  TGraph * gr_PtSpecTM25020_00_20_model=  (TGraph *)GetPtSpecTM2_5020_model(28,fileTinghua_pt_spectrum_0_20);
  TGraph * gr_PtSpecSHM5020_00_20_model=  (TGraph *)GetPtSpecSHM_5020_model(100,fileSHM_pt_spectrum_0_20);

  TGraph * gr_ratio_PtSpecTM1_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_00_20,gr_PtSpecSyst5020_00_20,gr_PtSpecTM15020_00_20_model);
  TGraph * gr_ratio_PtSpecTM2_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_00_20,gr_PtSpecSyst5020_00_20,gr_PtSpecTM25020_00_20_model);


  TGraphErrors * gr_ratio_uncertainty_data=(TGraphErrors *) GetRatioDataUncertainty(gr_PtSpecStat5020_00_20,gr_PtSpecSyst5020_00_20);
  
  gr_PtSpecTM15020_00_20_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_00_20_model->SetLineColor(kOrange+1);

  gr_PtSpecTM15020_00_20_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_00_20_model->SetLineColor(kOrange+1);

  gr_PtSpecTM25020_00_20_model  ->SetFillColorAlpha(kBlue,0.15);
  gr_PtSpecTM25020_00_20_model ->SetLineColor(kBlue);

  gr_ratio_PtSpecTM1_data  ->SetFillColorAlpha(kOrange,0.15);
  gr_ratio_PtSpecTM1_data->SetLineColor(kOrange);

  gr_ratio_PtSpecTM2_data  ->SetFillColorAlpha(kBlue,0.15);
  gr_ratio_PtSpecTM2_data->SetLineColor(kBlue);

  gr_ratio_uncertainty_data->SetFillColorAlpha(kRed,0.45);
  gr_ratio_uncertainty_data->SetLineColor(kRed);
 
  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtSpecSHM5020_00_20_model->SetFillColorAlpha(ci1,0.2);
  gr_PtSpecSHM5020_00_20_model->SetLineColor(ci1);

  TCanvas *c_temp=new TCanvas("c_temp","",1000,1000);
  TPad *pad1 = new TPad("pad1", "", 0, 0.4, 1, 1);
  TPad *pad2 = new TPad("pad2", "", 0, 0., 1, 0.4); 

  SetPad(pad1,0.02,0.,0.15,0.02);
  SetPad(pad2,0.,0.25,0.15,0.02);
  
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLogy();
  
  TH2F * h_dummy1=new TH2F("h_dummy1",";#it{p}_{T} (GeV/#it{c});1/#it{N}_{ev}d^{2}#it{N}/d#it{y}d#it{p}_{T} (GeV/#it{c})^{-1}",100,0,20,100,1.1e-7,0.1);
  TH2F * h_dummy2=new TH2F("h_dummy2",";#it{p}_{T} (GeV/#it{c}); Model/Data",100,0,20,100,1e-2,2.2);

  SetTH2F(h_dummy1,0.07,0.07,0.9,1,0.05,0.06,0.01,0.01,504,504);
  SetTH2F(h_dummy2,0.11,0.11, 1,0.5, 0.1,0.09, 0.02,0.02, 504,504);

  SetTGraphError(gr_PtSpecStat5020_00_20,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtSpecSyst5020_00_20,20,2.5,2,2,2,0);
  
  SetErrorX(gr_PtSpecSyst5020_00_20,0.5);
  SetErrorX(gr_ratio_uncertainty_data,0.2);
  
  h_dummy1->Draw();

  //  gr_PtSpecSHM5020_00_20_model->Draw("FL same");
  gr_PtSpecTM15020_00_20_model->Draw("FL same");
  gr_PtSpecTM25020_00_20_model->Draw("FL same");


    
  gr_PtSpecStat5020_00_20->Draw("samePE");
  gr_PtSpecSyst5020_00_20->Draw("sameE2");

  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.07);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.88,"ALICE");
  tex1.SetTextSize(0.058);

  tex1.DrawLatex(0.5,0.8,"Pb-Pb, 0-20%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.5,0.72,"Inclusive J/#psi, 2.5<#it{y}<4");

  TLegend *legend = new TLegend(0.2,0.06,0.45,0.35);
  SetLegend(legend,42,0.06,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtSpecStat5020_00_20,lg_data,"P");
  legend->AddEntry(gr_PtSpecTM15020_00_20_model,lg_TM1,"f");
  legend->AddEntry(gr_PtSpecTM25020_00_20_model,lg_TM2,"f");
  legend->AddEntry(gr_PtSpecSHM5020_00_20_model,lg_SHM,"f");
  legend->Draw();

  pad2->cd();

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,2,3,7);
  
  h_dummy2->Draw();
  line_unity->Draw("same");
  gr_ratio_PtSpecTM1_data->Draw("FL same");
  gr_ratio_PtSpecTM2_data->Draw("FL same");

  gr_ratio_uncertainty_data->Draw("sameE2");
  c_temp->SaveAs("output/Spectrum_Vs_pt_0_20_015_model_mm.pdf");
  
  delete h_dummy1;
  delete h_dummy2;
  delete c_temp;
}

void plot_spectrum_pt_20_40(){

  TGraphErrors *gr_PtSpecStat5020_20_40 = (TGraphErrors*)GetPtSpecStat5020_20_40();
  TGraphErrors *gr_PtSpecSyst5020_20_40  = (TGraphErrors*)GetPtSpecSyst5020_20_40();



  TGraph * gr_PtSpecTM15020_20_40_model=  (TGraph *)GetPtSpecTM1_5020_model(28,fileTAMU_pt_spectrum_20_40); //!!!!!!!!!!!!!
  TGraph * gr_PtSpecTM25020_20_40_model=  (TGraph *)GetPtSpecTM2_5020_model(28,fileTinghua_pt_spectrum_20_40); //!!!!!!!!!! 
  TGraph * gr_PtSpecSHM5020_20_40_model=  (TGraph *)GetPtSpecSHM_5020_model(100,fileSHM_pt_spectrum_0_20); //!!!!!!!!!!


  
  TGraph * gr_ratio_PtSpecTM1_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_20_40,gr_PtSpecSyst5020_20_40,gr_PtSpecTM15020_20_40_model);
  TGraph * gr_ratio_PtSpecTM2_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_20_40,gr_PtSpecSyst5020_20_40,gr_PtSpecTM25020_20_40_model);


  TGraphErrors * gr_ratio_uncertainty_data=(TGraphErrors *) GetRatioDataUncertainty(gr_PtSpecStat5020_20_40,gr_PtSpecSyst5020_20_40);
   
  gr_PtSpecTM15020_20_40_model ->SetFillColorAlpha(kOrange+1,0.15);
  gr_PtSpecTM15020_20_40_model->SetLineColor(kOrange+1);

  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtSpecSHM5020_20_40_model->SetFillColorAlpha(ci1,0.2);
  gr_PtSpecSHM5020_20_40_model->SetLineColor(ci1);


  gr_PtSpecTM25020_20_40_model  ->SetFillColorAlpha(kBlue,0.15);
  gr_PtSpecTM25020_20_40_model ->SetLineColor(kBlue);

  gr_ratio_PtSpecTM1_data  ->SetFillColorAlpha(kOrange,0.15);
  gr_ratio_PtSpecTM1_data->SetLineColor(kOrange);

  gr_ratio_PtSpecTM2_data  ->SetFillColorAlpha(kBlue,0.15);
  gr_ratio_PtSpecTM2_data->SetLineColor(kBlue);

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
  
  TH2F * h_dummy1=new TH2F("h_dummy1",";#it{p}_{T} (GeV/#it{c});1/#it{N}_{ev}d^{2}#it{N}/d#it{y}d#it{p}_{T} (GeV/#it{c})^{-1}",100,0,20,100,3e-7,3e-2);
  TH2F * h_dummy2=new TH2F("h_dummy2",";#it{p}_{T} (GeV/#it{c}); Model/Data",100,0,20,100,1e-2,2.2);

  SetTH2F(h_dummy1,0.07,0.07,0.9,0.9,0.05,0.06,0.01,0.01,504,504);
  SetTH2F(h_dummy2,0.11,0.11, 1,0.5, 0.1,0.09, 0.02,0.02, 504,504);


  SetTGraphError(gr_PtSpecStat5020_20_40,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtSpecSyst5020_20_40,20,2.5,2,2,2,0);

  SetErrorX(gr_PtSpecSyst5020_20_40,0.5);

  SetErrorX(gr_ratio_uncertainty_data,0.2);
  
  
  h_dummy1->Draw();

  
  /* gr_PtSpecSHM5020_20_40_model->Draw("FL same"); */
  gr_PtSpecTM15020_20_40_model->Draw("FL same");
  gr_PtSpecTM25020_20_40_model->Draw("FL same");

  gr_PtSpecStat5020_20_40->Draw("samePE");
  gr_PtSpecSyst5020_20_40->Draw("sameE2");

 

  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.07);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.88,"ALICE");
  tex1.SetTextSize(0.058);

  tex1.DrawLatex(0.45,0.8,"Pb-Pb, 20-40%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.45,0.72,"Inclusive J/#psi, 2.5<#it{y}<4");

  
  TLegend *legend = new TLegend(0.17,0.05,0.52,0.3);
  SetLegend(legend,42,0.06,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtSpecStat5020_20_40,lg_data,"P");
  legend->AddEntry(gr_PtSpecTM15020_20_40_model,lg_TM1,"f");
  legend->AddEntry(gr_PtSpecTM25020_20_40_model,lg_TM2,"f");  
  legend->AddEntry(gr_PtSpecSHM5020_20_40_model,lg_SHM,"f");
  legend->Draw();


  pad2->cd();
  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,2,3,7);
  h_dummy2->Draw();
  line_unity->Draw("same");

  gr_ratio_uncertainty_data->Draw("sameE2");
  gr_ratio_PtSpecTM1_data->Draw("FL same");
  gr_ratio_PtSpecTM2_data->Draw("FL same");
  
  c_temp->SaveAs("output/Spectrum_Vs_pt_20_40_015_model_mm.pdf");


  delete h_dummy1;
  delete h_dummy2;
  
  delete c_temp;

}

void plot_spectrum_pt_40_90(){

  TGraphErrors *gr_PtSpecStat5020_40_90 = (TGraphErrors*)GetPtSpecStat5020_40_90();
  TGraphErrors *gr_PtSpecSyst5020_40_90  = (TGraphErrors*)GetPtSpecSyst5020_40_90();

  TGraph * gr_PtSpecTM15020_40_90_model=  (TGraph *)GetPtSpecTM1_5020_model(28,fileTAMU_pt_spectrum_40_90); //!!!!!!!!!!!!!
  TGraph * gr_PtSpecTM25020_40_90_model=  (TGraph *)GetPtSpecTM2_5020_model(28,fileTinghua_pt_spectrum_40_90); //!!!!!!!!!! 
  TGraph * gr_PtSpecSHM5020_40_90_model=  (TGraph *)GetPtSpecSHM_5020_model(100,fileSHM_pt_spectrum_0_20); //!!!!!!!!!!

  TGraph * gr_ratio_PtSpecTM1_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_40_90,gr_PtSpecSyst5020_40_90,gr_PtSpecTM15020_40_90_model);
  TGraph * gr_ratio_PtSpecTM2_data=(TGraph *) GetRatioDataModel(gr_PtSpecStat5020_40_90,gr_PtSpecSyst5020_40_90,gr_PtSpecTM25020_40_90_model);
  
  TGraphErrors * gr_ratio_uncertainty_data=(TGraphErrors *) GetRatioDataUncertainty(gr_PtSpecStat5020_40_90,gr_PtSpecSyst5020_40_90);
 
  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtSpecSHM5020_40_90_model->SetFillColorAlpha(ci1,0.2);
  gr_PtSpecSHM5020_40_90_model->SetLineColor(ci1);

  gr_PtSpecTM15020_40_90_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtSpecTM15020_40_90_model->SetLineColor(kOrange+1);

  
  gr_PtSpecTM25020_40_90_model  ->SetFillColorAlpha(kBlue,0.15);
  gr_PtSpecTM25020_40_90_model ->SetLineColor(kBlue);

  gr_ratio_PtSpecTM1_data  ->SetFillColorAlpha(kOrange,0.15);
  gr_ratio_PtSpecTM1_data ->SetLineColor(kOrange);

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
  
  TH2F * h_dummy1=new TH2F("h_dummy1",";#it{p}_{T} (GeV/#it{c});1/#it{N}_{ev}d^{2}#it{N}/d#it{y}d#it{p}_{T} (GeV/#it{c})^{-1}",100,0,20,100,2e-8,7e-3);
  TH2F * h_dummy2=new TH2F("h_dummy2",";#it{p}_{T} (GeV/#it{c}); Model/Data",100,0,20,100,1e-2,2.1);

  SetTH2F(h_dummy1,0.07,0.07,0.9,0.9,0.05,0.06,0.01,0.01,504,504);
  SetTH2F(h_dummy2,0.11,0.11, 1,0.5, 0.1,0.09, 0.02,0.02, 504,504);


  SetTGraphError(gr_PtSpecStat5020_40_90,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtSpecSyst5020_40_90,20,2.5,2,2,2,0);

  SetErrorX(gr_PtSpecSyst5020_40_90,0.5);
  SetErrorX(gr_ratio_uncertainty_data,0.2);  
  h_dummy1->Draw();
  
  /* gr_PtSpecSHM5020_40_90_model->Draw("FL same"); */

  gr_PtSpecTM15020_40_90_model->Draw("FL same");
  gr_PtSpecTM25020_40_90_model->Draw("FL same");
  gr_PtSpecStat5020_40_90->Draw("samePE");
  gr_PtSpecSyst5020_40_90->Draw("sameE2");

  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.07);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.88,"ALICE");
  tex1.SetTextSize(0.058);

  tex1.DrawLatex(0.45,0.8,"Pb-Pb, 40-90%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.45,0.72,"Inclusive J/#psi, 2.5<#it{y}<4");

  
  TLegend *legend = new TLegend(0.17,0.06,0.52,0.35);  
  SetLegend(legend,42,0.06,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtSpecStat5020_40_90,lg_data,"P");
  legend->AddEntry(gr_PtSpecTM15020_40_90_model,lg_TM1,"f");
  legend->AddEntry(gr_PtSpecTM25020_40_90_model,lg_TM2,"f");  
  legend->AddEntry(gr_PtSpecSHM5020_40_90_model,lg_SHM,"f");
  legend->Draw();


  pad2->cd();
  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,2,3,7);
  h_dummy2->Draw();

  line_unity->Draw("same");
  gr_ratio_uncertainty_data->Draw("sameE2");
  gr_ratio_PtSpecTM1_data->Draw("FL same");
  gr_ratio_PtSpecTM2_data->Draw("FL same");
  
  c_temp->SaveAs("output/Spectrum_Vs_pt_40_90_015_model_mm.pdf");


  delete h_dummy1;
  delete h_dummy2;
  
  delete c_temp;

}



TGraphErrors *GetPtSpecStat5020_00_20(){

  TGraphAsymmErrors* grAPtSpecStat5020_00_20 = (TGraphAsymmErrors *) final_results_pt_fwdy->Get("Yields_vs_pT_0to20");
  TGraphErrors *grPtSpecStat5020_00_20 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecStat5020_00_20);

  //    grPtSpecStat5020_00_20->Print("all");
  
  grPtSpecStat5020_00_20->RemovePoint(0);//!!!!!!!
  grPtSpecStat5020_00_20->RemovePoint(0);//!!!!!!!

  // grPtSpecStat5020_00_20->Print("all");
  
  return grPtSpecStat5020_00_20;
}

TGraphErrors *GetPtSpecSyst5020_00_20(){

  TGraphAsymmErrors * grAPtSpecSyst5020_00_20=(TGraphAsymmErrors*) final_results_pt_fwdy->Get("Syst_Yields_vs_pT_0to20");
  TGraphErrors *grPtSpecSyst5020_00_20=(TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecSyst5020_00_20);

  grPtSpecSyst5020_00_20->RemovePoint(0);//!!!!!!!
  grPtSpecSyst5020_00_20->RemovePoint(0);//!!!!!!!    
  return grPtSpecSyst5020_00_20;
}

TGraphErrors *GetPtSpecStat5020_20_40(){

  TGraphAsymmErrors* grAPtSpecStat5020_20_40 = (TGraphAsymmErrors *) final_results_pt_fwdy->Get("Yields_vs_pT_20to40");
  TGraphErrors *grPtSpecStat5020_20_40 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecStat5020_20_40);

  grPtSpecStat5020_20_40->RemovePoint(0);//!!!!!!!
  grPtSpecStat5020_20_40->RemovePoint(0);//!!!!!!!

  return grPtSpecStat5020_20_40;
}

TGraphErrors *GetPtSpecSyst5020_20_40(){

  TGraphAsymmErrors * grAPtSpecSyst5020_20_40=(TGraphAsymmErrors*) final_results_pt_fwdy->Get("Syst_Yields_vs_pT_20to40");
  TGraphErrors *grPtSpecSyst5020_20_40=(TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecSyst5020_20_40);

  grPtSpecSyst5020_20_40->RemovePoint(0);//!!!!!!!
  grPtSpecSyst5020_20_40->RemovePoint(0);//!!!!!!!    
  return grPtSpecSyst5020_20_40;
}


TGraphErrors *GetPtSpecStat5020_40_90(){

  TGraphAsymmErrors* grAPtSpecStat5020_40_90 = (TGraphAsymmErrors *) final_results_pt_fwdy->Get("Yields_vs_pT_40to90");
  TGraphErrors *grPtSpecStat5020_40_90 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecStat5020_40_90);

  grPtSpecStat5020_40_90->RemovePoint(0);//!!!!!!!
  grPtSpecStat5020_40_90->RemovePoint(0);//!!!!!!!

  return grPtSpecStat5020_40_90;
}

TGraphErrors *GetPtSpecSyst5020_40_90(){

  TGraphAsymmErrors * grAPtSpecSyst5020_40_90=(TGraphAsymmErrors*) final_results_pt_fwdy->Get("Syst_Yields_vs_pT_40to90");
  TGraphErrors *grPtSpecSyst5020_40_90=(TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtSpecSyst5020_40_90);

  grPtSpecSyst5020_40_90->RemovePoint(0);//!!!!!!!
  grPtSpecSyst5020_40_90->RemovePoint(0);//!!!!!!!
  
  return grPtSpecSyst5020_40_90;
}
