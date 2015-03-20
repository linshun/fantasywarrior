var BattleLayer = (function(_G){

    var specialCamera = {valid:false, position:cc.p(0, 0)};
    var cameraOffset = cc.vec3(150, 0, 0);
    var cameraOffsetMin = cc.p(-300, -400);
    var cameraOffsetMax = cc.p(300, 400);

    return cc.Layer.extend({
    _uiLayer:null,
    _camera:null,
    _gameMaster:null,

    ctor:function(){
        this._super();
        this.setCascadeColorEnabled(true);
        this._gameMaster = new GameMaster(this);
        _G.gameMaster = this._gameMaster;
        this.scheduleUpdate();

        cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            onTouchBegan:this.onTouchBegan.bind(this),
            onTouchMoved:this.onTouchMoved.bind(this),
            onTouchEnded:this.onTouchEnded.bind(this)
        }, this);

        //create background
        var spriteBg = new cc.Sprite3D("model/scene/changing.c3b");
        this.addChild(spriteBg);
        spriteBg.setScale(2.65);
        spriteBg.setPosition3D(cc.vec3(-2300, -1000, 0));
        spriteBg.setRotation3D(cc.vec3(90, 0, 0));
        spriteBg.setGlobalZOrder(-10);

        var water = cc.Water.create("shader3D/water.png", "shader3D/wave1.jpg", "shader3D/18.jpg", cc.size(5500, 400), 0.77, 0.3797, 1.2);
        this.addChild(water);
        water.setPosition3D(cc.vec3(-3500, -580, -110));
        water.setAnchorPoint(0, 0);
        water.setGlobalZOrder(-10);

        //init ui layer
        var uiLayer = new BattleFieldUI();
        uiLayer.setVertexZ(-cc.director.getZEye()/4);
        uiLayer.setScale(0.25);
        uiLayer.ignoreAnchorPointForPosition(false);
        uiLayer.setGlobalZOrder(3000);
        this._uiLayer = uiLayer;

        //set camera
        this._camera = cc.Camera.createPerspective(60.0, cc.winSize.width/cc.winSize.height, 10.0, 4000.0);
        this._camera.setGlobalZOrder(10);
        this.addChild(this._camera);

        for(var i = 0; i < HeroManager.length; ++i){
            HeroManager[i]._puff.setCamera(this._camera);
        }

        this._camera.addChild(uiLayer);

        MessageDispatcher.registerMessage(MessageDispatcher.MessageType.SPECIAL_PERSPECTIVE, this.specialPerspective, this);
    },

    specialPerspective:function(param){

    },

    update:function(dt){
        this._gameMaster.update(dt);
        // this.collisionDetect(dt)
        // this.solveAttacks(dt)
        this.moveCamera(dt)
    },

    collisionDetect:function(dt){

    },

    solveAttacks:function(dt){

    },

    moveCamera:function(dt){
        if(!this._camera)
            return;

        var cameraPostion = this._camera.getPosition();
        var focusPoint = this._gameMaster.getFocusPointOfHeros();
        
        if(specialCamera.valid == true){
            //todo actor::updateAttack sent the message
        }else if(HeroManager.length > 0){
            var temp = cc.pLerp(cameraPostion, cc.p(focusPoint.x+cameraOffset.x, cameraOffset.y + focusPoint.y-cc.winSize.height*3/4), 2*dt);
            var position = cc.vec3(temp.x, temp.y, cc.winSize.height/2-0);
            this._camera.setPosition3D(position);
            this._camera.lookAt(cc.vec3(position.x, focusPoint.y, 50.0), cc.vec3(0, 0, 1));
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
            MessageDispatcher.dispatchMessage(message, [1]);
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
        cc.Texture2D.setDefaultAlphaPixelFormat(4);//RGB565
        var layer = new BattleLayer();
        this.addChild(layer);
        //this is an ugly way
        currentLayer = layer;
    }
});