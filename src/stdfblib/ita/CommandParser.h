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

#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include "core/mgmcmd.h"
#include "core/mgmcmdstruct.h"

#include <string>

class CDevice;

namespace forte::command_parser {

  const char *getResponseText(EMGMResponse paResp);

  /**
   * @brief Parse and executes a commmand on a destination in a device
   * 
   * @param paDest destination where to executed the command
   * @param paCommand the command to be executed
   * @param paCommandStorage this is needed just because the monitoring command stores its results inside of this object
   * @param paDevice device where to execute the command
   * @return EMGMResponse response of the execution of the command
   */
  EMGMResponse parseAndExecuteMGMCommand(const char *const paDest, char *paCommand, forte::core::SManagementCMD &paCommandStorage, CDevice& paDevice);

  /*! \brief Parse the given request header to determine the ID and the requested command
    *
    * \param paRequestString data of the request
    * \param paCommand the command structure for holding command information
    * \return pointer to the next part of the command zero on error
    */
  char* parseRequest(char *paRequestString, forte::core::SManagementCMD &paCommand);
  /*! \brief Parse the given request that is left after parsing the header to parse FB data
    *
    * \param paRequestPartLeft  data of the request that has been left after parsing the header
    * \param paCommand the command structure for holding command information
    * \return true if the FB data could be parsed
    */
  bool parseFBData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  /*! \brief Parse the given request that is left after parsing the header to parse FB or Adapter type
    *
    * \param paRequestPartLeft  data of the request that has been left after parsing the header
    * \param paCommand the command structure for holding command information
    * \param pa_requestType the type that should be searched
    * \return true if the FB type could be parsed
    */
  bool parseXType(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand, const char *paRequestType);
  /*! \brief Parse the given request that is left after parsing the header to parse connection data
    *
    * \param paRequestPartLeft   data of the request that has been left after parsing the header
    * \param paCommand the command structure for holding command information
    * \return true if the connection data could be parsed
    */
  bool parseConnectionData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  bool parseWriteConnectionData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);


  void parseCreateData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  void parseDeleteData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  //! Check if an FB is given for a state change command (i.e., START, STOP, KILL, RESET)
  void parseAdditionalStateCommandData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  void parseReadData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  void parseWriteData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);

#ifdef FORTE_SUPPORT_QUERY_CMD
  void parseQueryData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  bool parseTypeListData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
#endif


  /*! \brief parse a hierarchical identifier list
    *
    * The identifiers are separated  by '.' and the end character for the list is '\"'
    *
    * @param paIdentifierStart pointer to the start of the identifier that will be parsed
    * @param paIdentifier identifier vector where to write the parsed identifiers to
    * @return number of bytes used from the character array or -1 if the identifier could not be parsed
    */
  int parseIdentifier(char *paIdentifierStart, forte::core::TNameIdentifier &paIdentifier);

#ifdef FORTE_SUPPORT_MONITORING
  bool parseMonitoringData(char *paRequestPartLeft, forte::core::SManagementCMD &paCommand);
  std::string generateMonitorResponse(EMGMResponse paResp, forte::core::SManagementCMD &paCMD);
#endif //FORTE_SUPPORT_MONITORING

  /*! \brief set the RESP output of the DEV_MGR according to the given response data
    *
    * \param paID id of the response
    * \param paResp qualifier of the response
    */
  std::string generateResponse(const char *paID, EMGMResponse paResp);
  /*! \brief set the RESP output of the DEV_MGR according to the given response data
    *
    * \param paID id of the response
    * \param paResp qualifier of the response
    * \param paCMD the command type
    */
  std::string generateLongResponse(EMGMResponse paResp, forte::core::SManagementCMD &paCMD);
  void appendIdentifierName(std::string& paDest, forte::core::TNameIdentifier& paIdentifier);

} // namespace forte::command_parser


#endif /*_COMMAND_PARSER_H*/
