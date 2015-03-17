/**
 * @module cocos2dx_custom
 */
var cc = cc || {};

/**
 * @class Effect3D
 */
cc.Effect3D = {

/**
 * @method draw
 * @param {mat4_object} arg0
 */
draw : function (
mat4 
)
{
},

/**
 * @method setTarget
 * @param {cc.Sprite3D} arg0
 * @param {cc.Mesh} arg1
 */
setTarget : function (
sprite3d, 
mesh 
)
{
},

};

/**
 * @class Effect3DOutline
 */
cc.Effect3DOutline = {

/**
 * @method setOutlineWidth
 * @param {float} arg0
 */
setOutlineWidth : function (
float 
)
{
},

/**
 * @method setOutlineColor
 * @param {vec3_object} arg0
 */
setOutlineColor : function (
vec3 
)
{
},

/**
 * @method create
 * @return {cc.Effect3DOutline}
 */
create : function (
)
{
    return cc.Effect3DOutline;
},

};

/**
 * @class EffectSprite3D
 */
cc.EffectSprite3D = {

/**
 * @method setEffect3D
 * @param {cc.Effect3D} arg0
 */
setEffect3D : function (
effect3d 
)
{
},

/**
 * @method addEffect
 * @param {vec3_object} arg0
 * @param {float} arg1
 * @param {int} arg2
 */
addEffect : function (
vec3, 
float, 
int 
)
{
},

/**
 * @method getMesh
 * @return {Array}
 */
getMesh : function (
)
{
    return new Array();
},

/**
 * @method getMeshNum
 * @return {int}
 */
getMeshNum : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {cc.EffectSprite3D}
 */
create : function (
str 
)
{
    return cc.EffectSprite3D;
},

/**
 * @method createFromObjFileAndTexture
 * @param {String} arg0
 * @param {String} arg1
 * @return {cc.EffectSprite3D}
 */
createFromObjFileAndTexture : function (
str, 
str 
)
{
    return cc.EffectSprite3D;
},

};

/**
 * @class BillboardParticleSystem
 */
cc.BillboardParticleSystem = {

/**
 * @method getStartSizeVar
 * @return {float}
 */
getStartSizeVar : function (
)
{
    return 0;
},

/**
 * @method getStartColor
 * @return {color4f_object}
 */
getStartColor : function (
)
{
    return cc.Color4F;
},

/**
 * @method getPositionType
 * @return {cc.BillboardParticleSystem::PositionType}
 */
getPositionType : function (
)
{
    return 0;
},

/**
 * @method setPosVar
 * @param {vec2_object} arg0
 */
setPosVar : function (
vec2 
)
{
},

/**
 * @method getEndSpin
 * @return {float}
 */
getEndSpin : function (
)
{
    return 0;
},

/**
 * @method setRotatePerSecondVar
 * @param {float} arg0
 */
setRotatePerSecondVar : function (
float 
)
{
},

/**
 * @method getStartSpinVar
 * @return {float}
 */
getStartSpinVar : function (
)
{
    return 0;
},

/**
 * @method getRadialAccelVar
 * @return {float}
 */
getRadialAccelVar : function (
)
{
    return 0;
},

/**
 * @method getEndSizeVar
 * @return {float}
 */
getEndSizeVar : function (
)
{
    return 0;
},

/**
 * @method setRotation
 * @param {float} arg0
 */
setRotation : function (
float 
)
{
},

/**
 * @method setTangentialAccel
 * @param {float} arg0
 */
setTangentialAccel : function (
float 
)
{
},

/**
 * @method setScaleY
 * @param {float} arg0
 */
setScaleY : function (
float 
)
{
},

/**
 * @method setScaleX
 * @param {float} arg0
 */
setScaleX : function (
float 
)
{
},

/**
 * @method getRadialAccel
 * @return {float}
 */
getRadialAccel : function (
)
{
    return 0;
},

/**
 * @method setStartRadius
 * @param {float} arg0
 */
setStartRadius : function (
float 
)
{
},

/**
 * @method setRotatePerSecond
 * @param {float} arg0
 */
setRotatePerSecond : function (
float 
)
{
},

/**
 * @method setEndSize
 * @param {float} arg0
 */
setEndSize : function (
float 
)
{
},

/**
 * @method getGravity
 * @return {vec2_object}
 */
getGravity : function (
)
{
    return cc.Vec2;
},

/**
 * @method getTangentialAccel
 * @return {float}
 */
getTangentialAccel : function (
)
{
    return 0;
},

/**
 * @method setEndRadius
 * @param {float} arg0
 */
setEndRadius : function (
float 
)
{
},

/**
 * @method getSpeed
 * @return {float}
 */
getSpeed : function (
)
{
    return 0;
},

/**
 * @method getAngle
 * @return {float}
 */
getAngle : function (
)
{
    return 0;
},

/**
 * @method setEndColor
 * @param {color4f_object} arg0
 */
setEndColor : function (
color4f 
)
{
},

/**
 * @method setStartSpin
 * @param {float} arg0
 */
setStartSpin : function (
float 
)
{
},

/**
 * @method setDuration
 * @param {float} arg0
 */
setDuration : function (
float 
)
{
},

/**
 * @method setTexture
 * @param {cc.Texture2D} arg0
 */
setTexture : function (
texture2d 
)
{
},

/**
 * @method getPosVar
 * @return {vec2_object}
 */
getPosVar : function (
)
{
    return cc.Vec2;
},

/**
 * @method isBlendAdditive
 * @return {bool}
 */
isBlendAdditive : function (
)
{
    return false;
},

/**
 * @method getSpeedVar
 * @return {float}
 */
getSpeedVar : function (
)
{
    return 0;
},

/**
 * @method setPositionType
 * @param {cc.BillboardParticleSystem::PositionType} arg0
 */
setPositionType : function (
positiontype 
)
{
},

/**
 * @method stopSystem
 */
stopSystem : function (
)
{
},

/**
 * @method getSourcePosition
 * @return {vec2_object}
 */
getSourcePosition : function (
)
{
    return cc.Vec2;
},

/**
 * @method setLifeVar
 * @param {float} arg0
 */
setLifeVar : function (
float 
)
{
},

/**
 * @method setTotalParticles
 * @param {int} arg0
 */
setTotalParticles : function (
int 
)
{
},

/**
 * @method setEndColorVar
 * @param {color4f_object} arg0
 */
setEndColorVar : function (
color4f 
)
{
},

/**
 * @method getAtlasIndex
 * @return {int}
 */
getAtlasIndex : function (
)
{
    return 0;
},

/**
 * @method getStartSize
 * @return {float}
 */
getStartSize : function (
)
{
    return 0;
},

/**
 * @method setTextureWithRect
 * @param {cc.Texture2D} arg0
 * @param {rect_object} arg1
 */
setTextureWithRect : function (
texture2d, 
rect 
)
{
},

/**
 * @method setStartSpinVar
 * @param {float} arg0
 */
setStartSpinVar : function (
float 
)
{
},

/**
 * @method resetSystem
 */
resetSystem : function (
)
{
},

/**
 * @method setAtlasIndex
 * @param {int} arg0
 */
setAtlasIndex : function (
int 
)
{
},

/**
 * @method setTangentialAccelVar
 * @param {float} arg0
 */
setTangentialAccelVar : function (
float 
)
{
},

/**
 * @method getDuration
 * @return {float}
 */
getDuration : function (
)
{
    return 0;
},

/**
 * @method getEndRadius
 * @return {float}
 */
getEndRadius : function (
)
{
    return 0;
},

/**
 * @method setDepthTestEnabled
 * @param {bool} arg0
 */
setDepthTestEnabled : function (
bool 
)
{
},

/**
 * @method setRadialAccelVar
 * @param {float} arg0
 */
setRadialAccelVar : function (
float 
)
{
},

/**
 * @method setStartSize
 * @param {float} arg0
 */
setStartSize : function (
float 
)
{
},

/**
 * @method setSpeed
 * @param {float} arg0
 */
setSpeed : function (
float 
)
{
},

/**
 * @method getStartSpin
 * @return {float}
 */
getStartSpin : function (
)
{
    return 0;
},

/**
 * @method getRotatePerSecond
 * @return {float}
 */
getRotatePerSecond : function (
)
{
    return 0;
},

/**
 * @method setEmitterMode
 * @param {cc.BillboardParticleSystem::Mode} arg0
 */
setEmitterMode : function (
mode 
)
{
},

/**
 * @method setEndRadiusVar
 * @param {float} arg0
 */
setEndRadiusVar : function (
float 
)
{
},

/**
 * @method isOpacityModifyRGB
 * @return {bool}
 */
isOpacityModifyRGB : function (
)
{
    return false;
},

/**
 * @method setSourcePosition
 * @param {vec2_object} arg0
 */
setSourcePosition : function (
vec2 
)
{
},

/**
 * @method getEndSpinVar
 * @return {float}
 */
getEndSpinVar : function (
)
{
    return 0;
},

/**
 * @method setBlendAdditive
 * @param {bool} arg0
 */
setBlendAdditive : function (
bool 
)
{
},

/**
 * @method setLife
 * @param {float} arg0
 */
setLife : function (
float 
)
{
},

/**
 * @method setAngleVar
 * @param {float} arg0
 */
setAngleVar : function (
float 
)
{
},

/**
 * @method setRotationIsDir
 * @param {bool} arg0
 */
setRotationIsDir : function (
bool 
)
{
},

/**
 * @method setEndSizeVar
 * @param {float} arg0
 */
setEndSizeVar : function (
float 
)
{
},

/**
 * @method setAngle
 * @param {float} arg0
 */
setAngle : function (
float 
)
{
},

/**
 * @method getTangentialAccelVar
 * @return {float}
 */
getTangentialAccelVar : function (
)
{
    return 0;
},

/**
 * @method getEmitterMode
 * @return {cc.BillboardParticleSystem::Mode}
 */
getEmitterMode : function (
)
{
    return 0;
},

/**
 * @method setEndSpinVar
 * @param {float} arg0
 */
setEndSpinVar : function (
float 
)
{
},

/**
 * @method getAngleVar
 * @return {float}
 */
getAngleVar : function (
)
{
    return 0;
},

/**
 * @method setStartColor
 * @param {color4f_object} arg0
 */
setStartColor : function (
color4f 
)
{
},

/**
 * @method getRotatePerSecondVar
 * @return {float}
 */
getRotatePerSecondVar : function (
)
{
    return 0;
},

/**
 * @method getEndSize
 * @return {float}
 */
getEndSize : function (
)
{
    return 0;
},

/**
 * @method getLife
 * @return {float}
 */
getLife : function (
)
{
    return 0;
},

/**
 * @method setSpeedVar
 * @param {float} arg0
 */
setSpeedVar : function (
float 
)
{
},

/**
 * @method setGravity
 * @param {vec2_object} arg0
 */
setGravity : function (
vec2 
)
{
},

/**
 * @method setEmissionRate
 * @param {float} arg0
 */
setEmissionRate : function (
float 
)
{
},

/**
 * @method getEndColorVar
 * @return {color4f_object}
 */
getEndColorVar : function (
)
{
    return cc.Color4F;
},

/**
 * @method getRotationIsDir
 * @return {bool}
 */
getRotationIsDir : function (
)
{
    return false;
},

/**
 * @method setScale
 * @param {float} arg0
 */
setScale : function (
float 
)
{
},

/**
 * @method getEmissionRate
 * @return {float}
 */
getEmissionRate : function (
)
{
    return 0;
},

/**
 * @method getEndColor
 * @return {color4f_object}
 */
getEndColor : function (
)
{
    return cc.Color4F;
},

/**
 * @method getLifeVar
 * @return {float}
 */
getLifeVar : function (
)
{
    return 0;
},

/**
 * @method setCamera
 * @param {cc.Camera} arg0
 */
setCamera : function (
camera 
)
{
},

/**
 * @method setStartSizeVar
 * @param {float} arg0
 */
setStartSizeVar : function (
float 
)
{
},

/**
 * @method setOpacityModifyRGB
 * @param {bool} arg0
 */
setOpacityModifyRGB : function (
bool 
)
{
},

/**
 * @method getStartRadius
 * @return {float}
 */
getStartRadius : function (
)
{
    return 0;
},

/**
 * @method getParticleCount
 * @return {unsigned int}
 */
getParticleCount : function (
)
{
    return 0;
},

/**
 * @method getStartRadiusVar
 * @return {float}
 */
getStartRadiusVar : function (
)
{
    return 0;
},

/**
 * @method setStartColorVar
 * @param {color4f_object} arg0
 */
setStartColorVar : function (
color4f 
)
{
},

/**
 * @method setEndSpin
 * @param {float} arg0
 */
setEndSpin : function (
float 
)
{
},

/**
 * @method setRadialAccel
 * @param {float} arg0
 */
setRadialAccel : function (
float 
)
{
},

/**
 * @method setStartRadiusVar
 * @param {float} arg0
 */
setStartRadiusVar : function (
float 
)
{
},

/**
 * @method getEndRadiusVar
 * @return {float}
 */
getEndRadiusVar : function (
)
{
    return 0;
},

/**
 * @method getStartColorVar
 * @return {color4f_object}
 */
getStartColorVar : function (
)
{
    return cc.Color4F;
},

/**
 * @method create
* @param {map_object|String} map
* @return {cc.BillboardParticleSystem|cc.BillboardParticleSystem}
*/
create : function(
str 
)
{
    return cc.BillboardParticleSystem;
},

/**
 * @method BillboardParticleSystem
 * @constructor
 */
BillboardParticleSystem : function (
)
{
},

};

/**
 * @class Sequence3D
 */
cc.Sequence3D = {

/**
 * @method initWithActions
 * @param {Array} arg0
 * @return {bool}
 */
initWithActions : function (
array 
)
{
    return false;
},

/**
 * @method create
 * @param {Array} arg0
 * @return {cc.Sequence3D}
 */
create : function (
array 
)
{
    return cc.Sequence3D;
},

/**
 * @method Sequence3D
 * @constructor
 */
Sequence3D : function (
)
{
},

};

/**
 * @class DrawNode3D
 */
cc.DrawNode3D = {

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method drawLine
 * @param {vec3_object} arg0
 * @param {vec3_object} arg1
 * @param {color4f_object} arg2
 */
drawLine : function (
vec3, 
vec3, 
color4f 
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method onDraw
 * @param {mat4_object} arg0
 * @param {unsigned int} arg1
 */
onDraw : function (
mat4, 
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method drawCube
 * @param {vec3_object} arg0
 * @param {color4f_object} arg1
 */
drawCube : function (
vec3, 
color4f 
)
{
},

/**
 * @method create
 * @return {cc.DrawNode3D}
 */
create : function (
)
{
    return cc.DrawNode3D;
},

/**
 * @method DrawNode3D
 * @constructor
 */
DrawNode3D : function (
)
{
},

};

/**
 * @class Effect
 */
cc.Effect = {

/**
 * @method setTarget
 * @param {cc.EffectSprite} arg0
 */
setTarget : function (
effectsprite 
)
{
},

/**
 * @method updateUniforms
 */
updateUniforms : function (
)
{
},

/**
 * @method getGLProgramState
 * @return {cc.GLProgramState}
 */
getGLProgramState : function (
)
{
    return cc.GLProgramState;
},

};

/**
 * @class EffectNormalMapped
 */
cc.EffectNormalMapped = {

/**
 * @method setKBump
 * @param {float} arg0
 */
setKBump : function (
float 
)
{
},

/**
 * @method setPointLight
 * @param {point_object} arg0
 */
setPointLight : function (
pointlight 
)
{
},

/**
 * @method getKBump
 * @return {float}
 */
getKBump : function (
)
{
    return 0;
},

/**
 * @method create
* @param {String} str
* @return {cc.EffectNormalMapped|cc.EffectNormalMapped}
*/
create : function(
str 
)
{
    return cc.EffectNormalMapped;
},

};

/**
 * @class EffectSprite
 */
cc.EffectSprite = {

/**
 * @method setEffect
 * @param {cc.Effect} arg0
 */
setEffect : function (
effect 
)
{
},

/**
 * @method addEffect
 * @param {cc.Effect} arg0
 * @param {int} arg1
 */
addEffect : function (
effect, 
int 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @return {cc.EffectSprite}
 */
create : function (
str 
)
{
    return cc.EffectSprite;
},

};

/**
 * @class GreyShader
 */
cc.GreyShader = {

/**
 * @method setGreyShader
 * @param {cc.Sprite} arg0
 */
setGreyShader : function (
sprite 
)
{
},

};

/**
 * @class JumpBy3D
 */
cc.JumpBy3D = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {vec3_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
vec3, 
float, 
int 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {vec3_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {cc.JumpBy3D}
 */
create : function (
float, 
vec3, 
float, 
int 
)
{
    return cc.JumpBy3D;
},

/**
 * @method JumpBy3D
 * @constructor
 */
JumpBy3D : function (
)
{
},

};

/**
 * @class JumpTo3D
 */
cc.JumpTo3D = {

/**
 * @method create
 * @param {float} arg0
 * @param {vec3_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {cc.JumpTo3D}
 */
create : function (
float, 
vec3, 
float, 
int 
)
{
    return cc.JumpTo3D;
},

/**
 * @method JumpTo3D
 * @constructor
 */
JumpTo3D : function (
)
{
},

};

/**
 * @class ShadowSprite
 */
cc.ShadowSprite = {

/**
 * @method create
 * @param {String} arg0
 * @return {cc.ShadowSprite}
 */
create : function (
str 
)
{
    return cc.ShadowSprite;
},

/**
 * @method createWithSpriteFrameName
 * @param {String} arg0
 * @return {cc.ShadowSprite}
 */
createWithSpriteFrameName : function (
str 
)
{
    return cc.ShadowSprite;
},

/**
 * @method createWithSpriteFrame
 * @param {cc.SpriteFrame} arg0
 * @return {cc.ShadowSprite}
 */
createWithSpriteFrame : function (
spriteframe 
)
{
    return cc.ShadowSprite;
},

};

/**
 * @class Water
 */
cc.Water = {

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {size_object} arg3
 * @param {float} arg4
 * @param {float} arg5
 * @param {float} arg6
 * @return {cc.Water}
 */
create : function (
str, 
str, 
str, 
size, 
float, 
float, 
float 
)
{
    return cc.Water;
},

};
