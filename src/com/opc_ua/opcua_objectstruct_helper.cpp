/*******************************************************************************
 * Copyright (c) 2023 Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Markus Meingast - initial implementation
 *******************************************************************************/

#include "opcua_objectstruct_helper.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "opcua_objectstruct_helper_gen.cpp"
#endif
#include "opcua_layer.h"
#include "struct_action_info.h"
#include "../../core/cominfra/basecommfb.h"
#include "opcua_local_handler.h"
#include "../../core/utils/parameterParser.h"
#include <sstream>

using namespace forte::com_infra;

const std::string COPC_UA_ObjectStruct_Helper::smStructTypesBrowsePath = "/Types/0:ObjectTypes/0:BaseObjectType/%d:";

const std::string COPC_UA_ObjectStruct_Helper::smMemberNamespaceIndex = "/%d:";

char COPC_UA_ObjectStruct_Helper::smEmptyString[] = "";

COPC_UA_ObjectStruct_Helper::COPC_UA_ObjectStruct_Helper(COPC_UA_Layer &paLayer, COPC_UA_HandlerAbstract *paHandler):
  mLayer(paLayer), mHandler(paHandler), mOpcuaTypeNamespaceIndex(COPC_UA_Local_Handler::scmDefaultBrowsenameNameSpace),
  mOpcuaObjectNamespaceIndex(COPC_UA_Local_Handler::scmDefaultBrowsenameNameSpace) {
}

COPC_UA_ObjectStruct_Helper::~COPC_UA_ObjectStruct_Helper() {
  mHandler = nullptr;
}

void COPC_UA_ObjectStruct_Helper::uninitializeStruct() {
  for(std::shared_ptr<CActionInfo> actionInfo : mStructMemberActionInfos) {
    mHandler->uninitializeAction(*actionInfo);
  }
  if(mCreateNodeActionInfo) {
    mHandler->uninitializeAction(*mCreateNodeActionInfo);
  }
}

bool COPC_UA_ObjectStruct_Helper::checkStructTypeConnection(CActionInfo &paActionInfo, CIEC_STRUCT &paStructType) {
  bool retVal = true;
  checkOPCUANamespace();
  UA_NodeId typeNodeId = checkAndCreateOPCUAStructType(paActionInfo, paStructType);
  if(UA_NodeId_equal(&typeNodeId, &UA_NODEID_NULL)) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Could not create OPC UA Struct Type at FB %s\n", mLayer.getCommFB()->getInstanceName());
    retVal = false;
  }
  UA_NodeId_clear(&typeNodeId);
  return retVal;
}

UA_NodeId COPC_UA_ObjectStruct_Helper::checkAndCreateOPCUAStructType(CActionInfo &paActionInfo, CIEC_STRUCT &paStructType) {
  CActionInfo::CNodePairInfo nodePair(nullptr, getStructBrowsePath(smStructTypesBrowsePath, paStructType.getTypeNameID()));
  UA_NodeId typeNodeId;
  if(isOPCUAObjectPresent(nodePair)) {
    UA_NodeId_copy(nodePair.getNodeId(), &typeNodeId);
    return typeNodeId;
  } else if(createOPCUAStructType(paActionInfo, typeNodeId, CStringDictionary::getInstance().get(paStructType.getTypeNameID()), paStructType)) {
    return typeNodeId;
  }
  return UA_NODEID_NULL;
}

bool COPC_UA_ObjectStruct_Helper::createOPCUAStructType(CActionInfo &paActionInfo, UA_NodeId &paTypeNodeId, const std::string &paStructTypeName, CIEC_STRUCT &paStructType) {
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  if(!localHandler) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to get LocalHandler because LocalHandler is null!\n");
    return false;
  }
  UA_Server *server = localHandler->getUAServer();
  bool isNodeIdPresent = false;
  if(!paActionInfo.getNodePairInfo().empty()) {
    isNodeIdPresent = paActionInfo.getNodePairInfo().begin()->getNodeId() != nullptr;
  }
  UA_NodeId newTypeNodeId;
  if(!defineOPCUAStructTypeNode(server, newTypeNodeId, paStructTypeName, !isNodeIdPresent)){
    return false;
  }
  if(!addOPCUAStructTypeComponents(server, newTypeNodeId, paStructType, paStructTypeName)) {
    return false;
  }
  UA_NodeId_copy(&newTypeNodeId, &paTypeNodeId);
  UA_NodeId_clear(&newTypeNodeId);
  return true;
}

bool COPC_UA_ObjectStruct_Helper::createOPCUANamespace(char* nsName) {
  mHandler->enableHandler();
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  if(!localHandler) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to get LocalHandler because LocalHandler is null!\n");
    return false;
  }
  UA_Server *server = localHandler->getUAServer();
  UA_UInt16 nsIndex = UA_Server_addNamespace(server, nsName);
  if(nsIndex <= 0) {
    return false;
  }
  mOpcuaTypeNamespaceIndex = nsIndex;
  return true;
}

bool COPC_UA_ObjectStruct_Helper::defineOPCUAStructTypeNode(UA_Server *paServer, UA_NodeId &paNodeId, const std::string &paStructTypeName, bool defaultCase) {
  std::string structTypeName = paStructTypeName;
  if(defaultCase) {
    paNodeId = UA_NODEID_STRING(mOpcuaTypeNamespaceIndex, &structTypeName[0]);
  } else {
    paNodeId = UA_NODEID_NUMERIC(mOpcuaTypeNamespaceIndex, 0);
  }
  UA_ObjectTypeAttributes oAttr = UA_ObjectTypeAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT(smEmptyString, &structTypeName[0]);
  UA_StatusCode status = UA_Server_addObjectTypeNode(paServer, paNodeId,
    UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
    UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
    UA_QUALIFIEDNAME(mOpcuaTypeNamespaceIndex, &structTypeName[0]), oAttr,
    nullptr, &paNodeId);

  if (status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to create OPC UA Struct Type Node for Type %s, Status Code: %s\n", structTypeName.c_str(), UA_StatusCode_name(status));
    return false;
  }
  return true;
}

bool COPC_UA_ObjectStruct_Helper::addOPCUAStructTypeComponents(UA_Server *paServer, UA_NodeId &paParentNodeId, CIEC_STRUCT &paStructType, const std::string &paStructTypeName) {
  const CStringDictionary::TStringId* structMemberNames = paStructType.elementNames();
  for(size_t i = 0; i < paStructType.getStructSize(); i++) {
    CIEC_ANY* structMember = paStructType.getMember(i);
    if(structMember->getDataTypeID() == CIEC_ANY::e_STRUCT) {
      CIEC_STRUCT &memberStruct = static_cast<CIEC_STRUCT&>(structMember->unwrap());
      CActionInfo actionInfo{mLayer, CActionInfo::UA_ActionType::eCreateObject, std::string()};
      UA_NodeId memberTypeNodeId = checkAndCreateOPCUAStructType(actionInfo, memberStruct);
      if(UA_NodeId_equal(&memberTypeNodeId, &UA_NODEID_NULL)) {
        DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to create type of nested Struct member %s for Struct %s\n", CStringDictionary::getInstance().get(structMemberNames[i]),
         CStringDictionary::getInstance().get(paStructType.getTypeNameID()));
        return false;
      }
      if(!addOPCUAStructTypeObjectComponent(paServer, paParentNodeId, paStructTypeName, memberStruct, structMemberNames[i], memberTypeNodeId)) {
        DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to create nested Struct member %s for Struct %s\n", CStringDictionary::getInstance().get(structMemberNames[i]),
          CStringDictionary::getInstance().get(paStructType.getTypeNameID()));
        return false;
      }
      UA_NodeId_clear(&memberTypeNodeId);
    } else {
      if(!addOPCUAStructTypeVariableComponent(paServer, paParentNodeId, paStructTypeName, structMember, structMemberNames[i])) {
        DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to create Struct member %s\n", CStringDictionary::getInstance().get(structMemberNames[i]));
        return false;
      }
    } 
  }
  return true;
}

bool COPC_UA_ObjectStruct_Helper::addOPCUAStructTypeVariableComponent(UA_Server *paServer, UA_NodeId &paParentNodeId, const std::string &paStructName, CIEC_ANY *paStructMember, const CStringDictionary::TStringId paStructMemberNameId) {
  std::string structMemberName = CStringDictionary::getInstance().get(paStructMemberNameId);
  UA_VariableAttributes vAttr = UA_VariableAttributes_default;
    vAttr.displayName = UA_LOCALIZEDTEXT(smEmptyString, &structMemberName[0]);
    vAttr.valueRank = UA_VALUERANK_SCALAR;
    vAttr.minimumSamplingInterval = 0.000000;
    vAttr.userAccessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    vAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    vAttr.dataType = COPC_UA_Helper::getOPCUATypeFromAny(*paStructMember)->typeId;

  UA_NodeId memberNodeId;
  if(paParentNodeId.identifierType == UA_NODEIDTYPE_STRING) {
    std::string memberBrowsePathStr = getMemberBrowsePath(paStructName, structMemberName);
    memberNodeId = UA_NODEID_STRING_ALLOC(mOpcuaTypeNamespaceIndex, memberBrowsePathStr.c_str());
  } else {
    memberNodeId = UA_NODEID_NUMERIC(mOpcuaTypeNamespaceIndex, 0);
  }
  UA_StatusCode status = UA_Server_addVariableNode(paServer, memberNodeId, paParentNodeId,
    UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
    UA_QUALIFIEDNAME(mOpcuaTypeNamespaceIndex, &structMemberName[0]),
    UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vAttr, nullptr, nullptr);

  UA_NodeId_clear(&memberNodeId);
  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to add Variable Member to OPC UA Struct Type Node for Member %s, Status Code: %s\n", structMemberName.c_str(), UA_StatusCode_name(status));
    return false;
  }
  return true;
}

bool COPC_UA_ObjectStruct_Helper::addOPCUAStructTypeObjectComponent(UA_Server *paServer, UA_NodeId &paParentNodeId, const std::string &paStructName, CIEC_STRUCT &paStructMember, 
  const CStringDictionary::TStringId paStructMemberNameId, UA_NodeId &paMemberTypeNodeId) {
  std::string structMemberName = CStringDictionary::getInstance().get(paStructMemberNameId);
  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT(smEmptyString, &structMemberName[0]);
  UA_NodeId objectNodeId;
  std::string objectBrowsePath = structMemberName;
  if(paParentNodeId.identifierType == UA_NODEIDTYPE_STRING) {
    objectBrowsePath = getStructMemberBrowsePath(paStructName, paStructMemberNameId);
    objectNodeId = UA_NODEID_STRING_ALLOC(mOpcuaTypeNamespaceIndex, objectBrowsePath.c_str());
  } else {
    objectNodeId = UA_NODEID_NUMERIC(mOpcuaTypeNamespaceIndex, 0);
  }
  UA_StatusCode status = UA_Server_addObjectNode(paServer, objectNodeId, paParentNodeId, 
    UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), 
    UA_QUALIFIEDNAME(mOpcuaTypeNamespaceIndex, &structMemberName[0]),
    paMemberTypeNodeId, oAttr, nullptr, nullptr);

  if(status != UA_STATUSCODE_GOOD) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to add Object Member to OPC UA Struct Type Node for Member %s, Status Code: %s\n", structMemberName.c_str(), UA_StatusCode_name(status));
    return false;
  }
  if(!addOPCUAStructTypeComponents(paServer, objectNodeId, paStructMember, objectBrowsePath)) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to add members of Object member %s\n", structMemberName.c_str());
    return false;
  }
  UA_NodeId_clear(&objectNodeId);
  return true;
}

forte::com_infra::EComResponse COPC_UA_ObjectStruct_Helper::createObjectNode(CActionInfo& paActionInfo, CIEC_STRUCT &paStructType) {
  EComResponse response = e_InitTerminated;
  std::string browsePath = paActionInfo.getNodePairInfo().begin()->getBrowsePath();
  CActionInfo::CNodePairInfo nodePair(nullptr, browsePath);
  if(!isOPCUAObjectPresent(nodePair)) {
    mCreateNodeActionInfo = getCreateObjectActionInfo(paActionInfo, browsePath, paStructType);
    if( (UA_STATUSCODE_GOOD != mHandler->initializeAction(*mCreateNodeActionInfo)) || (UA_STATUSCODE_GOOD != mHandler->executeAction(*mCreateNodeActionInfo)) ) {
      return response;
    }
  } else {
    if(paActionInfo.getNodePairInfo().begin()->getNodeId() != nullptr) {
      mOpcuaObjectNamespaceIndex = paActionInfo.getNodePairInfo().begin()->getNodeId()->namespaceIndex;
    }
  }
  return initializeMemberAction(paActionInfo, browsePath, paStructType);
}

CIEC_ANY const *COPC_UA_ObjectStruct_Helper::getStructMember(CActionInfo &paActionInfo, bool paIsSD) {
  CIEC_ANY** apoDataPorts = paIsSD ? mLayer.getCommFB()->getSDs() : mLayer.getCommFB()->getRDs();
  CIEC_STRUCT& structType = static_cast<CIEC_STRUCT&>(apoDataPorts[0]->unwrap());
  const std::string actionBrowsePath = paActionInfo.getNodePairInfo().begin()->getBrowsePath();

  for(size_t i = 0; i < mStructMemberActionInfos.size(); i++) {
    std::shared_ptr<CActionInfo> actionInfo = mStructMemberActionInfos[i];
    std::string browsePath = actionInfo->getNodePairInfo().begin()->getBrowsePath();
    if(browsePath == actionBrowsePath) {
      return structType.getMember(i);
    }
  }
  return nullptr;
}

forte::com_infra::EComResponse COPC_UA_ObjectStruct_Helper::executeStructAction() {
  for(std::shared_ptr<CActionInfo> actionInfo : mStructMemberActionInfos) {
    if(UA_STATUSCODE_GOOD != mHandler->executeAction(*actionInfo)) {
      return e_ProcessDataSendFailed;
    }
  }
  return e_ProcessDataOk;
}

int COPC_UA_ObjectStruct_Helper::getRDBufferIndexFromNodeId(const UA_NodeId *paNodeId) {
  for(size_t i = 0; i < mStructMemberActionInfos.size(); i++) {
    std::shared_ptr<CActionInfo> actionInfo = mStructMemberActionInfos[i];
    auto *nodeId = actionInfo->getNodePairInfo().begin()->getNodeId();
    if(UA_NodeId_equal(nodeId, paNodeId)) {
      return (int)i;
    }
  }
  return -1;
}

void COPC_UA_ObjectStruct_Helper::setMemberValues(CIEC_ANY** paRDs, const std::vector<std::unique_ptr<CIEC_ANY>>& paRDBuffer) {
  CIEC_STRUCT& structType = static_cast<CIEC_STRUCT&>(paRDs[0]->unwrap());
  for(size_t i = 0; i < structType.getStructSize(); i++) {
    structType.getMember(i)->setValue(*paRDBuffer[i]);
  }
}

std::vector<std::unique_ptr<CIEC_ANY>> COPC_UA_ObjectStruct_Helper::initializeRDBuffer() {
  CIEC_ANY** rds = mLayer.getCommFB()->getRDs();
  CIEC_STRUCT& structType = static_cast<CIEC_STRUCT&>(rds[0]->unwrap());
  const size_t structSize = structType.getStructSize();
  std::vector<std::unique_ptr<CIEC_ANY>> RDBuffer;;
  for(size_t i = 0; i < structSize; i++) {
    RDBuffer.emplace_back(structType.getMember(i)->clone(nullptr));
  }
  return RDBuffer;
}

void COPC_UA_ObjectStruct_Helper::deleteRDBufferEntries(forte::com_infra::CBaseCommFB &paCommFB, std::vector<std::unique_ptr<CIEC_ANY>>& paRDBuffer) {
  if(paCommFB.getComServiceType() == e_Subscriber) {
    paRDBuffer.clear();
  }
}

bool COPC_UA_ObjectStruct_Helper::isStructType(const COPC_UA_Layer &paLayer, bool paIsPublisher) {
  TPortId nrOfPorts = paIsPublisher ? paLayer.getCommFB()->getNumSD() : paLayer.getCommFB()->getNumRD();
  CIEC_ANY** apoDataPorts = paIsPublisher ? paLayer.getCommFB()->getSDs() : paLayer.getCommFB()->getRDs();
  return nrOfPorts > 0 && CIEC_ANY::e_STRUCT == apoDataPorts[0]->unwrap().getDataTypeID();
}

std::shared_ptr<CActionInfo> COPC_UA_ObjectStruct_Helper::getCreateObjectActionInfo(CActionInfo& paActionInfo, std::string &paBrowsePath, CIEC_STRUCT &paStructType) {
  std::shared_ptr<CActionInfo> actionInfo = std::make_shared<CActionInfo>(mLayer, CActionInfo::UA_ActionType::eCreateObject, paActionInfo.getEndpoint());
  std::string typeBrowsePath(getStructBrowsePath(smStructTypesBrowsePath, paStructType.getTypeNameID()));
  auto& nodePairs = actionInfo->getNodePairInfo();
  nodePairs.emplace_back(nullptr, typeBrowsePath);
  bool isNodeIdPresent = paActionInfo.getNodePairInfo().begin()->getNodeId() != nullptr;
  UA_NodeId *nodeId = nullptr; 
  if(!isNodeIdPresent) {
    nodeId = createStringNodeIdFromBrowsepath(paBrowsePath);
  } else {
    nodeId = UA_NodeId_new();
    UA_NodeId_copy(paActionInfo.getNodePairInfo().begin()->getNodeId(), nodeId);
  }
  mOpcuaObjectNamespaceIndex = nodeId->namespaceIndex;
  nodePairs.emplace_back(nodeId, paBrowsePath);
  return actionInfo;
}

forte::com_infra::EComResponse COPC_UA_ObjectStruct_Helper::initializeMemberAction(CActionInfo& paActionInfo, std::string &paBrowsePath, CIEC_STRUCT &paStructType) {
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  if(!localHandler) {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to get LocalHandler because LocalHandler is null!\n");
    return e_InitTerminated;
  }
  const CStringDictionary::TStringId* structMemberNames = paStructType.elementNames();
  bool isNodeIdPresent = paActionInfo.getNodePairInfo().begin()->getNodeId() != nullptr;

  for(size_t i = 0; i < paStructType.getStructSize(); i++) {
    std::string memberBrowsePath(getStructMemberBrowsePathWithNSIndex(paBrowsePath, structMemberNames[i]));

    std::shared_ptr<CActionInfo> actionInfo = std::make_shared<CStructMemberActionInfo>(*this, mLayer, paActionInfo.getAction(), paActionInfo.getEndpoint());
    CIEC_ANY* memberVariable = paStructType.getMember(i);
    UA_NodeId* nodeId = nullptr;
    if(!isNodeIdPresent) {    
      nodeId = createStringNodeIdFromBrowsepath(memberBrowsePath);
    }
    actionInfo->getNodePairInfo().emplace_back(nodeId, memberBrowsePath);
    if(UA_STATUSCODE_GOOD != localHandler->initializeActionForObjectStruct(actionInfo, *memberVariable)) {
      DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Error occured in FB %s while initializing Struct member %s\n", mLayer.getCommFB()->getInstanceName(),
      CStringDictionary::getInstance().get(structMemberNames[i]));
      return e_InitTerminated;
    }
    mStructMemberActionInfos.push_back(std::move(actionInfo));
  }
  return e_InitOk;
}

bool COPC_UA_ObjectStruct_Helper::isOPCUAObjectPresent(CActionInfo::CNodePairInfo &paNodePair) {
  COPC_UA_Local_Handler* localHandler = static_cast<COPC_UA_Local_Handler*>(mHandler);
  if(localHandler) {
    bool retVal = localHandler->isOPCUAObjectPresent(paNodePair);;
    return retVal;
  } else {
    DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to get LocalHandler because LocalHandler is null!\n");
  }
  return false;
}

void COPC_UA_ObjectStruct_Helper::checkOPCUANamespace() {
  CIEC_WSTRING* configPort = static_cast<CIEC_WSTRING*>(mLayer.getCommFB()->getResource()->getDataInput(g_nStringIdOPCUA_Namespace));
  if(configPort && configPort->length() > 0) {
    if(!createOPCUANamespace(configPort->getValue())) {
      DEVLOG_ERROR("[OPC UA OBJECT STRUCT HELPER]: Failed to create OPC UA Namespace with value: %s", configPort->getValue());
    }
  }
}

UA_NodeId *COPC_UA_ObjectStruct_Helper::createStringNodeIdFromBrowsepath(const std::string &paBrowsePath) {
  UA_NodeId *newNodeId = UA_NodeId_new();
  UA_NodeId_init(newNodeId);
  newNodeId->namespaceIndex = getNamespaceIndexFromBrowsepath(paBrowsePath);
  newNodeId->identifierType = UA_NODEIDTYPE_STRING;
  newNodeId->identifier.string = UA_String_fromChars(removeNamespaceIndicesFromBrowsePath(paBrowsePath).c_str());
  return newNodeId;
}

UA_UInt16 COPC_UA_ObjectStruct_Helper::getNamespaceIndexFromBrowsepath(const std::string &paBrowsePath) {
  CParameterParser mainParser(paBrowsePath.c_str(), '/');
  size_t parsingResult = mainParser.parseParameters();
  if(parsingResult > 0) {
    size_t elementNameIndex = strcmp("", mainParser[parsingResult-1]) != 0 ? parsingResult-1 : parsingResult-2;
    std::string objectName(mainParser[elementNameIndex]);
    CParameterParser nsIndexParser(objectName.c_str(), ':');
    parsingResult = nsIndexParser.parseParameters();
    if(parsingResult > 1) {
      return static_cast<UA_UInt16>(forte::core::util::strtoul(nsIndexParser[0], nullptr, 10));
    }
  } else {
    DEVLOG_ERROR("[OPC UA HELPER]: Error while parsing FB browse path %s\n", paBrowsePath.c_str());
  }
  return COPC_UA_Local_Handler::scmDefaultBrowsenameNameSpace;
}

std::string COPC_UA_ObjectStruct_Helper::removeNamespaceIndicesFromBrowsePath(const std::string &paBrowsePath) {
  std::stringstream ss;
  CParameterParser mainParser(paBrowsePath.c_str(), '/');
  size_t mainParserLength = mainParser.parseParameters();
  for(size_t i = 0; i < mainParserLength; i++) {
    std::string nodePair(mainParser[i]);
    if(!nodePair.empty()) {
      CParameterParser nsIndexParser(nodePair.c_str(), ':');
      size_t parserLength = nsIndexParser.parseParameters();
      size_t browsePathIndex = parserLength > 1 ? 1 : 0;
      ss << '/' << nsIndexParser[browsePathIndex];
    }
  }
  return ss.str();
}

std::string COPC_UA_ObjectStruct_Helper::getStructBrowsePath(const std::string &paPathPrefix, CStringDictionary::TStringId paStructNameId) {
  std::string structTypeName(CStringDictionary::getInstance().get(paStructNameId));
  return getBrowsePath(paPathPrefix, structTypeName, mOpcuaTypeNamespaceIndex);
}

std::string COPC_UA_ObjectStruct_Helper::getBrowsePath(const std::string &paPathPrefix, const std::string &paObjectName, UA_UInt16 paNamespaceIndex) {
  if(paObjectName.empty()) {
    return std::string();
  }
  std::stringstream ss;
  char buf[1000];
  snprintf(buf, sizeof(buf), paPathPrefix.c_str(), paNamespaceIndex);
  ss << buf << paObjectName;
  return ss.str();
}


std::string COPC_UA_ObjectStruct_Helper::getStructMemberBrowsePathWithNSIndex(const std::string &paBrowsePathPrefix, const CStringDictionary::TStringId structMemberNameId) {
  std::stringstream ss;
  char buf[100];
  snprintf(buf, sizeof(buf), smMemberNamespaceIndex.c_str(), mOpcuaObjectNamespaceIndex);
  ss << paBrowsePathPrefix << buf << CStringDictionary::getInstance().get(structMemberNameId);
  return ss.str();
}

std::string COPC_UA_ObjectStruct_Helper::getMemberBrowsePath(const std::string &paBrowsePathPrefix, const std::string &paMemberName) {
  std::stringstream ss;
  ss << paBrowsePathPrefix << "/" << paMemberName;
  return ss.str();
}

std::string COPC_UA_ObjectStruct_Helper::getStructTypeName(bool paIsPublisher) {
  CIEC_ANY* type = paIsPublisher ? mLayer.getCommFB()->getSDs()[0] : mLayer.getCommFB()->getRDs()[0];
  return (type != nullptr) ? std::string(CStringDictionary::getInstance().get(type->unwrap().getTypeNameID())) : std::string();
}
