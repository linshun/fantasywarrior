#include "jsb_cocos2dx_custom_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"
#include "EffectSprite3D.h"
#include "BillboardParticleSystem.h"
#include "CCSequence3D.h"
#include "DrawNode3D.h"
#include "EffectSprite.h"
#include "GreyShader.h"
#include "JumpBy3D.h"
#include "JumpTo3D.h"
#include "ShadowSprite.h"
#include "Water.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocos2d_Effect3D_class;
JSObject *jsb_cocos2d_Effect3D_prototype;

bool js_cocos2dx_custom_Effect3D_draw(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect3D* cobj = (cocos2d::Effect3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect3D_draw : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Mat4 arg0;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Effect3D_draw : Error processing arguments");
        cobj->draw(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect3D_draw : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_Effect3D_setTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect3D* cobj = (cocos2d::Effect3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect3D_setTarget : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Sprite3D* arg0;
        cocos2d::Mesh* arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Mesh*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Effect3D_setTarget : Error processing arguments");
        cobj->setTarget(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect3D_setTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}


void js_cocos2d_Effect3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Effect3D)", obj);
}

void js_register_cocos2dx_custom_Effect3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Effect3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Effect3D_class->name = "Effect3D";
    jsb_cocos2d_Effect3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Effect3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Effect3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Effect3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Effect3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Effect3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Effect3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Effect3D_class->finalize = js_cocos2d_Effect3D_finalize;
    jsb_cocos2d_Effect3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("draw", js_cocos2dx_custom_Effect3D_draw, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTarget", js_cocos2dx_custom_Effect3D_setTarget, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Effect3D_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Effect3D_class,
        dummy_constructor<cocos2d::Effect3D>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Effect3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Effect3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Effect3D_class;
        p->proto = jsb_cocos2d_Effect3D_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Effect3DOutline_class;
JSObject *jsb_cocos2d_Effect3DOutline_prototype;

bool js_cocos2dx_custom_Effect3DOutline_setOutlineWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect3DOutline* cobj = (cocos2d::Effect3DOutline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect3DOutline_setOutlineWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Effect3DOutline_setOutlineWidth : Error processing arguments");
        cobj->setOutlineWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect3DOutline_setOutlineWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_Effect3DOutline_setOutlineColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect3DOutline* cobj = (cocos2d::Effect3DOutline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect3DOutline_setOutlineColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Effect3DOutline_setOutlineColor : Error processing arguments");
        cobj->setOutlineColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect3DOutline_setOutlineColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_Effect3DOutline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Effect3DOutline* ret = cocos2d::Effect3DOutline::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Effect3DOutline>(cx, (cocos2d::Effect3DOutline*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_Effect3DOutline_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Effect3D_prototype;

void js_cocos2d_Effect3DOutline_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Effect3DOutline)", obj);
}

void js_register_cocos2dx_custom_Effect3DOutline(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Effect3DOutline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Effect3DOutline_class->name = "Effect3DOutline";
    jsb_cocos2d_Effect3DOutline_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Effect3DOutline_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Effect3DOutline_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Effect3DOutline_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Effect3DOutline_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Effect3DOutline_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Effect3DOutline_class->convert = JS_ConvertStub;
    jsb_cocos2d_Effect3DOutline_class->finalize = js_cocos2d_Effect3DOutline_finalize;
    jsb_cocos2d_Effect3DOutline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setOutlineWidth", js_cocos2dx_custom_Effect3DOutline_setOutlineWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOutlineColor", js_cocos2dx_custom_Effect3DOutline_setOutlineColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_Effect3DOutline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Effect3DOutline_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Effect3D_prototype),
        jsb_cocos2d_Effect3DOutline_class,
        dummy_constructor<cocos2d::Effect3DOutline>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Effect3DOutline", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Effect3DOutline> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Effect3DOutline_class;
        p->proto = jsb_cocos2d_Effect3DOutline_prototype;
        p->parentProto = jsb_cocos2d_Effect3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_EffectSprite3D_class;
JSObject *jsb_cocos2d_EffectSprite3D_prototype;

bool js_cocos2dx_custom_EffectSprite3D_setEffect3D(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite3D* cobj = (cocos2d::EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite3D_setEffect3D : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Effect3D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Effect3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite3D_setEffect3D : Error processing arguments");
        cobj->setEffect3D(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_setEffect3D : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_EffectSprite3D_addEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite3D* cobj = (cocos2d::EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite3D_addEffect : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Vec3 arg0;
        double arg1;
        ssize_t arg2;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= jsval_to_ssize(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite3D_addEffect : Error processing arguments");
        cobj->addEffect(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_addEffect : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_custom_EffectSprite3D_getMesh(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite3D* cobj = (cocos2d::EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite3D_getMesh : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Mesh *>& ret = cobj->getMesh();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_getMesh : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_EffectSprite3D_getMeshNum(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite3D* cobj = (cocos2d::EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite3D_getMeshNum : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMeshNum();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_getMeshNum : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_EffectSprite3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite3D_create : Error processing arguments");
        cocos2d::EffectSprite3D* ret = cocos2d::EffectSprite3D::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EffectSprite3D>(cx, (cocos2d::EffectSprite3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture : Error processing arguments");
        cocos2d::EffectSprite3D* ret = cocos2d::EffectSprite3D::createFromObjFileAndTexture(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EffectSprite3D>(cx, (cocos2d::EffectSprite3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite3D_prototype;

void js_cocos2d_EffectSprite3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EffectSprite3D)", obj);
}

static bool js_cocos2d_EffectSprite3D_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::EffectSprite3D *nobj = new (std::nothrow) cocos2d::EffectSprite3D();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::EffectSprite3D");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_custom_EffectSprite3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_EffectSprite3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_EffectSprite3D_class->name = "EffectSprite3D";
    jsb_cocos2d_EffectSprite3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_EffectSprite3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_EffectSprite3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_EffectSprite3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_EffectSprite3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_EffectSprite3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_EffectSprite3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_EffectSprite3D_class->finalize = js_cocos2d_EffectSprite3D_finalize;
    jsb_cocos2d_EffectSprite3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEffect3D", js_cocos2dx_custom_EffectSprite3D_setEffect3D, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addEffect", js_cocos2dx_custom_EffectSprite3D_addEffect, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMesh", js_cocos2dx_custom_EffectSprite3D_getMesh, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshNum", js_cocos2dx_custom_EffectSprite3D_getMeshNum, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_EffectSprite3D_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_EffectSprite3D_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createFromObjFileAndTexture", js_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_EffectSprite3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite3D_prototype),
        jsb_cocos2d_EffectSprite3D_class,
        dummy_constructor<cocos2d::EffectSprite3D>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EffectSprite3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::EffectSprite3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_EffectSprite3D_class;
        p->proto = jsb_cocos2d_EffectSprite3D_prototype;
        p->parentProto = jsb_cocos2d_Sprite3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_BillboardParticleSystem_class;
JSObject *jsb_cocos2d_BillboardParticleSystem_prototype;

bool js_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartSizeVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4F& ret = cobj->getStartColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getPositionType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getPositionType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getPositionType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setPosVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setPosVar : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setPosVar : Error processing arguments");
        cobj->setPosVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setPosVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSpin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndSpin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndSpin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndSpin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar : Error processing arguments");
        cobj->setRotatePerSecondVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartSpinVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRadialAccelVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndSizeVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotation : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotation : Error processing arguments");
        cobj->setRotation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRotation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel : Error processing arguments");
        cobj->setTangentialAccel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setScaleY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScaleY : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScaleY : Error processing arguments");
        cobj->setScaleY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setScaleY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setScaleX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScaleX : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScaleX : Error processing arguments");
        cobj->setScaleX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setScaleX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getRadialAccel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getRadialAccel : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRadialAccel();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getRadialAccel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadius : Error processing arguments");
        cobj->setStartRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond : Error processing arguments");
        cobj->setRotatePerSecond(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSize : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSize : Error processing arguments");
        cobj->setEndSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getGravity : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getGravity();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTangentialAccel();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadius : Error processing arguments");
        cobj->setEndRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getAngle : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getAngle();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getAngle : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndColor : Error processing arguments");
        cobj->setEndColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSpin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpin : Error processing arguments");
        cobj->setStartSpin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setDuration : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setDuration : Error processing arguments");
        cobj->setDuration(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTexture : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Texture2D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTexture : Error processing arguments");
        cobj->setTexture(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getPosVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getPosVar : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getPosVar();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getPosVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBlendAdditive();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getSpeedVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getSpeedVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSpeedVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getSpeedVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setPositionType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BillboardParticleSystem::PositionType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setPositionType : Error processing arguments");
        cobj->setPositionType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setPositionType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_stopSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_stopSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->stopSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_stopSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getSourcePosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getSourcePosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getSourcePosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getSourcePosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setLifeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setLifeVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setLifeVar : Error processing arguments");
        cobj->setLifeVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setLifeVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles : Error processing arguments");
        cobj->setTotalParticles(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar : Error processing arguments");
        cobj->setEndColorVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getAtlasIndex();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartSize : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartSize();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Texture2D* arg0;
        cocos2d::Rect arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect : Error processing arguments");
        cobj->setTextureWithRect(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar : Error processing arguments");
        cobj->setStartSpinVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_resetSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_resetSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->resetSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_resetSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex : Error processing arguments");
        cobj->setAtlasIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar : Error processing arguments");
        cobj->setTangentialAccelVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getDuration : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDuration();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled : Error processing arguments");
        cobj->setDepthTestEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar : Error processing arguments");
        cobj->setRadialAccelVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSize : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSize : Error processing arguments");
        cobj->setStartSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSpeed : Error processing arguments");
        cobj->setSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartSpin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartSpin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartSpin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartSpin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRotatePerSecond();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BillboardParticleSystem::Mode arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode : Error processing arguments");
        cobj->setEmitterMode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar : Error processing arguments");
        cobj->setEndRadiusVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isOpacityModifyRGB();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition : Error processing arguments");
        cobj->setSourcePosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndSpinVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive : Error processing arguments");
        cobj->setBlendAdditive(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setLife(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setLife : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setLife : Error processing arguments");
        cobj->setLife(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setLife : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setAngleVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAngleVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAngleVar : Error processing arguments");
        cobj->setAngleVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setAngleVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir : Error processing arguments");
        cobj->setRotationIsDir(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar : Error processing arguments");
        cobj->setEndSizeVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAngle : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setAngle : Error processing arguments");
        cobj->setAngle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setAngle : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTangentialAccelVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEmitterMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEmitterMode : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getEmitterMode();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEmitterMode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar : Error processing arguments");
        cobj->setEndSpinVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getAngleVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getAngleVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getAngleVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getAngleVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartColor : Error processing arguments");
        cobj->setStartColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRotatePerSecondVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndSize : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndSize();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getLife(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getLife : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLife();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getLife : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar : Error processing arguments");
        cobj->setSpeedVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate : Error processing arguments");
        cobj->setEmissionRate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndColorVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndColorVar : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4F& ret = cobj->getEndColorVar();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndColorVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getRotationIsDir();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setScale : Error processing arguments");
        cobj->setScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEmissionRate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEmissionRate : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEmissionRate();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEmissionRate : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4F& ret = cobj->getEndColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getLifeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getLifeVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLifeVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getLifeVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setCamera : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Camera* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Camera*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setCamera : Error processing arguments");
        cobj->setCamera(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setCamera : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar : Error processing arguments");
        cobj->setStartSizeVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB : Error processing arguments");
        cobj->setOpacityModifyRGB(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getParticleCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getParticleCount : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getParticleCount();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getParticleCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getStartRadiusVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar : Error processing arguments");
        cobj->setStartColorVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setEndSpin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpin : Error processing arguments");
        cobj->setEndSpin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setEndSpin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel : Error processing arguments");
        cobj->setRadialAccel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar : Error processing arguments");
        cobj->setStartRadiusVar(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEndRadiusVar();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_getStartColorVar(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillboardParticleSystem* cobj = (cocos2d::BillboardParticleSystem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_BillboardParticleSystem_getStartColorVar : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4F& ret = cobj->getStartColorVar();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_getStartColorVar : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::ValueMap arg0;
            ok &= jsval_to_ccvaluemap(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::BillboardParticleSystem* ret = cocos2d::BillboardParticleSystem::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::BillboardParticleSystem>(cx, (cocos2d::BillboardParticleSystem*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::BillboardParticleSystem* ret = cocos2d::BillboardParticleSystem::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::BillboardParticleSystem>(cx, (cocos2d::BillboardParticleSystem*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_custom_BillboardParticleSystem_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_custom_BillboardParticleSystem_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::BillboardParticleSystem* cobj = new (std::nothrow) cocos2d::BillboardParticleSystem();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::BillboardParticleSystem> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::BillboardParticleSystem");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_BillboardParticleSystem_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (BillboardParticleSystem)", obj);
}

void js_register_cocos2dx_custom_BillboardParticleSystem(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_BillboardParticleSystem_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_BillboardParticleSystem_class->name = "BillboardParticleSystem";
    jsb_cocos2d_BillboardParticleSystem_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_BillboardParticleSystem_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_BillboardParticleSystem_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_BillboardParticleSystem_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_BillboardParticleSystem_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_BillboardParticleSystem_class->resolve = JS_ResolveStub;
    jsb_cocos2d_BillboardParticleSystem_class->convert = JS_ConvertStub;
    jsb_cocos2d_BillboardParticleSystem_class->finalize = js_cocos2d_BillboardParticleSystem_finalize;
    jsb_cocos2d_BillboardParticleSystem_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getStartSizeVar", js_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartColor", js_cocos2dx_custom_BillboardParticleSystem_getStartColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPositionType", js_cocos2dx_custom_BillboardParticleSystem_getPositionType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosVar", js_cocos2dx_custom_BillboardParticleSystem_setPosVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndSpin", js_cocos2dx_custom_BillboardParticleSystem_getEndSpin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRotatePerSecondVar", js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartSpinVar", js_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRadialAccelVar", js_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndSizeVar", js_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRotation", js_cocos2dx_custom_BillboardParticleSystem_setRotation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTangentialAccel", js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScaleY", js_cocos2dx_custom_BillboardParticleSystem_setScaleY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScaleX", js_cocos2dx_custom_BillboardParticleSystem_setScaleX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRadialAccel", js_cocos2dx_custom_BillboardParticleSystem_getRadialAccel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartRadius", js_cocos2dx_custom_BillboardParticleSystem_setStartRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRotatePerSecond", js_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndSize", js_cocos2dx_custom_BillboardParticleSystem_setEndSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGravity", js_cocos2dx_custom_BillboardParticleSystem_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTangentialAccel", js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndRadius", js_cocos2dx_custom_BillboardParticleSystem_setEndRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpeed", js_cocos2dx_custom_BillboardParticleSystem_getSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngle", js_cocos2dx_custom_BillboardParticleSystem_getAngle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndColor", js_cocos2dx_custom_BillboardParticleSystem_setEndColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartSpin", js_cocos2dx_custom_BillboardParticleSystem_setStartSpin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDuration", js_cocos2dx_custom_BillboardParticleSystem_setDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTexture", js_cocos2dx_custom_BillboardParticleSystem_setTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPosVar", js_cocos2dx_custom_BillboardParticleSystem_getPosVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBlendAdditive", js_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpeedVar", js_cocos2dx_custom_BillboardParticleSystem_getSpeedVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionType", js_cocos2dx_custom_BillboardParticleSystem_setPositionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopSystem", js_cocos2dx_custom_BillboardParticleSystem_stopSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSourcePosition", js_cocos2dx_custom_BillboardParticleSystem_getSourcePosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLifeVar", js_cocos2dx_custom_BillboardParticleSystem_setLifeVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTotalParticles", js_cocos2dx_custom_BillboardParticleSystem_setTotalParticles, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndColorVar", js_cocos2dx_custom_BillboardParticleSystem_setEndColorVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAtlasIndex", js_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartSize", js_cocos2dx_custom_BillboardParticleSystem_getStartSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextureWithRect", js_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartSpinVar", js_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resetSystem", js_cocos2dx_custom_BillboardParticleSystem_resetSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAtlasIndex", js_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTangentialAccelVar", js_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_cocos2dx_custom_BillboardParticleSystem_getDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndRadius", js_cocos2dx_custom_BillboardParticleSystem_getEndRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDepthTestEnabled", js_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRadialAccelVar", js_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartSize", js_cocos2dx_custom_BillboardParticleSystem_setStartSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpeed", js_cocos2dx_custom_BillboardParticleSystem_setSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartSpin", js_cocos2dx_custom_BillboardParticleSystem_getStartSpin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRotatePerSecond", js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmitterMode", js_cocos2dx_custom_BillboardParticleSystem_setEmitterMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndRadiusVar", js_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isOpacityModifyRGB", js_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSourcePosition", js_cocos2dx_custom_BillboardParticleSystem_setSourcePosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndSpinVar", js_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendAdditive", js_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLife", js_cocos2dx_custom_BillboardParticleSystem_setLife, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngleVar", js_cocos2dx_custom_BillboardParticleSystem_setAngleVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRotationIsDir", js_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndSizeVar", js_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngle", js_cocos2dx_custom_BillboardParticleSystem_setAngle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTangentialAccelVar", js_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEmitterMode", js_cocos2dx_custom_BillboardParticleSystem_getEmitterMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndSpinVar", js_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngleVar", js_cocos2dx_custom_BillboardParticleSystem_getAngleVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartColor", js_cocos2dx_custom_BillboardParticleSystem_setStartColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRotatePerSecondVar", js_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndSize", js_cocos2dx_custom_BillboardParticleSystem_getEndSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLife", js_cocos2dx_custom_BillboardParticleSystem_getLife, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpeedVar", js_cocos2dx_custom_BillboardParticleSystem_setSpeedVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGravity", js_cocos2dx_custom_BillboardParticleSystem_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmissionRate", js_cocos2dx_custom_BillboardParticleSystem_setEmissionRate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndColorVar", js_cocos2dx_custom_BillboardParticleSystem_getEndColorVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRotationIsDir", js_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale", js_cocos2dx_custom_BillboardParticleSystem_setScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEmissionRate", js_cocos2dx_custom_BillboardParticleSystem_getEmissionRate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndColor", js_cocos2dx_custom_BillboardParticleSystem_getEndColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLifeVar", js_cocos2dx_custom_BillboardParticleSystem_getLifeVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCamera", js_cocos2dx_custom_BillboardParticleSystem_setCamera, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartSizeVar", js_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOpacityModifyRGB", js_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartRadius", js_cocos2dx_custom_BillboardParticleSystem_getStartRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParticleCount", js_cocos2dx_custom_BillboardParticleSystem_getParticleCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartRadiusVar", js_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartColorVar", js_cocos2dx_custom_BillboardParticleSystem_setStartColorVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndSpin", js_cocos2dx_custom_BillboardParticleSystem_setEndSpin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRadialAccel", js_cocos2dx_custom_BillboardParticleSystem_setRadialAccel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartRadiusVar", js_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndRadiusVar", js_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartColorVar", js_cocos2dx_custom_BillboardParticleSystem_getStartColorVar, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_BillboardParticleSystem_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_BillboardParticleSystem_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocos2d_BillboardParticleSystem_class,
        js_cocos2dx_custom_BillboardParticleSystem_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BillboardParticleSystem", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::BillboardParticleSystem> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_BillboardParticleSystem_class;
        p->proto = jsb_cocos2d_BillboardParticleSystem_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Sequence3D_class;
JSObject *jsb_cocos2d_Sequence3D_prototype;

bool js_cocos2dx_custom_Sequence3D_initWithActions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sequence3D* cobj = (cocos2d::Sequence3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Sequence3D_initWithActions : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vector<cocos2d::Animate3D *> arg0;
        ok &= jsval_to_ccvector(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Sequence3D_initWithActions : Error processing arguments");
        bool ret = cobj->initWithActions(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Sequence3D_initWithActions : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_Sequence3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Vector<cocos2d::Animate3D *> arg0;
        ok &= jsval_to_ccvector(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Sequence3D_create : Error processing arguments");
        cocos2d::Sequence3D* ret = cocos2d::Sequence3D::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sequence3D>(cx, (cocos2d::Sequence3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_Sequence3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_Sequence3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Sequence3D* cobj = new (std::nothrow) cocos2d::Sequence3D();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Sequence3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Sequence3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_cocos2d_Sequence3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Sequence3D)", obj);
}

void js_register_cocos2dx_custom_Sequence3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Sequence3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Sequence3D_class->name = "Sequence3D";
    jsb_cocos2d_Sequence3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Sequence3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Sequence3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Sequence3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Sequence3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Sequence3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Sequence3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Sequence3D_class->finalize = js_cocos2d_Sequence3D_finalize;
    jsb_cocos2d_Sequence3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithActions", js_cocos2dx_custom_Sequence3D_initWithActions, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_Sequence3D_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Sequence3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_cocos2d_Sequence3D_class,
        js_cocos2dx_custom_Sequence3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Sequence3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Sequence3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Sequence3D_class;
        p->proto = jsb_cocos2d_Sequence3D_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_DrawNode3D_class;
JSObject *jsb_cocos2d_DrawNode3D_prototype;

bool js_cocos2dx_custom_DrawNode3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_DrawNode3D_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_drawLine(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_drawLine : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Color4F arg2;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        ok &= jsval_to_cccolor4f(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_DrawNode3D_drawLine : Error processing arguments");
        cobj->drawLine(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_drawLine : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_onDraw(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_onDraw : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        unsigned int arg1;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_DrawNode3D_onDraw : Error processing arguments");
        cobj->onDraw(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_onDraw : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_drawCube(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_DrawNode3D_drawCube : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec3* arg0;
        cocos2d::Color4F arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Vec3*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_cccolor4f(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_DrawNode3D_drawCube : Error processing arguments");
        cobj->drawCube(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_drawCube : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_custom_DrawNode3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::DrawNode3D* ret = cocos2d::DrawNode3D::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::DrawNode3D>(cx, (cocos2d::DrawNode3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_DrawNode3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_DrawNode3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::DrawNode3D* cobj = new (std::nothrow) cocos2d::DrawNode3D();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::DrawNode3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::DrawNode3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_DrawNode3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DrawNode3D)", obj);
}

void js_register_cocos2dx_custom_DrawNode3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_DrawNode3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_DrawNode3D_class->name = "DrawNode3D";
    jsb_cocos2d_DrawNode3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_DrawNode3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_DrawNode3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_DrawNode3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_DrawNode3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_DrawNode3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_DrawNode3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_DrawNode3D_class->finalize = js_cocos2d_DrawNode3D_finalize;
    jsb_cocos2d_DrawNode3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBlendFunc", js_cocos2dx_custom_DrawNode3D_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_custom_DrawNode3D_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("drawLine", js_cocos2dx_custom_DrawNode3D_drawLine, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_cocos2dx_custom_DrawNode3D_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onDraw", js_cocos2dx_custom_DrawNode3D_onDraw, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_custom_DrawNode3D_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("drawCube", js_cocos2dx_custom_DrawNode3D_drawCube, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_DrawNode3D_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_DrawNode3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocos2d_DrawNode3D_class,
        js_cocos2dx_custom_DrawNode3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DrawNode3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::DrawNode3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_DrawNode3D_class;
        p->proto = jsb_cocos2d_DrawNode3D_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Effect_class;
JSObject *jsb_cocos2d_Effect_prototype;

bool js_cocos2dx_custom_Effect_setTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect* cobj = (cocos2d::Effect *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect_setTarget : Invalid Native Object");
    if (argc == 1) {
        cocos2d::EffectSprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::EffectSprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Effect_setTarget : Error processing arguments");
        cobj->setTarget(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect_setTarget : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_Effect_updateUniforms(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect* cobj = (cocos2d::Effect *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect_updateUniforms : Invalid Native Object");
    if (argc == 0) {
        cobj->updateUniforms();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect_updateUniforms : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_Effect_getGLProgramState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Effect* cobj = (cocos2d::Effect *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_Effect_getGLProgramState : Invalid Native Object");
    if (argc == 0) {
        cocos2d::GLProgramState* ret = cobj->getGLProgramState();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::GLProgramState>(cx, (cocos2d::GLProgramState*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_Effect_getGLProgramState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_cocos2d_Effect_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Effect)", obj);
}

void js_register_cocos2dx_custom_Effect(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Effect_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Effect_class->name = "Effect";
    jsb_cocos2d_Effect_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Effect_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Effect_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Effect_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Effect_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Effect_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Effect_class->convert = JS_ConvertStub;
    jsb_cocos2d_Effect_class->finalize = js_cocos2d_Effect_finalize;
    jsb_cocos2d_Effect_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setTarget", js_cocos2dx_custom_Effect_setTarget, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateUniforms", js_cocos2dx_custom_Effect_updateUniforms, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGLProgramState", js_cocos2dx_custom_Effect_getGLProgramState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Effect_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Effect_class,
        dummy_constructor<cocos2d::Effect>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Effect", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Effect> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Effect_class;
        p->proto = jsb_cocos2d_Effect_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_EffectNormalMapped_class;
JSObject *jsb_cocos2d_EffectNormalMapped_prototype;

bool js_cocos2dx_custom_EffectNormalMapped_setKBump(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectNormalMapped* cobj = (cocos2d::EffectNormalMapped *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectNormalMapped_setKBump : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectNormalMapped_setKBump : Error processing arguments");
        cobj->setKBump(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectNormalMapped_setKBump : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_EffectNormalMapped_setPointLight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectNormalMapped* cobj = (cocos2d::EffectNormalMapped *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectNormalMapped_setPointLight : Invalid Native Object");
    if (argc == 1) {
        cocos2d::PointLight* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::PointLight*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectNormalMapped_setPointLight : Error processing arguments");
        cobj->setPointLight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectNormalMapped_setPointLight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_EffectNormalMapped_getKBump(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectNormalMapped* cobj = (cocos2d::EffectNormalMapped *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectNormalMapped_getKBump : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getKBump();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectNormalMapped_getKBump : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_custom_EffectNormalMapped_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::EffectNormalMapped* ret = cocos2d::EffectNormalMapped::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EffectNormalMapped>(cx, (cocos2d::EffectNormalMapped*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::EffectNormalMapped* ret = cocos2d::EffectNormalMapped::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EffectNormalMapped>(cx, (cocos2d::EffectNormalMapped*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_custom_EffectNormalMapped_create : wrong number of arguments");
    return false;
}

extern JSObject *jsb_cocos2d_Effect_prototype;

void js_cocos2d_EffectNormalMapped_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EffectNormalMapped)", obj);
}

void js_register_cocos2dx_custom_EffectNormalMapped(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_EffectNormalMapped_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_EffectNormalMapped_class->name = "EffectNormalMapped";
    jsb_cocos2d_EffectNormalMapped_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_EffectNormalMapped_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_EffectNormalMapped_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_EffectNormalMapped_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_EffectNormalMapped_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_EffectNormalMapped_class->resolve = JS_ResolveStub;
    jsb_cocos2d_EffectNormalMapped_class->convert = JS_ConvertStub;
    jsb_cocos2d_EffectNormalMapped_class->finalize = js_cocos2d_EffectNormalMapped_finalize;
    jsb_cocos2d_EffectNormalMapped_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setKBump", js_cocos2dx_custom_EffectNormalMapped_setKBump, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPointLight", js_cocos2dx_custom_EffectNormalMapped_setPointLight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getKBump", js_cocos2dx_custom_EffectNormalMapped_getKBump, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_EffectNormalMapped_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_EffectNormalMapped_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Effect_prototype),
        jsb_cocos2d_EffectNormalMapped_class,
        dummy_constructor<cocos2d::EffectNormalMapped>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EffectNormalMapped", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::EffectNormalMapped> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_EffectNormalMapped_class;
        p->proto = jsb_cocos2d_EffectNormalMapped_prototype;
        p->parentProto = jsb_cocos2d_Effect_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_EffectSprite_class;
JSObject *jsb_cocos2d_EffectSprite_prototype;

bool js_cocos2dx_custom_EffectSprite_setEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite* cobj = (cocos2d::EffectSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite_setEffect : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Effect* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Effect*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite_setEffect : Error processing arguments");
        cobj->setEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite_setEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_custom_EffectSprite_addEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EffectSprite* cobj = (cocos2d::EffectSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_EffectSprite_addEffect : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Effect* arg0;
        ssize_t arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Effect*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ssize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite_addEffect : Error processing arguments");
        cobj->addEffect(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite_addEffect : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_custom_EffectSprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_EffectSprite_create : Error processing arguments");
        cocos2d::EffectSprite* ret = cocos2d::EffectSprite::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::EffectSprite>(cx, (cocos2d::EffectSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_EffectSprite_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_cocos2d_EffectSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EffectSprite)", obj);
}

void js_register_cocos2dx_custom_EffectSprite(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_EffectSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_EffectSprite_class->name = "EffectSprite";
    jsb_cocos2d_EffectSprite_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_EffectSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_EffectSprite_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_EffectSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_EffectSprite_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_EffectSprite_class->resolve = JS_ResolveStub;
    jsb_cocos2d_EffectSprite_class->convert = JS_ConvertStub;
    jsb_cocos2d_EffectSprite_class->finalize = js_cocos2d_EffectSprite_finalize;
    jsb_cocos2d_EffectSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEffect", js_cocos2dx_custom_EffectSprite_setEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addEffect", js_cocos2dx_custom_EffectSprite_addEffect, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_EffectSprite_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_EffectSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_cocos2d_EffectSprite_class,
        dummy_constructor<cocos2d::EffectSprite>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EffectSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::EffectSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_EffectSprite_class;
        p->proto = jsb_cocos2d_EffectSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_GreyShader_class;
JSObject *jsb_cocos2d_GreyShader_prototype;

bool js_cocos2dx_custom_GreyShader_setGreyShader(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Sprite* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_GreyShader_setGreyShader : Error processing arguments");
        cocos2d::GreyShader::setGreyShader(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_GreyShader_setGreyShader : wrong number of arguments");
    return false;
}



void js_cocos2d_GreyShader_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GreyShader)", obj);
}

void js_register_cocos2dx_custom_GreyShader(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_GreyShader_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_GreyShader_class->name = "GreyShader";
    jsb_cocos2d_GreyShader_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_GreyShader_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_GreyShader_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_GreyShader_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_GreyShader_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_GreyShader_class->resolve = JS_ResolveStub;
    jsb_cocos2d_GreyShader_class->convert = JS_ConvertStub;
    jsb_cocos2d_GreyShader_class->finalize = js_cocos2d_GreyShader_finalize;
    jsb_cocos2d_GreyShader_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setGreyShader", js_cocos2dx_custom_GreyShader_setGreyShader, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_GreyShader_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_GreyShader_class,
        dummy_constructor<cocos2d::GreyShader>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GreyShader", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::GreyShader> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_GreyShader_class;
        p->proto = jsb_cocos2d_GreyShader_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_JumpBy3D_class;
JSObject *jsb_cocos2d_JumpBy3D_prototype;

bool js_cocos2dx_custom_JumpBy3D_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::JumpBy3D* cobj = (cocos2d::JumpBy3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_custom_JumpBy3D_initWithDuration : Invalid Native Object");
    if (argc == 4) {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_JumpBy3D_initWithDuration : Error processing arguments");
        bool ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_custom_JumpBy3D_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_custom_JumpBy3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_JumpBy3D_create : Error processing arguments");
        cocos2d::JumpBy3D* ret = cocos2d::JumpBy3D::create(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::JumpBy3D>(cx, (cocos2d::JumpBy3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_JumpBy3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_JumpBy3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::JumpBy3D* cobj = new (std::nothrow) cocos2d::JumpBy3D();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::JumpBy3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::JumpBy3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_cocos2d_JumpBy3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JumpBy3D)", obj);
}

void js_register_cocos2dx_custom_JumpBy3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_JumpBy3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_JumpBy3D_class->name = "JumpBy3D";
    jsb_cocos2d_JumpBy3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_JumpBy3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_JumpBy3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_JumpBy3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_JumpBy3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_JumpBy3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_JumpBy3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_JumpBy3D_class->finalize = js_cocos2d_JumpBy3D_finalize;
    jsb_cocos2d_JumpBy3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithDuration", js_cocos2dx_custom_JumpBy3D_initWithDuration, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_JumpBy3D_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_JumpBy3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_cocos2d_JumpBy3D_class,
        js_cocos2dx_custom_JumpBy3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "JumpBy3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::JumpBy3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_JumpBy3D_class;
        p->proto = jsb_cocos2d_JumpBy3D_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_JumpTo3D_class;
JSObject *jsb_cocos2d_JumpTo3D_prototype;

bool js_cocos2dx_custom_JumpTo3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_JumpTo3D_create : Error processing arguments");
        cocos2d::JumpTo3D* ret = cocos2d::JumpTo3D::create(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::JumpTo3D>(cx, (cocos2d::JumpTo3D*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_JumpTo3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_JumpTo3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::JumpTo3D* cobj = new (std::nothrow) cocos2d::JumpTo3D();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::JumpTo3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::JumpTo3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_JumpBy3D_prototype;

void js_cocos2d_JumpTo3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (JumpTo3D)", obj);
}

void js_register_cocos2dx_custom_JumpTo3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_JumpTo3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_JumpTo3D_class->name = "JumpTo3D";
    jsb_cocos2d_JumpTo3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_JumpTo3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_JumpTo3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_JumpTo3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_JumpTo3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_JumpTo3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_JumpTo3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_JumpTo3D_class->finalize = js_cocos2d_JumpTo3D_finalize;
    jsb_cocos2d_JumpTo3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_JumpTo3D_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_JumpTo3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_JumpBy3D_prototype),
        jsb_cocos2d_JumpTo3D_class,
        js_cocos2dx_custom_JumpTo3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "JumpTo3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::JumpTo3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_JumpTo3D_class;
        p->proto = jsb_cocos2d_JumpTo3D_prototype;
        p->parentProto = jsb_cocos2d_JumpBy3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ShadowSprite_class;
JSObject *jsb_cocos2d_ShadowSprite_prototype;

bool js_cocos2dx_custom_ShadowSprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_ShadowSprite_create : Error processing arguments");
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ShadowSprite>(cx, (cocos2d::ShadowSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_ShadowSprite_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName : Error processing arguments");
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::createWithSpriteFrameName(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ShadowSprite>(cx, (cocos2d::ShadowSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_custom_ShadowSprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::SpriteFrame* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_ShadowSprite_createWithSpriteFrame : Error processing arguments");
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::createWithSpriteFrame(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ShadowSprite>(cx, (cocos2d::ShadowSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_ShadowSprite_createWithSpriteFrame : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_cocos2d_ShadowSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ShadowSprite)", obj);
}

void js_register_cocos2dx_custom_ShadowSprite(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ShadowSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ShadowSprite_class->name = "ShadowSprite";
    jsb_cocos2d_ShadowSprite_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ShadowSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ShadowSprite_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ShadowSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ShadowSprite_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ShadowSprite_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ShadowSprite_class->convert = JS_ConvertStub;
    jsb_cocos2d_ShadowSprite_class->finalize = js_cocos2d_ShadowSprite_finalize;
    jsb_cocos2d_ShadowSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_ShadowSprite_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrameName", js_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrame", js_cocos2dx_custom_ShadowSprite_createWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ShadowSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_cocos2d_ShadowSprite_class,
        dummy_constructor<cocos2d::ShadowSprite>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ShadowSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ShadowSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ShadowSprite_class;
        p->proto = jsb_cocos2d_ShadowSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Water_class;
JSObject *jsb_cocos2d_Water_prototype;

bool js_cocos2dx_custom_Water_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 7) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::Size arg3;
        double arg4;
        double arg5;
        double arg6;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_ccsize(cx, args.get(3), &arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !isnan(arg5);
        ok &= JS::ToNumber( cx, args.get(6), &arg6) && !isnan(arg6);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_custom_Water_create : Error processing arguments");
        cocos2d::Water* ret = cocos2d::Water::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Water>(cx, (cocos2d::Water*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_custom_Water_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_cocos2d_Water_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Water)", obj);
}

void js_register_cocos2dx_custom_Water(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Water_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Water_class->name = "Water";
    jsb_cocos2d_Water_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Water_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Water_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Water_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Water_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Water_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Water_class->convert = JS_ConvertStub;
    jsb_cocos2d_Water_class->finalize = js_cocos2d_Water_finalize;
    jsb_cocos2d_Water_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_custom_Water_create, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Water_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_cocos2d_Water_class,
        dummy_constructor<cocos2d::Water>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Water", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Water> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Water_class;
        p->proto = jsb_cocos2d_Water_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_custom(JSContext* cx, JS::HandleObject obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "cc", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    //obj = ns;

    js_register_cocos2dx_custom_JumpBy3D(cx, ns);
    js_register_cocos2dx_custom_JumpTo3D(cx, ns);
    js_register_cocos2dx_custom_Effect3D(cx, ns);
    js_register_cocos2dx_custom_EffectSprite(cx, ns);
    js_register_cocos2dx_custom_Effect(cx, ns);
    js_register_cocos2dx_custom_Water(cx, ns);
    js_register_cocos2dx_custom_GreyShader(cx, ns);
    js_register_cocos2dx_custom_EffectNormalMapped(cx, ns);
    js_register_cocos2dx_custom_BillboardParticleSystem(cx, ns);
    js_register_cocos2dx_custom_Effect3DOutline(cx, ns);
    js_register_cocos2dx_custom_DrawNode3D(cx, ns);
    js_register_cocos2dx_custom_ShadowSprite(cx, ns);
    js_register_cocos2dx_custom_EffectSprite3D(cx, ns);
    js_register_cocos2dx_custom_Sequence3D(cx, ns);
}

