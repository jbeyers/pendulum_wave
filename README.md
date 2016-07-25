# pendulum_wave
Design files for a perpetual pendulum wave machine.

A pendulum wave is formed by a row of pendulums, each with a slightly different period. When started at the same time, they swing in a row, but quickly turn into a sinewavey snake shape, go through a whole set of interesting patterns and then end up in a straight row again.

The only ones I've seen are started and tuned manually. Using steel bearing balls for the pendulums, and giving them a bit of a kick every now and again with an electromagnet, the pendulums can be made to swing continuously. However, they would go out of tune after a few cycles.

The length of the pendulums can be adjusted, so I can get them roughly in time, but they will be kept accurate by varying the strength of the electromagnetic kick on each pendulum. When the pendulum swings through a larger angle, it goes slightly slower. This should be enough to keep them in time. Let's see if that works.....

Alternatively, and this might be the better option: This is slightly difficult to explain, but since the pendulums are built with fishing line, I can add a secondary pivot point below the first one, which will only kick in once the swing is larger than a certain angle. I think this might cause the overall period to shorten if the angle increases. If this is the case, the electromagnetic kick can just be done on a fixed cycle, and if it's close enough to the natural period, physical feedback will keep it in sync. This can even be implemented using curved sections at the top of the swing, maybe using halved pieces of large-diameter pipe. Needs checking.

If I can get them all under PID control, I should be able to get them to sync up no matter what the initial positions are. That's the goal.

Still figuring out what the license should be, since this is not code-only, but probably CC-BY-SA-4.0 for the designs and MIT for the software.
