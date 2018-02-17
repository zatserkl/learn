{
gROOT->Macro(gSystem->ExpandPathName("$(HOME)/macros/rootlogon.C"));
cout<< "*-- Local rootlogon" << endl;

// cout<< "Local rootlogon.C: Defined const char s[] = \"same\"" <<endl;
// const char s[] = "same";

// cout<< "Load FWLite" <<endl;
// gSystem->Load("libFWCoreFWLite.so");
// AutoLibraryLoader::enable();
}

