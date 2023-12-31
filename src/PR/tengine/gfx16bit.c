#include "gfx16bit.h"


// numerals 0-9
#include "overlay/font/0.h"
#include "overlay/font/1.h"
#include "overlay/font/2.h"
#include "overlay/font/3.h"
#include "overlay/font/4.h"
#include "overlay/font/5.h"
#include "overlay/font/6.h"
#include "overlay/font/7.h"
#include "overlay/font/8.h"
#include "overlay/font/9.h"
#include "overlay/font/0_4.h"
#include "overlay/font/1_4.h"
#include "overlay/font/2_4.h"
#include "overlay/font/3_4.h"
#include "overlay/font/4_4.h"
#include "overlay/font/5_4.h"
#include "overlay/font/6_4.h"
#include "overlay/font/7_4.h"
#include "overlay/font/8_4.h"
#include "overlay/font/9_4.h"
#include "overlay/font/neg.h"

// actual font
#include "overlay/font/a.h"
#include "overlay/font/b.h"
#include "overlay/font/c.h"
#include "overlay/font/d.h"
#include "overlay/font/e.h"
#include "overlay/font/f.h"
#include "overlay/font/g.h"
#include "overlay/font/h.h"
#include "overlay/font/i.h"
#include "overlay/font/j.h"
#include "overlay/font/k.h"
#include "overlay/font/l.h"
#include "overlay/font/m.h"
#include "overlay/font/n.h"
#include "overlay/font/o.h"
#include "overlay/font/p.h"
#include "overlay/font/q.h"
#include "overlay/font/r.h"
#include "overlay/font/s.h"
#include "overlay/font/t.h"
#include "overlay/font/u.h"
#include "overlay/font/v.h"
#include "overlay/font/w.h"
#include "overlay/font/x.h"
#include "overlay/font/y.h"
#include "overlay/font/z.h"
#include "overlay/font/copy.h"
#include "overlay/font/litl-c.h"
#include "overlay/font/period.h"
#include "overlay/font/comma.h"
#include "overlay/font/quote-l.h"
#include "overlay/font/quote-r.h"
#include "overlay/font/trade.h"
#include "overlay/font/ramp.h"

#ifdef GERMAN
#include "overlay/font/a-g.h"
#include "overlay/font/o-g.h"
#include "overlay/font/u-g.h"
#endif


#include "overlay/font/font.h"

// health
#include "overlay/health/health.h"
#include "overlay/health/armour.h"
#include "overlay/health/turkhead.h"
#include "overlay/health/liforce.h"
#include "overlay/health/airbar.h"
#include "overlay/health/bosbar.h"
#include "overlay/health/bar.h"
#include "overlay/health/bargrad.h"
#include "overlay/health/lens.h"
#include "overlay/health/sun.h"

// inventory stuff
#include "overlay/invent/key2.h"
#include "overlay/invent/key3.h"
#include "overlay/invent/key4.h"
#include "overlay/invent/key5.h"
#include "overlay/invent/key6.h"
#include "overlay/invent/key7.h"
#include "overlay/invent/key8.h"
#include "overlay/invent/chrono.h"

// walk - run icons
#include "overlay/health/walk.h"
#include "overlay/health/run.h"

// boxes
#include "overlay/boxes/rok.h"

// compass
//#include "overlay/compass/nesw.h"

// ammo
#include "overlay/ammo/arrow.h"
#include "overlay/ammo/xarrow.h"
#include "overlay/ammo/bullet.h"
#include "overlay/ammo/shell.h"
#include "overlay/ammo/xshell.h"
#include "overlay/ammo/energy.h"
#include "overlay/ammo/minigun.h"
#include "overlay/ammo/grenade.h"
#include "overlay/ammo/rocket.h"
//#include "overlay/ammo/shockwav.h"
#include "overlay/ammo/kamf.h"

// weapons
#include "overlay/weapons/knife.h"
#include "overlay/weapons/bow.h"
#include "overlay/weapons/pistol.h"
#include "overlay/weapons/rifle.h"
#include "overlay/weapons/shotgun.h"
#include "overlay/weapons/autosh.h"
#include "overlay/weapons/grenade.h"
#include "overlay/weapons/rocket.h"
#include "overlay/weapons/minigun.h"
#include "overlay/weapons/longhunt.h"
#include "overlay/weapons/infntry.h"
#include "overlay/weapons/shock.h"
#include "overlay/weapons/fusion.h"
#include "overlay/weapons/crone.h"


//#include "overlay/pause/slab.h"
#include "overlay/pause/pause.h"
#include "overlay/pause/game.h"
#include "overlay/pause/options.h"
#include "overlay/pause/bar.h"
#include "overlay/pause/slider.h"


#ifdef KANJI
#include "overlay/kanji/00.h"
#include "overlay/kanji/01.h"
#include "overlay/kanji/02.h"
#include "overlay/kanji/03.h"
#include "overlay/kanji/04.h"
#include "overlay/kanji/05.h"
#include "overlay/kanji/06.h"
#include "overlay/kanji/07.h"
#include "overlay/kanji/08.h"
#include "overlay/kanji/09.h"
#include "overlay/kanji/0a.h"
#include "overlay/kanji/0b.h"
#include "overlay/kanji/0c.h"
#include "overlay/kanji/0d.h"
#include "overlay/kanji/0e.h"
#include "overlay/kanji/0f.h"
#include "overlay/kanji/10.h"
#include "overlay/kanji/11.h"
#include "overlay/kanji/12.h"
#include "overlay/kanji/13.h"
#include "overlay/kanji/14.h"
#include "overlay/kanji/15.h"
#include "overlay/kanji/16.h"
#include "overlay/kanji/17.h"
#include "overlay/kanji/18.h"
#include "overlay/kanji/19.h"
#include "overlay/kanji/1a.h"
#include "overlay/kanji/1b.h"
#include "overlay/kanji/1c.h"
#include "overlay/kanji/1d.h"
#include "overlay/kanji/1e.h"
#include "overlay/kanji/1f.h"
#include "overlay/kanji/20.h"
#include "overlay/kanji/21.h"
#include "overlay/kanji/22.h"
#include "overlay/kanji/23.h"
#include "overlay/kanji/24.h"
#include "overlay/kanji/25.h"
#include "overlay/kanji/26.h"
#include "overlay/kanji/27.h"
#include "overlay/kanji/28.h"
#include "overlay/kanji/29.h"
#include "overlay/kanji/2a.h"
#include "overlay/kanji/2b.h"
#include "overlay/kanji/2c.h"
#include "overlay/kanji/2d.h"
#include "overlay/kanji/2e.h"
#include "overlay/kanji/2f.h"
#include "overlay/kanji/30.h"
#include "overlay/kanji/31.h"
#include "overlay/kanji/32.h"
#include "overlay/kanji/33.h"
#include "overlay/kanji/34.h"
#include "overlay/kanji/35.h"
#include "overlay/kanji/36.h"
#include "overlay/kanji/37.h"
#include "overlay/kanji/38.h"
#include "overlay/kanji/39.h"
#include "overlay/kanji/3a.h"
#include "overlay/kanji/3b.h"
#include "overlay/kanji/3c.h"
#include "overlay/kanji/3d.h"
#include "overlay/kanji/3e.h"
#include "overlay/kanji/3f.h"
#include "overlay/kanji/40.h"
#include "overlay/kanji/41.h"
#include "overlay/kanji/42.h"
#include "overlay/kanji/43.h"
#include "overlay/kanji/44.h"
#include "overlay/kanji/45.h"
#include "overlay/kanji/46.h"
#include "overlay/kanji/47.h"
#include "overlay/kanji/48.h"
#include "overlay/kanji/49.h"
#include "overlay/kanji/4a.h"
#include "overlay/kanji/4b.h"
#include "overlay/kanji/4c.h"
#include "overlay/kanji/4d.h"
#include "overlay/kanji/4e.h"
#include "overlay/kanji/4f.h"
#include "overlay/kanji/50.h"
#include "overlay/kanji/51.h"
#include "overlay/kanji/52.h"
#include "overlay/kanji/53.h"
#include "overlay/kanji/54.h"
#include "overlay/kanji/55.h"
#include "overlay/kanji/56.h"
#include "overlay/kanji/57.h"
#include "overlay/kanji/58.h"
#include "overlay/kanji/59.h"
#include "overlay/kanji/5a.h"
#include "overlay/kanji/5b.h"
#include "overlay/kanji/5c.h"
#include "overlay/kanji/5d.h"
#include "overlay/kanji/5e.h"
#include "overlay/kanji/5f.h"
#include "overlay/kanji/60.h"
#include "overlay/kanji/61.h"
#include "overlay/kanji/62.h"
#include "overlay/kanji/63.h"
#include "overlay/kanji/64.h"
#include "overlay/kanji/65.h"
#include "overlay/kanji/66.h"
#include "overlay/kanji/67.h"
#include "overlay/kanji/68.h"
#include "overlay/kanji/69.h"
#include "overlay/kanji/6a.h"
#include "overlay/kanji/6b.h"
#include "overlay/kanji/6c.h"
#include "overlay/kanji/6d.h"
#include "overlay/kanji/6e.h"
#include "overlay/kanji/6f.h"
#include "overlay/kanji/70.h"
#include "overlay/kanji/71.h"
#include "overlay/kanji/72.h"
#include "overlay/kanji/73.h"
#include "overlay/kanji/74.h"
#include "overlay/kanji/75.h"
#include "overlay/kanji/76.h"
#include "overlay/kanji/77.h"
#include "overlay/kanji/78.h"
#include "overlay/kanji/79.h"
#include "overlay/kanji/7a.h"
#include "overlay/kanji/7b.h"
#include "overlay/kanji/7c.h"
#include "overlay/kanji/7d.h"
#include "overlay/kanji/7e.h"
#include "overlay/kanji/7f.h"
#include "overlay/kanji/80.h"
#include "overlay/kanji/81.h"
#include "overlay/kanji/82.h"
#include "overlay/kanji/83.h"
#include "overlay/kanji/84.h"
#include "overlay/kanji/85.h"
#include "overlay/kanji/86.h"
#include "overlay/kanji/87.h"
#include "overlay/kanji/88.h"
#include "overlay/kanji/89.h"
#include "overlay/kanji/8a.h"
#include "overlay/kanji/8b.h"
#include "overlay/kanji/8c.h"
#include "overlay/kanji/8d.h"
#include "overlay/kanji/8e.h"
#include "overlay/kanji/8f.h"
#include "overlay/kanji/90.h"
#include "overlay/kanji/91.h"
#include "overlay/kanji/92.h"
#include "overlay/kanji/93.h"
#include "overlay/kanji/94.h"
#include "overlay/kanji/95.h"
#include "overlay/kanji/96.h"
#include "overlay/kanji/97.h"
#include "overlay/kanji/98.h"
#include "overlay/kanji/99.h"
#include "overlay/kanji/9a.h"
#include "overlay/kanji/9b.h"
#include "overlay/kanji/9c.h"
#include "overlay/kanji/9d.h"
#include "overlay/kanji/9e.h"
#include "overlay/kanji/9f.h"
#include "overlay/kanji/a0.h"
#include "overlay/kanji/a1.h"
#include "overlay/kanji/a2.h"
#include "overlay/kanji/a3.h"
#include "overlay/kanji/a4.h"
#include "overlay/kanji/a5.h"
#include "overlay/kanji/a6.h"
#include "overlay/kanji/a7.h"
#include "overlay/kanji/a8.h"
#include "overlay/kanji/a9.h"
#include "overlay/kanji/aa.h"
#include "overlay/kanji/ab.h"
#include "overlay/kanji/ac.h"
#include "overlay/kanji/ad.h"
#include "overlay/kanji/ae.h"
#include "overlay/kanji/af.h"
#include "overlay/kanji/b0.h"
#include "overlay/kanji/b1.h"
#include "overlay/kanji/b2.h"
#include "overlay/kanji/b3.h"
#include "overlay/kanji/b4.h"
#include "overlay/kanji/b5.h"
#include "overlay/kanji/b6.h"
#include "overlay/kanji/b7.h"
#include "overlay/kanji/b8.h"
#include "overlay/kanji/b9.h"
#include "overlay/kanji/ba.h"
#include "overlay/kanji/bb.h"
#include "overlay/kanji/bc.h"
#include "overlay/kanji/bd.h"
#include "overlay/kanji/be.h"
#include "overlay/kanji/bf.h"
#include "overlay/kanji/c0.h"
#include "overlay/kanji/c1.h"
#include "overlay/kanji/c2.h"
#include "overlay/kanji/c3.h"
#include "overlay/kanji/c4.h"
#include "overlay/kanji/c5.h"
#include "overlay/kanji/c6.h"
#include "overlay/kanji/c7.h"
#include "overlay/kanji/c8.h"
#include "overlay/kanji/c9.h"
#include "overlay/kanji/ca.h"
#include "overlay/kanji/cb.h"
#include "overlay/kanji/cc.h"
#include "overlay/kanji/cd.h"
#include "overlay/kanji/ce.h"
#include "overlay/kanji/cf.h"
#include "overlay/kanji/d0.h"
#include "overlay/kanji/d1.h"
#include "overlay/kanji/d2.h"
#include "overlay/kanji/d3.h"
#include "overlay/kanji/d4.h"
#include "overlay/kanji/d5.h"
#include "overlay/kanji/d6.h"
#include "overlay/kanji/d7.h"
#include "overlay/kanji/d8.h"
#include "overlay/kanji/d9.h"
#include "overlay/kanji/da.h"
#include "overlay/kanji/db.h"
#include "overlay/kanji/dc.h"
#include "overlay/kanji/dd.h"
#include "overlay/kanji/de.h"
#include "overlay/kanji/df.h"
#include "overlay/kanji/e0.h"
#include "overlay/kanji/e1.h"
#include "overlay/kanji/e2.h"
#include "overlay/kanji/e3.h"
#include "overlay/kanji/e4.h"
#include "overlay/kanji/e5.h"
#include "overlay/kanji/e6.h"
#include "overlay/kanji/e7.h"
#include "overlay/kanji/e8.h"
#include "overlay/kanji/e9.h"
#include "overlay/kanji/ea.h"
#include "overlay/kanji/ec.h"
#endif
