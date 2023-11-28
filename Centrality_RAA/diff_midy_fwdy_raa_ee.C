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

bool comput_difference=true;
bool comput_increasing=false;
void diff_midy_fwdy_raa_ee()
{

  SetStyle();

  final_results_cent_midy=new TFile("input/data/results_centrality.root","READ");
  final_results_cent_fwdy= "input/data/Raa_vs_centrality_fwd_fig4.txt";
  plot_raa_cent_data();
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
      
      int Npoint_mid=2;
      Double_t weight_mid[Npoint_mid];

      int Npoint_fwd=1;
      Double_t weight_fwd[Npoint_fwd];
      
      Double_t weight_mid_all=0.0;
      
      //      Double_t weight_mid=0.0;

      Double_t weight_fwd_all=0.0;
      //Double_t weight_mid=0.0;
      Double_t TAA_old_fwd[9][2]={{23.4,0.78},{14.3,0.46},{8.59,0.27},{4.92,0.16},{2.61,0.1},{1.28,0.063},{0.569,0.032},{0.232,0.015},{0.0923,0.007}};
      Double_t TAA_mid[8][2]={{26.08,0.176},{20.44,0.166},{14.4,0.126},{8.767,0.101},{5.086,0.0814},{2.747,0.04786},{0.9755,0.0233},{0.1611,0.00365}};
	  
      for(int i=8-Npoint_mid;i<8;i++)
        {
          gr_CentRaaStat5020->GetPoint(i,raa_mid_tem_x,raa_mid_tem_y);
      
          raa_mid_tem_sts_err=gr_CentRaaStat5020->GetErrorY(i);
          raa_mid_tem_sys_err=gr_CentRaaSyst5020->GetErrorY(i);


	  Double_t relative_sts=raa_mid_tem_sts_err/raa_mid_tem_y;
	  weight_mid_all+=1./(relative_sts*relative_sts);
 
	}

      Double_t Average_RAA_mid=0.0;
      Double_t Average_RAA_mid_sts=0.0;
      Double_t Average_RAA_mid_sys=0.0;
      
      for(int i=8-Npoint_mid;i<8;i++)                                                                                                                                                                                                                                                                                          
        {

	  gr_CentRaaStat5020->GetPoint(i,raa_mid_tem_x,raa_mid_tem_y);
          raa_mid_tem_sts_err=gr_CentRaaStat5020->GetErrorY(i);
          raa_mid_tem_sys_err=gr_CentRaaSyst5020->GetErrorY(i);

	  raa_mid_tem_sys_err=sqrt(raa_mid_tem_sys_err*raa_mid_tem_sys_err-(TAA_mid[i][1]/TAA_mid[i][0]*raa_mid_tem_y)*(TAA_mid[i][1]/TAA_mid[i][0]*raa_mid_tem_y)); //remove the TAA from mid;
 
	  Double_t relative_sts=raa_mid_tem_sts_err/raa_mid_tem_y;
	  Double_t weight=1./(relative_sts*relative_sts)/weight_mid_all;
	  
	  
	  Average_RAA_mid += raa_mid_tem_y*weight;
	  Average_RAA_mid_sys += raa_mid_tem_sys_err*weight;

	  Average_RAA_mid_sts+=(raa_mid_tem_sts_err*weight)*(raa_mid_tem_sts_err*weight);
	  
	  
	}

      Average_RAA_mid_sts=sqrt(Average_RAA_mid_sts);

      //      cout<< "Average RAA mid"<< Average_RAA_mid<< "Average_RAA_mid_sys"<< Average_RAA_mid_sys<<" Average_RAA_mid_sts"<< Average_RAA_mid_sts<< endl;
	
      for(int i=0;i<Npoint_fwd;i++)
        {
	  
          // fwdy 
         gr_CentRaaStat5020_fwd->GetPoint(i,raa_fwd_tem_x,raa_fwd_tem_y);
      
          raa_fwd_tem_sts_err=gr_CentRaaStat5020_fwd->GetErrorY(i);
          raa_fwd_tem_sys_err=gr_CentRaaSyst5020_fwd->GetErrorY(i);
	  
	  Double_t relative_sts=raa_fwd_tem_sts_err/raa_fwd_tem_y;
	  
	  weight_fwd_all+=1./(relative_sts*relative_sts);
 
        }       
      Double_t Average_RAA_fwd=0.0;
      Double_t Average_RAA_fwd_sts=0.0;
      Double_t Average_RAA_fwd_sys=0.0;
      
      for(int i=0;i<Npoint_fwd;i++)
        {
	  gr_CentRaaStat5020_fwd->GetPoint(i,raa_fwd_tem_x,raa_fwd_tem_y);
      
          raa_fwd_tem_sts_err=gr_CentRaaStat5020_fwd->GetErrorY(i);
          raa_fwd_tem_sys_err=gr_CentRaaSyst5020_fwd->GetErrorY(i);
	  raa_mid_tem_sys_err=sqrt(raa_mid_tem_sys_err*raa_mid_tem_sys_err-(TAA_old_fwd[i][1]/TAA_old_fwd[i][0]*raa_mid_tem_y)*(TAA_old_fwd[i][1]/TAA_old_fwd[i][0]*raa_mid_tem_y)); //remove the TAA from mid;
	  
	  Double_t relative_sts=raa_fwd_tem_sts_err/raa_fwd_tem_y; 
	  Double_t weight=1./(relative_sts*relative_sts)/weight_fwd_all;
	  
	  Average_RAA_fwd += raa_fwd_tem_y*weight;
	  Average_RAA_fwd_sys+=raa_fwd_tem_sys_err*weight;
	  Average_RAA_fwd_sts+=raa_fwd_tem_sts_err*weight*raa_fwd_tem_sts_err*weight;
	}

      raa_fwd_tem_sts_err=sqrt(raa_fwd_tem_sts_err);
      
      //      cout<< "Average RAA fwd"<< Average_RAA_fwd<< " Average_RAA_fwd_sys "<< Average_RAA_fwd_sys << " Average_RAA_fwd_sts "<< Average_RAA_fwd_sts<<endl;
	    


      Double_t Average_RAA_err=Average_RAA_mid_sts*Average_RAA_mid_sts+Average_RAA_mid_sys*Average_RAA_mid_sys;
      Average_RAA_err+=Average_RAA_fwd_sts*Average_RAA_fwd_sts+Average_RAA_fwd_sys*Average_RAA_fwd_sys;
      Average_RAA_err+=(0.07*Average_RAA_mid)*(0.07*Average_RAA_mid)+(0.07*Average_RAA_fwd)*(0.07*Average_RAA_fwd);
	
      Average_RAA_err=sqrt(Average_RAA_err);

      Double_t sigma=abs(Average_RAA_mid-Average_RAA_fwd)/Average_RAA_err;
      
      

      cout  <<"Average RAA mid"<< Average_RAA_mid<< "Average_RAA_mid_sts" <<  Average_RAA_mid_sts<< "Average_RAA_mid_sys"<< Average_RAA_mid_sys<<endl;
      cout  << "Average RAA fwd " << Average_RAA_fwd<< "Average_RAA_fwd_sts" <<  Average_RAA_fwd_sts<< "Average_RAA_fwd_sys"<< Average_RAA_fwd_sys<<endl;

      cout << "diff "<<abs(Average_RAA_mid-Average_RAA_fwd)<< " sigma "<<sigma<<endl;
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
