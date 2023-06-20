static Vtx rdpcov_case_vertex_00_vtx0[7] = {
	{ 0, 960, 0, 0, 0, 0, 0, 0, 255,  },
	{ 1280, 960, 0, 0, 0, 0, 0, 0, 255,  },
	{ -1280, 0, 0, 0, 0, 0, 0, 0, 255,  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 255,  },
	{ 1280, 0, 0, 0, 0, 0, 0, 0, 255,  },
	{ -1280, -960, 0, 0, 0, 0, 0, 0, 255,  },
	{ 0, -960, 0, 0, 0, 0, 0, 0, 255,  },
};
Gfx rdpcov_case_vertex_00[9] = {
	gsSPVertex(&(rdpcov_case_vertex_00_vtx0[0]), 7, 0),
	gsSP1Triangle(0, 3, 2, 0),
	gsSP1Triangle(0, 1, 3, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(2, 3, 5, 0),
	gsSP1Triangle(3, 6, 5, 0),
	gsSP1Triangle(3, 4, 6, 0),
	gsSPEndDisplayList(),
};

