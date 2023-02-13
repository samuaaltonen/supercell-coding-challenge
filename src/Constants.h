#pragma once

constexpr float BallRadius = 16.f;
constexpr std::size_t BallPoints = 32;
constexpr float PaddleWidth = 10.f;
constexpr float PaddleHeight = 160.f;
constexpr float PaddleOffsetFromEdge = 20.f;
constexpr float PaddleMoveSpeed = 400.f;

constexpr std::size_t MaxBalls = 10;
constexpr float BallRelativeSpawnTime = 1.f;

constexpr float MinFiringSpeed = 150.f;
constexpr float MaxFiringSpeed = 600.f;

enum Side
{
    LEFT = 0,
    RIGHT
};
