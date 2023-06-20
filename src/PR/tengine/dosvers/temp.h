// wall collision types
#define	WALL_STICK			0
#define	WALL_SLIDE			1
#define	WALL_SLIDEBOUNCE	2
#define	WALL_REDIRECT		3
#define	WALL_BOUNCE			4
#define	WALL_NOCOLLISION	5


// instance collision types
#define	INSTANCE_NOCOLLISION		0
#define	INSTANCE_STICK				1
#define	INSTANCE_SLIDE				2
#define	INSTANCE_GREASE			3
/*
// ground collision types
#define	GROUND_NOCOLLISION		0
#define	GROUND_STICK				1
#define	GROUND_SLIDE				2
*/
#define COLLISIONFLAG_BOUNCEOFFGROUND				(1 << 0)
#define COLLISIONFLAG_CANCLIMB						(1 << 1)
#define COLLISIONFLAG_UPDATEVELOCITY				(1 << 2)
#define COLLISIONFLAG_IGNOREDEAD						(1 << 3)
#define COLLISIONFLAG_USEWALLRADIUS					(1 << 4)
#define COLLISIONFLAG_SMALLWALLRADIUS				(1 << 5)
#define COLLISIONFLAG_PREVENTOSC						(1 << 6)
#define COLLISIONFLAG_NOHILLSLOWDOWN				(1 << 7)
#define COLLISIONFLAG_WATERCOLLISION				(1 << 8)
#define COLLISIONFLAG_NOGROUNDMOVEMENT				(1 << 9)
#define COLLISIONFLAG_MOVETHROUGHDOORS				(1 << 10)
#define COLLISIONFLAG_PICKUPCOLLISION				(1 << 11)
#define COLLISIONFLAG_CANCLIMBCLIMBABLE			(1 << 12)
#define COLLISIONFLAG_CLIFFONLY						(1 << 13)
#define COLLISIONFLAG_STICKTOGROUND					(1 << 14)
#define COLLISIONFLAG_DUCKING							(1 << 15)
#define COLLISIONFLAG_CANENTERRESTRICTEDAREA		(1 << 16)
#define COLLISIONFLAG_NOFLOORCOLLISION				(1 << 17)
#define COLLISIONFLAG_AVOIDPRESSUREPLATE			(1 << 18)


//#define COLLISIONFLAG_AVOIDWATER						(1 << 17)


typedef struct CCollisionInfo_t
{
// input
	DWORD 							m_WallBehavior,
										m_InstanceBehavior,
										m_dwFlags;
	float								m_GravityAcceleration,	// in ft/sec^2
										m_BounceReturnEnergy,	// 1.0 means perfectly elastic collision
										m_GroundFriction,			// 0.0 means no friction, 1.0 means 100% friction
										m_AirFriction,
										m_WaterFriction;
// output
	BOOL								m_WallCollision;
	CVector3							m_vWallCollisionPos;
	CGameRegion						*m_pWallCollisionRegion;
	int								m_nWallCollisionEdge;

	struct CInstanceHdr_t		*m_pInstanceCollision;
	CVector3							m_vInstanceCollisionPos;

#define GROUNDCOLLISION_NONE		0
#define GROUNDCOLLISION_GROUND	1
#define GROUNDCOLLISION_CEILING	2
	int								m_GroundCollision;
	CVector3							m_vGroundCollisionPos;
	CGameRegion						*m_pGroundCollisionRegion;

	BOOL								m_WaterCollision;
	CVector3							m_vWaterCollisionPos;
	CGameRegion						*m_pWaterCollisionRegion;

	CVector3							m_vCollisionVelocity;
} CCollisionInfo;
