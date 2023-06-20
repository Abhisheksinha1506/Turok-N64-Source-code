/*
 *  hand made primitives for Qsim tests
 */

#ifndef QSIM_PRIMS_INCLD
#define QSIM_PRIMS_INCLD


/*
 *  initial primitive to get steppers going
 */
static unsigned long qsim_p0[] = {
  0xcf80044d, 0x0113010d,
  0x00ae8000, 0xffff17a0,
  0x0079e98e, 0xffff59c8,
  0x0070f560, 0x00232a80,
  0x00150014, 0x00c900ff,
  0x0003ffff, 0xfffc0000,
  0x0000c8ce, 0xf7320000,
  0x59aef9d0, 0xac800000,
  0x00000000, 0xffff0000,
  0x00020000, 0xfffc0000,
  0x0000dcc8, 0x23380000,
  0x2ebbd983, 0xf7c10000,
  0x000008d9, 0x2d270005,
  0x00070000, 0xfffdffff,
  0x0000a7d6, 0x9413a4f6,
  0xe5894dc0, 0x29b0ffa5,
  0x0000fff5, 0x00650000,
  0x0005fff5, 0x00630000,
  0x000028a9, 0x45ac0ca8,
  0x24ea51bd, 0xc5f20c78,
  0x62d8a238, 0xfffbf120,
  0xff95a0a0, 0xff929e00
};


/*
 *  Put Edge Walker, increment edge by ones
 *  walk entire range of in Y
 */
static unsigned long qsim_p1[] = {
  0xcf001d9c, 0x1c4a01e0, /* yl, ym, yh */
  0x004b4000, 0x000066c8, /* xl, dxldy */
  0x00a00000, 0xfffff8d8, /* xh, dxhdy */
  0x00a00000, 0xfffff368, /* xm, dxmdy */
  0x00000000, 0x00000000, /* r, g, b, a */
  0x00010002, 0x00040008, /* dxr, dxg, dxb, dxa */
  0xaaaaaaaa, 0xaaaaaaaa, /* rf, gf, bf, af */
  0x55555555, 0x55555555, /* dxrf, dxgf, dxbf, dxaf */
  0x00080004, 0x00020001, /* der, deg, deb, dea */
  0x00010002, 0x00040008, /* dyr, dyg, dyb, dya */
  0xaaaaaaaa, 0xaaaaaaaa, /* derf, degf, debf, deaf */
  0x55555555, 0x55555555, /* dyrf, dygf, dybf, dyaf */
  0x00010002, 0x00040008, /* s, t, w, l */
  0x00080004, 0x00020001, /* dxs, dxt, dxw, dxl */
  0xaaaaaaaa, 0xaaaaaaaa, /* sf, tf, wf, lf */
  0x55555555, 0x55555555, /* dxsf, dxtf, dxwf, dxlf */
  0x00010002, 0x00040008, /* des, det, dew, del */
  0x00080004, 0x00020001, /* dys, dyt, dyw, dyl */
  0xaaaaaaaa, 0xaaaaaaaa, /* desf, detf, dewf, delf */
  0x55555555, 0x55555555, /* dysf, dytf, dywf, dylf */
  0x0008aa55, 0x000455aa, /* z, zf, dxz, dxzf */
  0x0002aa55, 0x000155aa  /* dez, dezf, dzy, dzyf */
};

/*
 *  Put Edge Walker, increment edge by 5555aaaa
 *  walk entire range in X
 */
static unsigned long qsim_p2[] = {
  0xcf001d9c, 0x1c4a01e0,
  0x004b4000, 0x000066c8,
  0x00a00000, 0xfffff8d8,
  0x00a00000, 0xfffff368,
  0x00800080, 0x00800080, /* r, g, b, a */
  0x11112222, 0x44448888, /* dxr, dxg, dxb, dxa */
  0xaaaaaaaa, 0xaaaaaaaa, /* rf, gf, bf, af */
  0x55555555, 0x55555555, /* dxrf, dxgf, dxbf, dxaf */
  0x88884444, 0x22221111, /* der, deg, deb, dea */
  0x11112222, 0x44448888, /* dyr, dyg, dyb, dya */
  0xaaaaaaaa, 0xaaaaaaaa, /* derf, degf, debf, deaf */
  0x55555555, 0x55555555, /* dyrf, dygf, dybf, dyaf */
  0x11112222, 0x44448888, /* s, t, w, l */
  0x88884444, 0x22221111, /* dxs, dxt, dxw, dxl */
  0xaaaaaaaa, 0xaaaaaaaa, /* sf, tf, wf, lf */
  0x55555555, 0x55555555, /* dxsf, dxtf, dxwf, dxlf */
  0x11112222, 0x44448888, /* des, det, dew, del */
  0x88884444, 0x22221111, /* dys, dyt, dyw, dyl */
  0xaaaaaaaa, 0xaaaaaaaa, /* desf, detf, dewf, delf */
  0x55555555, 0x55555555, /* dysf, dytf, dywf, dylf */
  0x8888aa55, 0x444455aa, /* z, zf, dxz, dxzf */
  0x2222aa55, 0x111155aa  /* dez, dezf, dzy, dzyf */
};


#endif /* QSIM_PRIMS_INCLD */
