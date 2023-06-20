
#define SEQUENCE_BUFFER_SIZE	16384
BYTE	sequence_buffer[SEQUENCE_BUFFER_SIZE];

#define TUNE_ID_OFFSET	100

//	MUST BE CALLED FROM GAME THREAD!
BOOL PlayATune(int nTune)
{
	static CCacheEntry	*pceSequence;

	if (!cache_is_valid)
		return FALSE;

	return CScene__RequestBinaryBlock(&GetApp()->m_Scene,
												 nTune + TUNE_ID_OFFSET,
												 &pceSequence,
												 NULL, (pfnCACHENOTIFY) TuneReceived);
}

void TuneReceived(void *pThis, CCacheEntry **ppceTarget)
{
	void		*pbTune;
	DWORD		size;

	pbTune = CCacheEntry__GetData(*ppceTarget);

	size = (*ppceTarget)->m_DataLength;
	ASSERT(size <= SEQUENCE_BUFFER_SIZE);

	memcpy(sequence_buffer, pbTune, size);

	// START SEQUENCE HERE!
}
