#*******************************************************************************
# Copyright (c) 2010 - 2014 ACIN, fortiss GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Alois Zoitl, Monika Wenger
# *     - initial API and implementation and/or initial documentation
# *******************************************************************************/

#############################################################################
# Event FB
#############################################################################
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
SET(SOURCE_GROUP ${SOURCE_GROUP}\\events)


forte_add_sourcefile_hcpp(E_CTU_fbt E_CTD_fbt E_CTUD_fbt E_CTUD_UDINT_fbt E_DELAY_fbt  E_D_FF_fbt    E_MERGE_fbt)
forte_add_sourcefile_hcpp( E_REND_fbt   E_RS_fbt     E_SELECT_fbt  E_SR_fbt)
forte_add_sourcefile_hcpp(E_CYCLE_fbt   E_DEMUX_fbt  E_F_TRIG_fbt  E_PERMIT_fbt) 
forte_add_sourcefile_hcpp(E_RDELAY_fbt   E_RESTART_fbt E_R_TRIG_fbt E_SPLIT_fbt   E_SWITCH_fbt)
forte_add_sourcefile_hcpp(GEN_E_DEMUX_fbt GEN_E_MUX_fbt)
forte_add_sourcefile_hcpp(ATimeOut_adp E_TimeOut_fbt ARTimeOut_adp E_RTimeOut_fbt E_T_FF_fbt)
forte_add_sourcefile_hcpp(E_TRAIN_fbt)
forte_add_sourcefile_hcpp(E_PULSE_fbt E_TP_fbt E_TON_fbt E_TOF_fbt E_TONOF_fbt)
forte_add_sourcefile_hcpp(E_TRIG_fbt)