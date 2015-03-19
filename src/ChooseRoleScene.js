var ChooseRoleLayer = (function(){

    // tag 3hero:1~3
    // tag bag:10 weapon:11 armour:12 helmet:13
    // tag actorinfo:101 actortext:102

    var TAG_middle = 2, TAG_left = 1, TAG_right = 3,
        TAG_bag = 10, TAG_weapon = 11, TAG_armour = 12, TAG_helmet = 13;
    // var rtt = [cc.vec3(-90, -60, 0), cc.vec3(0, 30, 0), cc.vec3(-90, -60, 0)];
    var visibleSize = cc.director.getVisibleSize();
    var pos = [cc.vec3(visibleSize.width*0.14, visibleSize.height*0.35, -180),
               cc.vec3(visibleSize.width*0.34, visibleSize.height*0.25, -40),
               cc.vec3(visibleSize.width*0.5, visibleSize.height*0.35, -180)];

    var weapon_item_pos = cc.p(832, 280), 
        armour_item_pos = cc.p(916, 280),
        helmet_item_pos = cc.p(1000, 280);

    var isMoving = false;
    var heroSize = cc.rect(155,120,465,420);

    return  cc.Layer.extend({
        _bag:null,
        _weaponItem:null,
        _armourItem:null,
        _helmetItem:null,
        _knight:null,
        _mage:null,
        _archer:null,

        ctor:function(){
            this._super();
            cc.Texture2D.setDefaultAlphaPixelFormat(0);// AUTO
            this.addBackground();
            this.addHeroes();
            this.addButton();
            this.addBag();
            cc.audioEngine.playMusic(BGM_RES.CHOOSEROLESCENEBGM, true);

            this.initTouchDispatcher();
        },

        addBackground:function(){
            //holder for background
            var node3d = new cc.Sprite3D();

            var bg = new cc.Sprite("chooseRole/cr_bk.jpg");
            bg.setAnchorPoint(0.5, 0.5);
            bg.setPosition(cc.winSize.width/2, cc.winSize.height/2);
            bg.setVertexZ(-250);
            bg.setScale(1.5);
            bg.setGlobalZOrder(-1);
            node3d.addChild(bg);
            this.addChild(node3d);
        },

        addHeroes:function(){
            var knight = new Knight();
            knight.setTag(TAG_middle);
            knight.setPosition3D(pos[1]);
            knight.setRotation3D(cc.vec3(0, 30, 0));
            knight.setScale(knight.getScale()*1.3);
            // knight.setAIEnabled(false);
            this.addChild(knight);
            this._knight = knight;

            var archer = new Archer();
            archer.setTag(TAG_left);
            archer.setPosition3D(pos[0]);
            archer.setRotation3D(cc.vec3(0, 30, 0));
            archer.setScale(archer.getScale()*1.3);
            // archer.setAIEnabled(false);
            this.addChild(archer);
            this._archer = archer;

            var mage = new Mage();
            mage.setTag(TAG_right);
            mage.setPosition3D(pos[2]);
            mage.setRotation3D(cc.vec3(0, 30, 0));
            mage.setScale(mage.getScale()*1.3);
            // mage.setAIEnabled(false);
            this.addChild(mage);
            this._mage = mage;

            this.schedule(this._hero_rotate, 0);
        },

        _hero_rotate:function(dt){
            var hero = this.getChildByTag(TAG_middle);
            var rotation = hero.getRotation3D();
            hero.setRotation3D(cc.vec3(rotation.x, rotation.y + 0.5, rotation.z));
        },

        addButton:function(){
            var button = new ccui.Button("button1.png", "", "", ccui.Widget.PLIST_TEXTURE);
            button.setNormalizedPosition(cc.p(0.34, 0.13));
            this.addChild(button);
            button.addTouchEventListener(function(sender, type){
                ReSkin.knight = {weapon:this._knight._useWeaponId, armour:this._knight._useArmourId, helmet:this._mage._useHelmetId};
                ReSkin.archer = {weapon:this._archer._useWeaponId, armour:this._archer._useArmourId, helmet:this._archer._useHelmetId};
                ReSkin.mage = {weapon:this._mage._useWeaponId, armour:this._mage._useArmourId, helmet:this._mage._useHelmetId};

                cc.audioEngine.stopMusic();
                cc.audioEngine.playEffect(BGM_RES.MAINMENUSTART);
                this.unschedule(this._hero_rotate);
                cc.director.replaceScene(new BattleScene);
            }, this);
        },

        addBag:function(){
            var bag = new cc.Sprite("#cr_bag.png");
            bag.setTag(10);
            this._bag = bag;
            this.switchTextWhenRotate()

            var bagSize = bag.getContentSize();
            weapon_item_pos = cc.p(bagSize.width*0.36, bagSize.height*0.4);
            armour_item_pos = cc.p(bagSize.width*0.54, bagSize.height*0.4);
            helmet_item_pos = cc.p(bagSize.width*0.72, bagSize.height*0.4);

            this._weaponItem = new cc.Sprite("#knight_w_1.png");
            this._weaponItem.setTag(11);
            this._weaponItem.setPosition(weapon_item_pos);
            bag.addChild(this._weaponItem);

            this._armourItem = new cc.Sprite("#knight_a_1.png");
            this._armourItem.setTag(12);
            this._armourItem.setPosition(armour_item_pos);
            bag.addChild(this._armourItem);

            this._helmetItem = new cc.Sprite("#knight_h_1.png");
            this._helmetItem.setTag(13);
            this._helmetItem.setPosition(helmet_item_pos);
            bag.addChild(this._helmetItem);

            bag.setNormalizedPosition(cc.p(0.75, 0.5));
            this.addChild(bag);

            var ttfconfig = {outlineSize : 0, fontSize : 15, glyphs:0, fontFilePath : "chooseRole/actor_param.ttf"};
            var text = "LEVEL\nATT\nHP\nDEF\nAGI\nCRT\nS.ATT";
            var text_label = cc.Label.createWithTTF(ttfconfig, text, cc.TEXT_ALIGNMENT_CENTER, 400);
            text_label.setPosition(cc.p(bagSize.width*0.45, bagSize.height*0.68));
            text_label.enableShadow(cc.color(92, 50, 31, 255), cc.size(1, -2), 0);
            bag.addChild(text_label, 1);
        },

        switchTextWhenRotate:function(){
            //get hero type
            var hero = this.getChildByTag(TAG_middle);
            var type = hero._type;
            //get bag , bagSize and judge if has child
            var bag = this._bag, size = this._bag.getContentSize();
            var actor = bag.getChildByTag(101);
            if(!!actor){
                bag.removeChildByTag(101);
                bag.removeChildByTag(102);
            }

            var ttfconfig = {outlineSize : 0, fontSize : 15, glyphs:0, fontFilePath : "chooseRole/actor_param.ttf"};
            var text = "LEVEL\nATT\nHP\nDEF\nAGI\nCRT\nS.ATT";
            var attr, point;

            if(type === "Knight"){
                actor = new cc.Sprite("#knight.png");
                point = cc.p(size.width*0.395, size.height*0.9);
                attr = "23\n"+KnightValues._normalAttack.damage+"\n"+KnightValues._hp+"\n"+KnightValues._defense+"\n"+parseInt(KnightValues._AIFrequency*100)+"\n"+KnightValues._specialAttack.damage+"\n"+KnightValues._specialAttack.damage;
            }else if(type === "Archer"){
                actor = new cc.Sprite("#archer.png");
                point = cc.p(size.width*0.4, size.height*0.905);
                attr = "23\n"+ArcherValues._normalAttack.damage+"\n"+ArcherValues._hp+"\n"+ArcherValues._defense+"\n"+parseInt(ArcherValues._AIFrequency*100)+"\n"+ArcherValues._specialAttack.damage+"\n"+ArcherValues._specialAttack.damage;
            }else if(type === "Mage"){
                actor = new cc.Sprite("#mage.png");
                point = cc.p(size.width*0.38, size.height*0.9);
                attr = "23\n"+MageValues._normalAttack.damage+"\n"+MageValues._hp+"\n"+MageValues._defense+"\n"+parseInt(MageValues._AIFrequency*100)+"\n"+MageValues._specialAttack.damage+"\n"+MageValues._specialAttack.damage;
            }
            actor.setPosition(point);

            var attr_label = cc.Label.createWithTTF(ttfconfig, attr, cc.TEXT_ALIGNMENT_CENTER, 400);
            attr_label.setPosition(cc.p(size.width*0.65, size.height*0.68));
            attr_label.enableShadow(cc.color(92, 50, 31, 255), cc.size(1, -2), 0);

            bag.addChild(actor, 1, 101);
            bag.addChild(attr_label, 1, 102);
        },

        switchItemtextureWhenRotate:function(){
            var hero = this.getChildByTag(TAG_middle);
            var type = hero._type;
            var weaponTexture, armourTexture, helmetTexture;

            if(type === "Knight"){
                weaponTexture = hero._useWeaponId === 0 ? "knight_w_1.png" : "knight_w_0.png";
                armourTexture = hero._useArmourId === 0 ? "knight_a_1.png" : "knight_a_0.png";
                helmetTexture = hero._useHelmetId === 0 ? "knight_h_1.png" : "knight_h_0.png";
            }else if(type === "Archer"){
                weaponTexture = hero._useWeaponId === 0 ? "archer_w_1.png" : "archer_w_0.png";
                armourTexture = hero._useArmourId === 0 ? "archer_a_1.png" : "archer_a_0.png";
                helmetTexture = hero._useHelmetId === 0 ? "archer_h_1.png" : "archer_h_0.png";
            }else if(type === "Mage"){
                weaponTexture = hero._useWeaponId === 0 ? "mage_w_1.png" : "mage_w_0.png";
                armourTexture = hero._useArmourId === 0 ? "mage_a_1.png" : "mage_a_0.png";
                helmetTexture = hero._useHelmetId === 0 ? "mage_h_1.png" : "mage_h_0.png";
            }

            this._weaponItem.setSpriteFrame(weaponTexture);
            this._armourItem.setSpriteFrame(armourTexture);
            this._helmetItem.setSpriteFrame(helmetTexture);
        },

        initTouchDispatcher:function(){
            //upvalues
            var self = this;
            var isRotateavaliable = false, isWeaponItemavaliable = false, isArmourItemavaliable = false, isHelmetItemavaliable = false;
            var touchbeginPt;

            function getWeaponTextureName(hero){
                if(hero._type === "Knight")
                    return (hero._useWeaponId === 0) ? "knight_w_1.png" : "knight_w_0.png";
                else if(hero._type === "Archer")
                    return (hero._useWeaponId === 0) ? "archer_w_1.png" : "archer_w_0.png";
                else if(hero._type === "Mage")
                    return (hero._useWeaponId === 0) ? "mage_w_1.png" : "mage_w_0.png";
            }

            function getArmourTextureName(hero){
                if(hero._type === "Knight")
                    return (hero._useArmourId === 0) ? "knight_a_1.png" : "knight_a_0.png";
                else if(hero._type === "Archer")
                    return (hero._useArmourId === 0) ? "archer_a_1.png" : "archer_a_0.png";
                else if(hero._type === "Mage")
                    return (hero._useArmourId === 0) ? "mage_a_1.png" : "mage_a_0.png";
            }

            function getHelmetTextureName(hero){
                if(hero._type === "Knight")
                    return (hero._useHelmetId === 0) ? "knight_h_1.png" : "knight_h_0.png";
                else if(hero._type === "Archer")
                    return (hero._useHelmetId === 0) ? "archer_h_1.png" : "archer_h_0.png";
                else if(hero._type === "Mage")
                    return (hero._useHelmetId === 0) ? "mage_h_1.png" : "mage_h_0.png";
            }

            cc.eventManager.addListener({
                event: cc.EventListener.TOUCH_ONE_BY_ONE,
                swallowTouches: true,
                onTouchBegan: function(touch, event){
                    touchbeginPt = touch.getLocation();
                    if(cc.rectContainsPoint(heroSize, touchbeginPt)){
                        isRotateavaliable = true;
                        return true;
                    }

                    touchbeginPt = self._bag.convertToNodeSpace(touchbeginPt);
                    if(cc.rectContainsPoint(self._weaponItem.getBoundingBox(), touchbeginPt)){

                        isWeaponItemavaliable = true;
                        self._weaponItem.setScale(1.7);
                        self._weaponItem.setOpacity(150);
                    }else if(cc.rectContainsPoint(self._armourItem.getBoundingBox(), touchbeginPt)){
                        isArmourItemavaliable = true;
                        self._armourItem.setScale(1.7);
                        self._armourItem.setOpacity(150);
                    }else if(cc.rectContainsPoint(self._helmetItem.getBoundingBox(), touchbeginPt)){
                        isHelmetItemavaliable = true;
                        self._helmetItem.setScale(1.7);
                        self._helmetItem.setOpacity(150);
                    }
                    return true;
                },
                onTouchMoved: function(touch, event){
                    if(isRotateavaliable && !isMoving){  //rotate
                        var dist = touch.getLocation().x - touchbeginPt.x;
                        if(dist > 50){ //right
                            self.rotate3Heroes.call(self, true);
                            isRotateavaliable = false;
                        }else if(dist < -50){ //left
                            self.rotate3Heroes(false);
                            isRotateavaliable = false;
                        }
                    }
                    
                    else if(isWeaponItemavaliable)
                        self._weaponItem.setPosition(self._bag.convertToNodeSpace(touch.getLocation()));
                    else if(isArmourItemavaliable)
                        self._armourItem.setPosition(self._bag.convertToNodeSpace(touch.getLocation()));
                    else if(isHelmetItemavaliable)
                        self._helmetItem.setPosition(self._bag.convertToNodeSpace(touch.getLocation()));
                },
                onTouchEnded: function(touch, event){
                    if(isRotateavaliable)
                        isRotateavaliable = false;

                    
                    else if(isWeaponItemavaliable){
                        isWeaponItemavaliable = false;
                        self._weaponItem.setPosition(weapon_item_pos);
                        self._weaponItem.setScale(1);
                        self._weaponItem.setOpacity(255);
                        var hero = self.getChildByTag(TAG_middle);
                        hero.switchWeapon();
                        self._weaponItem.setSpriteFrame(getWeaponTextureName(hero));
                    }else if(isArmourItemavaliable){
                        isArmourItemavaliable = false;
                        self._armourItem.setPosition(armour_item_pos);
                        self._armourItem.setScale(1);
                        self._armourItem.setOpacity(255);
                        var hero = self.getChildByTag(TAG_middle);
                        hero.switchArmour();
                        self._armourItem.setSpriteFrame(getArmourTextureName(hero));
                    }else if(isHelmetItemavaliable){
                        isHelmetItemavaliable = false;
                        self._helmetItem.setPosition(helmet_item_pos);
                        self._helmetItem.setScale(1);
                        self._helmetItem.setOpacity(255);
                        var hero = self.getChildByTag(TAG_middle);
                        hero.switchHelmet();
                        self._helmetItem.setSpriteFrame(getHelmetTextureName(hero));
                    }
                }
            }, this);
        },

        rotate3Heroes:function(isRight){
            var left = this.getChildByTag(TAG_left);
            var middle = this.getChildByTag(TAG_middle);
            var right = this.getChildByTag(TAG_right);

            middle.setRotation3D(cc.vec3(0, 30, 0));

            function playAudioWhenRotate(type){
                if(type === "Knight")
                    cc.audioEngine.playEffect(WarriorProperty.kickit);
                else if(type === "Archer")
                    cc.audioEngine.playEffect(Archerproperty.iwillfight);
                else if(type === "Mage")
                    cc.audioEngine.playEffect(MageProperty.letstrade);
            }

            var rotatetime = 0.6;
            if(isRight){
                middle.runAction(cc.sequence(
                        cc.callFunc(function(){isMoving = true;}),
                        cc.spawn(cc.moveTo(rotatetime, pos[2]).easing(cc.easeCircleActionInOut())),
                        cc.callFunc(function(){
                            isMoving = false;
                            playAudioWhenRotate(left._type);
                        })
                    ));
                left.runAction(cc.moveTo(rotatetime, pos[1]).easing(cc.easeCircleActionInOut()));
                right.runAction(cc.moveTo(rotatetime, pos[0]).easing(cc.easeCircleActionInOut()));

                middle.setTag(TAG_right);
                right.setTag(TAG_left);
                left.setTag(TAG_middle);
            }else{
                middle.runAction(cc.sequence(
                        cc.callFunc(function(){isMoving = true;}),
                        cc.spawn(cc.moveTo(rotatetime, pos[0]).easing(cc.easeCircleActionInOut())),
                        cc.callFunc(function(){
                            isMoving = false;
                            playAudioWhenRotate(right._type);
                        })
                    ));
                left.runAction(cc.moveTo(rotatetime, pos[2]).easing(cc.easeCircleActionInOut()));
                right.runAction(cc.moveTo(rotatetime, pos[1]).easing(cc.easeCircleActionInOut()));

                middle.setTag(TAG_left);
                left.setTag(TAG_right);
                right.setTag(TAG_middle);
            }

            this.switchItemtextureWhenRotate();
            this.switchTextWhenRotate();
        }

    });
})();

var ChooseRoleScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new ChooseRoleLayer();
        this.addChild(layer);
    }
});