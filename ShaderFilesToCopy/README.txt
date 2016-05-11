Use these modified unreal shader files (usf) if you are using depth of field in your post proccess.

Copy the files to the engine's shader folder (e.g. Program Files\Epic Games\4.11\Engine\Shaders) and replace the originals.

Note:
Use these only with the engine version the branch is marked for.
The engine will crash if used with an incompatible version so I recommend you to BACKUP the original files first.



Why do we need custom .usf? and how does it work?

Well, translucent objects (like the ocean plane) do not write in the depth buffer in UE4 
but DOF uses the scene depth in its calculations which results in visual errors where there is ocean.

With these .usf files, DOF will also read from the custom depth buffer (in code it's simply something like min(CustomDepth, SceneDepth)).
The ocean blueprint uses a secondary opaque mesh which writes to the custom depth buffer only for this to work.


