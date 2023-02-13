#pragma once

constexpr float BallRadius = 16.f;
constexpr std::size_t BallPoints = 32;
constexpr float FiringSpeed = 240.f;
constexpr float PaddleWidth = 10.f;
constexpr float PaddleHeight = 100.f;
constexpr float PaddleOffsetFromEdge = 20.f;
constexpr float PaddleMoveSpeed = 300.f;

constexpr std::size_t MaxBalls = 10;
constexpr float BallRelativeSpawnTime = 1.f;

enum Side
{
    LEFT = 0,
    RIGHT
};
