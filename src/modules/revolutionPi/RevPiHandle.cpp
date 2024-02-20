/*******************************************************************************
 * Copyright (c) 2017 fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "RevPiHandle.h"
#include <forte_word.h>

RevPiHandle::RevPiHandle(RevPiController *controller, CIEC_ANY::EDataTypeID type,
    forte::core::IO::IOMapper::Direction direction, uint16_t offset, uint8_t position) :
    forte::core::IO::IOHandle(controller, direction, type), valueLastCheck(0) {
  control.i16uAddress = offset;
  control.i8uBit = position;
  control.i8uValue = 0;
  switch(type){
    case CIEC_ANY::e_BOOL:
      valueLastCheck = new CIEC_BOOL;
      break;
    case CIEC_ANY::e_WORD:
      valueLastCheck = new CIEC_WORD;
      break;
    default:
      valueLastCheck = 0;
  }
}

RevPiHandle::~RevPiHandle(){
  if(0 != valueLastCheck){
    delete valueLastCheck;
  }
}

void RevPiHandle::set(const CIEC_ANY &state) {
  switch(type){
      case CIEC_ANY::e_BOOL:
        control.i8uValue = static_cast<const CIEC_BOOL&>(state) ? 1 : 0;
        piControlSetBitValue(&control);
        break;
      case CIEC_ANY::e_WORD:{
        TForteWord value = static_cast<TForteWord>(static_cast<const CIEC_WORD&>(state));
        piControlWrite(control.i16uAddress, 2,  reinterpret_cast<uint8_t*>(&value));
        break;
      }
      default:
        break;
    }
}

void RevPiHandle::get(CIEC_ANY &state) {
  switch (type){
    case CIEC_ANY::e_BOOL:
      piControlGetBitValue(&control);
      static_cast<CIEC_BOOL&>(state) = control.i8uValue;
      break;
    case CIEC_ANY::e_WORD:{
      TForteWord value;
      piControlRead(control.i16uAddress, 2, reinterpret_cast<uint8_t*>(&value));
      static_cast<CIEC_WORD&>(state) = value;
      break;
    }
    default:
      break;
  }
}

bool RevPiHandle::check() {
  bool changed;
  switch (type){
    case CIEC_ANY::e_BOOL:{
      CIEC_BOOL value;
      get(value);
      changed = value != *static_cast<CIEC_BOOL*>(valueLastCheck);
      valueLastCheck->setValue(value);
      break;
    }
    case CIEC_ANY::e_WORD:{
      CIEC_WORD value;
      get(value);
      changed = value != *static_cast<CIEC_WORD*>(valueLastCheck);
      valueLastCheck->setValue(value);
      break;
    }
    default:
      break;
  }
  return changed;
}

void RevPiHandle::dropObserver() {
  CIEC_WORD state = 0; //should work for boolean too
  set(state);

  forte::core::IO::IOHandle::dropObserver();
}