/*******************************************************************************
 * Copyright (c) 2017, 2024 fortiss GmbH, Monika Wenger, Johannes Kepler University Linz
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Monika Wenger, Alois Zoitl - migration to current runtime
 *******************************************************************************/

#include "RevPiConfig.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RevPiConfig_gen.cpp"
#endif

#include "RevPiController.h"

using namespace forte::core::io;

DEFINE_FIRMWARE_FB(RevPiConfig, g_nStringIdIORevPi)

const CStringDictionary::TStringId RevPiConfig::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdDigitalInput_1, g_nStringIdDigitalInput_2, g_nStringIdDigitalInput_3, g_nStringIdDigitalInput_4, g_nStringIdDigitalInput_5, g_nStringIdDigitalInput_6, g_nStringIdDigitalInput_7, g_nStringIdDigitalInput_8, g_nStringIdDigitalInput_9, g_nStringIdDigitalInput_10, g_nStringIdDigitalInput_11, g_nStringIdDigitalInput_12, g_nStringIdDigitalInput_13, g_nStringIdDigitalInput_14, g_nStringIdDigitalOutput_1, g_nStringIdDigitalOutput_2, g_nStringIdDigitalOutput_3, g_nStringIdDigitalOutput_4, g_nStringIdDigitalOutput_5, g_nStringIdDigitalOutput_6, g_nStringIdDigitalOutput_7, g_nStringIdDigitalOutput_8, g_nStringIdDigitalOutput_9, g_nStringIdDigitalOutput_10, g_nStringIdDigitalOutput_11, g_nStringIdDigitalOutput_12, g_nStringIdDigitalOutput_13, g_nStringIdDigitalOutput_14, g_nStringIdUpdateInterval};

const CStringDictionary::TStringId RevPiConfig::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdWSTRING, g_nStringIdUINT};

const CStringDictionary::TStringId RevPiConfig::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId RevPiConfig::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TForteInt16 RevPiConfig::scm_anEIWithIndexes[] = {0};
const TDataIOID RevPiConfig::scm_anEIWith[] = {0, 29, 1, 2, 3, 4, 5, 6, 9, 8, 7, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 255};
const CStringDictionary::TStringId RevPiConfig::scm_anEventInputNames[] = {g_nStringIdINIT};
const CStringDictionary::TStringId RevPiConfig::scmEventInputTypeIds[] = {g_nStringIdEInit};

const TDataIOID RevPiConfig::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 RevPiConfig::scm_anEOWithIndexes[] = {0, 3, -1};
const CStringDictionary::TStringId RevPiConfig::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdIND};
const CStringDictionary::TStringId RevPiConfig::scmEventOutputTypeIds[] = {g_nStringIdEvent,g_nStringIdEvent};

const SFBInterfaceSpec RevPiConfig::scm_stFBInterfaceSpec = {
  1,  scm_anEventInputNames, scmEventInputTypeIds,  scm_anEIWith,  scm_anEIWithIndexes,
  2,  scm_anEventOutputNames, scmEventOutputTypeIds, scm_anEOWith, scm_anEOWithIndexes,  30,  scm_anDataInputNames, scm_anDataInputTypeIds,
  2,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


void RevPiConfig::setInitialValues(){
  UpdateInterval() = 25;
}

void RevPiConfig::setConfig(){
  RevPiController::Config config;
  config.updateInterval = UpdateInterval();
  controller->setConfig(&config);
}

IODeviceController* RevPiConfig::createDeviceController(CDeviceExecution& paDeviceExecution){
    return new RevPiController(paDeviceExecution);
}
