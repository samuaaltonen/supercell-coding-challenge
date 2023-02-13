#pragma once

constexpr float BallRadius = 16.f;
constexpr std::size_t BallPoints = 32;
constexpr float PaddleWidth = 10.f;
constexpr float PaddleHeight = 160.f;
constexpr float PaddleOffsetFromEdge = 20.f;
constexpr float PaddleMoveSpeed = 300.f;

constexpr std::size_t MaxBalls = 30;
constexpr float BallRelativeSpawnTime = 0.5f;

constexpr float MinFiringSpeed = 150.f;
constexpr float MaxFiringSpeed = 500.f;

constexpr int MaxHealth = 8;

constexpr float BoostMultiplier = 4.f;
constexpr float MaxEnergy = 100.f;
constexpr float MinEnergyToBoost = 5.f;
constexpr float EnergyRegen = 30.f; // regen per second
constexpr float EnergyRegenCooldown = 0.5f; // regen starts after cooldown seconds
constexpr float EnergyUsage = 40.f; // energy usage per second when using

constexpr float UiMargin = 20.f;
constexpr float UiGap = 4.f;
constexpr float HeartWidth = 34.f;
constexpr float HeartHeight = 31.f;
constexpr float BatteryCount = 12.f;
constexpr float EnergyIconOffset = 360.f;
constexpr float EnergyWidth = 20.f;
constexpr float EnergyHeight = 31.f;

constexpr float ScorePerSpeed = 0.25f;
constexpr float ScorePerGoal = 1000.f;
/**
 * Rate per score per second (i.e. if score change is +10, rate starts with
 * 20 score / second and then reduces down to 0 when reaching the actual score.
 */
constexpr float RenderScoreIncreaseRate = 2.f;

constexpr int AIExhaustion = 3000; // Maximum collision calculations the AI will do in a single update per ball.
constexpr float MaxAIDifficulty = 100.f;
constexpr float MinAIDifficulty = 5.f;
constexpr float DefaultAIDifficulty = 75.f;
constexpr float AIUseBoostDifficultyThreshold = 25.f;
constexpr float DifficultyChangeRate = 25.f;

constexpr float DefaultVolume = 25.f;
constexpr float VolumeChangeRate = 50.f; // per second

enum Side
{
    LEFT = 0,
    RIGHT
};

enum Sounds
{
	SOUND_SCORE,
	SOUND_TAKE_DAMAGE,
	SOUND_GOAL
};
