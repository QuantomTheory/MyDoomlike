# SurvivalShooter
The second solo project for my portfolio, a simple FPS wave-based game with multiple weapons and a grappling hook for increased mobility.

Project Overview
This is a simple FPS game. It requires the player to survive for 5 increasingly difficult waves of enemies. To defeat a wave you must kill all the enemies in the allotted 3 mins.
The player has access to 4 weapons to defeat enemies, and a grappling hook for increased mobility.
This project was built by myself in Unreal Engine 5, using C++. All the visual and audio assets are from the Unreal Engine Marketplace.

My goal with this demo was to take what I had learned so far, and expand on it by challenging myself with new mechanics and features.
This included creating a grappling hook that should be fun and satisfying to use, as well creating multiple weapons that each feel at least somewhat unique.

This was my second solo project for my portfolio. With this project I wanted to make an FPA game that is fast paced with a decent mobility. I took inspiration from the recent DOOM games from id Software, and tried to create a fast paced game, with the grappling hook to allow the player to quickly move around the map. I wanted to expand on what I had learned so far, and add new features that would challenge me to build.

Player Character:
The player class was made as a child to the Character class, it contains all the functionality to receive player input, control the character and camera, as well as use the currently equipped weapon and grappling hook. It contains the functionality to cycle between weapons and manage the animation for that. Additionally, it contains a LookTrace that returns the location of where the player is looking, this is called by the guns so as to always fire towards the crosshair.

Weapons: The player has four different weapons available to them, a standard Assault Rifle, a high-damage short-range Shotgun, a rapid-fire Laser Gun, and a powerful Grenade Launcher. With a Grappling Hook to let them zip and swing around the map to avoid enemies.
To create the weapons I started by creating a base Gun c++ class that holds all the functionality for the standard projectile gun (e.g. firing a projectile, tracking clip ammo, reloading etc). This c++ class was then used to create the Assault Rifle and Grenade Launcher Blueprint classes.
Then, I created a child class HitScan_Gun c++ class from the Gun class. This overrides the Fire function to instead use a line trace instead of firing a projectile object. This class is then used to create the Shotgun and Laser Gun Blueprint classes.
Within both versions of the Gun c++ class, the fire function makes use of the <random> library to implement a ShotDistributionAngle to account for "bullet spray". Additionally, the HitScan_Gun uses a ShotCount variable to easily increase or decrease how many line traces to use per shot. Together, these variables allow you to very easily create a wide variety of projectile or hit scan guns.

Projectiles: To make the projectiles for the Assault Rifle and Grenade Launcher, I created a BaseProjectile c++ class that would deal damage on hit with an actor. I then created a child AoE_Projectile c++ class that would instead deal radial damage with falloff when it hit an actor. I would use the BaseProjectile to create an AssaultRifle_Projectile Blueprint class, and the AoE_Projectile to create a Grenade Blueprint class.

Grappling Hook: To make the grappling hook I created a GrappleLauncher c++ actor class that could be attached to the player, from which the grappling hook projectile would be launched from. This contained the functionality to launch the projectile, retract the hook to pull the player towards the grapple point, and cancel the grapple. I then created a GrappleHook c++ class, this contained a projectile movement component, and OnHit would trigger the Retract function on the Grapple Launcher.
The GrappleLauncher retract function would set a variable to true, then within the tick function, an impulse is applied to the player in the direction of the grapple hook. once the player is within a certain distance of the hook, it is automatically released.
‍
Health Component: The health component is functionally similar as in Arcane Defence, it tracks an actors current health, applies damage received, and checks if the actor IsDead. The single piece of new functionality is the ability to heal. Currently, this is only achieved by the Health Pickups placed around the map and dropped by enemies. When the player steps gains health that would exceed the MaxHealth, this bonus health is still applied as OverHealth but will deteriorate automatically. The rate at which the health decreases is greater the more OverHealth is present, with the rate slowing as it approaches the MaxHealth value, to a minimum loss rate of 1HP per second.

Inventory Component: The Inventory component simply stores the 4 weapons, and keeps track of what is the currently equipped weapon as well as changing the current weapon.

Challenges:
The main challenge that I faced throughout this project, was trying to get the mechanics to feel natural and fun to use. This meant getting the grappling hook to feel fun and have intuitive movement, I opted for more of a "rope swing" style grappling hook rather than an "reel-to-point" style, I chose this because the type of game I made was less about using it to explore a 3D space but instead increase mobility in an enclosed space.
