void strcmp_root()
{
   // environment to obtain GMT(UTC) time
   if (!gSystem->Getenv("TZ") || strcmp(gSystem->Getenv("TZ"),"UTC") != 0) {
      cout<< "//-- Warning: Setting environment TZ=UTC" <<endl;
      gSystem->Setenv("TZ", "UTC");
   }

}
