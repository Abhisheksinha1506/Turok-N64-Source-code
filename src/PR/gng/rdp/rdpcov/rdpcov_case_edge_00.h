static Vtx rdpcov_case_edge_00_vtx0[4] = {
	{ -1280, 0, 0, 0, 0, 0, 0, 255, 0,  },
	{ 0, 960, 0, 0, 0, 0, 0, 255, 0,  },
	{ 1280, 0, 0, 0, 0, 0, 0, 255, 0,  },
	{ 0, -960, 0, 0, 0, 0, 0, 255, 0,  },
};
Gfx rdpcov_case_edge_00[5] = {
	gsSPVertex(&(rdpcov_case_edge_00_vtx0[0]), 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

