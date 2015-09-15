#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2D.h"

void multi_plot()
{
  gROOT->Reset();
  gStyle->SetOptStat(0000);
  gStyle->SetOptFit(0000);

  TCanvas *c1 = new TCanvas("c1");
  c1->Divide(3, 1);

  TFile *histosf = new TFile("lattice_check.root");

  const int n_histos = 50;
  TH2D *h_buck_xmods_arr[n_histos];
  TH2D *h_buck_umods_arr[n_histos];
  TH2D *h_buck_vmods_arr[n_histos];

  for (int i = 0; i < n_histos; ++i) {
    char hnamex[200];
    char hnameu[200];
    char hnamev[200];
    sprintf(hnamex, "h_buck_v_xmods_%04d", i);
    sprintf(hnameu, "h_buck_v_umods_%04d", i);
    sprintf(hnamev, "h_buck_v_vmods_%04d", i);
    h_buck_xmods_arr[i] = (TH2D*)histosf->Get(hnamex);
    h_buck_umods_arr[i] = (TH2D*)histosf->Get(hnameu);
    h_buck_vmods_arr[i] = (TH2D*)histosf->Get(hnamev);
  }

  c1->Print("lattice_displays.pdf[","pdf");  // open file

  for (int i = 0; i < n_histos; ++i) {

    c1->cd(1);
    h_buck_xmods_arr[i]->Draw("colz");
    c1->cd(2);
    h_buck_umods_arr[i]->Draw("colz");
    c1->cd(3);
    h_buck_vmods_arr[i]->Draw("colz");
    c1->Print("lattice_displays.pdf","pdf");  // add to file

  } // end for loop over events

  c1->Print("lattice_displays.pdf]","pdf");  // close file
}

#ifndef __CINT__
// g++ -o multi_plotter.exe multi_plotter.C `root-config --cflags --libs`
int main() {
  multi_plot();
}
#endif

