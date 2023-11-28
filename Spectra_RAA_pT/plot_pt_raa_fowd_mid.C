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

void plot_raa_pt_0_10_data();
void plot_raa_pt_0_10_model();
void plot_raa_pt_0_10_model_new();

/* void plot_raa_pt_30_50(); */
/* void plot_raa_pt_0_10_30_50(); */

//bool 
//double NormUncert1   = 0.0072; // 0-10  %
double NormUncert2   = 0.0069; // 10-30 %
//double NormUncert3   = 0.012; // 30-50 %
double NormUncert_Fw = 0.040; // 0-20  %


//bool 
double NormUncert1   = 0.0072; // 0-10  %
//double NormUncert2   = 0.0069; // 10-30 %
double NormUncert3   = 0.016; // 30-50 %
//xdouble NormUncert_Fw = 0.040; // 0-20  %

double common_un=0.022;


bool run_difference=false;
bool run_difference_option1=false;

inline TGraphErrors *GetPtRaaStat5020_00_10_midy();
inline TGraphErrors *GetPtRaaSyst5020_00_10_midy();

inline TGraph *GetPtRaaTM15020_00_10_midy_model();
inline TGraph *GetPtRaaSHM5020_00_10_midy_model();

inline TGraphErrors *GetPtRaaStat5020_00_20_fwdy();
inline TGraphErrors *GetPtRaaSyst5020_00_20_fwdy();

inline TGraph *GetPtRaaTM15020_00_20_fwdy_model();
inline TGraph *GetPtRaaSHM5020_00_20_fwdy_model();

TFile *final_results_pt_midy;
const char *fileTAMU_pt_raa_0_10_midy;
const char *fileSHM_pt_raa_0_10_midy;

TFile *final_results_pt_fwdy;
const char *fileTAMU_pt_raa_0_10_fwdy;
const char *fileSHM_pt_raa_0_10_fwdy;


const char*  fileTAMU_pt_raa_0_10_midy_final = "../models/Ralf_Rapp/data/m0-10RAA.dat";
const char*  fileTHUA_pt_raa_0_10_midy_final = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-pt-cent0-10--2022Jan5/theory-RAA-pt-cent0-10.dat";
const char*  fileSHM_pt_raa_0_10_midy_final = "../models/SHMc/gRaaSHMc_midy_0_10.txt";
const char*  fileEloss_pt_0_10_midy_final = "../models/energy-loss-model/ElossPredictions.root";

const char*  fileTAMU_pt_raa_0_20_fwdy_final = "../models/Ralf_Rapp/data/f0-20RAA.dat";
const char*  fileTHUA_pt_raa_0_20_fwdy_final = "../models/PengfeiTM2/fig--forward-rapidity-2022_sigmacc718/cent020-RAA-pt-forwdY-2022/theory-RAA-pt-b48.dat";
const char*  fileSHM_pt_raa_0_20_fwdy_final = "../models/SHMc/gRaaSHMc_fwdy_0_20.txt";
const char*  fileEloss_pt_0_20_fwdy_final = "../models/energy-loss-model/ElossPredictions.root";
  


//inline TLine *GetUnitLine();
void plot_pt_raa_fowd_mid()
{

  SetStyle();
  //gStyle->SetOptStat(0);

  final_results_pt_midy=new TFile("input/data/Raa_final.root","READ");
  final_results_pt_fwdy= new TFile("input/data/mumu/RAA_0-20.root","READ");
 
  fileTAMU_pt_raa_0_10_midy = "input/models/TAMU_5020_0010.txt";
  fileSHM_pt_raa_0_10_midy= "input/models/SHM_PtDep_5020_midy_Cent0_11012019.txt";    
  
  fileTAMU_pt_raa_0_10_fwdy = "input/models/PbPb5020-ALICE-201910_Jpsi_0020_for.txt";
  fileSHM_pt_raa_0_10_fwdy= "input/models/SHM_PtDep_5020_fy_Cent1_11012019.txt";    


  fileTAMU_pt_raa_0_10_midy_final = "../models/Ralf_Rapp/data/m0-10RAA.dat";
  fileTHUA_pt_raa_0_10_midy_final = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-pt-cent0-10--2022Jan5/theory-RAA-pt-cent0-10.dat";
  fileSHM_pt_raa_0_10_midy_final = "../models/SHMc/gRaaSHMc_midy_0_10.txt";
  fileEloss_pt_0_10_midy_final = "../models/energy-loss-model/ElossPredictions.root";

  fileTAMU_pt_raa_0_20_fwdy_final = "../models/Ralf_Rapp/data/f0-20RAA.dat";
  fileTHUA_pt_raa_0_20_fwdy_final = "../models/PengfeiTM2/fig--forward-rapidity-2022_sigmacc718/cent020-RAA-pt-forwdY-2022/theory-RAA-pt-b48.dat";
  fileSHM_pt_raa_0_20_fwdy_final = "../models/SHMc/gRaaSHMc_fwdy_0_20.txt";
  fileEloss_pt_0_20_fwdy_final = "../models/energy-loss-model/ElossPredictions.root";
  
  
  
  plot_raa_pt_0_10_data();
  plot_raa_pt_0_10_model();
  plot_raa_pt_0_10_model_new();

}
void plot_raa_pt_0_10_data(){

  TGraphErrors *gr_PtRaaStat5020_00_10_midy = (TGraphErrors*)GetPtRaaStat5020_00_10_midy();
  TGraphErrors *gr_PtRaaSyst5020_00_10_midy  = (TGraphErrors*)GetPtRaaSyst5020_00_10_midy();

  TGraphErrors *gr_PtRaaStat5020_00_20_fwdy = (TGraphErrors*)GetPtRaaStat5020_00_20_fwdy();
  TGraphErrors *gr_PtRaaSyst5020_00_20_fwdy  = (TGraphErrors*)GetPtRaaSyst5020_00_20_fwdy();

  const int Npoint_0_10=7;
  TGraphErrors *gr_PtRaaStat5020_00_10_midy_extro = (TGraphErrors *) gr_PtRaaStat5020_00_10_midy->Clone("gr_PtRaaStat5020_00_10_midy_extro");

  for(int i=0;i<gr_PtRaaStat5020_00_10_midy->GetN();i++) 
    {
      if(i<Npoint_0_10){
        gr_PtRaaStat5020_00_10_midy_extro->SetPoint(i,999,-999);
      }
      else 
        {
          gr_PtRaaStat5020_00_10_midy->SetPoint(i,999,-999);
        }
    }
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.03,0.17,0.14,0.03);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#it{p}_{T} (GeV/#it{c});#it{R}_{AA}",100,0,20,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.88,0.06,0.06,0.015,0.015,504,504);
  
  pad1->cd();
  /* TBox *boxEle0010    = new TBox(14.3,1.-NormUncert1,14.7,1.+NormUncert1); */
  /* boxEle0010->SetFillColor(kRed); */

  /* TBox *boxEle3050    = new TBox(14.3,1.-NormUncert3,14.7,1.+NormUncert3); */
  /* boxEle3050->SetFillColor(kRed); */


  SetTGraphError(gr_PtRaaStat5020_00_10_midy,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaStat5020_00_10_midy_extro,24,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_10_midy,20,2.5,2,2,2,0);
  SetErrorX(gr_PtRaaSyst5020_00_10_midy,0.3);

  SetTGraphError(gr_PtRaaStat5020_00_20_fwdy ,20,2.5,4,4,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_20_fwdy,20,2.5,4,4,2,0);
  SetErrorX(gr_PtRaaSyst5020_00_20_fwdy,0.3);

  mh2Dummy->Draw();

  gr_PtRaaStat5020_00_10_midy->Draw("samePE");
  gr_PtRaaStat5020_00_10_midy_extro->Draw("samePE");
  gr_PtRaaSyst5020_00_10_midy->Draw("sameE2");
  gr_PtRaaStat5020_00_20_fwdy->Draw("samePE");
  gr_PtRaaSyst5020_00_20_fwdy->Draw("sameE2");
  //  boxEle0010->Draw("sameE2");
    

  TBox *boxEle0010    = new TBox(19.2,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.77,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);


  
  TBox *boxEle3050    = new TBox(18.9,1.-NormUncert_Fw,19.3,1.+NormUncert_Fw);
  boxEle3050->SetFillColor(4);

  boxEle0010->Draw("same");
  boxEle3050->Draw("same");
  cout<< " relatative correlated uncertainties at mid 0-10% "<< sqrt(NormUncert1*NormUncert1+common_un*common_un)<<endl;
  cout<< " relatative correlated uncertainties at fwd 0-20% "<< NormUncert_Fw<<endl;

  
  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.62,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  tex1.DrawLatex(0.5,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.5,0.77,"Inclusive J/#psi");

  /* TLegend *legend = new TLegend(0.5,0.6,0.85,0.75); */
  /* SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0); */

  TLegend *legend = new TLegend(0.48,0.6,0.7,0.75);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);  
  legend->AddEntry( gr_PtRaaStat5020_00_10_midy,"0#font[122]{-}10%, |#it{y}| < 0.9","P");
  legend->AddEntry( gr_PtRaaStat5020_00_20_fwdy,"0#font[122]{-}20%, 2.5 < #it{y} < 4","P");
    
  legend->Draw();

  TFile *file=new TFile("Jpsi_RAA_Npart.root","UPDATE");
  file->cd();
  gr_PtRaaStat5020_00_10_midy->Write("gr_RaaPtStat5020_0_10_midy_data");
  gr_PtRaaSyst5020_00_10_midy->Write("gr_RaaPtSyst5020_0_10_midy_data");
  gr_PtRaaStat5020_00_20_fwdy->Write("gr_RaaPtStat5020_0_20_fwdy_data");
  gr_PtRaaSyst5020_00_20_fwdy->Write("gr_RaaPtSyst5020_0_20_fwdy_data");
 

  
  c_temp->SaveAs("output/Raa_Vs_pt_midy_fwdy.pdf");
 
  delete mh2Dummy;
  delete c_temp;


  
}

void plot_raa_pt_0_10_model(){

  TGraphErrors *gr_PtRaaStat5020_00_10_midy = (TGraphErrors*)GetPtRaaStat5020_00_10_midy();
  TGraphErrors *gr_PtRaaSyst5020_00_10_midy  = (TGraphErrors*)GetPtRaaSyst5020_00_10_midy();

  TGraphErrors *gr_PtRaaStat5020_00_20_fwdy = (TGraphErrors*)GetPtRaaStat5020_00_20_fwdy();
  TGraphErrors *gr_PtRaaSyst5020_00_20_fwdy  = (TGraphErrors*)GetPtRaaSyst5020_00_20_fwdy();

  TGraph * gr_PtRaaTM15020_00_10_model=  (TGraph *)GetPtRaaTM15020_00_10_midy_model();
  TGraph * gr_PtRaaSHM5020_00_10_model=  (TGraph *)GetPtRaaSHM5020_00_10_midy_model();

  TGraph * gr_PtRaaTM15020_00_20_model=  (TGraph *)GetPtRaaTM15020_00_20_fwdy_model();
  TGraph * gr_PtRaaSHM5020_00_20_model=  (TGraph *)GetPtRaaSHM5020_00_20_fwdy_model();

  
  gr_PtRaaTM15020_00_20_model->SetFillColorAlpha(kRed-9,0.2);
  gr_PtRaaTM15020_00_20_model->SetLineColor(kRed-9);
  gr_PtRaaTM15020_00_20_model->SetLineStyle(2);

  gr_PtRaaTM15020_00_10_model->SetFillColorAlpha(kOrange+1,0.2);
  gr_PtRaaTM15020_00_10_model->SetLineColor(kOrange+1);

  gr_PtRaaSHM5020_00_20_model->SetFillColorAlpha(kBlue-9,0.2);
  gr_PtRaaSHM5020_00_20_model->SetLineColor(kBlue-9);
  gr_PtRaaSHM5020_00_20_model->SetLineStyle(2);
 
  int ci1;
  ci1 = TColor::GetColor("#33ccff");
  gr_PtRaaSHM5020_00_10_model->SetFillColorAlpha(ci1,0.2);
  gr_PtRaaSHM5020_00_10_model->SetLineColor(ci1);
  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  c_temp->cd();
  gPad->SetTopMargin(0.02);
  gPad->SetRightMargin(0.03);
  gPad->SetBottomMargin(0.17);  
  gPad->SetLeftMargin(0.14);

  TH2F * mh2Dummy=new TH2F("mh2Dummy","",100,0,15,100,0.,2.5);
  mh2Dummy->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  mh2Dummy->GetYaxis()->SetTitle("#it{R}_{AA}");

  mh2Dummy->GetXaxis()->SetTitleSize(0.06);
  mh2Dummy->GetYaxis()->SetTitleSize(0.06);
  mh2Dummy->GetXaxis()->SetTitleOffset(1.2);
  mh2Dummy->GetYaxis()->SetTitleOffset(1.1);
  mh2Dummy->GetXaxis()->SetLabelSize(0.05);
  mh2Dummy->GetYaxis()->SetLabelSize(0.05);

  mh2Dummy->GetXaxis()->SetLabelOffset(0.02);
  mh2Dummy->GetYaxis()->SetLabelOffset(0.02);
  mh2Dummy->GetXaxis()->SetNdivisions(504);
  mh2Dummy->GetYaxis()->SetNdivisions(504);

 
  TBox *boxEle0010    = new TBox(14.3,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),14.7,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);

  TBox *boxEle3050    = new TBox(13.9,1.-NormUncert_Fw,14.3,1.+NormUncert_Fw);
  boxEle3050->SetFillColor(4);

  boxEle0010->Print("all");
  boxEle3050->Print("all");
  
  
  gr_PtRaaStat5020_00_10_midy->SetMarkerStyle(20);
  gr_PtRaaStat5020_00_10_midy->SetMarkerSize(2.8);
  gr_PtRaaStat5020_00_10_midy->SetMarkerColor(2);
  gr_PtRaaStat5020_00_10_midy->SetLineColor(2);
  gr_PtRaaStat5020_00_10_midy->SetLineWidth(2);

  gr_PtRaaSyst5020_00_10_midy->SetLineColor(2);
  gr_PtRaaSyst5020_00_10_midy->SetFillStyle(0);
  gr_PtRaaSyst5020_00_10_midy->SetLineWidth(2);


  gr_PtRaaStat5020_00_20_fwdy->SetMarkerStyle(20);
  gr_PtRaaStat5020_00_20_fwdy->SetMarkerSize(2.8);
  gr_PtRaaStat5020_00_20_fwdy->SetMarkerColor(4);
  gr_PtRaaStat5020_00_20_fwdy->SetLineColor(4);
  gr_PtRaaStat5020_00_20_fwdy->SetLineWidth(2);

  gr_PtRaaSyst5020_00_20_fwdy->SetLineColor(4);
  gr_PtRaaSyst5020_00_20_fwdy->SetFillStyle(0);
  gr_PtRaaSyst5020_00_20_fwdy->SetLineWidth(2);


  
  mh2Dummy->Draw();

  gr_PtRaaTM15020_00_10_model->Draw("FL same");
  gr_PtRaaSHM5020_00_10_model->Draw("FL same");

  gr_PtRaaTM15020_00_20_model ->Draw("FL same");
  gr_PtRaaSHM5020_00_20_model ->Draw("FL same");
  
  
  gr_PtRaaStat5020_00_10_midy->Draw("samePE");
  gr_PtRaaSyst5020_00_10_midy->Draw("sameE2");

  gr_PtRaaStat5020_00_20_fwdy->Draw("samePE");
  gr_PtRaaSyst5020_00_20_fwdy->Draw("sameE2");

  boxEle0010->Draw("sameE2");
  boxEle3050->Draw("sameE2");

  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");

  
  /* TLine *unity= (TLine *) GetUnitLine(); */
  /* unity ->Draw("same"); */

  TLegend *legend_mid = new TLegend(0.5,0.53,0.65,0.75);
  legend_mid->SetFillStyle(0);                                                                                                                                                                                                                                                                                        
  legend_mid->SetFillColor(0);
  legend_mid->SetLineColor(0);                                                                                                                                                                                                                                                                                        
  legend_mid->SetLineWidth(0);                                                                                                                                                                                                                                                                                        
  legend_mid->SetTextFont(22);                                                                                                                                                                                                                                                                                        
  legend_mid->SetTextSize(0.045);
  
  legend_mid->AddEntry(gr_PtRaaStat5020_00_10_midy,"Data 0-10%","p");
  legend_mid->AddEntry(gr_PtRaaTM15020_00_10_model,"TAMU","f");
  legend_mid->AddEntry(gr_PtRaaSHM5020_00_10_model,"SHM","f");

  TLegend *legend_fwdy = new TLegend(0.7,0.53,0.85,0.75);
  legend_fwdy->SetFillStyle(0);                                                                                                                                                                                                                                                                                        
  legend_fwdy->SetFillColor(0);
  legend_fwdy->SetLineColor(0);                                                                                                                                                                                                                                                                                        
  legend_fwdy->SetLineWidth(0);                                                                                                                                                                                                                                                                                        
  legend_fwdy->SetTextFont(22);                                                                                                                                                                                                                                                                                        
  legend_fwdy->SetTextSize(0.04);
  
  legend_fwdy->AddEntry(gr_PtRaaStat5020_00_20_fwdy,"Data 0-20%","p");
  legend_fwdy->AddEntry(gr_PtRaaTM15020_00_20_model,"TAMU","f");
  legend_fwdy->AddEntry(gr_PtRaaSHM5020_00_20_model,"SHM","f");

  legend_mid->Draw("same");
  legend_fwdy->Draw("same");


  TLatex tex0(0.65,0.75," ");
  tex0.SetTextSize(0.05);
  tex0.SetNDC();
  tex0.SetTextFont(22);
  tex0.DrawLatex(0.72,0.76,"2.5 < #it{y} < 4");

  TLatex tex1(0.65,0.75," ");
  tex1.SetTextSize(0.052);
  tex1.SetNDC();
  tex1.SetTextFont(22);
  tex1.DrawLatex(0.53,0.76,"|#it{y}| < 0.9");

  
  TLatex tex2(0.5,0.5," ");
  tex2.SetTextSize(0.05);
  tex2.SetNDC();
  tex2.SetTextFont(22);
  tex2.DrawLatex(0.27,0.9,"ALICE");
  tex2.SetTextSize(0.04);
  tex2.DrawLatex(0.27,0.84,"Pb#font[122]{-}Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex2.DrawLatex(0.27,0.78,"Inclusive J/#psi");

  
  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_pt_midy_fwdy_model.pdf");


  delete mh2Dummy;
  delete c_temp;

  // new calculation
  if(run_difference_option1)
    {

      const   int Npoints=3;
      
      Double_t RAA_mid[Npoints];
      Double_t RAA_mid_sts[Npoints];
      Double_t RAA_mid_sys[Npoints];

      Double_t RAA_fwd[Npoints];
      Double_t RAA_fwd_sts[Npoints];
      Double_t RAA_fwd_sys[Npoints];
      
      
      Double_t raatem_x=-999.;
      Double_t raatem_x_err=-999.;

      Double_t raatem_y=-999.;
      Double_t raatem_y_sts_err=-999.;
      Double_t raatem_y_sys_err=-999.;

      //      gr_PtRaaStat5020_00_20_fwdy->Print("all");
      for(int i=0;i<Npoints;i++)
	{

	  gr_PtRaaStat5020_00_10_midy->GetPoint(i,raatem_x,raatem_y);
      
	  raatem_y_sts_err=gr_PtRaaStat5020_00_10_midy->GetErrorY(i);
	  raatem_y_sys_err=gr_PtRaaSyst5020_00_10_midy->GetErrorY(i);
	  
	  RAA_mid[i]=raatem_y;
	  RAA_mid_sts[i]=raatem_y_sts_err;
	  RAA_mid_sys[i]=raatem_y_sys_err;

	  // fwdy
	  gr_PtRaaStat5020_00_20_fwdy->GetPoint(i,raatem_x,raatem_y);
      	  raatem_y_sts_err=gr_PtRaaStat5020_00_20_fwdy->GetErrorY(i);
	  raatem_y_sys_err=gr_PtRaaSyst5020_00_20_fwdy->GetErrorY(i);
	  
	  RAA_fwd[i]=raatem_y;
	  RAA_fwd_sts[i]=raatem_y_sts_err;
	  RAA_fwd_sys[i]=raatem_y_sys_err;
	  
	}	    

      Int_t opt = 2; //0: simple average; 1: N_jpsi 2: stat unc. weighting;  

      Double_t      meanRAA_mid=0.0;
      Double_t      meanRAA_mid_sts=0.0;
      Double_t       meanRAA_mid_sys=0.0;

      Double_t      meanRAA_fwd=0.0;
      Double_t      meanRAA_fwd_sts=0.0;
      Double_t      meanRAA_fwd_sys=0.0;

      Double_t      Weight_total_mid=0.0;
      Double_t      Weight_total_fwd=0.0;    

      Double_t Weight_mid[Npoints];
      Double_t Weight_fwd[Npoints];
	  
	  if(opt==0)
	    {
	      Weight_mid[0]=0.333;
	      Weight_mid[1]=0.333;
	      Weight_mid[2]=0.333;

	      Weight_fwd[0]=0.333;
	      Weight_fwd[1]=0.333;
	      Weight_fwd[2]=0.333;
	    }
	  
	  if(opt==1)
	    {
	      Weight_mid[0]=0.227;
	      Weight_mid[1]=0.44;
	      Weight_mid[2]=0.333;

	      Weight_fwd[0]=0.29;
	      Weight_fwd[1]=0.414;
	      Weight_fwd[2]=0.29;
	    }
	   
	   if(opt==2)
	    {
	      Weight_mid[0]=0.205;
	      Weight_mid[1]=0.426;
	      Weight_mid[2]=0.368;

	      Weight_fwd[0]=0.15;
	      Weight_fwd[1]=0.41;
	      Weight_fwd[2]=0.44;
	    }

	  
	  
	  for(int i=0;i<Npoints;i++)
	    {	
	      meanRAA_mid+=RAA_mid[i]*Weight_mid[i];	
	      meanRAA_mid_sts+=(RAA_mid_sts[i]*Weight_mid[i])*(RAA_mid_sts[i]*Weight_mid[i]);
	      meanRAA_mid_sys+=RAA_mid_sys[i]*Weight_mid[i];
	      
	      meanRAA_fwd+=RAA_fwd[i]*Weight_fwd[i];	

	      meanRAA_fwd_sts+=(RAA_fwd_sts[i]*Weight_fwd[i])*(RAA_fwd_sts[i]*Weight_fwd[i]);
	      meanRAA_fwd_sys+=(RAA_fwd_sys[i]*Weight_fwd[i])*(RAA_fwd_sys[i]*Weight_fwd[i]);

	      //    meanRAA_fwd_sys+=RAA_fwd_sys[i]*Weight_fwd[i];
	    }	  
	
	  meanRAA_mid_sts=sqrt(meanRAA_mid_sts);
	  meanRAA_fwd_sts=sqrt(meanRAA_fwd_sts);

	  Double_t pplumi = 2.07/100;//unc. in percent
	  Double_t global_mid=0.023;
	  Double_t global_fwd=0.04;

	  Double_t global_mid_new=sqrt(global_mid*global_mid-pplumi*pplumi);
	  Double_t global_fwd_new=sqrt(global_fwd*global_fwd-pplumi*pplumi);

	  Double_t global_mid_err=meanRAA_mid*global_mid_new;
	  Double_t global_fwd_err=meanRAA_fwd*global_fwd_new;
	  
	  
	  Double_t RAA_diff=abs(meanRAA_mid-meanRAA_fwd);
	  Double_t sigma=RAA_diff/sqrt(meanRAA_mid_sts*meanRAA_mid_sts+meanRAA_mid_sys*meanRAA_mid_sys
				       +meanRAA_fwd_sts*meanRAA_fwd_sts+meanRAA_fwd_sys*meanRAA_fwd_sys
				       +global_mid_err*global_mid_err
				       +global_fwd_err*global_fwd_err
				       );

	  cout<< "reweight option: "<< opt<<endl;
	  cout<< "RAA_mid: "<< " "<<meanRAA_mid<< "RAA_mid_sts: "<< meanRAA_mid_sts<< "RAA_mid_sys: "<< meanRAA_mid_sys<< " global_mid: "<< global_mid_err<<endl;
	  cout<< "RAA_fwd: "<< " "<<meanRAA_fwd<< "RAA_fwd_sts: "<< meanRAA_fwd_sts<< "RAA_fwd_sys: "<< meanRAA_fwd_sys<<" global_fwd: "<< global_fwd_err<<endl;

	  cout<< "Num_sigma " <<sigma<<endl;
      
    }
  
}

void plot_raa_pt_0_10_model_new()
{

  TGraphErrors *gr_PtRaaStat5020_00_10_midy = (TGraphErrors*)GetPtRaaStat5020_00_10_midy();
  TGraphErrors *gr_PtRaaSyst5020_00_10_midy  = (TGraphErrors*)GetPtRaaSyst5020_00_10_midy();

  TGraphErrors *gr_PtRaaStat5020_00_20_fwdy = (TGraphErrors*)GetPtRaaStat5020_00_20_fwdy();
  TGraphErrors *gr_PtRaaSyst5020_00_20_fwdy  = (TGraphErrors*)GetPtRaaSyst5020_00_20_fwdy();

  //read the model for midy
  TGraph * gr_PtRaaTM15020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileTAMU_pt_raa_0_10_midy_final);
  TGraph * gr_PtRaaTM25020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileTHUA_pt_raa_0_10_midy_final);
  TGraph * gr_PtRaaSHM5020_0_10_model=  (TGraph *) GetPtRaaTM15020_model(16,fileSHM_pt_raa_0_10_midy_final);
  TGraphAsymmErrors * gr_PtRaaEL5020_0_10_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEloss_pt_0_10_midy_final,"RAA_binned_centrality_0_10");

  //read the model for fwdy
  TGraph * gr_PtRaaTM15020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTAMU_pt_raa_0_20_fwdy_final );
  TGraph * gr_PtRaaTM25020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileTHUA_pt_raa_0_20_fwdy_final );
  TGraph * gr_PtRaaSHM5020_00_20_model=  (TGraph *) GetPtRaaTM15020_model(28,fileSHM_pt_raa_0_20_fwdy_final);
  TGraphAsymmErrors * gr_PtRaaEL5020_00_20_model=  (TGraphAsymmErrors *) GetPtRaaEnergyLoss5020_model(fileEloss_pt_0_20_fwdy_final,"RAA_binned_centrality_0_20_ForwardRap");

  /* gr_PtRaaTM15020_00_20_model->Draw(); */
  /* return; */
  
  
  
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



  //  int ci1;
  ci1 = TColor::GetColor("#33ccff");
 
  gr_PtRaaSHM5020_00_20_model->SetFillColorAlpha(kBlue-9,0.2);
  gr_PtRaaSHM5020_00_20_model->SetLineColor(kBlue-9);
  gr_PtRaaSHM5020_00_20_model->SetLineStyle(2);
  
 
  gr_PtRaaTM15020_00_20_model->SetFillColorAlpha(kRed-9,0.2);
  gr_PtRaaTM15020_00_20_model->SetLineColor(kRed-9);
  gr_PtRaaTM15020_00_20_model->SetLineStyle(2);
 
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
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.88,0.06,0.06,0.015,0.015,504,504);
  
  pad1->cd();
  /* TBox *boxEle0010    = new TBox(14.3,1.-NormUncert1,14.7,1.+NormUncert1); */
  /* boxEle0010->SetFillColor(kRed); */

  /* TBox *boxEle3050    = new TBox(14.3,1.-NormUncert3,14.7,1.+NormUncert3); */
  /* boxEle3050->SetFillColor(kRed); */


  SetTGraphError(gr_PtRaaStat5020_00_10_midy,20,2.5,2,2,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_10_midy,20,2.5,2,2,2,0);
  SetErrorX(gr_PtRaaSyst5020_00_10_midy,0.3);

  SetTGraphError(gr_PtRaaStat5020_00_20_fwdy ,20,2.5,4,4,2,0);
  SetTGraphError(gr_PtRaaSyst5020_00_20_fwdy,20,2.5,4,4,2,0);
  SetErrorX(gr_PtRaaSyst5020_00_20_fwdy,0.3);

  mh2Dummy->Draw();

  gr_PtRaaTM15020_0_10_model->Draw("FL same");
  /* //  gr_PtRaaTM25020_0_10_model->Draw("FL same"); */
  gr_PtRaaSHM5020_0_10_model->Draw("FL same");
  //  gr_PtRaaEL5020_0_10_model->Draw("same E2");

  //  gr_PtRaaTM15020_00_20_model
  gr_PtRaaTM15020_00_20_model->Draw("FL same");
  //  gr_PtRaaTM25020_00_20_model->Draw("FL same");
  //gr_PtRaaEL5020_00_20_model->Draw("same E2F");
  gr_PtRaaSHM5020_00_20_model->Draw("FL same");

  
  gr_PtRaaStat5020_00_10_midy->Draw("samePE");
  gr_PtRaaSyst5020_00_10_midy->Draw("sameE2");
  gr_PtRaaStat5020_00_20_fwdy->Draw("samePE");
  gr_PtRaaSyst5020_00_20_fwdy->Draw("sameE2");
  //  boxEle0010->Draw("sameE2");
    

  TBox *boxEle0010    = new TBox(19.2,1.-sqrt(NormUncert1*NormUncert1+common_un*common_un),19.77,1.+sqrt(NormUncert1*NormUncert1+common_un*common_un));
  boxEle0010->SetFillColor(kRed);


  
  TBox *boxEle3050    = new TBox(18.9,1.-NormUncert_Fw,19.3,1.+NormUncert_Fw);
  boxEle3050->SetFillColor(4);

  boxEle0010->Draw("same");
  boxEle3050->Draw("same");
  cout<< " relatative correlated uncertainties at mid 0-10% "<< sqrt(NormUncert1*NormUncert1+common_un*common_un)<<endl;
  cout<< " relatative correlated uncertainties at fwd 0-20% "<< NormUncert_Fw<<endl;

  
  TLine *line_unity= (TLine *)GetLine(0,1.0,20,1.0,1,2,7);
  line_unity  ->Draw("same");


  
  /* TLatex tex1(0.5,0.5," "); */
  /* tex1.SetTextFont(42); */
  /* tex1.SetTextSize(0.055); */
  /* tex1.SetNDC(); */
  /* tex1.DrawLatex(0.62,0.9,"ALICE"); */
  /* tex1.SetTextSize(0.047); */

  /* tex1.DrawLatex(0.5,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV"); */
  /* tex1.DrawLatex(0.5,0.77,"Inclusive J/#psi"); */

  /* TLegend *legend = new TLegend(0.5,0.6,0.85,0.75); */
  /* SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0); */

  TLatex tex0(0.65,0.75," ");
  tex0.SetTextSize(0.05);
  tex0.SetNDC();
  tex0.SetTextFont(22);
  tex0.DrawLatex(0.72,0.76,"2.5 < #it{y} < 4");

  TLatex tex1(0.65,0.75," ");
  tex1.SetTextSize(0.052);
  tex1.SetNDC();
  tex1.SetTextFont(22);
  tex1.DrawLatex(0.53,0.76,"|#it{y}| < 0.9");

  
  TLatex tex2(0.5,0.5," ");
  tex2.SetTextSize(0.05);
  tex2.SetNDC();
  tex2.SetTextFont(22);
  tex2.DrawLatex(0.2,0.9,"ALICE");
  tex2.SetTextSize(0.04);
  tex2.DrawLatex(0.2,0.84,"Pb#font[122]{-}Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex2.DrawLatex(0.2,0.78,"Inclusive J/#psi");
  

  TLegend *legend_mid = new TLegend(0.5,0.53,0.65,0.75);
  
  legend_mid->SetFillStyle(0);                                                                                                                                                                                                         
  legend_mid->SetFillColor(0);
  legend_mid->SetLineColor(0);                                                                                                                                                                                                         
  legend_mid->SetLineWidth(0);                                                                                                                                                                                                         
  legend_mid->SetTextFont(22);                                                                                                                                                                                                         
  legend_mid->SetTextSize(0.045);
  
  legend_mid->AddEntry(gr_PtRaaStat5020_00_10_midy,"Data 0-10%","p");
  legend_mid->AddEntry(gr_PtRaaTM15020_0_10_model,"TAMU","f");
  legend_mid->AddEntry(gr_PtRaaSHM5020_0_10_model,"SHM","f");


  TLegend *legend_fwdy = new TLegend(0.7,0.53,0.85,0.75);
  legend_fwdy->SetFillStyle(0);                                                                                                                                                                                                        
  legend_fwdy->SetFillColor(0);
  legend_fwdy->SetLineColor(0);                                                                                                                                                                                                        
  legend_fwdy->SetLineWidth(0);                                                                                                                                                                                                        
  legend_fwdy->SetTextFont(22);                                                                                                                                                                                                        
  legend_fwdy->SetTextSize(0.04);
  
  legend_fwdy->AddEntry(gr_PtRaaStat5020_00_20_fwdy,"Data 0-20%","p");
  legend_fwdy->AddEntry(gr_PtRaaTM15020_00_20_model,"TAMU","f");
  legend_fwdy->AddEntry(gr_PtRaaSHM5020_00_20_model,"SHM","f");
  
  /* TLegend *legend = new TLegend(0.48,0.6,0.7,0.75); */
  /* SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);   */
  /* legend->AddEntry( gr_PtRaaStat5020_00_10_midy,"0#font[122]{-}10%, |#it{y}| < 0.9","P"); */
  /* legend->AddEntry( gr_PtRaaStat5020_00_20_fwdy,"0#font[122]{-}20%, 2.5 < #it{y} < 4","P"); */
    
  /* legend->Draw(); */

  /* TFile *file=new TFile("Jpsi_RAA_Npart.root","UPDATE"); */
  /* file->cd(); */
  /* gr_PtRaaStat5020_00_10_midy->Write("gr_RaaPtStat5020_0_10_midy_data"); */
  /* gr_PtRaaSyst5020_00_10_midy->Write("gr_RaaPtSyst5020_0_10_midy_data"); */
  /* gr_PtRaaStat5020_00_20_fwdy->Write("gr_RaaPtStat5020_0_20_fwdy_data"); */
  /* gr_PtRaaSyst5020_00_20_fwdy->Write("gr_RaaPtSyst5020_0_20_fwdy_data"); */
 
  legend_mid->Draw("same");
  legend_fwdy->Draw("same");
  
  c_temp->SaveAs("output/Raa_Vs_pt_midy_fwdy_model_final.pdf");
 
  delete mh2Dummy;
  delete c_temp;

  
}

TGraphErrors *GetPtRaaStat5020_00_10_midy(){
  TH1F *PtRaaStat5020_00_10_midy = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sts_0_10");
  TGraphErrors* grPtRaaStat5020_00_10_midy=new TGraphErrors(PtRaaStat5020_00_10_midy);

  return grPtRaaStat5020_00_10_midy;
}

TGraphErrors *GetPtRaaSyst5020_00_10_midy(){
  TH1F *PtRaaSyst5020_00_10_midy = (TH1F *) final_results_pt_midy->Get("PbPb_raa_pt_sys_0_10");
  TGraphErrors* grPtRaaSyst5020_00_10_midy=new TGraphErrors(PtRaaSyst5020_00_10_midy);

  return grPtRaaSyst5020_00_10_midy;
}

TGraphErrors *GetPtRaaStat5020_00_20_fwdy(){

TGraphErrors* grAPtRaaStat5020_0_20= (TGraphErrors *) final_results_pt_fwdy ->Get("gr_RAA_centbin1");
  return grAPtRaaStat5020_0_20;

  

}
TGraphErrors *GetPtRaaSyst5020_00_20_fwdy(){

  TGraphErrors* grAPtRaaSyst5020_0_20= (TGraphErrors *) final_results_pt_fwdy ->Get("gr_RAA_syst_centbin1");
  return grAPtRaaSyst5020_0_20;  

}

TGraph *GetPtRaaTM15020_00_10_midy_model(){
  
  ifstream myfileTAMU (fileTAMU_pt_raa_0_10_midy);

  const int nTAMU = 76; // lines in the txt file
  double ptTAMU[nTAMU];
  double raaTAMUmax[nTAMU];
  double raaTAMUmin[nTAMU];
  double ptT = 0.;
  double raaMinT = 0.;
  double raaMaxT = 0.;
  
  int iTAMU = 0; // counter

  while(myfileTAMU>>ptT>>raaMinT>>raaMaxT){
    ptTAMU[iTAMU]     = ptT;
    raaTAMUmin[iTAMU] = raaMinT;
    raaTAMUmax[iTAMU] = raaMaxT;
    
    iTAMU++;
  }

  TGraph *graaTAMUmin = new TGraph(nTAMU,ptTAMU,raaTAMUmin);
  TGraph *graaTAMUmax = new TGraph(nTAMU,ptTAMU,raaTAMUmax);
  
  TGraph *graaTAMU = new TGraph(2*nTAMU);
  for(int i=0 ; i<nTAMU ; i++){
    graaTAMU->SetPoint(i,graaTAMUmax->GetX()[i],graaTAMUmax->GetY()[i]);
    graaTAMU->SetPoint(nTAMU+i,graaTAMUmax->GetX()[nTAMU-i-1],graaTAMUmin->GetY()[nTAMU-i-1]);
  }

  return graaTAMU;
} 

TGraph *GetPtRaaSHM5020_00_10_midy_model(){
  
  ifstream myfileSHM (fileSHM_pt_raa_0_10_midy);

  const int nSHM = 100; // lines in the txt file
  double ptSHM[nSHM];
  double raaSHMmax[nSHM];
  double raaSHMmin[nSHM];
  double ptS = 0.;
  double raaMinS = 0.;
  double raaMaxS = 0.;
  double dummy1  = 0.;
  double dummy2  = 0.;


  int iSHM = 0; // counter
  while(myfileSHM>>ptS>>dummy1>>dummy2>>raaMinS>>raaMaxS){
    ptSHM[iSHM]     = ptS;
    raaSHMmin[iSHM] = raaMinS;
    raaSHMmax[iSHM] = raaMaxS;
    iSHM++;
    //  cout<< " "<<raaMinS<<endl;
  }

  TGraph *graaSHMmin = new TGraph(nSHM,ptSHM,raaSHMmin);
  TGraph *graaSHMmax = new TGraph(nSHM,ptSHM,raaSHMmax);
  
  TGraph *graaSHM = new TGraph(2*nSHM);
  for(int i=0 ; i<nSHM ; i++){
    graaSHM->SetPoint(i,graaSHMmax->GetX()[i],graaSHMmax->GetY()[i]);
    graaSHM->SetPoint(nSHM+i,graaSHMmax->GetX()[nSHM-i-1],graaSHMmin->GetY()[nSHM-i-1]);
  }
  return graaSHM;
}

TGraph *GetPtRaaTM15020_00_20_fwdy_model(){
  
  ifstream myfileTAMU (fileTAMU_pt_raa_0_10_fwdy);

  const int nTAMU = 100; // lines in the txt file
  double ptTAMU[nTAMU];
  double raaTAMUmax[nTAMU];
  double raaTAMUmin[nTAMU];
  double ptT = 0.;
  double raaMinT = 0.;
  double raaMaxT = 0.;
  
  int iTAMU = 0; // counter

  while(myfileTAMU>>ptT>>raaMinT>>raaMaxT){
    ptTAMU[iTAMU]     = ptT;
    raaTAMUmin[iTAMU] = raaMinT;
    raaTAMUmax[iTAMU] = raaMaxT;
    
    iTAMU++;
  }

  TGraph *graaTAMUmin = new TGraph(nTAMU,ptTAMU,raaTAMUmin);
  TGraph *graaTAMUmax = new TGraph(nTAMU,ptTAMU,raaTAMUmax);
  
  TGraph *graaTAMU = new TGraph(2*nTAMU);
  for(int i=0 ; i<nTAMU ; i++){
    graaTAMU->SetPoint(i,graaTAMUmax->GetX()[i],graaTAMUmax->GetY()[i]);
    graaTAMU->SetPoint(nTAMU+i,graaTAMUmax->GetX()[nTAMU-i-1],graaTAMUmin->GetY()[nTAMU-i-1]);
  }

  return graaTAMU;
} 

TGraph *GetPtRaaSHM5020_00_20_fwdy_model(){
  
  ifstream myfileSHM (fileSHM_pt_raa_0_10_fwdy);

  const int nSHM = 100; // lines in the txt file
  double ptSHM[nSHM];
  double raaSHMmax[nSHM];
  double raaSHMmin[nSHM];
  double ptS = 0.;
  double raaMinS = 0.;
  double raaMaxS = 0.;
  double dummy1  = 0.;
  double dummy2  = 0.;


  int iSHM = 0; // counter
  while(myfileSHM>>ptS>>dummy1>>dummy2>>raaMinS>>raaMaxS){
    ptSHM[iSHM]     = ptS;
    raaSHMmin[iSHM] = raaMinS;
    raaSHMmax[iSHM] = raaMaxS;
    iSHM++;
    //  cout<< " "<<raaMinS<<endl;
  }

  TGraph *graaSHMmin = new TGraph(nSHM,ptSHM,raaSHMmin);
  TGraph *graaSHMmax = new TGraph(nSHM,ptSHM,raaSHMmax);
  
  TGraph *graaSHM = new TGraph(2*nSHM);
  for(int i=0 ; i<nSHM ; i++){
    graaSHM->SetPoint(i,graaSHMmax->GetX()[i],graaSHMmax->GetY()[i]);
    graaSHM->SetPoint(nSHM+i,graaSHMmax->GetX()[nSHM-i-1],graaSHMmin->GetY()[nSHM-i-1]);
  }


  return graaSHM;
} 



/* inline TLine *GetUnitLine(){ */

/*   TLine *unity= new TLine(0.0,1.0,15.0,1.0); */
/*   unity->SetLineColor(1); */
/*   unity->SetLineWidth(2); */
/*   unity->SetLineStyle(7); */

/*   return unity; */
/* } */
