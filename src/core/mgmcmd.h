/*******************************************************************************
 * Copyright (c) 2005 - 2015 ACIN, Profactor GmbH, fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl, Gunnar Grabmaier, Thomas Strasser, Gerhard Ebenhofer,
 *    Martin Melik Merkumians, Ingo Hegny,
 *      - initial implementation and rework communication infrastructure
 *******************************************************************************/
#ifndef _MGMCMD_H_
#define _MGMCMD_H_

#include <forte_config.h>

#include <string>

/**  \ingroup CORE \defgroup MGMCommands Management Commands Internal Representation
 * \brief In this section the FORTE representation of the management commands is described.
 */
/*@{*/

/*!\brief Type for the management command (e.g. create, delete ...)
 *
 * The constants for the management commands are selected in the following way:
 *  - the lower 4 bit are the same as the corresponding command defined by the standard (see 61499-1: Table 6, p47).
 *  - the higher 4 bits are counted as they are listed in the Table 8, p48 in 61499-1.
 *
 */
enum class EMGMCommandType : uint8_t {
  CreateGroup = 0x00, //!< Identifier for all create commands

  CreateDataType = 0x10, //!< Create a new data type definition in the FORTE.
  CreateFBType = 0x20,   //!< Create a new FB type definition in the FORTE.
  CreateAdapterType = 0x50,   //!< Create a new Adapter type definition in the FORTE.

  /*! \brief Create a new FB or resource instance.
   *
   * When creating a FB instance the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for creating within the device or "resname" for creating within a resource
   *    - mFistParam = FB Instance name
   *    - mSecondParam = FB Type
   *    - mAdditionalParams not used
   */
  CreateFBInstance = 0x30,

  /*! \brief Create a new connection (can be event or data connection).
   *
   * When creating a connection the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for creating within the device or "resname" for creating within a resource
   *    - mFistParam = source of the connection given by: "fbname.output"
   *    - mSecondParam = destination of the connection given by: "fbname.intput"
   *    - mAdditionalParams not used
   */
  CreateConnection = 0x40,

  DeleteGroup = 0x01,   //!<Identifier for all delete commands
  DeleteDataType = 0x11,
  DeleteFBType = 0x21,

  /*! \brief Delete a FB or resource instance.
   *
   * When deleting a FB instance the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for deleting within the device or "resname" for creating within a resource
   *    - mFistParam = FB Instance name
   *    - mSecondParam not used
   *    - mAdditionalParams not used
   */
  DeleteFBInstance = 0x31,

  /*! \brief Delete a connection (can be event or data connection).
   *
   * When deleting a connection the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for deleting within the device or "resname" for deleting within a resource
   *    - mFistParam = source of the connection given by: "fbname.output"
   *    - mSecondParam = destination of the connection given by: "fbname.intput"
   *    - mAdditionalParams not used
   */
  DeleteConnection = 0x41,

  /*! \brief Delete all FBs or resource instances.
   *
   * When deleting a FB instance the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for deleting within the device or "resname" for deleting within a resource
   *    - mFistParam not used
   *    - mSecondParam not used
   *    - mAdditionalParams not used
   */
  DeleteAllFBInstances = 0x61,

  /*! \brief start a FB, resource or the device.
   *
   * When starting a FB, resource or the device the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for starting within the device or "resname" for starting within a resource
   *    - mFirstParam = target to be started can be empty for starting the whole device or resource, or contain a name for the resource or FB to start.
   *    - mSecondParam = not used
   *    - mAdditionalParams not used
   */
  Start = 0x02,

  /*! \brief stop a FB, resource or the device.
   *
   * When stopping a FB, resource or the device the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for stopping within the device or "resname" for stopping within a resource
   *    - mFirstParam = target to be stopped can be empty for starting the whole device or resource, or contain a name for the resource or FB to stop.
   *    - mSecondParam = not used
   *    - mAdditionalParams not used
   */
  Stop = 0x03,

  /*! \brief Read values from FB in- and outputs or from resource inputs
   *
   * When reading a parameter value the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for creating within the device or "resname" for creating within a resource
   *    - mFistParam = Source qualifier for reading an FB's variable ("fbname.var") variable identifier may be input, output, or internal var
   *    - mSecondParam = CStringDictionary::scmInvalidStringId
   *    - mAdditionalParams the read value is stored here
   */
  Read = 0x04,

  /*! \brief Write value to a given data input or output (FB or Resource)
   *
   * When writing a parameter value the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for creating within the device or "resname" for creating within a resource
   *    - mFistParam = Destination qualifier for writing on an FB's variable ("fbname.var") variable identifier may be input, output, or internal var
   *    - mSecondParam = CStringDictionary::scmInvalidStringId
   *    - mAdditionalParams = the string converted value to be set
   */
  Write = 0x05,

  /*! \brief kill a FB, resource or the device.
   *
   * When killing a FB, resource or the device the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for killing within the device or "resname" for stopping within a resource
   *    - mFistParam = target to be killed can be empty for starting the whole device or resource, or contain a name for the resource or FB to stop.
   *    - mSecondParam = not used
   *    - mAdditionalParams not used
   */
  Kill = 0x06,

#ifdef FORTE_SUPPORT_QUERY_CMD
  QueryGroup = 0x07,   //!< Identifier for all query commands

  /*! \brief query FBs
   *
   * The parameters of the SManagementCMD are defined as:
   *    - mDestination = "" to query within the device or "resname" for fetching within a resource
   *    - mFirstParam = CStringDictionary::scmInvalidStringId for all FBs or instance name
   *    - mSecondParam = CStringDictionary::scmInvalidStringId for all FB types or type name
   *    - mAdditionalParams  the response value of the query
   */
  QueryFB = 0x17,

  /*! \brief query connections
   *
   * The parameters of the SManagementCMD are defined as:
   *    - mDestination = "" to query within the device or "resname" for fetching within a resource
   *    - mFirstParam = CStringDictionary::scmInvalidStringId
   *    - mSecondParam = CStringDictionary::scmInvalidStringId
   *    - mAdditionalParams  the response value of the query - a list of event and data connections (comma separated list of end points to end points)
   */
  QueryConnection = 0x27,

  /*! \brief Read the existing fb types.
   *
   * When reading the fb types the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for reading within the device or "resname" for reading within a resource
   *    - mFistParam = not used
   *    - mSecondParam = not used
   *    - mAdditionalParams the read value is stored here
   */
  QueryFBTypes = 0x37,

  /*! \brief Read the existing data types.
   *
   * When reading the data types the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for reading within the device or "resname" for reading within a resource
   *    - mFistParam = not used
   *    - mSecondParam = not used
   *    - mAdditionalParams the read value is stored here
   */
  QueryDTTypes = 0x47,

  /*! \brief Read the existing data types.
   *
   * When reading the data types the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for reading within the device or "resname" for reading within a resource
   *    - mFirstParam = not used
   *    - mSecondParam = not used
   *    - mAdditionalParams the read value is stored here
   */
  QueryAdapterTypes = 0x57,

  /**
   * currently not implemented
   */
  QueryTypeVers = 0x67,

  /*! \brief Read the interface of a specific FB type.
   *
   * When reading the FB interface the parameters of the SManagementCMD are defined as:
   *    - mFirstParam = FB type name
   *    - mSecondParam = not used
   *    - mAdditionalParams the read value is stored here
   */
  QueryFBType = 0x77,

  /*! \brief Read the interface of a specific adapter type.
   *
   * When reading the adapter interface the parameters of the SManagementCMD are defined as:
   *    - mFirstParam = adapter type name
   *    - mSecondParam = not used
   *    - mAdditionalParams the read value is stored here
   */
  QueryAdapterType = 0x87,
#endif

  /*! \brief reset a FB, resource or the device.
   *
   * When reseting a FB, resource or the device the parameters of the SManagementCMD are defined as:
   *    - mDestination = "" for reseting within the device or "resname" for reseting within a resource
   *    - mFistParam = target to be reset can be empty for reseting the whole device or resource, or contain a name for the resource or FB to reset.
   *    - mSecondParam = not used
   *    - mAdditionalParams not used
   */
  Reset = 0x08,



#ifdef FORTE_SUPPORT_MONITORING
  MonitoringGroup = 0x0A,
  MonitoringAddWatch = 0x1A,
  MonitoringRemoveWatch = 0x2A,
  MonitoringReadWatches = 0x3A,
  MonitoringForce = 0x5A,
  MonitoringClearForce = 0x6A,
  MonitoringTriggerEvent = 0x7A,
  MonitoringResetEventCount = 0x8A,
#endif // FORTE_SUPPORT_MONITORING


  /*! \brief invalid command: some of the data could not be parsed
     */
  INVALID = 0xFF
};


/*!\brief Type for the response of MGM commands
 *
 * TODO fully define all responses as defined in IEC 61499 inc. numbers.
 */
enum class EMGMResponse {
    Ready,
    BadParams,
    LocalTermination,
    SystemTermination,
    NotReady,
    UnsupportedCmd,
    UnsupportedType,
    NoSuchObject,
    InvalidObject,
    InvalidOperation,
    InvalidState,
    Overflow,
    InvalidDst
};

namespace forte::mgm_cmd {

  const std::string& getResponseText(EMGMResponse paResp);

} // namespace forte::mgm_cmd

/*@}*/
#endif /*MGMCMD_H_*/
