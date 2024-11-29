/*******************************************************************************
 * Copyright (c) 2012 - 2015 ACIN, fortiss GmbH
 *                      2018 Johannes Kepler University
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl
 *   - initial API and implementation and/or initial documentation
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *   Martin Jobst
 *     - refactor for ANY variant
 *     - add generic readInputData and writeOutputData
 *   Michael Hansal
 *   - add support for array parameters
 *******************************************************************************/
#include "GEN_CSV_WRITER_fbt.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "GEN_CSV_WRITER_fbt_gen.cpp"
#endif
#include <errno.h>
#include "devlog.h"
#include "resource.h"
#include "criticalregion.h"

DEFINE_GENERIC_FIRMWARE_FB(GEN_CSV_WRITER, g_nStringIdGEN_CSV_WRITER);

const CStringDictionary::TStringId GEN_CSV_WRITER::scmDataOutputNames[] = { g_nStringIdQO, g_nStringIdSTATUS };

const CStringDictionary::TStringId GEN_CSV_WRITER::scmDataOutputTypeIds[] = { g_nStringIdBOOL, g_nStringIdSTRING };

const CStringDictionary::TStringId GEN_CSV_WRITER::scmEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };
const CStringDictionary::TStringId GEN_CSV_WRITER::scmEventInputTypeIds[] = {g_nStringIdEInit, g_nStringIdEvent};

const CStringDictionary::TStringId GEN_CSV_WRITER::scmEventOutputNames[] = { g_nStringIdINITO, g_nStringIdCNF };
const CStringDictionary::TStringId GEN_CSV_WRITER::scmEventOutputTypeIds[] = {g_nStringIdEvent, g_nStringIdEvent};

const CIEC_STRING GEN_CSV_WRITER::scmOK = "OK"_STRING;
const CIEC_STRING GEN_CSV_WRITER::scmFileAlreadyOpened = "File already opened"_STRING;
const CIEC_STRING GEN_CSV_WRITER::scmFileNotOpened = "File not opened"_STRING;

void GEN_CSV_WRITER::executeEvent(TEventID paEIID, CEventChainExecutionThread *const paECET) {
  if(scmEventINITID == paEIID) {
    if(QI()) {
      openCSVFile();
    } else {
      closeCSVFile();
    }
    sendOutputEvent(scmEventINITOID, paECET);
  } else if(scmEventREQID == paEIID) {
    QO() = QI();
    if(QI()) {
      writeCSVFileLine();
    }
    sendOutputEvent(scmEventCNFID, paECET);
  }
}

GEN_CSV_WRITER::GEN_CSV_WRITER(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CGenFunctionBlock<CFunctionBlock>(paContainer, paInstanceNameId), mCSVFile(nullptr) {
}

GEN_CSV_WRITER::~GEN_CSV_WRITER(){
  closeCSVFile();
}

void GEN_CSV_WRITER::readInputData(TEventID paEI) {
  switch(paEI) {
    case scmEventINITID: {
      readData(0, *mDIs[0], mDIConns[0]);
      readData(1, *mDIs[1], mDIConns[1]);
      break;
    }
    case scmEventREQID: {
      readData(0, *mDIs[0], mDIConns[0]);
      for(TPortId i = 2; i < getFBInterfaceSpec().mNumDIs; i++){
        readData(i, *mDIs[i], mDIConns[i]);
      }
      break;
    }
    default:
      break;
  }
}

void GEN_CSV_WRITER::writeOutputData(TEventID) {
  writeData(0, *mDOs[0], mDOConns[0]);
  writeData(1, *mDOs[1], mDOConns[1]);
}

bool GEN_CSV_WRITER::createInterfaceSpec(const char *paConfigString, SFBInterfaceSpec &paInterfaceSpec) {
  const char *acPos = strrchr(paConfigString, '_');
  if(nullptr != acPos){
    acPos++;
    paInterfaceSpec.mNumDIs = static_cast<TPortId>(forte::core::util::strtoul(acPos, nullptr, 10) + 2); // we have in addition to the SDs a QI and FILE_NAME data inputs

    mDataInputNames = std::make_unique<CStringDictionary::TStringId[]>(paInterfaceSpec.mNumDIs);
    mDataInputTypeIds = std::make_unique<CStringDictionary::TStringId[]>(paInterfaceSpec.mNumDIs);

    mDataInputNames[0] = g_nStringIdQI;
    mDataInputTypeIds[0] = g_nStringIdBOOL;
    mDataInputNames[1] = g_nStringIdFILE_NAME;
    mDataInputTypeIds[1] = g_nStringIdSTRING;

    generateGenericDataPointArrays("SD_", &(mDataInputTypeIds[2]), &(mDataInputNames[2]), paInterfaceSpec.mNumDIs - 2);

    //create the interface Specification
    paInterfaceSpec.mNumEIs = 2;
    paInterfaceSpec.mEINames = scmEventInputNames;
    paInterfaceSpec.mNumEOs = 2;
    paInterfaceSpec.mEONames = scmEventOutputNames;
    paInterfaceSpec.mDINames = mDataInputNames.get();
    paInterfaceSpec.mDIDataTypeNames = mDataInputTypeIds.get();
    paInterfaceSpec.mNumDOs = 2;
    paInterfaceSpec.mDONames = scmDataOutputNames;
    paInterfaceSpec.mDODataTypeNames = scmDataOutputTypeIds;
    return true;
  }
  return false;
}

void GEN_CSV_WRITER::openCSVFile() {
  QO() = CIEC_BOOL(false);
  if(nullptr == mCSVFile) {
    mCSVFile = forte_fopen(FILE_NAME().getStorage().c_str(), "w+");
    if(nullptr != mCSVFile) {
      QO() = CIEC_BOOL(true);
      STATUS() = scmOK;
      DEVLOG_INFO("[GEN_CSV_WRITER]: File %s successfully opened\n", FILE_NAME().getStorage().c_str());
    } else {
      const char* errorCode = strerror(errno); 
      STATUS() = CIEC_STRING(errorCode, strlen(errorCode));
      DEVLOG_ERROR("[GEN_CSV_WRITER]: Couldn't open file %s. Error: %s\n", FILE_NAME().getStorage().c_str(), STATUS().getStorage().c_str());
    }
  } else {
    STATUS() = scmFileAlreadyOpened;
    DEVLOG_ERROR("[GEN_CSV_WRITER]: Can't open file %s since it is already opened\n", FILE_NAME().getStorage().c_str());
  }
}

void GEN_CSV_WRITER::closeCSVFile() {
  QO() = CIEC_BOOL(false);
  if(nullptr != mCSVFile) {
    if(0 == forte_fclose(mCSVFile)) {
      STATUS() = scmOK;
      DEVLOG_INFO("[GEN_CSV_WRITER]: File %s successfully closed\n", FILE_NAME().getStorage().c_str());
    } else {
      const char *errorCode = strerror(errno);
      STATUS() = CIEC_STRING(errorCode, strlen(errorCode));
      DEVLOG_ERROR("[GEN_CSV_WRITER]: Couldn't close file %s. Error: %s\n", FILE_NAME().getStorage().c_str(), STATUS().getStorage().c_str());
    }
    mCSVFile = nullptr;
  }
}

bool GEN_CSV_WRITER::areDIsSameArrayLength(size_t& commonArraySize) {
  constexpr TPortId firstDataDI = 2;
  if(getFBInterfaceSpec().mNumDIs <= firstDataDI) {
    return false;
  }

  for(TPortId i = firstDataDI; i < getFBInterfaceSpec().mNumDIs; i++) {
    auto& value = getDI(i)->unwrap();
    if(value.getDataTypeID() != CIEC_ANY::e_ARRAY) {
      return false;
    }

    const size_t size = static_cast<const CIEC_ARRAY &>(value).size();
    if (i == firstDataDI) {
      commonArraySize = size;
    } else if (size != commonArraySize) {
      return false;
    }
  }

  return true;
}

void GEN_CSV_WRITER::writeCSVFileLine() {
  if(nullptr != mCSVFile) {
    size_t numLines;
    bool multiline = areDIsSameArrayLength(numLines);
    if(!multiline) {
      numLines = 1;
    }

    char acBuffer[scmWriteBufferSize];
    for(size_t line = 0; line < numLines; line++) {
      for(TPortId i = 2; i < getFBInterfaceSpec().mNumDIs; i++) {
        auto& value = getDI(i)->unwrap();
        int nLen;
        if(multiline) {
          auto& array = static_cast<const CIEC_ARRAY &>(value);
          nLen = array.at(line).unwrap().toString(acBuffer, scmWriteBufferSize);
        } else {
          nLen = value.toString(acBuffer, scmWriteBufferSize);
        }
        if(nLen >= 0) {
          forte_fwrite(acBuffer, 1, static_cast<size_t>(nLen), mCSVFile);
        } else {
          DEVLOG_ERROR("[GEN_CSV_WRITER]: Can't get string value for input %d\n", i);
        }
        forte_fwrite("; ", 1, 2, mCSVFile);
      }
      forte_fwrite("\n", 1, 1, mCSVFile);
    }
  } else {
    QO() = CIEC_BOOL(false);
    STATUS() = scmFileNotOpened;
    DEVLOG_ERROR("[GEN_CSV_WRITER]: Can't write to file %s since it is not opened\n", FILE_NAME().getStorage().c_str());
  }
}
