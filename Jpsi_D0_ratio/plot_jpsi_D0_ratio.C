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

void plot_ratio_cent_model_DtoJpsi_ratio();
void plot_ratio_cent_model_JpsitoD_ratio();

TGraphAsymmErrors *Get_DtoJpsi_ratio_SHM_5020_model();
inline TGraphErrors *GetDtoJpsi_ratio_Stat();
inline TGraphErrors *GetDtoJpsi_ratio_syst();


TGraphAsymmErrors *Get_JpsitoD_ratio_SHM_5020_model();
inline TGraphErrors *GetJpsitoD_ratio_Stat();
inline TGraphErrors *GetJpsitoD_ratio_syst();



TFile *final_results_cent_midy;
const char *final_results_cent_fwdy;



void plot_jpsi_D0_ratio()
{

  SetStyle();

  final_results_cent_midy=new TFile("input/data/D0_jpsi_ratio_withoutTPC_ITS_matching_from_D0.root","READ");

  plot_ratio_cent_model_DtoJpsi_ratio();
  plot_ratio_cent_model_JpsitoD_ratio();
}

void plot_ratio_cent_model_JpsitoD_ratio(){


  
  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetJpsitoD_ratio_Stat();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetJpsitoD_ratio_syst();


  TGraphAsymmErrors *gr_SHM_5020_model = (TGraphAsymmErrors *) Get_JpsitoD_ratio_SHM_5020_model(); 
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.16,0.16,0.02);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";Centrality; J/#psi/D^{0}",2,2,6,100,0.008,0.042);
  SetTH2F(mh2Dummy,0.07,0.07,1.14,1.14,0.0,0.06,0.015,0.015,2,504);

  

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  SetErrorX(gr_CentRaaSyst5020,0.1);
  SetErrorX(gr_CentRaaStat5020,0);
  
  pad1->cd();
  mh2Dummy->Draw();

  gr_SHM_5020_model->SetFillColor(4);
  gr_SHM_5020_model->SetMarkerStyle(20);


  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  ci1 = TColor::GetColor("#33ccff");
  gr_SHM_5020_model->SetFillColorAlpha(ci1,0.7);
  gr_SHM_5020_model->SetLineColor(ci1);

  TGraphAsymmErrors *  gr_SHM_5020_model_centra= (TGraphAsymmErrors *) gr_SHM_5020_model->Clone("gr_SHM_5020_model_centra");

 gr_SHM_5020_model_centra->SetPointEYhigh(0,0);
  gr_SHM_5020_model_centra->SetPointEYlow(0,0);

  gr_SHM_5020_model_centra->SetPointEYhigh(1,0);
  gr_SHM_5020_model_centra->SetPointEYlow(1,0);

  gr_SHM_5020_model_centra->SetLineWidth(2);
  gr_SHM_5020_model_centra->SetLineColor(4);


  


  
  gr_SHM_5020_model->Draw("sameE2");


  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  gr_SHM_5020_model_centra->Draw("sameE0");


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
  tex1.DrawLatex(0.21,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.21,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.21,0.77,"Inclusive J/#psi, |#it{y}| < 0.9, 0.15 < #it{p}_{T} <  15 GeV/#it{c}");
  tex1.DrawLatex(0.21,0.70,"Prompt D^{0}, |#it{y}| < 0.5, #it{p}_{T} > 0");
  
  TLegend  *legend= new TLegend(0.2,0.55,0.56,0.65);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  

  legend->AddEntry(gr_CentRaaStat5020, lg_data,"P");
  legend->AddEntry(gr_SHM_5020_model,lg_SHM,"f");
  
  legend->Draw();

  
  
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Jpsi_to_D0_ratio_data.pdf");
  delete mh2Dummy;
  delete c_temp;

  

  
}
void plot_ratio_cent_model_DtoJpsi_ratio(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetDtoJpsi_ratio_Stat();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetDtoJpsi_ratio_syst();


  TGraphAsymmErrors *gr_SHM_5020_model = (TGraphAsymmErrors *) Get_DtoJpsi_ratio_SHM_5020_model(); 
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.15,0.15,0.02);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";Centrality; D^{0}/J/#psi",2,2,6,100,30,152);
  SetTH2F(mh2Dummy,0.07,0.07,1.05,1.07,0.0,0.06,0.015,0.015,2,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  SetErrorX(gr_CentRaaSyst5020,0.1);
  SetErrorX(gr_CentRaaStat5020,0);
  
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

  TGraphAsymmErrors *  gr_SHM_5020_model_centra= (TGraphAsymmErrors *) gr_SHM_5020_model->Clone("gr_SHM_5020_model_centra");

  gr_SHM_5020_model_centra->SetLineColor(4);

  gr_SHM_5020_model_centra->SetPointEYhigh(0,0);
  gr_SHM_5020_model_centra->SetPointEYlow(0,0);

  gr_SHM_5020_model_centra->SetPointEYhigh(1,0);
  gr_SHM_5020_model_centra->SetPointEYlow(1,0);

  gr_SHM_5020_model_centra->SetLineWidth(2);
  
  gr_SHM_5020_model_centra->Draw("sameE0");

  
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
  tex1.DrawLatex(0.21,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.21,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.21,0.77,"Inclusive J/#psi, |#it{y}| < 0.9, 0.15 < #it{p}_{T} < 15 GeV/#it{c}");
  tex1.DrawLatex(0.21,0.70,"Prompt D^{0}, |#it{y}| < 0.5, #it{p}_{T} > 0");
  
  TLegend  *legend= new TLegend(0.2,0.55,0.56,0.65);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  

  legend->AddEntry(gr_CentRaaStat5020, lg_data,"P");
  legend->AddEntry(gr_SHM_5020_model,lg_SHM,"f");
  
  legend->Draw();
  
    gPad->RedrawAxis();
    c_temp->SaveAs("output/D0_to_jpsi_ratio_data.pdf");
    delete mh2Dummy;
  delete c_temp;
}


TGraphErrors *GetDtoJpsi_ratio_Stat(){

  TH1F * D0_jpsiratio_sts= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sts");
  TGraphErrors* gr_D0_jpsiratio_sts=new TGraphErrors(D0_jpsiratio_sts);

  D0_jpsiratio_sts->Print("all");
  return gr_D0_jpsiratio_sts;
}


TGraphErrors *GetJpsitoD_ratio_Stat(){

  TH1F * D0_jpsiratio_sts= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sts");

  for(int ibin=0;ibin<D0_jpsiratio_sts->GetNbinsX();ibin++)
    {

      Double_t ratio_tem=D0_jpsiratio_sts->GetBinContent(ibin+1);
      Double_t ratio_tem_err=D0_jpsiratio_sts->GetBinError(ibin+1);
     
      D0_jpsiratio_sts->SetBinContent(ibin+1,1./ratio_tem);
      D0_jpsiratio_sts->SetBinError(ibin+1,ratio_tem_err/(ratio_tem*ratio_tem));
    }
  
  TGraphErrors* gr_D0_jpsiratio_sts=new TGraphErrors(D0_jpsiratio_sts);

  return gr_D0_jpsiratio_sts;
}


TGraphErrors *GetDtoJpsi_ratio_syst(){
  //https://indico.cern.ch/event/1060074/contributions/4454852/attachments/2285428/3884362/xbai_20210721_v3.pdf
  TH1F * D0_jpsiratio_sys= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sys");
    
  TGraphErrors* gr_D0_jpsiratio_sys=new TGraphErrors(D0_jpsiratio_sys);
  return gr_D0_jpsiratio_sys;
}


TGraphErrors *GetJpsitoD_ratio_syst(){
  //https://indico.cern.ch/event/1060074/contributions/4454852/attachments/2285428/3884362/xbai_20210721_v3.pdf
  TH1F * D0_jpsiratio_sys= (TH1F *) final_results_cent_midy->Get("D0_jpsiratio_sys");


   for(int ibin=0;ibin<D0_jpsiratio_sys->GetNbinsX();ibin++)
    {

      Double_t ratio_tem=D0_jpsiratio_sys->GetBinContent(ibin+1);
      Double_t ratio_tem_err=D0_jpsiratio_sys->GetBinError(ibin+1);
     
      D0_jpsiratio_sys->SetBinContent(ibin+1,1./ratio_tem);
      D0_jpsiratio_sys->SetBinError(ibin+1,ratio_tem_err/(ratio_tem*ratio_tem));
    }
  
  TGraphErrors* gr_D0_jpsiratio_sys=new TGraphErrors(D0_jpsiratio_sys);
  return gr_D0_jpsiratio_sys;
}


TGraphAsymmErrors *Get_DtoJpsi_ratio_SHM_5020_model(){

  const int Npoints=2;

  Double_t x[Npoints]={3,5};
  Double_t y[Npoints]={53.55,75.63};
  Double_t exl[Npoints]={1,1};
  Double_t eyl[Npoints]={6.56,6.29};
  Double_t exh[Npoints]={1,1};
  Double_t eyh[Npoints]={8.61,6.98};

  TGraphAsymmErrors *gr_SHM_model = new TGraphAsymmErrors(Npoints,x,y,exl,exh,eyl,eyh);

  return gr_SHM_model;
}


TGraphAsymmErrors *Get_JpsitoD_ratio_SHM_5020_model(){

  const int Npoints=2;

  Double_t x[Npoints]={3,5};
  Double_t y[Npoints]={1./53.55,1./75.63};
  Double_t exl[Npoints]={1,1};
  Double_t eyl[Npoints]={8.61/(53.55*53.55),6.98/(75.63*75.63)};
  Double_t exh[Npoints]={1,1};
  Double_t eyh[Npoints]={6.56/(53.55*53.55),6.29/(75.63*75.63)};

 TGraphAsymmErrors *gr_SHM_model = new TGraphAsymmErrors(Npoints,x,y,exl,exh,eyl,eyh);

  return gr_SHM_model;
}

