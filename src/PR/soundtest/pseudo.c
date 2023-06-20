main thread start()
{
		create game thread
		set game thread priority normal
		start game thread

		// never gets reached
}

game thread start()
{
		create sound thread
		set sound thread priority high
		start sound thread

		setEvent for retrace at whatever fps with gameRetraceMessageQueue

		while (1)
		{
			draw graphics
		}
}

sound thread start()
{
		setEvent to get retrace at 60fps with soundRetraceMessageQueue

		while (1)
		{
			// process sound

			osReceiveMessage(soundRetraceMessageQueue, BLOCK);
		}
}