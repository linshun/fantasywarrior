var MainMenuLayer = cc.Layer.extend({
    _isBloodLabelShowing:false,
    _logoSize:null,
    _logo:null,
    _pointLight:null,
    _lightSprite:null,

    ctor:function(){
        this._super();
        cc.audioEngine.playMusic(BGM_RES.MAINMENUBGM, true);
        cc.Texture2D.setDefaultAlphaPixelFormat(0);// AUTO

        this.addBg();
        this.addCloud();
        this.addLogo();
        this.addPointLight();
        this.addButton();

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan: this.onTouchBegan.bind(this),
            onTouchMoved: this.onTouchMoved.bind(this),
            onTouchEnded: this.onTouchEnded.bind(this)
        }, this);
    },

    onExit:function(){
        this._super();
        this.unscheduleAllCallbacks();
    },

    addBg:function(){
        var bg = new cc.Sprite("mainmenuscene/bg.jpg");
        bg.setPosition(cc.winSize.width/2, cc.winSize.height/2);
        this.addChild(bg);
    },

    addCloud:function(){
        var size = cc.winSize;

        var cloud0 = new cc.Sprite("#cloud1.png");
        cloud0.attr({
            scale:2,
            x:size.width*1.1,
            y:size.height*0.9
        });
        this.addChild(cloud0);

        var cloud1 = new cc.Sprite("#cloud1.png");
        cloud1.attr({
            scale:2,
            x:size.width*0.38,
            y:size.height*0.6
        });
        this.addChild(cloud1);

        var cloud2 = new cc.Sprite("#cloud2.png");
        cloud2.attr({
            scale:2,
            x:size.width*0.95,
            y:size.height*0.5
        });
        this.addChild(cloud2);

        var clouds = [cloud0, cloud1, cloud2];
        var offset = [-0.5, -1.0, -1.2];
        this.schedule(function(){
            for(var i = 0; i < 3; ++i){
                var c = clouds[i];
                var x = c.x + offset[i];
                if(x < -c.getContentSize().width)
                    x = cc.winSize.width + c.getContentSize().width;
                c.x = x;
            }
        }, 0);
    },

    addLogo:function(){
        var logo = cc.EffectSprite.create("mainmenuscene/logo.png");
        this._logoSize = logo.getContentSize();
        this._logo = logo;
        logo.setPosition(cc.winSize.width*0.53, cc.winSize.height*0.55);
        logo.setScale(0.1);
        this.addChild(logo, 4);

        logo.runAction(cc.scaleTo(2, 1.1).easing(cc.easeElasticOut()));

        //logo shake
        var time = 0;
        this.schedule(function(){
            //rand_n = range * Math.sin(math.rad(time*speed+offset))
            var rand_x = 0.1 * Math.sin(cc.degreesToRadians(time*0.5+4356));
            var rand_y = 0.1 * Math.sin(cc.degreesToRadians(time*0.37+5436));
            var rand_z = 0.1 * Math.sin(cc.degreesToRadians(time*0.2+54325));
            logo.setRotation3D(cc.math.vec3(cc.radiansToDegrees(rand_x), cc.radiansToDegrees(rand_y), cc.radiansToDegrees(rand_z)));
            time++;
        }, 0);
    },

    _getLightSprite:function(){
        var ls = new cc.Sprite("#light.png");
        ls.setBlendFunc(cc.ONE, cc.ONE_MINUS_SRC_ALPHA);
        ls.setScale(1.2);
        ls.setPosition3D(cc.math.vec3(cc.winSize.width*0.5, cc.winSize.height*0.5, 0));
        this._lightSprite = ls;

        var light_size = ls.getContentSize(),
            rotate_top = cc.rotateBy(0.05, 50),
            rotate_bottom = cc.rotateBy(0.05, -50),
            origin_degree = 20,
            sprite_scale = 0,
            opacity = 100,
            scale = cc.scaleTo(0.07, 0.7);

        var swing_l1 = new cc.Sprite("#swing_l1.png");
        swing_l1.setScale(sprite_scale);
        swing_l1.setAnchorPoint(cc.p(1, 0));
        swing_l1.setPosition(light_size.width/2, light_size.height/2);
        swing_l1.setRotation(-origin_degree);
        swing_l1.setOpacity(opacity);
        swing_l1.setBlendFunc(cc.ONE, cc.ONE);
        swing_l1.runAction(cc.spawn(cc.sequence(rotate_top, rotate_top.reverse()), scale).repeatForever());
        ls.addChild(swing_l1, 5);

        var swing_l2 = new cc.Sprite("#swing_l2.png");
        swing_l2.setScale(sprite_scale);
        swing_l2.setAnchorPoint(cc.p(1, 1));
        swing_l2.setPosition(light_size.width/2, light_size.height/2);
        swing_l2.setRotation(origin_degree);
        swing_l2.setOpacity(opacity);
        swing_l2.runAction(cc.spawn(cc.sequence(rotate_bottom, rotate_bottom.reverse()), scale).repeatForever());
        ls.addChild(swing_l2, 5);

        var swing_r1 = new cc.Sprite("#swing_r1.png");
        swing_r1.setScale(sprite_scale);
        swing_r1.setAnchorPoint(cc.p(0, 0));
        swing_r1.setPosition(light_size.width/2, light_size.height/2);
        swing_r1.setRotation(-origin_degree);
        swing_r1.setOpacity(opacity);
        swing_r1.setBlendFunc(cc.ONE, cc.ONE);
        swing_r1.runAction(cc.spawn(cc.sequence(rotate_top.reverse(), rotate_top.clone()), scale).repeatForever());
        ls.addChild(swing_r1, 5);

        var swing_r2 = new cc.Sprite("#swing_r2.png");
        swing_r2.setScale(sprite_scale);
        swing_r2.setAnchorPoint(cc.p(0, 1));
        swing_r2.setPosition(light_size.width/2, light_size.height/2);
        swing_r2.setRotation(-origin_degree);
        swing_r2.setOpacity(opacity);
        swing_r2.runAction(cc.spawn(cc.sequence(rotate_bottom.reverse(), rotate_bottom.clone()), scale).repeatForever());
        ls.addChild(swing_r2, 5);
    },

    _getBezierAction:function(){
        var size = cc.winSize;
        return cc.sequence(
                cc.bezierTo(5, [
                    cc.p(size.width*0.9, size.height*0.4),
                    cc.p(size.width*0.9, size.height*0.8),
                    cc.p(size.width*0.5, size.height*0.8)
                ]),
                cc.bezierTo(5, [
                    cc.p(size.width*0.1, size.height*0.8),
                    cc.p(size.width*0.1, size.height*0.4),
                    cc.p(size.width*0.5, size.height*0.4)
                ])
            ).repeatForever();
    },

    addPointLight:function(){
        // add point light
        this._pointLight = jsb.PointLight.create(cc.math.vec3(0, 0, -100), cc.color(255, 255, 255), 10000);
        this._pointLight.setCameraMask(1);
        this._pointLight.setEnabled(true);

        // add light sprite
        this._getLightSprite();
        this._lightSprite.addChild(this._pointLight);
        this.addChild(this._lightSprite, 10);
        this._lightSprite.setVertexZ(100);

        //effectNormalMap
        var effectNormalMapped = cc.EffectNormalMapped.create("mainmenuscene/logo_normal.png");
        effectNormalMapped.setPointLight(this._pointLight);
        effectNormalMapped.setKBump(50);
        this._logo.setEffect(effectNormalMapped);

        var size = cc.winSize;
        this._lightSprite.runAction(this._getBezierAction());
    },

    addButton:function(){
        var button = new ccui.Button("start.png", "", "", ccui.Widget.PLIST_TEXTURE);
        button.setPosition(cc.winSize.width*0.5, cc.winSize.height*0.15);
        this.addChild(button, 4);
        button.addTouchEventListener(function(sender, type){
            if(type == ccui.Widget.TOUCH_ENDED){
                cc.audioEngine.playEffect(BGM_RES.MAINMENUSTART);
                cc.audioEngine.stopMusic();
                cc.director.replaceScene(new ChooseRoleScene());
            }
        }, this);

        var effectNormalMapped = cc.EffectNormalMapped.create("mainmenuscene/start_normal.png");
        effectNormalMapped.setPointLight(this._pointLight);
        effectNormalMapped.setKBump(100);

        var effectSprite = cc.EffectSprite.create("mainmenuscene/start.png");
        effectSprite.setPosition(cc.winSize.width*0.5, cc.winSize.height*0.15);
        this.addChild(effectSprite, 5);
        effectSprite.setEffect(effectNormalMapped);
    },

    movePoint:function(dt){
        var lightSpritePos = this._lightSprite.getPosition();
        var point = cc.pLerp(lightSpritePos, this._prePosition, dt*2);
        this._lightSprite.setPosition(point);
    },

    onTouchBegan:function(touch, event){
        this._lightSprite.stopAllActions();
        this._prePosition = touch.getLocation();
        this.schedule(this.movePoint, 0);
        return true;
    },

    onTouchMoved:function(touch, event){
        this._prePosition = touch.getLocation();
    },

    onTouchEnded:function(touch, event){
        this.unschedule(this.movePoint);
        this._lightSprite.stopAllActions();
        this._lightSprite.runAction(this._getBezierAction());
    }
});

var MainMenuScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new MainMenuLayer();
        this.addChild(layer);
    }
});