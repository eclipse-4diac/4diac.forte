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
  CancelGoal.cxx
  CancelGoalPubSubTypes.cxx

  # already defined
  # GoalInfo.cxx 
  # GoalInfoPubSubTypes.cxx
  # Time.cxx
  # TimePubSubTypes.cxx
  # UUID.cxx
  # UUIDPubSubTypes.cxx
)

forte_add_sourcefile_h(
  CancelGoal.h
  CancelGoalPubSubTypes.h
  GoalInfo.h
  GoalInfoPubSubTypes.h
  Time.h
  TimePubSubTypes.h
  UUID.h
  UUIDPubSubTypes.h
)

forte_add_sourcefile_hcpp(
  CancelGoalRequestPubSub
  CancelGoalResponsePubSub
)
