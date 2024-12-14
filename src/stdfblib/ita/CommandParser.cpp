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


namespace forte::command_parser {


char *parseRequest(char *paRequestString, forte::core::SManagementCMD &paCommand){
  //first check if it is an management request
  char *acCommandStart = nullptr;
  static const int scnCommandLength[] = {7, 7, 6, 5, 5, 6, 5, 6, 6};

  if(!strncmp("<Request ID=\"", paRequestString, 13)){
    int i = 13;
    int j;
    paCommand.mID = &(paRequestString[i]);
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
        paCommand.mCMD = EMGMCommandType::CreateGroup;
      }
      else if(!strncmp("DELETE", acCommandStart, 6)){
        paCommand.mCMD = EMGMCommandType::DeleteGroup;
      }
      else if(!strncmp("START", acCommandStart, 5)){
        paCommand.mCMD = EMGMCommandType::Start;
      }
      else if(!strncmp("STOP", acCommandStart, 4)){
        paCommand.mCMD = EMGMCommandType::Stop;
      }
      else if(!strncmp("KILL", acCommandStart, 4)){
        paCommand.mCMD = EMGMCommandType::Kill;
      }
      else if(!strncmp("RESET", acCommandStart, 5)){
        paCommand.mCMD = EMGMCommandType::Reset;
      }
      else if(!strncmp("READ", acCommandStart, 4)){
        paCommand.mCMD = EMGMCommandType::Read;
      }
      else if(!strncmp("WRITE", acCommandStart, 5)){
        paCommand.mCMD = EMGMCommandType::Write;
      }
#ifdef FORTE_SUPPORT_QUERY_CMD
      else if(!strncmp("QUERY", acCommandStart, 5)){
        paCommand.mCMD = EMGMCommandType::QueryGroup;
      }
#endif // FORTE_SUPPORT_QUERY_CMD
      else{
        return nullptr;
      }
      acCommandStart += scnCommandLength[static_cast<int>(paCommand.mCMD)];
    }
  }
  return acCommandStart;
}

#ifdef FORTE_DYNAMIC_TYPE_LOAD
bool parseXType(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand, const char *paRequestType) {
  bool retVal = false;
  size_t nReqLength = strlen(paRequestType);
  if(!strncmp(paRequestType, paRequestPartLeft, nReqLength)){
    paRequestPartLeft = &(paRequestPartLeft[nReqLength]);
    if('*' != paRequestPartLeft[0]){
      int i = parseIdentifier(paRequestPartLeft, paCommand.mFirstParam);
      paRequestPartLeft = (-1 == i) ? nullptr : strchr(&(paRequestPartLeft[i + 1]), '>');
    }
    if(nullptr != paRequestPartLeft){
      paRequestPartLeft++;
      char* endOfRequest = strchr(paRequestPartLeft, '<');
      *endOfRequest = '\0';
      forte::core::util::transformEscapedXMLToNonEscapedText(paRequestPartLeft);
      paCommand.mAdditionalParams = paRequestPartLeft;
      retVal = true;
    }
  }
  return retVal;
}
#endif // FORTE_DYNAMIC_TYPE_LOAD

bool parseFBData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  bool retVal = false;

  if(!strncmp("FB Name=\"", paRequestPartLeft, 9)){
    char *acBuf = &(paRequestPartLeft[9]);
    int i = 0;
    if(acBuf[0] != '*'){
      i = parseIdentifier(acBuf, paCommand.mFirstParam);
      acBuf = (-1 == i) ? nullptr : strchr(&(acBuf[i + 1]), '\"');
    }
    else{
      acBuf = strchr(&(acBuf[i + 2]), '\"');
    }

    if(acBuf != nullptr){
      if(acBuf[1] != '*'){
        ++acBuf;
        i = parseIdentifier(acBuf, paCommand.mSecondParam);
        if(-1 != i){
          acBuf = strchr(&(acBuf[i + 1]), '\"');
          if(acBuf != nullptr){
            // We have an application name given
            ++acBuf;
            TForteUInt16 nBufLength = static_cast<TForteUInt16>(strcspn(acBuf, "\"") + 1);
            paCommand.mAdditionalParams.assign(acBuf, nBufLength);
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

int parseIdentifier(char *paIdentifierStart, forte::core::TNameIdentifier &paIdentifier){
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

bool parseConnectionData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  bool bRetVal = false;
  if(!strncmp("Connection Source=\"", paRequestPartLeft, sizeof("Connection Source=\"") - 1)){
    int i = parseIdentifier(&(paRequestPartLeft[19]), paCommand.mFirstParam);
    if(-1 != i){
      char *acBuf = strchr(&(paRequestPartLeft[i + 21]), '\"');
      if(acBuf != nullptr){
        parseIdentifier(&(acBuf[1]), paCommand.mSecondParam);
        bRetVal = (-1 != i);
      }
    }
  }
  return bRetVal;
}

bool parseWriteConnectionData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
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
    paCommand.mAdditionalParams = addParams;
    delete[](addParams);
    *endOfSource = '"'; // restore the string
    paRequestPartLeft = strchr(endOfSource + 1, '\"');
    if(nullptr != paRequestPartLeft){
      retVal = (-1 != parseIdentifier(&paRequestPartLeft[1], paCommand.mFirstParam));
    }
  }
  return retVal;
}

void parseCreateData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  paCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
      switch (paRequestPartLeft[0]){
#ifdef FORTE_DYNAMIC_TYPE_LOAD
        case 'A': // we have an Adapter to Create
          if(parseXType(paRequestPartLeft, paCommand, "AdapterType Name=\"")){
            paCommand.mCMD = EMGMCommandType::CreateAdapterType;
          }
          break;
#endif // FORTE_DYNAMIC_TYPE_LOAD
        case 'F': // we have an FB to Create
          if(parseFBData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::CreateFBInstance;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, paCommand, "FBType Name=\"")){
            paCommand.mCMD = EMGMCommandType::CreateFBType;
          }
#endif // FORTE_DYNAMIC_TYPE_LOAD
          break;
        case 'C': // we have an Connection to Create
          if(parseConnectionData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::CreateConnection;
          }
          break;
#ifdef FORTE_SUPPORT_MONITORING
        case 'W': // we have an Watch to Add
          if(parseMonitoringData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::MonitoringAddWatch;
          }
          break;
#endif //FORTE_SUPPORT_MONITORING
        default:
          break;
      }
  }
}

void parseDeleteData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  paCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
    switch (paRequestPartLeft[0]){
      case 'F': // we have an FB to delete
        if(parseFBData(paRequestPartLeft, paCommand)){
          paCommand.mCMD = EMGMCommandType::DeleteFBInstance;
        }
        break;
      case 'C': // we have an Connection to delete
        if(parseConnectionData(paRequestPartLeft, paCommand)){
          paCommand.mCMD = EMGMCommandType::DeleteConnection;
        }
        break;
#ifdef FORTE_SUPPORT_MONITORING
      case 'W': // we have an Watch to remove
        if(parseMonitoringData(paRequestPartLeft, paCommand)){
           paCommand.mCMD = EMGMCommandType::MonitoringRemoveWatch;
        }
        break;
#endif // FORTE_SUPPORT_MONITORING
      default:
        break;
    }
  }
}

void parseAdditionalStateCommandData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  if(nullptr != paRequestPartLeft && '/' != paRequestPartLeft[0] && //if we have an additional xml token parse if it is an FB definition
    !parseFBData(paRequestPartLeft, paCommand)) {
    paCommand.mCMD = EMGMCommandType::INVALID;
  }
}

void parseReadData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  paCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
#ifdef FORTE_SUPPORT_MONITORING
    if('W' == paRequestPartLeft[0]){
          paCommand.mCMD = EMGMCommandType::MonitoringReadWatches;
    } else
#endif // FORTE_SUPPORT_MONITORING
      if(parseConnectionData(paRequestPartLeft, paCommand)){
        paCommand.mCMD = EMGMCommandType::Read;
      }
  }
}

void parseWriteData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  //We need an additional xml connection token parse if it is an connection definition
  paCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft && parseWriteConnectionData(paRequestPartLeft, paCommand)){
#ifdef FORTE_SUPPORT_MONITORING
    char *pch = strstr(paRequestPartLeft, "force=\"");
    if (nullptr != pch) {
      if (!strncmp(&pch[7], "true", sizeof("true") - 1)) {
        paCommand.mCMD = EMGMCommandType::MonitoringForce;
      } else if (!strncmp(&pch[7], "false", sizeof("false") - 1)) {
        paCommand.mCMD = EMGMCommandType::MonitoringClearForce;
      }
    } else if ((2 == paCommand.mAdditionalParams.length()) &&
      (('$' == paCommand.mAdditionalParams[0]) &&
        (('e' == paCommand.mAdditionalParams[1]) ||('E' == paCommand.mAdditionalParams[1]) ))){
      paCommand.mCMD = EMGMCommandType::MonitoringTriggerEvent;
    }else if ((3 == paCommand.mAdditionalParams.length()) &&
      (('$' == paCommand.mAdditionalParams[0]) &&
       (('e' == paCommand.mAdditionalParams[1]) ||('E' == paCommand.mAdditionalParams[1]) ) &&
       (('r' == paCommand.mAdditionalParams[2]) ||('R' == paCommand.mAdditionalParams[2]) ) )){
      paCommand.mCMD = EMGMCommandType::MonitoringResetEventCount;
    }else
#endif // FORTE_SUPPORT_MONITORING
      paCommand.mCMD = EMGMCommandType::Write;
  }
}

#ifdef FORTE_SUPPORT_QUERY_CMD
void parseQueryData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  paCommand.mCMD = EMGMCommandType::INVALID;
  if(nullptr != paRequestPartLeft){
    switch (paRequestPartLeft[0]){
      case 'F': // query fb or fb type list
        if(!strncmp(paRequestPartLeft, "FBT", sizeof("FBT") - 1)){
          if(parseTypeListData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::QueryFBTypes;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, paCommand, "FBType Name=\"")){
            paCommand.mCMD = EMGMCommandType::QueryFBType;
          }
#endif
          else {
            paCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }else if(parseFBData(paRequestPartLeft, paCommand)){
          paCommand.mCMD = EMGMCommandType::QueryFB;
        }
        break;
      case 'C': // query connection list
        if(parseConnectionData(paRequestPartLeft, paCommand)){
          paCommand.mCMD = EMGMCommandType::QueryConnection;
        }
        break;
      case 'D': // query datatype list
        if(!strncmp(paRequestPartLeft, "DataType", sizeof("DataType") - 1)){
          if(parseTypeListData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::QueryDTTypes;
          } else {
            paCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }
        break;
      case 'A': // query adaptertype list
        if(!strncmp(paRequestPartLeft, "AdapterT", sizeof("AdapterT") - 1)){
          if(parseTypeListData(paRequestPartLeft, paCommand)){
            paCommand.mCMD = EMGMCommandType::QueryAdapterTypes;
          }
#ifdef FORTE_DYNAMIC_TYPE_LOAD
          else if(parseXType(paRequestPartLeft, paCommand, "AdapterType Name=\"")){
            paCommand.mCMD = EMGMCommandType::QueryAdapterType;
          }
#endif
          else {
            paCommand.mCMD = EMGMCommandType::QueryGroup;
          }
        }

        break;
      default:
        break;
    }
  }
}

bool parseTypeListData(char *paRequestPartLeft, forte::core::SManagementCMD &){
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

std::string generateResponse(const char *paID, EMGMResponse paResp){
  std::string response;
  response.append("<Response ID=\"");
  if (nullptr != paID) {
    response.append(paID);
  }
  response.append("\"");
  if(EMGMResponse::Ready != paResp){
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(paResp));
    response.append("\"");
  }
  response.append(" />");
  return response;
}

std::string generateLongResponse(EMGMResponse paResp, forte::core::SManagementCMD &paCMD){
  std::string response;
  response.reserve(static_cast<TForteUInt16>(255 + (paCMD.mAdditionalParams.length())));
  response.append("<Response ID=\"");
  if (nullptr != paCMD.mID) {
    response.append(paCMD.mID);
  }
  response.append("\"");
  if(EMGMResponse::Ready != paResp){
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(paResp));
    response.append("\">\n  ");
  }
  else{
    response.append(">\n  ");
    if(paCMD.mCMD == EMGMCommandType::Read){
      response.append("<Connection Source=\"");
      appendIdentifierName(response, paCMD.mFirstParam);
      response.append("\" Destination=\"");
      response.append(paCMD.mAdditionalParams);
      response.append("\" />");
    }
#ifdef FORTE_SUPPORT_QUERY_CMD
    else if(paCMD.mCMD == EMGMCommandType::QueryConnection){
      if ((paCMD.mFirstParam.isEmpty()) &&
          (paCMD.mSecondParam.isEmpty())) { //src & dst = *
          response.append(paCMD.mAdditionalParams);
      }
      else { //either src or dst = * (both != * should be treated by generateResponse
        response.append("<EndpointList>\n    ");
        response.append(paCMD.mAdditionalParams);
        response.append("\n  </EndpointList>");
      }
    }
    else if(paCMD.mCMD == EMGMCommandType::QueryFB){
      if(!paCMD.mFirstParam.isEmpty()) {  //Name != "*"
        if(!paCMD.mSecondParam.isEmpty()){ //Type != "*"
          response.append("<FBStatus Status=\"");
          response.append(paCMD.mAdditionalParams);
          response.append("\" />");
        } else { //Type == "*"
          response.append("<FB Name=\"");
          appendIdentifierName(response, paCMD.mFirstParam);
          response.append("\" Type=\"");
          response.append(paCMD.mAdditionalParams);
          response.append("\" />");
        }
      }
      else{
        response.append("<FBList>\n    ");
        response.append(paCMD.mAdditionalParams);
        response.append("\n  </FBList>");
      }
    }
    else if(paCMD.mCMD == EMGMCommandType::QueryFBTypes || paCMD.mCMD == EMGMCommandType::QueryAdapterTypes){
      response.append("<NameList>\n    ");
      response.append(paCMD.mAdditionalParams);
      response.append("\n  </NameList>");
    }
    else if(paCMD.mCMD == EMGMCommandType::QueryDTTypes){
      response.append("<DTList>\n    ");
      response.append(paCMD.mAdditionalParams);
      response.append("\n  </DTList>");
    }
    else if(paCMD.mCMD == EMGMCommandType::QueryFBType){
      response.append("<FBType Comment=\"generated\" ");
      response.append(paCMD.mAdditionalParams);
      response.append("  </FBType>");
    }
    else if(paCMD.mCMD == EMGMCommandType::QueryAdapterType){
      response.append("<AdapterType Comment=\"generated\" ");
      response.append(paCMD.mAdditionalParams);
      response.append("   <Service Comment=\"generated\" LeftInterface=\"SOCKET\" RightInterface=\"PLUG\"/>\n</AdapterType>");
    }
#endif
  }
  response.append("\n</Response>");
  return response;
}

void appendIdentifierName(std::string& paDest, forte::core::TNameIdentifier& paIdentifier) {
  if(!paIdentifier.isEmpty()){
    for(forte::core::TNameIdentifier::CIterator runner(paIdentifier.begin());
        runner != paIdentifier.end(); ++runner){
      paDest.append(CStringDictionary::getInstance().get(*runner));
      paDest.append(".");
    }
    paDest.append(CStringDictionary::getInstance().get(paIdentifier.back()));
  }
}

EMGMResponse parseAndExecuteMGMCommand(const char *const paDest, char *paCommand, forte::core::SManagementCMD &paCommandStorage, CDevice& paDevice){
  paCommandStorage.mAdditionalParams.reserve(255);

  EMGMResponse eResp = EMGMResponse::InvalidObject;
  if(nullptr != strchr(paCommand, '>')){
    paCommandStorage.mDestination = (strlen(paDest) != 0) ? CStringDictionary::getInstance().insert(paDest) : CStringDictionary::scmInvalidStringId;
    paCommandStorage.mFirstParam.clear();
    paCommandStorage.mSecondParam.clear();
    if ( 255 <= paCommandStorage.mAdditionalParams.capacity()) {
      paCommandStorage.mAdditionalParams.reserve(255);
    }
    paCommandStorage.mID=nullptr;
#ifdef FORTE_SUPPORT_MONITORING
  paCommandStorage.mMonitorResponse.clear();
#endif // FORTE_SUPPORT_MONITORING
    char *acRequestPartLeft = parseRequest(paCommand, paCommandStorage);
    if(nullptr != acRequestPartLeft){
      acRequestPartLeft = strchr(acRequestPartLeft, '<');
      if(nullptr != acRequestPartLeft){
        acRequestPartLeft++; //point to the next character after the <
      }
      // we got the command for execution
      // now check the rest of the data
      switch (paCommandStorage.mCMD){
        case EMGMCommandType::CreateGroup: // create something
          parseCreateData(acRequestPartLeft, paCommandStorage);
          break;
        case EMGMCommandType::DeleteGroup: //delete something
          parseDeleteData(acRequestPartLeft, paCommandStorage);
          break;
        case EMGMCommandType::Start:
        case EMGMCommandType::Stop:
        case EMGMCommandType::Kill:
        case EMGMCommandType::Reset:
          parseAdditionalStateCommandData(acRequestPartLeft, paCommandStorage);
          break;
        case EMGMCommandType::Read:
          parseReadData(acRequestPartLeft, paCommandStorage);
          break;
        case EMGMCommandType::Write:
          parseWriteData(acRequestPartLeft, paCommandStorage);
          break;
#ifdef FORTE_SUPPORT_QUERY_CMD
        case EMGMCommandType::QueryGroup: // query something
          parseQueryData(acRequestPartLeft, paCommandStorage);
#endif
          break;
        default:
          break;
      }

      if(EMGMCommandType::INVALID != paCommandStorage.mCMD) {
          eResp = paDevice.executeMGMCommand(paCommandStorage);
      }
    }
    else {
      eResp = EMGMResponse::UnsupportedCmd;
    }
  }
  return eResp;
}

#ifdef FORTE_SUPPORT_MONITORING

bool parseMonitoringData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand){
  bool bRetVal = false;
  if(!strncmp("Watch Source=\"", paRequestPartLeft, sizeof("Watch Source=\"") - 1)){
    int i = parseIdentifier(&(paRequestPartLeft[14]), paCommand.mFirstParam);
    if(-1 != i){
      char *acBuf = strchr(&(paRequestPartLeft[i + 16]), '\"');
      if(acBuf != nullptr){
        parseIdentifier(&(acBuf[1]), paCommand.mSecondParam);
        bRetVal = (-1 != i);
      }
    }
  }
  return bRetVal;
}

std::string generateMonitorResponse(EMGMResponse paResp, forte::core::SManagementCMD &paCMD){
  std::string response; 
  if(EMGMResponse::Ready != paResp){
    response.append("<Response ID=\"");
    response.append(paCMD.mID);
    response.append("\"");
    response.append(" Reason=\"");
    response.append(forte::mgm_cmd::getResponseText(paResp));
    response.append("\">\n  ");
    response.append("\n</Response>");
  }else{
    TForteUInt16 size = static_cast<TForteUInt16>(paCMD.mMonitorResponse.length() + strlen(paCMD.mID) + 74);
    response.reserve(size);

    response.clear();
    response.append("<Response ID=\"");
    response.append(paCMD.mID);
    response.append("\"");
    response.append(">\n  ");
    if(paCMD.mCMD == EMGMCommandType::MonitoringReadWatches) {
      response.append("<Watches>\n    ");
      response.append(paCMD.mMonitorResponse);
      response.append("\n  </Watches>");
    }
    response.append("\n</Response>");
  }
  paCMD.mMonitorResponse.clear();
  return response;
}

#endif // FORTE_SUPPORT_MONITORING

} // namespace forte::command_parser
