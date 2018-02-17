/*************************************************************************
 * Class describes DCU used on CMS Pixel Port Card                       *
 *                                                                       *
 * Author: Andriy Zatserklyaniy, University of Puerto Rico		 *
 *                                                                       *
 *************************************************************************/

#include "PixelUtilities/PixelTKFECDataTools/include/PortCardDCU.h"

//--xdaq #include "xdaq/Application.h"
//--xdaq #include "xdaq/exception/Exception.h"
//--xdaq #include "xoap/MessageReference.h"

#include <sstream>
#include <iostream>
#include <cassert>

using std::cout; using std::endl;

namespace PortCard {

// General purpose string --> unsigned and unsigned --> string conversion functions
std::string unsigned2string(unsigned number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}
unsigned string2unsigned(std::string str) {
  std::stringstream ss(str);
  unsigned number = 0;                // NB: would not be changed in case of conversion error
  if (ss >> number) return number;
  else return 0;
}

//////////////////////////////
//
//  class DCU
//
//////////////////////////////

//
//  initializing of static fields of class DCU
//
const double DCU::kPt_ = 3850.e-6;
const std::string DCU::name_modeDCU   = "DCUmode";
const std::string DCU::name_modeValue = "DCUmodeValue";
const std::string DCU::name_modeLIR   = "DCUmodeLIR";
const std::string DCU::name_modeHIR   = "DCUmodeHIR";
const std::string DCU::name_Vaa       = "Vaa";
const std::string DCU::name_Vdd       = "Vdd";
const std::string DCU::name_RTD2      = "RTD2";
const std::string DCU::name_RTD3      = "RTD3";
const std::string DCU::name_AOH       = "AOH";
const std::string DCU::name_Vpc       = "Vpc";
const std::string DCU::name_Vbg       = "Vbg";
const std::string DCU::name_TS        = "TS";
const std::string DCU::name_wrong     = "";

DCU::DCU(): mode_(0), Vaa_(0), Vdd_(0), rtd2_(0), rtd3_(0), aoh_(0), Vpc_(0), Vbg_(0), ts_(0) {}
DCU::DCU(unsigned mode, unsigned Vaa, unsigned Vdd, unsigned rtd2, unsigned rtd3, unsigned aoh, unsigned Vpc, unsigned Vbg, unsigned ts):
  mode_(mode), Vaa_(Vaa), Vdd_(Vdd), rtd2_(rtd2), rtd3_(rtd3), aoh_(aoh), Vpc_(Vpc), Vbg_(Vbg), ts_(ts)
{}
void DCU::FillVector(std::vector<unsigned>& vchan) const {
  vchan.push_back(Vaa_);
  vchan.push_back(Vdd_);
  vchan.push_back(rtd2_);
  vchan.push_back(rtd3_);
  vchan.push_back(aoh_);
  vchan.push_back(Vpc_);
  vchan.push_back(Vbg_);
  vchan.push_back(ts_);
}
void DCU::SetADC(unsigned adc[]) {
  Vaa_  = adc[0];
  Vdd_  = adc[1];
  rtd2_ = adc[2];
  rtd3_ = adc[3];
  aoh_  = adc[4];
  Vpc_  = adc[5];
  Vbg_  = adc[6];
  ts_   = adc[7];
}
void DCU::print(std::ostream& out) const {
  out
    << "mode_ = " << mode_ 
    << " Vaa_ = " << Vaa_ 
    << " Vdd_ = " << Vdd_ 
    << " rtd2_ = " << rtd2_ 
    << " rtd3_ = " << rtd3_ 
    << " aoh_ = " << aoh_ 
    << " Vpc_ = " << Vpc_ 
    << " Vbg_ = " << Vbg_ 
    << " ts_ = " << ts_ 
  ;
}
std::string DCU::prints() const {
  std::stringstream out;
  out
    << "mode_ = " << mode_ 
    << " Vaa_ = " << Vaa_ 
    << " Vdd_ = " << Vdd_ 
    << " rtd2_ = " << rtd2_ 
    << " rtd3_ = " << rtd3_ 
    << " aoh_ = " << aoh_ 
    << " Vpc_ = " << Vpc_ 
    << " Vbg_ = " << Vbg_ 
    << " ts_ = " << ts_ 
  ;
  return out.str();
}
const std::string& DCU::name_chan(unsigned chan) {
  switch (chan) {
    case 0:  return name_Vaa;
    case 1:  return name_Vdd;
    case 2:  return name_RTD2;
    case 3:  return name_RTD3;
    case 4:  return name_AOH;
    case 5:  return name_Vpc;
    case 6:  return name_Vbg;
    case 7:  return name_TS;
    default: std::cout<< "ERROR PortCard::DCU::name_chan: channel " << chan << " is out of range (0..7)" <<std::endl;
    return name_wrong;
  }
}
unsigned DCU::GetChan(unsigned chan) const {
  switch (chan) {
    case 0:  return Vaa_;
    case 1:  return Vdd_;
    case 2:  return rtd2_;
    case 3:  return rtd3_;
    case 4:  return aoh_;
    case 5:  return Vpc_;
    case 6:  return Vbg_;
    case 7:  return ts_;
    default: std::cout<< "ERROR PortCard::DCU::GetChan: channel " << chan << " is out of range (0..7)" <<std::endl;
    return 0;
  }
}

//////////////////////////////
//
//  class Address
//
//////////////////////////////

Address::Address(): dcuId_(0), fecBoardId_(0), mfecId_(0), ccuId_(0), ccuChannelId_(0) {}
Address::Address(std::string portcardName, unsigned dcuId, unsigned fecBoardId, unsigned mfecId, unsigned ccuId, unsigned ccuChannelId):
  portcardName_(portcardName), dcuId_(dcuId), fecBoardId_(fecBoardId), mfecId_(mfecId), ccuId_(ccuId), ccuChannelId_(ccuChannelId)
{}
Address::Address(const Address& address):
  portcardName_(address.portcardName_), dcuId_(address.dcuId_), fecBoardId_(address.fecBoardId_), mfecId_(address.mfecId_), ccuId_(address.ccuId_), ccuChannelId_(address.ccuChannelId_)
{}
Address& Address::operator = (const Address& address)
{
  portcardName_ = address.portcardName_;
  dcuId_           = address.dcuId_;
  fecBoardId_   = address.fecBoardId_;
  mfecId_       = address.mfecId_;
  ccuId_        = address.ccuId_;
  ccuChannelId_ = address.ccuChannelId_;
  return *this;
}
bool Address::operator < (const Address& address) const
{
  // method to be used in std::map for comparison
  // Example of map definition:
  // std::map<Address, DCU> dcu_map;

  if (portcardName_ != address.portcardName_) return (portcardName_ < address.portcardName_);
  if (dcuId_        != address.dcuId_)        return (dcuId_        < address.dcuId_);
  if (fecBoardId_   != address.fecBoardId_)   return (fecBoardId_   < address.fecBoardId_);
  if (mfecId_       != address.mfecId_)       return (mfecId_       < address.mfecId_);
  if (ccuId_        != address.ccuId_)        return (ccuId_        < address.ccuId_);
  if (ccuChannelId_ != address.ccuChannelId_) return (ccuChannelId_ < address.ccuChannelId_);
  return false;   // at this point all fields are equal
}
void Address::print(std::ostream& out) const {
  out
    << "portcardName_ = " << portcardName_
    << " dcuId_ = " << dcuId_
    << " fecBoardId_ = " << fecBoardId_ 
    << " mfecId_ = " << mfecId_ 
    << " ccuId_ = " << ccuId_ 
    << " ccuChannelId_ = " << ccuChannelId_ 
  ;
}
std::string Address::prints() const {
  std::stringstream out;
  out
    << "portcardName_ = " << portcardName_
    << " dcuId_ = " << dcuId_
    << " fecBoardId_ = " << fecBoardId_ 
    << " mfecId_ = " << mfecId_ 
    << " ccuId_ = " << ccuId_ 
    << " ccuChannelId_ = " << ccuChannelId_ 
  ;
  return out.str();
}

void AddressDCU::print(std::ostream& out) const {
  address_.print(std::cout);
  out<<std::endl;
  dcu_.print(std::cout);
  out<<std::endl;
}

//--xdaq ////////////////////////////////////////////////////////////////////////////////////////////////
//--xdaq //
//--xdaq // SOAP message coders and decoders
//--xdaq //
//--xdaq ////////////////////////////////////////////////////////////////////////////////////////////////
//--xdaq 
//--xdaq /////////////////////////////////
//--xdaq //
//--xdaq // class SOAP_ReadAll
//--xdaq //
//--xdaq /////////////////////////////////
//--xdaq 
//--xdaq //
//--xdaq //  initializing of static fields of class SOAP_ReadAll
//--xdaq //
//--xdaq const std::string SOAP_ReadAll::name_xdaq_          = "xdaq";
//--xdaq const std::string SOAP_ReadAll::name_dp_            = "dp";
//--xdaq const std::string SOAP_ReadAll::name_command_       = "updateDpValueTrkFEC";    // never used, just for completeness here
//--xdaq const std::string SOAP_ReadAll::name_portcard_      = "portcard";
//--xdaq // address
//--xdaq const std::string SOAP_ReadAll::name_portcardId_    = "portcardId";
//--xdaq const std::string SOAP_ReadAll::name_fecBoardId_    = "fecBoardId";
//--xdaq const std::string SOAP_ReadAll::name_mfecId_        = "mfecId";
//--xdaq const std::string SOAP_ReadAll::name_ccuId_         = "ccuId";
//--xdaq const std::string SOAP_ReadAll::name_ccuChannelId_  = "ccuChannelId";
//--xdaq // DCU ID
//--xdaq const std::string SOAP_ReadAll::name_dcuIdId_       = "dcuIdId";
//--xdaq // DCU mode
//--xdaq const std::string SOAP_ReadAll::name_dcuModeId_     = "dcuModeId";
//--xdaq // DCU channels
//--xdaq const std::string SOAP_ReadAll::name_dcuChannelId_  = "dcuChannelId";
//--xdaq 
//--xdaq xoap::MessageReference SOAP_ReadAll::Make(const std::string& tagName, const std::vector<AddressDCU>& vdcu)
//--xdaq {
//--xdaq   //
//--xdaq   //  Creates SOAP message from vector of AddressDCU structures
//--xdaq   //
//--xdaq   
//--xdaq   // create SOAP message;
//--xdaq   xoap::MessageReference soapMessage = xoap::createMessage();
//--xdaq   xoap::SOAPEnvelope envelope = soapMessage->getSOAPPart().getEnvelope();
//--xdaq   xoap::SOAPBody body = envelope.getBody();
//--xdaq 
//--xdaq   xoap::SOAPName command = envelope.createName(tagName, name_xdaq_, XDAQ_NS_URI);
//--xdaq   xoap::SOAPBodyElement bodyElement = body.addBodyElement(command);
//--xdaq 
//--xdaq   for (std::vector<AddressDCU>::const_iterator addressDCU=vdcu.begin(); addressDCU!=vdcu.end(); ++addressDCU)
//--xdaq   {
//--xdaq     // add current Port Card as a child
//--xdaq     xoap::SOAPName portcardName = envelope.createName(name_portcard_);
//--xdaq     xoap::SOAPElement portcardElement = bodyElement.addChildElement(portcardName);
//--xdaq 
//--xdaq     // check the number of children
//--xdaq     //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: bodyElement.getChildElements(portcardName).size() = " << bodyElement.getChildElements(portcardName).size() <<endl;
//--xdaq 
//--xdaq     // add module location (fecAddress, ringAddress(==mfec), ccuAddress, I2C channelAddress) as attributes of portcardElement
//--xdaq 
//--xdaq     // portcardId
//--xdaq     xoap::SOAPName portcardIdName = envelope.createName(name_portcardId_);
//--xdaq     portcardElement.addAttribute(portcardIdName, addressDCU->address_.portcardName_);
//--xdaq 
//--xdaq     // IdId
//--xdaq     xoap::SOAPName IdIdName = envelope.createName(name_dcuIdId_);
//--xdaq     portcardElement.addAttribute(IdIdName, unsigned2string(addressDCU->address_.dcuId_));
//--xdaq 
//--xdaq     // fecBoardId
//--xdaq     xoap::SOAPName fecBoardIdName = envelope.createName(name_fecBoardId_);
//--xdaq     portcardElement.addAttribute(fecBoardIdName, unsigned2string(addressDCU->address_.fecBoardId_));
//--xdaq 
//--xdaq     // mfecId (NB: we are using term "mfecId" instead of "ring" here)
//--xdaq     xoap::SOAPName mfecIdName = envelope.createName(name_mfecId_);
//--xdaq     portcardElement.addAttribute(mfecIdName, unsigned2string(addressDCU->address_.mfecId_));
//--xdaq 
//--xdaq     // ccuId
//--xdaq     xoap::SOAPName ccuIdName = envelope.createName(name_ccuId_);
//--xdaq     portcardElement.addAttribute(ccuIdName, unsigned2string(addressDCU->address_.ccuId_));
//--xdaq 
//--xdaq     // ccuChannelId
//--xdaq     xoap::SOAPName ccuChannelIdName = envelope.createName(name_ccuChannelId_);
//--xdaq     portcardElement.addAttribute(ccuChannelIdName, unsigned2string(addressDCU->address_.ccuChannelId_));
//--xdaq 
//--xdaq     // store DCU input mode
//--xdaq     xoap::SOAPName dcuModeName = envelope.createName(name_dcuModeId_);
//--xdaq     portcardElement.addAttribute(dcuModeName, unsigned2string(addressDCU->dcu_.mode_));
//--xdaq     // add ADC values for all DCU channels of the current Port Card
//--xdaq     // Make child elements with name "dp"
//--xdaq     // Store channel No. as dp attribute
//--xdaq     // Store ADC value using dp method addTextNode
//--xdaq     std::vector<unsigned> vchan;
//--xdaq     addressDCU->dcu_.FillVector(vchan);
//--xdaq     for (std::vector<unsigned>::iterator channel=vchan.begin(); channel!=vchan.end(); ++channel)
//--xdaq     { // have to use iterator instead of const_iterator
//--xdaq       // because std::distance doesn't work with const_iterator: known issue
//--xdaq       unsigned iChannel = std::distance(vchan.begin(), channel);
//--xdaq       xoap::SOAPName dpName = envelope.createName(name_dp_);
//--xdaq       xoap::SOAPElement dpNameElement = portcardElement.addChildElement(dpName);    // current dp is a child of portcard
//--xdaq       xoap::SOAPName channelName = envelope.createName(name_dcuChannelId_);
//--xdaq       dpNameElement.addAttribute(channelName, unsigned2string(iChannel));           // the No. of DCU channel is attribute of dp
//--xdaq       dpNameElement.addTextNode(unsigned2string(*channel));                         // the ADC value is stored using addTextNode
//--xdaq     }
//--xdaq   }
//--xdaq   return soapMessage;
//--xdaq }
//--xdaq 
//--xdaq xoap::MessageReference SOAP_ReadAll::Make(const std::string& tagName, const std::string& receiver, const std::string& uri, const std::vector<AddressDCU>& vdcu)
//--xdaq {
//--xdaq   //
//--xdaq   //  Creates SOAP message from vector of AddressDCU structures
//--xdaq   //
//--xdaq   
//--xdaq   // create SOAP message;
//--xdaq   xoap::MessageReference soapMessage = xoap::createMessage();
//--xdaq   xoap::SOAPEnvelope envelope = soapMessage->getSOAPPart().getEnvelope();
//--xdaq   xoap::SOAPBody body = envelope.getBody();
//--xdaq 
//--xdaq   xoap::SOAPName command = envelope.createName(tagName, receiver, uri);
//--xdaq   xoap::SOAPBodyElement bodyElement = body.addBodyElement(command);
//--xdaq 
//--xdaq   for (std::vector<AddressDCU>::const_iterator addressDCU=vdcu.begin(); addressDCU!=vdcu.end(); ++addressDCU)
//--xdaq   {
//--xdaq     // add current Port Card as a child
//--xdaq     xoap::SOAPName portcardName = envelope.createName(name_portcard_);
//--xdaq     xoap::SOAPElement portcardElement = bodyElement.addChildElement(portcardName);
//--xdaq 
//--xdaq     // check the number of children
//--xdaq     //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: bodyElement.getChildElements(portcardName).size() = " << bodyElement.getChildElements(portcardName).size() <<endl;
//--xdaq 
//--xdaq     // add module location (fecAddress, ringAddress(==mfec), ccuAddress, I2C channelAddress) as attributes of portcardElement
//--xdaq 
//--xdaq     // portcardId
//--xdaq     xoap::SOAPName portcardIdName = envelope.createName(name_portcardId_);
//--xdaq     portcardElement.addAttribute(portcardIdName, addressDCU->address_.portcardName_);
//--xdaq 
//--xdaq     // IdId
//--xdaq     xoap::SOAPName IdIdName = envelope.createName(name_dcuIdId_);
//--xdaq     portcardElement.addAttribute(IdIdName, unsigned2string(addressDCU->address_.dcuId_));
//--xdaq 
//--xdaq     // fecBoardId
//--xdaq     xoap::SOAPName fecBoardIdName = envelope.createName(name_fecBoardId_);
//--xdaq     portcardElement.addAttribute(fecBoardIdName, unsigned2string(addressDCU->address_.fecBoardId_));
//--xdaq 
//--xdaq     // mfecId (NB: we are using term "mfecId" instead of "ring" here)
//--xdaq     xoap::SOAPName mfecIdName = envelope.createName(name_mfecId_);
//--xdaq     portcardElement.addAttribute(mfecIdName, unsigned2string(addressDCU->address_.mfecId_));
//--xdaq 
//--xdaq     // ccuId
//--xdaq     xoap::SOAPName ccuIdName = envelope.createName(name_ccuId_);
//--xdaq     portcardElement.addAttribute(ccuIdName, unsigned2string(addressDCU->address_.ccuId_));
//--xdaq 
//--xdaq     // ccuChannelId
//--xdaq     xoap::SOAPName ccuChannelIdName = envelope.createName(name_ccuChannelId_);
//--xdaq     portcardElement.addAttribute(ccuChannelIdName, unsigned2string(addressDCU->address_.ccuChannelId_));
//--xdaq 
//--xdaq     // store DCU input mode
//--xdaq     xoap::SOAPName dcuModeName = envelope.createName(name_dcuModeId_);
//--xdaq     portcardElement.addAttribute(dcuModeName, unsigned2string(addressDCU->dcu_.mode_));
//--xdaq     // add ADC values for all DCU channels of the current Port Card
//--xdaq     // Make child elements with name "dp"
//--xdaq     // Store channel No. as dp attribute
//--xdaq     // Store ADC value using dp method addTextNode
//--xdaq     std::vector<unsigned> vchan;
//--xdaq     addressDCU->dcu_.FillVector(vchan);
//--xdaq     for (std::vector<unsigned>::iterator channel=vchan.begin(); channel!=vchan.end(); ++channel)
//--xdaq     { // have to use iterator instead of const_iterator
//--xdaq       // because std::distance doesn't work with const_iterator: known issue
//--xdaq       unsigned iChannel = std::distance(vchan.begin(), channel);
//--xdaq       xoap::SOAPName dpName = envelope.createName(name_dp_);
//--xdaq       xoap::SOAPElement dpNameElement = portcardElement.addChildElement(dpName);    // current dp is a child of portcard
//--xdaq       xoap::SOAPName channelName = envelope.createName(name_dcuChannelId_);
//--xdaq       dpNameElement.addAttribute(channelName, unsigned2string(iChannel));           // the No. of DCU channel is attribute of dp
//--xdaq       dpNameElement.addTextNode(unsigned2string(*channel));                         // the ADC value is stored using addTextNode
//--xdaq     }
//--xdaq   }
//--xdaq   return soapMessage;
//--xdaq }
//--xdaq 
//--xdaq std::vector<AddressDCU> SOAP_ReadAll::Decode(xoap::MessageReference msg)
//--xdaq {
//--xdaq   //
//--xdaq   //  Extracts vector of AddressDCU structures from the SOAP message
//--xdaq   //
//--xdaq   std::vector<AddressDCU> vdcu;
//--xdaq   AddressDCU addressDCU;
//--xdaq 
//--xdaq   xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
//--xdaq   xoap::SOAPBody body = envelope.getBody();
//--xdaq   xoap::SOAPName commandElement = envelope.createName(name_command_);
//--xdaq   
//--xdaq   std::vector<xoap::SOAPElement> bodyElements = body.getChildElements(commandElement);
//--xdaq   //cout << "PixelTKFECSupervisor::readDCU_fakeSOAP: Number of BodyElements = " << bodyElements.size() << endl;
//--xdaq 
//--xdaq   for (std::vector<xoap::SOAPElement>::iterator p_bodyElement = bodyElements.begin(); p_bodyElement != bodyElements.end(); ++p_bodyElement)
//--xdaq   {
//--xdaq     //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: vector element " << std::distance(bodyElements.begin(), p_bodyElement) <<endl;
//--xdaq     //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: BodyElement name = " << p_bodyElement->getElementName().getQualifiedName() <<endl;
//--xdaq 
//--xdaq     xoap::SOAPName portcardName = envelope.createName(name_portcard_);
//--xdaq     std::vector<xoap::SOAPElement> portcardElement = p_bodyElement->getChildElements(portcardName);
//--xdaq     //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: portcardElement.size() = " << portcardElement.size() <<endl;
//--xdaq     for (std::vector<xoap::SOAPElement>::iterator portcard=portcardElement.begin(); portcard!=portcardElement.end(); ++portcard)
//--xdaq     {
//--xdaq       // PortCard::Address fields
//--xdaq       
//--xdaq       // portcardId
//--xdaq       xoap::SOAPName portcardIdName = envelope.createName(name_portcardId_);
//--xdaq       addressDCU.address_.portcardName_ = portcard->getAttributeValue(portcardIdName);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.portcardName_ = " << addressDCU.address_.portcardName_ <<endl;
//--xdaq 
//--xdaq       // dcuIdId
//--xdaq       xoap::SOAPName dcuIdName = envelope.createName(name_dcuIdId_);
//--xdaq       std::string dcuIdId_str = portcard->getAttributeValue(dcuIdName);
//--xdaq       addressDCU.address_.dcuId_ = string2unsigned(dcuIdId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.dcuId_ = " << addressDCU.address_.dcuId_ <<endl;
//--xdaq 
//--xdaq       // fecBoardId
//--xdaq       xoap::SOAPName fecBoardIdName = envelope.createName(name_fecBoardId_);
//--xdaq       std::string fecBoardId_str = portcard->getAttributeValue(fecBoardIdName);
//--xdaq       addressDCU.address_.fecBoardId_ = string2unsigned(fecBoardId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.fecBoardId_ = " << addressDCU.address_.fecBoardId_ <<endl;
//--xdaq 
//--xdaq       // mfecId (NB: we are using term "mfecId" instead of "ring" here)
//--xdaq       xoap::SOAPName mfecIdName = envelope.createName(name_mfecId_);
//--xdaq       std::string mfecId_str = portcard->getAttributeValue(mfecIdName);
//--xdaq       addressDCU.address_.mfecId_ = string2unsigned(mfecId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.mfecId_ = " << addressDCU.address_.mfecId_ <<endl;
//--xdaq 
//--xdaq       // ccuId
//--xdaq       xoap::SOAPName ccuIdName = envelope.createName(name_ccuId_);
//--xdaq       std::string ccuId_str = portcard->getAttributeValue(ccuIdName);
//--xdaq       addressDCU.address_.ccuId_ = string2unsigned(ccuId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.ccuId_ = " << addressDCU.address_.ccuId_ <<endl;
//--xdaq 
//--xdaq       // ccuChannelId
//--xdaq       xoap::SOAPName ccuChannelIdName = envelope.createName(name_ccuChannelId_);
//--xdaq       std::string ccuChannelId_str = portcard->getAttributeValue(ccuChannelIdName);
//--xdaq       addressDCU.address_.ccuChannelId_ = string2unsigned(ccuChannelId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU.address_.ccuChannelId_ = " << addressDCU.address_.ccuChannelId_ <<endl;
//--xdaq       
//--xdaq       // PortCard::DCU fields
//--xdaq 
//--xdaq       // dcu mode
//--xdaq       xoap::SOAPName dcuModeIdName = envelope.createName(name_dcuModeId_);
//--xdaq       std::string dcuModeId_str = portcard->getAttributeValue(dcuModeIdName);
//--xdaq       addressDCU.dcu_.mode_ = string2unsigned(dcuModeId_str);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: addressDCU->dcu_.mode_ = " << addressDCU.dcu_.mode_ <<endl;
//--xdaq 
//--xdaq       xoap::SOAPName dp_vector_Name = envelope.createName(name_dp_);
//--xdaq       std::vector<xoap::SOAPElement> dp_vector = portcard->getChildElements(dp_vector_Name);
//--xdaq       //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: dp_vector.size() = " << dp_vector.size() <<endl;
//--xdaq       unsigned adc[8];
//--xdaq       // basic test
//--xdaq       assert(dp_vector.size() == 8);
//--xdaq       for (std::vector<xoap::SOAPElement>::iterator dp=dp_vector.begin(); dp!=dp_vector.end(); ++dp)
//--xdaq       {
//--xdaq         xoap::SOAPName dcuChannelId = envelope.createName(name_dcuChannelId_);
//--xdaq         //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: dp->getAttributeValue(dcuChannelId): " << dp->getAttributeValue(dcuChannelId) <<endl;
//--xdaq         //cout<< "PixelTKFECSupervisor::readDCU_fakeSOAP: dp->getValue(): " << dp->getValue() <<endl;
//--xdaq         adc[std::distance(dp_vector.begin(), dp)] = string2unsigned(dp->getValue()); // more safe
//--xdaq         // adc[string2unsigned(dp->getAttributeValue(dcuChannelId))] = string2unsigned(dp->getValue());
//--xdaq       }
//--xdaq       addressDCU.dcu_.SetADC(adc);
//--xdaq 
//--xdaq       vdcu.push_back(addressDCU);
//--xdaq     }
//--xdaq   }
//--xdaq   // to make sure that vector is OK
//--xdaq   // for (std::vector<AddressDCU>::const_iterator addressDCU=vdcu.begin(); addressDCU!=vdcu.end(); ++addressDCU)
//--xdaq   // {
//--xdaq   //   addressDCU->print(cout);
//--xdaq   // }
//--xdaq   return vdcu;
//--xdaq }



} // namespace PortCard
