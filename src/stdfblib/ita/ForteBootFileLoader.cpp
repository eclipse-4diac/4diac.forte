/*******************************************************************************
 * Copyright (c) 2017 fortiss GmbH
 *               2022 Primetals Technologies Austria GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Monika Wenger
 *    - initial API and implementation and/or initial documentation
 *    Martin Melik Merkumians - changes for removed implicit constructor for
 *      primitve types
 *******************************************************************************/

#include "ForteBootFileLoader.h"
#include "../../arch/devlog.h"
#include "../../../src/core/datatypes/forte_string.h"
#include "mgmcmd.h"
#include "mgmcmdstruct.h"
#include "../../core/device.h"

char* gCommandLineBootFile = nullptr;

ForteBootFileLoader::ForteBootFileLoader(BootFileCallback paCallback, std::optional<std::string> paPathToFile) : mCallback(paCallback) {
  openBootFile(paPathToFile);
}

ForteBootFileLoader::~ForteBootFileLoader() {
  if(nullptr != mBootfile){
    DEVLOG_INFO("Closing bootfile\n");
    forte_fclose(mBootfile);
  }
}

bool ForteBootFileLoader::openBootFile(std::optional<std::string> paPathToFile) {
  bool retVal = false;
  std::string bootFileName;
  if(paPathToFile.has_value()){
    bootFileName = paPathToFile.value();
    DEVLOG_INFO("Using provided bootfile location passed as parameter: %s\n", bootFileName.c_str());
  } else {
    if(gCommandLineBootFile) {
        DEVLOG_INFO("Using provided bootfile location set in the command line: %s\n", gCommandLineBootFile);
        bootFileName = std::string(gCommandLineBootFile);
    } else {
      // select provided or default boot file name
      char * envBootFileName = forte_getenv("FORTE_BOOT_FILE");
      if(nullptr != envBootFileName) {
        DEVLOG_INFO("Using provided bootfile location from environment variable: %s\n", envBootFileName);
        bootFileName = std::string(envBootFileName);
      } else {
        DEVLOG_INFO("Using provided bootfile location set in CMake: %s\n", FORTE_BOOT_FILE_LOCATION);
        bootFileName = std::string(FORTE_BOOT_FILE_LOCATION);
      }
    }
  }
  

  // check if we finally have a boot file name
  if(bootFileName.empty()){
    DEVLOG_INFO("No bootfile specified and no default bootfile configured during build\n");
  } else {
    mBootfile = forte_fopen(bootFileName.c_str(), "r");
    if(nullptr != mBootfile){
      DEVLOG_INFO("Boot file %s opened\n", bootFileName.c_str());
      retVal = true;
    }
    else{
      if(nullptr != forte_getenv("FORTE_BOOT_FILE_FAIL_MISSING")){
        DEVLOG_ERROR("Boot file %s could not be opened and FORTE_BOOT_FILE_FAIL_MISSING is set. Failing...\n", bootFileName.c_str());
        mNeedsExit = true;
      }
      else{
        DEVLOG_INFO("Boot file %s could not be opened. Skipping...\n", bootFileName.c_str());
      }
    }
  }
  return retVal;
}

LoadBootResult ForteBootFileLoader::loadBootFile(){
  LoadBootResult eResp = FILE_NOT_OPENED;
  if(nullptr != mBootfile){
    //we could open the file try to load it
    int nLineCount = 1;
    eResp = LOAD_RESULT_OK;
    std::string line;
    while(readLine(line) && LOAD_RESULT_OK == eResp) {
      auto sepPosition = line.find(';');
      if(sepPosition == std::string::npos){
        eResp = MISSING_COLON;
        DEVLOG_ERROR("Boot file line does not contain separating ';'. Line: %d\n", nLineCount);
      } else {
        std::string command(line.substr(sepPosition + 1));
        std::string destination(line.substr(0, sepPosition));
        char *commandBuffer = new char[command.length() + 1]{};
        strcpy(commandBuffer, command.c_str());
        if(!mCallback(destination.c_str(), commandBuffer)) {
          //command was not successful
          DEVLOG_ERROR("Boot file command could not be executed. Line: %d: %s\n", nLineCount, commandBuffer);
          eResp = EXTERNAL_ERROR;
        } else {
          nLineCount++;
        }
        delete[](commandBuffer);
      }
    }
  }else{
    DEVLOG_ERROR("Loading cannot proceed because the boot file is no opened\n");
  }
  return eResp;
}

bool ForteBootFileLoader::readLine(std::string &line){
  const unsigned int size = 100;
  line.clear();
  char acLineBuf[size];
  do {
    if(nullptr != forte_fgets(acLineBuf, size, mBootfile)) {
      line.append(acLineBuf);
    } else {
      return 0 != line.length();
    }
  } while(!hasCommandEnded(line));
  return true;
}

bool ForteBootFileLoader::hasCommandEnded(const std::string &line) const{
  return (0 == strcmp(line.c_str() + line.length() - 11, "</Request>\n") || 0 == strcmp(line.c_str() + line.length() - 3, "/>\n"));
}
