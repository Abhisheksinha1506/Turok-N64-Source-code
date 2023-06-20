static Vtx rdpcov_case_skinny_00_vtx0[4] = {
	{ -1280, 4, 0, 0, 0, 0, 255, 255, 255,  },
	{ -1280, 3, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 4, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 3, 0, 0, 0, 0, 255, 255, 255,  },
};
static Vtx rdpcov_case_skinny_00_vtx1[4] = {
	{ -1280, 3, 0, 0, 0, 0, 255, 255, 255,  },
	{ -1280, 2, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 3, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 2, 0, 0, 0, 0, 255, 255, 255,  },
};
static Vtx rdpcov_case_skinny_00_vtx2[4] = {
	{ -1280, 2, 0, 0, 0, 0, 255, 255, 255,  },
	{ -1280, 1, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 2, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 1, 0, 0, 0, 0, 255, 255, 255,  },
};
static Vtx rdpcov_case_skinny_00_vtx3[4] = {
	{ -1280, 1, 0, 0, 0, 0, 255, 255, 255,  },
	{ -1280, 0, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 1, 0, 0, 0, 0, 255, 255, 255,  },
	{ 1280, 0, 0, 0, 0, 0, 255, 255, 255,  },
};
Gfx rdpcov_case_skinny_00[14] = {
	gsSPVertex(&(rdpcov_case_skinny_00_vtx0[0]), 4, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPVertex(&(rdpcov_case_skinny_00_vtx1[0]), 4, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPVertex(&(rdpcov_case_skinny_00_vtx2[0]), 4, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPVertex(&(rdpcov_case_skinny_00_vtx3[0]), 4, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};

