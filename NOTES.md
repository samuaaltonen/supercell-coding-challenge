Ideas:
- Spawn multiple balls with different colors representing different velocities. Different colors grant extra points.
- Balls have mass that affect other balls like gravity so it is possible to do trick shots where faster more straight going ball affects more slower ball
- Balls have collisions
- Colorful particle effects
- With many balls it is easy to lose after small mistake, change losing mechanism to be based on "health" instead. Draw health bar.

Workflow:
- Fixed a bug where players paddle always goes down. Also made it so that players paddle doesnt automatically move for better control.
- Changed constants to be constexpr instead (they are known at compile time)
- Added multiple balls spawner. Ball spawning rate depends on how many balls are already on the map (to not get owerwhelmed too quickly).