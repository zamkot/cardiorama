/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Thu May 24 08:07:40 EDT 2018 */

#include "rdft/codelet-rdft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_hc2hc.native -fma -compact -variables 4 -pipeline-latency 4 -sign 1 -twiddle-log3 -precompute-twiddles -n 5 -dif -name hb2_5 -include rdft/scalar/hb.h */

/*
 * This function contains 44 FP additions, 40 FP multiplications,
 * (or, 14 additions, 10 multiplications, 30 fused multiply/add),
 * 37 stack variables, 4 constants, and 20 memory accesses
 */
#include "rdft/scalar/hb.h"

static void hb2_5(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(10, rs)) {
	       E T9, TB, Tz, Tm, TC, TO, TG, TJ, TA, TF;
	       T9 = W[0];
	       TB = W[3];
	       Tz = W[2];
	       TA = T9 * Tz;
	       TF = T9 * TB;
	       Tm = W[1];
	       TC = FNMS(Tm, TB, TA);
	       TO = FNMS(Tm, Tz, TF);
	       TG = FMA(Tm, Tz, TF);
	       TJ = FMA(Tm, TB, TA);
	       {
		    E T1, Tb, TQ, Tw, T8, Ta, Tn, Tj, TL, Ts, Tq, Tr;
		    {
			 E T4, Tu, T7, Tv;
			 T1 = cr[0];
			 {
			      E T2, T3, T5, T6;
			      T2 = cr[WS(rs, 1)];
			      T3 = ci[0];
			      T4 = T2 + T3;
			      Tu = T2 - T3;
			      T5 = cr[WS(rs, 2)];
			      T6 = ci[WS(rs, 1)];
			      T7 = T5 + T6;
			      Tv = T5 - T6;
			 }
			 Tb = T4 - T7;
			 TQ = FNMS(KP618033988, Tu, Tv);
			 Tw = FMA(KP618033988, Tv, Tu);
			 T8 = T4 + T7;
			 Ta = FNMS(KP250000000, T8, T1);
		    }
		    {
			 E Tf, To, Ti, Tp;
			 Tn = ci[WS(rs, 4)];
			 {
			      E Td, Te, Tg, Th;
			      Td = ci[WS(rs, 3)];
			      Te = cr[WS(rs, 4)];
			      Tf = Td + Te;
			      To = Td - Te;
			      Tg = ci[WS(rs, 2)];
			      Th = cr[WS(rs, 3)];
			      Ti = Tg + Th;
			      Tp = Tg - Th;
			 }
			 Tj = FMA(KP618033988, Ti, Tf);
			 TL = FNMS(KP618033988, Tf, Ti);
			 Ts = To - Tp;
			 Tq = To + Tp;
			 Tr = FNMS(KP250000000, Tq, Tn);
		    }
		    cr[0] = T1 + T8;
		    ci[0] = Tn + Tq;
		    {
			 E Tk, TD, Tx, TH, Tc, Tt;
			 Tc = FMA(KP559016994, Tb, Ta);
			 Tk = FNMS(KP951056516, Tj, Tc);
			 TD = FMA(KP951056516, Tj, Tc);
			 Tt = FMA(KP559016994, Ts, Tr);
			 Tx = FMA(KP951056516, Tw, Tt);
			 TH = FNMS(KP951056516, Tw, Tt);
			 {
			      E Tl, Ty, TE, TI;
			      Tl = T9 * Tk;
			      cr[WS(rs, 1)] = FNMS(Tm, Tx, Tl);
			      Ty = Tm * Tk;
			      ci[WS(rs, 1)] = FMA(T9, Tx, Ty);
			      TE = TC * TD;
			      cr[WS(rs, 4)] = FNMS(TG, TH, TE);
			      TI = TG * TD;
			      ci[WS(rs, 4)] = FMA(TC, TH, TI);
			 }
		    }
		    {
			 E TM, TT, TR, TV, TK, TP;
			 TK = FNMS(KP559016994, Tb, Ta);
			 TM = FMA(KP951056516, TL, TK);
			 TT = FNMS(KP951056516, TL, TK);
			 TP = FNMS(KP559016994, Ts, Tr);
			 TR = FNMS(KP951056516, TQ, TP);
			 TV = FMA(KP951056516, TQ, TP);
			 {
			      E TN, TS, TU, TW;
			      TN = TJ * TM;
			      cr[WS(rs, 2)] = FNMS(TO, TR, TN);
			      TS = TO * TM;
			      ci[WS(rs, 2)] = FMA(TJ, TR, TS);
			      TU = Tz * TT;
			      cr[WS(rs, 3)] = FNMS(TB, TV, TU);
			      TW = TB * TT;
			      ci[WS(rs, 3)] = FMA(Tz, TV, TW);
			 }
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_CEXP, 1, 1},
     {TW_CEXP, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 5, "hb2_5", twinstr, &GENUS, {14, 10, 30, 0} };

void X(codelet_hb2_5) (planner *p) {
     X(khc2hc_register) (p, hb2_5, &desc);
}
#else

/* Generated by: ../../../genfft/gen_hc2hc.native -compact -variables 4 -pipeline-latency 4 -sign 1 -twiddle-log3 -precompute-twiddles -n 5 -dif -name hb2_5 -include rdft/scalar/hb.h */

/*
 * This function contains 44 FP additions, 32 FP multiplications,
 * (or, 30 additions, 18 multiplications, 14 fused multiply/add),
 * 33 stack variables, 4 constants, and 20 memory accesses
 */
#include "rdft/scalar/hb.h"

static void hb2_5(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(10, rs)) {
	       E Th, Tk, Ti, Tl, Tn, TP, Tx, TN;
	       {
		    E Tj, Tw, Tm, Tv;
		    Th = W[0];
		    Tk = W[1];
		    Ti = W[2];
		    Tl = W[3];
		    Tj = Th * Ti;
		    Tw = Tk * Ti;
		    Tm = Tk * Tl;
		    Tv = Th * Tl;
		    Tn = Tj + Tm;
		    TP = Tv + Tw;
		    Tx = Tv - Tw;
		    TN = Tj - Tm;
	       }
	       {
		    E T1, Tp, TK, TA, T8, To, T9, Tt, TI, TC, Tg, TB;
		    {
			 E T4, Ty, T7, Tz;
			 T1 = cr[0];
			 {
			      E T2, T3, T5, T6;
			      T2 = cr[WS(rs, 1)];
			      T3 = ci[0];
			      T4 = T2 + T3;
			      Ty = T2 - T3;
			      T5 = cr[WS(rs, 2)];
			      T6 = ci[WS(rs, 1)];
			      T7 = T5 + T6;
			      Tz = T5 - T6;
			 }
			 Tp = KP559016994 * (T4 - T7);
			 TK = FMA(KP951056516, Ty, KP587785252 * Tz);
			 TA = FNMS(KP951056516, Tz, KP587785252 * Ty);
			 T8 = T4 + T7;
			 To = FNMS(KP250000000, T8, T1);
		    }
		    {
			 E Tc, Tr, Tf, Ts;
			 T9 = ci[WS(rs, 4)];
			 {
			      E Ta, Tb, Td, Te;
			      Ta = ci[WS(rs, 3)];
			      Tb = cr[WS(rs, 4)];
			      Tc = Ta - Tb;
			      Tr = Ta + Tb;
			      Td = ci[WS(rs, 2)];
			      Te = cr[WS(rs, 3)];
			      Tf = Td - Te;
			      Ts = Td + Te;
			 }
			 Tt = FNMS(KP951056516, Ts, KP587785252 * Tr);
			 TI = FMA(KP951056516, Tr, KP587785252 * Ts);
			 TC = KP559016994 * (Tc - Tf);
			 Tg = Tc + Tf;
			 TB = FNMS(KP250000000, Tg, T9);
		    }
		    cr[0] = T1 + T8;
		    ci[0] = T9 + Tg;
		    {
			 E Tu, TF, TE, TG, Tq, TD;
			 Tq = To - Tp;
			 Tu = Tq - Tt;
			 TF = Tq + Tt;
			 TD = TB - TC;
			 TE = TA + TD;
			 TG = TD - TA;
			 cr[WS(rs, 2)] = FNMS(Tx, TE, Tn * Tu);
			 ci[WS(rs, 2)] = FMA(Tn, TE, Tx * Tu);
			 cr[WS(rs, 3)] = FNMS(Tl, TG, Ti * TF);
			 ci[WS(rs, 3)] = FMA(Ti, TG, Tl * TF);
		    }
		    {
			 E TJ, TO, TM, TQ, TH, TL;
			 TH = Tp + To;
			 TJ = TH - TI;
			 TO = TH + TI;
			 TL = TC + TB;
			 TM = TK + TL;
			 TQ = TL - TK;
			 cr[WS(rs, 1)] = FNMS(Tk, TM, Th * TJ);
			 ci[WS(rs, 1)] = FMA(Th, TM, Tk * TJ);
			 cr[WS(rs, 4)] = FNMS(TP, TQ, TN * TO);
			 ci[WS(rs, 4)] = FMA(TN, TQ, TP * TO);
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_CEXP, 1, 1},
     {TW_CEXP, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 5, "hb2_5", twinstr, &GENUS, {30, 18, 14, 0} };

void X(codelet_hb2_5) (planner *p) {
     X(khc2hc_register) (p, hb2_5, &desc);
}
#endif
