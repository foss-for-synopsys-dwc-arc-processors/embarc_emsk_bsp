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

/**
 * Vector ALU operations
 */

/**
 * \brief  Dual 16-bit SIMD addition.
		if (cc) {
			a.h0 = b.h0 + c.h0;
			a.h1 = b.h1 + c.h1;
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vadd2h(b, c)			_vadd2h(b, c)
extern unsigned _vadd2h(unsigned, unsigned);
#pragma intrinsic(_vadd2h, name => "vadd2h");

/**
 * \brief  Two-way 16-bit vector addition.
		a.h1 = SAT16(b.h1+c.h1);
		a.h0 = SAT16(b.h0+c.h0);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vadds2h(b, c)			_vadds2h(b, c)
extern unsigned _vadds2h(unsigned, unsigned);
#pragma intrinsic(_vadds2h, name => "vadds2h");

/**
 * \brief  Two-way 16-bit vector subtraction.
		if (cc) {
			a.h0 = b.h0 - c.h0;
			a.h1 = b.h1 - c.h1;
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vsub2h(b, c)			_vsub2h(b, c)
extern unsigned _vsub2h(unsigned, unsigned);
#pragma intrinsic(_vsub2h, name => "vsub2h");

/**
 * \brief  Dual 16-bit vector subtraction. The result is saturated.
		if (cc) {
			a.h0 = SAT16(b.h0 - c.h0);
			a.h1 = SAT16(b.h1 - c.h1);
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vsubs2h(b, c)			_vsubs2h(b, c)
extern unsigned _vsubs2h(unsigned, unsigned);
#pragma intrinsic(_vsubs2h, name => "vsubs2h");

/**
 * \brief  Dual 16-bit vector subtraction and addition.
		if (cc) {
			a.h0 = b.h0 - c.h0;
			a.h1 = b.h1 + c.h1;
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vsubadd2h(b, c)			_vsubadd2h(b, c)
extern unsigned _vsubadd2h(unsigned, unsigned);
#pragma intrinsic(_vsubadd2h, name => "vsubadd2h");

/**
 * \brief  Dual 16-bit vector subtraction and addition.
 	   The results are saturated.
		if (cc) {
			a.h0 = SAT16(b.h0 - c.h0);
			a.h1 = SAT16(b.h1 + c.h1);
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vsubadds2h(b, c)			_vsubadds2h(b, c)
extern unsigned _vsubadds2h(unsigned, unsigned);
#pragma intrinsic(_vsubadds2h, name => "vsubadds2h");

/**
 * \brief  Perform a two-way arithmetic shift left operation 16-bit vectors.
 	   The shift amount is specified in the second operand.
		a.h1 = b.h1 << c.h1;
		a.h0 = b.h0 << c.h0;
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vasl2h(b, c)			_vasl2h(b, c)
extern unsigned _vasl2h(unsigned, unsigned);
#pragma intrinsic(_vasl2h, name => "vasl2h");

/**
 * \brief  Two-way 16-bit vector arithmetic shift left and store
 	   the saturated result.
		a.h1 = SAT16(b.h1 << c.h1);
		a.h0 = SAT16(b.h0 << c.h0);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vasls2h(b, c)			_vasls2h(b, c)
extern unsigned _vasls2h(unsigned, unsigned);
#pragma intrinsic(_vasls2h, name => "vasls2h");

/**
 * \brief  Perform a two-way arithmetic shift right operation on 16-bit vectors.
 	   The shift amount is specified in the second operand.
		a.h1 = b.h1 >> c.h1;
		a.h0 = b.h0 >> c.h0;
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vasr2h(b, c)			_vasr2h(b, c)
extern unsigned _vasr2h(unsigned, unsigned);
#pragma intrinsic(_vasr2h, name => "vasr2h");

/**
 * \brief  Perform a two-way arithmetic shift right operation on 16-bit vectors.
 	   The result is saturated.
		a.h1 = SAT16(b.h1 >> c.h1);
		a.h0 = SAT16(b.h0 >> c.h0);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vasrs2h(b, c)			_vasrs2h(b, c)
extern unsigned _vasrs2h(unsigned, unsigned);
#pragma intrinsic(_vasrs2h, name => "vasrs2h");

/**
 * \brief  Perform a two-way logical shift right operation on 16-bit vectors.
 		a.h1 = unsigned (b.h1) >> c.h1;
		a.h0 = unsigned (b.h0) >> c.h0;
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vlsr2h(b, c)			_vlsr2h(b, c)
extern unsigned _vlsr2h(unsigned, unsigned);
#pragma intrinsic(_vlsr2h, name => "vlsr2h");

/**
 * \brief  Perform a two-way arithmetic shift right operation on 16-bit vectors.
 	   The result is rounded and saturated.
 		a.h1 = SAT16(RND16(b.h1 >> c.h1));
		a.h0 = SAT16(RND16(b.h0 >> c.h0));
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vasrsr2h(b, c)			_vasrsr2h(b, c)
extern unsigned _vasrsr2h(unsigned, unsigned);
#pragma intrinsic(_vasrsr2h, name => "vasrsr2h");

/**
 * \brief  Compare two-way 16-bit vectors and return the maximum.
 		a.h1 = max(b.h1, c.h1);
		a.h0 = max(b.h0, c.h0);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmax2h(b, c)			_vmax2h(b, c)
extern unsigned _vmax2h(unsigned, unsigned);
#pragma intrinsic(_vmax2h, name => "vmax2h");

/**
 * \brief  Four-way eight-bit vector subtraction.
 		a.b3 = b.b3 - c.b3;
		a.b2 = b.b2 - c.b2;
		a.b1 = b.b1 - c.b1;
		a.b0 = b.b0 - c.b0;
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vsub4b(b, c)			_vsub4b(b, c)
extern unsigned _vsub4b(unsigned, unsigned);
#pragma intrinsic(_vsub4b, name => "vsub4b");

/**
 * \brief  Compare two-way 16-bit signed vectors and return the minimum.
 		a.h1 = min(b.h1, c.h1);
		a.h0 = min(b.h0, c.h0);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmin2h(b, c)			_vmin2h(b, c)
extern unsigned _vmin2h(unsigned, unsigned);
#pragma intrinsic(_vmin2h, name => "vmin2h");

/**
 * \brief  Absolute value of a two-way 16-bit vector.
		b.h1 = ABS(c.h1);
		b.h0 = ABS(c.h0);
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vabs2h(c)				_vabs2h(c)
extern unsigned _vabs2h(unsigned);
#pragma intrinsic(_vabs2h, name => "vabs2h");

/**
 * \brief  Saturated absolute value of a two-way 16-bit vector.
		b.h1 = SAT16(ABS(c.h1));
		b.h0 = SAT16(ABS(c.h0));
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vabss2h(c)				_vabss2h(c)
extern unsigned _vabss2h(unsigned);
#pragma intrinsic(_vabss2h, name => "vabss2h");

/**
 * \brief  Negate the two 16-bit vectors of an operand
 	   and store the negated value in the destination operand.
		b.h1 = -c.h1;
		b.h0 = -c.h0;
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vneg2h(c)				_vneg2h(c)
extern unsigned _vneg2h(unsigned);
#pragma intrinsic(_vneg2h, name => "vneg2h");

/**
 * \brief  Negate the two 16-bit vectors of an operand
 	   and store the saturated negated value in the destination operand.
		b.h1 = SAT16(-c.h1);
		b.h0 = SAT16(-c.h0);
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vnegs2h(c)				_vnegs2h(c)
extern unsigned _vnegs2h(unsigned);
#pragma intrinsic(_vnegs2h, name => "vnegs2h");

/**
 * \brief  Two-way 16-bit vector normalization.
		b.h1 = norm(c.h1);
		b.h0 = norm(c.h0);
 * \param[in] unsigned c
 * \return unsigned b
 */
#define _arc_vnorm2h(c)				_vnorm2h(c)
extern unsigned _vnorm2h(unsigned);
#pragma intrinsic(_vnorm2h, name => "vnorm2h");

/**
 * Accumulator operations
 */

/**
 * \brief  Perform an arithmetic shift of the accumulator.
		switch (c.b1) {
			0: accwide = accwide << c.b0;
			1: acclo = acclo << c.b0;
			2: acchi = acchi << c.b0;
			3: acchi = acchi << c.b2; acclo = acclo << c.b0;
		}
 * \param[in] int c
 */
#define _arc_aslacc(c)				_aslacc(c)
extern void _aslacc(int);
#pragma intrinsic(_aslacc, name => "aslacc" __ACC_RW_EFFECTS);

/**
 * \brief  Perform an arithmetic shift of the accumulator.
		if (DSP_CTRL.GE) {
			switch (c.b1) {
			0: accwide = SAT72(accwide << c.b0);
			1: acclo = SAT40(acclo << c.b0);
			2: acchi = SAT40(acchi << c.b0);
			3: acchi = SAT40(acchi << c.b2); acclo = SAT40(acclo << c.b0);
		} else {
			switch (c.b1) {
			0: accwide = SAT64(accwide << c.b0);
			1: acclo = SAT32(acclo << c.b0);
			2: acchi = SAT32(acchi << c.b0);
			3: acchi = SAT32(acchi << c.b2); acclo = SAT32(acclo << c.b0);
		}
 * \param[in] int c
 */
#define _arc_aslsacc(c)				_aslsacc(c)
extern void _aslsacc(int);
#pragma intrinsic(_aslsacc, name => "aslsacc" __ACC_RW_EFFECTS);

/**
 * \brief  Copy accumulator flags to the STATUS32 register.
		switch (c.b1) {
			0,2,3: STATUS32.ZNCV = ACC0_GHI.ZNCV;
			1: STATUS32.ZNCV = ACC0_GLO.ZNCV;
		}
 * \param[in] int c
 */
#define _arc_flagacc(c)				_flagacc(c)
extern void _flagacc(int c);
#pragma intrinsic(_flagacc, name=>"flagacc", assume_volatile=>1, \
	effects=>"%status:is_written;%acc0_glo:is_read;%acc0_ghi:is_read");

/**
 * \brief  Set the accumulator value.
		if (c & 0x1) {
			switch (c.b1) {
				0: accwide = (int) b;
				1: acclo = (int) b;
				2: acchi = (int) b;
				3: acchi = (int) b; acclo = (int) b;
				4: accwide = (fract) b;
				5: acclo = (fract) b;
				6: acchi = (fract) b;
				7: acclo = (fract) b; acchi = (fract) b;
				8: accwide = (unsigned) b;
				9: acclo = (unsigned) b;
				10: acchi = (unsigned) b;
				11: acclo = (unsigned) b; acchi = (unsigned) b;
			}
		}
		else {
			switch (c.b1) {
				0: ACC0_LO = b;
				1: ACC0_HI = b;
				2: ACC0_GLO.GUARD = b;
				3: ACC0_GHI.GUARD = b;
			}
		}
 * \param[in] int b
 * \param[in] int c
 * \return int a
 */
#define _arc_setacc(b, c)			_setacc(b, c)
extern int _setacc(int, int);
#pragma intrinsic(_setacc, name=> "setacc" __ACC_W_EFFECTS);

/**
 * \brief  Get the accumulator value.
		b = shift_round_sat(acc, c);
 * \param[in] int c
 * \return int b
 */
#define _arc_getacc(c)				_getacc(c)
extern int _getacc(int);
#pragma intrinsic(_getacc, name=> "getacc" __ACC_R_EFFECTS);

/**
 * \brief  Get the accumulator value.
		switch (c.b1) {
			0: b.b0 = norm(accwide);
			1: b.b0 = norm(acclo);
			2: b.b0 = norm(acchi);
			3: b.b2 = norm(acchi); b.b0 = norm(acclo);
		}
 * \param[in] int c
 * \return int b
 */
#define _arc_normacc(c)				_normacc(c)
extern int _normacc(int);
#pragma intrinsic(_normacc, name=> "normacc" __ACC_R_EFFECT);

/**
 * Vector 16x16 MAC operations
 */

/**
 * \brief  Two-way signed multiplication and subtraction of
	   two 16-bit fractional vectors. The result is rounded and saturated.
		a.h1 = SAT16(RND16((acchi -= (b.h1*c.h1))<<1));
		a.h0 = SAT16(RND16((acclo -= (b.h0*c.h0))<<1));
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmsub2hfr(b, c)			_vmsub2hfr(b, c)
extern unsigned _vmsub2hfr(unsigned, unsigned);
#pragma intrinsic(_vmsub2hfr, name=> "vmsub2hfr" __ACC_RW_EFFECTS);

/**
 * \brief  Two-way signed multiplication and subtraction of two 16-bit fractional vectors.
 	   The result is saturated and stored.
		a.h1 = SAT16((acchi -= (b.h1*c.h1))<<1);
		a.h0 = SAT16((acclo -= (b.h0*c.h0))<<1);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmsub2hf(b, c)			_vmsub2hf(b, c)
extern unsigned _vmsub2hf(unsigned, unsigned);
#pragma intrinsic(_vmsub2hf, name=> "vmsub2hf" __ACC_RW_EFFECTS);

/**
 * \brief  Two-way signed multiplication and accumulation of two 16-bit fractional vectors.
 	   The result is rounded and saturated, and returned without a fractional shift.
		a.h1 = SAT16(RND16(acchi + (b.h1 * c.h1)));
		a.h0 = SAT16(RND16(acclo + (b.h0 * c.h0)));
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmac2hnfr(b, c)			_vmac2hnfr(b, c)
extern unsigned _vmac2hnfr(unsigned, unsigned);
#pragma intrinsic(_vmac2hnfr, name=> "vmac2hnfr" __ACC_RW_EFFECTS);

/**
 * \brief  Two-way signed multiplication and subtraction of two 16-bit fractional vectors.
 	   The result is saturated, and returned without a fractional shift.
		a.h1 = SAT16(RND16(acchi - (b.h1*c.h1)));
		a.h0 = SAT16(RND16(acclo - (b.h0*c.h0)));
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmsub2hnfr(b, c)			_vmsub2hnfr(b, c)
extern unsigned _vmsub2hnfr(unsigned, unsigned);
#pragma intrinsic(_vmsub2hnfr, name=> "vmsub2hnfr" __ACC_RW_EFFECTS);

/**
 * \brief  Dual 16-bit SIMD multiplication.
		if (cc) {
			acc.w0 = A.w0 = b.h0 * c.h0;
			acc.w1 = A.w1 = b.h1 * c.h1;
		}
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return long long a
 */
#define _arc_vmpy2h(b, c)			_vmpy2h(b, c)
extern long long _vmpy2h(unsigned, unsigned);
#pragma intrinsic(_vmpy2h, name=> "vmpy2h" __ACC_W_EFFECTS);

/**
 * \brief  Two-way signed multiplication of two 16-bit fractional vectors.
 	   The result is saturated and stored.
		a.h1 = SAT16((acchi =(b.h1 * c.h1))<<1);
		a.h0 = SAT16((acclo =(b.h0 * c.h0))<<1);
 * \param[in] unsigned b
 * \param[in] unsigned c
 * \return unsigned a
 */
#define _arc_vmpy2hf(b, c)			_vmpy2hf(b, c)
extern unsigned _vmpy2hf(unsigned, unsigned);
#pragma intrinsic(_vmpy2hf, name=> "vmpy2hf" __ACC_W_EFFECTS);

#endif /* ARC_FEATURE_DSP2 */

#endif /* __MW__ */

#ifdef __cplusplus
}
#endif

#endif	/* _ARC_DSP_INSTR_MW_H_ */

 /**  @} */
