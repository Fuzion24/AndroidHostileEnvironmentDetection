Android Emulator Detection
========================

Contains many different ways to identify hostile environments. This project is an android application that uses various techniques to identify the environment that it is currently running in. 
It borrows code and extends the idea offered up by BlueBox (here)[http://www.dexlabs.org/blog/btdetect]

There was a great presentation by Oberheide and Miller with their experience poking around the emulator. This project borrows and implements ideas from it as well. (Bouncer)[http://jon.oberheide.org/files/summercon12-bouncer.pdf]

Future work:
(A Fistful of RedPills)[https://www.usenix.org/legacy/event/woot09/tech/full_papers/paleari.pdf] a paper about auto generating ways to identify CPUs would be particularly useful in this case.  The premise is that certain instructions on CPUs have undefined behavior for various registers.  I.E. What state should the overflow bit have when a move regA, regB instruction is issued.  It turns out that some of these states are unique enough to identify CPU families.  These so-called 'pills' can also be auto generated.
