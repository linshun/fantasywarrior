#ifndef __cocos2dx_custom_h__
#define __cocos2dx_custom_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_Effect3D_class;
extern JSObject *jsb_cocos2d_Effect3D_prototype;

bool js_cocos2dx_custom_Effect3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_Effect3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_Effect3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_Effect3D_draw(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Effect3D_setTarget(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Effect3DOutline_class;
extern JSObject *jsb_cocos2d_Effect3DOutline_prototype;

bool js_cocos2dx_custom_Effect3DOutline_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_Effect3DOutline_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_Effect3DOutline(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_Effect3DOutline_setOutlineWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Effect3DOutline_setOutlineColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Effect3DOutline_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_EffectSprite3D_class;
extern JSObject *jsb_cocos2d_EffectSprite3D_prototype;

bool js_cocos2dx_custom_EffectSprite3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_EffectSprite3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_EffectSprite3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_EffectSprite3D_setEffect3D(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite3D_addEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite3D_getMesh(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite3D_getMeshNum(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_BillboardParticleSystem_class;
extern JSObject *jsb_cocos2d_BillboardParticleSystem_prototype;

bool js_cocos2dx_custom_BillboardParticleSystem_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_BillboardParticleSystem_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_BillboardParticleSystem(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getPositionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setPosVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSpin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setScaleY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setScaleX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getRadialAccel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSpin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getPosVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getSpeedVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setPositionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_stopSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getSourcePosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setLifeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_resetSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSpin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setLife(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setAngleVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEmitterMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getAngleVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getLife(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndColorVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEmissionRate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getLifeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getParticleCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSpin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_getStartColorVar(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_BillboardParticleSystem_BillboardParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Sequence3D_class;
extern JSObject *jsb_cocos2d_Sequence3D_prototype;

bool js_cocos2dx_custom_Sequence3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_Sequence3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_Sequence3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_Sequence3D_initWithActions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Sequence3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Sequence3D_Sequence3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_DrawNode3D_class;
extern JSObject *jsb_cocos2d_DrawNode3D_prototype;

bool js_cocos2dx_custom_DrawNode3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_DrawNode3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_DrawNode3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_DrawNode3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_drawLine(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_onDraw(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_drawCube(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_DrawNode3D_DrawNode3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Effect_class;
extern JSObject *jsb_cocos2d_Effect_prototype;

bool js_cocos2dx_custom_Effect_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_Effect_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_Effect(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_Effect_setTarget(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Effect_updateUniforms(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_Effect_getGLProgramState(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_EffectNormalMapped_class;
extern JSObject *jsb_cocos2d_EffectNormalMapped_prototype;

bool js_cocos2dx_custom_EffectNormalMapped_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_EffectNormalMapped_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_EffectNormalMapped(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_EffectNormalMapped_setKBump(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectNormalMapped_setPointLight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectNormalMapped_getKBump(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectNormalMapped_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_EffectSprite_class;
extern JSObject *jsb_cocos2d_EffectSprite_prototype;

bool js_cocos2dx_custom_EffectSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_EffectSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_EffectSprite(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_EffectSprite_setEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite_addEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_EffectSprite_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_GreyShader_class;
extern JSObject *jsb_cocos2d_GreyShader_prototype;

bool js_cocos2dx_custom_GreyShader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_GreyShader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_GreyShader(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_GreyShader_setGreyShader(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_JumpBy3D_class;
extern JSObject *jsb_cocos2d_JumpBy3D_prototype;

bool js_cocos2dx_custom_JumpBy3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_JumpBy3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_JumpBy3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_JumpBy3D_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_JumpBy3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_JumpBy3D_JumpBy3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_JumpTo3D_class;
extern JSObject *jsb_cocos2d_JumpTo3D_prototype;

bool js_cocos2dx_custom_JumpTo3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_JumpTo3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_JumpTo3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_JumpTo3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_JumpTo3D_JumpTo3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_ShadowSprite_class;
extern JSObject *jsb_cocos2d_ShadowSprite_prototype;

bool js_cocos2dx_custom_ShadowSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_ShadowSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_ShadowSprite(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_ShadowSprite_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_custom_ShadowSprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Water_class;
extern JSObject *jsb_cocos2d_Water_prototype;

bool js_cocos2dx_custom_Water_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_custom_Water_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_custom_Water(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_custom_Water_create(JSContext *cx, uint32_t argc, jsval *vp);
#endif

