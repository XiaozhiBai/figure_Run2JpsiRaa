



#include <iostream>
#include <iomanip>      // std::setprecision

#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGaxis.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TLatex.h"

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "TStyle.h"

#include  "../common/PlottingHelper.h"

inline void SetBasicStyle(double kBottomMargin, double kTopMargin);


void plot_0_5_Cent();
void plot_70_90_Cent();

void PlotInvMass_Mpt_diel(){

  SetStyle();
  gStyle->SetOptStat(0);

  plot_0_5_Cent();
  plot_70_90_Cent();
  
}

void plot_0_5_Cent()
{

  int icent=1;
  
  TFile *f=new TFile("input/meanPt/Jpsi_scale_method_allpT_1.root","READ");  

  TH1D *hUS ;
  TH1D *hME;
  TF1 *fResidual;
  TF1 *fFit;
    if(icent==1)
    {
      hUS     = (TH1D*)f->Get("0_cent_5_mh1seos");
      hME     = (TH1D*)f->Get("0_cent_5_mh1meos");
      fResidual     = (TF1*)f->Get("0_cent_5_gBkg_residual");
      fFit     = (TF1*)f->Get("0_cent_5_totalfit");
    }

    
  
  TCanvas *c=new TCanvas("c","",1000,800);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);
  SetPad(pad1,0.03,0.14,0.15,0.03);
  pad1->Draw();
  c->cd();
  pad1->cd();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{m}_{e^{+}e^{-}} (GeV/#it{c}^{2});#LT #it{p}_{T}^{e^{+}e^{-}} #GT (GeV/#it{c})",100,2.3,3.5,100,1.5,2.2);
  //  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{m}_{e^{+}e^{-}} (GeV/#it{c}^{2});#LT #it{p}_{T}^{e^{+}e^{-}} #GT (GeV/#it{c})",100,2.5,3.4,100,1.5,2); 

  SetTH2F(mh2Dummy,0.055,0.055,1.1,1.1,0.05,0.05,0.01,0.01,504,504);

  hUS->SetMarkerStyle(20);
  hUS->SetMarkerSize(2.2);
  hUS->SetMarkerColor(kBlack);
  hUS->SetLineColor(kBlack);
  hUS->SetLineWidth(2);
  
  hME->SetMarkerStyle(1);
  hME->SetLineWidth(2);
  hME->SetLineColor(kBlue);

  fFit->SetLineColor(2);
  fFit->SetLineWidth(2);
  
  mh2Dummy->Draw();

  TF1 *fullFit = (TF1 *) hUS->GetFunction("fullFit");
  hUS->GetListOfFunctions()->Remove(fullFit);
  TH1F * Ffit_total=(TH1F *) hUS->Clone("Ffit_total");  //->GetListOfFunctions()->Remove(fullFit);

  for(int i=1;i<Ffit_total->GetNbinsX();i++)
    {
      Ffit_total->SetBinContent(i,fFit->Eval(Ffit_total->GetBinCenter(i)));
      Ffit_total->SetBinError(i,0);
      
    }
  //  fullFit->Print("all");
  Ffit_total->SetLineColor(2);
  Ffit_total->SetLineWidth(2);
  
  Ffit_total->Draw("sameHIST");

  
  hME->Draw("same");
  hUS->Draw("same");
  //  fFit->Draw("sameSHIST");
  
  //  TLegend *legend1 = new TLegend(0.17,0.7,0.5,0.9);
  TLegend *legend1 = new TLegend(0.5,0.4,0.85,0.6);

  SetLegend(legend1,42,0.051,0.0,0.0,0.0,0.0);
  
  legend1->AddEntry(hUS,"Same event ","p");
  legend1->AddEntry(hME,"Mixed events","l");
  legend1->AddEntry(fFit,"Combined fit","l");
  legend1->Draw();
  
  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextFont(42);
  latex1.SetTextSize(0.05);
  latex1.DrawLatex(0.6, 0.9, "ALICE");
  latex1.SetTextSize(0.05);

  latex1.DrawLatex(0.5, 0.83, "Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  latex1.DrawLatex(0.5, 0.76, "Centrality 0#font[122]{-}5%, |#it{y}| < 0.9");
  //  latex1.DrawLatex(0.5, 0.68, "Inclusive J/#psi, 0.15 < #it{p}_{T} <15 GeV/#it{c}");
  latex1.DrawLatex(0.5, 0.68, "0.15 < #it{p}_{T} < 15 GeV/#it{c}");

  c->SaveAs("output/InvMass_midy_MeanpT_0_5.pdf");
}

void plot_70_90_Cent()
{
  bool bCent = 1; //0->0-10%, 1->60-90%
  TFile *f=new TFile("input/meanPt/Jpsi_scale_method_allpT_1.root","READ");  
							
  TH1D *hUS     = (TH1D*)f->Get("70_cent_90_mh1seos");
  TH1D *hME     = (TH1D*)f->Get("70_cent_90_mh1meos");
  TF1 *fResidual     = (TF1*)f->Get("70_cent_90_gBkg_residual");
  TF1 *fFit     = (TF1*)f->Get("70_cent_90_totalfit");


  TCanvas *c=new TCanvas("c","",1000,800);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);
  SetPad(pad1,0.03,0.14,0.13,0.03);

  c->cd();
  pad1->Draw();  
  pad1->cd();

 TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{m}_{e^{+}e^{-}} (GeV/#it{c}^{2});#LT #it{p}_{T}^{e^{+}e^{-}} #GT (GeV/#it{c})",100,2.3,3.5,100,1.5,2.8); 

  SetTH2F(mh2Dummy,0.055,0.055,1.1,1.1,0.05,0.05,0.01,0.01,504,504);
  
  
  hUS->SetMarkerStyle(20);
  hUS->SetMarkerSize(2.2);
  hUS->SetMarkerColor(kBlack);
  hUS->SetLineColor(kBlack);
  hUS->SetLineWidth(2);
  
  hME->SetMarkerStyle(1);
  hME->SetLineWidth(2);
  hME->SetLineColor(kBlue);

  fFit->SetLineColor(2);
  fFit->SetLineWidth(2);
  
  mh2Dummy->Draw();


  hME->Draw("same");
  hUS->Draw("sameP");
  
  TF1 *fullFit = (TF1 *) hUS->GetFunction("fullFit");
  hUS->GetListOfFunctions()->Remove(fullFit);
  TH1F * Ffit_total=(TH1F *) hUS->Clone("Ffit_total");  //->GetListOfFunctions()->Remove(fullFit);

  for(int i=1;i<Ffit_total->GetNbinsX();i++)
    {
      Ffit_total->SetBinContent(i,fFit->Eval(Ffit_total->GetBinCenter(i)));
      Ffit_total->SetBinError(i,0);
      
    }
  //  fullFit->Print("all");
  Ffit_total->SetLineColor(2);
  Ffit_total->SetLineWidth(2);
  
  Ffit_total->Draw("sameHIST");
  //  fFit->Draw("sameHIST");
  
  TLegend *legend1 = new TLegend(0.17,0.7,0.5,0.9);
  legend1->SetFillColor(0);
  legend1->SetLineColor(0);
  legend1->SetTextFont(42);
  legend1->SetTextSize(0.045);
  legend1->SetFillStyle(0);
  legend1->AddEntry(hUS,"Same event ","p");
  legend1->AddEntry(hME,"Mixed events","l");
  legend1->AddEntry(fFit,"Combined fit","l");
  //legend1->Draw();
  
  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextFont(42);
  latex1.SetTextSize(0.05);
  /* latex1.DrawLatex(0.6, 0.9, "ALICE"); */
  latex1.SetTextSize(0.05);

  /* latex1.DrawLatex(0.5, 0.82, "Pb#font[122]{-}Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"); */
  latex1.DrawLatex(0.45, 0.82, "Centrality 70#font[122]{-}90%, |#it{y}| < 0.9");
  //  latex1.DrawLatex(0.45, 0.70, "Inclusive J/#psi, 0.15 < #it{p}_{T} <15 GeV/#it{c}");
  latex1.DrawLatex(0.45, 0.75, "0.15 < #it{p}_{T} < 15 GeV/#it{c}");

  c->SaveAs("output/InvMass_midy_MeanpT_70_90.pdf");
}

//
// style stuff
//
void SetBasicStyle(double kBottomMargin, double kTopMargin){

  TGaxis::SetMaxDigits(3);
  TGaxis::SetExponentOffset(0.02,-0.1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);  
  
  gStyle->SetTextFont(42);
  gStyle->SetLineWidth(2);//axes etc
  gStyle->SetPadBottomMargin(kBottomMargin);
  gStyle->SetPadLeftMargin(kBottomMargin - 0.01);
  gStyle->SetPadRightMargin(kTopMargin);
  gStyle->SetPadTopMargin(kTopMargin);
}
