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
 * \version 2017.05
 * \date 2017-05-08
 * \author Qiang Gu(Qiang.Gu@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_DSP_INSTR_MW
 * \brief  header file including DSP instructions/functions for MetaWare toolchain
 */

 /**
  * \addtogroup ARC_DSP_INSTR_MW
  * @{
  */


#ifndef _ARC_DSP_INSTR_MW_H_
#define _ARC_DSP_INSTR_MW_H_

#include "arc_core_config.h"
#include "inc/embARC_toolchain.h"

/** Support for ARC EM DSP instructions
 *  For the ARC EM family only
 */
#if !defined(ARC_FEATURE_DSP2)
#if defined(core_config_dsp2) && core_config_dsp2 == 1
#define ARC_FEATURE_DSP2		1
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__MW__) && _ARCVER >= 0x42

#if defined(ARC_FEATURE_DSP2) && ARC_FEATURE_DSP2 == 1
/**
 * Basic saturating arithmetic operations
 */

/**
 * \brief  Sature a 32-bit value to 16-bit value.
 * \param[in] int operand
 * \return int b = SAT16(c)
 */
#define _arc_sath(c)			_sath(c)
extern int _sath(int);
#pragma intrinsic(_sath, name => "sath", flags=> "znv");

/**
 * \brief  Round and sature a 32-bit value to 16-bit value.
 * \param[in] int operand
 * \return int b = SAT16(RND16(c))
 */
#define _arc_rndh(c)			_rndh(c)
extern int _rndh(int);
#pragma intrinsic(_rndh, name => "rndh", flags=> "znv");

/**
 * \brief  Compute the absolute value of a 16-bit element and saturate the result.
 * \param[in] int operand
 * \return int b = SAT16(ABS(c.h0))
 */
#define _arc_abssh(c)			_abssh(c)
extern int _abssh(int);
#pragma intrinsic(_abssh, name => "abssh");

/**
 * \brief  Compute the absolute value of a 32-bit operand and saturate the result.
 * \param[in] int operand
 * \return int b = SAT32(ABS(c))
 */
#define _arc_abss(c)			_abss(c)
extern int _abss(int);
#pragma intrinsic(_abss, name => "abss");

/**
 * \brief  Negate the lower 16 bits of a word and saturate the result.
 * \param[in] int operand
 * \return int b = SAT16(-c)
 */
#define _arc_negsh(c)			_negsh(c)
extern int _negsh(int);
#pragma intrinsic(_negsh, name => "negsh", flags=>"znv");

/**
 * \brief  Negate a 32-bit word and saturate the result.
 * \param[in] int operand
 * \return int b = SAT32(-c)
 */
#define _arc_negs(c)			_negs(c)
extern int _negs(int);
#pragma intrinsic(_negs, name => "negs");

/**
 * \brief  Signed 32-bit addtion. The result is saturated.
 * \param[in] int operand
 * \param[in] int operand
 * \return int a = SAT32(b + c)
 */
#define _arc_adds(b, c)			_adds(b, c)
extern int _adds(int, int);
#pragma intrinsic(_adds, name => "adds");

/**
 * \brief  Signed 32-bit subtraction. The result is saturated.
 * \param[in] int operand
 * \param[in] int operand
 * \return int a = SAT32(b – c)
 */
#define _arc_subs(b, c)			_subs(b, c)
extern int _subs(int, int);
#pragma intrinsic(_subs, name => "subs");

/**
 * \brief  Perform an arithmetic shift left operation on an operand.
           The shift amount is specified in the second operand.
           Store the saturated result in the destination register.
 * \param[in] int operand
 * \param[in] int operand
 * \return int a = c >= 0 ? SAT32(b << c) : b >> -c
 */
#define _arc_asls(b, c)			_asls(b, c)
extern int _asls(int, int);
#pragma intrinsic(_asls, name => "asls");

/**
 * \brief  Perform an arithmetic shift right operation on an operand.
           The shift amount is specified in the second operand.
           Store the saturated result in the destination register.
 * \param[in] int operand
 * \param[in] int operand
 * \return int a = c > =0 ? b >> c : SAT32( b<< -c)
 */
#define _arc_asrs(b, c)			_asrs(b, c)
extern int _asrs(int, int);
#pragma intrinsic(_asrs, name => "asrs");

/**
 * \brief  Perform an arithmetic shift right operation on an operand.
           The shift amount is specified in the second operand.
           Store the rounded and saturated result in the destination register.
 * \param[in] int operand
 * \param[in] int operand
 * \return int a = c >= 0 ? RND32(b >> c) : SAT32(b << -c)
 */
#define _arc_asrsr(b, c)			_asrsr(b, c)
extern int _asrsr(int,int);
#pragma intrinsic(_asrsr, name => "asrsr", flags=> "znv");

/**
 * Vector unpacking operations
 */

/**
 * \brief  Two-way 16-bit vector addition and subtraction.
 	   The results are saturated and stored.
 	   if (cc) {
		a.h0 = SAT16(b.h0 + c.h0);
		a.h1 = SAT16(b.h1 - c.h1);
	   }
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_valgn2h(b, c)			_valgn2h(b, c)
extern unsigned _valgn2h(unsigned, unsigned);
#pragma intrinsic(_valgn2h, name => "valgn2h");

/**
 * \brief  Compose a dual 16-bit vector by replicating
 	   the least-significant 16 bits of an operand.
		b.h1 = c.h0;
		b.h0 = c.h0;
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vrep2hl(c)				_vrep2hl(c)
extern unsigned _vrep2hl(unsigned);
#pragma intrinsic(_vrep2hl, name => "vrep2hl");

/**
 * \brief  Compose a dual 16-bit vector by replicating
 	   the most-significant 16 bits of an operand.
		b.h1 = c.h1;
		b.h0 = c.h1;
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vrep2hm(c)				_vrep2hm(c)
extern unsigned _vrep2hm(unsigned);
#pragma intrinsic(_vrep2hm, name => "vrep2hm");

/**
 * \brief  Compose a dual 16-bit vector by zero-extending
 	   lower two bytes of an operand.
		b.b3 = 0;
		b.b2 = c.b1;
		b.b1 = 0;
		b.b0 = c.b0;
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vext2bhl(c)			_vext2bhl(c)
extern unsigned _vext2bhl(unsigned);
#pragma intrinsic(_vext2bhl, name => "vext2bhl");

/**
 * \brief  Compose a dual 16-bit vector by zero-extending
 	   higher two bytes of an operand.
		b.b3 = 0;
		b.b2 = c.b3;
		b.b1 = 0;
		b.b0 = c.b2;
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vext2bhm(c)			_vext2bhm(c)
extern unsigned _vext2bhm(unsigned);
#pragma intrinsic(_vext2bhm, name => "vext2bhm");

/**
 * \brief  Compose a dual 16-bit vector by sign-extending
 	   lower two bytes of an operand.
		b.h1 = sext(c.b1);
		b.h0 = sext(c.b0);
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vsext2bhl(c)			_vsext2bhl(c)
extern unsigned _vsext2bhl(unsigned);
#pragma intrinsic(_vsext2bhl, name => "vsext2bhl");

/**
 * \brief  Compose a dual 16-bit vector by sign-extending
 	   higher two bytes of an operand.
		b.h1 = sext(c.b3);
		b.h0 = sext(c.b2);
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vsext2bhm(c)			_vsext2bhm(c)
extern unsigned _vsext2bhm(unsigned);
#pragma intrinsic(_vsext2bhm, name => "vsext2bhm");


#endif /* ARC_FEATURE_DSP2 */

#endif /* __MW__ */

#ifdef __cplusplus
}
#endif

#endif	/* _ARC_DSP_INSTR_MW_H_ */

 /**  @} */
