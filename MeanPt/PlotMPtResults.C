#include "../common/PlottingHelper.h"


Double_t MPtSq_pp = 10.20;
Double_t MPtSq_ppStatErr = 0.46;
Double_t MPtSq_ppSystErr = 0.1;//0.24   

Double_t MeanPt502pp = 2.66;//+-0.044 (syst)                                                                                                 
Double_t MeanPt502ppStatErr = 0.06;
Double_t MeanPt502ppSystErr = 0.01;//0.03


//theory graphs
TGraph *graphPengLow = 0x0;
TGraph *graphPengMPtSq = 0x0;
TGraph *graphPengraa = 0x0;

TGraph *graphRappMPtLow = 0x0;
TGraph *graphRappMPtHigh = 0x0;
TGraph *graphRappMPtSqLow = 0x0;
TGraph *graphRappMPtSqHigh =0x0;
TGraph *graphRappraaLow = 0x0;
TGraph *graphRappraaHigh = 0x0;
TGraphErrors *graphRappMeanPt = 0x0;
TGraphErrors *graphRappraa = 0x0;

TGraph *graphSHMMPtHigh = 0x0;
TGraph *graphSHMMPtLow = 0x0;
TGraphErrors *graphSHMMeanPt= 0x0;

TGraph *graphSHMraaHigh = 0x0;
TGraph *graphSHMraaLow = 0x0;
TGraphErrors *graphSHMraa = 0x0;


//data graphs

TGraphErrors *graphMeanPtNA50=0x0;
TGraphErrors *graphMeanPtSqNA50=0x0;
TGraphErrors *graphraaNA50 =0x0;
TGraphErrors *graphMeanPtPhenixAuAu=0x0;
TGraphErrors *graphMeanPtPhenixAuAuSyst=0x0; 
TGraphErrors *graphraaPhenixAuAu=0x0;
TGraphErrors *graphraaPhenixAuAuSyst=0x0;

TGraphErrors *graphMeanPtPhenixCuCu=0x0;
TGraphErrors *graphMeanPtPhenixCuCuSyst=0x0;


TGraphErrors *graphraaPhenixCuCu =0x0;
TGraphErrors *graphraaPhenixCuCuSyst=0x0;

TGraphErrors *graphMeanPtPhenixpp=0x0;
TGraphErrors *graphMeanPtPhenixppSyst =0x0;

TGraphErrors *graphMeanPtALICE2760=0x0;
TGraphErrors *graphMeanPtALICE2760Syst =0x0;
TGraphErrors *graphMeanPtALICE2760pp=0x0;
TGraphErrors *graphMeanPtALICE2760Systpp =0x0;
TGraphErrors *graphraaALICE2760=0x0;
TGraphErrors *graphraaALICE2760Syst =0x0;


//TGraphErrors *graphMeanPtALICEpp=0x0;
//TGraphErrors *graphMeanPtALICEppSyst=0x0;


 void DrawLegendaryLegendMPt();
 void DrawLegendaryLegendMPtSq();
 void PrepareLowerEnergyGraphs();
 void PrepareTheoryCurvePengfey();  
 void PrepareTheoryCurveRapp();
 void PrepareTheoryCurveSHM();


  TGraphErrors *GetCentMptStat5020();
  TGraphErrors *GetCentMptSyst5020();

 TGraphErrors *GetCentraaStat5020();
 TGraphErrors *GetCentraaSyst5020();



void plot_meanpT_model();
void plot_raa_model();

/* void plot_meanpT_data(); */
/* void plot_raa_data(); */


void PlotMPtResults(){

  //Style
  //  LoadLibs();
  SetStyle();


  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadTopMargin(0.02);

  
  
  //Theory input
  PrepareTheoryCurvePengfey();
  PrepareTheoryCurveRapp();
  PrepareTheoryCurveSHM();

  //lower energy data graphs
  PrepareLowerEnergyGraphs();

  plot_meanpT_model();
  plot_raa_model();
  

}
void plot_meanpT_model()
{

  TGraphErrors *gr_CentMptStat5020 = (TGraphErrors*)GetCentMptStat5020();
  TGraphErrors *gr_CentMptSyst5020  = (TGraphErrors*)GetCentMptSyst5020();



  TH2F *mh2Dummy = new TH2F("mh2Dummy","mh2Dummy",100,-20.,400,100,1.6,3.7);
  
  mh2Dummy->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #LT #it{p}_{T} #GT (GeV/#it{c})");
  mh2Dummy->SetStats(0);
  mh2Dummy->GetYaxis()->SetTitleSize(0.07);
  mh2Dummy->GetXaxis()->SetTitleSize(0.07);
  mh2Dummy->GetYaxis()->SetTitleOffset(0.75);
  mh2Dummy->GetXaxis()->SetTitleOffset(0.85);
  mh2Dummy->GetYaxis()->SetLabelSize(0.055);
  mh2Dummy->GetXaxis()->SetLabelSize(0.055);
  mh2Dummy->GetXaxis()->SetNdivisions(505);
  mh2Dummy->GetYaxis()->SetNdivisions(505);



  gr_CentMptStat5020->SetMarkerStyle(20);
  gr_CentMptStat5020->SetMarkerSize(2.8);
  gr_CentMptStat5020->SetMarkerColor(2);
  gr_CentMptStat5020->SetLineColor(2);
  gr_CentMptStat5020->SetLineWidth(2);

  gr_CentMptSyst5020->SetLineColor(2);
  gr_CentMptSyst5020->SetFillStyle(0);
  gr_CentMptSyst5020->SetLineWidth(2);

  SetErrorX(gr_CentMptSyst5020,7);

  
 
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 800);
  mh2Dummy->Draw();


  gr_CentMptStat5020->Draw("samePE");
  gr_CentMptSyst5020->Draw("sameE2");



  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.20,0.9,"ALICE");
  tex1.SetTextSize(0.04);

  
  tex1.DrawLatex(0.18,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi, |#it{y}|<0.9");
  tex1.DrawLatex(0.18,0.70," 0.15 < #it{p}_{T} < 15 GeV/#it{c}");


  //  graphPengLow->Draw("Same");
  graphRappMPtLow->Draw("Same");
  graphRappMPtHigh->Draw("Same");
  graphRappMeanPt->Draw("Samee3");
  graphSHMMPtHigh->Draw("Same");
  graphSHMMPtLow->Draw("Same");
  graphSHMMeanPt->Draw("Samee3");


  
  TLegend *leg = new TLegend(0.63, 0.7, 0.9, 0.95);
  leg->SetTextSize(0.035);
  leg->AddEntry(gr_CentMptStat5020,"Data, Pb-Pb","p");
  leg->AddEntry(graphSHMMeanPt, "SHM (Andronic et al.)", "F");
  leg->AddEntry(graphRappMeanPt,"TM1 (Du et al)","F");
  //  leg->AddEntry(graphPengLow,"TM2 (Zhou et al.)","l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->Draw();

  c1->SaveAs("output/MeanPt_vs_Cent_model.pdf");
  delete mh2Dummy;
}

void plot_raa_model()
{

  TGraphErrors *gr_CentraaStat5020 = (TGraphErrors*)GetCentraaStat5020();
  TGraphErrors *gr_CentraaSyst5020  = (TGraphErrors*)GetCentraaSyst5020();



  TH2F *hDummy2 = new TH2F("hDummy2","hDummy2",100,0.,400,100,0.3,2);
  hDummy2->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #it{r}_{AA}");
  hDummy2->SetStats(0);
  hDummy2->GetYaxis()->SetTitleSize(0.07);
  hDummy2->GetXaxis()->SetTitleSize(0.07);
  hDummy2->GetYaxis()->SetTitleOffset(0.85);
  hDummy2->GetXaxis()->SetTitleOffset(0.85);
  hDummy2->GetYaxis()->SetLabelSize(0.055);
  hDummy2->GetXaxis()->SetLabelSize(0.055);
  hDummy2->GetXaxis()->SetNdivisions(505);
  hDummy2->GetYaxis()->SetNdivisions(505);


  gr_CentraaStat5020->SetMarkerStyle(20);
  gr_CentraaStat5020->SetMarkerSize(2.8);
  gr_CentraaStat5020->SetMarkerColor(2);
  gr_CentraaStat5020->SetLineColor(2);
  gr_CentraaStat5020->SetLineWidth(2);

  gr_CentraaSyst5020->SetLineColor(2);
  gr_CentraaSyst5020->SetFillStyle(0);
  gr_CentraaSyst5020->SetLineWidth(2);

  SetErrorX(gr_CentraaSyst5020,7);

  

  
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 700);

  hDummy2->Draw();
  

  TLine *lineSq = new TLine(0,1,400,1);
  lineSq->SetLineStyle(2);
  lineSq->SetLineWidth(2);
  lineSq->Draw();

  /* TBox *boxSq = new TBox(390,(MPtSq_pp-MPtSq_ppCombErr)/MPtSq_pp,400,(MPtSq_pp+MPtSq_ppCombErr)/MPtSq_pp); */
  /* boxSq->SetFillColor(kRed); */
  /* boxSq->SetLineWidth(2); */
  /* boxSq->Draw(); */

  /* TLatex tex1(0.5,0.5," "); */
  /* tex1.SetTextSize(0.048); */
  /* tex1.SetNDC(); */
  /* tex1.DrawLatex(0.68, 0.90,"ALICE"); */
  /* tex1.DrawLatex(0.58, 0.84,"Pb-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"); */
  /* tex1.DrawLatex(0.58, 0.78,"Inclusive J/#psi, |#it{y}| < 0.9"); */
  /* tex1.DrawLatex(0.17, 0.2,"#scale[0.8]{0.15 < #it{p}_{T} < 10 GeV/#it{c}}"); */


  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.20,0.9,"ALICE");
  tex1.SetTextSize(0.04);

  
  tex1.DrawLatex(0.18,0.84,"Pb-Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi, |#it{y}|<0.9");
  tex1.DrawLatex(0.18,0.70," 0.15 < #it{p}_{T} < 15 GeV/#it{c}");

  
  //  graphPengraa->Draw("Same");
  graphRappraaHigh->Draw("Same");
  graphRappraaLow->Draw("Same");
  graphRappraa->Draw("Samee3");

  graphSHMraaLow->Draw("Same");
  graphSHMraaHigh->Draw("Same");
  graphSHMraa->Draw("Samee3");


  gr_CentraaStat5020->Draw("samePE");
  gr_CentraaSyst5020->Draw("sameE2");

  
  TLegend *leg4 = new TLegend(0.63, 0.7, 0.9, 0.95);
  leg4->SetTextSize(0.04);
  leg4->AddEntry(gr_CentraaStat5020,"Data","p");
  leg4->AddEntry(graphSHMMeanPt, "SHM (Andronic et al.)", "F");
  leg4->AddEntry(graphRappMeanPt,"TM1 (Du et al.)","F");

  leg4->SetBorderSize(0);
  leg4->SetFillColor(0);
  leg4->SetFillStyle(0);
  leg4->Draw();



  c1->SaveAs("output/raa_vs_Cent_model.pdf");
}



TGraphErrors *GetCentMptStat5020()
{

  TFile *file = TFile::Open("input/data/MeanpT.root");

  TGraphErrors *MPtStat = (TGraphErrors*)file->Get("gr_pt_2018_sts");

  
  return MPtStat;
}

TGraphErrors *GetCentMptSyst5020()
{

  TFile *file = TFile::Open("input/data/MeanpT.root");
  TGraphErrors *MPtSyst = (TGraphErrors*)file->Get("gr_pt_2018_sys");

  return MPtSyst;
}


TGraphErrors *GetCentraaStat5020()
{

  TFile *file = TFile::Open("input/data/MeanpT_squ.root");

  TGraphErrors *MPtStat = (TGraphErrors*)file->Get("gr_rAA_sts_2018");

  
  return MPtStat;
}

TGraphErrors *GetCentraaSyst5020()
{

  TFile *file = TFile::Open("input/data/MeanpT_squ.root");
  TGraphErrors *MPtSyst = (TGraphErrors*)file->Get("gr_rAA_sys_2018");

  return MPtSyst;
}




/* TGraphErrors *GetCentMptStat5020() */
/* { */

/*   TFile *file = TFile::Open("input/data/MeanpT.root"); */

/*   TGraphErrors *MPtStat = (TGraphErrors*)file->Get("gr_pt_2018_sts"); */

  
/*   return MPtStat; */
/* } */



/*
  
  
  TFile *file = TFile::Open("input/data/MeanPtResultsCorr.root");

  TGraphErrors *MPtStat = (TGraphErrors*)file->Get("MeanPtStat");
  TGraphErrors *MPtSyst = (TGraphErrors*)file->Get("MeanPtSyst");

  TGraphErrors *raaStat = (TGraphErrors*)file->Get("raaStat");
  TGraphErrors *raaSyst = (TGraphErrors*)file->Get("raaSyst");


  raaStat->SetMarkerColor(kRed);
  raaStat->SetLineColor(kRed);
  raaSyst->SetLineColor(kRed);
  

  //  Double_t MPtSq_pp = 10.20; //+-0.29 (syst)                              
 // Double_t MPtSq_ppStatErr = 0.46;
 // Double_t MPtSq_ppSystErr = 0.1;//0.24              

  Double_t MPtSq_ppCombErr = TMath::Sqrt(MPtSq_ppStatErr*MPtSq_ppStatErr + MPtSq_ppSystErr*MPtSq_ppSystErr);

  //Double_t MeanPt502pp = 2.66;//+-0.044 (syst)                                                                                                 
 // Double_t MeanPt502ppStatErr = 0.06;
 // Double_t MeanPt502ppSystErr = 0.01;//0.03    





  const Int_t nBinsALICEpp = 1;

  Double_t ZeroArr[nBinsALICEpp]={0};

  Double_t NPartALICEpp[nBinsALICEpp] = {2};
  Double_t NPartErrALICEpp[nBinsALICEpp] ={5};
  Double_t MeanPtALICEppArr[nBinsALICEpp]= {MeanPt502pp};    

  Double_t MeanPtALICEppStatArr[nBinsALICEpp] = {MeanPt502ppStatErr};                           
  Double_t MeanPtALICEppSystArr[nBinsALICEpp]= {MeanPt502ppSystErr};

  TGraphErrors *graphMeanPtALICEpp = new TGraphErrors( nBinsALICEpp, NPartALICEpp, MeanPtALICEppArr, ZeroArr, MeanPtALICEppStatArr);
  TGraphErrors *graphMeanPtALICEppSyst = new TGraphErrors( nBinsALICEpp, NPartALICEpp, MeanPtALICEppArr,  NPartErrALICEpp, MeanPtALICEppSystArr);



  TH1D *hDummy1 = new TH1D("hDummy1","hDummy1",100,-20.,400);
  hDummy1->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #LT #it{p}_{T} #GT (GeV/#it{c})");
  hDummy1->GetYaxis()->SetRangeUser(1.8,3.4);
  hDummy1->SetStats(0);
  hDummy1->GetYaxis()->SetTitleSize(0.07);
  hDummy1->GetXaxis()->SetTitleSize(0.07);
  hDummy1->GetYaxis()->SetTitleOffset(0.75);
  hDummy1->GetXaxis()->SetTitleOffset(0.85);
  hDummy1->GetYaxis()->SetLabelSize(0.055);
  hDummy1->GetXaxis()->SetLabelSize(0.055);
  hDummy1->GetXaxis()->SetNdivisions(505);
  hDummy1->GetYaxis()->SetNdivisions(505);


  graphMeanPtALICEpp->SetLineWidth(2);
  graphMeanPtALICEpp->SetLineColor(kRed);
  graphMeanPtALICEpp->SetMarkerColor(kRed);
  graphMeanPtALICEpp->SetMarkerStyle(4);
  graphMeanPtALICEpp->SetMarkerSize(1.3);
  
  graphMeanPtALICEppSyst->SetFillColor(1);
  graphMeanPtALICEppSyst->SetFillStyle(0);
  graphMeanPtALICEppSyst->SetLineColor(kRed);
  graphMeanPtALICEppSyst->SetLineWidth(2);
  graphMeanPtALICEppSyst->SetMarkerStyle(4);
  graphMeanPtALICEppSyst->SetMarkerSize(1.5);


  MPtSyst->SetMarkerColor(kRed);
  MPtStat->SetMarkerColor(kRed);
  MPtSyst->SetLineColor(kRed);
  MPtStat->SetLineColor(kRed);
 


 
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
  c1->cd(1);



  hDummy1->DrawCopy();
  graphMeanPtALICEpp->Draw("pz same");
  graphMeanPtALICEppSyst->Draw("e2");
  MPtSyst->Draw("Samee2");
  MPtStat->Draw("Samepz");

  
  TLatex tex(0.5,0.5," ");
  tex.SetTextSize(0.048);
  tex.SetNDC();
  tex.DrawLatex(0.68, 0.90,"ALICE");
  tex.DrawLatex(0.58, 0.84,"Pb-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex.DrawLatex(0.58, 0.78,"Inclusive J/#psi, |#it{y}| < 0.9");
  tex.DrawLatex(0.17, 0.2,"#scale[0.8]{0.15 < #it{p}_{T} < 10 GeV/#it{c}}");

  graphPengLow->Draw("Same");
  graphRappMPtLow->Draw("Same");
  graphRappMPtHigh->Draw("Same");
  graphRappMeanPt->Draw("Samee3");
  graphSHMMPtHigh->Draw("Same");
  graphSHMMPtLow->Draw("Same");
  graphSHMMeanPt->Draw("Samee3");

  //draw again to be on top
  MPtSyst->Draw("Samee2");
  MPtStat->Draw("Samepz");

  TLegend *leg2 = new TLegend(0.16, 0.9, 0.3, 0.95);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(graphMeanPtALICEpp," ","p");
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(0);
  leg2->Draw();

  TLegend *leg3 = new TLegend(0.18, 0.9, 0.3, 0.95);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(MPtStat," ","p");
  leg3->SetBorderSize(0);
  leg3->SetFillColor(0);
  leg3->SetFillStyle(0);
  leg3->Draw();
  
  TLegend *leg = new TLegend(0.15, 0.7, 0.44, 0.95);
  leg->SetTextSize(0.04);
  leg->AddEntry((TObject*)0x0,"Data pp, Pb-Pb","");
  leg->AddEntry(graphSHMMeanPt, "SHM (Andronic et al.)", "F");
  leg->AddEntry(graphRappMeanPt,"TM1 (Du et al)","F");
  leg->AddEntry(graphPengLow,"TM2 (Zhou et al.)","l");
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->Draw();
  
  c1->RedrawAxis();





  TH1D *hDummy2 = new TH1D("hDummy2","hDummy2",100,0.,400);
  hDummy2->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #it{r}_{AA}");
  hDummy2->GetYaxis()->SetRangeUser(0.3,1.5);
  hDummy2->SetStats(0);
  hDummy2->GetYaxis()->SetTitleSize(0.07);
  hDummy2->GetXaxis()->SetTitleSize(0.07);
  hDummy2->GetYaxis()->SetTitleOffset(0.85);
  hDummy2->GetXaxis()->SetTitleOffset(0.85);
  hDummy2->GetYaxis()->SetLabelSize(0.055);
  hDummy2->GetXaxis()->SetLabelSize(0.055);
  hDummy2->GetXaxis()->SetNdivisions(505);
  hDummy2->GetYaxis()->SetNdivisions(505);

  TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
  c2->cd(1);

  hDummy2->DrawCopy("AXIS");
  raaStat->Draw("pz same");
  raaSyst->Draw("e2");

  TLine *lineSq = new TLine(0,1,400,1);
  lineSq->SetLineStyle(2);
  lineSq->SetLineWidth(2);
  lineSq->Draw();

  TBox *boxSq = new TBox(390,(MPtSq_pp-MPtSq_ppCombErr)/MPtSq_pp,400,(MPtSq_pp+MPtSq_ppCombErr)/MPtSq_pp);
  boxSq->SetFillColor(kRed);
  boxSq->SetLineWidth(2);
  boxSq->Draw();

  TLatex tex1(0.5,0.5," ");
  tex1.SetTextSize(0.048);
  tex1.SetNDC();
  tex1.DrawLatex(0.68, 0.90,"ALICE");
  tex1.DrawLatex(0.58, 0.84,"Pb-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.58, 0.78,"Inclusive J/#psi, |#it{y}| < 0.9");
  tex1.DrawLatex(0.17, 0.2,"#scale[0.8]{0.15 < #it{p}_{T} < 10 GeV/#it{c}}");


  graphPengraa->Draw("Same");
  graphRappraaHigh->Draw("Same");
  graphRappraaLow->Draw("Same");
  graphRappraa->Draw("Samee3");

  graphSHMraaLow->Draw("Same");
  graphSHMraaHigh->Draw("Same");
  graphSHMraa->Draw("Samee3");

  raaStat->Draw("Samepz");
  raaSyst->Draw("Samee2");

  TLegend *leg4 = new TLegend(0.15, 0.7, 0.44, 0.95);
  leg4->SetTextSize(0.04);
  leg4->AddEntry(raaStat,"Data","p");
  leg4->AddEntry(graphSHMMeanPt, "SHM (Andronic et al.)", "F");
  leg4->AddEntry(graphRappMeanPt,"TM1 (Du et al.)","F");
  leg4->AddEntry(graphPengLow,"TM2 (Zhou et al.)","l");
  leg4->SetBorderSize(0);
  leg4->SetFillColor(0);
  leg4->SetFillStyle(0);
  leg4->Draw();

  c2->RedrawAxis();

  //comparison to data



  TH1D *hDummy3 = new TH1D("hDummy3","hDummy3",100,-20.,400);
  hDummy3->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #LT #it{p}_{T} #GT (GeV/#it{c})");
  hDummy3->GetYaxis()->SetRangeUser(0.7,3.6);
  hDummy3->SetStats(0);
  hDummy3->GetYaxis()->SetTitleSize(0.065);
  hDummy3->GetXaxis()->SetTitleSize(0.065);
  hDummy3->GetYaxis()->SetTitleOffset(0.8);
  hDummy3->GetXaxis()->SetTitleOffset(0.9);
  hDummy3->GetYaxis()->SetLabelSize(0.055);
  hDummy3->GetXaxis()->SetLabelSize(0.055);
  hDummy3->GetXaxis()->SetNdivisions(505);
  hDummy3->GetYaxis()->SetNdivisions(505);


  TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
  c3->cd(1);
  c3->SetBottomMargin(0.13);
  c3->SetLeftMargin(0.12);
  
  hDummy3->DrawCopy();
  graphMeanPtALICEpp->Draw("pz same");
  //  graphMeanPtALICEppSyst->Draw("Samee2");


  MPtSyst->Draw("Samee2");
  MPtStat->Draw("Samepz");

  //lower energy data points
  graphMeanPtNA50->Draw("Samepz");

  graphMeanPtPhenixAuAu->Draw("Samepz");
  graphMeanPtPhenixAuAuSyst->Draw("Samee2");

  graphMeanPtPhenixCuCu->Draw("Samepz");
  graphMeanPtPhenixCuCuSyst->Draw("Samee2");
  
  graphMeanPtPhenixpp->Draw("Samepz");
  graphMeanPtPhenixppSyst->Draw("Samee2");

  graphMeanPtALICE2760->Draw("Samepz");
  graphMeanPtALICE2760Syst->Draw("Same e2");
  
  graphMeanPtALICE2760pp->Draw("Same pz");
  graphMeanPtALICE2760Systpp->Draw("Same e2");
  
  DrawLegendaryLegendMPt();



  TLatex tex3(0.5,0.5," ");
  tex3.SetTextSize(0.048);
  tex3.SetNDC();
  tex3.DrawLatex(0.65, 0.16,"Inclusive J/#psi");
  

  c3->RedrawAxis();

  
  
  TH1D *hDummy4 = new TH1D("hDummy4","hDummy4",100,0.,400);
  hDummy4->SetTitle(";#LT_{ }#it{N}_{part}_{ }#GT; #it{r}_{AA} ");
  hDummy4->GetYaxis()->SetRangeUser(0.3,2.5);
  hDummy4->SetStats(0);
  hDummy4->GetYaxis()->SetTitleSize(0.075);
  hDummy4->GetXaxis()->SetTitleSize(0.065);
  hDummy4->GetYaxis()->SetTitleOffset(0.7);
  hDummy4->GetXaxis()->SetTitleOffset(0.9);
  hDummy4->GetYaxis()->SetLabelSize(0.055);
  hDummy4->GetXaxis()->SetLabelSize(0.055);
  hDummy4->GetXaxis()->SetNdivisions(505);
  hDummy4->GetYaxis()->SetNdivisions(505);


  
  TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);
  c4->cd(1);

  c4->SetBottomMargin(0.13);
  c4->SetLeftMargin(0.12);
  hDummy4->DrawCopy();

  raaStat->Draw("pz same");
  raaSyst->Draw("Samee2");

  graphraaNA50->Draw("Samepz");
  graphraaPhenixAuAu->Draw("Samepz"); 
  graphraaPhenixAuAuSyst->Draw("Samee2");
  graphraaPhenixCuCu->Draw("Samepz");
  graphraaPhenixCuCuSyst->Draw("Samee2");

  graphraaALICE2760->Draw("Same pz");
  graphraaALICE2760Syst->Draw("Same e2");
  
  lineSq->Draw();
  boxSq->Draw();

  raaStat->Draw("Samepz");
  raaSyst->Draw("Samee2");


  DrawLegendaryLegendMPtSq();

  TLatex tex4(0.5,0.5," ");
  tex4.SetTextSize(0.048);
  tex4.SetNDC();
  tex4.DrawLatex(0.65, 0.16,"Inclusive J/#psi");

  c4->RedrawAxis();









*/

  

//}


void DrawLegendaryLegendMPt(){



  //ALICE DATA

  const Int_t One = 1;
  Double_t ppALICEx[One] = {35};
  Double_t ppALICEy[One]     = {3.44};

  TGraph *gr=new TGraph(One, ppALICEx, ppALICEy);
  gr->SetLineWidth(2);
  gr->SetLineColor(kRed);
  gr->SetMarkerColor(kRed);
  gr->SetMarkerStyle(4);
  gr->SetMarkerSize(1.5);
  gr->Draw("pz");

  Double_t ppALICEy2760[One] = {3.27};
  
  TGraph *gr2760=new TGraph(One, ppALICEx, ppALICEy2760);
  gr2760->SetLineWidth(2);
  gr2760->SetLineColor(kBlue);
  gr2760->SetMarkerColor(kBlue);
  gr2760->SetMarkerStyle(25);
  gr2760->SetMarkerSize(1.4);
  gr2760->Draw("pz");

  Double_t PbPbALICEx[One] = {50};
  
  TGraph *gr1=new TGraph(One, PbPbALICEx, ppALICEy);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(kRed);
  gr1->SetMarkerColor(kRed);
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1.5);
  gr1->Draw("pz");

  TGraph *gr1_2760=new TGraph(One, PbPbALICEx, ppALICEy2760);
  gr1_2760->SetLineWidth(2);
  gr1_2760->SetLineColor(kBlue);
  gr1_2760->SetMarkerColor(kBlue);
  gr1_2760->SetMarkerStyle(21);
  gr1_2760->SetMarkerSize(1.5);
  gr1_2760->Draw("pz");



 //PHENIX DATA

 Double_t ppPHENIXx[One] = {20};
 Double_t ppPHENIXy[One] = {3.1};

 TGraph *gr2=new TGraph(One, ppPHENIXx, ppPHENIXy);
 gr2->SetLineWidth(2);
 gr2->SetLineColor(kBlack);
 gr2->SetMarkerColor(kBlack);
 gr2->SetMarkerStyle(27);
 gr2->SetMarkerSize(2);
 gr2->Draw("pz");


 Double_t CuCuPHENIXx[One] = {35};
 Double_t CuCuPHENIXy[One] = {3.1};

 TGraph *gr3=new TGraph(One, CuCuPHENIXx, CuCuPHENIXy);
 gr3->SetLineWidth(2);
 gr3->SetLineColor(kGray+1);
 gr3->SetMarkerColor(kGray+1);
 gr3->SetMarkerStyle(33);
 gr3->SetMarkerSize(2);
 gr3->Draw("pz");


 Double_t AuAuPHENIXx[One] = {50};
 Double_t AuAuPHENIXy[One] = {3.1};

 TGraph *gr4=new TGraph(One, AuAuPHENIXx, AuAuPHENIXy);
 gr4->SetLineWidth(2);
 gr4->SetLineColor(kBlack);
 gr4->SetMarkerColor(kBlack);
 gr4->SetMarkerStyle(33);
 gr4->SetMarkerSize(2);
 gr4->Draw("pz");




 Double_t PbPbNA50x[One] = {50};
 Double_t PbPbNA50y[One] = {2.93};

 TGraph *gr5=new TGraph(One,  PbPbNA50x,  PbPbNA50y);
 gr5->SetLineWidth(2);
 gr5->SetLineColor(kGreen-1);
 gr5->SetMarkerColor(kGreen-1);
 gr5->SetMarkerStyle(34);
 gr5->SetMarkerSize(1.5);
 gr5->Draw("pz");

 // NA50, #sqrt{s_{NN}}=17.3 GeV, Pb-Pb, |y|<1


 TLatex tex3(0.5,0.5," ");
 tex3.SetTextSize(0.035);
 // tex3.SetNDC();
 tex3.DrawLatex(65,3.4,"ALICE, #sqrt{#it{s}_{NN}} = 5.02 TeV, pp, Pb-Pb, |#it{y}|<0.9");
 tex3.DrawLatex(65,3.23,"ALICE, #sqrt{#it{s}_{NN}} = 2.76 TeV, pp, Pb-Pb, |#it{y}|<0.8");
 tex3.DrawLatex(65,3.06,"PHENIX,#sqrt{#it{s}_{NN}} = 0.2 TeV, pp, Cu-Cu, Au-Au, |#it{y}|<0.35");
 tex3.DrawLatex(65,2.89,"NA50, #sqrt{#it{s}_{NN}} = 17.3 GeV, Pb-Pb, |#it{y}|<1");


   
}
void DrawLegendaryLegendMPtSq(){

 //ALICE DATA                                                                                                                                   

  const Int_t One = 1;
 Double_t PbPbSqALICEx[One] = {45};
 Double_t ppSqALICEy[One] = {2.34};

 TGraph *gr1=new TGraph(One, PbPbSqALICEx, ppSqALICEy);
 gr1->SetLineWidth(2);
 gr1->SetLineColor(kRed);
 gr1->SetMarkerColor(kRed);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1.5);
 gr1->Draw("pz");


 Double_t ppSqALICEy2760[One] = {2.19};

 TGraph *gr1_2760=new TGraph(One, PbPbSqALICEx, ppSqALICEy2760);
 gr1_2760->SetLineWidth(2);
 gr1_2760->SetLineColor(kBlue);
 gr1_2760->SetMarkerColor(kBlue);
 gr1_2760->SetMarkerStyle(21);
 gr1_2760->SetMarkerSize(1.5);
 gr1_2760->Draw("pz");
 

 //PHENIX DATA                                                                                                                                                                     
 Double_t CuCuPHENIXx[One] = {30};
 Double_t CuCuPHENIXy[One] = {2.04};

 TGraph *gr3=new TGraph(One, CuCuPHENIXx, CuCuPHENIXy);
 gr3->SetLineWidth(2);
 gr3->SetLineColor(kGray+1);
 gr3->SetMarkerColor(kGray+1);
 gr3->SetMarkerStyle(33);
 gr3->SetMarkerSize(2);
 gr3->Draw("pz");


 Double_t AuAuPHENIXx[One] = {45};
 Double_t AuAuPHENIXy[One] = {2.04};

 TGraph *gr4=new TGraph(One, AuAuPHENIXx, AuAuPHENIXy);
 gr4->SetLineWidth(2);
 gr4->SetLineColor(kBlack);
 gr4->SetMarkerColor(kBlack);
 gr4->SetMarkerStyle(33);
 gr4->SetMarkerSize(2);
 gr4->Draw("pz");






 Double_t PbPbNA50x[One] = {45};
 Double_t PbPbNA50y[One] = {1.89};

 TGraph *gr5=new TGraph(One,  PbPbNA50x,  PbPbNA50y);
 gr5->SetLineWidth(2);
 gr5->SetLineColor(kGreen-1);
 gr5->SetMarkerColor(kGreen-1);
 gr5->SetMarkerStyle(34);
 gr5->SetMarkerSize(1.5);
 gr5->Draw("pz");


 TLatex tex3(0.5,0.5," ");
 tex3.SetTextSize(0.035);
 // tex3.SetNDC();
 tex3.DrawLatex(60,2.3,"ALICE, #sqrt{#it{s}_{NN}} = 5.02 TeV, Pb-Pb, |#it{y}|<0.9");
 tex3.DrawLatex(60,2.15,"ALICE, #sqrt{#it{s}_{NN}} = 2.76 TeV, Pb-Pb, |#it{y}|<0.8");
 tex3.DrawLatex(60,2.0,"PHENIX,#sqrt{#it{s}_{NN}} = 0.2 TeV, Cu-Cu, Au-Au, |#it{y}|<0.35");
 tex3.DrawLatex(60,1.85,"NA50, #sqrt{#it{s}_{NN}} = 17.3 GeV, Pb-Pb, |#it{y}|<1");



}
void PrepareLowerEnergyGraphs(){
 
  //////////DATAPOINTS//////////////

  ///////
  //NA50////
  //////


  const Int_t nBinsNA50 = 15;

  Double_t NPartNA50[nBinsNA50] = {47, 81, 108, 139, 166, 190, 213, 237, 261, 281, 305, 329, 349, 373, 403};

  Double_t MeanPtNA50[nBinsNA50] = {1.072, 1.108, 1.130, 1.136, 1.151, 1.176, 1.174, 1.176, 1.179, 1.192, 1.183, 1.187, 1.191, 1.196, 1.222};
  Double_t MeanPtErrNA50[nBinsNA50] = {0.005, 0.007, 0.006, 0.007, 0.007, 0.008, 0.006, 0.009, 0.007, 0.009, 0.007, 0.010, 0.009, 0.012, 0.014};

  Double_t MeanPtSqNA50[nBinsNA50] = {1.504, 1.603, 1.670, 1.691, 1.735, 1.799, 1.804, 1.825, 1.831, 1.853, 1.844, 1.827, 1.864, 1.870, 1.946};
  Double_t MeanPtSqErrNA50[nBinsNA50] = {0.012, 0.021, 0.019, 0.020, 0.021, 0.023, 0.020, 0.027, 0.022, 0.025, 0.022, 0.030, 0.028, 0.035, 0.043};

  Double_t raaNA50[nBinsNA50] = {};
  Double_t raaNA50Err[nBinsNA50] = {};

  Double_t MeanPtSqNA50ppVal = 1.11;
  Double_t MeanPtSqNA50ppValErr = 0.02;
  Double_t ZeroArr[nBinsNA50] = {0};

  for (Int_t iCount = 0; iCount < nBinsNA50; iCount++) { raaNA50[iCount] = MeanPtSqNA50[iCount]/MeanPtSqNA50ppVal;
    raaNA50Err[iCount] = TMath::Sqrt((0.02/1.11)*(0.02/1.11) + (MeanPtSqErrNA50[iCount]/MeanPtSqNA50[iCount])*(MeanPtSqErrNA50[iCount]/MeanPtSqNA50[iCount]))*raaNA50[iCount];}



  ////
  // ALICE 2.76
  ////


  const Int_t nBinsALICE2760 = 3;
  Double_t NPartALICE2760[nBinsALICE2760]    = {356.,192.,38.};
  Double_t NPartErrALICE2760_0[nBinsALICE2760] = {0.,0.,0.};
  Double_t NPartErrALICE2760[nBinsALICE2760] = {5.,5.,5.};


  

  Double_t MeanPtALICE2760[nBinsALICE2760] = {2.23,2.01,2.02};
  Double_t MeanPtALICE2760StatErr[nBinsALICE2760] = {0.1,0.12,0.19};
  Double_t MeanPtALICE2760SystErr[nBinsALICE2760] = {TMath::Sqrt(0.08*0.08 + 0.04*0.04),
						     TMath::Sqrt(0.08*0.08 + 0.04*0.04),
						     TMath::Sqrt(0.29*0.29 + 0.04*0.04)};
  
  Double_t raaALICE2760[nBinsALICE2760]        = {0.61,0.55,0.57};
  Double_t raaALICE2760StatErr[nBinsALICE2760] = {0.06,0.07,0.12};
  Double_t raaALICE2760SystErr[nBinsALICE2760] = {TMath::Sqrt(0.03*0.03 + 0.01*0.01),
						      TMath::Sqrt(0.04*0.04 + 0.01*0.01),
						      TMath::Sqrt(0.13*0.13 + 0.01*0.01)};
  

  graphMeanPtALICE2760 = new TGraphErrors(nBinsALICE2760,NPartALICE2760 ,MeanPtALICE2760 , NPartErrALICE2760_0, MeanPtALICE2760StatErr);
  graphMeanPtALICE2760Syst = new TGraphErrors(nBinsALICE2760,NPartALICE2760 ,MeanPtALICE2760 , NPartErrALICE2760, MeanPtALICE2760SystErr);

  graphraaALICE2760 = new TGraphErrors(nBinsALICE2760,NPartALICE2760 ,raaALICE2760 , NPartErrALICE2760_0, raaALICE2760StatErr);
  graphraaALICE2760Syst = new TGraphErrors(nBinsALICE2760,NPartALICE2760 ,raaALICE2760 , NPartErrALICE2760, raaALICE2760SystErr);
  


  graphMeanPtALICE2760->SetMarkerStyle(21);
  graphMeanPtALICE2760->SetMarkerColor(kBlue);
  graphMeanPtALICE2760->SetMarkerSize(1.5);
  graphMeanPtALICE2760->SetLineColor(kBlue);
  graphMeanPtALICE2760->SetLineWidth(2);

  graphMeanPtALICE2760Syst->SetLineWidth(2);
  graphMeanPtALICE2760Syst->SetLineColor(kBlue);
  graphMeanPtALICE2760Syst->SetFillStyle(0);


  graphraaALICE2760->SetMarkerStyle(21);
  graphraaALICE2760->SetMarkerColor(kBlue);
  graphraaALICE2760->SetMarkerSize(1.5);
  graphraaALICE2760->SetLineColor(kBlue);
  graphraaALICE2760->SetLineWidth(2);

  graphraaALICE2760Syst->SetLineWidth(2);
  graphraaALICE2760Syst->SetLineColor(kBlue);
  graphraaALICE2760Syst->SetFillStyle(0);


  const Int_t nBinsALICE2760pp = 1;
  Double_t NPartALICE2760pp[nBinsALICE2760pp]    = {2.};
  Double_t NPartErrALICE2760pp[nBinsALICE2760pp] = {0.};

  Double_t MeanPtALICE2760pp[nBinsALICE2760pp] = {2.57};
  Double_t MeanPtALICE2760StatErrpp[nBinsALICE2760pp] = {0.02};
  Double_t MeanPtALICE2760SystErrpp[nBinsALICE2760pp] = {0.01};

  
  graphMeanPtALICE2760pp = new TGraphErrors(nBinsALICE2760pp,NPartALICE2760pp ,MeanPtALICE2760pp , NPartErrALICE2760pp, MeanPtALICE2760StatErrpp);
  graphMeanPtALICE2760Systpp = new TGraphErrors(nBinsALICE2760pp,NPartALICE2760pp ,MeanPtALICE2760pp , NPartErrALICE2760pp, MeanPtALICE2760SystErrpp);
  

  graphMeanPtALICE2760pp->SetMarkerStyle(25);
  graphMeanPtALICE2760pp->SetMarkerColor(kBlue);
  graphMeanPtALICE2760pp->SetMarkerSize(1.7);
  graphMeanPtALICE2760pp->SetLineColor(kBlue);
  graphMeanPtALICE2760pp->SetLineWidth(2);

  graphMeanPtALICE2760Systpp->SetLineWidth(2);
  graphMeanPtALICE2760Systpp->SetLineColor(kBlue);
  graphMeanPtALICE2760Systpp->SetFillStyle(0);

  
  
  //////
  //PHENIX///
  //////

  const Int_t nBinsPhenixAuAu = 4;
  Double_t NPartPhenixAuAu[nBinsPhenixAuAu] = {280, 140, 60, 14};
  Double_t NPartErrPhenixAuAu[nBinsPhenixAuAu] = {5,5,5,5};

  //from publication
  // Double_t MeanPtSqPhenixAuAu[nBinsPhenixAuAu] = {3.6, 4.6, 4.5, 3.6};
  // Double_t MeanPtSqPhenixAuAuStatErr[nBinsPhenixAuAu] = {0.6, 0.5, 0.7, 0.9};
  /// Double_t MeanPtSqPhenixAuAuSystErr[nBinsPhenixAuAu] = {0.1, 0.1, 0.2, 0.2};

  //Julians calculation
  Double_t MeanPtSqPhenixAuAu[nBinsPhenixAuAu] = {3.682, 4.491, 4.433, 3.462};
  Double_t MeanPtSqPhenixAuAuStatErr[nBinsPhenixAuAu] = {0.558, 0.515, 0.684, 0.958};
  Double_t MeanPtSqPhenixAuAuSystErr[nBinsPhenixAuAu] = {0.199, 0.212, 0.2, 0.152};
  //Julians calculation
  Double_t MeanPtPhenixAuAu[nBinsPhenixAuAu] = {1.641, 1.836, 1.763,  1.509};
  Double_t MeanPtPhenixAuAuStatErr[nBinsPhenixAuAu] = {0.176, 0.162, 0.202, 0.298};
  Double_t MeanPtPhenixAuAuSystErr[nBinsPhenixAuAu] = {0.091, 0.087, 0.076, 0.063};

  Double_t raaPhenixAuAu[nBinsPhenixAuAu] = {};
  Double_t raaPhenixAuAuStatErr[nBinsPhenixAuAu] = {};
  Double_t raaPhenixAuAuSystErr[nBinsPhenixAuAu] = {};

  //early paper values
  //Double_t MeanPtSqPhenixppVal = 4.1;
  ///Double_t MeanPtSqPhenixppValStatErr = 0.2;
  //Double_t MeanPtSqPhenixppValSystErr = 0.1;

  //calculated from 2012 spectrum:
  Double_t MeanPtSqPhenixppVal = 3.896;
  Double_t MeanPtSqPhenixppValStatErr = 0.156;
  Double_t MeanPtSqPhenixppValSystErr = 0.124;

  //calculated from 2012 spectrum:                                                                                                                                                
  Double_t MeanPtPhenixppVal = 1.709;
  Double_t MeanPtPhenixppValStatErr = 0.049;
  Double_t MeanPtPhenixppValSystErr = 0.055;



  for (Int_t iCount = 0; iCount < nBinsPhenixAuAu; iCount++) { raaPhenixAuAu[iCount] = MeanPtSqPhenixAuAu[iCount]/MeanPtSqPhenixppVal;
    raaPhenixAuAuStatErr[iCount] = TMath::Sqrt((MeanPtSqPhenixppValStatErr/MeanPtSqPhenixppVal)*(MeanPtSqPhenixppValStatErr/MeanPtSqPhenixppVal) + (MeanPtSqPhenixAuAuStatErr[iCount]/MeanPtSqPhenixAuAu[iCount])*(MeanPtSqPhenixAuAuStatErr[iCount]/MeanPtSqPhenixAuAu[iCount]))*raaPhenixAuAu[iCount];

    raaPhenixAuAuSystErr[iCount] = TMath::Sqrt((MeanPtSqPhenixppValSystErr/MeanPtSqPhenixppVal)*(MeanPtSqPhenixppValSystErr/MeanPtSqPhenixppVal) + (MeanPtSqPhenixAuAuSystErr[iCount]/MeanPtSqPhenixAuAu[iCount])*(MeanPtSqPhenixAuAuSystErr[iCount]/MeanPtSqPhenixAuAu[iCount]))*raaPhenixAuAu[iCount];
}



  const Int_t nBinsPhenixCuCu = 3;
  Double_t NPartPhenixCuCu[nBinsPhenixCuCu] = {85.9, 45.2, 21.2};
  Double_t NPartErrPhenixCuCu[nBinsPhenixCuCu] = {5,5,5};

  Double_t MeanPtSqPhenixCuCu[nBinsPhenixAuAu] = {4.24, 4.26, 4.04};
  Double_t MeanPtSqPhenixCuCuStatErr[nBinsPhenixAuAu] = {0.28, 0.27, 0.38};
  Double_t MeanPtSqPhenixCuCuSystErr[nBinsPhenixAuAu] = {0.14, 0.13, 0.16};

  Double_t MeanPtPhenixCuCu[nBinsPhenixAuAu] = {1.769, 1.788, 1.720};
  Double_t MeanPtPhenixCuCuStatErr[nBinsPhenixAuAu] = {0.112, 0.113, 0.168};
  Double_t MeanPtPhenixCuCuSystErr[nBinsPhenixAuAu] = {0.063, 0.064, 0.064};

  Double_t raaPhenixCuCu[nBinsPhenixAuAu] = {};
  Double_t raaPhenixCuCuStatErr[nBinsPhenixAuAu] = {};
  Double_t raaPhenixCuCuSystErr[nBinsPhenixAuAu] = {};

  //add pp reference error quadratically

  for (Int_t iCount = 0; iCount < nBinsPhenixCuCu; iCount++) { raaPhenixCuCu[iCount] = MeanPtSqPhenixCuCu[iCount]/MeanPtSqPhenixppVal;
    raaPhenixCuCuStatErr[iCount] = TMath::Sqrt((MeanPtSqPhenixppValStatErr/MeanPtSqPhenixppVal)*(MeanPtSqPhenixppValStatErr/MeanPtSqPhenixppVal) + (MeanPtSqPhenixCuCuStatErr[iCount]/MeanPtSqPhenixAuAu[iCount])*(MeanPtSqPhenixCuCuStatErr[iCount]/MeanPtSqPhenixAuAu[iCount]))*raaPhenixCuCu[iCount];

 raaPhenixCuCuSystErr[iCount] = TMath::Sqrt((MeanPtSqPhenixppValSystErr/MeanPtSqPhenixppVal)*(MeanPtSqPhenixppValSystErr/MeanPtSqPhenixppVal) + (MeanPtSqPhenixCuCuSystErr[iCount]/MeanPtSqPhenixCuCu[iCount])*(MeanPtSqPhenixCuCuSystErr[iCount]/MeanPtSqPhenixCuCu[iCount]))*raaPhenixCuCu[iCount];
  }



/////////PLOTS/////////////////////


 //NA50
    graphMeanPtNA50 = new TGraphErrors(nBinsNA50, NPartNA50, MeanPtNA50, ZeroArr, MeanPtErrNA50);
    graphMeanPtSqNA50 = new TGraphErrors(nBinsNA50, NPartNA50, MeanPtSqNA50, ZeroArr, MeanPtSqErrNA50);
    graphraaNA50 = new TGraphErrors(nBinsNA50, NPartNA50, raaNA50, ZeroArr, raaNA50Err);
    
    graphMeanPtNA50->SetLineWidth(2);
    graphMeanPtNA50->SetLineColor(kGreen-1); 
    graphMeanPtNA50->SetMarkerColor(kGreen-1);
    graphMeanPtNA50->SetMarkerStyle(34);
    graphMeanPtNA50->SetMarkerSize(1.5);
    //    graphMeanPtNA50->SetLineColor(kRed);
  //  graphMeanPtNA50->Draw("pz");
   //   MeanPtNA50->Draw("e2");


    //PHENIX AU+AU
    graphMeanPtPhenixAuAu = new TGraphErrors( nBinsPhenixAuAu, NPartPhenixAuAu, MeanPtPhenixAuAu, ZeroArr, MeanPtPhenixAuAuStatErr);
    graphMeanPtPhenixAuAuSyst = new TGraphErrors( nBinsPhenixAuAu, NPartPhenixAuAu, MeanPtPhenixAuAu,  NPartErrPhenixAuAu, MeanPtPhenixAuAuSystErr);

    graphraaPhenixAuAu = new TGraphErrors( nBinsPhenixAuAu, NPartPhenixAuAu, raaPhenixAuAu, ZeroArr, raaPhenixAuAuStatErr);
    graphraaPhenixAuAuSyst = new TGraphErrors( nBinsPhenixAuAu, NPartPhenixAuAu, raaPhenixAuAu,  NPartErrPhenixAuAu, raaPhenixAuAuSystErr);


    //PHENIX CU+CU

    graphMeanPtPhenixCuCu = new TGraphErrors( nBinsPhenixCuCu, NPartPhenixCuCu, MeanPtPhenixCuCu, ZeroArr, MeanPtPhenixCuCuStatErr);
    graphMeanPtPhenixCuCuSyst = new TGraphErrors( nBinsPhenixCuCu, NPartPhenixCuCu, MeanPtPhenixCuCu,  NPartErrPhenixCuCu, MeanPtPhenixCuCuSystErr);

    graphraaPhenixCuCu = new TGraphErrors( nBinsPhenixCuCu, NPartPhenixCuCu, raaPhenixCuCu, ZeroArr, raaPhenixCuCuStatErr);
    graphraaPhenixCuCuSyst = new TGraphErrors( nBinsPhenixCuCu, NPartPhenixCuCu, raaPhenixCuCu,  NPartErrPhenixCuCu, raaPhenixCuCuSystErr);

    const Int_t nBinsPhenixpp = 1;
    Double_t NPartPhenixpp[nBinsPhenixpp] = {2};
    Double_t NPartErrPhenixpp[nBinsPhenixpp] ={5};
    Double_t MeanPtPhenixppArr[nBinsPhenixpp]= {MeanPtPhenixppVal};
    Double_t MeanPtPhenixppStatArr[nBinsPhenixpp] = {MeanPtPhenixppValStatErr};
    Double_t MeanPtPhenixppSystArr[nBinsPhenixpp]= {MeanPtPhenixppValSystErr};

    //PHENIX pp
    graphMeanPtPhenixpp = new TGraphErrors( nBinsPhenixpp, NPartPhenixpp, MeanPtPhenixppArr, ZeroArr, MeanPtPhenixppStatArr);
    graphMeanPtPhenixppSyst = new TGraphErrors( nBinsPhenixpp, NPartPhenixpp, MeanPtPhenixppArr,  NPartErrPhenixpp, MeanPtPhenixppSystArr);


    //PP reference
    const Int_t nBinsALICEpp = 1;
    Double_t NPartALICEpp[nBinsPhenixpp] = {2};
    Double_t NPartErrALICEpp[nBinsPhenixpp] ={5};
    Double_t MeanPtALICEppArr[nBinsPhenixpp]= {MeanPt502pp}; //0.15-10GeV
    Double_t MeanPtALICEppStatArr[nBinsPhenixpp] = {MeanPt502ppStatErr}; 
    Double_t MeanPtALICEppSystArr[nBinsPhenixpp]= {MeanPt502ppSystErr};


    //ALICE pp

  //  graphMeanPtALICEpp = new TGraphErrors( nBinsALICEpp, NPartALICEpp, MeanPtALICEppArr, ZeroArr, MeanPtALICEppStatArr);
  //  graphMeanPtALICEppSyst = new TGraphErrors( nBinsALICEpp, NPartALICEpp, MeanPtALICEppArr,  NPartErrALICEpp, MeanPtALICEppSystArr);








    
    ////<pT>/////////////////////

    //PHENIX                                                                                                                                                               

    graphMeanPtPhenixAuAu->SetLineWidth(2);
    graphMeanPtPhenixAuAu->SetLineColor(kBlack);
    graphMeanPtPhenixAuAu->SetMarkerColor(kBlack);
    graphMeanPtPhenixAuAu->SetMarkerStyle(33);
    graphMeanPtPhenixAuAu->SetMarkerSize(2);
   // graphMeanPtPhenixAuAu->Draw("pz");

    graphMeanPtPhenixAuAuSyst->SetFillColor(1);
    graphMeanPtPhenixAuAuSyst->SetFillStyle(0);
    //  ci = TColor::GetColor("#ff0000");                                                                                                                                        
                                                                                                                                                                                 
    graphMeanPtPhenixAuAuSyst->SetLineColor(kBlack);
    graphMeanPtPhenixAuAuSyst->SetLineWidth(2);
                                                                                                                                                                               
    graphMeanPtPhenixAuAuSyst->SetMarkerStyle(20);
    graphMeanPtPhenixAuAuSyst->SetMarkerSize(1.5);
    //graphMeanPtPhenixAuAuSyst->Draw("e2");



    graphMeanPtPhenixCuCu->SetLineWidth(2);
    graphMeanPtPhenixCuCu->SetLineColor(kGray+1);
    graphMeanPtPhenixCuCu->SetMarkerColor(kGray+1);
    graphMeanPtPhenixCuCu->SetMarkerStyle(33);
    graphMeanPtPhenixCuCu->SetMarkerSize(2);
    //graphMeanPtPhenixCuCu->Draw("pz");

    graphMeanPtPhenixCuCuSyst->SetFillColor(1);
    graphMeanPtPhenixCuCuSyst->SetFillStyle(0);
                                                                                                                                                                                  
    graphMeanPtPhenixCuCuSyst->SetLineColor(kGray+1);
    graphMeanPtPhenixCuCuSyst->SetLineWidth(2);
    
    graphMeanPtPhenixCuCuSyst->SetMarkerStyle(20);
    graphMeanPtPhenixCuCuSyst->SetMarkerSize(1.5);
   // graphMeanPtPhenixCuCuSyst->Draw("e2");
    graphMeanPtPhenixAuAu->SetTitle("");


    
    graphMeanPtPhenixpp->SetLineWidth(2);
    graphMeanPtPhenixpp->SetLineColor(kBlack);
    graphMeanPtPhenixpp->SetMarkerColor(kBlack);
    graphMeanPtPhenixpp->SetMarkerStyle(27);
    graphMeanPtPhenixpp->SetMarkerSize(2);
    ///graphMeanPtPhenixpp->Draw("pz");



    graphMeanPtPhenixppSyst->SetFillColor(1);
    graphMeanPtPhenixppSyst->SetFillStyle(0);
    graphMeanPtPhenixppSyst->SetLineColor(kBlack);
    graphMeanPtPhenixppSyst->SetLineWidth(2);
    graphMeanPtPhenixppSyst->SetMarkerStyle(20);
    graphMeanPtPhenixppSyst->SetMarkerSize(1.5);
    //graphMeanPtPhenixppSyst->Draw("e2");
 




    ///////////////<pT^2>/////////////////////


    graphraaNA50->SetLineWidth(2);
    graphraaNA50->SetLineColor(kGreen-1);
    graphraaNA50->SetMarkerColor(kGreen-1);
    graphraaNA50->SetMarkerStyle(34);
    graphraaNA50->SetMarkerSize(1.5);
    //graphraaNA50->Draw("pz");



    graphraaPhenixAuAu->SetLineColor(kBlack);
    graphraaPhenixAuAu->SetMarkerColor(kBlack);
    graphraaPhenixAuAu->SetMarkerStyle(33);
    graphraaPhenixAuAu->SetMarkerSize(2);
    //graphraaPhenixAuAu->Draw("apz");

    graphraaPhenixAuAuSyst->SetFillColor(1);
    graphraaPhenixAuAuSyst->SetFillStyle(0);
    graphraaPhenixAuAuSyst->SetLineColor(kBlack);
    graphraaPhenixAuAuSyst->SetLineWidth(2);

    graphraaPhenixAuAuSyst->SetMarkerStyle(20);
    graphraaPhenixAuAuSyst->SetMarkerSize(1.5);

    //graphraaPhenixAuAuSyst->Draw("e2");
    



    graphraaPhenixCuCu->SetLineWidth(2);
    graphraaPhenixCuCu->SetLineColor(kGray+1);
    graphraaPhenixCuCu->SetMarkerColor(kGray+1);
    graphraaPhenixCuCu->SetMarkerStyle(33);
    graphraaPhenixCuCu->SetMarkerSize(2);
//    graphraaPhenixCuCu->Draw("pz");

    graphraaPhenixCuCuSyst->SetFillColor(1);
    graphraaPhenixCuCuSyst->SetFillStyle(0);
    graphraaPhenixCuCuSyst->SetLineColor(kGray+1);
    graphraaPhenixCuCuSyst->SetLineWidth(2);

    graphraaPhenixCuCuSyst->SetMarkerStyle(20);
    graphraaPhenixCuCuSyst->SetMarkerSize(1.5);

  //  graphraaPhenixCuCuSyst->Draw("e2");

    graphraaPhenixAuAu->SetTitle("");





   ///////LEGEND////////////



}

void PrepareTheoryCurvePengfey(){


  //============================                                                                                                                
  //PENGFEY                                                                                                                                     
  //============================                                                                                                                

  const Int_t NBinsPeng=26; 
  Double_t Peng_MPt[NBinsPeng]={0};
  Double_t Peng_nPart[NBinsPeng]={0};

  std::ifstream infilePengMPt("input/model/MeanPtPengfeyInFile.txt");

  int lineCounterRapp=0;

  double r1,r2,r3;

  while (infilePengMPt >> r1 >> r2 >> r3 )
    {
      //      cout << "Line " << lineCounterRapp << r1 << " " << r2 << "" << r3  <<endl;
      Peng_nPart[lineCounterRapp] = r2;

      Peng_MPt[lineCounterRapp]= r3;

      lineCounterRapp++;

    }


  graphPengLow=new TGraph(NBinsPeng, Peng_nPart, Peng_MPt);
  graphPengLow->SetName("");

  Double_t Peng_MPtSq[NBinsPeng]={0};
  Double_t Peng_raa[NBinsPeng]={0}; 


  std::ifstream infilePengMPtSq("input/model/MeanPtSqPengfeyInFile.txt");

  int lineCounterPeng=0;

  double p1Sq,p2Sq,p3Sq, p4Sq;


  while (infilePengMPtSq >> p1Sq >> p2Sq >> p3Sq >> p4Sq )
    {
      // cout << "Line " << lineCounterPeng << " "<< p1Sq << " " << p2Sq << " " <<  p3Sq << " " << p4Sq  <<endl;

      Peng_MPtSq[lineCounterPeng] = p3Sq;
      Peng_raa[lineCounterPeng]= p4Sq;

      lineCounterPeng++;

    }

  graphPengMPtSq=new TGraph(NBinsPeng, Peng_nPart, Peng_MPtSq);
  graphPengraa=new TGraph(NBinsPeng, Peng_nPart, Peng_raa);




  Int_t cj = TColor::GetColor("#6666ff");
  //  graphPengLow->GetXaxis()->SetLimits(0, 400);
  graphPengLow->SetLineWidth(4);
  graphPengLow->SetLineColor(cj);
  graphPengLow->SetTitle("");


  graphPengMPtSq->SetLineWidth(4);
  graphPengMPtSq->SetLineColor(cj);

  graphPengraa->SetLineWidth(4);
  graphPengraa->SetLineColor(cj);

}


void PrepareTheoryCurveRapp(){
  //==============================================                                                                                              
  //RAPP                                                                                                                                        
  //==============================================                                                                                              

  const Int_t NBinsRapp=29; // danger hard coding going on                                                                                      


  Double_t Rapp_MPtHigh[NBinsRapp]={0};
  Double_t Rapp_MPtLow[NBinsRapp]={0};

  Double_t Rapp_nPart[NBinsRapp]={0};

  Double_t Rapp_MPt[NBinsRapp]={0};
  Double_t Rapp_MPtErr[NBinsRapp]={0};

  //  std::ifstream infileRappMPt("MeanPtRappInFile.txt");                                                                                      
  //Pt<10                                                                                                                                       
  std::ifstream infileRappMPt("input/model/RappPtSmaller10_MeanPtInFile.txt");


  int lineCounterRapp=0;

  double r1,r2,r3;

  while (infileRappMPt >> r1 >> r2 >> r3 )
    {
      //      cout << "Line " << lineCounterRapp << " "<< r1 << " " << r2 << " " <<  r3 << endl;

      Rapp_nPart[lineCounterRapp] = r1;
      Rapp_MPtLow[lineCounterRapp]= r2;
      Rapp_MPtHigh[lineCounterRapp]= r3;

      Rapp_MPt[lineCounterRapp]= (r3+r2)/2;
      Rapp_MPtErr[lineCounterRapp]= r3 - (r3+r2)/2;



      lineCounterRapp++;

    }



  graphRappMPtLow=new TGraph(NBinsRapp, Rapp_nPart, Rapp_MPtLow);
  graphRappMPtHigh=new TGraph(NBinsRapp, Rapp_nPart, Rapp_MPtHigh);

  Int_t ci = TColor::GetColor("#ff9999");
  graphRappMPtHigh->SetLineColor(kOrange+1);
  graphRappMPtHigh->SetLineWidth(2);

  graphRappMPtLow->SetLineWidth(2);
  graphRappMPtLow->SetLineColor(kOrange+1);


  Double_t NullArrayRapp[NBinsRapp] = {0};

  graphRappMeanPt = new TGraphErrors(NBinsRapp, Rapp_nPart,  Rapp_MPt, NullArrayRapp,   Rapp_MPtErr);



  graphRappMeanPt->SetFillColorAlpha(kOrange+1,0.2);
  graphRappMeanPt->SetLineColor(kOrange+1);



  Double_t Rapp_raaHigh[NBinsRapp]={0};
  Double_t Rapp_raaLow[NBinsRapp]={0};

  Double_t Rapp_raa[NBinsRapp]={0};
  Double_t Rapp_raaErr[NBinsRapp]={0};

  Double_t Rapp_MPtSqHigh[NBinsRapp]={0};
  Double_t Rapp_MPtSqLow[NBinsRapp]={0};

  Double_t Rapp_MPtSq[NBinsRapp]={0};
  Double_t Rapp_MPtSqErr[NBinsRapp]={0};

  //not interpolation any more...
  Double_t MPtSqPPMarkusPtSmaller10 = MPtSq_pp;

  std::ifstream infileRappMPtSq("input/model/RappPtSmaller10_MeanPtSqInFile.txt");

  int lineCounterRappMPtSq=0;

  double r1Sq,r2Sq,r3Sq;


  while (infileRappMPtSq >> r1Sq >> r2Sq >> r3Sq )
    {
      //      cout << "Line " << lineCounterRappMPtSq << " "<< r1Sq << " " << r2Sq << " " <<  r3Sq << endl;


      Rapp_MPtSqLow[lineCounterRappMPtSq]=r2Sq;
      Rapp_MPtSqHigh[lineCounterRappMPtSq]=r3Sq;

      Rapp_MPtSq[lineCounterRappMPtSq]=(r3Sq+r2Sq)/2;
      Rapp_MPtSqErr[lineCounterRappMPtSq]=(r3Sq - (r3Sq+r2Sq)/2);

      //Rapp_nPart[lineCounterRappMPtSq] = r1;                                                                                                  
      Rapp_raaLow[lineCounterRappMPtSq]= r2Sq/MPtSqPPMarkusPtSmaller10;
      Rapp_raaHigh[lineCounterRappMPtSq]= r3Sq/MPtSqPPMarkusPtSmaller10;

      Rapp_raa[lineCounterRappMPtSq]= (r3Sq+r2Sq)/(2*MPtSqPPMarkusPtSmaller10);
      Rapp_raaErr[lineCounterRappMPtSq]= (r3Sq - (r3Sq+r2Sq)/2)/MPtSqPPMarkusPtSmaller10;



      lineCounterRappMPtSq++;

    }

  graphRappMPtSqLow=new TGraph(NBinsRapp, Rapp_nPart, Rapp_MPtSqLow);
  graphRappMPtSqHigh=new TGraph(NBinsRapp, Rapp_nPart, Rapp_MPtSqHigh);

  graphRappraaLow=new TGraph(NBinsRapp, Rapp_nPart, Rapp_raaLow);
  graphRappraaHigh=new TGraph(NBinsRapp, Rapp_nPart, Rapp_raaHigh);


  graphRappraaLow->SetLineWidth(2);
  graphRappraaLow->SetLineColor(kOrange+1);

  graphRappraaHigh->SetLineWidth(2);
  graphRappraaHigh->SetLineColor(kOrange+1);


  graphRappraa = new TGraphErrors(NBinsRapp, Rapp_nPart,  Rapp_raa, NullArrayRapp,   Rapp_raaErr);
                                                                                                                                            
 graphRappraa->SetName("Graph2");
 graphRappraa->SetTitle("Graph");

 graphRappraa->SetFillColorAlpha(kOrange+1,0.2);



}
void PrepareTheoryCurveSHM(){

  const Int_t NBinsSHM=4; // danger hard coding going on                                                                                        


  Double_t SHM_MPtHigh[NBinsSHM]={0};
  Double_t SHM_MPtLow[NBinsSHM]={0};

  Double_t SHM_nPart[NBinsSHM]={0};

  Double_t SHM_MPt[NBinsSHM]={0};
  Double_t SHM_MPtErr[NBinsSHM]={0};



  Double_t SHM_raaHigh[NBinsSHM]={0};
  Double_t SHM_raaLow[NBinsSHM]={0};

  Double_t SHM_raa[NBinsSHM]={0};
  Double_t SHM_raaErr[NBinsSHM]={0};

  Double_t SHM_MPtSqHigh[NBinsSHM]={0};
  Double_t SHM_MPtSqLow[NBinsSHM]={0};

  Double_t SHM_MPtSq[NBinsSHM]={0};
  Double_t SHM_MPtSqErr[NBinsSHM]={0};


  std::ifstream infileSHM("input/model/MeanPtSHM09052018.txt");

  int lineCounterSHM=0;

  double r1SHM,r2SHM,r3SHM,r4SHM,r5SHM;

  while (infileSHM >> r1SHM >> r2SHM >> r3SHM >> r4SHM >> r5SHM)
    {
      /* cout << "SHM: " << endl; */
      /* cout << "Line " << lineCounterSHM << " " << r1SHM << " " << r2SHM << " " <<  r3SHM << " " << r4SHM << " " << r5SHM <<  endl; */


      SHM_nPart[lineCounterSHM] = r1SHM;

      SHM_MPtLow[lineCounterSHM]=r2SHM;
      SHM_MPtHigh[lineCounterSHM]=r3SHM;

      SHM_MPt[lineCounterSHM]=(r3SHM + r2SHM)/2;
      SHM_MPtErr[lineCounterSHM]=r3SHM - SHM_MPt[lineCounterSHM];

      /* cout << "SHM_MPt: " <<SHM_MPt[lineCounterSHM] << endl; */
      /* cout << "SHM_MPtErr: " << SHM_MPtErr[lineCounterSHM] << endl; */


      SHM_MPtSqLow[lineCounterSHM]=r4SHM;
      SHM_MPtSqHigh[lineCounterSHM]=r5SHM;

      SHM_raaLow[lineCounterSHM]= r4SHM/MPtSq_pp;
      SHM_raaHigh[lineCounterSHM]= r5SHM/MPtSq_pp;

      SHM_raa[lineCounterSHM]= (r4SHM+r5SHM)/(2*MPtSq_pp);
      SHM_raaErr[lineCounterSHM]= (r5SHM - (r4SHM+r5SHM)/2)/MPtSq_pp;



      lineCounterSHM++;
    }

  graphSHMMPtLow=new TGraph(NBinsSHM, SHM_nPart, SHM_MPtLow);
  graphSHMMPtHigh=new TGraph(NBinsSHM, SHM_nPart, SHM_MPtHigh);

  graphSHMraaLow=new TGraph(NBinsSHM, SHM_nPart, SHM_raaLow);
  graphSHMraaHigh=new TGraph(NBinsSHM, SHM_nPart, SHM_raaHigh);

  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  

  graphSHMMPtLow->SetLineColor(ci1);
  graphSHMMPtLow->SetLineWidth(2);
  graphSHMMPtHigh->SetLineColor(ci1);
  graphSHMMPtHigh->SetLineWidth(2);

  Double_t NullArraySHM[NBinsSHM]={0};

  graphSHMMeanPt = new TGraphErrors(NBinsSHM, SHM_nPart,  SHM_MPt, NullArraySHM, SHM_MPtErr);

  graphSHMMeanPt->SetName("Graph2");
  graphSHMMeanPt->SetTitle("Graph");
                                                      
  graphSHMMeanPt->SetFillColorAlpha(ci1,0.3);                                                                                                     
  graphSHMMeanPt->SetLineColor(ci1);
  graphSHMMeanPt->SetLineWidth(2);

  graphSHMraaLow->SetLineColor(ci1);
  graphSHMraaLow->SetLineWidth(2);

  graphSHMraaHigh->SetLineColor(ci1);
  graphSHMraaHigh->SetLineWidth(2);



  graphSHMraa = new TGraphErrors(NBinsSHM, SHM_nPart,  SHM_raa, NullArraySHM,   SHM_raaErr);

  graphSHMraa->SetName("Graph12");
  graphSHMraa->SetTitle("Grap1h");
                                                                                                    
  graphSHMraa->SetFillColorAlpha(ci1,0.3);                                                                                                      
  graphSHMraa->SetLineColor(ci1);


}
