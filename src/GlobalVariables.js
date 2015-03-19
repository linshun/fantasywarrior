UIZorder = 2000
FXZorder = 1999
CelLine = 0.009
currentLayer = null;

var particleRes = {
    "iceTrail" : "FX/iceTrail.plist",
    "magic" : "FX/magic.plist",
    "pixi" : "FX/pixi.plist",
    "puffRing" : "FX/puffRing.plist",
    "puffRing2" : "FX/puffRing2.plist",
    "walkpuff" : "FX/walkingPuff.plist"
}

var spriteFrameRes = [
    "FX/FX.plist",
    "chooseRole/chooserole.plist",
    "battlefieldUI/battleFieldUI.plist",
    "mainmenuscene/mainmenuscene.plist",
];

var BGM_RES = {
    MAINMENUBGM : "audios/01 Beast Hunt.mp3",
    MAINMENUSTART: "audios/effects/magical_3.mp3",
    BATTLEFIELDBGM : "audios/The_Last_Encounter_Short_Loop.mp3",
    CHOOSEROLESCENEBGM : "audios/Imminent Threat Beat B FULL Loop.mp3"
}

//Warroir property
WarriorProperty = {
    normalAttack1 : "audios/effects/knight/swish-1.mp3",
    normalAttack2 : "audios/effects/knight/swish-2.mp3",
    specialAttack1 : "audios/effects/knight/swish-3.mp3",
    specialAttack2 : "audios/effects/knight/swish-4.mp3",
    kickit : "audios/effects/knight/kickit.mp3",
    normalAttackShout : "audios/effects/knight/normalAttackShout.mp3",
    specialAttackShout : "audios/effects/knight/specialAttackShout.mp3",
    wounded : "audios/effects/knight/wounded.mp3",
    dead : "audios/effects/knight/dead.mp3"
}

//Archer property
Archerproperty = {
    attack1 : "audios/effects/archer/swish-3.mp3",
    attack2 : "audios/effects/archer/swish-4.mp3",
    iwillfight : "audios/effects/archer/iwillfight.mp3",
    wounded : "audios/effects/archer/hurt.mp3",
    normalAttackShout : "audios/effects/archer/normalAttackShout.mp3",
    specialAttackShout : "audios/effects/archer/specialAttackShout.mp3",
    wounded : "audios/effects/archer/hurt.mp3",
    dead : "audios/effects/archer/dead.mp3"
}

//Mage property
MageProperty = {
    blood : 1000,
    attack : 100,
    defense : 100,
    speed : 50,
    special_attack_chance : 0.33,
        letstrade : "audios/effects/mage/letstrade.mp3",
    ice_normal : "audios/effects/mage/ice_1.mp3",
    ice_special : "audios/effects/mage/ice_2.mp3",
    ice_normalAttackHit : "audios/effects/mage/ice_3.mp3",
    ice_specialAttackHit : "audios/effects/mage/ice_4.mp3",
    specialAttackShout : "audios/effects/mage/specialAttack.mp3",
    normalAttackShout : "audios/effects/mage/normalAttack.mp3",
    wounded : "audios/effects/mage/hurt.mp3",
    dead : "audios/effects/mage/dead.mp3"
}

KnightValues = {
    // _racetype       : EnumRaceType.HERO,
    _name           : "Knight",
    _radius         : 50,
    _mass           : 1000,
    _shadowSize     : 70,
    
    _hp             : 1850,
    _maxhp          : 1850,
    _defense        : 180,
    _attackFrequency : 2.2,
    _recoverTime    : 0.4,
    _AIFrequency    : 1.1,
    _attackRange    : 140,
    _specialAttackChance : 0,
    _specialSlowTime : 1, 

    _normalAttack   : {
        minRange : 0,
        maxRange : 130,
        angle    : cc.degreesToRadians(70),
        knock    : 60,
        damage   : 250,
        // mask     : EnumRaceType.HERO,
        duration : 0,
        speed    : 0,
        criticalChance : 0.15
    }, 
    _specialAttack   : {
        minRange : 0,
        maxRange : 250,
        angle    : cc.degreesToRadians(160),
        knock    : 150,
        damage   : 350,
        // mask     : EnumRaceType.HERO,
        duration : 0,
        speed    : 0,
        criticalChance : 0.35
    }, 
}

ArcherValues = {
    // _racetype       : EnumRaceType.HERO,
    _name           : "Archer",
    _radius         : 50,
    _mass           : 800,
    _shadowSize     : 70,

    _hp             : 1200,
    _maxhp          : 1200,
    _defense        : 130,
    _attackFrequency : 2.5,
    _recoverTime    : 0.4,
    _AIFrequency    : 1.3,
    _attackRange    : 450,
    _specialAttackChance : 0,
    _turnSpeed      : cc.degreesToRadians(360), //actor turning speed in radians/seconds
    _specialSlowTime : 0.5, 

    _normalAttack   : {
        minRange : 0,
        maxRange : 30,
        angle    : cc.degreesToRadians(360),
        knock    : 100,
        damage   : 200,
        // mask     : EnumRaceType.HERO,
        duration : 1.3,
        speed    : 900,
        criticalChance : 0.33
    }, 
    _specialAttack   : {
        minRange : 0,
        maxRange : 75,
        angle    : cc.degreesToRadians(360),
        knock    : 100,
        damage   : 200,
        // mask     : EnumRaceType.HERO,
        duration : 1.5,
        speed    : 850,
        criticalChance : 0.5,
        DOTTimer : 0.3,
        curDOTTime : 0.3,
        DOTApplied : false
    }, 
}

MageValues = {
    // _racetype       : EnumRaceType.HERO,
    _name           : "Mage",
    _radius         : 50,
    _mass           : 800,
    _shadowSize     : 70,

    _hp             : 1100,
    _maxhp          : 1100,
    _defense        : 120,
    _attackFrequency : 2.67,
    _recoverTime    : 0.8,
    _AIFrequency    : 1.33,
    _attackRange    : 400,
    _specialAttackChance : 0,
    _specialSlowTime : 0.67,

    _normalAttack   : {
        minRange : 0,
        maxRange : 50,
        angle    : cc.degreesToRadians(360),
        knock    : 10,
        damage   : 280,
        // mask     : EnumRaceType.HERO,
        duration : 2,
        speed    : 400,
        criticalChance : 0.05
    }, 
    _specialAttack   : {
        minRange : 0,
        maxRange : 140,
        angle    : cc.degreesToRadians(360),
        knock    : 75,
        damage   : 250,
        // mask     : EnumRaceType.HERO,
        duration : 4.5,
        speed    : 0,
        criticalChance : 0.05,
        DOTTimer : 0.75, //it will be able to hurt every 0.5 seconds
        curDOTTime : 0.75,
        DOTApplied : false
    }, 
}

ReSkin = {
    knight : {weapon : 0, armour : 0, helmet : 0},
    archer : {weapon : 0, armour : 0, helmet : 0},
    mage : {weapon : 0, armour : 0, helmet : 0}
}