#include <iostream>
#include "TH1D.h"
#include "finer_to_coarser_error_prop.h"
using namespace std;

TH1D *finer_to_coarser_error_prop(TH1D* finer_histo){

  //FinerEtaBins
  int nlepEta_ZincNjet_finerbins(46);
  double lepEta_ZincNjet_finerbins[47] = {-2.4, -2.3, -2.2, -2.1, -2, -1.85, -1.75, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.75, 1.85, 2, 2.1, 2.2, 2.3, 2.4};
  
  //CoarserEtaBins
  int nlepEta_ZincNjet_coarserbins(20);
  double lepEta_ZincNjet_coarserbins[21] = {-2.1, -1.85, -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
  TH1D *coarser_histo = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);

  int total_bins = 0;
  total_bins = finer_histo->GetNbinsX();

  double bc_m21m185=0.0,  bc_m21m185_err=0.0;
  double bc_m185m16=0.0,  bc_m185m16_err=0.0;
  double bc_m16m14 =0.0,  bc_m16m14_err=0.0;
  double bc_m14m12 =0.0,  bc_m14m12_err=0.0;
  double bc_m12m10 =0.0,  bc_m12m10_err=0.0;
  double bc_m10m08 =0.0,  bc_m10m08_err=0.0;
  double bc_m08m06 =0.0,  bc_m08m06_err=0.0;
  double bc_m06m04 =0.0,  bc_m06m04_err=0.0;
  double bc_m04m02 =0.0,  bc_m04m02_err=0.0;
  double bc_m02m00 =0.0,  bc_m02m00_err=0.0;
  double bc_p00p02 =0.0,  bc_p00p02_err=0.0;
  double bc_p02p04 =0.0,  bc_p02p04_err=0.0;
  double bc_p04p06 =0.0,  bc_p04p06_err=0.0;
  double bc_p06p08 =0.0,  bc_p06p08_err=0.0;
  double bc_p08p10 =0.0,  bc_p08p10_err=0.0;
  double bc_p10p12 =0.0,  bc_p10p12_err=0.0;
  double bc_p12p14 =0.0,  bc_p12p14_err=0.0;
  double bc_p14p16 =0.0,  bc_p14p16_err=0.0;
  double bc_p16p185=0.0,  bc_p16p185_err=0.0;
  double bc_p185p21=0.0,  bc_p185p21_err=0.0;

  for(int i=1; i<=total_bins; i++){
    if((lepEta_ZincNjet_finerbins[i-1]>=-2.1) && (lepEta_ZincNjet_finerbins[i]<= -1.85)){
      bc_m21m185 = finer_histo->GetBinContent(i) + bc_m21m185; 
      bc_m21m185_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m21m185_err*bc_m21m185_err));
      coarser_histo->SetBinContent(1,bc_m21m185);
      coarser_histo->SetBinError(1,bc_m21m185_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-1.85) && (lepEta_ZincNjet_finerbins[i]<= -1.6)){
      bc_m185m16 = finer_histo->GetBinContent(i) + bc_m185m16; 
      bc_m185m16_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m185m16_err*bc_m185m16_err));
      coarser_histo->SetBinContent(2,bc_m185m16);
      coarser_histo->SetBinError(2,bc_m185m16_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-1.6) && (lepEta_ZincNjet_finerbins[i]<= -1.4)){
      bc_m16m14 = finer_histo->GetBinContent(i) + bc_m16m14; 
      bc_m16m14_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m16m14_err*bc_m16m14_err));
      coarser_histo->SetBinContent(3,bc_m16m14);
      coarser_histo->SetBinError(3,bc_m16m14_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-1.4) && (lepEta_ZincNjet_finerbins[i]<= -1.2)){
      bc_m14m12 = finer_histo->GetBinContent(i) + bc_m14m12; 
      bc_m14m12_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m14m12_err*bc_m14m12_err));
      coarser_histo->SetBinContent(4,bc_m14m12);
      coarser_histo->SetBinError(4,bc_m14m12_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-1.2) && (lepEta_ZincNjet_finerbins[i]<= -1.0)){
      bc_m12m10 = finer_histo->GetBinContent(i) + bc_m12m10; 
      bc_m12m10_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m12m10_err*bc_m12m10_err));
      coarser_histo->SetBinContent(5,bc_m12m10);
      coarser_histo->SetBinError(5,bc_m12m10_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-1.0) && (lepEta_ZincNjet_finerbins[i]<= -0.8)){
      bc_m10m08 = finer_histo->GetBinContent(i) + bc_m10m08; 
      bc_m10m08_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m10m08_err*bc_m10m08_err));
      coarser_histo->SetBinContent(6,bc_m10m08);
      coarser_histo->SetBinError(6,bc_m10m08_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-0.8) && (lepEta_ZincNjet_finerbins[i]<= -0.6)){
      bc_m08m06 = finer_histo->GetBinContent(i) + bc_m08m06; 
      bc_m08m06_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m08m06_err*bc_m08m06_err));
      coarser_histo->SetBinContent(7,bc_m08m06);
      coarser_histo->SetBinError(7,bc_m08m06_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-0.6) && (lepEta_ZincNjet_finerbins[i]<= -0.4)){
      bc_m06m04 = finer_histo->GetBinContent(i) + bc_m06m04; 
      bc_m06m04_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m06m04_err*bc_m06m04_err));
      coarser_histo->SetBinContent(8,bc_m06m04);
      coarser_histo->SetBinError(8,bc_m06m04_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-0.4) && (lepEta_ZincNjet_finerbins[i]<= -0.2)){
      bc_m04m02 = finer_histo->GetBinContent(i) + bc_m04m02; 
      bc_m04m02_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m04m02_err*bc_m04m02_err));
      coarser_histo->SetBinContent(9,bc_m04m02);
      coarser_histo->SetBinError(9,bc_m04m02_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=-0.2) && (lepEta_ZincNjet_finerbins[i]<= 0.0)){
      bc_m02m00 = finer_histo->GetBinContent(i) + bc_m02m00; 
      bc_m02m00_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_m02m00_err*bc_m02m00_err));
      coarser_histo->SetBinContent(10,bc_m02m00);
      coarser_histo->SetBinError(10,bc_m02m00_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=0.0) && (lepEta_ZincNjet_finerbins[i]<= 0.2)){
      bc_p00p02 = finer_histo->GetBinContent(i) + bc_p00p02; 
      bc_p00p02_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p00p02_err*bc_p00p02_err));
      coarser_histo->SetBinContent(11,bc_p00p02);
      coarser_histo->SetBinError(11,bc_p00p02_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=0.2) && (lepEta_ZincNjet_finerbins[i]<= 0.4)){
      bc_p02p04 = finer_histo->GetBinContent(i) + bc_p02p04; 
      bc_p02p04_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p02p04_err*bc_p02p04_err));
      coarser_histo->SetBinContent(12,bc_p02p04);
      coarser_histo->SetBinError(12,bc_p02p04_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=0.4) && (lepEta_ZincNjet_finerbins[i]<= 0.6)){
      bc_p04p06 = finer_histo->GetBinContent(i) + bc_p04p06; 
      bc_p04p06_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p04p06_err*bc_p04p06_err));
      coarser_histo->SetBinContent(13,bc_p04p06);
      coarser_histo->SetBinError(13,bc_p04p06_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=0.6) && (lepEta_ZincNjet_finerbins[i]<= 0.8)){
      bc_p06p08 = finer_histo->GetBinContent(i) + bc_p06p08; 
      bc_p06p08_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p06p08_err*bc_p06p08_err));
      coarser_histo->SetBinContent(14,bc_p06p08);
      coarser_histo->SetBinError(14,bc_p06p08_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=0.8) && (lepEta_ZincNjet_finerbins[i]<= 1.0)){
      bc_p08p10 = finer_histo->GetBinContent(i) + bc_p08p10; 
      bc_p08p10_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p08p10_err*bc_p08p10_err));
      coarser_histo->SetBinContent(15,bc_p08p10);
      coarser_histo->SetBinError(15,bc_p08p10_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=1.0) && (lepEta_ZincNjet_finerbins[i]<= 1.2)){
      bc_p10p12 = finer_histo->GetBinContent(i) + bc_p10p12; 
      bc_p10p12_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p10p12_err*bc_p10p12_err));
      coarser_histo->SetBinContent(16,bc_p10p12);
      coarser_histo->SetBinError(16,bc_p10p12_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=1.2) && (lepEta_ZincNjet_finerbins[i]<= 1.4)){
      bc_p12p14 = finer_histo->GetBinContent(i) + bc_p12p14; 
      bc_p12p14_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p12p14_err*bc_p12p14_err));
      coarser_histo->SetBinContent(17,bc_p12p14);
      coarser_histo->SetBinError(17,bc_p12p14_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=1.4) && (lepEta_ZincNjet_finerbins[i]<= 1.6)){
      bc_p14p16 = finer_histo->GetBinContent(i) + bc_p14p16; 
      bc_p14p16_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p14p16_err*bc_p14p16_err));
      coarser_histo->SetBinContent(18,bc_p14p16);
      coarser_histo->SetBinError(18,bc_p14p16_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=1.6) && (lepEta_ZincNjet_finerbins[i]<= 1.85)){
      bc_p16p185 = finer_histo->GetBinContent(i) + bc_p16p185; 
      bc_p16p185_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p16p185_err*bc_p16p185_err));
      coarser_histo->SetBinContent(19,bc_p16p185);
      coarser_histo->SetBinError(19,bc_p16p185_err);
    }
    if((lepEta_ZincNjet_finerbins[i-1]>=1.85) && (lepEta_ZincNjet_finerbins[i]<= 2.1)){
      bc_p185p21 = finer_histo->GetBinContent(i) + bc_p185p21; 
      bc_p185p21_err = sqrt((finer_histo->GetBinError(i) * finer_histo->GetBinError(i)) + (bc_p185p21_err*bc_p185p21_err));
      coarser_histo->SetBinContent(20,bc_p185p21);
      coarser_histo->SetBinError(20,bc_p185p21_err);
    }
  }  

  return coarser_histo;
}
