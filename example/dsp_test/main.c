/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2016-04-20
 * \author Qiang Gu(Qiang.Gu@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	EMBARC_APP_BAREMETAL_BLINKY	embARC Blinky Example
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_BAREMETAL
 * \brief	embARC example for toggle leds on board
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *
 * ### Design Concept
 *     This example is designed to test board without any extra peripheral
 *
 * ### Usage Manual
 *     Toggle all leds on board in 1s period
 *
 * ### Extra Comments
 *
 */

/**
 * \file
 * \ingroup	EMBARC_APP_BAREMETAL_BLINKY
 * \brief	main source file for blinky example
 */

/**
 * \addtogroup	EMBARC_APP_BAREMETAL_BLINKY
 * @{
 */
/* embARC HAL */
#include <stdio.h>
#include <stdlib.h>

#include "board/board.h"
#include "inc/embARC_debug.h"
#include "inc/dsp/arc_dsp_instr_mw.h"

int main(void)
{
	/* Basic saturating arithmetic operations */
	EMBARC_PRINTF("_arc_sath(32768) = %d\r\n", _arc_sath(32768));
	EMBARC_PRINTF("_arc_rndh(32767) = %d\r\n", _arc_rndh(32767));
	EMBARC_PRINTF("_arc_abssh(-32769) = %d\r\n", _arc_abssh(-32769));
	EMBARC_PRINTF("_arc_abss(-32769) = %d\r\n", _arc_abss(-32769));
	EMBARC_PRINTF("_arc_negsh(32767) = %d\r\n", _arc_negsh(32767));
	EMBARC_PRINTF("_arc_negs(32769) = %d\r\n", _arc_negs(32769));
	EMBARC_PRINTF("_arc_adds(10, -51) = %d\r\n",_arc_adds(10, -51));
	EMBARC_PRINTF("_arc_subs(10, -51) = %d\r\n",_arc_subs(10, -51));
	EMBARC_PRINTF("_arc_asls(10, -1) = %d\r\n",_arc_asls(10, -1));
	EMBARC_PRINTF("_arc_asrs(-3, 1) = %d\r\n",_arc_asrs(-3, 1));
	EMBARC_PRINTF("_arc_asrsr(-3, 1) = %d\r\n",_arc_asrsr(-3, 1));

	EMBARC_PRINTF("!!!Hello World!!!\r\n"); /* prints !!!Hello World!!! */

	return EXIT_SUCCESS;
}

/** @} */
