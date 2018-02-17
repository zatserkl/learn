#include <string>
#include <vector>
#include <iostream>

using namespace std;

main()
{
  std::string str = "abcdef";
  std::string sub = "abc";
  cout<< "str = " << str << " sub = " << sub << " str.find(sub, 0) = " << str.find(sub, 0) <<endl;
  if (str.find(sub, 0) != std::string::npos) cout<< "str.find(sub, 0) != std::string::npos ==> string str contains substring sub" <<endl;
  cout<<endl;

  std::ostream& stream = std::cout;

  std::string indent = " ";
  std::string indent_start = "  ";
  std::string bra = indent_start + "<";
  std::string ket = ">";
 
  stream
    << bra << "dataSet type=\"DCU\""
    << " mode=\"" << "mode_" << "\""
  << endl;
  
  //for (std::map<PortCard::Address, std::vector<PortCard::DCU> >::const_iterator it_map=address_vpoints_map_.begin(); it_map!=address_vpoints_map_.end(); ++it_map)
  //{
    //const PortCard::Address& address        = it_map->first;
    //const std::vector<PortCard::DCU>& vdcu  = it_map->second;
    
    std::vector<unsigned> vdcu;
    for (int i=0; i<5; ++i) {
      unsigned adc = 1000 + i;
      vdcu.push_back(adc);
    }
    
    // increase indent
    bra.insert(0, indent);
    
    // <FPix_BmO_D1_PRT1>
    stream << bra << "FPix_BmO_D1_PRT1" << ket <<endl;
    //cout << bra << address.portcardName_ << ket <<endl;
    
    // increase indent
    bra.insert(0, indent);
    
    // <Vaa>
    stream << bra << "Vaa" << ket <<endl;
    //cout << bra << PortCard::DCU::name_Vaa << ket <<endl;
    
    // increase indent
    bra.insert(0, indent);
    
    for (std::vector<unsigned>::const_iterator it_dcu=vdcu.begin(); it_dcu!=vdcu.end(); ++it_dcu)
    {
      // some comment for emacs customization

      stream << bra << *it_dcu << ket <<endl;
      //cout << bra << it_dcu->Vaa() << ket <<endl;
    }
    
    // decrease indent
    cout<< "bra now: ---" << "1234567890" << "---" <<endl;
    cout<< "bra now: ---" << bra << "---" <<endl;
    if (bra.find(indent, 0) != std::string::npos) bra.erase(0, indent.size());
    // bra.erase(0, indent.size());
    cout<< "bra now: ---" << bra << "---" <<endl;
  
    //cout<< "indent now: ---" << "1234567890" << "---" <<endl;
    //cout<< "indent now: ---" << indent << "---" <<endl;
    
    // </Vaa>
    stream << bra << "/" << "Vaa" << ket <<endl;
    //cout << bra << "/" << PortCard::DCU::name_Vaa << ket <<endl;
  //}
}
