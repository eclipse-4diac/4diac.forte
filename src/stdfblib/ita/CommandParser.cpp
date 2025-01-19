/*******************************************************************************
 * Copyright (c) 2024 Jose Cabral
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Jose Cabral
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "CommandParser.h"

#include <cstring>

#include "core/utils/string_utils.h"
#include "core/device.h"


namespace forte::ita {

CommandParser::CommandParser(CDevice& paDevice) : mDevice{paDevice}{
  mCommand.mAdditionalParams.reserve(255);
}

EMGMResponse CommandParser::parseAndExecuteMGMCommand(const char *const paDest, char *paCommand){
  mLastResponse = EMGMResponse::InvalidObject;
 
  if(nullptr != strchr(paCommand, '>')){
    mCommand.mID = nullptr;
    mCommand.mAdditionalParams.clear();
    mCommand.mFirstParam.clear();
    mCommand.mSecondParam.clear();
#ifdef FORTE_SUPPORT_MONITORING
    mCommand.mMonitorResponse.clear();
#endif // FORTE_SUPPORT_MONITORING

    mCommand.mDestination = (strlen(paDest) != 0) ? CStringDictionary::getInstance().insert(paDest) : CStringDictionary::scmInvalidStringId;
    if ( 255 <= mCommand.mAdditionalParams.capacity()) {
      mCommand.mAdditionalParams.reserve(255);
    }

    char *acRequestPartLeft = parseRequest(paCommand);
    if(nullptr != acRequestPartLeft){
      acRequestPartLeft = strchr(acRequestPartLeft, '<');
      if(nullptr != acRequestPartLeft){
        acRequestPartLeft++; //point to the next character after the <
      }
      // we got the command for execution
      // now check the rest of the data
      switch (mCommand.mCMD){
        case EMGMCommandType::CreateGroup: // create something
          parseCreateData(acRequestPartLeft);
          break;
        case EMGMCommandType::DeleteGroup: //delete something
          parseDeleteData(acRequestPartLeft);
          break;
        case EMGMCommandType::Start:
        case EMGMCommandType::Stop:
        case EMGMCommandType::Kill:
        case EMGMCommandType::Reset:
          parseAdditionalStateCommandData(acRequestPartLeft);
          break;
        case EMGMCommandType::Read:
          parseReadData(acRequestPartLeft);
          break;
        case EMGMCommandType::Write:
          parseWriteData(acRequestPartLeft);
          break;
#ifdef FORTE_SUPPORT_QUERY_CMD
        case EMGMCommandType::QueryGroup: // query something
          parseQueryData(acRequestPartLeft);
#endif
          break;
        default:
          break;
      }

      if(EMGMCommandType::INVALID != mCommand.mCMD) {
          mLastResponse = mDevice.executeMGMCommand(mCommand);
      }
    }
    else {
      mLastResponse = EMGMResponse::UnsupportedCmd;
    }
  }
  return mLastResponse;
}


std::string CommandParser::generateResponse(){
#ifdef FORTE_SUPPORT_MONITORING
  if (0 != mCommand.mMonitorResponse.length()) {
    return generateMonitorResponse();
  }
#endif //FORTE_SUPPORT_MONITORING

  if(0 < mCommand.mAdditionalParams.length()){
    return generateLongResponse();
  }

  return generateShortResponse();
}

std::string CommandParser::generateShortResponse(){
  std::string response;
  response.append("<Response ID=\"");
  if (nullptr != mCommand.mID) {
    response.append(mCommand.mID);
  }
  response.append("\"");
  if(EMGMResponse::Ready != mLastResponse){
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(mLastResponse));
    response.append("\"");
  }
  response.append(" />");
  return response;
}

std::string CommandParser::generateLongResponse(){
  std::string response;
  response.reserve(static_cast<TForteUInt16>(255 + (mCommand.mAdditionalParams.length())));
  response.append("<Response ID=\"");
  if (nullptr != mCommand.mID) {
    response.append(mCommand.mID);
  }
  response.append("\"");
  if(EMGMResponse::Ready != mLastResponse){
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(mLastResponse));
    response.append("\">\n  ");
  }
  else{
    response.append(">\n  ");
    if(mCommand.mCMD == EMGMCommandType::Read){
      response.append("<Connection Source=\"");
      appendIdentifierName(response, mCommand.mFirstParam);
      response.append("\" Destination=\"");
      response.append(mCommand.mAdditionalParams);
      response.append("\" />");
    }
#ifdef FORTE_SUPPORT_QUERY_CMD
    else if(mCommand.mCMD == EMGMCommandType::QueryConnection){
      if ((mCommand.mFirstParam.isEmpty()) &&
          (mCommand.mSecondParam.isEmpty())) { //src & dst = *
          response.append(mCommand.mAdditionalParams);
      }
      else { //either src or dst = * (both != * should be treated by generateResponse
        response.append("<EndpointList>\n    ");
        response.append(mCommand.mAdditionalParams);
        response.append("\n  </EndpointList>");
      }
    }
    else if(mCommand.mCMD == EMGMCommandType::QueryFB){
      if(!mCommand.mFirstParam.isEmpty()) {  //Name != "*"
        if(!mCommand.mSecondParam.isEmpty()){ //Type != "*"
          response.append("<FBStatus Status=\"");
          response.append(mCommand.mAdditionalParams);
          response.append("\" />");
        } else { //Type == "*"
          response.append("<FB Name=\"");
          appendIdentifierName(response, mCommand.mFirstParam);
          response.append("\" Type=\"");
          response.append(mCommand.mAdditionalParams);
          response.append("\" />");
        }
      }
      else{
        response.append("<FBList>\n    ");
        response.append(mCommand.mAdditionalParams);
        response.append("\n  </FBList>");
      }
    }
    else if(mCommand.mCMD == EMGMCommandType::QueryFBTypes || mCommand.mCMD == EMGMCommandType::QueryAdapterTypes){
      response.append("<NameList>\n    ");
      response.append(mCommand.mAdditionalParams);
      response.append("\n  </NameList>");
    }
    else if(mCommand.mCMD == EMGMCommandType::QueryDTTypes){
      response.append("<DTList>\n    ");
      response.append(mCommand.mAdditionalParams);
      response.append("\n  </DTList>");
    }
    else if(mCommand.mCMD == EMGMCommandType::QueryFBType){
      response.append("<FBType Comment=\"generated\" ");
      response.append(mCommand.mAdditionalParams);
      response.append("  </FBType>");
    }
    else if(mCommand.mCMD == EMGMCommandType::QueryAdapterType){
      response.append("<AdapterType Comment=\"generated\" ");
      response.append(mCommand.mAdditionalParams);
      response.append("   <Service Comment=\"generated\" LeftInterface=\"SOCKET\" RightInterface=\"PLUG\"/>\n</AdapterType>");
    }
#endif
  }
  response.append("\n</Response>");
  return response;
}

char* CommandParser::parseRequest(char *paRequestString){
  //first check if it is an management request
  char *acCommandStart = nullptr;
  static const int scnCommandLength[] = {7, 7, 6, 5, 5, 6, 5, 6, 6};

  if(!strncmp("<Request ID=\"", paRequestString, 13)){
    int i = 13;
    int j;
    mCommand.mID = &(paRequestString[i]);
    for(j = 0; paRequestString[i] != '\"'; ++i, ++j){
      if(j >= 7){
        return nullptr;
      }
    }
    paRequestString[i] = '\0'; //close ID
    ++i;
    acCommandStart = strchr((&paRequestString[i]), '\"');
    if(acCommandStart != nullptr){
      acCommandStart++; //this is the real start of the command
      if(!strncmp("CREATE", acCommandStart, 6)){
        mCommand.mCMD = EMGMCommandType::CreateGroup;
      }
      else if(!strncmp("DELETE", acCommandStart, 6)){
        mCommand.mCMD = EMGMCommandType::DeleteGroup;
      }
      else if(!strncmp("START", acCommandStart, 5)){
        mCommand.mCMD = EMGMCommandType::Start;
      }
      else if(!strncmp("STOP", acCommandStart, 4)){
        mCommand.mCMD = EMGMCommandType::Stop;
      }
      else if(!strncmp("KILL", acCommandStart, 4)){
        mCommand.mCMD = EMGMCommandType::Kill;
      }
      else if(!strncmp("RESET", acCommandStart, 5)){
        mCommand.mCMD = EMGMCommandType::Reset;
      }
      else if(!strncmp("READ", acCommandStart, 4)){
        mCommand.mCMD = EMGMCommandType::Read;
      }
      else if(!strncmp("WRITE", acCommandStart, 5)){
        mCommand.mCMD = EMGMCommandType::Write;
      }
#ifdef FORTE_SUPPORT_QUERY_CMD
      else if(!strncmp("QUERY", acCommandStart, 5)){
        mCommand.mCMD = EMGMCommandType::QueryGroup;
      }
#endif // FORTE_SUPPORT_QUERY_CMD
      else{
        return nullptr;
      }
      acCommandStart += scnCommandLength[static_cast<int>(mCommand.mCMD)];
    }
  }
  return acCommandStart;
}

#ifdef FORTE_DYNAMIC_TYPE_LOAD
bool CommandParser::parseXType(char *paRequestPartLeft, const char *paRequestType) {
  bool retVal = false;
  size_t nReqLength = strlen(paRequestType);
  if(!strncmp(paRequestType, paRequestPartLeft, nReqLength)){
    paRequestPartLeft = &(paRequestPartLeft[nReqLength]);
    if('*' != paRequestPartLeft[0]){
      int i = parseIdentifier(paRequestPartLeft, mCommand.mFirstParam);
      paRequestPartLeft = (-1 == i) ? nullptr : strchr(&(paRequestPartLeft[i + 1]), '>');
    }
    if(nullptr != paRequestPartLeft){
      paRequestPartLeft++;
      char* endOfRequest = strchr(paRequestPartLeft, '<');
      *endOfRequest = '\0';
      forte::core::util::transformEscapedXMLToNonEscapedText(paRequestPartLeft);
      mCommand.mAdditionalParams = paRequestPartLeft;
      retVal = true;
    }
  }
  return retVal;
}
#endif // FORTE_DYNAMIC_TYPE_LOAD

bool CommandParser::parseFBData(char *paRequestPartLeft){
  bool retVal = false;

  if(!strncmp("FB Name=\"", paRequestPartLeft, 9)){
    char *acBuf = &(paRequestPartLeft[9]);
    int i = 0;
    if(acBuf[0] != '*'){
      i = parseIdentifier(acBuf, mCommand.mFirstParam);
      acBuf = (-1 == i) ? nullptr : strchr(&(acBuf[i + 1]), '\"');
    }
    else{
      acBuf = strchr(&(acBuf[i + 2]), '\"');
    }

    if(acBuf != nullptr){
      if(acBuf[1] != '*'){
        ++acBuf;
        i = parseIdentifier(acBuf, mCommand.mSecondParam);
        if(-1 != i){
          acBuf = strchr(&(acBuf[i + 1]), '\"');
          if(acBuf != nullptr){
            // We have an application name given
            ++acBuf;
            TForteUInt16 nBufLength = static_cast<TForteUInt16>(strcspn(acBuf, "\"") + 1);
            mCommand.mAdditionalParams.assign(acBuf, nBufLength);
          }
        }
        else{
          return false;
        }
      }
      retVal = true;
    }
  }
  return retVal;
}

int CommandParser::parseIdentifier(char *paIdentifierStart, forte::core::TNameIdentifier &paIdentifier){
  for(char *runner = paIdentifierStart, *start = paIdentifierStart; '\0' != *runner; ++runner){
    if('.' == *runner){
      *runner = '\0';
      if(!paIdentifier.pushBack(CStringDictionary::getInstance().insert(start))){
        return -1;
      }
      *runner = '.';
      start = runner + 1;
    } else if ('"' == *runner){
      *runner = '\0';
      if(!paIdentifier.pushBack(CStringDictionary::getInstance().insert(start))){
        return -1;
      }
      *runner = '"';
      return static_cast<int>(runner - paIdentifierStart);
    }
  }
  return -1;
}

bool CommandParser::parseConnectionData(char *paRequestPartLeft){
  bool bRetVal = false;
  if(!strncmp("Connection Source=\"", paRequestPartLeft, sizeof("Connection Source=\"") - 1)){
    int i = parseIdentifier(&(paRequestPartLeft[19]), mCommand.mFirstParam);
    if(-1 != i){
      char *acBuf = strchr(&(paRequestPartLeft[i + 21]), '\"');
      if(acBuf != nullptr){
        parseIdentifier(&(acBuf[1]), mCommand.mSecondParam);
        bRetVal = (-1 != i);
      }
    }
  }
  return bRetVal;
}

bool CommandParser::parseWriteConnectionData(char *paRequestPartLeft){
  bool retVal = false;
  if(!strncmp("Connection Source=\"", paRequestPartLeft, sizeof("Connection Source=\"") - 1)){
    paRequestPartLeft = &(paRequestPartLeft[19]);

    char* endOfSource = strchr(paRequestPartLeft, '\"');
    if(nullptr == endOfSource){
      return false;
    }
    *endOfSource = '\0';
    char *addParams = new char[strlen(paRequestPartLeft) + 1]();
    strcpy(addParams, paRequestPartLeft);
    forte::core::util::transformEscapedXMLToNonEscapedText(addParams);
    mCommand.mAdditionalParams = addParams;
    delete[](addParams);
    *endOfSource = '"'; // restore the string
    paRequestPartLeft = strchr(endOfSource + 1, '\"');
    if(nullptr != paRequestPartLeft){
      retVal = (-1 != parseIdentifier(&paRequestPartLeft[1], mCommand.mFirstParam));
    }
  }
  return retVal;
}

void CommandParser::parseCreateData(char *paRequestPartLeft){
  mCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
      switch (paRequestPartLeft[0]){
#ifdef FORTE_DYNAMIC_TYPE_LOAD
        case 'A': // we have an Adapter to Create
          if(parseXType(paRequestPartLeft, "AdapterType Name=\"")){
            mCommand.mCMD = EMGMCommandType::CreateAdapterType;
          }
          break;
#endif // FORTE_DYNAMIC_TYPE_LOAD
        case 'F': // we have an FB to Create
          if(parseFBData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::CreateFBInstance;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, "FBType Name=\"")){
            mCommand.mCMD = EMGMCommandType::CreateFBType;
          }
#endif // FORTE_DYNAMIC_TYPE_LOAD
          break;
        case 'C': // we have an Connection to Create
          if(parseConnectionData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::CreateConnection;
          }
          break;
#ifdef FORTE_SUPPORT_MONITORING
        case 'W': // we have an Watch to Add
          if(parseMonitoringData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::MonitoringAddWatch;
          }
          break;
#endif //FORTE_SUPPORT_MONITORING
        default:
          break;
      }
  }
}

void CommandParser::parseDeleteData(char *paRequestPartLeft){
  mCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
    switch (paRequestPartLeft[0]){
      case 'F': // we have an FB to delete
        if(parseFBData(paRequestPartLeft)){
          mCommand.mCMD = EMGMCommandType::DeleteFBInstance;
        }
        break;
      case 'C': // we have an Connection to delete
        if(parseConnectionData(paRequestPartLeft)){
          mCommand.mCMD = EMGMCommandType::DeleteConnection;
        }
        break;
#ifdef FORTE_SUPPORT_MONITORING
      case 'W': // we have an Watch to remove
        if(parseMonitoringData(paRequestPartLeft)){
           mCommand.mCMD = EMGMCommandType::MonitoringRemoveWatch;
        }
        break;
#endif // FORTE_SUPPORT_MONITORING
      default:
        break;
    }
  }
}

void CommandParser::parseAdditionalStateCommandData(char *paRequestPartLeft){
  if(nullptr != paRequestPartLeft && '/' != paRequestPartLeft[0] && //if we have an additional xml token parse if it is an FB definition
    !parseFBData(paRequestPartLeft)) {
    mCommand.mCMD = EMGMCommandType::INVALID;
  }
}

void CommandParser::parseReadData(char *paRequestPartLeft){
  mCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
#ifdef FORTE_SUPPORT_MONITORING
    if('W' == paRequestPartLeft[0]){
          mCommand.mCMD = EMGMCommandType::MonitoringReadWatches;
    } else
#endif // FORTE_SUPPORT_MONITORING
      if(parseConnectionData(paRequestPartLeft)){
        mCommand.mCMD = EMGMCommandType::Read;
      }
  }
}

void CommandParser::parseWriteData(char *paRequestPartLeft){
  //We need an additional xml connection token parse if it is an connection definition
  mCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft && parseWriteConnectionData(paRequestPartLeft)){
#ifdef FORTE_SUPPORT_MONITORING
    char *pch = strstr(paRequestPartLeft, "force=\"");
    if (nullptr != pch) {
      if (!strncmp(&pch[7], "true", sizeof("true") - 1)) {
        mCommand.mCMD = EMGMCommandType::MonitoringForce;
      } else if (!strncmp(&pch[7], "false", sizeof("false") - 1)) {
        mCommand.mCMD = EMGMCommandType::MonitoringClearForce;
      }
    } else if ((2 == mCommand.mAdditionalParams.length()) &&
      (('$' == mCommand.mAdditionalParams[0]) &&
        (('e' == mCommand.mAdditionalParams[1]) ||('E' == mCommand.mAdditionalParams[1]) ))){
      mCommand.mCMD = EMGMCommandType::MonitoringTriggerEvent;
    }else if ((3 == mCommand.mAdditionalParams.length()) &&
      (('$' == mCommand.mAdditionalParams[0]) &&
       (('e' == mCommand.mAdditionalParams[1]) ||('E' == mCommand.mAdditionalParams[1]) ) &&
       (('r' == mCommand.mAdditionalParams[2]) ||('R' == mCommand.mAdditionalParams[2]) ) )){
      mCommand.mCMD = EMGMCommandType::MonitoringResetEventCount;
    }else
#endif // FORTE_SUPPORT_MONITORING
      mCommand.mCMD = EMGMCommandType::Write;
  }
}

#ifdef FORTE_SUPPORT_QUERY_CMD
void CommandParser::parseQueryData(char *paRequestPartLeft){
  mCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
    switch (paRequestPartLeft[0]){
      case 'F': // query fb or fb type list
        if(!strncmp(paRequestPartLeft, "FBT", sizeof("FBT") - 1)){
          if(parseTypeListData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::QueryFBTypes;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, "FBType Name=\"")){
            mCommand.mCMD = EMGMCommandType::QueryFBType;
          }
#endif
          else {
            mCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }else if(parseFBData(paRequestPartLeft)){
          mCommand.mCMD = EMGMCommandType::QueryFB;
        }
        break;
      case 'C': // query connection list
        if(parseConnectionData(paRequestPartLeft)){
          mCommand.mCMD = EMGMCommandType::QueryConnection;
        }
        break;
      case 'D': // query datatype list
        if(!strncmp(paRequestPartLeft, "DataType", sizeof("DataType") - 1)){
          if(parseTypeListData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::QueryDTTypes;
          } else {
            mCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }
        break;
      case 'A': // query adaptertype list
        if(!strncmp(paRequestPartLeft, "AdapterT", sizeof("AdapterT") - 1)){
          if(parseTypeListData(paRequestPartLeft)){
            mCommand.mCMD = EMGMCommandType::QueryAdapterTypes;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, "AdapterType Name=\"")){
            mCommand.mCMD = EMGMCommandType::QueryAdapterType;
          }
#endif
          else {
            mCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }

        break;
      default:
        break;
    }
  }
}

bool CommandParser::parseTypeListData(char *paRequestPartLeft){
  bool retVal = true;

  if (!strncmp("DataType Name=\"", paRequestPartLeft, sizeof("DataType Name=\"") - 1)) {
    if(paRequestPartLeft[15] != '*'){ //does not support query for DataType-Declaration
      retVal = false;
    }
  }
  else if(!strncmp("FBType Name=\"", paRequestPartLeft, sizeof("FBType Name=\"") - 1)){
    if(paRequestPartLeft[13] != '*'){ //supports query for FBType-Declaration only for DynamicTypeLoad profile (LUA enabled)
      retVal = false;
    }
  }
  else if(!strncmp("AdapterType Name=\"", paRequestPartLeft, sizeof("AdapterType Name=\"") - 1)){
    if(paRequestPartLeft[18] != '*'){ //does not support query for AdapterType-Declaration
      retVal = false;
    }
  }
  return retVal;
}
#endif


void CommandParser::appendIdentifierName(std::string& paDest, forte::core::TNameIdentifier& paIdentifier) {
  if(!paIdentifier.isEmpty()){
    for(forte::core::TNameIdentifier::CIterator runner(paIdentifier.begin());
        runner != paIdentifier.end(); ++runner){
      paDest.append(CStringDictionary::getInstance().get(*runner));
      paDest.append(".");
    }
    paDest.append(CStringDictionary::getInstance().get(paIdentifier.back()));
  }
}

#ifdef FORTE_SUPPORT_MONITORING

bool CommandParser::parseMonitoringData(char *paRequestPartLeft){
  bool bRetVal = false;
  if(!strncmp("Watch Source=\"", paRequestPartLeft, sizeof("Watch Source=\"") - 1)){
    int i = parseIdentifier(&(paRequestPartLeft[14]), mCommand.mFirstParam);
    if(-1 != i){
      char *acBuf = strchr(&(paRequestPartLeft[i + 16]), '\"');
      if(acBuf != nullptr){
        parseIdentifier(&(acBuf[1]), mCommand.mSecondParam);
        bRetVal = (-1 != i);
      }
    }
  }
  return bRetVal;
}

std::string CommandParser::generateMonitorResponse(){
  std::string response; 
  if(EMGMResponse::Ready != mLastResponse){
    response.append("<Response ID=\"");
    response.append(mCommand.mID);
    response.append("\"");
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(mLastResponse));
    response.append("\">\n  ");
    response.append("\n</Response>");
  }else{
    TForteUInt16 size = static_cast<TForteUInt16>(mCommand.mMonitorResponse.length() + strlen(mCommand.mID) + 74);
    response.reserve(size);

    response.clear();
    response.append("<Response ID=\"");
    response.append(mCommand.mID);
    response.append("\"");
    response.append(">\n  ");
    if(mCommand.mCMD == EMGMCommandType::MonitoringReadWatches) {
      response.append("<Watches>\n    ");
      response.append(mCommand.mMonitorResponse);
      response.append("\n  </Watches>");
    }
    response.append("\n</Response>");
  }
  return response;
}

#endif // FORTE_SUPPORT_MONITORING

} // namespace forte::ita
