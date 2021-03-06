# What is Speak Me Not?

Speak Me Not is a CLI/GUI speech synthesizer + microphone output for Windows that uses Google Translate &amp; VLC.

Lets say you don't have a microphone.

What this application can do is turn Google Translate into your voice; all you will need to do is type into the command line / GUI and the other party will hear Google Translate speaking through your microphone.

Cool, isn't it?

Although there is a command line version, there is a GUI version that is designed to be a "background" sort of application; with the press of a button, you can bring up an prompt and type in what you want to say swiftly.

How this application works is that it uses VLC to play the sound file from Google Translate. 

First, you need to setup a virtual audio cable to act as the virtual microphone (so that VLC can "reroute" the sound to a virtual external microphone) that you can use as your active microphone when talking to your friends via Skype, Steam, whatever.

Next, you will need to install (if you haven't) and configure VLC to use the virtual audio cable.

Note: I realize portable VLCs may exist so that installation (and configuration) of VLC would not be required by the user but I have not found one which is suitable.

A detailed step by step guide:

#Setup Guide

Part 1: Setting up the Virtual Audio Cable
---------------------------------
1.Download and install the driver from VB-AUDIO (zip file also included in guide pack)
	http://vb-audio.pagesperso-orange.fr/Cable/
2.Play some music.
3.Control Panel > Sound 
	OR
  Taskbar > Right click volume control > Sounds

4.Select the Playback tab.
5.Right click CABLE Input and Set as default device. The music should have stopped (as with all sound). If this doesn't happen, reboot and try again.
6.Select the Recording tab. CABLE Output should be seeing some action (see the bar).
7.Lets say you want to listen to what you're playing through this audio cable - 
	Right click CABLE Output and select properties
	Listen tab
	Check Listen to this device
	Select your speaker as the device

Step 7 can be used with any recording device (e.g. your mic, so you can do multiple things at 1 time like playing music and speaking while on Skype or gaming)

Part 2: Setting up the VLC player
---------------------------------
1. Install VLC media player (tested on 2.1.2 Rincewind). The guide is based on this version of VLC because it is not recently updated; for newer versions, you may have to explore on your own how to configure the Audio Output.
2. Tools > Preferences >
	 Interface > Privacy / Network Interaction
	 	Uncheck Save recently played items (OPTIONAL but recommended)
	 Interface > Playlist and Instances ***
	 	Check Allow only one instance
	 	Check Enqueue items into playlist in one instance mode
	 Audio > Output 
		Output Module: DirectX audio output (or waveout)
		Device: The virtual audio cable configured (CABLE Output)

3. Press the save button & close the VLC player. THIS IS IMPORTANT AS YOU NEED TO RESTART VLC MEDIA PLAYER FOR CHANGES TO TAKE EFFECT.
4. Play some music on the VLC player (if you don't got any on your computer, Media > Open Network Stream > paste in youtube link and press play). It should play music through the CABLE virtual audio cable.

5. Check "Allow only one instance" has both advantages and disadvantages, so evaluate both sides and decide whether to do so.
	**Good:**
		You would not experience the scenario of having multiple voices at one time, if you decide to speak before the previous speech has completed - instead, it would queue.
	**Bad:**
		You will only have one instance of VLC open - this means you cannot play music while speaking - at least, not with VLC.

Part 3: Setting up the software
--------------------------------
1. Navigate to your vlc.exe in your Program Files (32 bit), VideoLAN folder.
2. Create a shortcut to vlc.exe (right click vlc.exe and create shortcut).
3. Name the shortcut "vlcLNK".
4. Place the shortcut in the same folder as speakMeNot.exe.

Part 4: Setting up hot text (AKA shortcuts) (OPTIONAL)
--------------------------------
1. Open up the hotText.txt file (dist>speak me not>hotText.txt) for more details.
Hot Text are basically shortcut text; when you type in a hot text, it gets replaced by the text it is acting as a shortcut for. This can be used for shortcuts, or to manually configure Google Translate to sound more accurate if you are using slang.

You're done! 
--------------------------------


The MIT License (MIT)

Copyright (c) 2013 Crazoter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

