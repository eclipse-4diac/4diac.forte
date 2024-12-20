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

#pragma once

#include "opcua_layer.h"
#include <memory>
#include "opcua_action_info.h"

class COPC_UA_HandlerAbstract;

namespace forte {
  namespace com_infra {
    class CBaseCommFB;
  }
}

class COPC_UA_ObjectStruct_Helper {
  public:

    COPC_UA_ObjectStruct_Helper(COPC_UA_Layer &paLayer, COPC_UA_HandlerAbstract *paHandler);

    ~COPC_UA_ObjectStruct_Helper();

    /**
    * Uninitialize ActionInfos of Struct and Struct members
    */
    void uninitializeStruct();

    /**
     * Check that the Struct Object type of the SDs is valid
     * @param paActionInfo The ActionInfo of the request
     * @param paStructType The StructType
     * @return True if Struct Object Type is valid, false otherwise
     */
    bool checkStructTypeConnection(CActionInfo &paActionInfo, CIEC_STRUCT &paStructType);

    /**
     * Create an OPC UA Object Node from Struct Type, if it is not present
     * @param paActionInfo The ActionInfo to create the Object Node from
     * @param paStructType The Struct Type
     * @return e_InitOk if Object Node was created successfully, e_InitTerminated otherwise
    */
    forte::com_infra::EComResponse createObjectNode(CActionInfo& paActionInfo, CIEC_STRUCT &paStructType);

    /**
     * Get Object Struct member from ActionInfo browsepath
     * @param paActionInfo ActionInfo to get the browsepath from
     * @param paIsSD True if the local port is an SD, false otherwise
     * @return The pointer to the member variable
    */
    CIEC_ANY const *getStructMember(CActionInfo &paActionInfo, bool paIsSD);

    /**
     * Execute the action for a Object Node Struct
     * @return e_ProcessDataOK if no problem occurred, other value otherwise
     */
    forte::com_infra::EComResponse executeStructAction();

    /**
     * Get index to the corresponding Object Struct RDBuffer entry from the Node ID
     * @param paNodeId The Node ID
     * @return The index to the corresponding RDBuffer entry
    */
    int getRDBufferIndexFromNodeId(const UA_NodeId *paNodeId);

    /**
     * Set values of Object Struct members from the RDBuffer
     *
     * @param paRDs      the array of data pointers to be sent
     * @param paRDBuffer The buffer for the data
    */
    static void setMemberValues(CIEC_ANY** paRDs, const std::vector<std::unique_ptr<CIEC_ANY>>& paRDBuffer);

    /**
     * Initialize RDBuffer for Object Structs
     * @return The initialized buffer
    */
    std::vector<std::unique_ptr<CIEC_ANY>> initializeRDBuffer();

    /**
     * Delete all entries of the RDBuffer
     *
     * @param paCommFB   The comm fb for which the rdbuffer was created
     * @param paRDBuffer The buffer to be uninitialized
    */
    static void deleteRDBufferEntries(forte::com_infra::CBaseCommFB &paCommFB, std::vector<std::unique_ptr<CIEC_ANY>>& paRDBuffer);

    /**
     * Check if Data Connection is a Struct Type
     * @param paLayer The corresponding OPC UA layer
     * @param paIsPublisher True if the FB is a Publisher, false othewise
     * @return True if connected data type is Struct, false otherwise
    */
    static bool isStructType(const COPC_UA_Layer &paLayer, bool paIsPublisher);

    /**
     * Get the BrowsePath to the OPC UA Object Type
     * @param paPathPrefix The BrowsePath directory with namespace (e.g. /Objects/1:)
     * @param paObjectName The name of the object the BrowsePath refers to
     * @param paNamespaceIndex The Namespace index the type should be in
     */
    static std::string getBrowsePath(const std::string &paPathPrefix, const std::string &paObjectName, UA_UInt16 paNamespaceIndex);

    /**
     * Get the BrowsePath to the OPC UA Object member
     * @param paBrowsePathPrefix BrowsePath to the Struct Object Node
     * @param paMemberName Name of OPC UA Object Member
     */
    static std::string getMemberBrowsePath(const std::string &paBrowsePathPrefix, const std::string &paMemberName);

    /**
     * Creates NodeId of type string from the given browsepath
     * @param paBrowsePath The browsepath of the Object Struct
     * @return The NodeId of type string 
    */
    static UA_NodeId *createStringNodeIdFromBrowsepath(const std::string& paBrowsePath);
    
  private:

    COPC_UA_Layer &mLayer; 
    COPC_UA_HandlerAbstract *mHandler;

    /**
     * OPC UA Object Struct Type Namespace Index.
     * The default NamespaceIndex is 1.
    */
    UA_UInt16 mOpcuaTypeNamespaceIndex;

    /**
     * OPC UA Object Struct Instance Namespace Index.
     * The default NamespaceIndex is 1.
    */
    UA_UInt16 mOpcuaObjectNamespaceIndex;

    /**
     * BrowsePath to folder that contains Object Node Struct Types
     */
     static const std::string smStructTypesBrowsePath;

    /**
     * String representation to the Namespace Index for Object Struct Members
    */
     static const std::string smMemberNamespaceIndex;

     static char smEmptyString[];

    /**
     * ActionInfos of created Struct objects
     */
    std::vector<std::shared_ptr<CActionInfo>> mStructObjectActionInfos;

    /**
     * ActionInfos of Struct member variables 
    */
    std::vector<std::shared_ptr<CActionInfo>> mStructMemberActionInfos;

    /**
     * Check if Object Node Struct is present in OPC UA server
     * @param paNodePair The NodePair of the OPC UA Object Node
     * @return true, if Object Node already exists, false otherwise
    */
    bool isOPCUAObjectPresent(CActionInfo::CNodePairInfo &paNodePair);

    /**
     * Get the ActionInfo to create the OPC UA Object Node for Struct Type.
     * Supports only one connected Struct Type currently
     * @param paActionInfo The ActionInfo to create the Object Node from
     * @param paBrowsePath BrowsePath to the Struct Object Node
     * @param paStructType The Struct Type
     * @return The ActionInfo for creating OPC UA Object Node
    */
    std::shared_ptr<CActionInfo> getCreateObjectActionInfo(CActionInfo &paActionInfo, std::string &paBrowsePath, CIEC_STRUCT &paStructType);


    /**
     * Create a OPC UA Basic Object Type from the Struct Type and Name
     * @param paActionInfo The ActionInfo to create the Object Node from
     * @param paTypeNodeId The NodeId of the new type
     * @param paStructTypeName The name of the Struct Type
     * @param paStructType The Struct Type
     * 
    */
    bool createOPCUAStructType(CActionInfo &paActionInfo, UA_NodeId &paTypeNodeId, const std::string &paStructTypeName, CIEC_STRUCT &paStructType);

    /**
     * Perform initialization for Object Struct Members
     * @param paActionInfo The ActionInfo to create the Object Node from
     * @param paBrowsePath The browsepath to the Object Struct
     * @param paStructType The Struct Type
     * @return e_InitOk if initialization was successful, e_InitTerminated otherwise
     */
    forte::com_infra::EComResponse initializeMemberAction(CActionInfo& paActionInfo, std::string &paBrowsePath, CIEC_STRUCT &paStructType);
    
    /**
     * Check if OPC UA namespace is given by the Resource configuration. 
     * If the configuration is set, change the namespace index. 
     * Otherwise, leave it in default state.
    */
    void checkOPCUANamespace();

    /**
     * Check if OPC UA Struct Type exists and return its NodeId. If it does not exists the Struct Type
     * is created.
     * @param paActionInfo The ActionInfo of the request
     * @param paStructType The StructType
     * @return The NodeId of the OPC UA Struct Type
     */
    UA_NodeId checkAndCreateOPCUAStructType(CActionInfo &paActionInfo, CIEC_STRUCT &paStructType);

    /**
     * Get the BrowsePath to the OPC UA Struct Object Type from the local Struct Type
     * @param paPathPrefix The BrowsePath directory with namespace (e.g. /Objects/1:)
     * @param paStructNameId NameId of the Struct
     */
    std::string getStructBrowsePath(const std::string &paPathPrefix, CStringDictionary::TStringId paStructNameId);

    /**
     * @param paIsPublisher True if the FB is a Publisher, false othewise
    */
    std::string getStructTypeName(bool paIsPublisher);

    /**
     * Get the BrowsePath to the OPC UA Object Struct members from the local Struct Type with the namespace index
     * @param paBrowsePathPrefix BrowsePath to the Struct Object Node
     * @param structMemberNameId Name Id of Object Node Struct member
     */
    std::string getStructMemberBrowsePathWithNSIndex(const std::string &paBrowsePathPrefix, const CStringDictionary::TStringId structMemberNameId);

    /**
     * Creates an OPC UA namespace with the given name and assigns the 
     * namespace index to the mOpcuaTypeNamespaceIndex member variable.
     * @param nsName The name of the OPC UA Namespace
     * @return true if namespace was successfully created or if it already exists, false otherwise
    */
    bool createOPCUANamespace(char* nsName);

    /**
     * Creates OPC UA Struct Type Object Node in Base Object Types folder with the given Struct Type Name
     * @param paServer The OPC UA server
     * @param paNodeId The NodeId to be written
     * @param paStructTypeName The name of the Struct Type
     * @param defaultCase The initialisation case for the NodeId type (true -> String NodeId, false -> Numeric NodeId)
    */
    bool defineOPCUAStructTypeNode(UA_Server *paServer, UA_NodeId &paNodeId, const std::string &paStructTypeName, bool defaultCase);

    /**
     * Creates the members for the OPC UA Struct Type Object Node with the given Struct Member Name
     * @param paServer The OPC UA server
     * @param paParentNodeId The NodeId of the Struct Type Object Node
     * @param paStructName The name of the Struct
     * @param paStructMember The Struct Member
     * @param paStructMemberNameId The id of the Struct Member name
    */
    bool addOPCUAStructTypeComponents(UA_Server *paServer, UA_NodeId &paParentNodeId, CIEC_STRUCT &paStructType, const std::string &paStructTypeName/*UA_Server *paServer, UA_NodeId &paParentNodeId, const std::string &paStructName, CIEC_ANY *paStructMember, const CStringDictionary::TStringId paStructMemberNameId*/);

    /**
     * Creates the member variable for the OPC UA Struct Type Object Node with the given Struct Member Name
     * @param paServer The OPC UA server
     * @param paParentNodeId The NodeId of the Struct Type Object Node
     * @param paStructName The name of the Struct
     * @param paStructMember The Struct Member
     * @param paStructMemberNameId The id of the Struct Member name
    */
    bool addOPCUAStructTypeVariableComponent(UA_Server *paServer, UA_NodeId &paParentNodeId, const std::string &paStructName, CIEC_ANY *paStructMember, const CStringDictionary::TStringId paStructMemberNameId);

    /**
     * Creates the member object for the OPC UA Struct Type Object Node with the given Struct Member Name
     * @param paServer The OPC UA server
     * @param paParentNodeId The NodeId of the Struct Type Object Node
     * @param paStructName The name of the Struct
     * @param paStructMember The Struct Member
     * @param paStructMemberNameId The id of the Struct Member name
     * @param paMemberTypeNodeId The NodeId of the member type
    */
    bool addOPCUAStructTypeObjectComponent(UA_Server *paServer, UA_NodeId &paParentNodeId, const std::string &paStructName, CIEC_STRUCT &paStructMember, 
      const CStringDictionary::TStringId paStructMemberNameId, UA_NodeId &paMemberTypeNodeId);

    /**
     * Returns the namespace index of the Object Struct Instance from the given browsepath
     * @param paBrowsePath The browsepath of the Object Struct
     * @return The namespace index of the Object Struct
    */
    static UA_UInt16 getNamespaceIndexFromBrowsepath(const std::string& paBrowsePath);

    /**
     * Removes any present namespace indices from the browsepath.
     * @param paBrowsePath The browsepath of the Object Struct
     * @return The browsepath without any namespace indices
    */
    static std::string removeNamespaceIndicesFromBrowsePath(const std::string& paBrowsePath);
};
