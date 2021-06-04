#pragma once

class ScoreListener
{
public:
    /// <summary>
    /// Index-based score type - makes things easier when rewarding score in other classes.
    /// </summary>
    enum ScoreType
    {
        Ring,
        Enemy,
        Physics,
        PointMarker,
        RedRing,
        RainbowRing,
        ItemBox,
        SuperRing,
        TrickFinish,
        Trick,
        Life,
        DashRing,
        QuickStep,
        Drift,
        Balloon,
        Super,
        BoardTrick
    };

    /// <summary>
    /// Resets all statistics used for score calculation.
    /// </summary>
    static void Reset();

    /// <summary>
    /// Adds the input score to reward and clamps it to the maximum allowed.
    /// </summary>
    static void AddClamp(unsigned int scoreToReward);

    /// <summary>
    /// Rewards the player with score based on the input type.
    /// </summary>
    static void __fastcall Reward(ScoreType type);

    /// <summary>
    /// Score calculated locally.
    /// </summary>
    static int score;

    struct ScoreTable
    {
        // Score rewarded for objects.
        int Ring = 0;
        int Enemy = 0;
        int Physics = 0;
        int PointMarker = 0;
        int RedRing = 0;
        int RainbowRing = 0;
        int ItemBox = 0;
        int SuperRing = 0;
        int TrickFinish = 0;
        int Trick = 0;
        int Life = 0;
        int DashRing = 0;
        int QuickStep = 0;
        int Drift = 0;
        int Balloon = 0;
        int Super = 0;
        int BoardTrick = 0;

        static ScoreTable GetScore()
        {
            ScoreTable scoreTable;

            // Use the current configuration to get the score for objects.
            scoreTable.Ring        = Configuration::config.GetInteger("Score", "Ring", 0);
            scoreTable.Enemy       = Configuration::config.GetInteger("Score", "Enemy", 0);
            scoreTable.Physics     = Configuration::config.GetInteger("Score", "Physics", 0);
            scoreTable.PointMarker = Configuration::config.GetInteger("Score", "PointMarker", 0);
            scoreTable.RedRing     = Configuration::config.GetInteger("Score", "RedRing", 0);
            scoreTable.RainbowRing = Configuration::config.GetInteger("Score", "RainbowRing", 0);
            scoreTable.ItemBox     = Configuration::config.GetInteger("Score", "ItemBox", 0);
            scoreTable.SuperRing   = Configuration::config.GetInteger("Score", "SuperRing", 0);
            scoreTable.TrickFinish = Configuration::config.GetInteger("Score", "TrickFinish", 0);
            scoreTable.Trick       = Configuration::config.GetInteger("Score", "Trick", 0);
            scoreTable.Life        = Configuration::config.GetInteger("Score", "Life", 0);
            scoreTable.DashRing    = Configuration::config.GetInteger("Score", "DashRing", 0);
            scoreTable.Drift       = Configuration::config.GetInteger("Score", "Drift", 0);
            scoreTable.Balloon     = Configuration::config.GetInteger("Score", "Balloon", 0);
            scoreTable.Super       = Configuration::config.GetInteger("Score", "Super", 0);
            scoreTable.BoardTrick  = Configuration::config.GetInteger("Score", "BoardTrick", 0);

#if _DEBUG
            printf("[Score Generations] Ring = %d\n", scoreTable.Ring);
            printf("[Score Generations] Enemy = %d\n", scoreTable.Enemy);
            printf("[Score Generations] Physics = %d\n", scoreTable.Physics);
            printf("[Score Generations] PointMarker = %d\n", scoreTable.PointMarker);
            printf("[Score Generations] RedRing = %d\n", scoreTable.RedRing);
            printf("[Score Generations] RainbowRing = %d\n", scoreTable.RainbowRing);
            printf("[Score Generations] ItemBox = %d\n", scoreTable.ItemBox);
            printf("[Score Generations] SuperRing = %d\n", scoreTable.SuperRing);
            printf("[Score Generations] TrickFinish = %d\n", scoreTable.TrickFinish);
            printf("[Score Generations] Trick = %d\n", scoreTable.Trick);
            printf("[Score Generations] Life = %d\n", scoreTable.Life);
            printf("[Score Generations] DashRing = %d\n", scoreTable.DashRing);
            printf("[Score Generations] Drift = %d\n", scoreTable.Drift);
            printf("[Score Generations] Balloon = %d\n", scoreTable.Balloon);
            printf("[Score Generations] Super = %d\n", scoreTable.Balloon);
            printf("[Score Generations] BoardTrick = %d\n", scoreTable.BoardTrick);
#endif

            return scoreTable;
        }
    };

    static ScoreTable scoreTable;
};