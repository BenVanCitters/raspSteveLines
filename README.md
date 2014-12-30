raspSteveLines
==============

Jazz Music Visualizer

This is a project dedicated to Johnny Muller - who will be missed.  It is a project that deals with openFrameworks 8.4 and GLSL specifically configured to work on the raspberry pi

In it's current state the app is meant to run on a raspbian raspberry pi with a webcam attached that has a microphone.  If these conditions are met it will put out a waveform display and then do some cool shader FX with those.  It draws a waveform 'triangle strip' via the audio shader and, in turn, draws that to an FBO and draws that on top of itself to get a nice feedback effect via the GLSL shaders feedback.vert & feedback.frag.

This project owes some gratitude to the repo at https://github.com/openFrameworks-arm/Resonate2013Workshop for showing how to do shaders on the 'Pi and Joshua Noble for making these Raspberry Pi+openFrameworks examples known to me.

