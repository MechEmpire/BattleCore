--Configuration Data for Armors: Mech Empire II
--Version 2014/08/16
--By MangoSister and ShrekShao


--Weapon Data

--Name of Each Weapon
name_Weapon={};
name_Weapon[1]="Cannon";
name_Weapon[2]="Shotgun";
name_Weapon[3]="R.P.G.";
name_Weapon[4]="Machine gun";
name_Weapon[5]="Prism";
name_Weapon[6]="Tesla";
name_Weapon[7]="Plasma torch";
name_Weapon[8]="Missile launcher";
name_Weapon[9]="Electric saw";
name_Weapon[10]="Grenade Thrower";
name_Weapon[11]="Mine Layer";


--Damage of Each Weapon
--already abandoned
--damage is a value of Bullet

--Magazine Capacity of Each Weapon
Ammo_Weapon={};
Ammo_Weapon[1]=10;
Ammo_Weapon[2]=8;
Ammo_Weapon[3]=5;
Ammo_Weapon[4]=50;
Ammo_Weapon[5]=7;
Ammo_Weapon[6]=11;
Ammo_Weapon[7]=12;
Ammo_Weapon[8]=10;
Ammo_Weapon[9]=100;
Ammo_Weapon[10]=9;
Ammo_Weapon[11]=40;		--num of mines

--Cooling Time of Each Weapon
coolingTime_Weapon={};
coolingTime_Weapon[1]=30;
coolingTime_Weapon[2]=80;
coolingTime_Weapon[3]=100;
coolingTime_Weapon[4]=5;
coolingTime_Weapon[5]=50;
coolingTime_Weapon[6]=40;
coolingTime_Weapon[7]=25;
coolingTime_Weapon[8]=100;
coolingTime_Weapon[9]=1;
coolingTime_Weapon[10]=40;
coolingTime_Weapon[11]=50;		--cooling time of laying mine

--Deviation of Each Weapon when Attacking
inaccuracy_Weapon={};
inaccuracy_Weapon[1]=5;
inaccuracy_Weapon[2]=5;
inaccuracy_Weapon[3]=3;
inaccuracy_Weapon[4]=7;
inaccuracy_Weapon[5]=5;
inaccuracy_Weapon[6]=30;
inaccuracy_Weapon[7]=5;
inaccuracy_Weapon[8]=5;
inaccuracy_Weapon[9]=5;
inaccuracy_Weapon[10]=20;
inaccuracy_Weapon[11]=0;

--Rotation Speed of Each Weapon when Turning
rotationSpeed_Weapon={};
rotationSpeed_Weapon[1]=5;
rotationSpeed_Weapon[2]=2;
rotationSpeed_Weapon[3]=5;
rotationSpeed_Weapon[4]=4;
rotationSpeed_Weapon[5]=1;
rotationSpeed_Weapon[6]=3;
rotationSpeed_Weapon[7]=1.5;
rotationSpeed_Weapon[8]=2;
rotationSpeed_Weapon[9]=2;
rotationSpeed_Weapon[10]=5;
rotationSpeed_Weapon[11]=3;

--Radium of Weapon
radium_Weapon={};
radium_Weapon[1]=95;
radium_Weapon[2]=65;
radium_Weapon[3]=85;
radium_Weapon[4]=69;
radium_Weapon[5]=76;
radium_Weapon[6]=45;
radium_Weapon[7]=75;
radium_Weapon[8]=50;
radium_Weapon[9]=95;
radium_Weapon[10]=50;
radium_Weapon[11]=50;

--Cooling Speed for all Weapons
coolingSpeed_AllWeapon=1;

--Specific Properties of Shotgun
burst_Shotgun=5;
gapRotation_Shotgun=3;


--for Mine Layer
coolingTime_Tiny_MineLayer=20;
ammoConsumption_Mine_MineLayer=5;



--Bullets Info
name_Bullet={};
name_Bullet[1]="加农炮弹";
name_Bullet[2]="霰弹砂";
name_Bullet[3]="火箭弹";
name_Bullet[4]="银色子弹";
name_Bullet[5]="光棱";
name_Bullet[6]="磁暴";
name_Bullet[7]="等离子";
name_Bullet[8]="跟踪导弹";
name_Bullet[9]="电锯";
name_Bullet[10]="手雷";
name_Bullet[11]="Vulture地雷";
name_Bullet[12]="微型10mm辅助子弹";


speed_Bullet={};
speed_Bullet[1]=8;
speed_Bullet[2]=7.5;
speed_Bullet[3]=6;
speed_Bullet[4]=10;
speed_Bullet[5]=5;
speed_Bullet[6]=5;
speed_Bullet[7]=5;
speed_Bullet[8]=4;
speed_Bullet[9]=5;
speed_Bullet[10]=4;
speed_Bullet[11]=0;
speed_Bullet[12]=5;



--Damage of Each Bullet
damage_Bullet={};
damage_Bullet[1]=25;
damage_Bullet[2]=10;
damage_Bullet[3]=35;
damage_Bullet[4]=7;
damage_Bullet[5]=20;
damage_Bullet[6]=22;
damage_Bullet[7]=18;
damage_Bullet[8]=15;
damage_Bullet[9]=5;
damage_Bullet[10]=25;
damage_Bullet[11]=45;
damage_Bullet[12]=4;


--flyTime of Each Bullet
flyTime_Bullet={};
flyTime_Bullet[1]=9999;
flyTime_Bullet[2]=9999;
flyTime_Bullet[3]=9999;
flyTime_Bullet[4]=9999;
flyTime_Bullet[5]=1;
flyTime_Bullet[6]=1;
flyTime_Bullet[7]=9999;
flyTime_Bullet[8]=9999;
flyTime_Bullet[9]=1;
flyTime_Bullet[10]=100;
flyTime_Bullet[11]=200;		--??
flyTime_Bullet[12]=9999;


--RPGBall
explodeR_RPGBall=100;
acceleration_RPGBall=1.05;

--Grenade
explodeR_Grenade=70;

--Mine
explodeR_Mine=100;

--PlasmaBall
bounce_time=2;

--TrackingMissile
spinSpeed_TrackingMissile=1.5;



--Engine Data

--Name of Each Engine
name_Engine={};
name_Engine[1]="Spider V3";
name_Engine[2]="Destroyer";
name_Engine[3]="Warhammer Tank"
name_Engine[4]="UFO"

--maxSpeed
maxSpeed_Engine={};
maxSpeed_Engine[1]=4;
maxSpeed_Engine[2]=5;
maxSpeed_Engine[3]=7;
maxSpeed_Engine[4]=6;

--Hp
maxHp_Engine={};
maxHp_Engine[1]=85;
maxHp_Engine[2]=90;
maxHp_Engine[3]=100;
maxHp_Engine[4]=100;

--RotationSpeed
rotationSpeed_Engine={};
rotationSpeed_Engine[1]=0;
rotationSpeed_Engine[2]=3;
rotationSpeed_Engine[3]=3.5;
rotationSpeed_Engine[4]=4.5;

--Acceleration
acceleration_Engine={};
acceleration_Engine[1]=0;
acceleration_Engine[2]=0;
acceleration_Engine[3]=0.15;
acceleration_Engine[4]=0.2;

--Radium of engine
radium_Engine={};
radium_Engine[1]=45;
radium_Engine[2]=48;
radium_Engine[3]=50;
radium_Engine[4]=46;


--Arsenal
radium_Arsenal=5;
respawningTime_Arsenal=1000;