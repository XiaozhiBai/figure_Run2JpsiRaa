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



void plot_pt_raa_mm()
{
  SetStyle();
  gStyle->SetOptStat(0);

  final_results_pt_fwdy_00_20 =new TFile("input/data/mumu/RAA/RAA_vs_pT_0to20.root","READ");
  final_results_pt_fwdy_20_40 =new TFile("input/data/mumu/RAA/RAA_vs_pT_20to40.root","READ");
  final_results_pt_fwdy_40_90 =new TFile("input/data/mumu/RAA/RAA_vs_pT_40to90.root","READ");

  
  fileTAMU_pt_raa_00_20 = "input/models/TAMU/f0-20RAA.dat";
  fileTAMU_pt_raa_20_40 = "input/models/TAMU/f20-40RAA.dat";
  fileTAMU_pt_raa_40_90 = "input/models/TAMU/f40-90RAA.dat";

  fileTHUA_pt_raa_00_20 = "input/models/Tinghua/data_5020_forward/Part2/Raa_pt_f020.dat";
  fileTHUA_pt_raa_20_40 = "input/models/Tinghua/data_5020_forward/Part2/Raa_pt_f2040.dat";
  fileTHUA_pt_raa_40_90 = "input/models/Tinghua/data_5020_forward/Part2/Raa_pt_f4090.dat";
  
  fileSHM_pt_raa_00_20 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";
  fileSHM_pt_raa_20_40 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";
  fileSHM_pt_raa_40_90 = "input/models/SHM_PtDep_5020_midy_Cent3_11012019.txt";
  

  plot_raa_pt_0_20();
  plot_raa_pt_20_40();
  plot_raa_pt_40_90();
  plot_raa_pt_all();
}
void plot_raa_pt_0_20(){
  
  TGraphErrors *gr_PtRaaStat5020_00_20 = (TGraphErrors*)GetPtRaaStat5020_00_20();
  TGraphErrors *gr_PtRaaSyst5020_00_20  = (TGraphErrors*)GetPtRaaSyst5020_00_20();

  
  TGraph * gr_PtRaaTM15020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(30,fileTAMU_pt_raa_00_20);
  TGraph * gr_PtRaaTM25020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(30,fileTHUA_pt_raa_00_20);
  TGraph * gr_PtRaaSHM5020_00_20_model=  (TGraph *) GetPtRaaSHM5020_model(100,fileSHM_pt_raa_00_20);
  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_00_20_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_00_20_model->SetLineColor(ci1);

  gr_PtRaaTM15020_00_20_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_00_20_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_00_20_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_00_20_model->SetLineColor(kBlue+1);

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.1,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(19.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  SetTGraphError(gr_PtRaaStat5020_00_20,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_20,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_00_20,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_00_20_model->Draw("FL same");
  gr_PtRaaTM25020_00_20_model->Draw("FL same");
  //  gr_PtRaaSHM5020_00_20_model->Draw("FL same");

  gr_PtRaaStat5020_00_20->Draw("samePE");
  gr_PtRaaSyst5020_00_20->Draw("sameE2");

  // boxEle0010->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.47,0.84,"Pb-Pb, 0-20%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, 2.5<#it{y}<4");

  TLegend *legend = new TLegend(0.17,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtRaaStat5020_00_20,"Data","P");
  legend->AddEntry(gr_PtRaaTM15020_00_20_model,"TAMU","f");
  legend->AddEntry(gr_PtRaaTM25020_00_20_model,"THU","f");
  //legend->AddEntry(gr_PtRaaSHM5020_00_20_model,"SHM (Andronic et al.)","f");
    
  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_00_20_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;
}


void plot_raa_pt_20_40(){
  
  TGraphErrors *gr_PtRaaStat5020_20_40 = (TGraphErrors*) GetPtRaaStat5020_20_40();
  TGraphErrors *gr_PtRaaSyst5020_20_40  = (TGraphErrors*)GetPtRaaSyst5020_20_40();

  
  TGraph * gr_PtRaaTM15020_20_40_model=  (TGraph *) GetPtRaaTM15020_model(30,fileTAMU_pt_raa_20_40);
  TGraph * gr_PtRaaTM25020_20_40_model=  (TGraph *) GetPtRaaTM25020_model(30,fileTHUA_pt_raa_20_40);
  TGraph * gr_PtRaaSHM5020_20_40_model=  (TGraph *) GetPtRaaSHM5020_model(100,fileSHM_pt_raa_20_40);
  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_20_40_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_20_40_model->SetLineColor(ci1);

  gr_PtRaaTM15020_20_40_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_20_40_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_20_40_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_20_40_model->SetLineColor(kBlue+1);

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.1,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(19.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  SetTGraphError(gr_PtRaaStat5020_20_40,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_20_40,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_20_40,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_20_40_model->Draw("FL same");
  gr_PtRaaTM25020_20_40_model->Draw("FL same");
  //  gr_PtRaaSHM5020_20_40_model->Draw("FL same");

  gr_PtRaaStat5020_20_40->Draw("samePE");
  gr_PtRaaSyst5020_20_40->Draw("sameE2");

  //  boxEle0010->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.47,0.84,"Pb-Pb, 20-40%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, 2.5<#it{y}<4");

  

  TLegend *legend = new TLegend(0.17,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  legend->AddEntry( gr_PtRaaStat5020_20_40,"Data","P");
  legend->AddEntry(gr_PtRaaTM15020_20_40_model,"TAMU","f");
  legend->AddEntry(gr_PtRaaTM25020_20_40_model,"THU","f");
  //legend->AddEntry(gr_PtRaaSHM5020_20_40_model,"SHM (Andronic et al.)","f");
    

  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_20_40_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;
}


void plot_raa_pt_40_90(){
  
  TGraphErrors *gr_PtRaaStat5020_40_90 = (TGraphErrors*) GetPtRaaStat5020_40_90();
  TGraphErrors *gr_PtRaaSyst5020_40_90  = (TGraphErrors*)GetPtRaaSyst5020_40_90();

  
  TGraph * gr_PtRaaTM15020_40_90_model=  (TGraph *) GetPtRaaTM15020_model(30,fileTAMU_pt_raa_40_90);
  TGraph * gr_PtRaaTM25020_40_90_model=  (TGraph *) GetPtRaaTM25020_model(30,fileTHUA_pt_raa_40_90);
  TGraph * gr_PtRaaSHM5020_40_90_model=  (TGraph *) GetPtRaaSHM5020_model(100,fileSHM_pt_raa_40_90);
  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_40_90_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_40_90_model->SetLineColor(ci1);

  gr_PtRaaTM15020_40_90_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_40_90_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_40_90_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_40_90_model->SetLineColor(kBlue+1);

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.1,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(19.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  SetTGraphError(gr_PtRaaStat5020_40_90,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_40_90,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_40_90,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_40_90_model->Draw("FL same");
  gr_PtRaaTM25020_40_90_model->Draw("FL same");
  //  gr_PtRaaSHM5020_40_90_model->Draw("FL same");

  gr_PtRaaStat5020_40_90->Draw("samePE");
  gr_PtRaaSyst5020_40_90->Draw("sameE2");

  //  boxEle0010->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.47,0.84,"Pb-Pb, 40-90%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, 2.5<#it{y}<4");

  
  TLegend *legend = new TLegend(0.17,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_40_90,"Data","P");
  legend->AddEntry(gr_PtRaaTM15020_40_90_model,"TAMU","f");
  legend->AddEntry(gr_PtRaaTM25020_40_90_model,"THU","f");
  
  legend->AddEntry(gr_PtRaaSHM5020_40_90_model,"SHM","f");
    
  legend->Draw();
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

  SetPad(pad1,0.02,0.15,0.1,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2);
  SetTH2F(mh2Dummy,0.07,0.07,0.95,0.6,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(19.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  pad1->cd();
  mh2Dummy->Draw();


  gr_PtRaaStat5020_00_20->Draw("samePE");
  gr_PtRaaSyst5020_00_20->Draw("sameE2");
  
  
  gr_PtRaaStat5020_20_40->Draw("samePE");
  gr_PtRaaSyst5020_20_40->Draw("sameE2");

  gr_PtRaaStat5020_40_90->Draw("samePE");
  gr_PtRaaSyst5020_40_90->Draw("sameE2");

  //  boxEle0010->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.47,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, 2.5<#it{y}<4");

  
  TLegend *legend = new TLegend(0.17,0.68,0.4,0.9);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_00_20,"0-20%","P");
  legend->AddEntry( gr_PtRaaStat5020_20_40,"20-40%","P");
  legend->AddEntry( gr_PtRaaStat5020_40_90,"40-90%","P");
    
  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_all_015_model_mm.pdf");
  delete mh2Dummy;
  delete c_temp;

  

}

TGraphErrors *GetPtRaaStat5020_00_20(){

  TGraphAsymmErrors* grAPtRaaStat5020_00_20= (TGraphAsymmErrors *) final_results_pt_fwdy_00_20->Get("gr_Raa_CL");

  grAPtRaaStat5020_00_20->RemovePoint(15);

  TGraphErrors *grPtRaaStat5020_00_20 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaStat5020_00_20);

  
  return grPtRaaStat5020_00_20;
}
TGraphErrors *GetPtRaaSyst5020_00_20(){

  TGraphAsymmErrors* grAPtRaaSyst5020_00_20= (TGraphAsymmErrors *) final_results_pt_fwdy_00_20->Get("gr_Raa_syst_CL");
  grAPtRaaSyst5020_00_20->RemovePoint(15);

  TGraphErrors *grPtRaaSyst5020_00_20 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaSyst5020_00_20);
  return grPtRaaSyst5020_00_20;
}

TGraphErrors *GetPtRaaStat5020_20_40(){
  TGraphAsymmErrors* grAPtRaaStat5020_20_40= (TGraphAsymmErrors *) final_results_pt_fwdy_20_40->Get("gr_Raa_CL");
  grAPtRaaStat5020_20_40->RemovePoint(0);
  grAPtRaaStat5020_20_40->RemovePoint(14);

  TGraphErrors *grPtRaaStat5020_20_40 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaStat5020_20_40);
  return grPtRaaStat5020_20_40;
}

TGraphErrors *GetPtRaaSyst5020_20_40(){
  TGraphAsymmErrors* grAPtRaaSyst5020_20_40= (TGraphAsymmErrors *) final_results_pt_fwdy_20_40->Get("gr_Raa_syst_CL");
  grAPtRaaSyst5020_20_40->RemovePoint(0);
  grAPtRaaSyst5020_20_40->RemovePoint(14);
  TGraphErrors *grPtRaaSyst5020_20_40 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaSyst5020_20_40);
  return grPtRaaSyst5020_20_40;
}

TGraphErrors *GetPtRaaStat5020_40_90(){
  TGraphAsymmErrors* grAPtRaaStat5020_40_90= (TGraphAsymmErrors *) final_results_pt_fwdy_40_90->Get("gr_Raa_CL");
  grAPtRaaStat5020_40_90->RemovePoint(0);
  grAPtRaaStat5020_40_90->RemovePoint(14);

  TGraphErrors *grPtRaaStat5020_40_90 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaStat5020_40_90);
  return grPtRaaStat5020_40_90;
}

TGraphErrors *GetPtRaaSyst5020_40_90(){

  TGraphAsymmErrors* grAPtRaaSyst5020_40_90= (TGraphAsymmErrors *) final_results_pt_fwdy_40_90->Get("gr_Raa_syst_CL");
  grAPtRaaSyst5020_40_90->RemovePoint(0);
  grAPtRaaSyst5020_40_90->RemovePoint(14);

  TGraphErrors *grPtRaaSyst5020_40_90 = (TGraphErrors *) TGraphAsymmErrors_to_TGraphErrors(grAPtRaaSyst5020_40_90);
  return grPtRaaSyst5020_40_90;
}

