//
//  CmdTool.h
//  hello-cocos
//
//  Created by why on 7/9/14.
//
//

#ifndef __hello_cocos__CmdTool__
#define __hello_cocos__CmdTool__

#include <iostream>

using namespace std;

class CmdTool
{
public:
    
    // 将服务器的命令的cmd取出
    static string getCmd(string msgString);

    // 取出命令的参数
    static string getCmdPara(string msgString);
    
    
    // fight!key=[enemyKey]&px=[position.x]&py=[position.y]&fx=[force.x]&fy=[force.y]
    
    
    // 取出打斗过程的cmdKey
    static string getCmdKey(string msgString);
    // 取出打斗过程的Position.x
    static string getFightPx(string msgString);
    // 取出打斗过程的Position.y
    static string getFightPy(string msgString);
    // 取出打斗过程的Force.x
    static string getFightFx(string msgString);
    // 取出打斗过程的Force.y
    static string getFightFy(string msgString);
    



    
};
#endif /* defined(__hello_cocos__CmdTool__) */
