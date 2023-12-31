
static Vtx head_vtx[8] =
{
    {	-8,  0, -8, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	-8,  0,  8, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	 8,  0,  8, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	 8,  0, -8, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	-8, 20, -8, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	-8, 20,  8, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	 8, 20,  8, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	 8, 20, -8, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static Vtx body_vtx[8] =
{
    {	-10, -20, -10, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	-10, -20,  10, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	 10, -20,  10, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	 10, -20, -10, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	-20, 20, -10, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	-20, 20,  10, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	 20, 20,  10, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	 20, 20, -10, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static Vtx left_leg_vtx[8] =	/* both upper and both lower legs pieces */
{
    {	 5, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	 5, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	10, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	10, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	 5, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	 5, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	10, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	10, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};


static Vtx right_leg_vtx[8] =	/* both upper and both lower legs pieces */
{
    {  -10, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {  -10, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	-5, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	-5, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {  -10, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {  -10, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	-5, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	-5, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};


static Vtx right_arm_vtx[8] =
{
    {	 -5, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	 -5, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	  0, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	  0, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	 -5, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	 -5, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	  0, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	  0, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static Vtx right_wrist_vtx[8] =
{
    {	 -5, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	 -5, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	  0, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	  0, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	 -5, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	 -5, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	  0, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	  0, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static Vtx left_arm_vtx[8] =
{
    {	  0, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	  0, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	  5, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	  5, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	  0, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	  0, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	  5, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	  5, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static Vtx left_wrist_vtx[8] =
{
    {	  0, -20, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
    {	  0, -20,  5, 0, 0, 0, 0, 0xff, 0, 0xff	},
    {	  5, -20,  5, 0, 0, 0, 0xff, 0, 0, 0xff	},
    {	  5, -20, -5, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},

    {	  0, 0, -5, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
    {	  0, 0,  5, 0, 0, 0, 0xff, 0, 0xff, 0xff	},
    {	  5, 0,  5, 0, 0, 0, 0xff, 0xff, 0, 0xff	},
    {	  5, 0, -5, 0, 0, 0, 0x7f, 0, 0x7f, 0xff	},
};

static gtTriN	cube_tris[] =
{
    { 4, 5, 6, 0, },	/* top */
    { 4, 6, 7, 0, },	

    { 0, 2, 1, 0, },	/* bottom */
    { 0, 3, 2, 0, },

    { 5, 4, 0, 0, },	/* left */
    { 5, 0, 1, 0, },	

    { 7, 6, 2, 0, },	/* right */
    { 7, 2, 3, 0, },

    { 3, 4, 7, 0, },	/* near */
    { 3, 0, 4, 0, },	

    { 6, 5, 1, 0, },	/* far */
    { 6, 1, 2, 0, },
};
