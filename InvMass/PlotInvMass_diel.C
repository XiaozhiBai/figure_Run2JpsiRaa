//*******************************************************************************
// plot the results                                                             *
// by Xiaozhi Bai xiaozhi.bai@cern.ch baixiaozhi@ustc.edu.cn                    *
// Wed Dec 22 13:12:08 CST 2021                                                 *
//*******************************************************************************

// root -l -b -q PlotInvMass_diel.C 


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

#include "../common/PlottingHelper.h"

void SetBasicStyle( double, double );

void PlotInvMass_diel(){

  TGaxis::SetExponentOffset(0.02,-0.1);
  SetStyle();
  
  //   SetBasicStyle(0.15,0.01);
  							
  bool bCent = 1; //0->0-10%, 1->60-90%

  TString fFile = "input/Jpsi_scale_method_1_allpT_1.root";
  TFile f(Form("%s",fFile.Data()));

							
  TH1D *hUS     = (TH1D*)f.Get("mh1unlike_temp_centrality_0_from_5_pt_15_from_1500");
  TH1D *hME     = (TH1D*)f.Get("bkg_shape_centrality_0_from_5_pt_15_from_1500");
  TH1D *hSignal = (TH1D*)f.Get("mh1Raw_Jpsi_temp_centrality_0_from_5_pt_15_from_1500");
  TH1F *hMC     = (TH1F*)f.Get("mh1Jpsi_mc_temp_centrality_0_from_5_pt_15_from_1500");
  TF1 *fResidual     = (TF1*)f.Get("fBkgFitFunction_centrality_0_from_5_pt_15_from_1500");
  TF1 *fFit     = (TF1*)f.Get("fGlobalFitFunction_centrality_0_from_5_pt_15_from_1500");
  
  hUS->SetMarkerStyle(8);
  hUS->SetMarkerSize(1.2);
  hUS->SetMarkerColor(kBlack);
  hUS->SetLineColor(kBlack);
  hUS->SetLineWidth(2);
  
  hME->SetMarkerStyle(1);
  hME->SetLineWidth(2);
  hME->SetLineColor(kRed);
  
  hSignal->SetMarkerStyle(8);
  hSignal->SetMarkerSize(1.2);
  hSignal->SetMarkerColor(kBlack);
  hSignal->SetLineWidth(2);
  hSignal->SetLineColor(kBlack);
  hMC->SetLineColor(kBlue);

  fResidual->SetLineWidth(2);
  fResidual->SetLineColor(4);

  fFit->SetLineColor(2);
  fFit->SetLineWidth(2);
  
  double xMin = 2;
  double xMax = 3.7;

  double yMin1,yMax1;
  double yMin2,yMax2;

  if(bCent == 1){
    yMin1 = 10;
    yMax1 = 1.2e6;

    yMin2 = -1e3;
    yMax2 = 1.6e4;

  } else{
    yMin1 = 0.;
    yMax1 = 4.5e2;

    yMin2 = -5.e1;
    yMax2 = 1.7e2;
  }

  TLine *line_0=new TLine(xMin,0,xMax,0);

  line_0->SetLineColor(1);
  line_0->SetLineStyle(7);
  line_0->SetLineWidth(2);
  
  
  TH2F *hDummyUp = new TH2F("hDummyUp",";;Counts per 40 MeV/#it{c^{2}}",100,xMin,xMax,100,yMin1,yMax1);
  TH2F *hDummyLo = new TH2F("hDummyLo",";#it{m}_{e^{+}e^{-}} (GeV/#it{c^{2}});Counts per 40 MeV/#it{c^{2}}",100,xMin,xMax,100,yMin2,yMax2);
 
  SetTH2F(hDummyUp,0.07,0.07,0.95,0.95,0.06,0.06,0.02,0.02,504,504);
  SetTH2F(hDummyLo,0.07,0.07,1.08,0.95,0.06,0.06,0.02,0.02,504,504);
 
  hDummyUp->GetYaxis()->SetMaxDigits(3);
  hDummyLo->GetYaxis()->SetMaxDigits(3);
    
  TCanvas *cInvMass = new TCanvas("cInvMass","cInvMass",800,1000);
  auto padUp = new TPad("padUp","padUp",0.0,0.5,1,1);
  auto padLo = new TPad("padLo","padLo",0.,0.,1,0.5);

  SetPad(padUp,0.02,0,0.14,0.02);
  SetPad(padLo ,0.0,0.16,0.14,0.02);
  
  padUp->Draw();
  padLo->Draw();
  padUp->cd();
  hDummyUp->Draw();

 
  hUS->Draw("pe same");
  hME->Draw("hist e same");
 
  TLegend *legend1 = new TLegend(0.2,0.2,0.5,0.4);
  SetLegend(legend1,42,0.055,0.0,0.0,0.0,0.0);
  legend1->SetHeader("Opposite-sign distribution","L");
  legend1->AddEntry(hUS,"Same event","p");
  legend1->AddEntry(hME,"Mixed events","l");
  legend1->Draw();
  
  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextFont(42);
  latex1.SetTextSize(0.065);
  latex1.DrawLatex(0.5, 0.9, "ALICE");
  latex1.SetTextSize(0.06);

  latex1.DrawLatex(0.5, 0.82, "Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  latex1.DrawLatex(0.5, 0.74, "Centrality 0#font[122]{-}5%, |#it{y}|<0.9");
  latex1.DrawLatex(0.5, 0.66, "J/#psi #rightarrow e^{+}e^{#minus}, #it{p}_{T} > 0.15 GeV/#it{c}");


  cInvMass->Update();
  padLo->cd();
  hDummyLo->DrawCopy();
  hSignal->DrawCopy("same LC");
  fFit->Draw("same");
  fResidual->DrawCopy("same");
  line_0->Draw("same");
  
  TLegend *legend2 = new TLegend(0.2,0.65,0.5,0.87);

  SetLegend(legend2,42,0.055,0.0,0.0,0.0,0.0);
  
  legend2->SetHeader("Signal","L"); // 
  legend2->AddEntry(hSignal,"Data","p");
  legend2->AddEntry(fFit,"Fit","l");
  legend2->AddEntry(fResidual,"Residual background","l");
  legend2->Draw();

  
  TLatex latex2;
  latex2.SetNDC();
  latex2.SetTextFont(42);
  latex2.SetTextSize(0.05);
  latex2.DrawLatex(0.7, 0.9, "N_{J/#psi} = 33707 #pm 2154");//6141 +/- 562
  latex2.DrawLatex(0.7, 0.8, "#chi^{2}/N_{dof} = 0.91");//6141 +/- 562


  cInvMass->SaveAs("output/InvMass_midy_0_5.pdf");
}



//
// style stuff
//
void SetBasicStyle(double kBottomMargin, double kTopMargin){

  TGaxis::SetMaxDigits(3);

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);  
  
  gStyle->SetTextFont(42);
  gStyle->SetLineWidth(2);//axes etc
  gStyle->SetPadBottomMargin(kBottomMargin);
  gStyle->SetPadLeftMargin(kBottomMargin - 0.01);
  gStyle->SetPadRightMargin(kTopMargin);
  gStyle->SetPadTopMargin(kTopMargin);
}
