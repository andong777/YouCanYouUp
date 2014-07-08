#include "MapLayer.h"
class ForestMapLayer : public MapLayer
{
protected:
	virtual bool init();  
	
public:
	CREATE_FUNC(ForestMapLayer);
};