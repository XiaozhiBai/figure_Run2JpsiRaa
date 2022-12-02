//*******************************************************************************
// plot the results                                                             *
// by Xiaozhi Bai xiaozhi.bai@cern.ch baixiaozhi@ustc.edu.cn                    *
// Wed Dec 22 13:12:08 CST 2021                                                 *
//*******************************************************************************


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

inline void SetBasicStyle(double kBottomMargin, double kTopMargin);

void PlotInvMass_dimu(){

  TGaxis::SetExponentOffset(0.02,-0.1);
  SetStyle();
  
  //  SetBasicStyle(0.15,0.01);
							
  bool bCent = 1; //0->0-10%, 1->60-90%
  
  TString fFile = "input/invMassDimu.root";

  TFile *f=new TFile(Form("%s",fFile.Data()),"READ");

  
							
  TH1F *hUS     = (TH1F*)f->Get("histoRawInvMass_1to2__1");
  TH1F *hME     = (TH1F*)f->Get("histoMixInvMass_1to2__2");
  TH1F *hSignal = (TH1F*)f->Get("histoSubInvMass_Pt1to2__1");
  TF1 *hMC     = (TF1*)f->Get("fitCB2_JPsi");
  TF1 *fResidual     = (TF1*)f->Get("fitExp");
  TF1 *fFit     = (TF1*)f->Get("fitFuncCB2Exp_geant3");
  
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

  /* hSignal->Draw("PE"); */
  /* return; */

  
  double xMin = 2.4;
  double xMax = 4.7;

  double yMin1,yMax1;
  double yMin2,yMax2;

  if(bCent == 1){
    yMin1 = 1;
    yMax1 = 3.2e5;

    yMin2 = -1.9e3;
    yMax2 = 3.1e4;

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
  
  
  TH2F *hDummyUp = new TH2F("hDummyUp",";;Counts per 25 MeV/#it{c^{2}}",100,xMin,xMax,100,yMin1,yMax1);
  TH2F *hDummyLo = new TH2F("hDummyLo",";#it{m}_{#mu^{+}#mu^{-}} (GeV/#it{c^{2}});Counts per 25 MeV/#it{c^{2}}",100,xMin,xMax,100,yMin2,yMax2);

  SetTH2F(hDummyUp,0.07,0.07,0.97,0.93,0.06,0.06,0.02,0.02,504,504);
  SetTH2F(hDummyLo,0.07,0.07,0.97,0.93,0.06,0.06,0.02,0.02,504,504);
 
  hDummyUp->GetYaxis()->SetMaxDigits(3);
  hDummyLo->GetYaxis()->SetMaxDigits(3);
    
    TCanvas *cInvMass = new TCanvas("cInvMass","cInvMass",800,1000);
  //  TCanvas *cInvMass = new TCanvas("cInvMass","cInvMass",2800,5000);
  auto padUp = new TPad("padUp","padUp",0.0,0.5,1,1);
  auto padLo = new TPad("padLo","padLo",0.,0.,1,0.5);

  SetPad(padUp,0.02,0,0.13,0.02);
  SetPad(padLo ,0.0,0.16,0.13,0.02);
  
  
 
  padUp->Draw();
  padLo->Draw();
  padUp->cd();

  hDummyUp->DrawCopy();
  hME->DrawCopy("hist e same");
  hUS->DrawCopy("pe same X0");

  //  return;
  //
    
  TLegend *legend1 = new TLegend(0.2,0.2,0.5,0.4);

  SetLegend(legend1,42,0.05,0.0,0.0,0.0,0.0);

  legend1->SetHeader("Opposite-sign distribution","L");
  legend1->AddEntry(hUS,"Same event","p");
  legend1->AddEntry(hME,"Mixed events","l");
  //legend1->Draw();
  
  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextFont(42);
  latex1.SetTextSize(0.06);
  // latex1.DrawLatex(0.65, 0.9, "ALICE");
  // latex1.SetTextSize(0.05);
  //  latex1.DrawLatex(0.55, 0.82, "Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  /* if(bCent == 1)latex1.DrawLatex(0.69, 0.78, "Centrality 0-20%"); */
  /* else latex1.DrawLatex(0.69, 0.78, "Centrality 60-90%"); */
  latex1.DrawLatex(0.5, 0.74, "Centrality 0#font[122]{-}20% , 2.5 < #it{y} < 4");
  latex1.DrawLatex(0.5, 0.66, "J/#psi #rightarrow #mu^{+}#mu^{#minus}, 1 < #it{p}_{T} < 2 GeV/#it{c}");



  
  padUp->RedrawAxis();
  cInvMass->RedrawAxis();
  cInvMass->Update();


  padLo->cd();
  hDummyLo->DrawCopy();
  hSignal->DrawCopy("same LC X0");
  //  hMC->DrawCopy("same C");
  fFit->Draw("same");
  fResidual->DrawCopy("same");
  line_0->Draw("same");
  
  
  TLegend *legend2 = new TLegend(0.2,0.65,0.5,0.87);
  SetLegend(legend1,42,0.05,0.0,0.0,0.0,0.0);
  legend2->SetHeader("Signal","L"); // 
  legend2->AddEntry(hSignal,"Data","p");
  //  legend2->AddEntry(hMC,"MC shape","l");
  legend2->AddEntry(fFit,"Fit","l");
  legend2->AddEntry(fResidual,"Residual background","l");
  //legend2->Draw();

  
  TLatex latex2;
  latex2.SetNDC();
  latex2.SetTextFont(42);
  latex2.SetTextSize(0.05);
  latex2.DrawLatex(0.65, 0.9, "N_{J/#psi} = 182596 #pm 1927");//6141 +/- 562
  //latex2.DrawLatex(0.72, 0.82, "Signif. = 63.9");//11.1 +/- 1.0
  latex2.DrawLatex(0.65, 0.8, "#chi^{2}/N_{dof} = 1.55");//6141 +/- 562
  
  padLo->RedrawAxis();
  cInvMass->RedrawAxis();
  cInvMass->Update();

  //  cInvMass->SaveAs("output/InvMass_fordy_10_20.eps");
  cInvMass->SaveAs("output/InvMass_fordy_10_20.pdf");
  //cInvMass->SaveAs("output/InvMass_fordy_10_20.png");
    
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
