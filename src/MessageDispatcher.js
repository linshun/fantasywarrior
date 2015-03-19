(function(_G){
    var MessageQue = [];

    var MessageType = {
        BLOOD_MINUS : "BLOOD_MINUS",
        REDUCE_SCORE : "REDUCE_SCORE",
        KNOCKED : "KNOCKED",
        KNOCKEDAOE : "KNOCKEDAOE",
        SPECIAL_PERSPECTIVE : "SPECIAL_PERSPECTIVE",
        SPECIAL_KNIGHT : "SPECIAL_KNIGHT",
        SPECIAL_ARCHER : "SPECIAL_ARCHER",
        SPECIAL_MAGE : "SPECIAL_MAGE",
        ANGRY_CHANGE : "ANGRY_CHANGE"
    }

    //need param messageType and callback function
    function registerMessage(messageType, callback, ctx=_G){
        if(MessageType[messageType] == undefined || typeof callback != "function"){
            cc.log("param is invalid");
            return;
        }

        // add message to messageQue
        MessageQue.push({
            message:messageType,
            callback:callback,
            ctx:ctx
        })
    }

    function dispatchMessage(messageType, args=[]){
        if(MessageType[messageType] == undefined || typeof args != "object"){
            cc.log("param is invalid");
            return;
        }

        for(var i = 0; i < MessageQue.length; ++i){
            if(MessageQue[i].message == messageType){
                MessageQue[i].callback.apply(MessageQue[i].ctx, args);
            }
        }
    }

    function removeMessage(messageType,callback){
        if(MessageType[messageType] == undefined || typeof callback != "function"){
            cc.log("param is invalid");
            return;
        }

        for(var i = 0; i < MessageQue.length; ++i){
            if(MessageQue[i].message == messageType && messageQue[i].callback == callback){
                MessageQue.splice(i, 1);
                return;
            }
        }
    }

    _G.MessageDispatcher =  {
        registerMessage : registerMessage,
        dispatchMessage : dispatchMessage,
        removeMessage : removeMessage,
        MessageType : MessageType
    };
})(this);
