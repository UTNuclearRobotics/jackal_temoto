# jackal_temoto

This repository contains information about how to run TeMoto framework on Jackal. 

## Submodules
jackal --> Relevant packages for jackal 
jackal_robot --> Packages to bring up the robot
temoto --> Includes Temoto Core and all of the managers

# Running TeMoto Framework

Launch TeMoto
```bash
roslaunch jackal_tws temoto.launch temoto_namespace:=jack
```
If you want to load the robot using TeMoto, run in another terminal:
```bash
roslaunch ta_initialize_robot invoke_action.launch wake_word:=jack
```
If you want to bring up the robot using Phonex, please refer to https://wikis.utexas.edu/display/NRG/AFC+Jackal to see how to connect and run Jackal.

The ta_navigation_arl actions, works as a wrapper to send goal poses using TeMoto to Phoenix navigation. 

```bash
roslaunch ta_navigate_arl invoke_action.launch wake_word:=jack
```
