(function(_G){
    var _plistMap = {};

    var addPlistData = function(keyName, fileName){
        if(fileName == "" || keyName == "")
            return;
        if(keyName in _plistMap){
            cc.log("the keyName is exist already.");
            return;
        }
        var plistData = jsb.fileUtils.getValueMapFromFile(fileName);
        _plistMap[keyName] = plistData;

    };

    var getPlistData = function(keyName){
        if(keyName in _plistMap)
            return _plistMap[keyName];
        cc.log("can't find plistData by the specified keyName.");
    };

    _G.ParticleManager = {
        addPlistData : addPlistData,
        getPlistData : getPlistData
    };

})(this);