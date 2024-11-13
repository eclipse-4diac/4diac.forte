/*******************************************************************************
 * Copyright (c) 2005, 2024 ACIN, Profactor GmbH, nxtControl GmbH, fortiss GmbH,
 *                          Johannes Kepler University, Martin Erich Jobst,
 *                          Primetals Technologies Austria GmbH
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Thomas Strasser, Gunnar Grabmaier, Smodic Rene,
 *    Gerhard Ebenhofer, Michael Hofmann, Martin Melik Merkumians, Ingo Hegny,
 *    Stanislav Meduna, Patrick Smejkal,
 *      - initial implementation and rework communication infrastructure
 *    Alois Zoitl - introduced new CGenFB class for better handling generic FBs
 *    Martin Jobst - account for data type size in FB initialization
 *******************************************************************************/
#ifndef _FUNCBLOC_H_
#define _FUNCBLOC_H_

#include <forte_config.h>
#include "fbcontainer.h"
#include "mgmcmd.h"
#include "event.h"
#include "dataconn.h"
#include "inoutdataconn.h"
#include "eventconn.h"
#include "stringdict.h"
#include "../arch/devlog.h"
#include "iec61131_functions.h"
#include <stringlist.h>
#include "forte_state.h"
#include "forte_st_iterator.h"
#include "forte_st_util.h"


class CEventChainExecutionThread;
class CAdapter;
class CTimerHandler;
class CDevice;

typedef CFunctionBlock *TFunctionBlockPtr;

namespace forte {
  namespace core {
    class CFBContainer;
  }
}

#ifdef FORTE_SUPPORT_MONITORING
#include "mgmcmdstruct.h"
namespace forte {
  namespace core {
    class CMonitoringHandler;
  }
}
#endif //FORTE_SUPPORT_MONITORING


typedef CAdapter *TAdapterPtr;

typedef TPortId TDataIOID; //!< \ingroup CORE Type for holding an data In- or output ID

/*!\ingroup CORE\brief Structure to hold all data of adapters instantiated in the function block.
 */
struct SAdapterInstanceDef {
    CStringDictionary::TStringId mAdapterTypeNameID; //!< Adapter type name
    CStringDictionary::TStringId mAdapterNameID; //!< Adapter instance name
    bool mIsPlug; //!< Flag for distinction of adapter nature (plug/socket)
};

/*!
 * \brief Instance and type name of to be created FBs. Used in CFBs FBNs and BFB/SFBs internal FBs
 */
struct SCFB_FBInstanceData {
    CStringDictionary::TStringId mFBInstanceNameId;
    CStringDictionary::TStringId mFBTypeNameId;
};

/*!\ingroup CORE\brief Structure to hold all the data for specifying a function block interface.
 */
struct SFBInterfaceSpec {
    TEventID mNumEIs; //!< Number of event inputs
    const CStringDictionary::TStringId *mEINames; //!< List of the event input names
    const CStringDictionary::TStringId *mEITypeNames; //!< List of the event input types
    const TDataIOID *mEIWith; //!< Input WITH reference list. This list contains an array of input data ids. For each input event the associated data inputs are listed. The start for each input event is specified in the mEIWithIndexes field. The end is defined by the value scmWithListDelimiter.
    const TForteInt16 *mEIWithIndexes; //!< Index list for each input event. This list gives for each input event an entry in the mEIWith. Input events are numbered starting from 0. if the input event has no assciated data inputs -1 is the entry at this event inputs postion.
    TEventID mNumEOs; //!< Number of event outputs
    const CStringDictionary::TStringId *mEONames; //!< List of the event output names
    const CStringDictionary::TStringId *mEOTypeNames; //!< List of the event output types
    const TDataIOID *mEOWith; //!< Output WITH reference list. This list contains an array of output data ids. For each output event the associated data outputs are listed. The start for each output event is specified in the mEOWithIndexes field. The end is defined by the value scmWithListDelimiter.
    const TForteInt16 *mEOWithIndexes; //!< Index list for each output event. This list gives for each output event an entry in the mEOWith. Output events are numbered starting from 0. If the output event has no assciated data outputs -1 is the entry at this event outputs postion. Additionally at the postion mNumEOs in this list an index to an own list in the mEOWith list is stored specifying all output data port that are not associated with any output event. That values will be updated on every FB invocation.
    TPortId mNumDIs; //!< Number of data inputs
    const CStringDictionary::TStringId *mDINames; //!< List of the data input names
    const CStringDictionary::TStringId *mDIDataTypeNames; //!< List of the data type names for the data inputs
    TPortId mNumDOs; //!< Number of data outputs
    const CStringDictionary::TStringId *mDONames; //!< List of the data output names
    const CStringDictionary::TStringId *mDODataTypeNames; //!< List of the data type names for the data outputs
    TPortId mNumDIOs;  //!< Number of data inouts
    const CStringDictionary::TStringId *mDIONames;         //!< List of the data inout names
    TPortId mNumAdapters; //!< Number of Adapters
    const SAdapterInstanceDef *mAdapterInstanceDefinition; //!< List of adapter instances
};

/*!\ingroup CORE\brief Base class for all function blocks.
 */
class CFunctionBlock : public forte::core::CFBContainer {
  public:
    constexpr static TDataIOID scmWithListDelimiter = cgInvalidPortId; //!< value identifying the end of a with list
    constexpr static TForteInt16 scmNoDataAssociated = static_cast<TForteInt16>(cgInvalidPortId); //!< value identifying the end of a with list

    /*!\brief Possible states of a runable object.
     *
     */
    enum class E_FBStates {
      Running = 0, // in the most critical execution path of FORTE we are checking for this enum value it is faster if this is the zero entry
      Idle,
      Stopped,
      Killed
    };

    /*! \brief Indicator that the given EventID is an included adapter's eventID.
     *
     * EventIDs > scmMaxInterfaceEvents: highByte indicates (AdapterID+1)
     */
    static const TEventID scmMaxInterfaceEvents = cgInvalidPortId;
    static_assert((scmMaxInterfaceEvents & (scmMaxInterfaceEvents + 1)) == 0,
                  "scmMaxInterfaceEvents must be a valid bitmask");

    bool initialize() override;

    virtual ~CFunctionBlock();

    /*!\brief Get the timer of the device where the FB is contained.
     */
    CTimerHandler& getTimer();

    /*!\brief Returns the stringId for type name of this FB instance
     */
    virtual CStringDictionary::TStringId getFBTypeId() const = 0;


    /*!\brief Returns the type name of this FB instance
     */
    const char * getFBTypeName() const {
      return CStringDictionary::getInstance().get(getFBTypeId());
    }

    /*!\brief Get the ID of a specific event input of the FB.
     *
     * \param paEINameId   StringId to the event input name.
     * \return The ID of the event input or cgInvalidEventID.
     */
    TEventID getEIID(CStringDictionary::TStringId paEINameId) const {
      return static_cast<TEventID>(getPortId(paEINameId, getFBInterfaceSpec().mNumEIs, getFBInterfaceSpec().mEINames));
    }

    /*!\brief Get the ID of a specific event output of the FB.
     *
     * \param paEONameId string id to the event output name.
     * \return The ID of the event output or cgInvalidEventID.
     */
    TEventID getEOID(CStringDictionary::TStringId paEONameId) const {
      return static_cast<TEventID>(getPortId(paEONameId, getFBInterfaceSpec().mNumEOs, getFBInterfaceSpec().mEONames));
    }

    /*! \brief Gets the EventTypeID of a specific input event
     * \param paEIID  StringId of the event name.
     * \return Returns the EventTypeID of a specific input event
     */
    CStringDictionary::TStringId getEIType(TEventID paEIID) const;

    /*! \brief Gets the EventTypeID of a specific output event
     * \param paEOID  StringId of the event name.
     * \return Returns the EventTypeID of a specific output event
    */
    CStringDictionary::TStringId getEOType(TEventID paEOID) const;

    CEventConnection* getEOConnection(CStringDictionary::TStringId paEONameId);

    const CEventConnection* getEOConnection(CStringDictionary::TStringId paEONameId) const;

    /*!\brief Connects specific data input of a FB with a specific data connection.
     *
     * If the connection pointer is 0 then it is equal to a disconnect. Furthermore, if their is already a connection
     * to the given data port the connection attempt will be rejected. However if the further connection attempt
     * is done with the same connection object then it is a reconfiguration attempt for any data inputs. This is necessary
     * when during the first connection the data type of the connection was not clear.
     *
     * \param paDINameId StringID of the data input name.
     * \param paDataCon Pointer to the data connection the FB should be connected to.
     * \return TRUE on success, FALSE if data output not exists or output is already connected.
     */
    virtual bool connectDI(TPortId paDIPortId, CDataConnection *paDataCon);

    virtual bool connectDIO(TPortId paDIPortId, CInOutDataConnection *paDataCon);

    /*! \brief Gets the index of the mDINames array of a specific data output of a FB
     *
     * \param paDINameId  StringId of the data input name.
     * \return Returns index of the Data Input Array of a FB
     */
    TPortId getDIID(CStringDictionary::TStringId paDINameId) const {
      return getPortId(paDINameId, getFBInterfaceSpec().mNumDIs, getFBInterfaceSpec().mDINames);
    }

    /*!\brief Get the pointer to a data input of the FB.
     *
     * \param paDINameId ID of the data input name.
     * \return Pointer to the data input or 0. If 0 is returned DataInput is ANY
     */
    CIEC_ANY* getDataInput(CStringDictionary::TStringId paDINameId);

    /*!\brief get the pointer to a data input using the portId as identifier
     */
    CIEC_ANY* getDIFromPortId(TPortId paDIPortId);

    /*! \brief Gets the index of the mDONames array of a specific data output of a FB
     * \param paDONameId  StringId of the data input name.
     * \return Returns index of the Data Output Array of a FB
     */
    TPortId getDOID(CStringDictionary::TStringId paDONameId) const {
      return getPortId(paDONameId, getFBInterfaceSpec().mNumDOs, getFBInterfaceSpec().mDONames);
    }

    /*! \brief Gets the index of the mDONames array of a specific data output of a FB
     * \param paDONameId  StringId of the data input name.
     * \return Returns index of the Data Output Array of a FB
     */
    TPortId getDIOID(CStringDictionary::TStringId paDIONameId) const {
      return getPortId(paDIONameId, getFBInterfaceSpec().mNumDIOs, getFBInterfaceSpec().mDIONames);
    }

    /*!\brief get the pointer to a data output using the portId as identifier
     */
    CIEC_ANY* getDOFromPortId(TPortId paDOPortId);

    CIEC_ANY* getDIOFromPortId(TPortId paDIPortId);

    CDataConnection* getDIConnection(CStringDictionary::TStringId paDINameId);

    const CDataConnection* getDIConnection(CStringDictionary::TStringId paDINameId) const;

    CDataConnection* getDOConnection(CStringDictionary::TStringId paDONameId);

    const CDataConnection* getDOConnection(CStringDictionary::TStringId paDONameId) const;

    CInOutDataConnection *getDIOInConnection(CStringDictionary::TStringId paDIONameId);

    const CInOutDataConnection *getDIOInConnection(CStringDictionary::TStringId paDIONameId) const;

    CInOutDataConnection *getDIOOutConnection(CStringDictionary::TStringId paDIONameId);

    const CInOutDataConnection *getDIOOutConnection(CStringDictionary::TStringId paDIONameId) const;

    /*!\brief if the data output is of generic type (i.e, ANY) this function allows an data connection to configure
     * the DO with the specific type coming from the other end of the connection
     */
    virtual bool configureGenericDO(TPortId paDOPortId, const CIEC_ANY &paRefValue);

    /*!\brief Get the pointer to a data output of the FB.
     *
     * \param paDONameId StringID of the data output name.
     * \return Pointer to the data output or 0. If 0 is returned DataOutput is ANY
     */
    CIEC_ANY* getDataOutput(CStringDictionary::TStringId paDONameId);

    /*!\brief Get the pointer to a variable of the FB.
     *
     * @param paNameList array of the name hierarchy the requested variable
     * @param paNameListSize length of the array
     * \return Pointer to the variable or 0.
     *  The variable may be input, output or in the case of a BFB an internal var.
     */
    virtual CIEC_ANY* getVar(CStringDictionary::TStringId *paNameList, unsigned int paNameListSize);

    /*!\brief Get the pointer to the adapter instance of the FB.
     *
     * \param paAdapterNameId  StringId of the adapter name.
     * \return Pointer to the adapter or nullptr.
     */
    CAdapter* getAdapter(CStringDictionary::TStringId paAdapterNameId);

    const CAdapter* getAdapter(CStringDictionary::TStringId paAdapterNameId) const;

    TPortId getAdapterPortId(CStringDictionary::TStringId paAdapterNameId) const;

    /*!\brief Function that handles incoming events.
     *
     * \param paEIID ID of the input event that has occurred.
     * \param paExecEnv Event chain execution environment the FB will be executed in (used for adding output events).
     */
    void receiveInputEvent(TEventID paEIID, CEventChainExecutionThread *paExecEnv) {
      FORTE_TRACE("InputEvent: Function Block (%s) got event: %d (maxid: %d)\n", CStringDictionary::getInstance().get(getInstanceNameId()), paEIID, getFBInterfaceSpec().mNumEIs - 1);

      #ifdef FORTE_TRACE_CTF
        traceInputEvent(paEIID);
      #endif

      if(E_FBStates::Running == getState()){
        if(paEIID < getFBInterfaceSpec().mNumEIs) {
          readInputData(paEIID);
          #ifdef FORTE_SUPPORT_MONITORING
                // Count Event for monitoring
                mEIMonitorCount[paEIID]++;
          #endif //FORTE_SUPPORT_MONITORING
        }
        executeEvent(paEIID, paExecEnv);
      }
    }

    /*!\brief Configuration interface used by the typelib to parameterize generic function blocks.
     *
     * \param paConfigString  A string containing the needed configuration data.
     * \return TRUE if configuration went ok, else FALSE.
     *
     */
    virtual bool configureFB(const char *paConfigString);

    const SFBInterfaceSpec& getFBInterfaceSpec() const {
      return mInterfaceSpec;
    }

    EMGMResponse changeExecutionState(EMGMCommandType paCommand) override;

    /*!\brief Get information if the runable object is deletable by a management command.
     *
     */
    bool getDeletable() const {
      return mDeletable;
    }

    /*!\brief Set attribute to enable/disable the runable object deletion by a management command.
     *
     */
    void setDeletable(const bool &paDelAble) {
      mDeletable = paDelAble;
    }

    /*!\brief Return if the runable object is allowed to be deleted now.
     *
     * This is more complex then the simple deleteable flag as the current state has to be incorporated.
     * According to IEC 61499-1 Figure 24 an FB is deleteable if it is not in the Running state
     * \return true if currently all conditions are met to be deleteable
     */
    bool isCurrentlyDeleteable() const {
      return ((mDeletable) && (mFBState != E_FBStates::Running));
    }

    /*!\brief return the current execution state of the managed object
     */
    E_FBStates getState() const {
      return mFBState;
    }

    /*! \brief Get the data input with given number
     *
     * Attention this function will not perform any range checks on the paDINum parameter!
     * @param paDINum number of the data input starting with 0
     * @return pointer to the data input
     */
    virtual CIEC_ANY* getDI(TPortId paDINum) = 0;

    const CIEC_ANY* getDI(TPortId paDINum) const {
      return const_cast<CFunctionBlock*>(this)->getDI(paDINum);
    }

    /*! \brief Get the data output with given number
     *
     * Attention this function will not perform any range checks on the paDONum parameter!
     * @param paDONum number of the data output starting with 0
     * @return pointer to the data output
     */
    virtual CIEC_ANY* getDO(TPortId paDONum) = 0;

    const CIEC_ANY* getDO(TPortId paDONum) const {
      return const_cast<CFunctionBlock *>(this)->getDO(paDONum);
    }

    /*! \brief Get the data output with given number
     *
     * Attention this function will not perform any range checks on the paDONum parameter!
     * @param paDONum number of the data output starting with 0
     * @return pointer to the data output
     */
    virtual CIEC_ANY* getDIO(TPortId paDIONum) {
      (void)paDIONum; // indicate to the compiler that the param is unused
      return nullptr;
    }

    const CIEC_ANY* getDIO(TPortId paDIONum) const {
      return const_cast<CFunctionBlock *>(this)->getDIO(paDIONum);
    }

    /*!\brief get any internal FB referenced by the iterator to the name list
     *
     * This allows that also adapters and the internals of a CFB can be monitored.
     */
    CFunctionBlock *getFB(forte::core::TNameIdentifier::CIterator &paNameListIt) override;

#ifdef FORTE_SUPPORT_MONITORING
    TForteUInt32 &getEIMonitorData(TEventID paEIID);

    TForteUInt32 &getEOMonitorData(TEventID paEOID);
#endif //FORTE_SUPPORT_MONITORING
    
    virtual int toString(char* paValue, size_t paBufferSize) const;

    virtual size_t getToStringBufferSize() const;

#ifdef FORTE_TRACE_CTF
    virtual void traceInstanceData() {}
#endif //FORTE_TRACE_CTF

  protected:

    /*!\brief The main constructor for a function block.
     *
     * \param paContainer      FB container this function block is contained in (mainly necessary for management functions and service interfaces)
     * \param paInterfaceSpec  const pointer to the interface spec
     * \param paInstanceNameId string id
     * \param paFBConnData     Byte-array for fb-specific connection data. It will need space for the event output connections,
     *                             data input connections, and data output connections, in that order. The space requirements are:
     *                               sizeof(TEventConnectionPtr) * Number of Event outputs +
     *                               sizeof(TDataConnectionPtr)  * Number of Data inputs +
     *                               sizeof(TDataConnectionPtr)  * Number of Data outputs
     * \param paFBVarsData    Byte-array for fb-specific variable data. It will need space for the data inputs, data outputs, and adapters in that order.
     *                             The space requirements are:
     *                               sizeof(CIEC_ANY)) * Number of Data inputs +
     *                               sizeof(CIEC_ANY)) * Number of Data outputs +
     *                               sizeof(TAdapterPtr) * ta_nNumAdapters
     */
    CFunctionBlock(forte::core::CFBContainer &paContainer, const SFBInterfaceSpec& paInterfaceSpec, CStringDictionary::TStringId paInstanceNameId);

    static TPortId getPortId(CStringDictionary::TStringId paPortNameId, TPortId paMaxPortNames, const CStringDictionary::TStringId *paPortNames);


    /*!\brief Function to send an output event of the FB.
     *
     * \param paECET the event chain execution thread to be used for sending output events
     * \param paEO Event output ID where event should be fired.
     * \param paExecEnv Event chain execution environment where the event will be sent to.
     */
    void sendOutputEvent(TEventID paEO, CEventChainExecutionThread * const paECET){
      FORTE_TRACE("OutputEvent: Function Block sending event: %d (maxid: %d)\n", paEO, getFBInterfaceSpec().mNumEOs - 1);

      #ifdef FORTE_TRACE_CTF
        traceOutputEvent(paEO);
      #endif

      if(paEO < getFBInterfaceSpec().mNumEOs) {
        writeOutputData(paEO);
        getEOConUnchecked(static_cast<TPortId>(paEO))->triggerEvent(paECET);

        #ifdef FORTE_SUPPORT_MONITORING
            // Count Event for monitoring
            mEOMonitorCount[paEO]++;
        #endif //FORTE_SUPPORT_MONITORING
      }
    }

    /*!\brief Function to read data from an input connection into a variable of the FB.
     *
     * \param paValue Variable to read into.
     * \param paConn Connection to read from.
     */
#ifdef FORTE_TRACE_CTF
    void readData(size_t paDONum, CIEC_ANY &paValue, const CDataConnection *const paConn);
#else
    void readData(size_t, CIEC_ANY &paValue, const CDataConnection *const paConn) {
      if(!paConn) {
        return;
      }
#ifdef FORTE_SUPPORT_MONITORING
      if(!paValue.isForced()) {
#endif //FORTE_SUPPORT_MONITORING
        paConn->readData(paValue);
#ifdef FORTE_SUPPORT_MONITORING
      }
#endif //FORTE_SUPPORT_MONITORING
    }
#endif //FORTE_TRACE_CTF

    /*!\brief Function to write data to an output connection from a variable of the FB.
     *
     * \param paValue Variable to write from.
     * \param paConn Connection to write into.
     */
#ifdef FORTE_TRACE_CTF
    void writeData(size_t paDONum, CIEC_ANY& paValue, CDataConnection& paConn);
#else
    void writeData(size_t, CIEC_ANY& paValue, CDataConnection& paConn) {
      if(paConn.isConnected()) {
#ifdef FORTE_SUPPORT_MONITORING
        if(!paValue.isForced()) {
#endif //FORTE_SUPPORT_MONITORING
          paConn.writeData(paValue);
#ifdef FORTE_SUPPORT_MONITORING
        } else {
          //when forcing we write back the value from the connection to keep the forced value on the output
          paConn.readData(paValue);
        }
#endif //FORTE_SUPPORT_MONITORING
      }
    }
#endif //FORTE_TRACE_CTF

    /*!\brief Set the initial values of data inputs, outputs, and internal vars.
     *
     * The default implementation initializes all input, output, and internal variables
     * to the implicit default value corresponding to the type of the variable.
     *
     * Any FB with explicit default values still has to override setInitialValues for proper Reset behavior,
     * other FBs may choose to override for improved performance.
     */
    virtual void setInitialValues();

    /*!\brief Function to send an output event via the adapter.
     *
     * \param paAdapterID ID of Adapter in current FBs adapter list.
     * \param paEID Event ID where event should be fired.
     * \param paExecEnv Event chain execution environment where the event will be sent to.
     */
    void sendAdapterEvent(TPortId paAdapterID, TEventID paEID, CEventChainExecutionThread * const paECET);

    virtual CEventConnection *getEOConUnchecked(TPortId paEONum) = 0;

    /*! \brief Get the data output connection with given number
     *
     * Attention this function will not perform any range checks on the paDONum parameter!
     * @param paDONum number of the data output starting with 0
     * @return pointer to the data output connection
     */
    virtual CDataConnection *getDOConUnchecked(TPortId paDONum) = 0;

    /*! \brief Get the data input connection with given number
     *
     * Attention this function will not perform any range checks on the paDINum parameter!
     * @param paDINum number of the data input starting with 0
     * @return pointer to the data input connection
     */
    virtual CDataConnection **getDIConUnchecked(TPortId paDINum) = 0;

    /*! \brief Get the data inout connection with given number
     *
     * Attention this function will not perform any range checks on the paDIONum parameter!
     * @param paDIONum number of the data inout starting with 0
     * @return pointer to the data inout connection
     */
    virtual CInOutDataConnection **getDIOInConUnchecked(TPortId paDIONum) {
      (void)paDIONum; // indicate to the compiler that the param is unused
      return nullptr;
    }

    virtual CInOutDataConnection *getDIOOutConUnchecked(TPortId) {
      return nullptr;
    }

    virtual CAdapter *getAdapterUnchecked(TPortId) {
      return nullptr;
    }

    /*!\brief Get the size of a data point
     *
     * @param paDataTypeIds pointer to the data type ids. If the datatype
     *        is an Array to more values are taken from the array. If the given
     *        type is Any 0 is returned as necessary for maintaining the FB's interface.
     *        The functions puts the pointer in the datatype array to the next data point's id.
     * @return The size of the data point
     */
    static size_t getDataPointSize(const CStringDictionary::TStringId *&paDataTypeIds);

    /*!\brief Function to create an data type instance of given type
     *
     * @param paDataTypeIds pointer to the data type ids. If the datatype
     *        is an Array to more values are taken from the array. If the given
     *        type is Any 0 is returned as necessary for maintaining the FB's interface.
     *        The functions puts the pointer in the datatype array to the next data point's id.
     * @param paDataBuf pointer to the data buffer which should be used by the data type to create
     * @return on success... pointer to the datatype instance
     *         on error... 0
     */
    static CIEC_ANY* createDataPoint(const CStringDictionary::TStringId *&paDataTypeIds, TForteByte *&paDataBuf);

    /*!\brief Function to skip to the next data point
     *
     * @param paDataTypeIds pointer to the data type ids. If the datatype
     *        is an Array to more values are taken from the array.
     */
    static void nextDataPoint(const CStringDictionary::TStringId *&paDataTypeIds);

    /*!\brief Function to create an adapter instance
     *
     * @param paAdapterInstanceDefinition the adapter instance definition
     * @param paParentAdapterlistID the adapter index
     * @return on success... pointer to the adapter instance
     *         on error... nullptr
     */
    CAdapter *createAdapter(const SAdapterInstanceDef &paAdapterInstanceDefinition, TForteUInt8 paParentAdapterlistID);

    static void destroyAdapter(CAdapter *adapter);

    const SFBInterfaceSpec &mInterfaceSpec; //!< Pointer to the interface specification

#ifdef FORTE_SUPPORT_MONITORING
    void setupEventMonitoringData();
    void freeEventMonitoringData();
#endif
  private:
    bool isFB() override {
       return true;
    }

    bool isDynamicContainer() override {
      return false;
    }

    /*!\brief Function providing the functionality of the FB (e.g. execute ECC for basic FBs).
     *
     * \param paECET the event chain execution thread this FB was invoked from
     * \param paEIID Event input ID where event occurred.
     * \param paExecEnv Event chain execution environment the FB will be executed in (used for adding output events).
     *
     *
     */
    virtual void executeEvent(TEventID paEIID, CEventChainExecutionThread * const paECET) = 0;

    /*!\brief Function reading the values from input connections of the FB.
     *
     * \param paEIID Event input ID where event occurred.
     */
    virtual void readInputData(TEventID paEIID) = 0;

    /*!\brief Function writing the values to output connections of the FB.
     *
     * \param paEIID Event output ID where event occurred.
     */
    virtual void writeOutputData(TEventID paEO) = 0;

  public:
    CFunctionBlock(const CFunctionBlock&) = delete;

  protected:
    int writeToStringNameValuePair(char *paValue, size_t paBufferSize, const CStringDictionary::TStringId variableNameId, const CIEC_ANY *const variable) const;
    constexpr static char csmToStringSeparator[] = ", ";

  private:
    void configureGenericDI(TPortId paDIPortId, const CIEC_ANY *paRefValue);
    void configureGenericDIO(TPortId paDIOPortId, const CIEC_ANY *paRefValue);

#ifdef FORTE_SUPPORT_MONITORING
    TForteUInt32 *mEOMonitorCount;
    TForteUInt32 *mEIMonitorCount;
#endif

#ifdef FORTE_TRACE_CTF
    void traceInputEvent(TEventID paEIID);
    void traceOutputEvent(TEventID paEOID);
#endif

    /*!\brief Current state of the runnable object.
     *
     */
    E_FBStates mFBState;

    /*!\brief Attribute defines if runnable object can be deleted by a management command.
     *
     * Default value is set to true.
     * If the runnable object is declared in a device or resource specification it must be set to false.
     */
    bool mDeletable;

#ifdef FORTE_SUPPORT_MONITORING
    friend class forte::core::CMonitoringHandler;
#endif //FORTE_SUPPORT_MONITORING

#ifdef FORTE_FMU
    friend class fmuInstance;
#endif //FORTE_FMU
};

#define FUNCTION_BLOCK_CTOR(fbclass) \
 fbclass(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : \
 CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId)

#define FUNCTION_BLOCK_CTOR_WITH_BASE_CLASS(fbclass, fbBaseClass) \
 fbclass(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) : \
 fbBaseClass(paContainer, scmFBInterfaceSpec, paInstanceNameId)


#ifdef OPTIONAL
#undef OPTIONAL
#endif

#endif /*_FUNCBLOC_H_*/
