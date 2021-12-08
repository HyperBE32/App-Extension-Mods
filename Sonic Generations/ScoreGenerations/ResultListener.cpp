ResultListener::ResultDescription ResultListener::resultDescription;

void ResultListener::Bonus()
{
	// Rewards the Lua bonuses and clamps them.
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.timeBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.speedBonusAlgorithm), false);
	ScoreListener::AddClamp(ScoreListener::totalScore, LuaCallback::RunAlgorithm(TableListener::bonusTable.userAlgorithm), false);
}

ResultListener::RankType ResultListener::Rank(bool perfect)
{
	RankType rank;
	int total = ScoreListener::totalScore;
	int S = TableListener::rankTables[StateHooks::stageID].S;
	int A = TableListener::rankTables[StateHooks::stageID].A;
	int B = TableListener::rankTables[StateHooks::stageID].B;
	int C = TableListener::rankTables[StateHooks::stageID].C;

	if (Configuration::perfectBonus == 0 && S != -1 && total > S)
	{
		/* Only use S rank if perfect bonus is disabled
		   and S rank isn't the default value. */
		return RankType::S;
	}

	if (total < A)
	{
		if (total < B)
		{
			if (total < C)
			{
				rank = RankType::D;
			}
			else
			{
				rank = RankType::C;
			}
		}
		else
		{
			rank = RankType::B;
		}
	}
	else
	{
		rank = RankType::A;
	}

	return (RankType)(perfect ? rank + 1 : rank);
}

/// <summary>
/// Computes the progress bar percentage based on the input rank and divider.
/// </summary>
/// <param name="rank">Rank to line up with.</param>
/// <param name="divider">Divider to set up rank results.</param>
float ComputeProgressBar(ResultListener::RankType rank, int divider)
{
	switch (rank)
	{
		case ResultListener::RankType::D:
			return ((float)divider / (float)TableListener::rankTables[StateHooks::stageID].C) / 3.0f;

		case ResultListener::RankType::C:
		{
			const float baseScore = (float)TableListener::rankTables[StateHooks::stageID].C;
			return (1.0f / 3.0f) + (((float)divider - baseScore) / ((float)TableListener::rankTables[StateHooks::stageID].B - baseScore)) / 3.0f;
		}

		case ResultListener::RankType::B:
		{
			const float baseScore = (float)TableListener::rankTables[StateHooks::stageID].B;
			return (2.0f / 3.0f) + (((float)divider - baseScore) / ((float)TableListener::rankTables[StateHooks::stageID].A - baseScore)) / 3.0f;
		}

		case ResultListener::RankType::A:
		case ResultListener::RankType::S:
			return 1.0f;
	}
}

tuple<float, float> ResultListener::ComputeProgressBars(RankType rank)
{
	float scoreProgress;
	float ringProgress;

	int ringBonus = LuaCallback::RunAlgorithm(TableListener::bonusTable.ringBonusAlgorithm);

	// Compute score progress.
	scoreProgress = ComputeProgressBar(rank, ScoreListener::totalScore - ringBonus);

	// Compute ring progress.
	ringProgress = ComputeProgressBar(rank, ScoreListener::totalScore + ringBonus / StatisticsListener::totals.ringCount) + 0.0001;

	return { scoreProgress, ringProgress };
}

void ResultListener::Result()
{
	// Calculate the bonuses.
	ResultListener::Bonus();

	// Set the final score.
	resultDescription.score = ScoreListener::totalScore;

	// Print exposed Lua data before results manipulation.
	LuaCallback::PrintExposedData();

	// Set up ranks.
	resultDescription.rank = Rank();
	resultDescription.perfectRank = Rank(true);

	// Compute results progress bar.
	auto [score, ring] = ComputeProgressBars(Rank());

	// Set up progress bars.
	resultDescription.scoreProgress = score;
	resultDescription.ringProgress = ring;
}