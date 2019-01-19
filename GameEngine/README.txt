/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<README>
Purpose:<Information about what implemented>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<10/16/2018>
-End Header --------------------------------------------------------*/

<History: 10/16/2018>
Control Guid:
Up     Image Up  Press
Down Image Down  Press
Left Image Down Trigger
Right Image Right Release

1      switch image 1
2      switch image 2

Suggestion: 1. press 1 or 2 to switch image
	   2. press Up Down Left Right buttons

if run and press Up Down Left Right buttons directly, you will see the image 2 

You can change the frame at '#define Frame' line, it means frames/second.

Moving is time-based.


<History: 10/26/2018>
Control Guid:
Up      	Image Up  	Press
Down  	Image Down  	Press
Left     	Image Down 	Press
Right  	Image Right	Press

can modify the files 'scene1' 'enemy' 'player' to modify the components of each gameObject, also can add more file to create more objects.

In 'scene1' file, you can modify lines with other file name(don't add '.txt'), that means you add a object. In the other file, you can modify components for this object.


sprite		sprite component, next line is the sprite name
transform 	transform component, next line is the position, need two number(float(0.0) and int(0) are both ok)
controller		controller component, don't need more line
updown 		updown component, next line is the speed and how far should the object move

<History: 11/1/2018>
Replace loading from txt to loading from Json.

can just modify the test.json. 


<History: 11/8/2018>
select 'help' manu before playing to get more information.