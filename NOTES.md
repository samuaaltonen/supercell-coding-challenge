Ideas:
- Spawn multiple balls with different colors representing different velocities. Different colors grant extra points.
- Paddle movement boost with shift. Boost uses energy. AI has also boost.
- Balls have mass that affect other balls like gravity so it is possible to do trick shots with gravity effects.
- Balls have collisions
- With many balls it is easy to lose after small mistake, change losing mechanism to be based on "health" instead. Draw health bar.
- Paddles have traction so it is possible to alter ball direction with paddle movement
- Colorful particle effects, textures, music, ball bounce sound, score sound, health lose sound

Workflow:
- Fixed a bug where players paddle always goes down. Also made it so that players paddle doesnt automatically move for better control.
- Changed constants to be constexpr instead (they are known at compile time)
- Added multiple balls spawner. Ball spawning rate depends on how many balls are already on the map (to not get owerwhelmed too quickly).
- Added keybind for ESC to close the game for conveniency
- Noticed that there was no variance between games in ball spawning direction. srand random seed initializer was missing, added it.
- Generated heart and energy battery assets with DALL-E and edited with Photoshop into same spritesheet
- Added health and energy bars for both sides
- Added taking damage if other side scores a goal
- Modified score to be given based on successfull defends instead. Score amount is proportional to ball velocity.
- Added rendering score which targets actual score every frame (to achieve running score count). Change depends on distance to actual score and score change rate to get accelerating score increase effect.
- Added smarter AI which calculates balls intersection points to goal line and moves accordingly using boost only when necessary.
- Noticed that the AI is now way too smart and kinda impossible to defeat. Need to do difficulty slider.
- Added sound effects. Using free soundpack by GameSupplyGuy, added link/credits to CREDITS.md.