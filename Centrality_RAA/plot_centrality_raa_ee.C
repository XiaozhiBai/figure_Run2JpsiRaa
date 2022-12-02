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

double common_uncertainty_fwdy=0.078;

//sqrt(0.039*0.039+0.058*0.058+0.021*0.021+0.01*0.01)

//pp from sts, sys, lumi, Jpis BR



char buf[1024];

void plot_raa_cent_model();
void plot_raa_cent_data();
TGraphErrors* GetCentRaa_5020_data_sts(int, const char *);
TGraphErrors* GetCentRaa_5020_data_sys(int, const char *);

//bool 
double NormUncert1   = 0.0072; // 0-10  %
double NormUncert2   = 0.0069; // 10-30 %
double NormUncert3   = 0.012; // 30-50 %
double NormUncert_Fw = 0.040; // 0-20  %


inline TGraphErrors *GetCentRaaStat5020();
inline TGraphErrors *GetCentRaaSyst5020();



inline TGraph *GetCentRaaTM15020_model();
inline TGraph *GetCentRaaTM25020_model();
inline TGraph *GetCentRaaSHM5020_model();
inline TGraph *GetCentRaaComv020_model();

TFile *final_results_cent_midy;
const char *final_results_cent_fwdy;

const char *fileTAMU_cent_raa;
const char *fileQinghua_cent_raa;
const char *fileSHM_cent_raa;
const char *fileComover_cent_raa;

bool comput_difference=false;
bool comput_increasing=false;
void plot_centrality_raa_ee()
{

  SetStyle();

  final_results_cent_midy=new TFile("input/data/results_centrality.root","READ");
  final_results_cent_fwdy= "input/data/Raa_vs_centrality_fwd_fig4.txt";

  fileTAMU_cent_raa = "../models/Ralf_Rapp/data/TAMU_5020_cent_RAA_mid.txt";
  fileQinghua_cent_raa = "../models/PengfeiTM2/fig--central-rapidity-2022/RAA-Np-2022Jan5/theory-RAA-Np.dat";
  fileComover_cent_raa = "input/models/comover_5020_midy.txt";
  //  fileSHM_cent_raa = "input/models/SHM_CentDep_PbPb5020_midy_11012019.txt";
  fileSHM_cent_raa = "../models/SHMc/gRaaSHMc_midy_RAA_Npart.txt";    

  plot_raa_cent_model();
  plot_raa_cent_data();
}

void plot_raa_cent_model(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetCentRaaStat5020();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetCentRaaSyst5020();

  TGraph * gr_CentRaaTM15020_model=  (TGraph *)GetCentRaaTM1_5020_model(29,fileTAMU_cent_raa);
  TGraph * gr_CentRaaTM25020_model=  (TGraph *)GetCentRaaTM2_5020_model(26,fileQinghua_cent_raa);
  TGraph * gr_CentRaaSHM5020_model=  (TGraph *)GetCentRaaSHM_5020_model(40,fileSHM_cent_raa);
  TGraph * gr_CentRaaComv5020_model=  (TGraph *)GetCentRaaComv020_model(14,fileComover_cent_raa);  

  int ci1;
  ci1 = TColor::GetColor("#33ccff");

  gr_CentRaaSHM5020_model->SetFillColorAlpha(ci1,0.15);
  gr_CentRaaSHM5020_model->SetLineColor(ci1);

  gr_CentRaaComv5020_model ->SetFillColorAlpha(kGreen,0.15);
  gr_CentRaaComv5020_model ->SetLineColor(kGreen);

  gr_CentRaaTM15020_model  ->SetFillColorAlpha(kOrange+1,0.2);
  gr_CentRaaTM15020_model ->SetLineColor(kOrange+1);
  
  gr_CentRaaTM25020_model->SetFillColorAlpha(kBlue,0.15);
  gr_CentRaaTM25020_model->SetLineColor(kBlue);

  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.17,0.13,0.035);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#LT_{ }#it{N}_{part}_{ }#GT;#it{R}_{AA}",100,0,400,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.8,0.06,0.06,0.015,0.015,504,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  SetErrorX(gr_CentRaaSyst5020,6);
  
  pad1->cd();
  mh2Dummy->Draw();
  gr_CentRaaTM15020_model->Draw("FL same");
  gr_CentRaaSHM5020_model->Draw("FL same");
  gr_CentRaaTM25020_model->Draw("FL same");
  
  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  box_comm ->Draw("sameE2");

  box_comm->Print("all");
    
  TLine *line_unity= (TLine *)GetLine(0,1.0,400,1.0,1,2,7);
  line_unity  ->Draw("same");
  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.280,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.18,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi, |#it{y}|<0.9");
  tex1.DrawLatex(0.18,0.70,"#it{p}_{T} > 0.15 GeV/#it{c}");
  
  TLegend  *legend= new TLegend(0.52,0.7,0.82,0.92);
  SetLegend(legend,42,0.044,0.0,0.0,0.0,0.0);
  
  legend->AddEntry( gr_CentRaaStat5020,lg_data,"P");
  legend->AddEntry(gr_CentRaaTM15020_model,lg_TM1,"f");
  legend->AddEntry(gr_CentRaaTM25020_model,lg_TM2,"f");
  legend->AddEntry(gr_CentRaaSHM5020_model,lg_SHM,"f");
  
  legend->Draw();

  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_cent_015_model.pdf");
  c_temp->SaveAs("output/Raa_Vs_cent_015_model.png");


  TFile *file=new TFile("Jpsi_RAA_Npart.root","RECREATE");

  file->cd();
  gr_CentRaaTM15020_model->Write("gr_RaaNpart_Ralf_Papp_midy_model");
  gr_CentRaaSHM5020_model->Write("gr_RaaNpart_SHM_midy_model");
  gr_CentRaaTM25020_model->Write("gr_RaaNpart_Pengfei_midy_model");
  
  gr_CentRaaStat5020->Write("gr_RaaNpart_stat_midy_data");
  gr_CentRaaSyst5020->Write("gr_RaaNpart_syst_midy_data");
  
  delete mh2Dummy;
  delete c_temp;
}

void plot_raa_cent_data(){

  TGraphErrors *gr_CentRaaStat5020 = (TGraphErrors*)GetCentRaaStat5020();
  TGraphErrors *gr_CentRaaSyst5020  = (TGraphErrors*)GetCentRaaSyst5020();

  TGraphErrors *gr_CentRaaStat5020_fwd=(TGraphErrors *)GetCentRaa_5020_data_sts(9,final_results_cent_fwdy);
  TGraphErrors *gr_CentRaaSyst5020_fwd=(TGraphErrors *)GetCentRaa_5020_data_sys(9,final_results_cent_fwdy);
  

  
  TCanvas *c_temp=new TCanvas("c_temp","",1200,900);
  TPad *pad1 = new TPad("pad1", "", 0, 0, 1, 1);

  SetPad(pad1,0.02,0.17,0.14,0.035);
  c_temp->cd();
  pad1->Draw();

  TH2F * mh2Dummy=new TH2F("mh2Dummy",";#LT_{ }#it{N}_{part}_{ }#GT;#it{R}_{AA}",100,0,410,100,0.,2.2);
  SetTH2F(mh2Dummy,0.07,0.07,1.1,0.85,0.06,0.06,0.015,0.015,504,504);

  
  TBox *box_comm    = new TBox(392,1.-common_uncertainty,400,1.+common_uncertainty);
  box_comm ->SetFillColor(kRed);

  TBox *box_fwdy    = new TBox(400,1.-common_uncertainty_fwdy,408,1.+common_uncertainty_fwdy);
  box_fwdy ->SetFillColor(kBlue);

  SetTGraphError(gr_CentRaaStat5020,20,2.5,2,2,2,0);
  SetTGraphError(gr_CentRaaSyst5020,20,2.5,2,2,2,0);

  
  /* SetTGraphError(gr_CentRaaStat5020,20,2,2,2,2,0); */
  /* SetTGraphError(gr_CentRaaSyst5020,20,2,2,2,2,0); */
  SetErrorX(gr_CentRaaSyst5020,6);

  SetTGraphError(gr_CentRaaStat5020_fwd,20,2.5,4,4,2,0);
  SetTGraphError(gr_CentRaaSyst5020_fwd,20,2.5,4,4,2,0);
  SetErrorX(gr_CentRaaSyst5020_fwd,6);

  
  pad1->cd();
  mh2Dummy->Draw();

  gr_CentRaaStat5020_fwd->Draw("samePE");
  gr_CentRaaSyst5020_fwd->Draw("sameE2");

  gr_CentRaaStat5020->Draw("samePE");
  gr_CentRaaSyst5020->Draw("sameE2");

  
  
  if(comput_increasing)
    {

  for(int i=0;i<8;i++)
        {

	  Double_t  raa_mid=0.0;
	  Double_t  raa_mid_err=0.0;
      
	  Double_t  raa_mid_tem_x=0.0;
	  Double_t  raa_mid_tem_y=0.0;
 
	  Double_t  raa_mid_tem_sts_err=0.0;
	  Double_t  raa_mid_tem_sys_err=0.0;

	  Double_t total_uncer=0.0;
	  
          gr_CentRaaStat5020->GetPoint(i,raa_mid_tem_x,raa_mid_tem_y);
      
          raa_mid_tem_sts_err=gr_CentRaaStat5020->GetErrorY(i);
          raa_mid_tem_sys_err=gr_CentRaaSyst5020->GetErrorY(i);

	  gr_CentRaaStat5020->SetPointError(i,0.0,sqrt(raa_mid_tem_sts_err*raa_mid_tem_sts_err+raa_mid_tem_sys_err*raa_mid_tem_sys_err));
          /* //      cout<< " "<<i <<" "<<raa_mid_tem_x<< "  "<<raa_mid_tem_y<< " sts."<< raa_mid_tem_x_err<<endl; */
	  /* //   raa_mid+=raa_mid_tem_y; */
 
 
          /* raa_mid_err +=raa_mid_tem_sts_err *raa_mid_tem_sts_err; */
          /* raa_mid_err +=raa_mid_tem_sys_err *raa_mid_tem_sys_err; */
 
          /* cout<< "raa_mid"<< raa_mid<< " raa_mid_err" << raa_mid_err<<endl; */
 
	}

  //  gr_CentRaaStat5020->Fit("pol0","","",120,400);
  
    }
    
  if(comput_difference)
    {


      cout<< " mwdy stst."<<endl;
      gr_CentRaaStat5020->Print("all"); 
      cout<< " mwdy sys."<<endl;
      gr_CentRaaSyst5020->Print("all"); 

      cout<< " fwdy stat"<<endl;
     gr_CentRaaStat5020_fwd->Print("all"); 
      cout<< " fwdy syst."<<endl;
      gr_CentRaaSyst5020_fwd->Print("all"); 


      Double_t  raa_mid=0.0;
      Double_t  raa_mid_err=0.0;
      
      Double_t  raa_mid_tem_x=0.0;
      Double_t  raa_mid_tem_y=0.0;
 
      Double_t  raa_mid_tem_sts_err=0.0;
      Double_t  raa_mid_tem_sys_err=0.0;
 
      Double_t  raa_fwd=0.0;
      Double_t  raa_fwd_err=0.0;
      
      Double_t  raa_fwd_tem_x=0.0;
      Double_t  raa_fwd_tem_y=0.0;
 
      Double_t  raa_fwd_tem_sts_err=0.0;
      Double_t  raa_fwd_tem_sys_err=0.0;
      
 
      
      for(int i=3;i<8;i++)
        {
	  Double_t TAA[8][2]={{26.08,0.176},{20.44,0.166},{14.4,0.126},{8.767,0.101},{5.086,0.0814},{2.747,0.04786},{0.9755,0.0233},{0.1611,0.00365}};

          gr_CentRaaStat5020->GetPoint(i,raa_mid_tem_x,raa_mid_tem_y);
      
          raa_mid_tem_sts_err=gr_CentRaaStat5020->GetErrorY(i);
          raa_mid_tem_sys_err=gr_CentRaaSyst5020->GetErrorY(i);

	  //	  raa_mid_tem_sys_err
	  //	  cout<< " XXXX"<<i <<" "<<raa_mid_tem_x<< "  "<<raa_mid_tem_sts_err<< " sts."<< raa_mid_tem_sts_err<< " "<<TAA[i][0]<<" "<<TAA[i][1]<<" "<<raa_mid_tem_y<<endl;
	  raa_mid_tem_sys_err=sqrt(raa_mid_tem_sys_err*raa_mid_tem_sys_err-(TAA[i][1]/TAA[i][0]*raa_mid_tem_y)*(TAA[i][1]/TAA[i][0]*raa_mid_tem_y)); //remove the TAA from mid;
	    
	    raa_mid+=raa_mid_tem_y;
 
 
          raa_mid_err +=raa_mid_tem_sts_err *raa_mid_tem_sts_err;
          raa_mid_err +=raa_mid_tem_sys_err *raa_mid_tem_sys_err;
 
          cout<< "raa_mid"<< raa_mid<< " raa_mid_err" << raa_mid_err<<endl;
 
	}

      for(int i=0;i<4;i++)
        {
	  Double_t TAA[9][2]={{23.4,0.78},{14.3,0.46},{8.59,0.27},{4.92,0.16},{2.61,0.1},{1.28,0.063},{0.569,0.032},{0.232,0.015},{0.0923,0.007}};
          // fwdy 
         gr_CentRaaStat5020_fwd->GetPoint(i,raa_fwd_tem_x,raa_fwd_tem_y);
      
          raa_fwd_tem_sts_err=gr_CentRaaStat5020_fwd->GetErrorY(i);
          raa_fwd_tem_sys_err=gr_CentRaaSyst5020_fwd->GetErrorY(i);
          
	  cout<< " XXX "<<i <<" "<<raa_fwd_tem_x<< "  "<<raa_fwd_tem_y<< " sts."<<endl;
	  raa_mid_tem_sys_err=sqrt(raa_mid_tem_sys_err*raa_mid_tem_sys_err-(TAA[i][1]/TAA[i][0]*raa_mid_tem_y)*(TAA[i][1]/TAA[i][0]*raa_mid_tem_y)); //remove the TAA from mid;
	  raa_fwd+=raa_fwd_tem_y;
 
 
          raa_fwd_err +=raa_fwd_tem_sts_err *raa_fwd_tem_sts_err;
          raa_fwd_err +=raa_fwd_tem_sys_err *raa_fwd_tem_sys_err;
 
          cout<< "raa_fwd"<< raa_fwd<< " raa_fwd_err" << raa_fwd_err<<endl;

	  //      cout<< " "<<i <<" "<<raa_fwd_tem_x<< "  "<<raa_fwd_tem_y<< " sts."<< raa_fwd_tem_x_err<<endl;
          raa_fwd+=raa_fwd_tem_y;
 
 
          raa_fwd_err +=raa_fwd_tem_sts_err *raa_fwd_tem_sts_err;
          raa_fwd_err +=raa_fwd_tem_sys_err *raa_fwd_tem_sys_err;
 
	  //    cout<< "raa_fwd"<< raa_fwd<< " raa_fwd_err" << raa_fwd_err<<endl;
          
          
          
        }       
 
      /* cout<<" XXX difference"<<endl; */
 
      raa_mid/=5.;
      raa_mid_err/=25;

      raa_fwd/=4.;
      raa_fwd_err/=16;
      
      
	
      /* raa_fwd/=3.; */
 
      /* cout<< "mid"<<  raa_mid<< " fwd"<< raa_fwd<<endl; */
      Double_t diff= abs(raa_fwd-raa_mid);
      /* //      diff/=3.; */
      Double_t err=raa_fwd_err+raa_mid_err;
      /* err/=9.0; */
 
      err+=(0.07*raa_mid*0.07*raa_mid)+(0.07*raa_fwd*0.07*raa_fwd);
      err=sqrt(err);
 
      cout<< "diff "<<diff<< "  "<<err<< " "<< diff/err<<endl;
      
      // }



  
    }
  /* if(comput_difference) */
  /*   { */


  /*     //      gr_CentRaaStat5020_fwd->Fit("pol0","R","same",290,400); */
  /*     /\* gr_CentRaaSyst5020->Fit("pol0","R","same",290,400); *\/ */

      
  /*     TGraphErrors*  tem_sts_sys_gr_CentRaaStat5020_fwd=(TGraphErrors*) gr_CentRaaStat5020_fwd->Clone("tem_sts_sys_gr_CentRaaStat5020_fwd"); */
  /*     TGraphErrors*  tem_sts_sys_gr_CentRaaSyst5020_fwd=(TGraphErrors*) gr_CentRaaSyst5020_fwd->Clone("tem_sts_sys_gr_CentRaaSyst5020_fwd"); */
      
  /*     TGraphErrors*  tem_sts_sys_gr_CentRaaStat5020=(TGraphErrors*) gr_CentRaaStat5020->Clone("tem_sts_sys_gr_CentRaaStat5020"); */
  /*     TGraphErrors*  tem_sts_sys_gr_CentRaaSyst5020=(TGraphErrors*) gr_CentRaaSyst5020->Clone("tem_sts_sys_gr_CentRaaSyst5020"); */
      


  /*     for(int ipoint=0;ipoint<tem_sts_sys_gr_CentRaaStat5020_fwd->GetN();ipoint++) */
  /* 	{ */
  /* 	  double temp_x=-999.; */
  /* 	  double temp_y=-999.; */

  /* 	  double temp_x_err=-999.; */
  /* 	  double temp_y_err_sts=-999.; */
  /* 	  double temp_y_err_sys=-999.; */

  /* 	  tem_sts_sys_gr_CentRaaStat5020_fwd->GetPoint(ipoint,temp_x,temp_y); */

  /* 	  temp_y_err_sts = tem_sts_sys_gr_CentRaaStat5020_fwd->GetErrorX(ipoint); */
  /* 	  temp_y_err_sys= gr_CentRaaSyst5020_fwd->GetErrorY(ipoint); */

  /* 	  tem_sts_sys_gr_CentRaaStat5020_fwd->SetPointError(ipoint,temp_x_err,sqrt(temp_y_err_sts*temp_y_err_sts+temp_y_err_sys*temp_y_err_sys)); */

  /* 	} */
  /*     cout<< "forward rapidity fit:  "<<endl; */
  /*     /\* tem_sts_sys_gr_CentRaaStat5020_fwd->Fit("pol0","R","",290,400); *\/ */
  /*     /\* tem_sts_sys_gr_CentRaaStat5020_fwd->Draw("samePE"); *\/ */
  /*     // midy */

  /*     //      gr_CentRaaStat5020->Fit("pol0","R","same",290,400); */

  /*     //tem_sts_sys_gr_CentRaaStat5020_fwd->Print("all"); */
      
  /*     for(int ipoint=0;ipoint<tem_sts_sys_gr_CentRaaStat5020->GetN();ipoint++) */
  /* 	{ */
  /* 	  double temp_x=-999.; */
  /* 	  double temp_y=-999.; */

  /* 	  double temp_x_err=-999.; */
  /* 	  double temp_y_err_sts=-999.; */
  /* 	  double temp_y_err_sys=-999.; */

  /* 	  tem_sts_sys_gr_CentRaaStat5020->GetPoint(ipoint,temp_x,temp_y); */

  /* 	  temp_y_err_sts =gr_CentRaaStat5020->GetErrorX(ipoint); */
  /* 	  temp_y_err_sys= gr_CentRaaSyst5020->GetErrorY(ipoint); */
  /* 	  tem_sts_sys_gr_CentRaaStat5020->SetPointError(ipoint,temp_x_err,sqrt(temp_y_err_sts*temp_y_err_sts+temp_y_err_sys*temp_y_err_sys)); */
  /* 	} */
  /*      cout<< "mid rapidity fit:  "<<endl; */
  /*     gr_CentRaaStat5020->Fit("pol0","R","",290,400); */
  /*     //      tem_sts_sys_gr_CentRaaStat5020->Draw("samePE"); */
  /*     //      temp_y_err_sts->print("all"); */
  /*     gr_CentRaaSyst5020->Print("all"); */
  /*     //      gr_CentRaaStat5020->Print("all"); */
  /*     cout<<"XXX"<<endl; */
  /*     gr_CentRaaSyst5020->Print("all"); */
  /*   } */


  

  

  
  box_comm ->Draw("sameE2");
  box_fwdy ->Draw("sameE2");
  
    
  TLine *line_unity= (TLine *)GetLine(0,1.0,400,1.0,1,2,7);
  line_unity  ->Draw("same");


  
  TLatex tex1(0.5,0.5," ");
  tex1.SetTextFont(42);
  tex1.SetTextSize(0.055);
  tex1.SetNDC();
  tex1.DrawLatex(0.280,0.9,"ALICE");
  tex1.SetTextSize(0.047);

  
  tex1.DrawLatex(0.18,0.84,"Pb#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex1.DrawLatex(0.18,0.77,"Inclusive J/#psi");
  //  tex1.DrawLatex(0.18,0.70,"#it{p}_{T} > 0.15 GeV/#it{c}");
  
  TLegend  *legend= new TLegend(0.4,0.6,0.8,0.75);
  SetLegend(legend,42,0.045,0.0,0.0,0.0,0.0);
  

  legend->AddEntry( gr_CentRaaStat5020,"|y| < 0.9 (0.15 < #it{p}_{T} < 15 GeV/#it{c})","P");
  legend->AddEntry( gr_CentRaaStat5020_fwd,"2.5 < y < 4 (0.3 < #it{p}_{T} < 8 GeV/#it{c})","P");
  
  legend->Draw();

  gPad->RedrawAxis();
  c_temp->SaveAs("output/Raa_Vs_cent_015_data.pdf");
  c_temp->SaveAs("output/Raa_Vs_cent_015_data.png");
  delete mh2Dummy;
  delete c_temp;
}

TGraphErrors *GetCentRaaStat5020(){

  TGraphErrors* grCentRaaStat5020=(TGraphErrors*) final_results_cent_midy ->Get("gr_PbPb_Raa_N_part_sts");
  return grCentRaaStat5020;
}

TGraphErrors *GetCentRaaSyst5020(){

  TGraphErrors* grCentRaaSyst5020=(TGraphErrors*) final_results_cent_midy ->Get("gr_PbPb_Raa_N_part_sys");
  return grCentRaaSyst5020;
}

TGraphErrors* GetCentRaa_5020_data_sts(Int_t Npoint, const  char * input)
{
  ifstream myfiledata(input);
  const int ndata_sts = Npoint; // lines in the txt file

  double npart[ndata_sts];
  double raa[ndata_sts];
  double raa_sts[ndata_sts];
  double raa_sys_corr[ndata_sts];
  double raa_sys_uncorr[ndata_sts];
  double dummyErr_x[ndata_sts];

  double npart_temp = 0.;
  double raa_temp = 0.;
  double raa_sts_temp = 0.;
  double raa_sys_corr_temp = 0.;
  double raa_sys_uncorr_temp = 0.;

  
  int idata = 0; // counter

  while(myfiledata>>npart_temp >>raa_temp>> raa_sts_temp >> raa_sys_uncorr_temp >> raa_sys_corr_temp){
    
    npart[idata]     = npart_temp;
    raa[idata] = raa_temp;
    raa_sts[idata] = raa_sts_temp;
    dummyErr_x[idata]=0.0;
    idata++;
  }
  TGraphErrors *graadata_sts = new TGraphErrors(ndata_sts, npart, raa, dummyErr_x, raa_sts);
  return graadata_sts;
  

}

TGraphErrors* GetCentRaa_5020_data_sys(Int_t Npoint, const  char * input)
{
  ifstream myfiledata(input);
  const int ndata_sys = Npoint; // lines in the txt file

  double npart[ndata_sys];
  double raa[ndata_sys];
  double raa_sts[ndata_sys];
  double raa_sys[ndata_sys];

  double raa_sys_corr[ndata_sys];
  double raa_sys_uncorr[ndata_sys];
  double dummyErr_x[ndata_sys];

  double npart_temp = 0.;
  double raa_temp = 0.;
  double raa_sts_temp = 0.;
  double raa_sys_corr_temp = 0.;
  double raa_sys_uncorr_temp = 0.;

  
  int idata = 0; // counter

  while(myfiledata>>npart_temp >>raa_temp>> raa_sts_temp >> raa_sys_uncorr_temp >> raa_sys_corr_temp){

    npart[idata]     = npart_temp;
    raa[idata] = raa_temp;
    raa_sys[idata] = sqrt(raa_sys_uncorr_temp*raa_sys_uncorr_temp+raa_sys_corr_temp*raa_sys_corr_temp);
    dummyErr_x[idata]=0.0;
    raa_sys_uncorr[idata]=raa_sys_uncorr_temp;
    idata++;
  }

  TGraphErrors *graadata_sys = new TGraphErrors(ndata_sys, npart, raa, dummyErr_x,raa_sys_uncorr);
  return graadata_sys;
  

}
