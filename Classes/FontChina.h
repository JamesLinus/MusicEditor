/*********************************************************
 *
 * Cocos2dx不支持中文显示
 * 修改编码后就可显示中文
 *
 ********************************************************/


#pragma once
class FontChina
{
public:
	FontChina(void);
	~FontChina(void);
	static const char* G2U(const char* gb2312);
};

