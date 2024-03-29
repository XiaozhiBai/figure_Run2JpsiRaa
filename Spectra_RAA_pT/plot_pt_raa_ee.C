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

void plot_raa_pt_0_10();
void plot_raa_pt_30_50();
void plot_raa_pt_0_10_30_50();

//bool 
double NormUncert1   = 0.0072; // 0-10  %
//double NormUncert2   = 0.0069; // 10-30 %
double NormUncert3   = 0.016; // 30-50 %
//xdouble NormUncert_Fw = 0.040; // 0-20  %

double common_un=0.022;
//sqrt(0.022*0.022+0.021*0.021+0.0053*0.0053)

inline TGraphErrors *GetPtRaaStat5020_00_10();
inline TGraphErrors *GetPtRaaSyst5020_00_10();

inline TGraphErrors *GetPtRaaStat5020_30_50();
inline TGraphErrors *GetPtRaaSyst5020_30_50();


TFile *final_results_pt_midy;


const char *fileTAMU_pt_raa_0_10;
const char *fileTHUA_pt_raa_0_10;
const char *fileSHM_pt_raa_0_10;

const char *fileTAMU_pt_raa_30_50;
const char *fileTHUA_pt_raa_30_50;
const char *fileSHM_pt_raa_30_50;

const char *fileEnergy_loss_model;
const int Npoint_0_10=7;
const int Npoint_30_50=5;

void plot_pt_raa_ee()
{
  SetStyle();
  gStyle->SetOptStat(0);

  final_results_pt_midy=new TFile("input/data/Raa_final.root","READ");

  fileTAMU_pt_raa_0_10 = "../models/Ralf_Rapp/data/m0-10RAA.dat";
  fileTHUA_pt_raa_0_10 = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-pt-cent0-10--2022Jan5/theory-RAA-pt-cent0-10.dat";
  fileSHM_pt_raa_0_10 = "../models/SHMc/gRaaSHMc_midy_0_10.txt";    

  fileTAMU_pt_raa_30_50 = "../models/Ralf_Rapp/data/m30-50RAA.dat";
  fileTHUA_pt_raa_30_50 = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-pt-cent30-50-2022Jan5/theory-RAA-pt-cent30-50.dat";
  fileSHM_pt_raa_30_50 = "../models/SHMc/gRaaSHMc_midy_30_50.txt";    

  //energy losse mdoel
  fileEnergy_loss_model= "../models/energy-loss-model/ElossPredictions.root";
  
  plot_raa_pt_0_10();
  plot_raa_pt_30_50();
  plot_raa_pt_0_10_30_50();
 
}
void plot_raa_pt_0_10(){

  TGraphErrors *gr_PtRaaStat5020_00_10 = (TGraphErrors*)GetPtRaaStat5020_00_10();
  TGraphErrors *gr_PtRaaSyst5020_00_10  = (TGraphErrors*)GetPtRaaSyst5020_00_10();

  TGraph * gr_PtRaaTM15020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileTAMU_pt_raa_0_10);
  TGraph * gr_PtRaaTM25020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileTHUA_pt_raa_0_10);
  TGraph * gr_PtRaaSHM5020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileSHM_pt_raa_0_10);

  TGraphErrors *gr_PtRaaStat5020_00_10_extro = (TGraphErrors *) gr_PtRaaStat5020_00_10->Clone("gr_PtRaaStat5020_00_10_extro");

  for(int i=0;i<gr_PtRaaSyst5020_00_10->GetN();i++) 
    {
      if(i<Npoint_0_10){
	gr_PtRaaStat5020_00_10_extro->SetPoint(i,999,-999);
      }
      else 
	{
	  gr_PtRaaStat5020_00_10->SetPoint(i,999,-999);
	}
    }
      
  TGraphAsymmErrors * gr_PtRaaEL5020_0_10_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEnergy_loss_model,"RAA_binned_centrality_0_10");
  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_PtRaaSHM5020_0_10_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_0_10_model->SetLineColor(ci1);

  gr_PtRaaTM15020_0_10_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_0_10_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_0_10_model->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_0_10_model->SetLineColor(kBlue+1);

  gr_PtRaaEL5020_0_10_model->SetFillColorAlpha(kPink+1,0.4);
  gr_PtRaaEL5020_0_10_model->SetLineColor(kPink+9);

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,15,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.88,0.06,0.06,0.015,0.015,504,504);
  
  TBox *boxEle0010    = new TBox(14.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),14.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  SetTGraphError(gr_PtRaaStat5020_00_10,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_10,20,2.5,2,2,2,0);

  SetTGraphError(gr_PtRaaStat5020_00_10_extro,24,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_00_10,0.3);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaTM15020_0_10_model->Draw("FL same");
  gr_PtRaaTM25020_0_10_model->Draw("FL same");
  gr_PtRaaSHM5020_0_10_model->Draw("FL same");

  gr_PtRaaEL5020_0_10_model->Draw("same E2");
  

  gr_PtRaaStat5020_00_10->Draw("samePE");
  gr_PtRaaSyst5020_00_10->Draw("sameE2");


  gr_PtRaaStat5020_00_10_extro->Draw("samePE");
  //TGraphErrors *gr_PtRaaSyst5020_00_10_extro = gr_PtRaaSyst5020_00_10->Clone("gr_PtRaaSyst5020_00_10_extro");

  

  
  boxEle0010->Draw("sameE2");
  boxEle0010->Print("all");
  TLine *line_unity= (TLine *)GetLine(0,1.0,15,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.47,0.84,"Pb#font[122]{-}Pb,0#font[122]{-}10%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.47,0.77,"Inclusive J/#psi, |#it{y}| < 0.9");

  //  tex1.DrawLatex(0.17,0.65,"Pb#font[122]{-}Pb,0#font[122]{-}10%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
    
  TLegend *legend = new TLegend(0.43,0.41,0.8,0.71);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_00_10,lg_data,"P");
  legend->AddEntry(gr_PtRaaTM15020_0_10_model,lg_TM1,"f");
  legend->AddEntry(gr_PtRaaTM25020_0_10_model,lg_TM2,"f");
  legend->AddEntry(gr_PtRaaSHM5020_0_10_model,lg_SHM,"f");
  legend->AddEntry(gr_PtRaaEL5020_0_10_model,lg_EL,"f");

  legend->Draw();
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_0_10_015_model_ee.pdf");


  TFile *file=new TFile("Jpsi_RAA_Npart.root","UPDATE");
  file->cd();

  gr_PtRaaTM15020_0_10_model->Write("gr_RaaPt_Ralf_Rapp_5020_midy_0_10_model");
  gr_PtRaaTM25020_0_10_model->Write("gr_RaaPt_Pengfei_5020_midy_0_10_model");
  gr_PtRaaSHM5020_0_10_model->Write("gr_RaaPt_SHM_5020_midy_0_10_model");
  gr_PtRaaEL5020_0_10_model->Write("gr_RaaPt_Eloss_5020_midy_0_10_model");

  //  gr_PtRaaEL5020_0_10_model->Print("all");
  /* gr_PtRaaStat5020_0_10->Print("all"); */
  /* gr_PtRaaSyst5020_0_10->Print("all"); */
  
  delete mh2Dummy;
  delete c_temp;
}

void plot_raa_pt_30_50(){

  TGraphErrors *gr_PtRaaStat5020_30_50 = (TGraphErrors*)GetPtRaaStat5020_30_50();
  TGraphErrors *gr_PtRaaSyst5020_30_50  = (TGraphErrors*)GetPtRaaSyst5020_30_50();

    TGraphErrors *gr_PtRaaStat5020_30_50_extro = (TGraphErrors *) gr_PtRaaStat5020_30_50->Clone("gr_PtRaaStat5020_30_50_extro");

    for(int i=0;i<gr_PtRaaSyst5020_30_50->GetN();i++) 
      {
	if(i<Npoint_30_50){
	  gr_PtRaaStat5020_30_50_extro->SetPoint(i,999,-999);
	}
	else 
	  {
	    gr_PtRaaStat5020_30_50->SetPoint(i,999,-999);
	  }
      }
  
  TGraph * gr_PtRaaTM15020_30_50_model=  (TGraph *)GetPtRaaTM15020_model(12,fileTAMU_pt_raa_30_50);
  TGraph * gr_PtRaaTM25020_30_50_model=  (TGraph *)GetPtRaaTM15020_model(12,fileTHUA_pt_raa_30_50);
  TGraph * gr_PtRaaSHM5020_30_50_model=  (TGraph *)GetPtRaaTM15020_model(12,fileSHM_pt_raa_30_50);


  TGraphAsymmErrors * gr_PtRaaEL5020_30_50_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEnergy_loss_model,"RAA_binned_centrality_30_50");
  
  gr_PtRaaTM15020_30_50_model ->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_30_50_model->SetLineColor(kOrange+1);

  gr_PtRaaTM25020_30_50_model ->SetFillColorAlpha(kBlue+1,0.2);
  gr_PtRaaTM25020_30_50_model->SetLineColor(kBlue+1);
  
  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtRaaSHM5020_30_50_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_30_50_model->SetLineColor(ci1);

  gr_PtRaaEL5020_30_50_model->SetFillColorAlpha(kPink+1,0.4);
  gr_PtRaaEL5020_30_50_model->SetLineColor(kPink+9);
  

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,15,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.15,0.88,0.06,0.06,0.015,0.015,504,504);
  
  
  TBox *boxEle3050    = new TBox(14.3,1.-sqrt(NormUncert3*NormUncert3+common_un*common_un),14.7,1.+sqrt(NormUncert3*NormUncert3+common_un*common_un));
  boxEle3050->SetFillColor(kRed);

  //  boxEle3050->Print("all");
  SetTGraphError(gr_PtRaaStat5020_30_50,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaStat5020_30_50_extro,24,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_30_50,20,2.5,2,2,2,0);

  SetErrorX(gr_PtRaaSyst5020_30_50,0.3);

  pad1->cd();
  mh2Dummy->Draw();

  gr_PtRaaSHM5020_30_50_model->Draw("FL same");
  gr_PtRaaTM15020_30_50_model->Draw("FL same");
  gr_PtRaaTM25020_30_50_model->Draw("FL same");
  gr_PtRaaEL5020_30_50_model->Draw("same E2");

  gr_PtRaaStat5020_30_50->Draw("samePE");
  gr_PtRaaStat5020_30_50_extro->Draw("samePE");
  gr_PtRaaSyst5020_30_50->Draw("sameE2");

  boxEle3050->Draw("sameE2");
    
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.48,0.84,"Pb#font[122]{-}Pb, 30#font[122]{-}50%, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.48,0.77,"Inclusive J/#psi, |#it{y}| < 0.9");

  TLegend *legend = new TLegend(0.47,0.5,0.85,0.75);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);

  /* legend->AddEntry( gr_PtRaaStat5020_30_50,"Data","P"); */
  /* legend->AddEntry(gr_PtRaaTM15020_30_50_model,"TAMU","f"); */
  /* legend->AddEntry(gr_PtRaaTM25020_30_50_model,"THU","f");   */
  /* legend->AddEntry(gr_PtRaaSHM5020_30_50_model,"SHM (old)","f"); */
  /* legend->AddEntry(gr_PtRaaEL5020_30_50_model,"Energy loss","f"); */

  legend->AddEntry( gr_PtRaaStat5020_30_50,lg_data,"P");
  legend->AddEntry(gr_PtRaaTM15020_30_50_model,lg_TM1,"f");
  legend->AddEntry(gr_PtRaaTM25020_30_50_model,lg_TM2,"f");
  legend->AddEntry(gr_PtRaaSHM5020_30_50_model,lg_SHM,"f");
  legend->AddEntry(gr_PtRaaEL5020_30_50_model,lg_EL,"f");

  //  gr_PtRaaEL5020_30_50_model->Print("all");
  /* gr_PtRaaStat5020_30_50->Print("all"); */
  /* gr_PtRaaSyst5020_30_50->Print("all"); */
  //  legend->Draw();

  TLine *line_unity= (TLine *)GetLine(0,1.0,15,1.0,1,2,7);
  line_unity  ->Draw("same");
  c_temp->SaveAs("output/Raa_Vs_pt_30_50_015_model_ee.pdf");


  delete mh2Dummy;
  delete c_temp;
  }

void plot_raa_pt_0_10_30_50(){

  TBox *boxEle0010    = new TBox(14.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),14.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);
  
  TBox *boxEle3050    = new TBox(13.9,1.-sqrt(NormUncert3*NormUncert3+common_un*common_un),14.3,1.+sqrt(NormUncert3*NormUncert3+common_un*common_un));
  boxEle3050->SetFillColor(4);

  
  TGraphErrors *gr_PtRaaStat5020_00_10 = (TGraphErrors*)GetPtRaaStat5020_00_10();
  TGraphErrors *gr_PtRaaSyst5020_00_10  = (TGraphErrors*)GetPtRaaSyst5020_00_10();

  TGraphErrors *gr_PtRaaStat5020_30_50 = (TGraphErrors*)GetPtRaaStat5020_30_50();
  TGraphErrors *gr_PtRaaSyst5020_30_50  = (TGraphErrors*)GetPtRaaSyst5020_30_50();

  TGraphErrors *gr_PtRaaStat5020_00_10_extro = (TGraphErrors *) gr_PtRaaStat5020_00_10->Clone("gr_PtRaaStat5020_00_10_extro");
  TGraphErrors *gr_PtRaaStat5020_30_50_extro = (TGraphErrors *) gr_PtRaaStat5020_30_50->Clone("gr_PtRaaStat5020_30_50_extro");

  for(int i=0;i<gr_PtRaaSyst5020_00_10->GetN();i++) 
    {
      if(i<Npoint_0_10){
	gr_PtRaaStat5020_00_10_extro->SetPoint(i,999,-999);
      }
      else 
	{
	  gr_PtRaaStat5020_00_10->SetPoint(i,999,-999);
	}
    }

  for(int i=0;i<gr_PtRaaSyst5020_30_50->GetN();i++) 
    {
      if(i<Npoint_30_50){
	gr_PtRaaStat5020_30_50_extro->SetPoint(i,999,-999);
      }
      else 
	{
	  gr_PtRaaStat5020_30_50->SetPoint(i,999,-999);
	}
    }
    

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,15,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.9,0.06,0.06,0.015,0.015,504,504);


  SetTGraphError(gr_PtRaaStat5020_00_10,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaStat5020_00_10_extro,24,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_10,20,2.5,2,2,2,0);
  SetErrorX(gr_PtRaaSyst5020_00_10,0.3);

  
  SetTGraphError(gr_PtRaaStat5020_30_50,20,2.5,4,4,2,0);
  SetTGraphError(gr_PtRaaStat5020_30_50_extro,24,2.5,4,4,2,0);
  SetTGraphError(gr_PtRaaSyst5020_30_50,20,2.5,4,4,2,0);
  SetErrorX(gr_PtRaaSyst5020_30_50,0.3);
  
  pad1->cd();
  
  mh2Dummy->Draw();

  gr_PtRaaStat5020_00_10->Draw("samePE");
  gr_PtRaaStat5020_00_10_extro->Draw("samePE");
  gr_PtRaaSyst5020_00_10->Draw("sameE2");
  gr_PtRaaStat5020_30_50->Draw("samePE");
  gr_PtRaaStat5020_30_50_extro->Draw("samePE");
  gr_PtRaaSyst5020_30_50->Draw("sameE2");

  boxEle0010->Draw("sameE2");
  boxEle3050 ->Draw("sameE2");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.06);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.052);

  tex1.DrawLatex(0.5,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.5,0.77,"Inclusive J/#psi, |#it{y}| < 0.9");

  TLegend *legend = new TLegend(0.5,0.62,0.9,0.755);
  SetLegend(legend,42,0.05,0.0,0.0,0.0,0.0);

  legend->AddEntry( gr_PtRaaStat5020_00_10,"0#font[122]{-}10%","P");
  legend->AddEntry( gr_PtRaaStat5020_30_50,"30#font[122]{-}50%","P");
  legend->Draw();
  TLine *line_unity= (TLine *)GetLine(0,1.0,15,1.0,1,3,7);
  line_unity->Draw();
  c_temp->SaveAs("output/Raa_Vs_pt_0_10_30_50_015_data_ee.pdf");

  
  delete mh2Dummy;
  delete c_temp;

}
TGraphErrors *GetPtRaaStat5020_00_10(){
  TH1F *PtRaaStat5020_00_10 = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sts_0_10");
  TGraphErrors* grPtRaaStat5020_00_10=new TGraphErrors(PtRaaStat5020_00_10);

  return grPtRaaStat5020_00_10;
}

TGraphErrors *GetPtRaaSyst5020_00_10(){
  TH1F *PtRaaSyst5020_00_10 = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sys_0_10");
  TGraphErrors* grPtRaaSyst5020_00_10=new TGraphErrors(PtRaaSyst5020_00_10);

  return grPtRaaSyst5020_00_10;
}

TGraphErrors *GetPtRaaStat5020_30_50(){
  TH1F *PtRaaStat5020_30_50 = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sts_30_50");
  TGraphErrors* grPtRaaStat5020_30_50=new TGraphErrors(PtRaaStat5020_30_50);

  return grPtRaaStat5020_30_50;
}

TGraphErrors *GetPtRaaSyst5020_30_50(){
  TH1F *PtRaaSyst5020_30_50 = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sys_30_50");
  TGraphErrors* grPtRaaSyst5020_30_50=new TGraphErrors(PtRaaSyst5020_30_50);

  return grPtRaaSyst5020_30_50;
}
