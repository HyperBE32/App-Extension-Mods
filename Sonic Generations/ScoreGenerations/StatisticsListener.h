#pragma once

class StatisticsListener
{
public:
    /// <summary>
    /// Installs the mid-ASM hooks.
    /// </summary>
    static void Install();

    /// <summary>
    /// Calculates the elapsed time from the minutes and seconds.
    /// </summary>
    static int GetElapsedTime();

    static struct Statistics
    {
        /// <summary>
        /// Total number of rings obtained by the player.
        /// </summary>
        int totalRingCount;

        /// <summary>
        /// Total number of enemies destroyed by the player.
        /// </summary>
        int totalEnemies;

        /// <summary>
        /// Total number of physics objects destroyed by the player.
        /// </summary>
        int totalPhysics;

        /// <summary>
        /// Total number of checkpoints passed by the player.
        /// </summary>
        int totalPointMarkers;

        /// <summary>
        /// Total number of red rings obtained by the player.
        /// </summary>
        int totalRedRings;

        /// <summary>
        /// Total number of rainbow rings passed by the player.
        /// </summary>
        int totalRainbowRings;

        /// <summary>
        /// Total number of item boxes obtained by the player.
        /// </summary>
        int totalItemBoxes;

        /// <summary>
        /// Total number of super rings obtained by the player.
        /// </summary>
        int totalSuperRings;

        /// <summary>
        /// Total number of tricks performed by the player.
        /// </summary>
        int totalTricks;

        /// <summary>
        /// Total number of dash rings passed by the player.
        /// </summary>
        int totalDashRings;

        /// <summary>
        /// Total number of quick steps performed by the player.
        /// </summary>
        int totalQuickSteps;

        /// <summary>
        /// Total number of drifts performed by the player.
        /// </summary>
        int totalDrifts;

        /// <summary>
        /// Total number of balloons destroyed by the player.
        /// </summary>
        int totalBalloons;

        /// <summary>
        /// Total number of hits taken by the player.
        /// </summary>
        int totalDamage;

        /// <summary>
        /// Total amount of speed from checkpoints.
        /// </summary>
        int totalVelocity;

        /// <summary>
        /// Current number of rings obtained by the player.
        /// </summary>
        int ringCount;

        /// <summary>
        /// Minutes counted by the game.
        /// </summary>
        int minutes;

        /// <summary>
        /// Seconds counted by the game.
        /// </summary>
        int seconds;

        void Reset()
        {
            totalRingCount = 0;
            totalEnemies = 0;
            totalPhysics = 0;
            totalPointMarkers = 0;
            totalRedRings = 0;
            totalRainbowRings = 0;
            totalItemBoxes = 0;
            totalSuperRings = 0;
            totalTricks = 0;
            totalDashRings = 0;
            totalQuickSteps = 0;
            totalDrifts = 0;
            totalBalloons = 0;
            totalDamage = 0;
            totalVelocity = 0;
            ringCount = 0;
            minutes = 0;
            seconds = 0;
        }
    };

    static Statistics stats;
};