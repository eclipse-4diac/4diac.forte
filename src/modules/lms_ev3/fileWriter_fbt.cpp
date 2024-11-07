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
 
#include "fileWriter_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "fileWriter_fbt_gen.cpp"
#endif

#include <sstream>
#include <ostream>
#include <iostream>

DEFINE_FIRMWARE_FB(fileWriter, g_nStringIdfileWriter)

const CStringDictionary::TStringId fileWriter::scmDataInputNames[] = {g_nStringIdQI, g_nStringIdFILE_NAME, g_nStringIdS1, g_nStringIdAPPEND, g_nStringIdAPPCHAR};

const CStringDictionary::TStringId fileWriter::scmDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdSTRING, g_nStringIdSTRING, g_nStringIdBOOL, g_nStringIdSTRING};

const CStringDictionary::TStringId fileWriter::scmDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId fileWriter::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 fileWriter::scmEIWithIndexes[] = {0, 3};
const TDataIOID fileWriter::scmEIWith[] = {0, 1, scmWithListDelimiter, 0, 2, 3, 4, scmWithListDelimiter};
const CStringDictionary::TStringId fileWriter::scmEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ};
const CStringDictionary::TStringId fileWriter::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const TDataIOID fileWriter::scmEOWith[] = {0, 1, scmWithListDelimiter, 0, 1, scmWithListDelimiter};
const TForteInt16 fileWriter::scmEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId fileWriter::scmEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};
const CStringDictionary::TStringId fileWriter::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const SFBInterfaceSpec fileWriter::scmFBInterfaceSpec = {
  2,  scmEventInputNames, scmEventInputTypeIds,  scmEIWith,  scmEIWithIndexes,
  2,  scmEventOutputNames, scmEventOutputTypeIds,  scmEOWith, scmEOWithIndexes,
  5,  scmDataInputNames, scmDataInputTypeIds,
  2,  scmDataOutputNames, scmDataOutputTypeIds,
  0, 0
};

const char * const fileWriter::scmOK = "OK";
const char * const fileWriter::scmNotInitialised = "Not initialized";
const char * const fileWriter::scmCouldNotWrite = "Could not write";

void fileWriter::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) { //TODO: manage output and status
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
        QO() = writeFile();
      }
      sendOutputEvent(scmEventCNFID, paECET);
      if (false == QO()){
        std::cout << "----------ERROR\n";
      }

      break;
  }
}

fileWriter::fileWriter(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId){
  mFile.rdbuf()->pubsetbuf(nullptr, 0); //disable buffer to avoid latency
}

bool fileWriter::openFile(){
  int retVal = false;
  std::string sysFileName(FILE_NAME().getValue());
  if(sysFileName.size()){
    mFile.open(sysFileName.c_str(), std::fstream::out); //TODO change this when fully switching to C++11 for LMS EV3
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

void fileWriter::closeFile(){
  if(mFile.is_open()){
    mFile.close();
  }
}

bool fileWriter::writeFile(){
  bool retVal = false;
  if(mFile.is_open()){
    std::string toWrite = "";
    if (APPEND()){
      toWrite = APPCHAR().getValue();
    } else {
      mFile.seekp(0, std::ios::beg);
    }
    mFile.clear();
    toWrite += S1().getValue();
    mFile << toWrite;
    if (mFile.fail()){
      STATUS() = scmCouldNotWrite;
    }else{
      STATUS() = scmOK;
      retVal = true;
    }
  }
  return retVal;
}

