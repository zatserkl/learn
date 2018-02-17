#include <iostream>
#include <map>

using std::cout;      using std::endl;

// average value
std::map<unsigned int       // fecBoardId
, std::map<unsigned int     // mfecId
, std::map<unsigned int     // ccuId
, std::map<unsigned int     // ccuChannelId
, std::map<unsigned int     // dcuChannelId
, double
> > > > > average_;

unsigned int fecBoard = 1;
unsigned int mfec = 2;
unsigned int ccu = 3;
unsigned int ccuChannel = 4;
unsigned int ichan = 5;

bool exist_new_details() {
  cout<< "exist_new_details()" <<endl;
  bool found = false;
  if (average_.find(fecBoard) != average_.end()) {
    cout<< "found average_.find(fecBoard)" <<endl;
    if (average_[fecBoard].find(mfec) != average_[fecBoard].end()) {
      cout<< "found average_[fecBoard].find(mfec)" <<endl;
      if (average_[fecBoard][mfec].find(ccu) != average_[fecBoard][mfec].end()) {
        cout<< "found average_[fecBoard][mfec].find(ccu)" <<endl;
        if (average_[fecBoard][mfec][ccu].find(ccuChannel) != average_[fecBoard][mfec][ccu].end()) {
          cout<< "found average_[fecBoard][mfec][ccu].find(ccuChannel)" <<endl;
          if (average_[fecBoard][mfec][ccu][ccuChannel].find(ichan) != average_[fecBoard][mfec][ccu][ccuChannel].end()) {
            cout<< "found average_[fecBoard][mfec][ccu][ccuChannel].find(ichan)" <<endl;
            cout<< "average_[fecBoard][mfec][ccu][ccuChannel][ichan] = " << average_[fecBoard][mfec][ccu][ccuChannel][ichan] <<endl;
            found = true;
          }
        }
      }
    }
  }
  return found;
}

bool exist_new() {
  cout<< "average_.find(fecBoard) != average_.end() = " << (average_.find(fecBoard) != average_.end()) <<endl;
  bool found = false;
  if (average_.find(fecBoard) != average_.end()
      && average_[fecBoard].find(mfec) != average_[fecBoard].end()
      && average_[fecBoard][mfec].find(ccu) != average_[fecBoard][mfec].end()
      && average_[fecBoard][mfec][ccu].find(ccuChannel) != average_[fecBoard][mfec][ccu].end()
      && average_[fecBoard][mfec][ccu][ccuChannel].find(ichan) != average_[fecBoard][mfec][ccu][ccuChannel].end()
  ) found = true;
  return found;
}

bool exist_old() {
  unsigned mean0 = average_[fecBoard][mfec][ccu][ccuChannel][ichan];
  return mean0 != 0;
}

main()
{
  // NB: exist_new first because exist_old is modifying map!

  cout<<endl<< "the map is empty" <<endl;
  exist_new_details();
  exist_new_details();
  cout<< "exist_new() = " << exist_new() <<endl;
  cout<< "exist_old() = " << exist_old() <<endl;

  // Wow! In one line new with old new will fire!
  cout<<endl<< "// Wow! In one line new with old the new will fire! -- see comment about order of arguments in the code." <<endl;
  //-- you may try this line before old which in fact filled map by 0. You'll see that new will fire.
  //-- Conclusion: the same trick as with order of computation of the function's parameters.
  // cout<< "exist_new() = " << exist_new() << " exist_old() = " << exist_old() <<endl;

  average_[fecBoard][mfec][ccu][ccuChannel][ichan] = 3.14;

  cout<<endl<< "the map is filled" <<endl;
  exist_new_details();
  cout<< "exist_new() = " << exist_new() <<endl;
  cout<< "exist_old() = " << exist_old() <<endl;

  const double& ref = average_[fecBoard][mfec][ccu][ccuChannel][ichan];
  cout<< "const double& ref = " << ref <<endl;

  // copy average map to another map

  average_[fecBoard][mfec][ccu][ccuChannel][ichan+1] = 2.71;

  std::map<unsigned int         // fecBoardId
    , std::map<unsigned int     // mfecId
    , std::map<unsigned int     // ccuId
    , std::map<unsigned int     // ccuChannelId
    , std::map<unsigned int     // dcuChannelId
    , double
    > > > > > average_copy_;

  // fill some field in average_copy_ before the copy
  average_[0][0][0][0][0] = 1;

  //--
  //-- direct assignement really works!
  //-- NB: this operator will add average_ fields and leave existing average_copy_ fields (if cells are different)
  //--
  average_copy_ = average_;

  //
  // this stuff works as well:
  //
  // for (std::map<unsigned int          // fecBoardId
  //     , std::map<unsigned int         // mfecId
  //     , std::map<unsigned int         // ccuId
  //     , std::map<unsigned int         // ccuChannelId
  //     , std::map<unsigned int         // dcuChannelId
  //     , double
  //     > > > > >::const_iterator i_fecBoard=average_.begin(); i_fecBoard!=average_.end(); ++i_fecBoard)
  // {
  //   for (std::map<unsigned int        // mfecId
  //       , std::map<unsigned int       // ccuId
  //       , std::map<unsigned int       // ccuChannelId
  //       , std::map<unsigned int       // dcuChannelId
  //       , double
  //       > > > >::const_iterator i_mfec=i_fecBoard->second.begin(); i_mfec!=i_fecBoard->second.end(); ++i_mfec)
  //     for (std::map<unsigned int      // ccuId
  //         , std::map<unsigned int     // ccuChannelId
  //         , std::map<unsigned int     // dcuChannelId
  //         , double
  //         > > >::const_iterator i_ccu=i_mfec->second.begin(); i_ccu!=i_mfec->second.end(); ++i_ccu)
  //       for (std::map<unsigned int     // ccuChannelId
  //           , std::map<unsigned int    // dcuChannelId
  //           , double
  //           > >::const_iterator i_ccuChannel=i_ccu->second.begin(); i_ccuChannel!=i_ccu->second.end(); ++i_ccuChannel)
  //         for (std::map<unsigned int   // dcuChannelId
  //             , double
  //             >::const_iterator i_dcuChannel=i_ccuChannel->second.begin(); i_dcuChannel!=i_ccuChannel->second.end(); ++i_dcuChannel)
  //         {
  //           average_copy_[i_fecBoard->first][i_mfec->first][i_ccu->first][i_ccuChannel->first][i_dcuChannel->first] = i_dcuChannel->second;
  //         }
  // }

  //-- print new map

  for (std::map<unsigned int            // fecBoardId
      , std::map<unsigned int           // mfecId
      , std::map<unsigned int           // ccuId
      , std::map<unsigned int           // ccuChannelId
      , std::map<unsigned int           // dcuChannelId
      , double
      > > > > >::const_iterator i_fecBoard=average_copy_.begin(); i_fecBoard!=average_copy_.end(); ++i_fecBoard)
  {
    for (std::map<unsigned int          // mfecId
        , std::map<unsigned int         // ccuId
        , std::map<unsigned int         // ccuChannelId
        , std::map<unsigned int         // dcuChannelId
        , double
        > > > >::const_iterator i_mfec=i_fecBoard->second.begin(); i_mfec!=i_fecBoard->second.end(); ++i_mfec)
      for (std::map<unsigned int        // ccuId
          , std::map<unsigned int       // ccuChannelId
          , std::map<unsigned int       // dcuChannelId
          , double
          > > >::const_iterator i_ccu=i_mfec->second.begin(); i_ccu!=i_mfec->second.end(); ++i_ccu)
        for (std::map<unsigned int      // ccuChannelId
            , std::map<unsigned int     // dcuChannelId
            , double
            > >::const_iterator i_ccuChannel=i_ccu->second.begin(); i_ccuChannel!=i_ccu->second.end(); ++i_ccuChannel)
          for (std::map<unsigned int    // dcuChannelId
              , double
              >::const_iterator i_dcuChannel=i_ccuChannel->second.begin(); i_dcuChannel!=i_ccuChannel->second.end(); ++i_dcuChannel)
          {
            cout<< "average_copy_"
              << "[" << i_fecBoard->first << "]"
              << "[" << i_mfec->first << "]"
              << "[" << i_ccu->first << "]"
              << "[" << i_ccuChannel->first << "]"
              << "[" << i_dcuChannel->first << "]"
              << " = " << i_dcuChannel->second
            <<endl;
          }
  }
}
