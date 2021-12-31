//PlottingHelper Class v0.1
// Author: Dennis Weiser

#include "TLatex.h"
#include "TH1.h"
#include "TStyle.h"
#include "TSystem.h"
#include <iostream>
#include "TGraph.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TGraphErrors.h"
#include "TPad.h"
#include "TColor.h"




void DrawText(const char *text, Double_t xCoord=0.5, Double_t yCoord=0.5, Double_t textSize = 0.053, Double_t lineWidth=2){

  TLatex *   tex1 = new TLatex(xCoord,yCoord,text);
  tex1->SetNDC();
  tex1->SetTextFont(42);
  tex1->SetTextSize(textSize);                                                                                                                                                   
  tex1->SetLineWidth(lineWidth);
  tex1->Draw();


}

void SetPad(TPad *pad,Double_t top,Double_t bottom, Double_t left, Double_t right)
{
  pad->SetBottomMargin(bottom);
  pad->SetTopMargin(top);
  pad->SetRightMargin(right);
  pad->SetLeftMargin(left);
  return ;
}

void SetTH2F(TH2F *mh2, Double_t XTitle_size, Double_t YTitle_size, Double_t XTitle_offSet, Double_t YTitle_offSet, Double_t Xlable_size,Double_t Ylable_size,Double_t Xlable_offSet,Double_t Ylable_offSet, Double_t XNdivisions,Double_t YNdivisions)  
{
  mh2->GetXaxis()->SetTitleSize(XTitle_size );
  mh2->GetYaxis()->SetTitleSize(YTitle_size);
  mh2->GetXaxis()->SetTitleOffset(XTitle_offSet);
  mh2->GetYaxis()->SetTitleOffset(YTitle_offSet);
  mh2->GetXaxis()->SetLabelSize(Xlable_size);
  mh2->GetYaxis()->SetLabelSize(Ylable_size);
  mh2->GetXaxis()->SetLabelOffset(Xlable_offSet);
  mh2->GetYaxis()->SetLabelOffset(Ylable_offSet);
  mh2->GetXaxis()->SetNdivisions(XNdivisions);
  mh2->GetYaxis()->SetNdivisions(YNdivisions);
  
  return ;
}

void SetLegend(TLegend *legend, Double_t TextFont=42, Double_t TextSize=0.05,Double_t fillStyle=0,Double_t fillColor=0, Double_t lineColor=0.0, Double_t lineWidth=0.0)
{
  legend->SetTextFont(TextFont);
  legend->SetTextSize(TextSize);

   legend->SetFillStyle(fillStyle);
  legend->SetFillColor(fillColor);
  legend->SetLineColor(lineColor);
  legend->SetLineWidth(lineWidth);
  return ; 
}

void SetTGraphError(TGraphErrors *gr_dummy, Double_t MarkerStyle=20, Double_t MarkerSize=1.0,Double_t MarkerColor=1,Double_t LineColor=1, Double_t LineWidth=2.0, Double_t FillStyle=0.0)
{
  gr_dummy->SetMarkerStyle(MarkerStyle);
  gr_dummy->SetMarkerSize(MarkerSize);
  gr_dummy->SetMarkerColor(MarkerColor);
  gr_dummy->SetLineColor(LineColor);
  gr_dummy->SetLineWidth(LineWidth);
   gr_dummy->SetFillStyle(FillStyle);
  
  return;  

}
void LoadLibs() {
  gSystem->Load("libCore.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libVMC");
  gSystem->Load("libTree");
  gSystem->Load("libMinuit");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGTools");
}


void SetStyle(Bool_t graypalette=kFALSE) {
  cout << "Setting style!" << endl;

  gStyle->Reset("Plain");
  gStyle->SetEndErrorSize(0); //no ticks at End of error bars, unit pixels
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  if(graypalette) gStyle->SetPalette(8,0);
  else gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  gStyle->SetFuncColor(kRed); //DW: Don't like kGreen (std) for fitfunctions etc...
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.01,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetTitleOffset(1.25,"y");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  //  gStyle->SetTickLength(0.04,"X");  gStyle->SetTickLength(0.04,"Y");                                                                       \
                                                                                                                                                

  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  //  gStyle->SetFillColor(kWhite);                                                                                                            \
                                                                                                                                                
  gStyle->SetLegendFont(42);


}

void ForceStyle(TH1F *Histo){

   Histo->SetStats(kFALSE);
   Histo->SetLineWidth(2);
   Histo->SetLabelSize(0.045,"xyz");
   Histo->SetLabelOffset(0.01,"y");
   Histo->SetLabelOffset(0.01,"x");
   Histo->SetLabelColor(kBlack,"xyz");
   Histo->SetTitleSize(0.05,"xyz");
   Histo->SetTitleOffset(1.25,"y");
   Histo->SetTitleOffset(1.2,"x");
}


TGraph *GetRatioDataModel(TGraphErrors *gr_data_sts,TGraphErrors *gr_data_sys,TGraph *gr_model)
{
  TGraphErrors *grDataModel= (TGraphErrors *) gr_data_sts->Clone("grDataModel");
  cout<<" the ratio between data and mdoel"<<endl;

 const  int Npoints=gr_data_sts->GetN();

  Double_t x_data;
  Double_t y_data;

  Double_t xErr_data;
  Double_t yErr_data;

  Double_t x_model_max;
  Double_t y_model_max;

  Double_t x_model_min;
  Double_t y_model_min;
  

  Double_t  pt_ratio[2*Npoints];
  Double_t  spectrummin[2*Npoints];
  Double_t  spectrummax[2*Npoints];

  
  for(int ipoint=0;ipoint<Npoints;ipoint++)
  
    {
      gr_data_sts->GetPoint(ipoint,x_data,y_data);
      xErr_data= gr_data_sts->GetErrorX(ipoint);
      yErr_data= gr_data_sts->GetErrorY(ipoint);
      
      //      cout<< ipoint<< " "<<x_data << " "<<y_data<< " "<<yErr_data<<std::endl;

      
      gr_model->GetPoint(ipoint*2,x_model_min,y_model_min);
      gr_model->GetPoint(Npoints*4-ipoint*2-2,x_model_max,y_model_max);

      //  cout<< ipoint<< " model"  <<x_model_min<< " "<<x_model_max<< " "<<y_model_min<< "  " << y_model_max<<endl;

      //      cout<< ipoint<< " model"<<x_model_max<< " "<<y_model_max<<endl;

      pt_ratio[2*ipoint] = x_model_min;
      pt_ratio[2*ipoint+1] = x_model_max;
      
      spectrummin[2*ipoint] = y_model_min/y_data;
      spectrummin[2*ipoint+1] = y_model_min/y_data;

      spectrummax[2*ipoint] = y_model_max/y_data;
      spectrummax[2*ipoint+1] = y_model_max/y_data;
    }

  TGraph *gspectrummin = new TGraph(2*Npoints,pt_ratio,spectrummin);
  
  TGraph *gspectrummax = new TGraph(2*Npoints,pt_ratio,spectrummax);

  TGraph *gspectrum_ratio = new TGraph(4*Npoints);


  for(int i=0 ; i<2*Npoints ; i++){

    // cout<< "XXX"<<gspectrummin->GetX()[i*2]<< "  "<< gspectrummin->GetX()[i*2+1]<<endl;

    gspectrum_ratio->SetPoint(i,gspectrummax->GetX()[i],gspectrummax->GetY()[i]);
    gspectrum_ratio->SetPoint(2*Npoints+i,gspectrummax->GetX()[2*Npoints-i-1],gspectrummin->GetY()[2*Npoints-i-1]);

  }

  return gspectrum_ratio;
}

TLine *GetLine(Double_t x1,Double_t y1,Double_t x2,Double_t y2,Double_t lineColor,Double_t lineWidth,Double_t lineStyle){

  TLine *line= new TLine(x1,y1,x2,y2);
  line->SetLineColor(lineColor);
  line->SetLineWidth(lineWidth);
  line->SetLineStyle(lineStyle);

  return line;
}

void SetErrorX(TGraphErrors* gr, double xE){

  for(int i=0 ; i<gr->GetN(); i++){

    gr->SetPointError(i,xE,gr->GetEY()[i]);
    //    cout<< "i"<< " "<<gr->GetEY()[i]<<endl; 
  }
}

TGraphErrors* TGraphAsymmErrors_to_TGraphErrors(TGraphAsymmErrors *gr)
{

  TGraphErrors *gr_new= new TGraphErrors(gr->GetN());
  
  
  for(int i=0 ; i<gr->GetN(); i++)
    {
      gr_new->SetPoint(i,gr->GetPointX(i),gr->GetPointY(i));
      gr_new->SetPointError(i,gr->GetErrorX(i),gr->GetErrorY(i));
    }
    
  gr_new->SetName(gr->GetName());

  return gr_new;
}

TGraph *GetPtSpecTM2_5020_model(Int_t Npoint, const  char *input)
{
  ifstream myfileTinghua (input);
  const int nTinghua = Npoint; // lines in the txt file
  double ptTinghua[nTinghua];
  double spectrumTinghuamax[nTinghua];
  double spectrumTinghuamin[nTinghua];
  double ptT = 0.;
  double spectrumMinT = 0.;
  double spectrumMaxT = 0.;
  
  int iTinghua = 0; // counter

  while(myfileTinghua>>ptT>>spectrumMinT>>spectrumMaxT){
    ptTinghua[iTinghua]     = ptT;
    spectrumTinghuamin[iTinghua] = spectrumMinT;
    spectrumTinghuamax[iTinghua] = spectrumMaxT;
    iTinghua++;
  
  }

  TGraph *gspectrumTinghuamin = new TGraph(nTinghua,ptTinghua,spectrumTinghuamin);
  TGraph *gspectrumTinghuamax = new TGraph(nTinghua,ptTinghua,spectrumTinghuamax);
  
  TGraph *gspectrumTinghua = new TGraph(2*nTinghua);
  for(int i=0 ; i<nTinghua ; i++){
    gspectrumTinghua->SetPoint(i,gspectrumTinghuamax->GetX()[i],gspectrumTinghuamax->GetY()[i]);
    gspectrumTinghua->SetPoint(nTinghua+i,gspectrumTinghuamax->GetX()[nTinghua-i-1],gspectrumTinghuamin->GetY()[nTinghua-i-1]);
  }
  return gspectrumTinghua;
} 



TGraph *GetPtSpecTM1_5020_model(Int_t Npoint, const  char *input)
{
  ifstream myfileTAMU(input);
  const int nTAMU = Npoint; // lines in the txt file
  double ptTAMU[nTAMU];
  double spectrumTAMUmax[nTAMU];
  double spectrumTAMUmin[nTAMU];
  double ptT = 0.;
  double spectrumMinT = 0.;
  double spectrumMaxT = 0.;
  
  int iTAMU = 0; // counter

  while(myfileTAMU>>ptT>>spectrumMinT>>spectrumMaxT){
    ptTAMU[iTAMU]     = ptT;
    spectrumTAMUmin[iTAMU] = spectrumMinT;
    spectrumTAMUmax[iTAMU] = spectrumMaxT;
    
    iTAMU++;
  }

  TGraph *gspectrumTAMUmin = new TGraph(nTAMU,ptTAMU,spectrumTAMUmin);
  TGraph *gspectrumTAMUmax = new TGraph(nTAMU,ptTAMU,spectrumTAMUmax);
  
  TGraph *gspectrumTAMU = new TGraph(2*nTAMU);
  for(int i=0 ; i<nTAMU ; i++){
    gspectrumTAMU->SetPoint(i,gspectrumTAMUmax->GetX()[i],gspectrumTAMUmax->GetY()[i]);
    gspectrumTAMU->SetPoint(nTAMU+i,gspectrumTAMUmax->GetX()[nTAMU-i-1],gspectrumTAMUmin->GetY()[nTAMU-i-1]);
  }

  return gspectrumTAMU;
} 


TGraph *GetPtSpecSHM_5020_model(Int_t Npoint, const  char *input)
{
  ifstream myfileSHM (input);
  const int nSHM = Npoint; // lines in the txt file
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
    raaSHMmin[iSHM] = dummy1;
    raaSHMmax[iSHM] = dummy2;
    iSHM++;
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

TGraph *GetPtRaaTM15020_model(Int_t Npoint, const  char * input){
  
  ifstream myfileTAMU(input);

  const int nTAMU = Npoint; // lines in the txt file
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

TGraph *GetPtRaaTM25020_model(Int_t Npoint, const  char * input){

  ifstream myfileTAMU(input);

  const int nTAMU = Npoint; // lines in the txt file
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


TGraph *GetPtRaaSHM5020_model(Int_t Npoint, const  char * input){
  
  ifstream myfileSHM (input);
  const int nSHM = Npoint; // lines in the txt file
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



TGraph *GetCentRaaTM1_5020_model(Int_t Npoint, const  char *input)
{

  ifstream myfileTAMU (input);
  const int nTAMU = Npoint; // lines in the txt file
  double npartTAMU[nTAMU];
  double raaTAMUmax[nTAMU];
  double raaTAMUmin[nTAMU];
  double npartT = 0.;
  double raaMinT = 0.;
  double raaMaxT = 0.;
  
  int iTAMU = 0; // counter

  while(myfileTAMU>>npartT>>raaMinT>>raaMaxT){
    npartTAMU[iTAMU]  = npartT;
    raaTAMUmin[iTAMU] = raaMinT;
    raaTAMUmax[iTAMU] = raaMaxT;
    
    iTAMU++;
  }

  
  TGraph *graaTAMUmin = new TGraph(nTAMU,npartTAMU,raaTAMUmin);
  TGraph *graaTAMUmax = new TGraph(nTAMU,npartTAMU,raaTAMUmax);
  
  TGraph *graaTAMU = new TGraph(2*nTAMU);
  for(int i=0 ; i<nTAMU ; i++){
    graaTAMU->SetPoint(i,graaTAMUmax->GetX()[i],graaTAMUmax->GetY()[i]);
    graaTAMU->SetPoint(nTAMU+i,graaTAMUmax->GetX()[nTAMU-i-1],graaTAMUmin->GetY()[nTAMU-i-1]);
  }
  return graaTAMU;
  
} 


TGraph *GetCentRaaTM2_5020_model(Int_t Npoint, const  char *input)
{

 ifstream myfileTsin(input);
  
  const int nTsin = Npoint; // lines in the txt file
  double npartTsin[nTsin];
  double raaTsinmax[nTsin];
  double raaTsinmin[nTsin];
  double npartTs  = 0.;
  double raaMinTs = 0.;
  double raaMaxTs = 0.;
  double dummy1 = 0.;
  double dummy2 = 0.;
  double dummy3 = 0.;
  int iTsin = 0; // counter

  while(myfileTsin>>npartTs>>raaMinTs>>raaMaxTs){
    npartTsin[iTsin]  = npartTs;
    raaTsinmin[iTsin] = raaMinTs;
    raaTsinmax[iTsin] = raaMaxTs;
    
    iTsin++;
  }

  TGraph *graaTsinmin = new TGraph(nTsin,npartTsin,raaTsinmin);
  TGraph *graaTsinmax = new TGraph(nTsin,npartTsin,raaTsinmax);
  TGraph *graaTsin = new TGraph(2*nTsin);
  
  for(int i=0 ; i<nTsin ; i++){
    graaTsin->SetPoint(i,graaTsinmax->GetX()[i],graaTsinmax->GetY()[i]);
    graaTsin->SetPoint(nTsin+i,graaTsinmax->GetX()[nTsin-i-1],graaTsinmin->GetY()[nTsin-i-1]);
  }
  return graaTsin;
  
  
} 

TGraph *GetCentRaaSHM_5020_model(Int_t Npoint, const  char *input)
{
  ifstream myfileSHM (input);
  //
  // Statistical Hadronisation
  //
  const int nSHM = Npoint; // lines in the txt file
  double npartSHM[nSHM];
  double raaSHMmax[nSHM];
  double raaSHMmin[nSHM];
  double npartS  = 0.;
  double raaMinS = 0.;
  double raaMaxS = 0.;

  int iSHM = 0; // counter

  while(myfileSHM>>npartS>>raaMinS>>raaMaxS){
    
    npartSHM[iSHM]  = npartS;
    raaSHMmin[iSHM] = raaMinS;
    raaSHMmax[iSHM] = raaMaxS;
    
    iSHM++;
  }

  TGraph *graaSHMmin = new TGraph(nSHM,npartSHM,raaSHMmin);
  TGraph *graaSHMmax = new TGraph(nSHM,npartSHM,raaSHMmax);
  
  TGraph *graaSHM = new TGraph(2*nSHM);
  for(int i=0 ; i<nSHM ; i++){
    graaSHM->SetPoint(i,graaSHMmax->GetX()[i],graaSHMmax->GetY()[i]);
    graaSHM->SetPoint(nSHM+i,graaSHMmax->GetX()[nSHM-i-1],graaSHMmin->GetY()[nSHM-i-1]);
  }
  
  return graaSHM;  
  
} 

TGraph *GetCentRaaComv020_model(Int_t Npoint, const  char *input)
{
  ifstream myfileComv(input);
  //
  // 
  //
  const int nComv = Npoint; // lines in the txt file
  double npartComv[nComv];
  double raaComvmax[nComv];
  double raaComvmin[nComv];
  double npartS  = 0.;
  double raaMinS = 0.;
  double raaMaxS = 0.;

  int iComv = 0; // counter

  while(myfileComv>>npartS>>raaMinS>>raaMaxS){
    
    npartComv[iComv]  = npartS;
    raaComvmin[iComv] = raaMinS;
    raaComvmax[iComv] = raaMaxS;
    
    iComv++;
  }

  TGraph *graaComvmin = new TGraph(nComv,npartComv,raaComvmin);
  TGraph *graaComvmax = new TGraph(nComv,npartComv,raaComvmax);
  
  TGraph *graaComv = new TGraph(2*nComv);
  for(int i=0 ; i<nComv ; i++){
    graaComv->SetPoint(i,graaComvmax->GetX()[i],graaComvmax->GetY()[i]);
    graaComv->SetPoint(nComv+i,graaComvmax->GetX()[nComv-i-1],graaComvmin->GetY()[nComv-i-1]);
  }
  
  return graaComv;  
  
} 
