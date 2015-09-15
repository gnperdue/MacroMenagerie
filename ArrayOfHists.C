#include "TFile.h"
#include "TRandom.h"
#include "TObjArray.h"
#include "TH2D.h"

void arr_of_hists()
{
  TObjArray *Hlist = new TObjArray(0);
  const int max_entries = 50;

  const int n_xmods = 104;
  const int n_buckets = 22;

  TH2D *h_buck_v_xmods_arr[max_entries];

  for (int i = 0; i < max_entries; ++i) {
    char hnamex[200];
    sprintf(hnamex, "h_buck_v_xmods_%04d", i);
    h_buck_v_xmods_arr[i] = new TH2D(hnamex, "Bucket vs X-Module;X Module;Bucket",
        n_xmods, 0, n_xmods, n_buckets, 0, n_buckets);
    Hlist->Add(h_buck_v_xmods_arr[i]);
  }

  for (int i = 0; i < 4; ++i) {

    TH2D *h = *(h_buck_v_xmods_arr + i);
    double x = gRandom->Rndm() * n_xmods;
    double y = gRandom->Rndm() * n_buckets;
    double w = gRandom->Rndm();
    h->Fill(x, y, w); 

  } // end for loop over events

  char histname[500];
  sprintf(histname, "arr_of_histos.root");
  TFile *outputfile = new TFile(histname, "RECREATE");
  Hlist->Write();
  outputfile->Close();
}

#ifndef __CINT__
int main() {
  arr_of_hists();
}
#endif

