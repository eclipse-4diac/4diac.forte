/*******************************************************************************
 * Copyright (c) 2015, 2023 Florian Froschermeier <florian.froschermeier@tum.de>,
 *                          fortiss GmbH, Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Florian Froschermeier
 *      - initial integration of the OPC-UA protocol
 *    Stefan Profanter
 *      - refactoring and adaption to new concept
 *    Jose Cabral:
 *      - refactoring to cleaner architecture
 *    Martin Melik Merkumians:
 *      - Change CIEC_STRING to std::string
 *    Markus Meingast:
 *      - Add support for Object Structs
 *******************************************************************************/

#ifndef SRC_MODULES_OPC_UA_OPCUALOCALHANDLER_H_
#define SRC_MODULES_OPC_UA_OPCUALOCALHANDLER_H_

#include <forte_thread.h>
#include <conn.h>
#include <forte_sem.h>
#include <forte_sync.h>
#include "../../core/fortelist.h"
#include "opcua_handler_abstract.h"
#include "opcua_helper.h"
#include <string>

/**
 * Class to handle all action that are executed on a local OPC UA server
 */
// cppcheck-suppress noConstructor
class COPC_UA_Local_Handler : public COPC_UA_HandlerAbstract, public CThread {
  DECLARE_HANDLER(COPC_UA_Local_Handler)
  public:
    /**
     * Starts OPC UA Server
     */
    void enableHandler() override;

    /**
     * Stops the OPC UA server
     */
    void disableHandler() override;

    /**
     * Class containing all local callback functions that are called by the OPC UA stack
     */
    class CUA_LocalCallbackFunctions {
      public:
        /**
         * Callback when a method in the OPC UA server was executed
         */
        static UA_StatusCode onServerMethodCall(UA_Server *paServer, const UA_NodeId *paSessionId, void *paSessionContext, const UA_NodeId *paMethodId,
            void *paMethodContext, const UA_NodeId *paObjectId, void *paObjectContext, size_t paInputSize, const UA_Variant *paInput, size_t paOutputSize,
            UA_Variant *paOutput);

        /**
         * Callback when an external client writes to a variable on this server.
         */
        static void onWrite(UA_Server *paServer, const UA_NodeId *paSessionId, void *paSessionContext, const UA_NodeId *paNodeId, void *paNodeContext,
            const UA_NumericRange *paRange, const UA_DataValue *paData);
    };

    UA_Server* getUAServer() {
      return mUaServer;
    }

    /**
     * Check if Struct is present in OPC UA server
     * @param paNodePair The NodePair of the Object Node to be looked for
     * @return true, if the Object Node exists, false otherwise
    */
    bool isOPCUAObjectPresent(CActionInfo::CNodePairInfo &paNodePair);

    /**
     * Perform initialization of the action for an Object Struct
     * @param paActionInfo Action to be initialized
     * @return UA_STATUSCODE_GOOD if no problem occurred, other value otherwise
     */
    UA_StatusCode initializeActionForObjectStruct(std::shared_ptr<CActionInfo> &paActionInfo, CIEC_ANY &paMember);

    /**
     * Default value for the namespace of the browsename for all created nodes
     */
    static const UA_UInt16 scmDefaultBrowsenameNameSpace = 1;

  protected:

    /**
     * Perform all the needed initialization of the action
     * @param paActionInfo Action to be initialized
     * @return UA_STATUSCODE_GOOD if no problem occurred, other value otherwise
     */
    UA_StatusCode initializeAction(CActionInfo &paActionInfo) override;

    /**
     * Execute the action
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD if no problem occurred, other value otherwise
     */
    UA_StatusCode executeAction(CActionInfo &paActionInfo) override;

    /**
     * Uninitialize the action
     * @param paActionInfo Action to be Uninitialized
     * @return UA_STATUSCODE_GOOD if no problem occurred, other value otherwise
     */
    UA_StatusCode uninitializeAction(CActionInfo &paActionInfo) override;


  private:

    /**
     * Overridden run() from CThread which loops the UA Server.
     */
    void run() override;

    /**
     * Starts the OPC UA server, if it is not already running
     */
    void startServer();

    /**
     * Indicates that the server has started, and allow waiting threads to work on it
     */
    CSemaphore mServerStarted;

    /**
     * Stops the OPC UA server
     */
    void stopServer();

    /**
     * Structure to contain all needed strings to configure the server
     */
    struct UA_ServerStrings {
        std::string mHostname;
        std::string mAppURI;
#ifdef FORTE_COM_OPC_UA_MULTICAST
        std::string mMdnsServerName;
#endif //FORTE_COM_OPC_UA_MULTICAST
    };

    /**
     * Generate the hostname and the application URI that will be used to configure the server
     * @param paUAServerPort Port where the OPC UA server will listen
     * @param paServerStrings Place to store the generated strings
     */
    void generateServerStrings(TForteUInt16 paUAServerPort, UA_ServerStrings &paServerStrings) const;
    
    /**
     *  Creates the configuration for the OPC UA Server.
     * @param paServerStrings Strings needed to configure the server
     * @param paUaServerConfig Place to store all the configurations
     */
    void configureUAServer(UA_ServerStrings &paServerStrings, UA_ServerConfig &paUaServerConfig) const;

    /**
     * Handler of the OPC UA stack server
     */
    UA_Server *mUaServer;

    /**
     * Maximal length for the server name
     */
    static const size_t scmMaxServerNameLength = 255;

    /**
     * Generated function that call the initialization of all nodespaces added by the user in CMake
     * @param paUaServer OPC UA Server
     * @return True if no error occurred, false otherwise
     */
    bool initializeNodesets(UA_Server &paUaServer);

    /**
     * Map to know which actions are using which nodes. When an action is unitialized, this is checked
     * to see if the nodeId still has some action using it. If not, then it can be safely deleted
     */
    struct nodesReferencedByActions {
        const UA_NodeId *mNodeId;
        std::vector<CActionInfo*> mActionsReferencingIt;
    };

    /**
     * For each node that is accessed by the action, an entry in this list is added
     */
    std::vector<nodesReferencedByActions> mNodesReferences;

    /**
     * For all nodes that an action is referencing, it adds the action as reference
     * @param paNodes Nodes being referenced by the action
     * @param paActionInfo Action referencing the nodes
     */
    void referencedNodesIncrement(const CSinglyLinkedList<UA_NodeId*> &paNodes, CActionInfo &paActionInfo);

    /**
     * Removes the action from the references from all the nodes where it's present
     * @param paActionInfo Action to be removed
     */
    void referencedNodesDecrement(const CActionInfo &paActionInfo);

    /**
     * Looks for all nodes which an action is referencing
     * @param paActionInfo Action to be look for as a reference
     * @param paNodes Place to store the nodes that are referencing the action
     */
    void getNodesReferencedByAction(const CActionInfo &paActionInfo, std::vector<const UA_NodeId*> &paNodes) const;

    /**
     * Parent class that encapsulates the information needed to create something in the OPC UA Stack
     */
    class CCreateInfo {
      public:
        CCreateInfo() :
            mRequestedNodeId(nullptr), mParentNodeId(nullptr), mBrowseName(UA_QualifiedName_new()), mReturnedNodeId(UA_NodeId_new()) {
        }

        virtual ~CCreateInfo() {
          UA_NodeId_delete(mReturnedNodeId);
          UA_QualifiedName_delete(mBrowseName);
        }

        UA_NodeId *mRequestedNodeId;
        const UA_NodeId *mParentNodeId;
        UA_QualifiedName *mBrowseName;
        UA_NodeId *mReturnedNodeId;

        CCreateInfo(const CCreateInfo &other) = delete;
        CCreateInfo& operator=(const CCreateInfo &other) = delete;
    };

    /**
     * Class that encapsulates the information needed to create an object in the OPC UA Stack
     */
    class CCreateObjectInfo : public CCreateInfo {
      public:
        CCreateObjectInfo() :
            CCreateInfo(), mTypeNodeId(nullptr) {
        }

        ~CCreateObjectInfo() override = default;

        UA_NodeId *mTypeNodeId;

        CCreateObjectInfo(const CCreateObjectInfo &paObj) = delete;
        CCreateObjectInfo& operator=(const CCreateObjectInfo &other) = delete;
    };

    /**
     * Class that encapsulates the information needed to create a variable in the OPC UA Stack
     */
    class CCreateVariableInfo : public CCreateInfo {
      public:
        CCreateVariableInfo() :
            CCreateInfo(), mTypeConvert(nullptr), mInitData(nullptr), mAllowWrite(false), mVariableTypeNodeId(nullptr) {

        }

        ~CCreateVariableInfo() override = default;

        const UA_DataType *mTypeConvert;
        const CIEC_ANY *mInitData;
        bool mAllowWrite;
        UA_NodeId *mVariableTypeNodeId;

        CCreateVariableInfo(const CCreateVariableInfo &paObj) = delete;
        CCreateVariableInfo& operator=(const CCreateVariableInfo &other) = delete;
    };

    /**
     * Class that encapsulates the information needed to create a method in the OPC UA Stack
     */
    class CCreateMethodInfo : public CCreateInfo {
      public:
        explicit CCreateMethodInfo(CLocalMethodInfo &paCallack) :
            CCreateInfo(), mInputArguments(nullptr), mOutputArguments(nullptr), mLocalMethodInfo(paCallack), mInputSize(0), mOutputSize(0) {

        }
        ~CCreateMethodInfo() override {
          UA_Array_delete(mInputArguments, mInputSize, &UA_TYPES[UA_TYPES_ARGUMENT]);
          UA_Array_delete(mOutputArguments, mOutputSize, &UA_TYPES[UA_TYPES_ARGUMENT]);
        }

        UA_Argument *mInputArguments;
        UA_Argument *mOutputArguments;
        CLocalMethodInfo &mLocalMethodInfo;
        size_t mInputSize;
        size_t mOutputSize;

        CCreateMethodInfo(CCreateMethodInfo &other) = delete;
        CCreateMethodInfo& operator=(const CCreateMethodInfo &other) = delete;
    };

    /**
     * Takes care of the requested nodeId, parent nodeId and the browsename to be given to the new created object/method/variable.
     * The critical part is the browsename, since it can be given with the namespace using a semicolon (e.g. /Objects/1:myPath/), so
     * this function handles this case
     * @param paNodeName Nodename given by the user in the parameters of the action
     * @param paNodePairInfo Information containing the requested node ID
     * @param paParentNodeId Information containing the parent node ID
     * @param paResult Place to store the results
     */
    void initializeCreateInfo(std::string &paNodeName, const CActionInfo::CNodePairInfo &paNodePairInfo, const UA_NodeId *paParentNodeId,
        CCreateInfo &paResult) const;

    /**
     * Context passed to a variable node in the OPC UA stack, which is returned when the variable is written from a client.
     * ATTENTION: this is exactly the same class as the one used for subscription in the client (UA_SubscribeContext_Handle),
     * but because of compilation errors occurred when including headers, it was copied, since no right place could be found where to
     * declare/define this class. If someone can manage to use the same class both in the CUA_ClientInformation and here, it can be deleted
     */
    struct UA_VariableContext_Handle {
        UA_VariableContext_Handle(CActionInfo &paActionInfo, size_t paPortIndex) :
            mActionInfo(paActionInfo), mPortIndex(paPortIndex) {
        }

        //default copy constructor should be enough

        bool operator==(UA_VariableContext_Handle const &paRightObject) const {
          return (&mActionInfo == &paRightObject.mActionInfo && mPortIndex == paRightObject.mPortIndex);
        }

        CActionInfo &mActionInfo;
        size_t mPortIndex;
    };

    /**
     * List for callback handles to be able to clean them up on destroy.
     */
    CSinglyLinkedList<UA_VariableContext_Handle> mNodeCallbackHandles;

    /**
     * Mutex used to avoid many threads (Resources) to access the server
     */
    CSyncObject mServerAccessMutex;

    /**
     * Semaphore to tell the server it needs iteration
     */
    CSemaphore mServerNeedsIteration;

    /**
     * The minimum time the iteration loop must wait when no interrupted
     */
    static const UA_UInt16 scmMinimumIterationWaitTime = 1;

    /**
     * This class is used to store who is the parent of each method. This need comes from the fact when creating objects that have methods,
     * the method nodeId of every instance is the same as the method nodeID of the Object type. We can then use a CREATE_METHOD action pointing to this instance of the method,
     * (let's call it "reference CREATE_METHOD") but there's no way of setting a specific context (in our case, a CLocalMethodInfo) that is returned in the callback, because the
     * OPC UA API ask just for nodeID of the node when setting the context (and as said before, all methods instances share the same nodeId).
     * We can set the context for methods that are created directly (no "reference CREATE_METHOD"), but for keeping the context the same for all kind of methods,
     * in those cases, we also store the information using this class
     */
    class UA_ParentNodeHandler {
      public:
        UA_ParentNodeHandler(const UA_NodeId &paParentNodeId, UA_NodeId *paMethodNodeId, CLocalMethodInfo &paActionInfo) :
            mParentNodeId(UA_NodeId_new()), mMethodNodeId(paMethodNodeId), mActionInfo(paActionInfo) {
          UA_NodeId_copy(&paParentNodeId, mParentNodeId);
        }
        ~UA_ParentNodeHandler() {
          UA_NodeId_delete(mParentNodeId);
        }

        UA_ParentNodeHandler(const UA_ParentNodeHandler &other) :
            mParentNodeId(UA_NodeId_new()), mMethodNodeId(other.mMethodNodeId), mActionInfo(other.mActionInfo) {
          UA_NodeId_copy(other.mParentNodeId, mParentNodeId);
        }

        UA_NodeId *mParentNodeId;
        UA_NodeId *mMethodNodeId;
        CLocalMethodInfo &mActionInfo;

        UA_ParentNodeHandler& operator=(const UA_ParentNodeHandler &other) = delete;
    };

    /**
     * The list of parent/method information of the used methods
     */
    CSinglyLinkedList<UA_ParentNodeHandler> mMethodsContexts;

    /**
     * Initialization of read and write of variables. It handles both existing and non-existing cases
     * @param paActionInfo Action to be initialized
     * @param paWrite True if the action is to write a variable, false if it's for reading
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode initializeVariable(CActionInfo &paActionInfo, bool isWrite);

    /**
     * Initialization of read and write of Object Struct member variables. It handles both existing and non-existing cases
     * @param paActionInfo Action to be initialized
     * @param paMember The member to be initialized
     * @param paWrite True if the action is to write a variable, false if it's for reading
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode initializeObjectStructMemberVariable(std::shared_ptr<CActionInfo> &paActionInfo, CIEC_ANY *paMember, bool paWrite);

    /**
     * When an action refers to variable that already exist in the OPC UA server, another variable shouldn't be created. If you are trying to read a variable
     * that has already another FB reading from it, it will fail. If the variable was created as a write, by reading it, it will set the writing permission
     * to the variable and set the action as a callback context
     * @param paActionInfo Action accessing the existing variable
     * @param paNodePairInfo Information about the variable being accessed
     * @param paVariable Variable to check the type
     * @param paIndexOfNodePair Information about on which RD the variable will be read
     * @param paWrite True if the action is to write a variable, false if it's for reading
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode handleExistingVariable(CActionInfo &paActionInfo, CActionInfo::CNodePairInfo &paNodePairInfo, const CIEC_ANY &paVariable,
        size_t paIndexOfNodePair, bool paWrite);

    /**
     * Creates the variable in the OPC UA server. If the folders in the path to the variable don't exist, it will create them with random nodeIds
     * @param paActionInfo Action creating the variable
     * @param paNodePairInfo Information about the variable node being created
     * @param paVariable Variable to get the type from
     * @param paIndexOfNodePair Information about which RD/SD should be used to read/write the variable
     * @param paReferencedNodes Place to store the nodes being references by the action (the variable node and folders)
     * @param paWrite True if the action is to write a variable, false if it's for reading
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode handleNonExistingVariable(CActionInfo &paActionInfo, CActionInfo::CNodePairInfo &paNodePairInfo, const CIEC_ANY &paVariable,
        size_t paIndexOfNodePair, CSinglyLinkedList<UA_NodeId*> &paReferencedNodes, bool paWrite);

    /**
     * Creates a variable in the OPC UA server using directly the API from the passed information
     * @param paCreateVariableInfo Information needed to create the variable
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode createVariableNode(const CCreateVariableInfo &paCreateVariableInfo);

    /**
     * Update a variable node value from a IEC61499 data object.
     * @param paNodeId Node Id of the node to be updated
     * @param paData Source data for the new value
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode updateNodeValue(const UA_NodeId &paNodeId, const CIEC_ANY *paData);

    /**
     * Register the onWrite function as callback routine when a variable is written and also the context that is passed back
     * @param paNodeId Node ID of the node where to register the callback function and context
     * @param paActionInfo The action executing the register
     * @param paPortIndex Which RD is requesting the callback
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode
    registerVariableCallBack(const UA_NodeId &paNodeId, CActionInfo &paActionInfo, size_t paPortIndex);

    /**
     * Adds write permission to a node
     * @param paNodeId Node Id of the node to add write permission
     * @return  UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode addWritePermission(const UA_NodeId &paNodeId);

    /**
     * Perform all the needed initialization of the create method action
     * @param paActionInfo Action to be initialized
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode initializeCreateMethod(CActionInfo &paActionInfo);

    /**
     * When an action references a method that already exists in the OPC UA server, it checks that another action is no already referencing it,
     * and if that's the case, it stores the information about the parent.
     * @param paActionInfo The action referencing the existing method
     * @param paParentNode Parent node of the method. For methods instances of an object, the node id of the methods is the same, only the parent is different
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode handleExistingMethod(CActionInfo &paActionInfo, const UA_NodeId &paParentNode);

    /**
     * Create the arguments for a method from the information of the action and store it in the encasulation for creating a method
     * @param paActionInfo Action containing information about the arguments characteristics
     * @param paCreateMethodInfo Place to store the created arguments
     */
    void createMethodArguments(CActionInfo &paActionInfo, CCreateMethodInfo &paCreateMethodInfo) const;

    /**
     * Creates a method node in the OPC UA server using directly the API from the passed information
     * @param paMethodInfo Information needed to create the method node
     * @param paNodeId Place to store the node id of the created method
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode createMethodNode(CCreateMethodInfo &paMethodInfo, UA_NodeId **paNodeId);

    /**
     * Perform all the needed initialization of the create node action
     * @param paActionInfo Action to be initialized
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode initializeCreateNode(CActionInfo &paActionInfo) const;

    /**
     * Perform all the needed initialization of the delete object action
     * @param paActionInfo Action to be initialized
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode initializeDeleteNode(const CActionInfo &paActionInfo) const;

    /**
     * Execute the write action to a local variable
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode executeWrite(CActionInfo &paActionInfo);

    /**
     * When the FB of the local method is triggered to signalize the end of the method, this function is called
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode executeCreateMethod(CActionInfo &paActionInfo);

    /**
     * Creates an object in the local server
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode executeCreateObject(CActionInfo &paActionInfo);

    /**
     * Creates a variable of specified type in the local server
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode executeCreateVariable(CActionInfo &paActionInfo);

    /**
     * Creates an object in the OPC UA server using directly the API from the passed information
     * @param paCreateObjectInfo Information needed to create the object
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode createObjectNode(const CCreateObjectInfo &paCreateObjectInfo) const;

    /**
     * Checks if a node, specified in node pair info, exists in the local server
     * @param paNodePairInfo Information about the Node Type
     * @return True if it exists, false otherwise
     */
    bool isNodePresent(CActionInfo::CNodePairInfo &paNodePairInfo);

    /**
     * Deletes an object from the local server
     * @param paActionInfo Action to be executed
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode executeDeleteObject(CActionInfo &paActionInfo);

    /**
     * Looks for a node in the local OPC UA Server. If both the browsepath and NodeId are provided, they should match to consider that the
     * node exists.
     * @param paNodeInfo Information about the node to look for. If no nodeId was provided and the node exist, the node Id of the existing node is stored here
     * @param paFoundNodeIds Place to store the found nodes (folders included). The list is altered only the final node is present
     * @param paIsPresent Place to store true if the node is present in the local server, false otherwise
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode getNode(CActionInfo::CNodePairInfo &paNodeInfo, CSinglyLinkedList<UA_NodeId*> &paFoundNodeIds, bool *paIsPresent);

    /**
     * Execute the TranslateBrowsePathToNodeIds service in the local OPC UA server from a string containing the path
     * @param paBrowsePath Path used to execute the service. Each element of the path is checked
     * @param paBrowsePaths Place to store the request to the service, created from paBrowsePath
     * @param paFoldercount Place to store how many folders were found in the path
     * @param paFirstNonExistingNode Place to store the first non existing node in the path
     * @param paFoundNodeIds Place to store the found node IDs
     * @return  UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode translateBrowseNameAndStore(const char *paBrowsePath, UA_BrowsePath **paBrowsePaths, size_t *paFoldercount, size_t *paFirstNonExistingNode,
        CSinglyLinkedList<UA_NodeId*> &paFoundNodeIds) const;

    /**
     * Store the existing node from a TranslateBrowsePathToNodeIds service in a list of node Ids
     * @param paBrowsePathsResults Results of a TranslateBrowsePathToNodeIds service
     * @param paFolderCnt Size of paBrowsePathsResults
     * @param paFirstNonExistingNode Store to place the first non existing node in paBrowsePathsResults
     * @param paCreatedNodeIds Place to store the existing Node IDs
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode storeAlreadyExistingNodes(const UA_BrowsePathResult *paBrowsePathsResults, size_t paFolderCnt, size_t *paFirstNonExistingNode,
        CSinglyLinkedList<UA_NodeId*> &paCreatedNodeIds) const;

    /**
     * Create folder objects in the OPC UA server from the string. It's assumed that the end node is not present in the path
     * @param paFolders Path of folders
     * @param paCreatedNodeIds Place to store the created nodeIds
     * @return UA_STATUSCODE_GOOD on success, other value otherwise
     */
    UA_StatusCode createFolders(const char *paFolders, CSinglyLinkedList<UA_NodeId*> &paCreatedNodeIds) const;

    /**
     * Splits a browsepath into folders and node name. The non-existing folders are created in the local server
     * @param paBrowsePath Browsepath to be splitted
     * @param paNodeName Place to store the nodename
     * @param paRreferencedNodes List of nodes that are used by this browsename. It will include all folders, but not the end node since it was not created yet
     * @return UA_STATUSCODE_GOOD is no problem occurred, other value otherwise
     */
    UA_StatusCode splitAndCreateFolders(const std::string &paBrowsePath, std::string &paNodeName, CSinglyLinkedList<UA_NodeId*> &paRreferencedNodes) const;

    /**
     * Split a string into folders and node name. The provided place for store of the folder and node name are only
     * changed if the result value is true
     * @param paOriginal String containing the path to be split
     * @param paFolder Place to store the folders part of the string
     * @param paNodeName Place to store the node name part of the string
     * @return True if the provided string is a valid path, false otherwise
     */
    bool splitFoldersFromNode(const std::string &paOriginal, std::string &paFolder, std::string &paNodeName) const;

    /**
     * If paFailed is true, it deletes all NodeIds from paPresentNodes, otherwise it copies them to paReferencedNodes.
     * It's used to handle the NodeIds that been previously allocated, and decide if they should be stored or deleted
     * @param paPresentNodes NodeIds to be analyzed
     * @param paReferencedNodes Place to store the NodeIds if paFailed is true
     * @param paFailed True if the NodeIds should be deleted, false if they need to be copied into paReferencedNodes
     */
    void handlePresentNodes(const CSinglyLinkedList<UA_NodeId*> &paPresentNodes, CSinglyLinkedList<UA_NodeId*> &paReferencedNodes, bool paFailed) const;

    /**
     * Maximum time a local method can take to finish execution without producing an error
     */
    static const size_t scmMethodCallTimeoutInNanoSeconds = static_cast<size_t>(4 * 1E9); //4s

    /**
     * Encapsulation of the information of an external call to a local server
     */
    struct CLocalMethodCall {
        CLocalMethodCall(CLocalMethodInfo &paActionInfo, COPC_UA_Helper::UA_SendVariable_handle &paSendHandle) :
            mActionInfo(paActionInfo), mSendHandle(paSendHandle) {
        }

        //default copy constructor should be enough

        bool operator==(CLocalMethodCall const &rhs) const {
          return this == &rhs;
        }

        CLocalMethodInfo &mActionInfo;
        COPC_UA_Helper::UA_SendVariable_handle &mSendHandle;

    };

    /**
     * List of external method calls currently being executed. This is to allow many external calls in parallalel.
     * TODO: It seems that the OPC UA server cannot execute many calls at the same time. For each call, onServerMethodCall
     * is called which waits for the method to finish before returning, meaning that always only 1 method call can be executed.
     * Check if this is always true, and if yes, the following related functions and variables aren't necessary, and only one
     * CLocalMethodCall is necessary
     */
    CSinglyLinkedList<CLocalMethodCall> mMethodCalls;

    /**
     * Mutex to access mMethodCalls
     */
    CSyncObject mMethodCallsMutex;

    /**
     * Add a method call to the list when onServerMethodCall is called
     * @param paActionInfo Action adding the call
     * @param paHandleRecv Information to later store the results of the method call
     * @return The result added method call
     */
    CLocalMethodCall& addMethodCall(CLocalMethodInfo &paActionInfo, COPC_UA_Helper::UA_SendVariable_handle &paHandleRecv);

    /**
     * Removes a method call from the list when the method is finished
     * @param toDelete Call to remove
     */
    void removeMethodCall(const CLocalMethodCall &toRemove);

    /**
     * Look for the oldest method call of an action
     * @param paActionInfo Action on which the call was triggered
     * @return The method call. 0 if an external call for the action was not triggered
     */
    CLocalMethodCall* getLocalMethodCall(const CLocalMethodInfo &paActionInfo);

    /**
     * English locale used as default for all nodes
     */
    static const char *const mEnglishLocaleForNodes;

    /**
     * Default description for variable nodes
     */
    static const char *const mDefaultDescriptionForVariableNodes;
};

#endif /* SRC_MODULES_OPC_UA_OPCUALOCALHANDLER_H_ */
