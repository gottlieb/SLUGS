1. Introduction
===============

The Santa Cruz Low-cost UAV GNC System is a high-end UAV Autopilot that has been developed by the Autonomous Systems Lab at the University of California Santa Cruz. It has been thoroughly tested in flight.

SLUGS Official  Website <http://slugsuav.soe.ucsc.edu/>.

The SLUGS Autopilot offers the following features:

* Designed from the ground-up to be easily reprogrammable using Mathworks' Simulink and The Real Time Workshop Embedded Coder.

* Powered by two dsPICs DSCs; one for sensor fusion and attitude estimation from a rich sensor suite. The other for control and communications tasks, providing enough processing power for complex algorithms.

* Small enough to fit in a tactical UAV but able to drive up to ten different servos. It also includes a multiplexer to choose between pilot and automatic control

* Easily go from Simulink simulation to Embedded code. Test your algorithms in Simulink then download them to the Autopilot without any effort.

* Fast execution time. The main processing cycles are executed at 100Hz. Telemetry reports of attitude and position at 100 Hz and the rest of the messages scheduled at 10 Hz.

* Fully integrated with Google Earth to allow the Ground Station operator to create flight way points and display the UAV's flight trajectory in 3D.

* Full featured Ground Station software with graphical displays for all of the UAV telemetry. More than 15 different telemetry sentences to report the full status of the UAV.

* Complete Hardware-In-the-Loop simulator allows you to test new algorithms directly in the auto pilot without leaving your desk. No more waiting for flying to test new ideas.

* Very low power allows to run on a typical RC battery for extended time. You can select to power the receiver and MUX from the same battery, or use an additional battery via configuration jumpers.

* Open. Hardware schematics, layout, and software source code available via a GIT repository with an MIT Open Source License.


2. Code and Hardware
====================

This section will guide you to get the complete repository to your hard drive. If you don't know what GIT is, you can of course read about it in the Wikipedia. This is a small screencast that was prepared for UCSC's Autonomous Systems Lab.

msysgit
--------

Using msysgit is the best way to get Git running on Windows. Git is officially supported under Cygwin, but I consider using it this way more of a hack and I also don't want to install all of Cygwin just for this (takes forever mostly). msysgit can be installed by downloading it from here. Make sure you select the plain Git installation, not the portable or msysgit versions. This is currently at version 1.6.5.1.

There are no surprises during the installation save one set of options. In order for msysgit to work properly with Tortoise Git you must select the option to add Git to the system PATH environment variable (this was the middle option in version 1.6.3).

Once you have msysgit running than all you have to do is open a git bash window (right click on the selected folder on the Windows explorer and select git bash here) and then type:

git clone git://github.com/malife/SLUGS.git

Tar or Zip File
---------------

If you only want a copy of the files and are not interested on getting all the benefits of GIT you can go to the github project page <http://github.com/malife/SLUGS>  and download a zip or tar file of the selected branch by clicking on the `download` button located in the top right corner.

3. Requirements
===============

Software Requirements
---------------------

These are the software requirements to get up and running. Note that if you do not plan on modifying any of the sections you do not need the requirements since we provide binaries for all of the sections. I.E. if you do not want to modify the Ground Station, then you do not need the components listed under that section.
Ground Station 

* Borland C++ Builder 6.0 (old version but very reliable. Yes, hard to find)
* RX Lib for C++ Builder Components (Free)
* Overbyte ICS UDP Components (Free)
* Abakus VCL for graphical components (Commercial)
* Tiny XML for interacting with KML files from Google Earth
* Simulink Models

* Matlab 2007A or newer with Simulink, the Real Time Workshop, and the Embedded Coder
* dsPIC Blockset
* Schematics and Layout

* Version 1 of the board is in Eagle 4.0
* Version 2 of the board in Orcad
* Microchip dsPIC Software and Hardware

* C30 Compiler Student Edition (free)
* PicKit 2 Programmer and Debugger (or any other dsPIC programmer)

Repository Organization
-----------------------

Sending a Board to Manufacture
------------------------------

Building a Connection Harness
-----------------------------

(Comment: Remember to point out that the PIC12 should be preprogrammed. Jonathan Lowert)

Flight Harness
--------------

Ground Harness
--------------

Understanding the Architecture
------------------------------

4. Installing Hardware to the UAV

5. Software Simulation

6. Hardware in the Loop Simulation

7. References
