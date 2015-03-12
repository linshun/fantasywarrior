void register_all_${prefix}(JSContext* cx, JS::HandleObject obj) {
    #if $target_ns
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "${target_ns}", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "${target_ns}", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    //obj = ns;
    #end if

    #for jsclass in $sorted_classes
    #if $in_listed_classes(jsclass)
    js_register_${prefix}_${jsclass}(cx, ns);
    #end if
    #end for
}

