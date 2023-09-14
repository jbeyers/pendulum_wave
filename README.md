# A perpetual pendulum wave machine

## What is it?

A pendulum wave is formed by a row of pendulums, each with a slightly different period. When started at the same time, they swing in a row, but quickly turn into a sinewavey snake shape, go through a whole set of interesting patterns and then end up in a straight row again.

The only ones I've seen are started and tuned manually.


## But perpetual?

Using steel bearing balls with magnets for the pendulums, and giving them a bit of a kick every now and again with a wire solenoid coil, the pendulums can be made to swing continuously. However, they would go out of tune after a few cycles.

The length of the pendulums are adjustable, so I can get them pretty close.

Getting the pendulums to vary their period is the tricky bit. This is slightly difficult to explain, but since the pendulums are built with fishing line, I can add a secondary pivot point below the first one, which will only kick in once the swing is larger than a certain angle. This causes the overall period to shorten if the angle increases.

Each coil has a sensing circuit to detect the pendulum swinging overhead. The coil is slightly offset to one side so that it can determine the direction of the swing from the slight difference in sensing time between the left and right swings.

Each coil is pulsed under PID control, so they sync up no matter what the initial positions are.

## License

This repository contains various files. In general, licensing is CC-BY-SA-4.0 for the designs and MIT for the software. Let me know if you need clarification.
