/*******************************************************************************
 * Copyright (c) 2005 - 2018 ACIN, Profactor GmbH, fortiss GmbH, Johannes Kepler University
 *               2022 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Rene Smodic, Thomas Strasser, Gerhard Ebenhofer, Ingo Hegny,
 *      - initial implementation and rework communication infrastructure
 *    Martin Jobst - add CTF tracing integration
 *******************************************************************************/
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <utility>

#include "ecet.h"
#include "fbcontainer.h"
#include "funcbloc.h"
#include "forte_sync.h"

#ifdef FORTE_SUPPORT_MONITORING
#include "monitoring.h"
#endif

#ifdef FORTE_DYNAMIC_TYPE_LOAD
class CLuaEngine;
#endif

#ifdef FORTE_TRACE_CTF
#include "tracerConfig.h"
#endif

class CInterface2InternalDataConnection;

/*! \ingroup CORE\brief Base class for all resources handling the reconfiguration management within this
 * resource and the background execution of event chains.
 *
 */
class CResource : public CFunctionBlock{

  public:
    /*! \brief The main constructor for a resource.
     *
     * The resource can only be generated with a given device the resource is contained. A resource can not exist outside of an device.
     *  \param paDevice           the device the resource is contained in
     *  \param paInterfaceSpec   interface-specification of resource
     *  \param paInstanceNameId    StringId of instance-name
     *  \param paObjectHandler    reference to object handler
     *  \param paFBData           Byte-array for resource-specific data
     */
    CResource(forte::core::CFBContainer &paDevice, const SFBInterfaceSpec& paInterfaceSpec, CStringDictionary::TStringId paInstanceNameId);

    ~CResource() override;

    bool initialize() override;

    /*!\brief Execute the given management command
     *
     * Evaluates the mDestination parameter of the command if empty the resource tries
     * to execute the management command if not it tries to apply the mgm command to a
     * contained FB if possible.
     * \param paCommand internal representation of the management command
     * \return response of the MGMCommand execution as defined in IEC 61499
     */
    virtual EMGMResponse executeMGMCommand(forte::core::SManagementCMD &paCommand);

    CResource* getResource() override {
      return this;
    }

    const CResource* getResource() const override {
       return this;
    }

    CDevice* getDevice() override {
      return CFBContainer::getDevice();
    }

    const CDevice* getDevice() const override {
      return CFBContainer::getDevice();
    }

    std::string getFullQualifiedApplicationInstanceName(const char ) const override{
      // we don't want to add anything here as the resource name should be excluded
      return std::string();
    }

    CEventChainExecutionThread *getResourceEventExecution() const{
      return mResourceEventExecution;
    };

    EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;

    /*!\brief Write a parameter value to a given FB-input
     *
     * @param paNameList the identifier name list of the parameter to be written
     * @param paValue the value to be writen
     * @return response of the command execution as defined in IEC 61499
     */
    virtual EMGMResponse writeValue(forte::core::TNameIdentifier &paNameList, const std::string & paValue, bool paForce = false);

#ifdef FORTE_SUPPORT_MONITORING
    forte::core::CMonitoringHandler &getMonitoringHandler(){
      return mMonitoringHandler;
    }
#endif

#ifdef FORTE_DYNAMIC_TYPE_LOAD
    CLuaEngine *getLuaEngine(){
      return luaEngine;
    }
#endif

#ifdef FORTE_TRACE_CTF
    CForteTracer &getTracer() {
      return mTracer;
    }
#endif

    bool isDynamicContainer() override {
      return true;
    }

  protected:
    CResource(const SFBInterfaceSpec& paInterfaceSpec, CStringDictionary::TStringId paInstanceNameId);

    void executeEvent(TEventID, CEventChainExecutionThread * const) override {
      // nothing to do here for a resource
    }

    void readInputData(TEventID) override {
      // nothing to read from for a resource
    }

    void writeOutputData(TEventID) override {
      // nothing to write to for a resource
    }

    CIEC_ANY *getDO(size_t) override {
      return nullptr;
    }

    CEventConnection *getEOConUnchecked(TPortId) override {
      return nullptr;
    }

    CDataConnection *getDOConUnchecked(TPortId) override {
      return nullptr;
    }

    class CInitialValue {
      private:
        CIEC_ANY& mIECVariable;
        const std::string mInitString;

      public:
        CInitialValue(CIEC_ANY& paVariable, std::string paInitString) : mIECVariable(paVariable), mInitString(std::move(paInitString)) {}

        [[nodiscard]]
        const std::string& getInitString() const{
          return mInitString;
        }

        CIEC_ANY& getIECVariable() {
          return mIECVariable;
        }

    };

    std::vector<CInitialValue> mInitialValues;

    void setInitialValues() override;

    /*! Wrapper for simplifying connection creation in resources
     *
     */
    EMGMResponse createConnection(forte::core::SManagementCMD &paCommand);

#ifdef FORTE_DYNAMIC_TYPE_LOAD
    CLuaEngine *luaEngine; //!< The Lua engine for this container
#endif

  private:
    /*!\brief Create a new connection between source and destination
     *
     * This function is protected so that devices and resource can utilize to setup their connections.
     * @param  paSrcNameList identifier name list for the source of the connection
     * @param  padstNameList identifier name list for the destination of the connection
     * @return response of the command execution as defined in IEC 61499
     */
    EMGMResponse createConnection(forte::core::TNameIdentifier &paSrcNameList,
        forte::core::TNameIdentifier &paDstNameList);

    /*! Handle and perform the actions required for an execution state change
     * command (i.e., START, STOP, KILL, RESET)
     *
     * @param paCMD    the ecuctoin state change command to be performed
     * @param paTarget identifier which is the target for this request if empty the target is the resource
     * @return response of the command execution as defined in IEC 61499
     */
    EMGMResponse handleExecutionStateCmd(EMGMCommandType paCMD,
        forte::core::TNameIdentifier &paTarget);

    /*!\brief Create a new connection between source and destination
     *
     * @param  paSrcNameList identifier name list for the source of the connection
     * @param  padstNameList identifier name list for the destination of the connection
     * @return response of the command execution as defined in IEC 61499
     */
    EMGMResponse deleteConnection(forte::core::TNameIdentifier &paSrcNameList,
        forte::core::TNameIdentifier &paDstNameList);

    /*!\brief Read a parameter value from a given FB
     *
     * @param paNameList the identifier name list of the parameter to be read
     * @param paValue the destination for the value to be read
     * @return response of the command execution as defined in IEC 61499
     */
    EMGMResponse readValue(forte::core::TNameIdentifier &paNameList, std::string & paValue);

#ifdef FORTE_SUPPORT_QUERY_CMD
    /*!\brief Read the existing fb types.
     *
     * @return response of the command execution as defined in IEC 61499
     */
    static EMGMResponse queryAllFBTypes(std::string& paValue);

    /*!\brief Read the existing adapter types.
     *
     * @return response of the command execution as defined in IEC 61499
     */
    static EMGMResponse queryAllAdapterTypes(std::string& paValue);

    static void appendTypeNameList(std::string & paValue, CTypeLib::CTypeEntry *paTypeListStart);

    /*!\brief Retrieve the list of FB instances
     *
     * @param paValue the result of the query
     * @return response of the command execution as defined in IEC 61499
     */
    static EMGMResponse queryFBs(std::string &paValue, const CFBContainer &container, std::string prefix);
    static void createFBResponseMessage(const CFunctionBlock &paFb, const std::string &fullName, std::string &paValue);

    EMGMResponse queryConnections(std::string &paValue, const CFBContainer& container);
    void createEOConnectionResponse(const CFunctionBlock& paFb, std::string& paReqResult);
    void createDOConnectionResponse(const CFunctionBlock& paFb, std::string& paReqResult);
    void createAOConnectionResponse(const CFunctionBlock& paFb, std::string& paReqResult);
    void createConnectionResponseMessage(const CStringDictionary::TStringId srcId, const CStringDictionary::TStringId dstId, const CFunctionBlock& paDstFb,
        const CFunctionBlock& paFb, std::string& paValue) const;

    EMGMResponse createFBTypeResponseMessage(const CStringDictionary::TStringId paValue, std::string & paReqResult);
    EMGMResponse createAdapterTypeResponseMessage(const CStringDictionary::TStringId paValue, std::string & paReqResult);
    EMGMResponse createXTypeResponseMessage(const CTypeLib::CSpecTypeEntry* paInterfaceSpec, const CStringDictionary::TStringId paValue, EMGMResponse retVal, std::string& paReqResult);
    void createEventInterfaceResponseMessage(const SFBInterfaceSpec* paInterfaceSpec, std::string& paReqResult);
    void createDataInterfaceResponseMessage(const SFBInterfaceSpec* paInterfaceSpec, std::string& paReqResult);
    void createAdapterInterfaceResponseMessage(const SFBInterfaceSpec* paInterfaceSpec, std::string& paReqResult);
    void createInterfaceResponseMessages(std::string& paReqResult, const char *paCommand, const CStringDictionary::TStringId* paNameList,
        const CStringDictionary::TStringId* paTypeList, const TEventID paNumberOfElements = 0, const TDataIOID* paEWith = nullptr, const TForteInt16* paEWithIndexes = nullptr,
        const CStringDictionary::TStringId* paDNameList = nullptr);
    void createInterfaceResponseMessage(std::string& paReqResult, const char* paCommand, const std::string& paName, const std::string& paType,
        const TDataIOID* paEWith = nullptr, const TForteInt16* paEWithIndexes = nullptr, const TEventID paIndex = 0,
        const CStringDictionary::TStringId* paENameList = nullptr) const;

#endif //FORTE_SUPPORT_QUERY_CMD

#ifdef FORTE_DYNAMIC_TYPE_LOAD
    /*!\brief create
     *
     * @return response of the command execution as defined in IEC 61499
     */
    EMGMResponse createFBTypeFromLua(CStringDictionary::TStringId typeNameId,
        const std::string&  paLuaScriptAsString);

    EMGMResponse createAdapterTypeFromLua(CStringDictionary::TStringId typeNameId,
        const std::string&  paLuaScriptAsString);
#endif
    /*!\brief get the variable with the given name identifier
     *
     * @param paNameList the identifier name list of the variable to be retrieved
     * @return the pointer to the variable or 0 if the variable with the given identifier name list does not exist
     */
    CIEC_ANY *getVariable(forte::core::TNameIdentifier &paNameList);

    /*!\brief get the connection object for the given source identifier
     *
     * @param paSrcNameList array of the name hierarchy the requested connection source
     * @return pointer to the requested connection, returns 0 if there is no such source
     */
    CConnection *getConnection(forte::core::TNameIdentifier &paSrcNameList);

    CConnection *getResIf2InConnection(CStringDictionary::TStringId paResInput) const;

    void initializeResIf2InConnections();

    /*!\brief The event chain execution of background (low priority) event chains started within this resource
     */
    CEventChainExecutionThread *mResourceEventExecution;

    CInterface2InternalDataConnection *mResIf2InConnections; //!< List of all connections from the res interface to internal FBs

#ifdef FORTE_SUPPORT_MONITORING
    forte::core::CMonitoringHandler mMonitoringHandler;
#endif //#ifdef FORTE_SUPPORT_MONITORING

#ifdef FORTE_TRACE_CTF
    CForteTracer mTracer;
#endif // FORTE_TRACE_CTF

};

#endif /*RESOURCE_H_*/
