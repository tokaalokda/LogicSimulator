#include"Component.h"

Component::Component(GraphicsInfo* r_GfxInfo) {
	m_pGfxInfo = r_GfxInfo;
}

Component::Component() {}

Component:: ~Component() {}

void Component::setSourcePin(OutputPin* pSrcPin) { }
void Component::setDestPin(InputPin* pDstPin) { }
OutputPin* Component::getSourcePin() { return 0; }
InputPin* Component::getDestPin()
{
InputPin* garbage; 
return garbage;
}

void Component::setPins(ApplicationManager* pManager) {}; 