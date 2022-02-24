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
In another terminal we can load the robot:
```bash
roslaunch ta_initialize_robot invoke_action.launch wake_word:=jack
```

(Dont forget to source your workpace)
```bash
stemoto 
or 
source ~/jackal_temoto/devel/setup.bash
```

