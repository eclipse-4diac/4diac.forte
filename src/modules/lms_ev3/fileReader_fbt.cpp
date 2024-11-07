/*******************************************************************************
 * Copyright (c) 2016 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Jose Cabral - initial API and implementation and/or initial documentation
 *******************************************************************************/
 
#include "fileReader_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "fileReader_fbt_gen.cpp"
#endif

#include <sstream>
#include <ostream>
#include <iostream>

DEFINE_FIRMWARE_FB(fileReader, g_nStringIdfileReader)

const CStringDictionary::TStringId fileReader::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdFILE_NAME};

const CStringDictionary::TStringId fileReader::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING};

const CStringDictionary::TStringId fileReader::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdS1};

const CStringDictionary::TStringId fileReader::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdSTRING};

const TForteInt16 fileReader::scmEIWithIndexes[] = {0, 3};
const TDataIOID fileReader::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, scmWithListDelimiter};
const CStringDictionary::TStringId fileReader::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId fileReader::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const TDataIOID fileReader::scmEOWith[] = {0, 1, 2, scmWithListDelimiter, 0, 1, 2, scmWithListDelimiter};
const TForteInt16 fileReader::scmEOWithIndexes[] = {0, 4, -1};
const CStringDictionary::TStringId fileReader::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId fileReader::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec fileReader::scmFBInterfaceSpec = {
  2,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,
  2,  scmDataInputNames, scmDataInputTypeIds,
  3,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

const char * const fileReader::scmOK = "OK";
const char * const fileReader::scmNotInitialised = "Not initialized";
const char * const fileReader::scmCouldNotRead = "Could not read";

void fileReader::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) { //TODO: manage output and status
  switch (paEIID){
    case scmEventINITID:
      if(true == QI()){
        QO() = openFile();
      }
      else{
        closeFile();
      }
      sendOutputEvent(scmEventINITOID, paECET);
      break;
    case scmEventREQID:
      QO() = QI();
      if(true == QI()){
        QO() = readFile();
      }
      sendOutputEvent(scmEventCNFID, paECET);
      if (false == QO()){
        std::cout << "----------ERROR\n";
      }
      break;
  }
}

fileReader::fileReader(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId){
  mFile.rdbuf()->pubsetbuf(nullptr, 0); //disable buffer to avoid latency
}

bool fileReader::openFile(){
  int retVal = false;
  std::string sysFileName(FILE_NAME().getValue());
  if(sysFileName.size()){
    mFile.open(sysFileName.c_str(), std::fstream::in); //TODO change this when fully switching to C++11 for LMS EV3
    if(mFile.is_open()){
      retVal = true;
    }else{
      STATUS() = scmNotInitialised;
    }
  }else{
    STATUS() = scmNotInitialised;
  }
  return retVal;
}

void fileReader::closeFile(){
  if(mFile.is_open()){
    mFile.close();
  }
}

bool fileReader::readFile(){
  bool retVal = false;
  if(mFile.is_open()){
    std::string read = "";
    mFile.clear();
    mFile.seekg(0, std::ios::beg);
    mFile >> read;
    if (mFile.fail()){
      STATUS() = scmCouldNotRead;
    }else{
      S1() = read.c_str();
      STATUS() = scmOK;
      retVal = true;
    }
  }else{
    STATUS() = scmNotInitialised;
  }
  return retVal;
}

