//! @file InputComponent.h

#ifndef __Dungeon_InputComponent__
#define __Dungeon_InputComponent__

#include	<Component.h>

namespace Dungeon
{
	class GameObject;

	class InputComponent : public Component
	{
	public:
		//! 构造函数
		InputComponent(GameObject* gameObject);

		//! 处理输入（重写）
		void	ProcessInput(const uint8_t* state) override;
	};
}

#endif	// __Dungeon_InputComponent__