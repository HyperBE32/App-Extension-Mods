// Declare class variables.
unsigned int ScoreListener::score = 0;
struct ScoreListener::ScoreTable ScoreListener::scoreTable;
struct ScoreListener::RankTable ScoreListener::rankTable;

/// <summary>
/// Resets all statistics used for score calculation.
/// </summary>
void ScoreListener::Reset()
{
	StatisticsListener::elapsedTime = 0;
	StatisticsListener::totalRingCount = 0;
	StatisticsListener::ringCount = 0;

	score = 0;

#if _DEBUG
	printf("[Score Generations] Score has been reset...\n");
	printf("[Score Generations] StatisticsListener::elapsedTime = %d\n", StatisticsListener::elapsedTime);
	printf("[Score Generations] StatisticsListener::totalRingCount = %d\n", StatisticsListener::totalRingCount);
	printf("[Score Generations] StatisticsListener::ringCount = %d\n", StatisticsListener::ringCount);
	printf("[Score Generations] ScoreListener::score = %d\n", score);
#endif
}

/// <summary>
/// Calculates the bonuses and adds them to the total score.
/// </summary>
void ScoreListener::Bonus()
{
	// Add ring bonus (Forces).
	ScoreListener::score += StatisticsListener::ringCount * 300;
}

/// <summary>
/// Rewards the player with score based on the input type.
/// </summary>
void __fastcall ScoreListener::Reward(Object type)
{
	int scoreToReward = 0;

	switch (type)
	{
		case Ring:
			scoreToReward = scoreTable.Ring;
			break;

		case Enemy:
			scoreToReward = scoreTable.Enemy;
			break;

		case Physics:
			scoreToReward = scoreTable.Physics;
			break;

		case PointMarker:
			scoreToReward = scoreTable.PointMarker;
			break;

		case RedRing:
			scoreToReward = scoreTable.RedRing;
			break;

		case RainbowRing:
			scoreToReward = scoreTable.RainbowRing;
			break;

		case ItemBox:
			scoreToReward = scoreTable.ItemBox;
			break;

		case SuperRing:
			scoreToReward = scoreTable.SuperRing;
			break;

		case TrickRamp:
			scoreToReward = scoreTable.TrickRamp;
			break;

		case Tricks:
			scoreToReward = scoreTable.TrickRamp;
			break;

		case Life:
			scoreToReward = scoreTable.Life;
			break;
	}

	// Clamp the maximum score.
	if ((score + scoreToReward) <= 999999)
		score += scoreToReward;
	else
		score = 999999;

#if _DEBUG
	printf("[Score Generations] Type %d rewarded player with %d score!\n", type, scoreToReward);
#endif
}