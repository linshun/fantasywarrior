var BattleLayer = (function(_G){

    var specialCamera = {valid:false, position:cc.p(0, 0)};
    var cameraOffset = cc.math.vec3(150, 0, 0);
    var cameraOffsetMin = cc.p(-300, -400);
    var cameraOffsetMax = cc.p(300, 400);

    function collision(object){
        for(var i = 0; i < HeroManager.length; ++i){
            var sprite = HeroManager[i];
            if(sprite._isalive && sprite != object)
                solveCollision(sprite, object);
        }

        for(var i = 0; i < MonsterManager.length; ++i){
            var sprite = MonsterManager[i];
            if(sprite._isalive && sprite != object)
                solveCollision(sprite, object);
        }
    }

    function solveCollision(object1, object2){
        var miniDistance = object1._radius + object2._radius;
        var obj1Pos = object1.getPosition();
        var obj2Pos = object2.getPosition();
        var tempDistance = cc.pDistance(obj1Pos, obj2Pos);

        if(tempDistance < miniDistance){
            var angle = cc.pToAngleSelf(cc.pSub(obj1Pos, obj2Pos));
            var distance = miniDistance - tempDistance + 1;
            var distance1 = (1 - object1._mass/(object1._mass + object2._mass))*distance;
            var distance2 = distance - distance1;

            object1.setPosition(cc.pRotateByAngle(cc.pAdd(cc.p(distance1, 0), obj1Pos), obj1Pos, angle));
            object2.setPosition(cc.pRotateByAngle(cc.pAdd(cc.p(cc.p(-distance2, 0)), obj2Pos), obj2Pos, angle));
        }
    }

    function isOutOfBound(object){
        var currentPos = object.getPosition();
        
        if(currentPos.x < G.activearea.left)
            currentPos.x = G.activearea.left;

        if(currentPos.x > G.activearea.right)
            currentPos.x = G.activearea.right;

        if(currentPos.y < G.activearea.bottom)
            currentPos.y = G.activearea.bottom;

        if(currentPos.y > G.activearea.top)
            currentPos.y = G.activearea.top;

        object.setPosition(currentPos);
    }

    return cc.Layer.extend({
    _uiLayer:null,
    _camera:null,
    _gameMaster:null,

    ctor:function(){
        this._super();
        this.setCascadeColorEnabled(true);
        cc.Texture2D.setDefaultAlphaPixelFormat(4);//RGB565

        // this.scheduleUpdate();
        delayExecute(this, function(){
            this._gameMaster.init();
            this.scheduleUpdate();
        }, 0.01);

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:this.onTouchBegan.bind(this),
            onTouchMoved:this.onTouchMoved.bind(this),
            onTouchEnded:this.onTouchEnded.bind(this)
        }, this);

        //create background
        var spriteBg = new jsb.Sprite3D("model/scene/changing.c3b");
        this.addChild(spriteBg);
        spriteBg.setScale(2.65);
        spriteBg.setPosition3D(cc.math.vec3(-2300, -1000, 0));
        spriteBg.setRotation3D(cc.math.vec3(90, 0, 0));
        spriteBg.setGlobalZOrder(-10);

        var water = cc.Water.create("shader3D/water.png", "shader3D/wave1.jpg", "shader3D/18.jpg", cc.size(5500, 400), 0.77, 0.3797, 1.2);
        this.addChild(water);
        water.setPosition3D(cc.math.vec3(-3500, -580, -110));
        water.setAnchorPoint(0, 0);
        water.setGlobalZOrder(-10);

        //init ui layer
        var uiLayer = new BattleFieldUI();
        uiLayer.setVertexZ(-cc.director.getZEye()/4);
        uiLayer.setScale(0.25);
        uiLayer.ignoreAnchorPointForPosition(false);
        uiLayer.setGlobalZOrder(3000);
        this._uiLayer = uiLayer;


        this._gameMaster = new GameMaster(this);
        _G.gameMaster = this._gameMaster;
        
        //set camera
        this._camera = cc.Camera.createPerspective(60.0, cc.winSize.width/cc.winSize.height, 10.0, 4000.0);
        this._camera.setPosition3D(cc.math.vec3(0, 200, 100));
        this._camera.setGlobalZOrder(10);
        this._camera.setCameraFlag(cc.CameraFlag.USER1);
        this.addChild(this._camera);

        for(var i = 0; i < HeroManager.length; ++i){
            HeroManager[i]._puff.setCamera(this._camera);
        }

        this._camera.addChild(uiLayer);
        this.setCameraMask(cc.CameraFlag.USER1, true);

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.SPECIAL_PERSPECTIVE, this.specialPerspective, this);
    },

    specialPerspective:function(speed, pos, dur, target){
        if(specialCamera.valid == true)
            return;

        specialCamera.position = pos;
        specialCamera.valid = true;
        //TODO fix color 
        // this.setColor(cc.color(125, 125, 125));

        var self = this;
        function restoreTimeScale(){
            specialCamera.valid = false;
            self.setColor(cc.color(255, 255, 255));
            cc.director.getScheduler().setTimeScale(1.0);    
            target.setCascadeColorEnabled(true)
        }
        
        delayExecute(this, restoreTimeScale, dur);
        cc.director.getScheduler().setTimeScale(speed);
    },

    update:function(dt){
        this._gameMaster.update(dt);
        this.collisionDetect(dt)
        solveAttacks(dt)
        this.moveCamera(dt)
    },

    collisionDetect:function(dt){
        for(var i = 0; i < HeroManager.length; ++i){
            var sprite = HeroManager[i];
            if(sprite._isalive){
                collision(sprite);
                isOutOfBound(sprite);
                // sprite._effectNode.setPosition(sprite._myPos);
            }else{
                HeroManager.splice(i, 1);
            }
        }

        for(var i = 0; i < MonsterManager.length; ++i){
            var sprite = MonsterManager[i];
            if(sprite._isalive){
                collision(sprite);
                isOutOfBound(sprite);
                // sprite._effectNode.setPosition(sprite._myPos);
            }else{
                MonsterManager.splice(i, 1);
            }
        }
    },

    moveCamera:function(dt){
        if(!this._camera)
            return;

        var cameraPostion = this._camera.getPosition();
        var focusPoint = this._gameMaster.getFocusPointOfHeros();
        
        if(specialCamera.valid == true){
            var position = cc.pLerp(cameraPostion, cc.p(specialCamera.position.x, (cameraOffset.y + focusPoint.y-cc.winSize.height*3/4)*0.5), 5*dt)
            this._camera.setPosition(position);
            this._camera.lookAt(cc.math.vec3(position.x, specialCamera.position.y, 50), cc.math.vec3(0, 1, 0));
        }else if(HeroManager.length > 0){
            var temp = cc.pLerp(cameraPostion, cc.p(focusPoint.x+cameraOffset.x, cameraOffset.y + focusPoint.y-cc.winSize.height*3/4), 2*dt);
            var position = cc.math.vec3(temp.x, temp.y, cc.winSize.height/2-0);
            this._camera.setPosition3D(position);
            this._camera.lookAt(cc.math.vec3(position.x, focusPoint.y, 50.0), cc.math.vec3(0, 0, 1));
        }
    },

    onTouchBegan:function(touch, event){
        return true;
    },

    onTouchMoved:function(touch, event){
        if(this.UIcontainsPoint(touch.getLocation()) == null){
            var delta = touch.getDelta();
            cameraOffset = cc.pGetClampPoint(cc.pSub(cameraOffset, delta), cameraOffsetMin, cameraOffsetMax);
        }
    },

    onTouchEnded:function(touch, event){
        var location = touch.getLocation();
        var message = this.UIcontainsPoint(location);
        if(message !== null){
            MessageDispatcher.dispatchMessage(message);
        }
    },

    UIcontainsPoint:function(position){
        var message = null;

        var rectKnight = this._uiLayer.knightPngFrame.getBoundingBox();
        var rectArcher = this._uiLayer.archerPngFrame.getBoundingBox();
        var rectMage = this._uiLayer.magePngFrame.getBoundingBox();

        if(cc.rectContainsPoint(rectKnight, position) && this._uiLayer.knightAngry.getPercentage() == 100)
            message = MessageDispatcher.MessageType.SPECIAL_KNIGHT;
        else if(cc.rectContainsPoint(rectArcher, position) && this._uiLayer.archerAngry.getPercentage() == 100)
            message = MessageDispatcher.MessageType.SPECIAL_ARCHER;
        else if(cc.rectContainsPoint(rectMage, position) && this._uiLayer.mageAngry.getPercentage() == 100)
            message = MessageDispatcher.MessageType.SPECIAL_MAGE

        return message;
    }
});
})(this);

var BattleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        
        var layer = new BattleLayer();
        this.addChild(layer);
        //this is an ugly way
        currentLayer = layer;
    }
});
