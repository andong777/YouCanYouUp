//
//  CmdTool.cpp
//  hello-cocos
//
//  Created by why on 7/9/14.
//
//

#include "CmdTool.h"
#include <string.h>

string CmdTool::getCmd(string msgString){
    int tagPos = msgString.find("!");
    if (tagPos != string::npos) {
        return msgString.substr(0,tagPos);
    }
    return "";
}


string CmdTool::getCmdPara(string msgString){
    
    int tagPos = msgString.find("!");
    if (tagPos == string::npos) {
        return "";
    }
    string cmdPara = msgString.substr(tagPos+1);

    return cmdPara;
    
}


// ---------- 打斗 ----------
// fight!key=[enemyKey]&px=[position.x]&py=[position.y]&fx=[force.x]&fy=[force.y]

// 取出打斗过程的Position.x
string CmdTool::getCmdKey(string msgString){
    int pos1 = msgString.find("key");
    int pos2 = msgString.find("&px");
    
    if (pos1 == string::npos || pos2 == string::npos) {
        return "";
    }
    
    string px = msgString.substr(pos1+4,pos2-pos1-4);
    
    return px;
}

// 取出打斗过程的Position.x
string CmdTool::getFightPx(string msgString){
    int pos1 = msgString.find("px");
    int pos2 = msgString.find("&py");
    
    if (pos1 == string::npos || pos2 == string::npos) {
        return "";
    }
    
    string px = msgString.substr(pos1+3,pos2-pos1-3);
    
    return px;
}


// 取出打斗过程的Position.y
string CmdTool::getFightPy(string msgString){
    int pos1 = msgString.find("py");
    int pos2 = msgString.find("&fx");
    
    if (pos1 == string::npos || pos2 == string::npos) {
        return "";
    }
    
    string py = msgString.substr(pos1+3,pos2-pos1-3);
    
    return py;
}


// 取出打斗过程的Force.x
string CmdTool::getFightFx(string msgString){
    int pos1 = msgString.find("fx");
    int pos2 = msgString.find("&fy");
    
    if (pos1 == string::npos || pos2 == string::npos) {
        return "";
    }
    
    string fx = msgString.substr(pos1+3,pos2-pos1-3);
    
    return fx;
}


// 取出打斗过程的Force.y
string CmdTool::getFightFy(string msgString){
    int pos1 = msgString.find("fy");
    
    if (pos1 == string::npos) {
        return "";
    }
    
    string fy = msgString.substr(pos1+3);
    
    return fy;
}

