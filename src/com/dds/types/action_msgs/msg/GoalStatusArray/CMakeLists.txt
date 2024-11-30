#*******************************************************************************
# *******************************************************************************
# Copyright (c) 2024 Malte Grave
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#     Malte Grave
# *******************************************************************************/
# *******************************************************************************/

forte_add_sourcefile_cpp(
  GoalStatus.cxx 
  GoalStatusPubSubTypes.cxx
  GoalStatusArray.cxx
  GoalStatusArrayPubSubTypes.cxx
)

forte_add_sourcefile_h(
  Time.h
  TimePubSubTypes.h
  UUID.h
  UUIDPubSubTypes.h
  GoalInfo.h
  GoalInfoPubSubTypes.h
  GoalStatus.h
  GoalStatusPubSubTypes.h
  GoalStatusArray.h
  GoalStatusArrayPubSubTypes.h
)

forte_add_sourcefile_hcpp(
  GoalStatusArrayPubSub
)
