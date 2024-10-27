/*******************************************************************************
 * Copyright (c) 2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Martin Erich Jobst - initial implementation
 *******************************************************************************/
#pragma once

#include <array>

namespace forte::core::util {

  template<typename T, std::size_t size>
  class CRingBuffer {
  public:
    CRingBuffer() = default;

    bool push(T &elem) {
      if(isFull()) {
        return false;
      }
      mData[mPushIndex++ & cmIndexMask] = elem;
      return true;
    }

    T *pop() {
      if(isEmpty()) {
        return nullptr;
      }
      return &mData[mPopIndex++ & cmIndexMask];
    }

    void clear() {
      mPopIndex = 0;
      mPushIndex = 0;
    }

    constexpr bool isEmpty() const {
      return mPopIndex == mPushIndex;
    }

    constexpr bool isFull() const {
      return mPushIndex == mPopIndex + cmIndexMask;
    }

    static_assert((size & (size - 1)) == 0, "size must be a power of 2");
  private:
    constexpr static std::size_t cmIndexMask = size - 1;

    std::size_t mPopIndex{0};
    std::size_t mPushIndex{0};
    std::array<T, size> mData;
  };
}

