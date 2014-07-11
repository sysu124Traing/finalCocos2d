#include "MyMap.h"
#include "resource.h"
USING_NS_CC;

MyMap::MyMap(){
	mlayer = NULL;
	mapCount = 2;
	mapWidth = 0;
	curMap = 0;
}
MyMap* MyMap::create(Layer* layer){
	MyMap* map = new MyMap();
	map->mlayer = layer;
	map->mapa = Sprite::create(PIC_AMAP);  
	map->mapb = Sprite::create(PIC_BMAP);  

      
    // ����a������ê�����½�  
	map->mapa->setAnchorPoint(Point(0, 0));  
	map->mapa->setPosition(ccp(0, 0));  
	map->mlayer->addChild(map->mapa);  
	map->mapa->setTag(TAG_MAP);
      
    // һ�ŵ�ͼ���  
	map->mapWidth = map->mapa->getContentSize().width;  
      
    // ����b������ê�����½ǣ�λ��  
	map->mapb->setAnchorPoint(Point(0, 0));  
	map->mapb->setPosition(Point(map->mapWidth, 0));  
	map->mlayer->addChild(map->mapb);  
	map->mapb->setTag(TAG_MAP);
    
      
	return map;  
}
bool MyMap::mapReload(float xpos){
	/*int newCur = xpos/mapWidth;
	if(curMap == newCur){
		return false;
	}
	Sprite* tmpMap;
	if(0 == newCur % mapCount ){
		tmpMap = mapb;
	}
	else{
		tmpMap = mapa;
	}
	curMap = newCur;
	tmpMap->setPositionX(mapWidth*(curMap+1));*/
	if(xpos> mapb->getPositionX()+100){
		curMap++;
		mapa->setPositionX(mapWidth*(curMap+1));
		Sprite* tmp;
		tmp = mapa;
		mapa = mapb;
		mapb = tmp;
	return true;
	}
	else
	{
		return false;
	}
}
