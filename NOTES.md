Ideas:
- Spawn multiple balls with different colors representing different velocities. Different colors grant extra points.
- Paddle movement boost with shift. Boost uses energy. AI has also boost.
- Balls have mass that affect other balls like gravity so it is possible to do trick shots with gravity effects.
- Balls have collisions
- With many balls it is easy to lose after small mistake, change losing mechanism to be based on "health" instead. Draw health bar.
- Colorful particle effects, textures, music, ball bounce sound, score sound, health lose sound

Workflow:
- Fixed a bug where players paddle always goes down. Also made it so that players paddle doesnt automatically move for better control.
- Changed constants to be constexpr instead (they are known at compile time)
- Added multiple balls spawner. Ball spawning rate depends on how many balls are already on the map (to not get owerwhelmed too quickly).
- Added keybind for ESC to close the game for conveniency
- Noticed that there was no variance between games in ball spawning direction. srand random seed initializer was missing, added it.