# Clue

The most comprehensive BeOS GUI tracing tool, allowing inspection on almost all of the BeOS native objects.

![Clue](clue.png)


By:  Jeff Braun and Mathew Hounsell
Version:    2.1.0 Alpha/Development for Zeta 1.1.0 (et al)
Contact:    mat_geek at yahoo.com.au
Web:        http://web.archive.org/web/20070826055004/http://brauns.dyndns.org/BeOS/Clue/
Date:       2006 May 30
License:    LGPLv2
Originally from: http://sourceforge.net/projects/clue/

Contained in the Zip file should be:

clue-2-1-0-alpha-zeta-1-1-0             The Server and Display
clue-2-1-0-alpha-zeta-1-1-0.so          The Library to Link Against
cluedemo-2-1-0-alpha-zeta-1-1-0         The Exmple Message Sender
Clue.h                                  The Header to Include
Localized Strings                       Translations for the Server
Sample                                  Example Message Sender
Documentation                           HTML Documentation

You should begin by moving "clue-2-1-0-alpha-zeta-1-1-0.so" to your
"/home/config/lib" folder.  This can be done easily by dragging and dropping it
onto the included folder called "Place clue-2-1-0-alpha-zeta-1-1-0.so Here".

Included in this download is a full sample application that shows some ways in which you can use Clue, and its code is located in the "Sample"
folder.

Wherever you end up placing the Clue application, you should move the "Documentation" folder to the same place. The "File/Help" menu
will be looking for the "index.htm" file in the Documentation folder where the app was started from.

NOTE: Need to update documentation for this next release. Being as this is a development release, this document isn't finished!!! My major focus with the next release is to add a timeline; and to harden the code!!!  It's a big job, so that is why I'm releasing this dev version, to get something out there so people know this project isn't dead. If you can be of any help with language translation, I would appreciate it very much. I still have some hard-coded strings in my latest code, so the "localized strings" file will change as I get closer to the final release.

Also included is a file called "Localized Strings".  This file contains all of
the string definitions that Clue uses.  In almost all of the languages, there
are some non-localized strings.  If you are fluent in any of the languages
(German, Czech, Russian, French, or Portuguese) and can help by translating the English string, I would appreciate it greatly!!!  The file has to be compiled into the program, so just changing the strings won't change Clue.

Thanks,
Mathew Hounsell

P.S. Thank you Jeff Braun for creating and open sourcing this fantastic tool.

P.P.S. A very special thanks goes out to Brian Tietz (btietz at biomail.ucsd.edu) for providing code from his SantasGiftBag. I took out a big portion of his code
Jeff didn't need, and changed his mouse handling code so that it didn't poll, but used the preferred MouseMoved events instead.
