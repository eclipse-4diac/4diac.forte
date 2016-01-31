/*******************************************************************************
 * Copyright (c) 2006 - 2013 Profactor GmbH, ACIN
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Thomas Strasser, Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny,
 *   - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "STRING2STRING.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "STRING2STRING_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(STRING2STRING, g_nStringIdSTRING2STRING)

const CStringDictionary::TStringId STRING2STRING::scm_anDataInputNames[] = {g_nStringIdIN};

const CStringDictionary::TStringId STRING2STRING::scm_anDataOutputNames[] = {g_nStringIdOUT};
const CStringDictionary::TStringId STRING2STRING::scm_aunDIDataTypeIds[] = {g_nStringIdSTRING};
const CStringDictionary::TStringId STRING2STRING::scm_aunDODataTypeIds[] = {g_nStringIdSTRING};

const TForteInt16 STRING2STRING::scm_anEIWithIndexes[] = {0};
const TDataIOID STRING2STRING::scm_anEIWith[] = {0, 255};
const CStringDictionary::TStringId STRING2STRING::scm_anEventInputNames[] = {g_nStringIdREQ};

const TDataIOID STRING2STRING::scm_anEOWith[] = {0, 255};
const TForteInt16 STRING2STRING::scm_anEOWithIndexes[] = {0};
const CStringDictionary::TStringId STRING2STRING::scm_anEventOutputNames[] = {g_nStringIdCNF};

const SFBInterfaceSpec STRING2STRING::scm_stFBInterfaceSpec = {
  1,
  scm_anEventInputNames,
  scm_anEIWith,
  scm_anEIWithIndexes,
  1,
  scm_anEventOutputNames,
  scm_anEOWith,
  scm_anEOWithIndexes,
  1,
  scm_anDataInputNames, scm_aunDIDataTypeIds,
  1,
  scm_anDataOutputNames, scm_aunDODataTypeIds,
  0,
  0
};

void STRING2STRING::executeEvent(int pa_nEIID){
  if(scm_nEventREQID == pa_nEIID){
    OUT() = IN();
    sendOutputEvent(scm_nEventCNFID);
  }
}

STRING2STRING::~STRING2STRING(){
}



