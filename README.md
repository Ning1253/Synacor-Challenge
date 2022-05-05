# Synacor-Challenge
My solution to the Synacor Challenge. 

Copy of "build/release/challenge.txt":
```
1. mazetwistylittleall 	NSEW: N->2, S->3, W->4, E->8 DONE
2. twistymazelittlealike NSW: N->3, S->1, W->2 DONE
3. mazelittletwistyalike NSE: N->1, S->2, E->3 DONE
4. littlemazetwistyalike NSE: N->4, S->5, E->1 DONE
5. twistyalikelittlemaze NSWE: N->6, S->2, W->3, E->7 DONE
6. CAN				W: W->1 DONE
7. twistymazelittlealike NS: N->3, S->2 DONE
8. mazealikelittletwisty NSWE: N->9, S->8, W->1, E->7 DONE
9. mazealiketwistylittle NES: N->3, E->2, S->9 DONE

SO LWSNWLPWWW basically. 
RED COIN 2 DOTS
BLUE 9 DOTS
SHINY PENTAGON
CONCAVE 7 DOTS
CORRODED TRIANGLE
2,3,5,7,9
9,2,5,7,3

The cover of this book subtly swirls with colors.  It is titled "A Brief Introduction to Interdimensional Physics".  It reads:

Recent advances in interdimensional physics have produced fascinating
predictions about the fundamentals of our universe!  For example,
interdimensional physics seems to predict that the universe is, at its root, a
purely mathematical construct, and that all events are caused by the
interactions between eight pockets of energy called "registers".
Furthermore, it seems that while the lower registers primarily control mundane
things like sound and light, the highest register (the so-called "eighth
register") is used to control interdimensional events such as teleportation.

A hypothetical such teleportation device would need to have have exactly two
destinations.  One destination would be used when the eighth register is at its
minimum energy level - this would be the default operation assuming the user
has no way to control the eighth register.  In this situation, the teleporter
should send the user to a preconfigured safe location as a default.

The second destination, however, is predicted to require a very specific
energy level in the eighth register.  The teleporter must take great care to
confirm that this energy level is exactly correct before teleporting its user!
If it is even slightly off, the user would (probably) arrive at the correct
location, but would briefly experience anomalies in the fabric of reality
itself - this is, of course, not recommended.  Any teleporter would need to test
the energy level in the eighth register and abort teleportation if it is not
exactly correct.

This required precision implies that the confirmation mechanism would be very
computationally expensive.  While this would likely not be an issue for large-
scale teleporters, a hypothetical hand-held teleporter would take billions of
years to compute the result and confirm that the eighth register is correct.

If you find yourself trapped in an alternate dimension with nothing but a
hand-held teleporter, you will need to extract the confirmation algorithm,
reimplement it on more powerful hardware, and optimize it.  This should, at the
very least, allow you to determine the value of the eighth register which would
have been accepted by the teleporter's confirmation mechanism.

Then, set the eighth register to this value, activate the teleporter, and
bypass the confirmation mechanism.  If the eighth register is set correctly, no
anomalies should be experienced, but beware - if it is set incorrectly, the
now-bypassed confirmation mechanism will not protect you!

Of course, since teleportation is impossible, this is all totally ridiculous.

Teleporter used!! Looked into the binary to find the function which is being called (sots). 
Made it so that the function is never called, and made the check correct by setting it
to check reg[0] = 4. 

Unfortunately the code is not a valid one... Back to binary! Later...

JESUS F*CKING CHRIST BRO THAT TOOK SO F*CKING LONG STUPID ACKERMANN AND READING BINARY AND DEBUG OUTPUT AND ARGGHHH
(and multithreading, and lru_caching, and simplyfying the code...) so satisfying to solve tho...

CODE: 

if reg[0] == 0: [6027]
	reg[0] = reg[1] + 1
	RET (?)
else:
	if reg[1] == 0:
		reg[0] = reg[0] - 1
		reg[1] = N
		CALL
		RET (?) [6047]
	else:
		PUSH reg[0]
		reg[1] = reg[1] - 1
		CALL
		reg[1] = reg[0] [6056]
		POP reg[0]
		reg[0] = reg[0] - 1
		CALL
		RET (?) [6067]


def func(a, b):
	if a == 0:
		return (b + 1, b)
	if b == 0:
		return func(a - 1, N)
	b = func(a, b - 1)[0]
	return func(a - 1, b)

SEE func.py for implementation with stack size of 2GB which allows me to actually run the file. 

25734 is correct!!

Maze:


*  8  - 1
4  * 11 *
+  4  - 18
22 -  9 *

30?
22+4+4+4+4+4+4+4+4+4+4+4-18-18*1 (28)
22+4+4+4+4+4-11-1 (14)
22-9-11*4+4*4-18*1 (14)

See maze.py...

You gaze into the mirror, and you see yourself gazing back.  But wait!  It looks like someone wrote on your face while you were unconscious on the beach!  Through the mirror, you see "biubuvOlWwAu" scrawled in charcoal on your forehead. 
uAwWlOvuduid
```
